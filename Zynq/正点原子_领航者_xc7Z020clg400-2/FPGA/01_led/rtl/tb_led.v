/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	tb_led.v
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.06.02
描  述: 实现对点亮led灯的测试
备  注:	
修改记录:

  1.  日期: 2025.06.02
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

`timescale 1ns/1ns      //单位/精度

module tb_led();

reg key;
wire led;

initial begin
     key <= 1'b1;
     #200
     key <= 1'b0;
     #500
     key <= 1'b1;
     #1000
     key <= 1'b0;
     #1000
     key <= 1'b1;    
end

led u_led(
    .key (key),
    .led (led)
);

endmodule