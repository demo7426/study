/*
  Time: 2024/11/11 
  code: UTF-8
  Author: xf
  Content:
*/

#ifndef LEVEL_QSPI_API_H			
#define LEVEL_QSPI_API_H			
    //-- #include "level_qspi_API.h" 
    //-- 库名称 ：pcie_qspi.a

#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

#if 0
  typedef unsigned long long * addr_ptr;
  typedef unsigned long long  addr_ptr_n;
#else
  typedef unsigned int *  addr_ptr;
  typedef unsigned int    addr_ptr_n;
#endif

#define QSPI_0_FIFO_DEPTH         16U
#define QSPI_0_NUM_TRANSFER_BITS  8U  //-- QSPI  

/// <summary>
/// 初始化
/// </summary>
/// <returns>-2--函数执行失败；-1--传入参数错误；0--函数执行成功</returns>
//int level_Init_qspi(unsigned int qspi_reg_ddr);
void level_Init_qspi(addr_ptr_n qspi_reg_ddr);
/// <summary>
/// 清除函数
/// </summary>
/// <returns>-2--函数执行失败；-1--传入参数错误；0--函数执行成功</returns>
void level_exit_qspi();

/// <summary>
/// 读数据
/// </summary>
/// <returns>-2--函数执行失败；-1--传入参数错误；0--函数执行成功</returns>
int level_qspi_read(addr_ptr_n falsh_ddr,addr_ptr_n data_ddr,int data_len);

/// <summary>
/// 写数据
/// </summary>
/// <returns>-2--函数执行失败；-1--传入参数错误；0--函数执行成功</returns>
int level_qspi_write(unsigned int falsh_ddr,unsigned long long data_ddr,int data_len);

/// <summary>
/// 擦数据
/// </summary>
/// <returns>-2--函数执行失败；-1--传入参数错误；0--函数执行成功</returns>
int level_qspi_erase(unsigned int falsh_ddr,int data_len);

/// <summary>
/// 返回falsh长度
/// </summary>
/// <returns>-2--函数执行失败；-1--传入参数错误；0--函数执行成功</returns>
int level_qspi_getFalshLen();


int FlashReadID(void);
int Flash_command(unsigned char command);
#ifdef __cplusplus
}
#endif  //__cplusplus


#endif
