/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	ft5426.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.11.12
描  述: linux ft5426芯片的触摸屏驱动
备  注:	
修改记录:

  1.  日期: 2025.11.12
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
#include <linux/input.h>
#include <linux/input/mt.h>
#include <linux/delay.h>
#include <linux/of_gpio.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>

#define FT5426_DEVIDE_MODE_REG  0x00    //模式寄存器
#define FT5426_TD_STATUS_REG    0x02    //状态寄存器
#define FT5426_TOUCH_DATA_REG   0x03    //触摸数据读取的起始寄存器
#define FT5426_ID_G_MODE_REG    0xA4    //中断模式寄存器

#define MAX_SUPPORT_POINTS      5       //ft5426最大支持5点触摸

#define TOUCH_EVENT_DOWN        0x00    //按下
#define TOUCH_EVENT_UP          0x01    //抬起
#define TOUCH_EVENT_ON          0x02    //接触
#define TOUCH_EVENT_RESERVED    0x03    //保留

/// @brief ft5426设备信息
typedef struct _EDT_FT5426_DEV
{
    struct i2c_client* ptI2C_Client;    //i2c子设备
    struct input_dev* ptInputDev;       //输入设备
    int ResetGpio;                      //复位gpio
    int IrqGpio;                        //中断gpio
}EDT_FT5426_DEV, *PEDT_FT5426_DEV;

/// @brief 向FT5426设备多个连续的寄存器写入数据
/// @param _ptFT5426_Dev 
/// @param _Reg 
/// @param _pBuf 
/// @param _Len 
/// @return 0--成功;!0--失败
static int FT5426_Write_Reg(PEDT_FT5426_DEV _ptFT5426_Dev, u8 _Reg, u8* _pBuf, u8 _Len)
{
    struct i2c_client* ptI2C_Client = _ptFT5426_Dev->ptI2C_Client;
    struct i2c_msg tI2C_Msg = { 0 };
    u8 uchSendBuf[17] = { 0 };              //因为FT5426寄存器数量为16个，第一个buf[0]用于存储寄存器首地址，所以buf大小设置为17即可
    int nRet = 0;

    if(!_ptFT5426_Dev || !_pBuf || _Len <= 0)
    {
        printk(KERN_ERR "%s, input paramter is err\n", __func__);
        return -EINVAL;
    }

    if(_Len > (sizeof(uchSendBuf) / sizeof(uchSendBuf[0]) - 1))
    {
        dev_err(&ptI2C_Client->dev, "%s, input paramter is err, _Len = %d\n", __func__, _Len);
        return -EINVAL;
    }

    uchSendBuf[0] = _Reg;                   //寄存器首地址
    memcpy(&uchSendBuf[1], _pBuf, _Len);

    tI2C_Msg.addr = ptI2C_Client->addr;     //FT5426从机地址
    tI2C_Msg.flags = ptI2C_Client->flags;   //标记为写数据
    tI2C_Msg.buf = uchSendBuf;              //要写入的数据缓冲区
    tI2C_Msg.len = _Len + 1;                //要写入的数据长度

    nRet = i2c_transfer(ptI2C_Client->adapter, &tI2C_Msg, 1);       //返回写入的数据数量，此情况正常应该返回1，表示写入了1个 struct i2c_msg 数据
    if(nRet != 1)       
    {
        dev_err(&ptI2C_Client->dev, "%s, i2c_transfer err, _Reg = %d, _Len = %d, nRet = %d\n", __func__, _Reg, _Len, nRet);
        return -EIO;
    }

    return 0;
}

/// @brief 从FT5426设备读取多个寄存器数据
/// @param _ptFT5426_Dev 
/// @param _Reg 
/// @param _pBuf 
/// @param _Len 
/// @return 0--成功;!0--失败
static int FT5426_Read_Reg(PEDT_FT5426_DEV _ptFT5426_Dev, u8 _Reg, u8* _pBuf, u8 _Len)
{
    struct i2c_client* ptI2C_Client = _ptFT5426_Dev->ptI2C_Client;
    struct i2c_msg tI2C_Msgs[2];
    int nRet = 0;

    if(!_ptFT5426_Dev || !_pBuf || _Len <= 0)
    {
        printk(KERN_ERR "%s, input paramter is err\n", __func__);
        return -EINVAL;
    }

    tI2C_Msgs[0].addr = ptI2C_Client->addr;      //FT5426从机地址
    tI2C_Msgs[0].flags = ptI2C_Client->flags;    //标记为写数据
    tI2C_Msgs[0].buf = &_Reg;                    //要写入的数据缓冲区
    tI2C_Msgs[0].len = 1;                        //要写入的数据长度

    tI2C_Msgs[1].addr = ptI2C_Client->addr;                  //FT5426从机地址
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

/// @brief 复位ft5426触摸芯片
/// @param _ptEdt_FT5426_Dev 
/// @return 
static int EDT_FT5426_Reset(PEDT_FT5426_DEV _ptEdt_FT5426_Dev)
{
    int nRet = 0;
    struct i2c_client *ptI2c_Client = _ptEdt_FT5426_Dev->ptI2C_Client;
    struct device* ptDev = &ptI2c_Client->dev;

    _ptEdt_FT5426_Dev->ResetGpio = of_get_named_gpio(ptDev->of_node, "reset-gpio", 0);
    if(!gpio_is_valid(_ptEdt_FT5426_Dev->ResetGpio))
    {
        dev_err(&ptI2c_Client->dev, "Failed to get reset-gpio\n");
        return -EINVAL;
    }

    //向gpio子系统申请使用gpio
    nRet = devm_gpio_request_one(ptDev, _ptEdt_FT5426_Dev->ResetGpio, GPIOF_OUT_INIT_LOW, "ft5426 reset gpio");
    if(nRet)
    {
        printk(KERN_ERR "Failed to devm_gpio_request_one reset-gpio\n");
        return -EINVAL;
    }

    msleep(50);

    gpio_set_value_cansleep(_ptEdt_FT5426_Dev->ResetGpio, 1);       //拉高复位引脚，结束复位
    msleep(300);

    return nRet;
}

/// @brief 中断处理函数
/// @param _Irq 中断号
/// @param _pArgv 中断参数
/// @return IRQ_HANDLED--成功;
static irqreturn_t EDT_FT5426_Isr(int _Irq, void *_pArgv)
{
    int nRet = 0;
    PEDT_FT5426_DEV ptEdt_FT5426_Dev = _pArgv;
    struct i2c_client *ptI2c_Client = ptEdt_FT5426_Dev->ptI2C_Client;
    u8 uchRdBuf[30] = { 0 };
    int i, nType, nX, nY, nID;
    bool bIsDown = false;           //是否按下

    nRet = FT5426_Read_Reg(ptEdt_FT5426_Dev, FT5426_TD_STATUS_REG, uchRdBuf, 29);
    if(nRet)
    {
        dev_err(&ptI2c_Client->dev, "EDT_FT5426_Isr FT5426_Read_Reg is err\n");
        return IRQ_HANDLED;
    }

    for (i = 0; i < MAX_SUPPORT_POINTS; i++)
    {
        u8* puchBuf = &(uchRdBuf[6 * i + 1]);

        /* 以第一个触摸点为例，寄存器 TOUCH1_XH(地址 0x03)，各 bit 位描述如下：
        * bit7:6 Event flag 0:按下 1:释放 2:接触 3:没有事件
        * bit5:4 保留
        * bit3:0 X 轴触摸点的 11~8 位
        */
        nType = puchBuf[0] >> 6;
        if(nType == TOUCH_EVENT_RESERVED)
            continue;

        //我们所使用的触摸屏和 FT5426 是反过来的
        nX = ((puchBuf[2] << 8) | puchBuf[3]) & 0x0fff;
        nY = ((puchBuf[0] << 8) | puchBuf[1]) & 0x0fff;

        /* 以第一个触摸点为例，寄存器 TOUCH1_YH(地址 0x05)，各 bit 位描述如下：
        * bit7:4 Touch ID 触摸 ID，表示是哪个触摸点
        * bit3:0 Y 轴触摸点的 11~8 位。
        */
        nID = (puchBuf[2] >> 4) & 0x0f;
        bIsDown = nType != TOUCH_EVENT_UP;

        input_mt_slot(ptEdt_FT5426_Dev->ptInputDev, nID);
        input_mt_report_slot_state(ptEdt_FT5426_Dev->ptInputDev, MT_TOOL_FINGER, bIsDown);

        if(!bIsDown)
            continue;
        
        input_report_abs(ptEdt_FT5426_Dev->ptInputDev, ABS_MT_POSITION_X, nX);
        input_report_abs(ptEdt_FT5426_Dev->ptInputDev, ABS_MT_POSITION_Y, nY);
    }

    input_mt_report_pointer_emulation(ptEdt_FT5426_Dev->ptInputDev, true);
    input_sync(ptEdt_FT5426_Dev->ptInputDev);

    return IRQ_HANDLED;
}

static int EDT_FT5426_TS_Irq(PEDT_FT5426_DEV _ptEdt_FT5426_Dev)
{
    int nRet = 0;
    struct i2c_client *ptI2c_Client = _ptEdt_FT5426_Dev->ptI2C_Client;
    struct device* ptDev = &ptI2c_Client->dev;

    _ptEdt_FT5426_Dev->IrqGpio = of_get_named_gpio(ptDev->of_node, "interrupt-gpio", 0);
    if(!gpio_is_valid(_ptEdt_FT5426_Dev->IrqGpio))
    {
        dev_err(&ptI2c_Client->dev, "Failed to get interrupt-gpio\n");
        return -EINVAL;
    }

    //向gpio子系统申请使用gpio
    nRet = devm_gpio_request_one(ptDev, _ptEdt_FT5426_Dev->IrqGpio, GPIOF_OUT_INIT_LOW, "ft5426 interrupt gpio");
    if(nRet)
    {
        printk(KERN_ERR "Failed to devm_gpio_request_one interrupt-gpio\n");
        return -EINVAL;
    }

    //注册中断服务函数
    nRet = devm_request_threaded_irq(
        ptDev, 
        ptI2c_Client->irq, 
        NULL, 
        EDT_FT5426_Isr, 
        IRQF_TRIGGER_FALLING | IRQF_ONESHOT, 
        ptI2c_Client->name, 
        _ptEdt_FT5426_Dev
        );
    if(nRet)
    {
        dev_err(&ptI2c_Client->dev, "Failed to devm_request_threaded_irq\n");
        return -EINVAL;
    }

    return nRet;
}

int FT5426_Probe(struct i2c_client *client, const struct i2c_device_id *id)
{
    int nRet = 0;
    PEDT_FT5426_DEV ptEdt_FT5426_Dev = NULL;
    struct input_dev* ptInputDev = NULL;
    u8 uchData = 0;

    ptEdt_FT5426_Dev = devm_kzalloc(&client->dev, sizeof(EDT_FT5426_DEV), GFP_KERNEL);
    if(!ptEdt_FT5426_Dev)
    {
        dev_err(&client->dev, "FT5426_Probe devm_kzalloc is err\n");
        return -ENOMEM;
    }

    ptEdt_FT5426_Dev->ptI2C_Client = client;

    nRet = EDT_FT5426_Reset(ptEdt_FT5426_Dev);
    if(nRet)
    {
        dev_err(&client->dev, "FT5426_Probe EDT_FT5426_Reset is err\n");
        return nRet;
    }

    //初始化ft5426
    uchData = 0;
    nRet = FT5426_Write_Reg(ptEdt_FT5426_Dev, FT5426_DEVIDE_MODE_REG, &uchData, 1);
    if(nRet)
    {
        dev_err(&client->dev, "FT5426_Probe FT5426_Write_Reg FT5426_DEVIDE_MODE_REG is err\n");
        return nRet;
    }

    msleep(1);

    uchData = 1;
    nRet = FT5426_Write_Reg(ptEdt_FT5426_Dev, FT5426_ID_G_MODE_REG, &uchData, 1);
    if(nRet)
    {
        dev_err(&client->dev, "FT5426_Probe FT5426_Write_Reg FT5426_ID_G_MODE_REG is err\n");
        return nRet;
    }

    //申请和注册中断服务函数
    nRet = EDT_FT5426_TS_Irq(ptEdt_FT5426_Dev);
    if(nRet)
    {
        dev_err(&client->dev, "FT5426_Probe EDT_FT5426_TS_Irq is err\n");
        return nRet;
    }

    //注册input设备
    ptInputDev = devm_input_allocate_device(&client->dev);
    if(!ptInputDev)
    {
        dev_err(&client->dev, "FT5426_Probe devm_input_allocate_device is err\n");
        return nRet;
    }

    ptEdt_FT5426_Dev->ptInputDev = ptInputDev;
    ptInputDev->name = "focal tech ft5426 touch screen";
    ptInputDev->id.bustype = BUS_I2C;

    input_set_abs_params(ptInputDev, ABS_MT_POSITION_X, 0, 800, 0, 0);
    input_set_abs_params(ptInputDev, ABS_MT_POSITION_Y, 0, 480, 0, 0);

    nRet = input_mt_init_slots(ptInputDev, MAX_SUPPORT_POINTS, INPUT_MT_DIRECT);
    if(nRet)
    {
        dev_err(&client->dev, "FT5426_Probe input_mt_init_slots is err\n");
        return nRet;
    }

    nRet = input_register_device(ptInputDev);
    if(nRet)
    {
        dev_err(&client->dev, "FT5426_Probe input_register_device is err\n");
        return nRet;
    }

    device_init_wakeup(&client->dev, 1);
    i2c_set_clientdata(client, ptEdt_FT5426_Dev);

    printk(KERN_ALERT "FT5426_Probe success.\n");

    return nRet;
}

int FT5426_Remove(struct i2c_client *client)
{
    PEDT_FT5426_DEV ptEdt_FT5426_Dev = i2c_get_clientdata(client);

    input_unregister_device(ptEdt_FT5426_Dev->ptInputDev);

    printk(KERN_ALERT "FT5426_Remove success.\n");

    return 0;
}

static const struct of_device_id g_tFT5426_Of_Match[] = {
    { .compatible = "edt,edt-ft5426" },
    {}
};

static struct i2c_driver g_tFT5426_Driver = {
    .driver = {
        .name = "edt-ft5426",
        .of_match_table = g_tFT5426_Of_Match,
    },
    .probe = FT5426_Probe,
    .remove = FT5426_Remove
};

module_i2c_driver(g_tFT5426_Driver);

MODULE_AUTHOR("qianrui");
MODULE_DESCRIPTION("FT5426 iic driver");
MODULE_LICENSE("GPL");


