/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	iic.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.10.21
描  述: linux i2c总线框架，实现对外设时钟pcf8563数据的读取和写入
备  注:	
修改记录:

  1.  日期: 2025.10.21
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/cdev.h>
#include <linux/bcd.h>
#include <linux/uaccess.h>
#include <linux/fs.h>

#define DEVICE_NAME "pcf8563"           //设备名称

#define PCF8563_CTL_STATUS_1    0x00    //控制寄存器 1
#define PCF8563_CTL_STATUS_2    0x01    //控制寄存器 2
#define PCF8563_VL_SECONDS      0x02    //时间：秒
#define PCF8563_VL_MINUTES      0x03    //时间：分
#define PCF8563_VL_HOURS        0x04    //时间：时
#define PCF8563_VL_DAYS         0x05    //时间：日
#define PCF8563_VL_WEEKDAYS     0x06    //时间：星期
#define PCF8563_VL_MONTHS       0x07    //时间：月
#define PCF8563_VL_YEARS        0x08    //时间：年

#define PCF8563_YEAR_BASE       2000    //基础年份

/// @brief 表示时间和日期信息
typedef struct _PCF8563_TIME
{
    int Sec;                            //秒
    int Min;                            //分
    int Hour;                           //小时
    int Day;                            //日
    int WDay;                           //星期
    int Month;                          //月
    int Year;                           //年
}PCF8563_TIME, *PPCF8563_TIME;

/// @brief pcf8563设备信息
typedef struct _PCF8563_DEV
{
    struct i2c_client* ptI2C_Client;    //i2c子设备
    dev_t DevID;                        //设备号
    struct cdev CharDev;                //字符设备
    struct class* pCharClass;           //类
    struct device* pDevice;             //设备
    int Major;                          //主设备号
    int Minor;                          //次设备号
}PCF8563_DEV, *PPCF8563_DEV;

struct _PCF8563_DEV g_tPCF8563_Dev = { 0 };     //pcf8563设备

/// @brief 对字符设备文件 open 回调函数
/// @param _pInode 
/// @param _pFp 文件描述符
/// @return <0--执行失败，=0--执行成功
int PCF8563_Open(struct inode* _pInode, struct file* _pFp);  

/// @brief 对字符设备文件 read 回调函数
/// @param _pFp 文件描述符
/// @param _pBuf 读取缓冲区
/// @param _Len 读取缓冲区长度
/// @param _pOffset 读取缓冲区偏移量
/// @return <0--执行失败，>=0--执行成功
ssize_t PCF8563_Read(struct file* _pFp, char __user* _pBuf, size_t _Len, loff_t* _pOffset);                    

/// @brief 对字符设备文件 write 回调函数
/// @param _pFp 文件描述符
/// @param _pBuf 读取缓冲区
/// @param _Len 读取缓冲区长度
/// @param _pOffset 读取缓冲区偏移量
/// @return <0--执行失败，>=0--执行成功
ssize_t PCF8563_Write(struct file* _pFp, const char __user* _pBuf, size_t _Len, loff_t* _pOffset);

/// @brief 对字符设备文件 release 回调函数
/// @param _pInode 
/// @param _pFp 文件描述符
/// @return <0--执行失败，=0--执行成功
int PCF8563_Release(struct inode* _pInode, struct file* _pFp);  

static struct file_operations g_tFile_Operations = 
{
    .owner = THIS_MODULE,
    .open = PCF8563_Open,
    .read = PCF8563_Read,
    .write = PCF8563_Write,
    .release = PCF8563_Release,
};

/// @brief 向pcf8563设备多个连续的寄存器写入数据
/// @param _ptPCF8563_Dev 
/// @param _Reg 
/// @param _pBuf 
/// @param _Len 
/// @return 0--成功;!0--失败
static int PCF8563_Write_Reg(PPCF8563_DEV _ptPCF8563_Dev, u8 _Reg, u8* _pBuf, u8 _Len)
{
    if(!_ptPCF8563_Dev || !_pBuf || _Len <= 0)
    {
        printk(KERN_ERR "%s, input paramter is err\n", __func__);
        return -EINVAL;
    }

    struct i2c_client* ptI2C_Client = _ptPCF8563_Dev->ptI2C_Client;
    struct i2c_msg tI2C_Msg = { 0 };
    u8 uchSendBuf[17] = { 0 };              //因为pcf8563寄存器数量为16个，第一个buf[0]用于存储寄存器首地址，所以buf大小设置为17即可
    int nRet = 0;

    if(_Len > (sizeof(uchSendBuf) / sizeof(uchSendBuf[0]) - 1))
    {
        dev_err(&ptI2C_Client->dev, "%s, input paramter is err, _Len = %d\n", __func__, _Len);
        return -EINVAL;
    }

    uchSendBuf[0] = _Reg;                   //寄存器首地址
    memcpy(&uchSendBuf[1], _pBuf, _Len);

    tI2C_Msg.addr = ptI2C_Client->addr;     //pcf8563从机地址
    tI2C_Msg.flags = ptI2C_Client->flags;   //标记为写数据
    tI2C_Msg.buf = uchSendBuf;              //要写入的数据缓冲区
    tI2C_Msg.len = _Len + 1;                //要写入的数据长度

    nRet = i2c_transfer(ptI2C_Client->adapter, &tI2C_Msg, 1);       //返回写入的数据数量，此情况正常应该返回1，表示写入了1个 struct i2c_msg 数据
    if(nRet != 1)       
    {
        dev_err(&ptI2C_Client->dev, "%s, i2c_transfer err, _Reg = %d, _Len = %d\n", __func__, _Reg, _Len);
        return -EIO;
    }

    return 0;
}

/// @brief 从pcf8563设备读取多个寄存器数据
/// @param _ptPCF8563_Dev 
/// @param _Reg 
/// @param _pBuf 
/// @param _Len 
/// @return 0--成功;!0--失败
static int PCF8563_Read_Reg(PPCF8563_DEV _ptPCF8563_Dev, u8 _Reg, u8* _pBuf, u8 _Len)
{
    if(!_ptPCF8563_Dev || !_pBuf || _Len <= 0)
    {
        printk(KERN_ERR "%s, input paramter is err\n", __func__);
        return -EINVAL;
    }

    struct i2c_client* ptI2C_Client = _ptPCF8563_Dev->ptI2C_Client;
    struct i2c_msg tI2C_Msgs[2];
    int nRet = 0;

    tI2C_Msgs[0].addr = ptI2C_Client->addr;      //pcf8563从机地址
    tI2C_Msgs[0].flags = ptI2C_Client->flags;    //标记为写数据
    tI2C_Msgs[0].buf = &_Reg;                    //要写入的数据缓冲区
    tI2C_Msgs[0].len = 1;                        //要写入的数据长度

    tI2C_Msgs[1].addr = ptI2C_Client->addr;                  //pcf8563从机地址
    tI2C_Msgs[1].flags = ptI2C_Client->flags | I2C_M_RD;     //标记为写数据
    tI2C_Msgs[1].buf = _pBuf;                                //要写入的数据缓冲区
    tI2C_Msgs[1].len = _Len;                                 //要写入的数据长度

    nRet = i2c_transfer(ptI2C_Client->adapter, tI2C_Msgs, 2);       //返回写入的数据数量，此情况正常应该返回2，表示写入了2个 struct i2c_msg 数据
    if(nRet != 2)       
    {
        dev_err(&ptI2C_Client->dev, "%s, i2c_transfer err, _Reg = %d, _Len = %d\n", __func__, _Reg, _Len);
        return -EIO;
    }

    return 0;
}

int PCF8563_Open(struct inode* _pInode, struct file* _pFp)
{
    _pFp->private_data = &g_tPCF8563_Dev;                                            //设置私有数据
    printk(KERN_ALERT "PCF8563_Open success.\n");

    return 0;
}

ssize_t PCF8563_Read(struct file* _pFp, char __user* _pBuf, size_t _Len, loff_t* _pOffset)
{
    PPCF8563_DEV ptPCF8563_Dev = _pFp->private_data;
    struct i2c_client* ptI2C_Client = ptPCF8563_Dev->ptI2C_Client;
    u8 uchReadBuf[17] = { 0 };                                                      //读取缓冲
    int nRet = 0;
    PCF8563_TIME tPCF8563_Time = { 0 };

    if(!_pBuf || _Len != sizeof tPCF8563_Time)
    {
        dev_err(&ptI2C_Client->dev, "PCF8563_Read input parameter is err\n");
        return EINVAL;
    }

    //读取pcf8563从设备寄存器全部信息
    nRet = PCF8563_Read_Reg(ptPCF8563_Dev, PCF8563_CTL_STATUS_1, uchReadBuf, 9);
    if(nRet)
    {
        dev_err(&ptI2C_Client->dev, "PCF8563_Read PCF8563_Read_Reg is err\n");
        return nRet;
    }   

    //校验时钟完整性
    if((uchReadBuf[PCF8563_VL_SECONDS] & 0x80))
    {
        dev_err(&ptI2C_Client->dev, "PCF8563_Read PCF8563_Read_Reg is err\n");
        return -EINVAL;
    }

    //pcf8563数据是以BCD码进行存储的，需要将BCD码转换为十进制数据
    tPCF8563_Time.Sec = bcd2bin(uchReadBuf[PCF8563_VL_SECONDS] & 0x7f);     
    tPCF8563_Time.Min = bcd2bin(uchReadBuf[PCF8563_VL_MINUTES] & 0x7f);  
    tPCF8563_Time.Hour = bcd2bin(uchReadBuf[PCF8563_VL_HOURS] & 0x3f);  
    tPCF8563_Time.Day = bcd2bin(uchReadBuf[PCF8563_VL_DAYS] & 0x3f);  
    tPCF8563_Time.WDay = bcd2bin(uchReadBuf[PCF8563_VL_WEEKDAYS] & 0x7);  
    tPCF8563_Time.Month = bcd2bin(uchReadBuf[PCF8563_VL_MONTHS] & 0x1f);  
    tPCF8563_Time.Year = bcd2bin(uchReadBuf[PCF8563_VL_YEARS] & 0x7f) + PCF8563_YEAR_BASE;  

    return copy_to_user(_pBuf, &tPCF8563_Time, _Len);
}

ssize_t PCF8563_Write(struct file* _pFp, const char __user* _pBuf, size_t _Len, loff_t* _pOffset)
{
    PPCF8563_DEV ptPCF8563_Dev = _pFp->private_data;
    struct i2c_client* ptI2C_Client = ptPCF8563_Dev->ptI2C_Client;
    u8 uchWriteBuf[17] = { 0 };                                                      //读取缓冲
    int nRet = 0;
    PCF8563_TIME tPCF8563_Time = { 0 };

    if(!_pBuf || _Len != sizeof tPCF8563_Time)
    {
        dev_err(&ptI2C_Client->dev, "PCF8563_Write input parameter is err\n");
        return EINVAL;
    }

    nRet = copy_from_user(&tPCF8563_Time, _pBuf, _Len);
    if(nRet)
    {
        dev_err(&ptI2C_Client->dev, "PCF8563_Write copy_from_user is err\n");
        return nRet;
    }

    uchWriteBuf[PCF8563_VL_SECONDS] = bin2bcd(tPCF8563_Time.Sec);
    uchWriteBuf[PCF8563_VL_MINUTES] = bin2bcd(tPCF8563_Time.Min);
    uchWriteBuf[PCF8563_VL_HOURS] = bin2bcd(tPCF8563_Time.Hour);
    uchWriteBuf[PCF8563_VL_DAYS] = bin2bcd(tPCF8563_Time.Day);
    uchWriteBuf[PCF8563_VL_WEEKDAYS] = bin2bcd(tPCF8563_Time.WDay);
    uchWriteBuf[PCF8563_VL_MONTHS] = bin2bcd(tPCF8563_Time.Month);
    uchWriteBuf[PCF8563_VL_YEARS] = bin2bcd(tPCF8563_Time.Year - PCF8563_YEAR_BASE);

    //将数据写入寄存器
    nRet = PCF8563_Write_Reg(ptPCF8563_Dev, PCF8563_VL_SECONDS, &(uchWriteBuf[PCF8563_VL_SECONDS]), 7);
    if(nRet)
    {
        dev_err(&ptI2C_Client->dev, "PCF8563_Write PCF8563_Write_Reg is err\n");
        return nRet;
    }

    return 0;
}

int PCF8563_Release(struct inode* _pInode, struct file* _pFp)
{
    return 0;
}

static int PCF8563_Init(PPCF8563_DEV _ptPCF8563_Dev)
{
    struct i2c_client* ptI2C_Client = _ptPCF8563_Dev->ptI2C_Client;
    u8 chReadData = 0;       //读取数据缓冲
    int nRet = 0;

    nRet = PCF8563_Read_Reg(_ptPCF8563_Dev, PCF8563_VL_SECONDS, &chReadData, sizeof chReadData);        //读取VL_SECONDS寄存器
    if(nRet != 0)
    {
        dev_err(&ptI2C_Client->dev, "PCF8563_Init PCF8563_Read_Reg is err\n");
        return nRet;
    }

    chReadData &= 0x7F;      //将寄存器最高1位清零，也就是将VL位清零

    return PCF8563_Write_Reg(_ptPCF8563_Dev, PCF8563_VL_SECONDS, &chReadData, sizeof chReadData);       //写入VL_SECONDS寄存器
}

int PCF8563_Probe(struct i2c_client *client, const struct i2c_device_id *id)
{
    int nRet = 0;

    g_tPCF8563_Dev.ptI2C_Client = client;
    nRet = PCF8563_Init(&g_tPCF8563_Dev);
    if(nRet)
    {   
        dev_err(&client->dev, "PCF8563_Probe PCF8563_Init is err\n");
        return nRet;
    }   

    //注册字符设备驱动
    //指定设备号
    if(g_tPCF8563_Dev.Major)
    {
        g_tPCF8563_Dev.DevID = MKDEV(g_tPCF8563_Dev.Major, 0);
        
        nRet = register_chrdev_region(g_tPCF8563_Dev.DevID, 1, DEVICE_NAME);
        if(nRet)
            goto out1;
    }
    else        //分配设备号
    {
        nRet = alloc_chrdev_region(&g_tPCF8563_Dev.DevID, 0, 1, DEVICE_NAME);
        if(nRet)
            goto out1;
        
        g_tPCF8563_Dev.Major = MAJOR(g_tPCF8563_Dev.DevID);
        g_tPCF8563_Dev.Minor = MINOR(g_tPCF8563_Dev.DevID);
    }

    printk(KERN_ALERT "PCF8563_Init major = %d, minor = %d.\n", g_tPCF8563_Dev.Major, g_tPCF8563_Dev.Minor);

    //初始化cdev
    g_tPCF8563_Dev.CharDev.owner = THIS_MODULE;
    cdev_init(&g_tPCF8563_Dev.CharDev, &g_tFile_Operations);

    //添加一个cdev
    nRet = cdev_add(&g_tPCF8563_Dev.CharDev, g_tPCF8563_Dev.DevID, 1);
    if(nRet)
        goto out2;

    //创建类
    g_tPCF8563_Dev.pCharClass = class_create(THIS_MODULE, DEVICE_NAME);
    if(IS_ERR(g_tPCF8563_Dev.pCharClass))
    {
       nRet = PTR_ERR(g_tPCF8563_Dev.pCharClass); 
       goto out3;
    }

    //创建设备
    g_tPCF8563_Dev.pDevice = device_create(g_tPCF8563_Dev.pCharClass, NULL, g_tPCF8563_Dev.DevID, NULL, DEVICE_NAME);
    if(IS_ERR(g_tPCF8563_Dev.pDevice))
    {
       nRet = PTR_ERR(g_tPCF8563_Dev.pDevice); 
       goto out4;
    }

    i2c_set_clientdata(client, &g_tPCF8563_Dev);

    printk(KERN_ALERT "PCF8563_Init success.\n");

    return nRet;                //正常退出

out4:
    class_destroy(g_tPCF8563_Dev.pCharClass);

out3:
    cdev_del(&g_tPCF8563_Dev.CharDev);

out2:
    unregister_chrdev_region(g_tPCF8563_Dev.DevID, 1);

out1:

    return -EPERM;
}

int PCF8563_Remove(struct i2c_client *client)
{
    PPCF8563_DEV ptPCF8563_Dev = i2c_get_clientdata(client);

    device_destroy(ptPCF8563_Dev->pCharClass, ptPCF8563_Dev->DevID);          //注销设备

    class_destroy(ptPCF8563_Dev->pCharClass);                                //注销类

    cdev_del(&ptPCF8563_Dev->CharDev);                                       //删除cdev

    unregister_chrdev_region(ptPCF8563_Dev->DevID, 1);                       //注销设备号
    
    printk(KERN_ALERT "PCF8563_Remove success.\n");

    return 0;
}

static const struct of_device_id g_tPCF8563_Of_Match[] = {
    { .compatible = "zynq-pcf8563" },
    {}
};

static struct i2c_driver g_tPCF8563_Driver = {
    .driver = {
        .name = "pcf8563",
        .of_match_table = g_tPCF8563_Of_Match,
    },
    .probe = PCF8563_Probe,
    .remove = PCF8563_Remove
};

module_i2c_driver(g_tPCF8563_Driver);

MODULE_AUTHOR("qianrui");
MODULE_DESCRIPTION("Philips pcf8563 rtc driver");
MODULE_LICENSE("GPL");


