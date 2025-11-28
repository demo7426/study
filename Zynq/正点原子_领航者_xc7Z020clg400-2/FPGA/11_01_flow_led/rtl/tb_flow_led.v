/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	tb_led.v
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.11.27
描  述: 实现对led流水灯的测试
备  注:	
修改记录:

  1.  日期: 2025.11.27
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

`timescale 1ns/1ns      //仿真单位/仿真精度

module tb_flow_led();

parameter CLK_PERIOD = 20;  //时钟周期20ns

reg sys_clk;
reg sys_rst_n;

wire [1:0] led;

//信号初始化
initial begin
    sys_clk <= 1'b0;
    sys_rst_n <= 1'b0;
    #200
    sys_rst_n <= 1'b1;
end

//产生时钟
always #(CLK_PERIOD/2) sys_clk = ~sys_clk;

//例化待测设计
flow_led u_flow_led(
    .sys_clk        (sys_clk),
    .sys_rst_n      (sys_rst_n),
    .led            (led)
    );

endmodule