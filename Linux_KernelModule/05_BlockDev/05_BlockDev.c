/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	04_VirtualNIC.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.08.07
描  述: 编写一个简易的块设备驱动
备  注:	
修改记录:

  1.  日期: 2024.08.07
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.1.0
  1.  日期: 2024.08.08
	  作者: 钱锐
	  内容:
		  1) 在原来无法正常编译文件的基础上，优化了代码实现；
	  版本:V0.2.0

*************************************************/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/vmalloc.h>
#include <linux/fs.h>
#include <linux/blkdev.h>
#include <linux/blk_types.h>
#include <linux/genhd.h>
#include <linux/errno.h>
#include <linux/hdreg.h>
#include <linux/bio.h>
#include <linux/blk-mq.h>
#include <asm/uaccess.h>

#define RTN_FAILURE -2
#define RTN_SUCCESS 0
#define LOG                 printk

#define DEVICE_NAME         "05_BlockDev"
#define DEVICE_CAPACITY     1024                //设备容量（扇区数量）
#define SECTOR_SIZE         512                 //扇区大小

/// @brief 执行shell指令
/// @param _pCmd shell指令s
void DealShellCmd(char* _pCmd);

/// @brief 在dev创建块设备驱动文件 
void Blk_Create_Dev(void);

/// @brief 删除dev目录下的块设备文件 
void Blk_Delete_Dev(void);

/// @brief 打开块设备
/// @param _pBlkDev 
/// @param _Mode 
/// @return 
static int Blk_Dev_Open(struct block_device* _pBlkDev, fmode_t _Mode);

/// @brief 关闭块设备
/// @param _pGenDisk 
/// @param _Mode 
static void Blk_Dev_Release(struct gendisk* _pGenDisk, fmode_t _Mode);

/// @brief 处理用户态对块设备的读、写请求
/// @param _pRequestQue 
static void Blk_Dev_Request(struct request_queue* _pRequestQue);

typedef struct _BLKDEV_INFO
{
    u8* m_pchDevData;                           //块设备数据缓冲起始地址
    int m_nMajor_Num;                           //块设备主版本号
    struct request_queue* m_ptReq_Que;          //块设备的请求队列
    struct gendisk* m_ptGenDisk;                //块设备的
} BLKDEV_INFO, *PBLKDEV_INFO;

static BLKDEV_INFO g_tBlkDev_Info;              //块设备信息

static const struct block_device_operations g_tBlkDec_Operat = {
    .owner = THIS_MODULE,
    .open = Blk_Dev_Open,
    .release = Blk_Dev_Release,
};


static int Blk_Dev_Open(struct block_device* _pBlkDev, fmode_t _Mode)
{
    LOG(KERN_INFO "Blk_Dev_Open is success.\n");
    return 0;
}

static void Blk_Dev_Release(struct gendisk* _pGenDisk, fmode_t _Mode)
{
    LOG(KERN_INFO "Blk_Dev_Release is success.\n");
}

void DealShellCmd(char* _pCmd)
{
    char cmdPath[] = "/bin/bash";    
    
    char* cmdArgv[] = {cmdPath, "-c", _pCmd, NULL};   
    
    char* cmdEnvp[] = {"HOME=/", "PATH=/sbin:/bin:/usr/bin", NULL};    

    call_usermodehelper(cmdPath, cmdArgv, cmdEnvp, UMH_WAIT_PROC); 
}

static void Blk_Dev_Request(struct request_queue* _pRequestQue)
{
    struct request* ptRequset = NULL;

    while ((ptRequset = blk_get_request(_pRequestQue, REQ_OP_READ & REQ_OP_WRITE, 0)) != NULL)
    {
        struct bio_vec tBio_Vec;
        struct req_iterator tReq_Iterator;
        sector_t nSectorOffset;                                             //用户读取的起始地址的扇区偏移数量
        unsigned int unOperateLen = 0;                                      //用户操作数据的长度
        u8* pchStartBuf = NULL;                                             //用户传入的缓冲区起始地址

        nSectorOffset = blk_rq_pos(ptRequset);
        unOperateLen = blk_rq_cur_sectors(ptRequset) * SECTOR_SIZE;

        rq_for_each_segment(tBio_Vec, ptRequset, tReq_Iterator)
        {
            pchStartBuf = page_address(tBio_Vec.bv_page) + tBio_Vec.bv_offset;
            if(rq_data_dir(ptRequset) == READ)
            {
                memcpy(pchStartBuf, g_tBlkDev_Info.m_pchDevData + nSectorOffset * SECTOR_SIZE, unOperateLen);
            }
            else if(rq_data_dir(ptRequset) == WRITE)
            {
                memcpy(g_tBlkDev_Info.m_pchDevData + nSectorOffset * SECTOR_SIZE, pchStartBuf, unOperateLen);
            }

            nSectorOffset += unOperateLen / SECTOR_SIZE;
        }

        __blk_mq_end_request(ptRequset, 0);
    }
    
}

void Blk_Create_Dev(void)
{
    char chCmd[257] = { 0 };                //命令

    sprintf(chCmd, "sudo mknod -m 666 /dev/%s b %d 0", DEVICE_NAME, g_tBlkDev_Info.m_nMajor_Num);

    LOG(KERN_INFO "%s", chCmd); 
    DealShellCmd(chCmd);
}

void Blk_Delete_Dev(void)
{
    char chCmd[257] = { 0 };                //命令

    sprintf(chCmd, "sudo rm -rf /dev/%s", DEVICE_NAME);

    DealShellCmd(chCmd);
}

/// @brief 块设备驱动初始化
/// @param  
/// @return 
static int __init Blk_Init(void)
{
    g_tBlkDev_Info.m_pchDevData = vmalloc(DEVICE_CAPACITY * SECTOR_SIZE);       //分配一大块内存，用于模拟块设备驱动缓冲
    if(g_tBlkDev_Info.m_pchDevData == NULL)
    {
        LOG(KERN_ERR "Blk_Init vmalloc is err.\n");
        return -ENOMEM;
    }

    g_tBlkDev_Info.m_nMajor_Num = register_blkdev(0, DEVICE_NAME);              //注册块设备的主设备号
    if(g_tBlkDev_Info.m_nMajor_Num <= 0)
    {
        LOG(KERN_ERR "Blk_Init register_blkdev is err.\n");
        vfree(g_tBlkDev_Info.m_pchDevData);
        return -EBUSY;
    }

    g_tBlkDev_Info.m_ptReq_Que = blk_alloc_queue(Blk_Dev_Request);              //初始化块设备的请求队列（用户态多并发操作的read、write操作，都是提交队列请求）
    if(g_tBlkDev_Info.m_ptReq_Que == NULL)
    {
        LOG(KERN_ERR "Blk_Init blk_init_queue is err.\n");
        unregister_blkdev(g_tBlkDev_Info.m_nMajor_Num, DEVICE_NAME);
        vfree(g_tBlkDev_Info.m_pchDevData);
        return -ENOMEM;
    }

    struct gendisk* ptGenDisk = alloc_disk(1);                                  //申请一个 struct gendisk 资源
    if (ptGenDisk == NULL)
    {
        LOG(KERN_ERR "Blk_Init alloc_disk is err.\n");
        blk_cleanup_queue(g_tBlkDev_Info.m_ptReq_Que);
        unregister_blkdev(g_tBlkDev_Info.m_nMajor_Num, DEVICE_NAME);
        vfree(g_tBlkDev_Info.m_pchDevData);
        return -ENOMEM;
    }
    
    ptGenDisk->major = g_tBlkDev_Info.m_nMajor_Num;
    ptGenDisk->first_minor = 0;
    ptGenDisk->fops = &g_tBlkDec_Operat;                                        //注册块设备一般事件回调函数
    ptGenDisk->queue = g_tBlkDev_Info.m_ptReq_Que;
    snprintf(ptGenDisk->disk_name, 32, DEVICE_NAME);
    set_capacity(ptGenDisk, DEVICE_CAPACITY);
    add_disk(ptGenDisk);                                                        //注册块设备

    g_tBlkDev_Info.m_ptGenDisk = ptGenDisk;
    
    LOG(KERN_INFO "Blk_Init is success.\n");
    return RTN_SUCCESS;
}

static void __exit Blk_Exit(void)
{
    del_gendisk(g_tBlkDev_Info.m_ptGenDisk);                                    //删除块设备
    put_disk(g_tBlkDev_Info.m_ptGenDisk);                                       //释放资源
    blk_cleanup_queue(g_tBlkDev_Info.m_ptReq_Que);
    unregister_blkdev(g_tBlkDev_Info.m_nMajor_Num, DEVICE_NAME);
    vfree(g_tBlkDev_Info.m_pchDevData);
    
    LOG(KERN_INFO "Blk_Exit is success.\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("qianrui");
MODULE_VERSION("0.2.0");
MODULE_DESCRIPTION("This is a simple block device");

module_init(Blk_Init);
module_exit(Blk_Exit);
