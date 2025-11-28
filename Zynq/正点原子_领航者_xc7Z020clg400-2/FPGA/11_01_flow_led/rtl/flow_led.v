/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	flow_led.v
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.11.27
描  述: led流水灯
备  注:	
修改记录:

  1.  日期: 2025.11.27
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

module flow_led (
    input               sys_clk,            //系统时钟
    input               sys_rst_n,          //系统复位信号，低电平有效
    output reg [1:0]    led                 //输出LED,高电平点亮
);

reg [24:0] cnt;

//计数器计时0.5s
always @(posedge sys_clk or negedge sys_rst_n) begin
    if (!sys_rst_n) 
        cnt <= 25'd0;
    else if(cnt < 25'd25000000 - 25'd1)
        cnt <= cnt + 25'd1;
    else
        cnt <= 25'd0;
end

//led移位控制
always @(posedge sys_clk or negedge sys_rst_n) begin
    if(!sys_rst_n)
        led <= 2'b01;
    else if(cnt == (25'd25000000 - 25'd1))
        led <= {led[0], led[1]};
    else
        led <= led;
end
    
endmodule


