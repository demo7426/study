/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Test.c
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.08.02
描  述: 编写一个对虚拟网卡操作的测试程序,使用 dmesg 命令可以查看到对应网卡发送数据包的动作
备  注:	
修改记录:

  1.  日期: 2024.08.02
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V1.0.0

*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>

#define SERVER_IP "10.0.0.226"
#define SERVER_PORT 8888
#define IFNAME "vnic0"
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    struct ifreq ifr;
    char buffer[BUFFER_SIZE];
    unsigned int unFreq = 0;

    // 创建UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 设置接口为vnet0
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, IFNAME, IFNAMSIZ);
    if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) < 0) {
        perror("SO_BINDTODEVICE failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // 配置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("inet_pton failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

	while (1)
	{
		// 发送消息到服务器
    	snprintf(buffer, BUFFER_SIZE, "Hello from vnet0, unFreq = %u", ++unFreq);
		if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
			perror("sendto failed");
			close(sockfd);
			exit(EXIT_FAILURE);
		}

		printf("Message sent to %s:%d via %s unFreq = %u\n", SERVER_IP, SERVER_PORT, IFNAME, unFreq);	
		usleep(100000);
	}
	

    // 关闭 socket
    close(sockfd);
    return 0;
}
