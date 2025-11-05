/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	spi.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.11.05
描  述: linux spi总线框架示例
备  注:	
修改记录:

  1.  日期: 2025.11.05
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/cdev.h>
#include <linux/bcd.h>
#include <linux/uaccess.h>
#include <linux/fs.h>

#define DEVICE_NAME "myspi"           //设备名称

/// @brief spi设备信息
typedef struct _MYSPI_DEV
{
    struct spi_device* pSPI;            //spi从设备对象指针
    dev_t DevID;                        //设备号
    struct cdev CharDev;                //字符设备
    struct class* pCharClass;           //类
    struct device* pDevice;             //设备
    int Major;                          //主设备号
    int Minor;                          //次设备号
}MYSPI_DEV, *PMYSPI_DEV;

struct _MYSPI_DEV g_tMySPI_Dev = { 0 };     //spi设备

/// @brief 对字符设备文件 open 回调函数
/// @param _pInode 
/// @param _pFp 文件描述符
/// @return <0--执行失败，=0--执行成功
int MySPI_Open(struct inode* _pInode, struct file* _pFp);  

/// @brief 对字符设备文件 read 回调函数
/// @param _pFp 文件描述符
/// @param _pBuf 读取缓冲区
/// @param _Len 读取缓冲区长度
/// @param _pOffset 读取缓冲区偏移量
/// @return <0--执行失败，>=0--执行成功
ssize_t MySPI_Read(struct file* _pFp, char __user* _pBuf, size_t _Len, loff_t* _pOffset);                    

/// @brief 对字符设备文件 write 回调函数
/// @param _pFp 文件描述符
/// @param _pBuf 读取缓冲区
/// @param _Len 读取缓冲区长度
/// @param _pOffset 读取缓冲区偏移量
/// @return <0--执行失败，>=0--执行成功
ssize_t MySPI_Write(struct file* _pFp, const char __user* _pBuf, size_t _Len, loff_t* _pOffset);

/// @brief 对字符设备文件 release 回调函数
/// @param _pInode 
/// @param _pFp 文件描述符
/// @return <0--执行失败，=0--执行成功
int MySPI_Release(struct inode* _pInode, struct file* _pFp);  

static struct file_operations g_tFile_Operations = 
{
    .owner = THIS_MODULE,
    .open = MySPI_Open,
    .read = MySPI_Read,
    .write = MySPI_Write,
    .release = MySPI_Release,
};

int MySPI_Open(struct inode* _pInode, struct file* _pFp)
{
    _pFp->private_data = &g_tMySPI_Dev;                                            //设置私有数据
    printk(KERN_ALERT "MySPI_Open success.\n");

    return 0;
}

ssize_t MySPI_Read(struct file* _pFp, char __user* _pBuf, size_t _Len, loff_t* _pOffset)
{
    int nRtn = 0;                                           //返回值
    PMYSPI_DEV ptMySPI_Dev = _pFp->private_data;
    struct spi_message tSPI_Msg = { 0 };
    struct spi_transfer tSPITransfers[2] = { 0 };
    unsigned char chTx[5] = { 0 };                          //发送缓冲
    unsigned char chRx[5] = { 0 };                          //接收缓冲

    //填充两次传输序列              
    tSPITransfers[0].tx_buf = chTx;                          //发送数据缓存区
    tSPITransfers[0].bits_per_word = 8;                      //一次传输8个bit
    tSPITransfers[0].len = 1;                                //传输长度为1个字节

    tSPITransfers[1].tx_buf = chRx;                          //接收数据缓存区
    tSPITransfers[1].bits_per_word = 8;                      //一次传输8个bit
    tSPITransfers[1].len = 1;                                //传输长度为1个字节

    chTx[0] = 0x45;                                         //要读取的从机设备寄存器地址（举个例子，假设寄存器地址是一个字节）
    spi_message_init(&tSPI_Msg);                            //初始化 struct spi_message
    spi_message_add_tail(&(tSPITransfers[0]), &tSPI_Msg);    //将发送序列添加到 struct spi_message
    spi_message_add_tail(&(tSPITransfers[1]), &tSPI_Msg);    //将接收序列添加到 struct spi_message
    nRtn = spi_sync(ptMySPI_Dev->pSPI, &tSPI_Msg);
    if(nRtn)
    {
        dev_err(&ptMySPI_Dev->pSPI->dev, "spi_sync is err\n");
        return nRtn;
    }

    return copy_to_user(_pBuf, chRx, 1);
}

ssize_t MySPI_Write(struct file* _pFp, const char __user* _pBuf, size_t _Len, loff_t* _pOffset)
{
    int nRtn = 0;                                           //返回值
    PMYSPI_DEV ptMySPI_Dev = _pFp->private_data;
    struct spi_message tSPI_Msg = { 0 };
    struct spi_transfer tSPITransfer = { 0 };
    unsigned char chTx[5] = { 0 };                          //发送缓冲
      
    tSPITransfer.tx_buf = chTx;                          //发送数据缓存区
    tSPITransfer.bits_per_word = 8;                      //一次传输8个bit
    tSPITransfer.len = 2;                                //传输长度为2个字节
    
    chTx[0] = 0x55;                                         //要读取的从机设备寄存器地址（举个例子，假设寄存器地址是一个字节）
    chTx[1] = 0xff;                                         //要往该寄存器写入的数据

    spi_message_init(&tSPI_Msg);                            //初始化 struct spi_message
    spi_message_add_tail(&tSPITransfer, &tSPI_Msg);         //将发送序列添加到 struct spi_message
    nRtn = spi_sync(ptMySPI_Dev->pSPI, &tSPI_Msg);
    if(nRtn)
    {
        dev_err(&ptMySPI_Dev->pSPI->dev, "spi_sync is err\n");
        return nRtn;
    }

    return nRtn;
}

int MySPI_Release(struct inode* _pInode, struct file* _pFp)
{
    return 0;
}

static int MySPI_Init(PMYSPI_DEV _ptMySPI_Dev)
{
    return 0;      
}

int MySPI_Probe(struct spi_device *spi)
{
    int nRet = 0;

    g_tMySPI_Dev.pSPI = spi;
    nRet = MySPI_Init(&g_tMySPI_Dev);
    if(nRet)
    {   
        dev_err(&spi->dev, "MySPI_Probe MySPI_Init is err\n");
        return nRet;
    }   

    //注册字符设备驱动
    //指定设备号
    if(g_tMySPI_Dev.Major)
    {
        g_tMySPI_Dev.DevID = MKDEV(g_tMySPI_Dev.Major, 0);
        
        nRet = register_chrdev_region(g_tMySPI_Dev.DevID, 1, DEVICE_NAME);
        if(nRet)
            goto out1;
    }
    else        //分配设备号
    {
        nRet = alloc_chrdev_region(&g_tMySPI_Dev.DevID, 0, 1, DEVICE_NAME);
        if(nRet)
            goto out1;
        
        g_tMySPI_Dev.Major = MAJOR(g_tMySPI_Dev.DevID);
        g_tMySPI_Dev.Minor = MINOR(g_tMySPI_Dev.DevID);
    }

    printk(KERN_ALERT "MySPI_Init major = %d, minor = %d.\n", g_tMySPI_Dev.Major, g_tMySPI_Dev.Minor);

    //初始化cdev
    g_tMySPI_Dev.CharDev.owner = THIS_MODULE;
    cdev_init(&g_tMySPI_Dev.CharDev, &g_tFile_Operations);

    //添加一个cdev
    nRet = cdev_add(&g_tMySPI_Dev.CharDev, g_tMySPI_Dev.DevID, 1);
    if(nRet)
        goto out2;

    //创建类
    g_tMySPI_Dev.pCharClass = class_create(THIS_MODULE, DEVICE_NAME);
    if(IS_ERR(g_tMySPI_Dev.pCharClass))
    {
       nRet = PTR_ERR(g_tMySPI_Dev.pCharClass); 
       goto out3;
    }

    //创建设备
    g_tMySPI_Dev.pDevice = device_create(g_tMySPI_Dev.pCharClass, NULL, g_tMySPI_Dev.DevID, NULL, DEVICE_NAME);
    if(IS_ERR(g_tMySPI_Dev.pDevice))
    {
       nRet = PTR_ERR(g_tMySPI_Dev.pDevice); 
       goto out4;
    }

    spi_set_drvdata(spi, &g_tMySPI_Dev);

    printk(KERN_ALERT "MySPI_Init success.\n");

    return nRet;                //正常退出

out4:
    class_destroy(g_tMySPI_Dev.pCharClass);

out3:
    cdev_del(&g_tMySPI_Dev.CharDev);

out2:
    unregister_chrdev_region(g_tMySPI_Dev.DevID, 1);

out1:

    return -EPERM;
}

int MySPI_Remove(struct spi_device *spi)
{
    PMYSPI_DEV ptMySPI_Dev = spi_get_drvdata(spi);

    device_destroy(ptMySPI_Dev->pCharClass, ptMySPI_Dev->DevID);          //注销设备

    class_destroy(ptMySPI_Dev->pCharClass);                                //注销类

    cdev_del(&ptMySPI_Dev->CharDev);                                       //删除cdev

    unregister_chrdev_region(ptMySPI_Dev->DevID, 1);                       //注销设备号
    
    printk(KERN_ALERT "MySPI_Remove success.\n");

    return 0;
}

static const struct of_device_id g_tMySPI_Of_Match[] = {
    { .compatible = "zynq-MySPI" },
    {}
};

static struct spi_driver g_tMySPI_Driver = {
    .driver = {
        .name = "MySPI",
        .of_match_table = g_tMySPI_Of_Match,
    },
    .probe = MySPI_Probe,
    .remove = MySPI_Remove
};

module_spi_driver(g_tMySPI_Driver);

MODULE_AUTHOR("qianrui");
MODULE_DESCRIPTION("Virtual device driver based on spi subsystem");
MODULE_LICENSE("GPL");

