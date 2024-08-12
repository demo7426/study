/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2024-08-07 19:25:39
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2024-08-09 14:59:58
 * @FilePath: /alientek/qianrui/Linux_KernelModule/05_BlockDev/Test.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Test.c
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.08.09
描  述: 编写一个对指定块设备文件操作的测试程序
备  注:	
修改记录:

  1.  日期: 2024.08.09
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V1.0.0

*************************************************/

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define RTN_FAILURE -2
#define RTN_SUCCESS 0

static constexpr const char* g_pchBlkDevPath = "/dev/05_BlockDev";                   //块设备文件路径

int Test01() 
{
    try
    {
        int nBlkDevFd = -1;
        char chWriteBuf[129] = "Hello, block device.";
        char chReadBuf[129] = { 0 };

        nBlkDevFd = open(g_pchBlkDevPath, O_RDWR);                              //打开块设备
        if (nBlkDevFd < 0)
        {
            std::cerr << "Test01 open is err." << std::endl;
            return RTN_FAILURE;
        }

        if (write(nBlkDevFd, chWriteBuf, strlen(chWriteBuf)))                   //写数据到块设备
        {
            std::cerr << "Test01 write is err." << std::endl;
            return RTN_FAILURE;
        }
        
        lseek(nBlkDevFd, 0, SEEK_SET);
        if (read(nBlkDevFd, chReadBuf, sizeof chReadBuf) < 0)                   //从块设备读数据
        {
            std::cerr << "Test01 read is err." << std::endl;
            return RTN_FAILURE;
        }

        if (strncmp(chWriteBuf, chReadBuf, strlen(chWriteBuf)) != 0)
        {
            std::cerr << "Test01 strncmp is err." << std::endl;
            return RTN_FAILURE;
        }

        std::cout << "Test01 is success." << std::endl;
    }   
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return RTN_FAILURE;
    }
    
    return RTN_SUCCESS;
}

int main() 
{
    Test01();

    return RTN_SUCCESS;
}
