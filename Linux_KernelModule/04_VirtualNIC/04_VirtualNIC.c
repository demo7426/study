/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	04_VirtualNIC.c
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.08.01
描  述: 编写一个简易的虚拟网卡驱动
备  注:	
修改记录:

  1.  日期: 2024.08.01
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V1.0.0

  2.  日期: 2024.08.02
	  作者: 钱锐
	  内容:
		  1) 新增支持借用现有的以太网设备发送数据包，前提是真实以太网卡是可以正常收发数据的；
          2) 只测试通过了 Test.elf 程序，及发送UDP包
	  版本:V1.0.0
*************************************************/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>

#include <linux/skbuff.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/icmp.h>

#define RTN_FAILURE -2                      //失败
#define RTN_SUCCESS 0                       //成功

static char* g_pchRealNICName = NULL;                               //真实网卡名称
static struct net_device *g_ptNetDev = NULL;                        //虚拟网络设备信息             

/// @brief 打开虚拟网卡
/// @param _pDev 
/// @return -2--执行失败;0--执行成功
static int VirtualNIC_Open(struct net_device *_pDev);

/// @brief 停止虚拟网卡
/// @param _pDev 
/// @return -2--执行失败;0--执行成功
static int VirtualNIC_Stop(struct net_device *_pDev);

/// @brief 
/// @param _pSkB 
/// @param _pDev 
/// @return 
static netdev_tx_t VirtualNIC_Start_Xmit(struct sk_buff *_pSkB, struct net_device *_pDev);

/// @brief 设置虚拟网卡的属性
/// @param _pDev 
static void VirtualNIC_SetProperty(struct net_device *_pDev);

/// @brief 设置mac地址
/// @param _pDev 
/// @return 
static int VirtualNIC_SetMacAddress(struct net_device *_pDev, void *_pAddr);

/// @brief 实现ICMP的接收和发送
/// @param _pSkB 
/// @param _pDev 
/// @return 
static int VirtualNIC_ICMP(struct sk_buff *_pSkB, struct net_device *_pDev);

static struct net_device_ops tNetDevOps = 
{
    .ndo_open = VirtualNIC_Open,
    .ndo_stop = VirtualNIC_Stop,
    .ndo_start_xmit = VirtualNIC_Start_Xmit,
    .ndo_set_mac_address = VirtualNIC_SetMacAddress,
};

/// @brief 虚拟网卡设备初始化操作
/// @param  
/// @return 
static int __init VirtualNIC_Init(void)
{
    int nRtn = 0;

    g_ptNetDev = alloc_netdev(0, "vnic%d", NET_NAME_UNKNOWN, VirtualNIC_SetProperty);               //分配网络设备
    if (g_ptNetDev == NULL)
    {
        printk(KERN_ERR "VirtualNIC_Init alloc_netdev err.\n");
        return -ENOMEM;
    }
    
    nRtn = register_netdev(g_ptNetDev);                                                             //向内核注册网络设备
    if(nRtn != 0)
    {
        printk(KERN_ERR "VirtualNIC_Init register_netdev err.\n");
        free_netdev(g_ptNetDev);
        return nRtn;
    }

    printk(KERN_INFO "VirtualNIC_Init success.\n");
    return nRtn;
}

static int VirtualNIC_Open(struct net_device *_pDev)
{
    netif_start_queue(_pDev);

    printk(KERN_INFO "VirtualNIC_Open success.\n");
    return RTN_SUCCESS;
}

static int VirtualNIC_Stop(struct net_device *_pDev)
{
    netif_stop_queue(_pDev);

    printk(KERN_INFO "VirtualNIC_Stop success.\n");
    return RTN_SUCCESS;
}

static netdev_tx_t VirtualNIC_Start_Xmit(struct sk_buff *_pSkB, struct net_device *_pDev)
{
    //处理数据包的逻辑（例如发送到硬件）
    
    if(VirtualNIC_ICMP(_pSkB, _pDev) == NETDEV_TX_OK)                               //ICMP包如果成功发送，后续就不需要再使用实际的网卡传输数据了
        return NETDEV_TX_OK;

    if(g_pchRealNICName == NULL)
    {
        printk(KERN_ERR "VirtualNIC_Start_Xmit g_pchRealNICName err.\n");
        return NETDEV_TX_OK;
    }

    struct net_device *ptNetDev = NULL;

    ptNetDev = dev_get_by_name(&init_net, g_pchRealNICName);
    if(!ptNetDev)
    {
        //处理完后释放数据包
        dev_kfree_skb(_pSkB);
        printk(KERN_ERR "VirtualNIC_Start_Xmit dev_get_by_name err.\n");
        return NETDEV_TX_OK;
    }

    _pSkB->dev = ptNetDev;                  //改变 _pSkb 的设备未实际的以太网设备 

    dev_queue_xmit(_pSkB);                  //发送数据包    
    dev_put(ptNetDev);                      //释放对真实nic设备的引用

    _pDev->stats.tx_packets++;
    _pDev->stats.tx_bytes += _pSkB->len;

    printk(KERN_INFO "VirtualNIC_Start_Xmit success protocol = %u, tx_packets = %u, tx_bytes = %u.\n", _pSkB->protocol, _pDev->stats.tx_packets, _pDev->stats.tx_bytes);
    return NETDEV_TX_OK;
}

/// @brief 虚拟网卡设备退出操作
/// @param  
/// @return 
static void __exit VirtualNIC_Exit(void)
{
    unregister_netdev(g_ptNetDev);
    free_netdev(g_ptNetDev);
    printk(KERN_INFO "VirtualNIC_Exit success.\n");
}

void VirtualNIC_SetProperty(struct net_device *_pDev)
{
    //设置网络设备的私有数据和其他属性
    
    ether_setup(_pDev);                     //设置以太网设备的默认值

    _pDev->netdev_ops = &tNetDevOps;
    _pDev->flags |= IFF_NOARP;
    _pDev->features |= NETIF_F_HW_CSUM;
    random_ether_addr(_pDev->dev_addr);
}

static int VirtualNIC_SetMacAddress(struct net_device *_pDev, void *_pAddr)
{
    struct sockaddr *ptSockAddr = _pAddr;
    if(!is_valid_ether_addr(ptSockAddr->sa_data))               //设置虚拟网卡mac地址
    {
        printk(KERN_ERR "VirtualNIC_SetMacAddress is_valid_ether_addr err.\n");
        return -EADDRNOTAVAIL;
    }

    memcpy(_pDev->dev_addr, ptSockAddr->sa_data, _pDev->addr_len);
    return RTN_SUCCESS;
}

static int VirtualNIC_ICMP(struct sk_buff *_pSkB, struct net_device *_pDev)
{
    struct ethhdr *eth;
    struct iphdr *ip;
    struct icmphdr *icmp;
    struct sk_buff *rx_skb;

    eth = (struct ethhdr *)skb_mac_header(_pSkB);
    ip = (struct iphdr *)(_pSkB->data + sizeof(struct ethhdr));
    icmp = (struct icmphdr *)(_pSkB->data + sizeof(struct ethhdr) + (ip->ihl * 4));

    if (ntohs(eth->h_proto) == ETH_P_IP && ip->protocol == IPPROTO_ICMP) 
    {
        if (icmp->type == ICMP_ECHO) 
        {
            printk(KERN_INFO "%s: ICMP Echo Request received\n", "vnic0");

            // 创建用于接收的 skb
            rx_skb = dev_alloc_skb(_pSkB->len);
            if (!rx_skb) 
            {
                dev_kfree_skb(_pSkB);
                return NETDEV_TX_OK;
            }

            // 拷贝原始数据
            skb_put_data(rx_skb, _pSkB->data, _pSkB->len);

            // 修改 ICMP 报头类型为 Echo Reply
            icmp = (struct icmphdr *)(rx_skb->data + sizeof(struct ethhdr) + (ip->ihl * 4));
            icmp->type = ICMP_ECHOREPLY;

            // 交换 IP 地址
            ip = (struct iphdr *)(rx_skb->data + sizeof(struct ethhdr));
            __be32 tmp_ip = ip->saddr;
            ip->saddr = ip->daddr;
            ip->daddr = tmp_ip;

            // 交换 MAC 地址
            eth = (struct ethhdr *)rx_skb->data;
            memcpy(eth->h_dest, eth->h_source, ETH_ALEN);
            memcpy(eth->h_source, _pDev->dev_addr, ETH_ALEN);

            // 更新 skb 元数据
            rx_skb->dev = _pDev;
            rx_skb->protocol = eth_type_trans(rx_skb, _pDev);
            netif_rx(rx_skb);

            _pDev->stats.rx_packets++;
            _pDev->stats.rx_bytes += rx_skb->len;

            // dev_kfree_skb(_pSkB);
            return NETDEV_TX_OK;
        }
    }
    return NETDEV_TX_BUSY;
}

module_param(g_pchRealNICName, charp, S_IRUGO);                                     //用于命令窗口设置真实网卡名称

module_init(VirtualNIC_Init);
module_exit(VirtualNIC_Exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("qianrui");
MODULE_DESCRIPTION("A simple virtual network interface card.");


