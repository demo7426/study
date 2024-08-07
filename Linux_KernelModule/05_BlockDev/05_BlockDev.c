/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	04_VirtualNIC.c
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.08.07
描  述: 编写一个简易的块设备驱动
备  注:	
修改记录:

  1.  日期: 2024.08.07
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V1.0.0

*************************************************/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#define RTN_FAILURE -2
#define RTN_SUCCESS 0
#define LOG                 printk

#define DEVICE_NAME         __FILE__
#define DEVICE_CAPACITY     1024                //设备容量（扇区数量）
#define SECTOR_SIZE         512                 //扇区大小

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

static void Blk_Dev_Request(struct request_queue* _pRequestQue)
{
    struct request* ptRequset = NULL;
    struct bio_vec tBio_Vec;
    struct req_iterator tReq_Iterator;
    sector_t nSectorOffset;                                            //用户读取的起始地址的扇区偏移数量
    unsigned int unOperateLen = 0;                                      //用户操作数据的长度
    u8* pchStartBuf = NULL;                                             //用户传入的缓冲区起始地址

    while ((ptRequset = blk_fetch_request(_pRequestQue)) != NULL)
    {
        nSectorOffset = blk_rq_pos(ptRequset);
        unReadLen = blk_rq_cur_sectors(ptRequset) * SECTOR_SIZE;

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

        __blk_end_request_all(ptRequset, 0);
    }
    


}

/// @brief 块设备驱动初始化
/// @param  
/// @return 
static int __init Blk_Init(void)
{
    g_tBlkDev_Info.m_pchDevData = vmalloc(DEVICE_CAPACITY * SECTOR_SIZE);
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

    g_tBlkDev_Info.m_ptReq_Que = blk_init_queue(Blk_Dev_Request, NULL);         //初始化块设备的请求队列（用户态多并发操作的read、write操作，都是提交队列请求）
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
        blk_clean_queue(g_tBlkDev_Info.m_ptReq_Que);
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
    blk_clean_queue(g_tBlkDev_Info.m_ptReq_Que);
    unregister_blkdev(g_tBlkDev_Info.m_nMajor_Num, DEVICE_NAME);
    vfree(g_tBlkDev_Info.m_pchDevData);

    LOG(KERN_INFO "Blk_Exit is success.\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("qianrui");
MODULE_VERSION("0.1.0");
MODULE_DESCRIPTION("This is a simple block device");