/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	ramdisk.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.12.01
描  述: 使用ram实现一个虚拟磁盘
备  注:	
修改记录:

  1.  日期: 2025.12.01
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/blkdev.h>
#include <linux/hdreg.h>
#include <linux/spinlock_types.h>
#include <linux/spinlock.h>
#include <linux/genhd.h>
#include <linux/fs.h>
#include <linux/bio.h>

#define RAMDISK_SIZE    (2 * 1024 * 1024u)          //容量大小为2MB
#define RAMDISK_NAME    "ramdisk"                   //设备名字
#define RAMDISK_MINOR   3                           //表示三个磁盘分区；不是次设备号为3！

//ramdisk 设备结构体
typedef struct _RAMDISK_DEV
{
    int Major;                                      //主设备号
    unsigned char* pRamdisk_Buf;                    //ramdisk内存空间，用于模拟块设备
    spinlock_t tSpinlock;                           //自旋锁
    struct gendisk* ptGendisk;                      //gendisk
    struct request_queue* ptRequestQueue;           //请求队列
}RAMDISK_DEV, *PRAMDISK_DEV;

static struct _RAMDISK_DEV g_tRamdisk_Dev = { 0 }; //ramdisk 设备

int Block_Device_Open(struct block_device *_pDev, fmode_t _Mode)
{   
    printk(KERN_INFO "Block_Device_Open is success.\n");
    
    return 0;
}

void Block_Device_Release(struct gendisk *_pDev, fmode_t _Mode)
{
    printk(KERN_INFO "Block_Device_Release is success.\n");
}

int Block_Device_GetGeo(struct block_device *_pDev, struct hd_geometry *_pGeo)
{
    //这是相对于机械硬盘的概念
    _pGeo->heads = 2;                               //磁头
    _pGeo->cylinders = 32;                          //柱面
    _pGeo->sectors = RAMDISK_SIZE / (2 * 32 * 512); //磁道上的扇区数量

    return 0;
}

static struct block_device_operations g_tBlock_Device_FOps = {
    .owner = THIS_MODULE,
    .open = Block_Device_Open,
    .release = Block_Device_Release,
    .getgeo = Block_Device_GetGeo
};

/// @brief "制造请求"函数
/// @param q 
/// @param bio 
/// @return 
static blk_qc_t Make_Request_Fn(struct request_queue *q, struct bio *bio)
{
    int nOffset = 0;
    struct bio_vec tBio_Vec;
    struct bvec_iter tBVec_Iter;
    unsigned long ulLen = 0;

    nOffset = (bio->bi_iter.bi_sector) << 9;

    //处理 bio 中的每个段
    bio_for_each_segment(tBio_Vec, bio, tBVec_Iter)
    {
        char* ptr = page_address(tBio_Vec.bv_page) + tBio_Vec.bv_offset;
        ulLen = tBio_Vec.bv_len;

        if(bio_data_dir(bio) == READ)   //读数据
            memcpy(ptr, g_tRamdisk_Dev.pRamdisk_Buf + nOffset, ulLen);
        else 
            memcpy(g_tRamdisk_Dev.pRamdisk_Buf + nOffset, ptr, ulLen);

        nOffset += ulLen;
    }

    bio_endio(bio);     //结束bio

    return BLK_QC_T_NONE;
}

static int __init Ramdisk_Init(void)
{
    int nRet = 0;

    //为ramdisk分配内存
    g_tRamdisk_Dev.pRamdisk_Buf = kzalloc(RAMDISK_SIZE, GFP_KERNEL);
    if(!g_tRamdisk_Dev.pRamdisk_Buf)
    {
        printk(KERN_WARNING "Ramdisk_Init kzalloc is err\n");
        return -ENOMEM;
    }

    //初始化自旋锁
    spin_lock_init(&g_tRamdisk_Dev.tSpinlock);

    g_tRamdisk_Dev.Major = register_blkdev(0, RAMDISK_NAME);
    if(g_tRamdisk_Dev.Major < 0)
    {
        printk(KERN_WARNING "Ramdisk_Init register_blkdev is err\n");
        nRet = g_tRamdisk_Dev.Major;
        goto out1;
    }

    printk(KERN_INFO "Major = %d\n", g_tRamdisk_Dev.Major);

    //分配并初始化gendisk
    g_tRamdisk_Dev.ptGendisk = alloc_disk(RAMDISK_MINOR);
    if(!g_tRamdisk_Dev.ptGendisk)
    {
        nRet = -ENOMEM;
        goto out2;
    }

    //分配请求队列
    g_tRamdisk_Dev.ptRequestQueue = blk_alloc_queue(GFP_KERNEL);
    if(!g_tRamdisk_Dev.ptRequestQueue)
    {
        nRet = -ENOMEM;
        goto out3;
    }

    //设置"制造请求"函数
    blk_queue_make_request(g_tRamdisk_Dev.ptRequestQueue, Make_Request_Fn);

    //添加(注册)disk
    g_tRamdisk_Dev.ptGendisk->major = g_tRamdisk_Dev.Major;     //主设备号
    g_tRamdisk_Dev.ptGendisk->first_minor = 0;                  //起始次设备号
    g_tRamdisk_Dev.ptGendisk->fops = &g_tBlock_Device_FOps;     //操作函数
    g_tRamdisk_Dev.ptGendisk->private_data = &g_tRamdisk_Dev;   //私有数据
    g_tRamdisk_Dev.ptGendisk->queue = g_tRamdisk_Dev.ptRequestQueue;        //请求队列
    strcpy(g_tRamdisk_Dev.ptGendisk->disk_name, RAMDISK_NAME);  //名字
    set_capacity(g_tRamdisk_Dev.ptGendisk, RAMDISK_SIZE/512);   //设备容量(单位为扇区)

    add_disk(g_tRamdisk_Dev.ptGendisk);

    return 0;

out3:
    put_disk(g_tRamdisk_Dev.ptGendisk);

out2:
    unregister_blkdev(g_tRamdisk_Dev.Major, RAMDISK_NAME);

out1:
    kfree(g_tRamdisk_Dev.pRamdisk_Buf);

    return nRet;    
}


static void __exit Ramdisk_Exit(void)
{   
    //卸载 gendisk
    del_gendisk(g_tRamdisk_Dev.ptGendisk);

    //清除请求队列
    blk_cleanup_queue(g_tRamdisk_Dev.ptRequestQueue);

    //释放 gendisk
    put_disk(g_tRamdisk_Dev.ptGendisk);

    //注销块设备
    unregister_blkdev(g_tRamdisk_Dev.Major, RAMDISK_NAME);

    //释放内存
    kfree(g_tRamdisk_Dev.pRamdisk_Buf);
}

module_init(Ramdisk_Init);
module_exit(Ramdisk_Exit);

MODULE_AUTHOR("qianrui");
MODULE_DESCRIPTION("Memory simulation block device driver");
MODULE_LICENSE("GPL");