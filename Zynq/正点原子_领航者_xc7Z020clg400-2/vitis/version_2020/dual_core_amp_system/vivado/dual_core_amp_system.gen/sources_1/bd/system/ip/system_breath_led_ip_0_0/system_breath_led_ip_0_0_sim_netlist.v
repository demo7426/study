// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.2 (win64) Build 3064766 Wed Nov 18 09:12:45 MST 2020
// Date        : Tue Jul 15 16:03:21 2025
// Host        : DESKTOP-D3LRDNP running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               d:/Zynq/vitis/version_2020/dual_core_amp_system/vivado/dual_core_amp_system.gen/sources_1/bd/system/ip/system_breath_led_ip_0_0/system_breath_led_ip_0_0_sim_netlist.v
// Design      : system_breath_led_ip_0_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7z020clg400-2
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "system_breath_led_ip_0_0,breath_led_ip_v1_0,{}" *) (* DowngradeIPIdentifiedWarnings = "yes" *) (* X_CORE_INFO = "breath_led_ip_v1_0,Vivado 2020.2" *) 
(* NotValidForBitStream *)
module system_breath_led_ip_0_0
   (led,
    s0_axi_aclk,
    s0_axi_aresetn,
    s0_axi_awaddr,
    s0_axi_awprot,
    s0_axi_awvalid,
    s0_axi_awready,
    s0_axi_wdata,
    s0_axi_wstrb,
    s0_axi_wvalid,
    s0_axi_wready,
    s0_axi_bresp,
    s0_axi_bvalid,
    s0_axi_bready,
    s0_axi_araddr,
    s0_axi_arprot,
    s0_axi_arvalid,
    s0_axi_arready,
    s0_axi_rdata,
    s0_axi_rresp,
    s0_axi_rvalid,
    s0_axi_rready);
  output led;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 S0_AXI_CLK CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME S0_AXI_CLK, ASSOCIATED_BUSIF S0_AXI, ASSOCIATED_RESET s0_axi_aresetn, FREQ_HZ 50000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN system_processing_system7_0_0_FCLK_CLK0, INSERT_VIP 0" *) input s0_axi_aclk;
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 S0_AXI_RST RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME S0_AXI_RST, POLARITY ACTIVE_LOW, INSERT_VIP 0" *) input s0_axi_aresetn;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S0_AXI AWADDR" *) input [3:0]s0_axi_awaddr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S0_AXI AWPROT" *) input [2:0]s0_axi_awprot;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S0_AXI AWVALID" *) input s0_axi_awvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S0_AXI AWREADY" *) output s0_axi_awready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S0_AXI WDATA" *) input [31:0]s0_axi_wdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S0_AXI WSTRB" *) input [3:0]s0_axi_wstrb;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S0_AXI WVALID" *) input s0_axi_wvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S0_AXI WREADY" *) output s0_axi_wready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S0_AXI BRESP" *) output [1:0]s0_axi_bresp;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S0_AXI BVALID" *) output s0_axi_bvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S0_AXI BREADY" *) input s0_axi_bready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S0_AXI ARADDR" *) input [3:0]s0_axi_araddr;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S0_AXI ARPROT" *) input [2:0]s0_axi_arprot;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S0_AXI ARVALID" *) input s0_axi_arvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S0_AXI ARREADY" *) output s0_axi_arready;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S0_AXI RDATA" *) output [31:0]s0_axi_rdata;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S0_AXI RRESP" *) output [1:0]s0_axi_rresp;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S0_AXI RVALID" *) output s0_axi_rvalid;
  (* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 S0_AXI RREADY" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME S0_AXI, WIZ_DATA_WIDTH 32, WIZ_NUM_REG 4, SUPPORTS_NARROW_BURST 0, DATA_WIDTH 32, PROTOCOL AXI4LITE, FREQ_HZ 50000000, ID_WIDTH 0, ADDR_WIDTH 4, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 1, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, NUM_READ_OUTSTANDING 8, NUM_WRITE_OUTSTANDING 8, MAX_BURST_LENGTH 1, PHASE 0.000, CLK_DOMAIN system_processing_system7_0_0_FCLK_CLK0, NUM_READ_THREADS 4, NUM_WRITE_THREADS 4, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *) input s0_axi_rready;

  wire \<const0> ;
  wire led;
  wire s0_axi_aclk;
  wire [3:0]s0_axi_araddr;
  wire s0_axi_aresetn;
  wire s0_axi_arready;
  wire s0_axi_arvalid;
  wire [3:0]s0_axi_awaddr;
  wire s0_axi_awready;
  wire s0_axi_awvalid;
  wire s0_axi_bready;
  wire s0_axi_bvalid;
  wire [31:0]s0_axi_rdata;
  wire s0_axi_rready;
  wire s0_axi_rvalid;
  wire [31:0]s0_axi_wdata;
  wire s0_axi_wready;
  wire [3:0]s0_axi_wstrb;
  wire s0_axi_wvalid;

  assign s0_axi_bresp[1] = \<const0> ;
  assign s0_axi_bresp[0] = \<const0> ;
  assign s0_axi_rresp[1] = \<const0> ;
  assign s0_axi_rresp[0] = \<const0> ;
  GND GND
       (.G(\<const0> ));
  system_breath_led_ip_0_0_breath_led_ip_v1_0 inst
       (.S_AXI_ARREADY(s0_axi_arready),
        .S_AXI_AWREADY(s0_axi_awready),
        .S_AXI_WREADY(s0_axi_wready),
        .led(led),
        .s0_axi_aclk(s0_axi_aclk),
        .s0_axi_araddr(s0_axi_araddr[3:2]),
        .s0_axi_aresetn(s0_axi_aresetn),
        .s0_axi_arvalid(s0_axi_arvalid),
        .s0_axi_awaddr(s0_axi_awaddr[3:2]),
        .s0_axi_awvalid(s0_axi_awvalid),
        .s0_axi_bready(s0_axi_bready),
        .s0_axi_bvalid(s0_axi_bvalid),
        .s0_axi_rdata(s0_axi_rdata),
        .s0_axi_rready(s0_axi_rready),
        .s0_axi_rvalid(s0_axi_rvalid),
        .s0_axi_wdata(s0_axi_wdata),
        .s0_axi_wstrb(s0_axi_wstrb),
        .s0_axi_wvalid(s0_axi_wvalid));
endmodule

(* ORIG_REF_NAME = "breath_led" *) 
module system_breath_led_ip_0_0_breath_led
   (s0_axi_aresetn_0,
    led,
    s0_axi_aclk,
    Q,
    s0_axi_aresetn,
    led_0);
  output s0_axi_aresetn_0;
  output led;
  input s0_axi_aclk;
  input [10:0]Q;
  input s0_axi_aresetn;
  input [0:0]led_0;

  wire [10:0]Q;
  wire cnt_2ms0;
  wire \cnt_2ms[6]_i_2_n_0 ;
  wire \cnt_2ms[8]_i_2_n_0 ;
  wire \cnt_2ms[9]_i_3_n_0 ;
  wire \cnt_2ms[9]_i_4_n_0 ;
  wire \cnt_2ms[9]_i_5_n_0 ;
  wire \cnt_2ms[9]_i_6_n_0 ;
  wire \cnt_2ms[9]_i_7_n_0 ;
  wire [9:0]cnt_2ms_reg;
  wire \cnt_2s[9]_i_1_n_0 ;
  wire \cnt_2s[9]_i_2_n_0 ;
  wire \cnt_2s[9]_i_3_n_0 ;
  wire \cnt_2s[9]_i_4_n_0 ;
  wire \cnt_2s_inferred__0/i__carry__0_n_0 ;
  wire \cnt_2s_inferred__0/i__carry__0_n_1 ;
  wire \cnt_2s_inferred__0/i__carry__0_n_2 ;
  wire \cnt_2s_inferred__0/i__carry__0_n_3 ;
  wire \cnt_2s_inferred__0/i__carry__0_n_4 ;
  wire \cnt_2s_inferred__0/i__carry__0_n_5 ;
  wire \cnt_2s_inferred__0/i__carry__0_n_6 ;
  wire \cnt_2s_inferred__0/i__carry__0_n_7 ;
  wire \cnt_2s_inferred__0/i__carry__1_n_3 ;
  wire \cnt_2s_inferred__0/i__carry__1_n_6 ;
  wire \cnt_2s_inferred__0/i__carry__1_n_7 ;
  wire \cnt_2s_inferred__0/i__carry_n_0 ;
  wire \cnt_2s_inferred__0/i__carry_n_1 ;
  wire \cnt_2s_inferred__0/i__carry_n_2 ;
  wire \cnt_2s_inferred__0/i__carry_n_3 ;
  wire \cnt_2s_inferred__0/i__carry_n_4 ;
  wire \cnt_2s_inferred__0/i__carry_n_5 ;
  wire \cnt_2s_inferred__0/i__carry_n_6 ;
  wire \cnt_2s_inferred__0/i__carry_n_7 ;
  wire [9:0]cnt_2s_reg;
  wire [6:0]cnt_2us;
  wire \cnt_2us[6]_i_2_n_0 ;
  wire [6:0]cnt_2us_0;
  wire \freq_step[0]_i_1_n_0 ;
  wire \freq_step[0]_i_2_n_0 ;
  wire \freq_step[0]_i_3_n_0 ;
  wire \freq_step[0]_i_4_n_0 ;
  wire \freq_step[3]_i_1_n_0 ;
  wire \freq_step[3]_i_3_n_0 ;
  wire \freq_step[3]_i_4_n_0 ;
  wire i__carry__0_i_1__0_n_0;
  wire i__carry__0_i_1_n_0;
  wire i__carry__0_i_2__0_n_0;
  wire i__carry__0_i_2_n_0;
  wire i__carry__0_i_3_n_0;
  wire i__carry__0_i_4_n_0;
  wire i__carry__1_i_1_n_0;
  wire i__carry__1_i_2_n_0;
  wire i__carry_i_10_n_0;
  wire i__carry_i_1__0_n_0;
  wire i__carry_i_1_n_0;
  wire i__carry_i_2__0_n_0;
  wire i__carry_i_2_n_0;
  wire i__carry_i_3__0_n_0;
  wire i__carry_i_3_n_0;
  wire i__carry_i_4__0_n_0;
  wire i__carry_i_4_n_0;
  wire i__carry_i_5__0_n_0;
  wire i__carry_i_5_n_0;
  wire i__carry_i_6__0_n_0;
  wire i__carry_i_6_n_0;
  wire i__carry_i_7__0_n_0;
  wire i__carry_i_7_n_0;
  wire i__carry_i_8__0_n_0;
  wire i__carry_i_8_n_0;
  wire i__carry_i_9_n_0;
  wire [3:0]in;
  wire inc_dec_flag;
  wire inc_dec_flag_i_1_n_0;
  wire led;
  wire [0:0]led_0;
  wire led_t;
  wire led_t2;
  wire led_t21_in;
  wire led_t2_carry__0_i_1_n_0;
  wire led_t2_carry__0_i_2_n_0;
  wire led_t2_carry_i_1_n_0;
  wire led_t2_carry_i_2_n_0;
  wire led_t2_carry_i_3_n_0;
  wire led_t2_carry_i_4_n_0;
  wire led_t2_carry_i_5_n_0;
  wire led_t2_carry_i_6_n_0;
  wire led_t2_carry_i_7_n_0;
  wire led_t2_carry_i_8_n_0;
  wire led_t2_carry_n_0;
  wire led_t2_carry_n_1;
  wire led_t2_carry_n_2;
  wire led_t2_carry_n_3;
  wire \led_t2_inferred__0/i__carry_n_0 ;
  wire \led_t2_inferred__0/i__carry_n_1 ;
  wire \led_t2_inferred__0/i__carry_n_2 ;
  wire \led_t2_inferred__0/i__carry_n_3 ;
  wire led_t_i_1_n_0;
  wire [9:0]p_0_in__0;
  wire [3:1]p_1_in;
  wire s0_axi_aclk;
  wire s0_axi_aresetn;
  wire s0_axi_aresetn_0;
  wire [3:1]\NLW_cnt_2s_inferred__0/i__carry__1_CO_UNCONNECTED ;
  wire [3:2]\NLW_cnt_2s_inferred__0/i__carry__1_O_UNCONNECTED ;
  wire [3:0]NLW_led_t2_carry_O_UNCONNECTED;
  wire [3:1]NLW_led_t2_carry__0_CO_UNCONNECTED;
  wire [3:0]NLW_led_t2_carry__0_O_UNCONNECTED;
  wire [3:0]\NLW_led_t2_inferred__0/i__carry_O_UNCONNECTED ;
  wire [3:1]\NLW_led_t2_inferred__0/i__carry__0_CO_UNCONNECTED ;
  wire [3:0]\NLW_led_t2_inferred__0/i__carry__0_O_UNCONNECTED ;

  LUT1 #(
    .INIT(2'h1)) 
    axi_awready_i_1
       (.I0(s0_axi_aresetn),
        .O(s0_axi_aresetn_0));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \cnt_2ms[0]_i_1 
       (.I0(cnt_2ms_reg[0]),
        .O(p_0_in__0[0]));
  (* SOFT_HLUTNM = "soft_lutpair8" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \cnt_2ms[1]_i_1 
       (.I0(cnt_2ms_reg[1]),
        .I1(cnt_2ms_reg[0]),
        .O(p_0_in__0[1]));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT3 #(
    .INIT(8'h6A)) 
    \cnt_2ms[2]_i_1 
       (.I0(cnt_2ms_reg[2]),
        .I1(cnt_2ms_reg[1]),
        .I2(cnt_2ms_reg[0]),
        .O(p_0_in__0[2]));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h2AAA8000)) 
    \cnt_2ms[3]_i_1 
       (.I0(\cnt_2ms[9]_i_4_n_0 ),
        .I1(cnt_2ms_reg[0]),
        .I2(cnt_2ms_reg[1]),
        .I3(cnt_2ms_reg[2]),
        .I4(cnt_2ms_reg[3]),
        .O(p_0_in__0[3]));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'h6AAAAAAA)) 
    \cnt_2ms[4]_i_1 
       (.I0(cnt_2ms_reg[4]),
        .I1(cnt_2ms_reg[2]),
        .I2(cnt_2ms_reg[1]),
        .I3(cnt_2ms_reg[0]),
        .I4(cnt_2ms_reg[3]),
        .O(p_0_in__0[4]));
  LUT5 #(
    .INIT(32'hA2AA0800)) 
    \cnt_2ms[5]_i_1 
       (.I0(\cnt_2ms[9]_i_4_n_0 ),
        .I1(cnt_2ms_reg[3]),
        .I2(\cnt_2ms[6]_i_2_n_0 ),
        .I3(cnt_2ms_reg[4]),
        .I4(cnt_2ms_reg[5]),
        .O(p_0_in__0[5]));
  LUT6 #(
    .INIT(64'hA2AAAAAA08000000)) 
    \cnt_2ms[6]_i_1 
       (.I0(\cnt_2ms[9]_i_4_n_0 ),
        .I1(cnt_2ms_reg[4]),
        .I2(\cnt_2ms[6]_i_2_n_0 ),
        .I3(cnt_2ms_reg[3]),
        .I4(cnt_2ms_reg[5]),
        .I5(cnt_2ms_reg[6]),
        .O(p_0_in__0[6]));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT3 #(
    .INIT(8'h7F)) 
    \cnt_2ms[6]_i_2 
       (.I0(cnt_2ms_reg[0]),
        .I1(cnt_2ms_reg[1]),
        .I2(cnt_2ms_reg[2]),
        .O(\cnt_2ms[6]_i_2_n_0 ));
  LUT5 #(
    .INIT(32'hA2AA0800)) 
    \cnt_2ms[7]_i_1 
       (.I0(\cnt_2ms[9]_i_4_n_0 ),
        .I1(cnt_2ms_reg[5]),
        .I2(\cnt_2ms[8]_i_2_n_0 ),
        .I3(cnt_2ms_reg[6]),
        .I4(cnt_2ms_reg[7]),
        .O(p_0_in__0[7]));
  LUT6 #(
    .INIT(64'hAA2AAAAA00800000)) 
    \cnt_2ms[8]_i_1 
       (.I0(\cnt_2ms[9]_i_4_n_0 ),
        .I1(cnt_2ms_reg[7]),
        .I2(cnt_2ms_reg[6]),
        .I3(\cnt_2ms[8]_i_2_n_0 ),
        .I4(cnt_2ms_reg[5]),
        .I5(cnt_2ms_reg[8]),
        .O(p_0_in__0[8]));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'h7FFFFFFF)) 
    \cnt_2ms[8]_i_2 
       (.I0(cnt_2ms_reg[3]),
        .I1(cnt_2ms_reg[0]),
        .I2(cnt_2ms_reg[1]),
        .I3(cnt_2ms_reg[2]),
        .I4(cnt_2ms_reg[4]),
        .O(\cnt_2ms[8]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h0000010000000000)) 
    \cnt_2ms[9]_i_1 
       (.I0(\cnt_2us[6]_i_2_n_0 ),
        .I1(cnt_2us[2]),
        .I2(cnt_2us[4]),
        .I3(cnt_2us[6]),
        .I4(cnt_2us[3]),
        .I5(cnt_2us[5]),
        .O(cnt_2ms0));
  LUT6 #(
    .INIT(64'hBFFF400000000000)) 
    \cnt_2ms[9]_i_2 
       (.I0(\cnt_2ms[9]_i_3_n_0 ),
        .I1(cnt_2ms_reg[6]),
        .I2(cnt_2ms_reg[7]),
        .I3(cnt_2ms_reg[8]),
        .I4(cnt_2ms_reg[9]),
        .I5(\cnt_2ms[9]_i_4_n_0 ),
        .O(p_0_in__0[9]));
  LUT6 #(
    .INIT(64'h7FFFFFFFFFFFFFFF)) 
    \cnt_2ms[9]_i_3 
       (.I0(cnt_2ms_reg[4]),
        .I1(cnt_2ms_reg[2]),
        .I2(cnt_2ms_reg[1]),
        .I3(cnt_2ms_reg[0]),
        .I4(cnt_2ms_reg[3]),
        .I5(cnt_2ms_reg[5]),
        .O(\cnt_2ms[9]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFEFFFFFFFF)) 
    \cnt_2ms[9]_i_4 
       (.I0(\cnt_2ms[9]_i_5_n_0 ),
        .I1(\cnt_2ms[9]_i_6_n_0 ),
        .I2(cnt_2ms_reg[3]),
        .I3(cnt_2ms_reg[4]),
        .I4(\cnt_2s[9]_i_2_n_0 ),
        .I5(\cnt_2ms[9]_i_7_n_0 ),
        .O(\cnt_2ms[9]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair3" *) 
  LUT4 #(
    .INIT(16'h7FFF)) 
    \cnt_2ms[9]_i_5 
       (.I0(cnt_2ms_reg[0]),
        .I1(cnt_2ms_reg[1]),
        .I2(cnt_2ms_reg[9]),
        .I3(cnt_2ms_reg[2]),
        .O(\cnt_2ms[9]_i_5_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT4 #(
    .INIT(16'h7FFF)) 
    \cnt_2ms[9]_i_6 
       (.I0(cnt_2ms_reg[7]),
        .I1(cnt_2ms_reg[5]),
        .I2(cnt_2ms_reg[8]),
        .I3(cnt_2ms_reg[6]),
        .O(\cnt_2ms[9]_i_6_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT3 #(
    .INIT(8'h40)) 
    \cnt_2ms[9]_i_7 
       (.I0(cnt_2us[2]),
        .I1(cnt_2us[1]),
        .I2(cnt_2us[0]),
        .O(\cnt_2ms[9]_i_7_n_0 ));
  FDCE \cnt_2ms_reg[0] 
       (.C(s0_axi_aclk),
        .CE(cnt_2ms0),
        .CLR(s0_axi_aresetn_0),
        .D(p_0_in__0[0]),
        .Q(cnt_2ms_reg[0]));
  FDCE \cnt_2ms_reg[1] 
       (.C(s0_axi_aclk),
        .CE(cnt_2ms0),
        .CLR(s0_axi_aresetn_0),
        .D(p_0_in__0[1]),
        .Q(cnt_2ms_reg[1]));
  FDCE \cnt_2ms_reg[2] 
       (.C(s0_axi_aclk),
        .CE(cnt_2ms0),
        .CLR(s0_axi_aresetn_0),
        .D(p_0_in__0[2]),
        .Q(cnt_2ms_reg[2]));
  FDCE \cnt_2ms_reg[3] 
       (.C(s0_axi_aclk),
        .CE(cnt_2ms0),
        .CLR(s0_axi_aresetn_0),
        .D(p_0_in__0[3]),
        .Q(cnt_2ms_reg[3]));
  FDCE \cnt_2ms_reg[4] 
       (.C(s0_axi_aclk),
        .CE(cnt_2ms0),
        .CLR(s0_axi_aresetn_0),
        .D(p_0_in__0[4]),
        .Q(cnt_2ms_reg[4]));
  FDCE \cnt_2ms_reg[5] 
       (.C(s0_axi_aclk),
        .CE(cnt_2ms0),
        .CLR(s0_axi_aresetn_0),
        .D(p_0_in__0[5]),
        .Q(cnt_2ms_reg[5]));
  FDCE \cnt_2ms_reg[6] 
       (.C(s0_axi_aclk),
        .CE(cnt_2ms0),
        .CLR(s0_axi_aresetn_0),
        .D(p_0_in__0[6]),
        .Q(cnt_2ms_reg[6]));
  FDCE \cnt_2ms_reg[7] 
       (.C(s0_axi_aclk),
        .CE(cnt_2ms0),
        .CLR(s0_axi_aresetn_0),
        .D(p_0_in__0[7]),
        .Q(cnt_2ms_reg[7]));
  FDCE \cnt_2ms_reg[8] 
       (.C(s0_axi_aclk),
        .CE(cnt_2ms0),
        .CLR(s0_axi_aresetn_0),
        .D(p_0_in__0[8]),
        .Q(cnt_2ms_reg[8]));
  FDCE \cnt_2ms_reg[9] 
       (.C(s0_axi_aclk),
        .CE(cnt_2ms0),
        .CLR(s0_axi_aresetn_0),
        .D(p_0_in__0[9]),
        .Q(cnt_2ms_reg[9]));
  LUT6 #(
    .INIT(64'h0000000000000001)) 
    \cnt_2s[9]_i_1 
       (.I0(\cnt_2s[9]_i_2_n_0 ),
        .I1(cnt_2us[2]),
        .I2(\cnt_2us[6]_i_2_n_0 ),
        .I3(\cnt_2s[9]_i_3_n_0 ),
        .I4(\cnt_2s[9]_i_4_n_0 ),
        .I5(\cnt_2ms[6]_i_2_n_0 ),
        .O(\cnt_2s[9]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'hFFDF)) 
    \cnt_2s[9]_i_2 
       (.I0(cnt_2us[5]),
        .I1(cnt_2us[3]),
        .I2(cnt_2us[6]),
        .I3(cnt_2us[4]),
        .O(\cnt_2s[9]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair4" *) 
  LUT3 #(
    .INIT(8'hDF)) 
    \cnt_2s[9]_i_3 
       (.I0(cnt_2ms_reg[6]),
        .I1(cnt_2ms_reg[3]),
        .I2(cnt_2ms_reg[5]),
        .O(\cnt_2s[9]_i_3_n_0 ));
  LUT4 #(
    .INIT(16'hFF7F)) 
    \cnt_2s[9]_i_4 
       (.I0(cnt_2ms_reg[9]),
        .I1(cnt_2ms_reg[7]),
        .I2(cnt_2ms_reg[8]),
        .I3(cnt_2ms_reg[4]),
        .O(\cnt_2s[9]_i_4_n_0 ));
  CARRY4 \cnt_2s_inferred__0/i__carry 
       (.CI(1'b0),
        .CO({\cnt_2s_inferred__0/i__carry_n_0 ,\cnt_2s_inferred__0/i__carry_n_1 ,\cnt_2s_inferred__0/i__carry_n_2 ,\cnt_2s_inferred__0/i__carry_n_3 }),
        .CYINIT(1'b0),
        .DI({i__carry_i_1_n_0,i__carry_i_2_n_0,i__carry_i_3_n_0,i__carry_i_4_n_0}),
        .O({\cnt_2s_inferred__0/i__carry_n_4 ,\cnt_2s_inferred__0/i__carry_n_5 ,\cnt_2s_inferred__0/i__carry_n_6 ,\cnt_2s_inferred__0/i__carry_n_7 }),
        .S({i__carry_i_5__0_n_0,i__carry_i_6__0_n_0,i__carry_i_7__0_n_0,i__carry_i_8__0_n_0}));
  CARRY4 \cnt_2s_inferred__0/i__carry__0 
       (.CI(\cnt_2s_inferred__0/i__carry_n_0 ),
        .CO({\cnt_2s_inferred__0/i__carry__0_n_0 ,\cnt_2s_inferred__0/i__carry__0_n_1 ,\cnt_2s_inferred__0/i__carry__0_n_2 ,\cnt_2s_inferred__0/i__carry__0_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\cnt_2s_inferred__0/i__carry__0_n_4 ,\cnt_2s_inferred__0/i__carry__0_n_5 ,\cnt_2s_inferred__0/i__carry__0_n_6 ,\cnt_2s_inferred__0/i__carry__0_n_7 }),
        .S({i__carry__0_i_1_n_0,i__carry__0_i_2_n_0,i__carry__0_i_3_n_0,i__carry__0_i_4_n_0}));
  CARRY4 \cnt_2s_inferred__0/i__carry__1 
       (.CI(\cnt_2s_inferred__0/i__carry__0_n_0 ),
        .CO({\NLW_cnt_2s_inferred__0/i__carry__1_CO_UNCONNECTED [3:1],\cnt_2s_inferred__0/i__carry__1_n_3 }),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,1'b0}),
        .O({\NLW_cnt_2s_inferred__0/i__carry__1_O_UNCONNECTED [3:2],\cnt_2s_inferred__0/i__carry__1_n_6 ,\cnt_2s_inferred__0/i__carry__1_n_7 }),
        .S({1'b0,1'b0,i__carry__1_i_1_n_0,i__carry__1_i_2_n_0}));
  FDCE \cnt_2s_reg[0] 
       (.C(s0_axi_aclk),
        .CE(\cnt_2s[9]_i_1_n_0 ),
        .CLR(s0_axi_aresetn_0),
        .D(\cnt_2s_inferred__0/i__carry_n_7 ),
        .Q(cnt_2s_reg[0]));
  FDCE \cnt_2s_reg[1] 
       (.C(s0_axi_aclk),
        .CE(\cnt_2s[9]_i_1_n_0 ),
        .CLR(s0_axi_aresetn_0),
        .D(\cnt_2s_inferred__0/i__carry_n_6 ),
        .Q(cnt_2s_reg[1]));
  FDCE \cnt_2s_reg[2] 
       (.C(s0_axi_aclk),
        .CE(\cnt_2s[9]_i_1_n_0 ),
        .CLR(s0_axi_aresetn_0),
        .D(\cnt_2s_inferred__0/i__carry_n_5 ),
        .Q(cnt_2s_reg[2]));
  FDCE \cnt_2s_reg[3] 
       (.C(s0_axi_aclk),
        .CE(\cnt_2s[9]_i_1_n_0 ),
        .CLR(s0_axi_aresetn_0),
        .D(\cnt_2s_inferred__0/i__carry_n_4 ),
        .Q(cnt_2s_reg[3]));
  FDCE \cnt_2s_reg[4] 
       (.C(s0_axi_aclk),
        .CE(\cnt_2s[9]_i_1_n_0 ),
        .CLR(s0_axi_aresetn_0),
        .D(\cnt_2s_inferred__0/i__carry__0_n_7 ),
        .Q(cnt_2s_reg[4]));
  FDCE \cnt_2s_reg[5] 
       (.C(s0_axi_aclk),
        .CE(\cnt_2s[9]_i_1_n_0 ),
        .CLR(s0_axi_aresetn_0),
        .D(\cnt_2s_inferred__0/i__carry__0_n_6 ),
        .Q(cnt_2s_reg[5]));
  FDCE \cnt_2s_reg[6] 
       (.C(s0_axi_aclk),
        .CE(\cnt_2s[9]_i_1_n_0 ),
        .CLR(s0_axi_aresetn_0),
        .D(\cnt_2s_inferred__0/i__carry__0_n_5 ),
        .Q(cnt_2s_reg[6]));
  FDCE \cnt_2s_reg[7] 
       (.C(s0_axi_aclk),
        .CE(\cnt_2s[9]_i_1_n_0 ),
        .CLR(s0_axi_aresetn_0),
        .D(\cnt_2s_inferred__0/i__carry__0_n_4 ),
        .Q(cnt_2s_reg[7]));
  FDCE \cnt_2s_reg[8] 
       (.C(s0_axi_aclk),
        .CE(\cnt_2s[9]_i_1_n_0 ),
        .CLR(s0_axi_aresetn_0),
        .D(\cnt_2s_inferred__0/i__carry__1_n_7 ),
        .Q(cnt_2s_reg[8]));
  FDCE \cnt_2s_reg[9] 
       (.C(s0_axi_aclk),
        .CE(\cnt_2s[9]_i_1_n_0 ),
        .CLR(s0_axi_aresetn_0),
        .D(\cnt_2s_inferred__0/i__carry__1_n_6 ),
        .Q(cnt_2s_reg[9]));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT1 #(
    .INIT(2'h1)) 
    \cnt_2us[0]_i_1 
       (.I0(cnt_2us[0]),
        .O(cnt_2us_0[0]));
  (* SOFT_HLUTNM = "soft_lutpair9" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \cnt_2us[1]_i_1 
       (.I0(cnt_2us[0]),
        .I1(cnt_2us[1]),
        .O(cnt_2us_0[1]));
  LUT6 #(
    .INIT(64'hFFFF00000000FFDF)) 
    \cnt_2us[2]_i_1 
       (.I0(cnt_2us[5]),
        .I1(cnt_2us[3]),
        .I2(cnt_2us[6]),
        .I3(cnt_2us[4]),
        .I4(cnt_2us[2]),
        .I5(\cnt_2us[6]_i_2_n_0 ),
        .O(cnt_2us_0[2]));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT4 #(
    .INIT(16'h6AAA)) 
    \cnt_2us[3]_i_1 
       (.I0(cnt_2us[3]),
        .I1(cnt_2us[1]),
        .I2(cnt_2us[0]),
        .I3(cnt_2us[2]),
        .O(cnt_2us_0[3]));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT5 #(
    .INIT(32'h6AAAAAAA)) 
    \cnt_2us[4]_i_1 
       (.I0(cnt_2us[4]),
        .I1(cnt_2us[2]),
        .I2(cnt_2us[0]),
        .I3(cnt_2us[1]),
        .I4(cnt_2us[3]),
        .O(cnt_2us_0[4]));
  LUT6 #(
    .INIT(64'hF7FE0800F7FF0800)) 
    \cnt_2us[5]_i_1 
       (.I0(cnt_2us[4]),
        .I1(cnt_2us[2]),
        .I2(\cnt_2us[6]_i_2_n_0 ),
        .I3(cnt_2us[3]),
        .I4(cnt_2us[5]),
        .I5(cnt_2us[6]),
        .O(cnt_2us_0[5]));
  LUT6 #(
    .INIT(64'hF7FEFFFF08000000)) 
    \cnt_2us[6]_i_1 
       (.I0(cnt_2us[4]),
        .I1(cnt_2us[2]),
        .I2(\cnt_2us[6]_i_2_n_0 ),
        .I3(cnt_2us[3]),
        .I4(cnt_2us[5]),
        .I5(cnt_2us[6]),
        .O(cnt_2us_0[6]));
  (* SOFT_HLUTNM = "soft_lutpair5" *) 
  LUT2 #(
    .INIT(4'h7)) 
    \cnt_2us[6]_i_2 
       (.I0(cnt_2us[0]),
        .I1(cnt_2us[1]),
        .O(\cnt_2us[6]_i_2_n_0 ));
  FDCE \cnt_2us_reg[0] 
       (.C(s0_axi_aclk),
        .CE(1'b1),
        .CLR(s0_axi_aresetn_0),
        .D(cnt_2us_0[0]),
        .Q(cnt_2us[0]));
  FDCE \cnt_2us_reg[1] 
       (.C(s0_axi_aclk),
        .CE(1'b1),
        .CLR(s0_axi_aresetn_0),
        .D(cnt_2us_0[1]),
        .Q(cnt_2us[1]));
  FDCE \cnt_2us_reg[2] 
       (.C(s0_axi_aclk),
        .CE(1'b1),
        .CLR(s0_axi_aresetn_0),
        .D(cnt_2us_0[2]),
        .Q(cnt_2us[2]));
  FDCE \cnt_2us_reg[3] 
       (.C(s0_axi_aclk),
        .CE(1'b1),
        .CLR(s0_axi_aresetn_0),
        .D(cnt_2us_0[3]),
        .Q(cnt_2us[3]));
  FDCE \cnt_2us_reg[4] 
       (.C(s0_axi_aclk),
        .CE(1'b1),
        .CLR(s0_axi_aresetn_0),
        .D(cnt_2us_0[4]),
        .Q(cnt_2us[4]));
  FDCE \cnt_2us_reg[5] 
       (.C(s0_axi_aclk),
        .CE(1'b1),
        .CLR(s0_axi_aresetn_0),
        .D(cnt_2us_0[5]),
        .Q(cnt_2us[5]));
  FDCE \cnt_2us_reg[6] 
       (.C(s0_axi_aclk),
        .CE(1'b1),
        .CLR(s0_axi_aresetn_0),
        .D(cnt_2us_0[6]),
        .Q(cnt_2us[6]));
  LUT5 #(
    .INIT(32'hF200FFFF)) 
    \freq_step[0]_i_1 
       (.I0(Q[0]),
        .I1(\freq_step[3]_i_3_n_0 ),
        .I2(\freq_step[0]_i_2_n_0 ),
        .I3(\freq_step[0]_i_3_n_0 ),
        .I4(s0_axi_aresetn),
        .O(\freq_step[0]_i_1_n_0 ));
  LUT5 #(
    .INIT(32'h00000001)) 
    \freq_step[0]_i_2 
       (.I0(Q[8]),
        .I1(Q[0]),
        .I2(Q[9]),
        .I3(Q[5]),
        .I4(\freq_step[0]_i_4_n_0 ),
        .O(\freq_step[0]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'hF1F0F1F0F1F0F1F1)) 
    \freq_step[0]_i_3 
       (.I0(Q[8]),
        .I1(Q[7]),
        .I2(Q[9]),
        .I3(Q[6]),
        .I4(Q[5]),
        .I5(Q[4]),
        .O(\freq_step[0]_i_3_n_0 ));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFF44F4)) 
    \freq_step[0]_i_4 
       (.I0(Q[7]),
        .I1(Q[6]),
        .I2(Q[3]),
        .I3(Q[4]),
        .I4(Q[1]),
        .I5(Q[2]),
        .O(\freq_step[0]_i_4_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT3 #(
    .INIT(8'hA8)) 
    \freq_step[1]_i_1 
       (.I0(s0_axi_aresetn),
        .I1(\freq_step[3]_i_3_n_0 ),
        .I2(Q[1]),
        .O(p_1_in[1]));
  LUT3 #(
    .INIT(8'h08)) 
    \freq_step[2]_i_1 
       (.I0(Q[2]),
        .I1(s0_axi_aresetn),
        .I2(\freq_step[3]_i_3_n_0 ),
        .O(p_1_in[2]));
  LUT2 #(
    .INIT(4'hB)) 
    \freq_step[3]_i_1 
       (.I0(Q[10]),
        .I1(s0_axi_aresetn),
        .O(\freq_step[3]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair7" *) 
  LUT3 #(
    .INIT(8'hA8)) 
    \freq_step[3]_i_2 
       (.I0(s0_axi_aresetn),
        .I1(\freq_step[3]_i_3_n_0 ),
        .I2(Q[3]),
        .O(p_1_in[3]));
  LUT5 #(
    .INIT(32'hFFFFFFFE)) 
    \freq_step[3]_i_3 
       (.I0(Q[9]),
        .I1(Q[6]),
        .I2(Q[8]),
        .I3(Q[7]),
        .I4(\freq_step[3]_i_4_n_0 ),
        .O(\freq_step[3]_i_3_n_0 ));
  LUT5 #(
    .INIT(32'hFEFEFEEE)) 
    \freq_step[3]_i_4 
       (.I0(Q[4]),
        .I1(Q[5]),
        .I2(Q[3]),
        .I3(Q[1]),
        .I4(Q[2]),
        .O(\freq_step[3]_i_4_n_0 ));
  FDRE \freq_step_reg[0] 
       (.C(s0_axi_aclk),
        .CE(\freq_step[3]_i_1_n_0 ),
        .D(\freq_step[0]_i_1_n_0 ),
        .Q(in[0]),
        .R(1'b0));
  FDRE \freq_step_reg[1] 
       (.C(s0_axi_aclk),
        .CE(\freq_step[3]_i_1_n_0 ),
        .D(p_1_in[1]),
        .Q(in[1]),
        .R(1'b0));
  FDRE \freq_step_reg[2] 
       (.C(s0_axi_aclk),
        .CE(\freq_step[3]_i_1_n_0 ),
        .D(p_1_in[2]),
        .Q(in[2]),
        .R(1'b0));
  FDRE \freq_step_reg[3] 
       (.C(s0_axi_aclk),
        .CE(\freq_step[3]_i_1_n_0 ),
        .D(p_1_in[3]),
        .Q(in[3]),
        .R(1'b0));
  LUT3 #(
    .INIT(8'hA8)) 
    i__carry__0_i_1
       (.I0(cnt_2s_reg[7]),
        .I1(\cnt_2ms[9]_i_4_n_0 ),
        .I2(i__carry_i_9_n_0),
        .O(i__carry__0_i_1_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry__0_i_1__0
       (.I0(cnt_2ms_reg[8]),
        .I1(cnt_2s_reg[8]),
        .I2(cnt_2s_reg[9]),
        .I3(cnt_2ms_reg[9]),
        .O(i__carry__0_i_1__0_n_0));
  LUT3 #(
    .INIT(8'hA8)) 
    i__carry__0_i_2
       (.I0(cnt_2s_reg[6]),
        .I1(\cnt_2ms[9]_i_4_n_0 ),
        .I2(i__carry_i_9_n_0),
        .O(i__carry__0_i_2_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry__0_i_2__0
       (.I0(cnt_2ms_reg[8]),
        .I1(cnt_2s_reg[8]),
        .I2(cnt_2s_reg[9]),
        .I3(cnt_2ms_reg[9]),
        .O(i__carry__0_i_2__0_n_0));
  LUT3 #(
    .INIT(8'hA8)) 
    i__carry__0_i_3
       (.I0(cnt_2s_reg[5]),
        .I1(\cnt_2ms[9]_i_4_n_0 ),
        .I2(i__carry_i_9_n_0),
        .O(i__carry__0_i_3_n_0));
  LUT3 #(
    .INIT(8'hA8)) 
    i__carry__0_i_4
       (.I0(cnt_2s_reg[4]),
        .I1(\cnt_2ms[9]_i_4_n_0 ),
        .I2(i__carry_i_9_n_0),
        .O(i__carry__0_i_4_n_0));
  LUT3 #(
    .INIT(8'h8A)) 
    i__carry__1_i_1
       (.I0(cnt_2s_reg[9]),
        .I1(i__carry_i_9_n_0),
        .I2(\cnt_2s[9]_i_1_n_0 ),
        .O(i__carry__1_i_1_n_0));
  LUT3 #(
    .INIT(8'hA8)) 
    i__carry__1_i_2
       (.I0(cnt_2s_reg[8]),
        .I1(\cnt_2ms[9]_i_4_n_0 ),
        .I2(i__carry_i_9_n_0),
        .O(i__carry__1_i_2_n_0));
  LUT3 #(
    .INIT(8'hA8)) 
    i__carry_i_1
       (.I0(in[3]),
        .I1(\cnt_2ms[9]_i_4_n_0 ),
        .I2(i__carry_i_9_n_0),
        .O(i__carry_i_1_n_0));
  LUT5 #(
    .INIT(32'h0000007F)) 
    i__carry_i_10
       (.I0(cnt_2s_reg[2]),
        .I1(cnt_2s_reg[0]),
        .I2(cnt_2s_reg[1]),
        .I3(cnt_2s_reg[3]),
        .I4(cnt_2s_reg[4]),
        .O(i__carry_i_10_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_1__0
       (.I0(cnt_2ms_reg[6]),
        .I1(cnt_2s_reg[6]),
        .I2(cnt_2s_reg[7]),
        .I3(cnt_2ms_reg[7]),
        .O(i__carry_i_1__0_n_0));
  LUT3 #(
    .INIT(8'hA8)) 
    i__carry_i_2
       (.I0(in[2]),
        .I1(\cnt_2ms[9]_i_4_n_0 ),
        .I2(i__carry_i_9_n_0),
        .O(i__carry_i_2_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_2__0
       (.I0(cnt_2ms_reg[4]),
        .I1(cnt_2s_reg[4]),
        .I2(cnt_2s_reg[5]),
        .I3(cnt_2ms_reg[5]),
        .O(i__carry_i_2__0_n_0));
  LUT3 #(
    .INIT(8'hA8)) 
    i__carry_i_3
       (.I0(in[1]),
        .I1(\cnt_2ms[9]_i_4_n_0 ),
        .I2(i__carry_i_9_n_0),
        .O(i__carry_i_3_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_3__0
       (.I0(cnt_2ms_reg[2]),
        .I1(cnt_2s_reg[2]),
        .I2(cnt_2s_reg[3]),
        .I3(cnt_2ms_reg[3]),
        .O(i__carry_i_3__0_n_0));
  LUT3 #(
    .INIT(8'hA8)) 
    i__carry_i_4
       (.I0(in[0]),
        .I1(\cnt_2ms[9]_i_4_n_0 ),
        .I2(i__carry_i_9_n_0),
        .O(i__carry_i_4_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    i__carry_i_4__0
       (.I0(cnt_2ms_reg[0]),
        .I1(cnt_2s_reg[0]),
        .I2(cnt_2s_reg[1]),
        .I3(cnt_2ms_reg[1]),
        .O(i__carry_i_4__0_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_5
       (.I0(cnt_2ms_reg[6]),
        .I1(cnt_2s_reg[6]),
        .I2(cnt_2s_reg[7]),
        .I3(cnt_2ms_reg[7]),
        .O(i__carry_i_5_n_0));
  LUT4 #(
    .INIT(16'h54A8)) 
    i__carry_i_5__0
       (.I0(in[3]),
        .I1(i__carry_i_9_n_0),
        .I2(\cnt_2ms[9]_i_4_n_0 ),
        .I3(cnt_2s_reg[3]),
        .O(i__carry_i_5__0_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_6
       (.I0(cnt_2ms_reg[4]),
        .I1(cnt_2s_reg[4]),
        .I2(cnt_2s_reg[5]),
        .I3(cnt_2ms_reg[5]),
        .O(i__carry_i_6_n_0));
  LUT4 #(
    .INIT(16'h54A8)) 
    i__carry_i_6__0
       (.I0(in[2]),
        .I1(i__carry_i_9_n_0),
        .I2(\cnt_2ms[9]_i_4_n_0 ),
        .I3(cnt_2s_reg[2]),
        .O(i__carry_i_6__0_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_7
       (.I0(cnt_2ms_reg[2]),
        .I1(cnt_2s_reg[2]),
        .I2(cnt_2s_reg[3]),
        .I3(cnt_2ms_reg[3]),
        .O(i__carry_i_7_n_0));
  LUT4 #(
    .INIT(16'h54A8)) 
    i__carry_i_7__0
       (.I0(in[1]),
        .I1(i__carry_i_9_n_0),
        .I2(\cnt_2ms[9]_i_4_n_0 ),
        .I3(cnt_2s_reg[1]),
        .O(i__carry_i_7__0_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    i__carry_i_8
       (.I0(cnt_2ms_reg[0]),
        .I1(cnt_2s_reg[0]),
        .I2(cnt_2s_reg[1]),
        .I3(cnt_2ms_reg[1]),
        .O(i__carry_i_8_n_0));
  LUT4 #(
    .INIT(16'h54A8)) 
    i__carry_i_8__0
       (.I0(in[0]),
        .I1(i__carry_i_9_n_0),
        .I2(\cnt_2ms[9]_i_4_n_0 ),
        .I3(cnt_2s_reg[0]),
        .O(i__carry_i_8__0_n_0));
  LUT6 #(
    .INIT(64'hFFFFFFFF7FFFFFFF)) 
    i__carry_i_9
       (.I0(cnt_2s_reg[8]),
        .I1(cnt_2s_reg[5]),
        .I2(cnt_2s_reg[6]),
        .I3(cnt_2s_reg[7]),
        .I4(cnt_2s_reg[9]),
        .I5(i__carry_i_10_n_0),
        .O(i__carry_i_9_n_0));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT3 #(
    .INIT(8'hB4)) 
    inc_dec_flag_i_1
       (.I0(i__carry_i_9_n_0),
        .I1(\cnt_2s[9]_i_1_n_0 ),
        .I2(inc_dec_flag),
        .O(inc_dec_flag_i_1_n_0));
  FDCE inc_dec_flag_reg
       (.C(s0_axi_aclk),
        .CE(1'b1),
        .CLR(s0_axi_aresetn_0),
        .D(inc_dec_flag_i_1_n_0),
        .Q(inc_dec_flag));
  LUT2 #(
    .INIT(4'h8)) 
    led_INST_0
       (.I0(led_t),
        .I1(led_0),
        .O(led));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY4 led_t2_carry
       (.CI(1'b0),
        .CO({led_t2_carry_n_0,led_t2_carry_n_1,led_t2_carry_n_2,led_t2_carry_n_3}),
        .CYINIT(1'b1),
        .DI({led_t2_carry_i_1_n_0,led_t2_carry_i_2_n_0,led_t2_carry_i_3_n_0,led_t2_carry_i_4_n_0}),
        .O(NLW_led_t2_carry_O_UNCONNECTED[3:0]),
        .S({led_t2_carry_i_5_n_0,led_t2_carry_i_6_n_0,led_t2_carry_i_7_n_0,led_t2_carry_i_8_n_0}));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY4 led_t2_carry__0
       (.CI(led_t2_carry_n_0),
        .CO({NLW_led_t2_carry__0_CO_UNCONNECTED[3:1],led_t2}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,led_t2_carry__0_i_1_n_0}),
        .O(NLW_led_t2_carry__0_O_UNCONNECTED[3:0]),
        .S({1'b0,1'b0,1'b0,led_t2_carry__0_i_2_n_0}));
  LUT4 #(
    .INIT(16'h2F02)) 
    led_t2_carry__0_i_1
       (.I0(cnt_2s_reg[8]),
        .I1(cnt_2ms_reg[8]),
        .I2(cnt_2ms_reg[9]),
        .I3(cnt_2s_reg[9]),
        .O(led_t2_carry__0_i_1_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    led_t2_carry__0_i_2
       (.I0(cnt_2ms_reg[8]),
        .I1(cnt_2s_reg[8]),
        .I2(cnt_2s_reg[9]),
        .I3(cnt_2ms_reg[9]),
        .O(led_t2_carry__0_i_2_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    led_t2_carry_i_1
       (.I0(cnt_2s_reg[6]),
        .I1(cnt_2ms_reg[6]),
        .I2(cnt_2ms_reg[7]),
        .I3(cnt_2s_reg[7]),
        .O(led_t2_carry_i_1_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    led_t2_carry_i_2
       (.I0(cnt_2s_reg[4]),
        .I1(cnt_2ms_reg[4]),
        .I2(cnt_2ms_reg[5]),
        .I3(cnt_2s_reg[5]),
        .O(led_t2_carry_i_2_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    led_t2_carry_i_3
       (.I0(cnt_2s_reg[2]),
        .I1(cnt_2ms_reg[2]),
        .I2(cnt_2ms_reg[3]),
        .I3(cnt_2s_reg[3]),
        .O(led_t2_carry_i_3_n_0));
  LUT4 #(
    .INIT(16'h2F02)) 
    led_t2_carry_i_4
       (.I0(cnt_2s_reg[0]),
        .I1(cnt_2ms_reg[0]),
        .I2(cnt_2ms_reg[1]),
        .I3(cnt_2s_reg[1]),
        .O(led_t2_carry_i_4_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    led_t2_carry_i_5
       (.I0(cnt_2ms_reg[6]),
        .I1(cnt_2s_reg[6]),
        .I2(cnt_2s_reg[7]),
        .I3(cnt_2ms_reg[7]),
        .O(led_t2_carry_i_5_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    led_t2_carry_i_6
       (.I0(cnt_2ms_reg[4]),
        .I1(cnt_2s_reg[4]),
        .I2(cnt_2s_reg[5]),
        .I3(cnt_2ms_reg[5]),
        .O(led_t2_carry_i_6_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    led_t2_carry_i_7
       (.I0(cnt_2ms_reg[2]),
        .I1(cnt_2s_reg[2]),
        .I2(cnt_2s_reg[3]),
        .I3(cnt_2ms_reg[3]),
        .O(led_t2_carry_i_7_n_0));
  LUT4 #(
    .INIT(16'h9009)) 
    led_t2_carry_i_8
       (.I0(cnt_2ms_reg[0]),
        .I1(cnt_2s_reg[0]),
        .I2(cnt_2s_reg[1]),
        .I3(cnt_2ms_reg[1]),
        .O(led_t2_carry_i_8_n_0));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY4 \led_t2_inferred__0/i__carry 
       (.CI(1'b0),
        .CO({\led_t2_inferred__0/i__carry_n_0 ,\led_t2_inferred__0/i__carry_n_1 ,\led_t2_inferred__0/i__carry_n_2 ,\led_t2_inferred__0/i__carry_n_3 }),
        .CYINIT(1'b1),
        .DI({i__carry_i_1__0_n_0,i__carry_i_2__0_n_0,i__carry_i_3__0_n_0,i__carry_i_4__0_n_0}),
        .O(\NLW_led_t2_inferred__0/i__carry_O_UNCONNECTED [3:0]),
        .S({i__carry_i_5_n_0,i__carry_i_6_n_0,i__carry_i_7_n_0,i__carry_i_8_n_0}));
  (* COMPARATOR_THRESHOLD = "11" *) 
  CARRY4 \led_t2_inferred__0/i__carry__0 
       (.CI(\led_t2_inferred__0/i__carry_n_0 ),
        .CO({\NLW_led_t2_inferred__0/i__carry__0_CO_UNCONNECTED [3:1],led_t21_in}),
        .CYINIT(1'b0),
        .DI({1'b0,1'b0,1'b0,i__carry__0_i_1__0_n_0}),
        .O(\NLW_led_t2_inferred__0/i__carry__0_O_UNCONNECTED [3:0]),
        .S({1'b0,1'b0,1'b0,i__carry__0_i_2__0_n_0}));
  (* SOFT_HLUTNM = "soft_lutpair6" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    led_t_i_1
       (.I0(led_t21_in),
        .I1(inc_dec_flag),
        .I2(led_t2),
        .O(led_t_i_1_n_0));
  FDCE led_t_reg
       (.C(s0_axi_aclk),
        .CE(1'b1),
        .CLR(s0_axi_aresetn_0),
        .D(led_t_i_1_n_0),
        .Q(led_t));
endmodule

(* ORIG_REF_NAME = "breath_led_ip_v1_0" *) 
module system_breath_led_ip_0_0_breath_led_ip_v1_0
   (S_AXI_AWREADY,
    S_AXI_WREADY,
    S_AXI_ARREADY,
    s0_axi_rdata,
    led,
    s0_axi_rvalid,
    s0_axi_bvalid,
    s0_axi_aresetn,
    s0_axi_aclk,
    s0_axi_awaddr,
    s0_axi_wvalid,
    s0_axi_awvalid,
    s0_axi_wdata,
    s0_axi_araddr,
    s0_axi_arvalid,
    s0_axi_wstrb,
    s0_axi_bready,
    s0_axi_rready);
  output S_AXI_AWREADY;
  output S_AXI_WREADY;
  output S_AXI_ARREADY;
  output [31:0]s0_axi_rdata;
  output led;
  output s0_axi_rvalid;
  output s0_axi_bvalid;
  input s0_axi_aresetn;
  input s0_axi_aclk;
  input [1:0]s0_axi_awaddr;
  input s0_axi_wvalid;
  input s0_axi_awvalid;
  input [31:0]s0_axi_wdata;
  input [1:0]s0_axi_araddr;
  input s0_axi_arvalid;
  input [3:0]s0_axi_wstrb;
  input s0_axi_bready;
  input s0_axi_rready;

  wire S_AXI_ARREADY;
  wire S_AXI_AWREADY;
  wire S_AXI_WREADY;
  wire led;
  wire s0_axi_aclk;
  wire [1:0]s0_axi_araddr;
  wire s0_axi_aresetn;
  wire s0_axi_arvalid;
  wire [1:0]s0_axi_awaddr;
  wire s0_axi_awvalid;
  wire s0_axi_bready;
  wire s0_axi_bvalid;
  wire [31:0]s0_axi_rdata;
  wire s0_axi_rready;
  wire s0_axi_rvalid;
  wire [31:0]s0_axi_wdata;
  wire [3:0]s0_axi_wstrb;
  wire s0_axi_wvalid;

  system_breath_led_ip_0_0_breath_led_ip_v1_0_S0_AXI breath_led_ip_v1_0_S0_AXI_inst
       (.S_AXI_ARREADY(S_AXI_ARREADY),
        .S_AXI_AWREADY(S_AXI_AWREADY),
        .S_AXI_WREADY(S_AXI_WREADY),
        .led(led),
        .s0_axi_aclk(s0_axi_aclk),
        .s0_axi_araddr(s0_axi_araddr),
        .s0_axi_aresetn(s0_axi_aresetn),
        .s0_axi_arvalid(s0_axi_arvalid),
        .s0_axi_awaddr(s0_axi_awaddr),
        .s0_axi_awvalid(s0_axi_awvalid),
        .s0_axi_bready(s0_axi_bready),
        .s0_axi_bvalid(s0_axi_bvalid),
        .s0_axi_rdata(s0_axi_rdata),
        .s0_axi_rready(s0_axi_rready),
        .s0_axi_rvalid(s0_axi_rvalid),
        .s0_axi_wdata(s0_axi_wdata),
        .s0_axi_wstrb(s0_axi_wstrb),
        .s0_axi_wvalid(s0_axi_wvalid));
endmodule

(* ORIG_REF_NAME = "breath_led_ip_v1_0_S0_AXI" *) 
module system_breath_led_ip_0_0_breath_led_ip_v1_0_S0_AXI
   (S_AXI_AWREADY,
    S_AXI_WREADY,
    S_AXI_ARREADY,
    s0_axi_rdata,
    led,
    s0_axi_rvalid,
    s0_axi_bvalid,
    s0_axi_aresetn,
    s0_axi_aclk,
    s0_axi_awaddr,
    s0_axi_wvalid,
    s0_axi_awvalid,
    s0_axi_wdata,
    s0_axi_araddr,
    s0_axi_arvalid,
    s0_axi_wstrb,
    s0_axi_bready,
    s0_axi_rready);
  output S_AXI_AWREADY;
  output S_AXI_WREADY;
  output S_AXI_ARREADY;
  output [31:0]s0_axi_rdata;
  output led;
  output s0_axi_rvalid;
  output s0_axi_bvalid;
  input s0_axi_aresetn;
  input s0_axi_aclk;
  input [1:0]s0_axi_awaddr;
  input s0_axi_wvalid;
  input s0_axi_awvalid;
  input [31:0]s0_axi_wdata;
  input [1:0]s0_axi_araddr;
  input s0_axi_arvalid;
  input [3:0]s0_axi_wstrb;
  input s0_axi_bready;
  input s0_axi_rready;

  wire S_AXI_ARREADY;
  wire S_AXI_AWREADY;
  wire S_AXI_WREADY;
  wire aw_en_i_1_n_0;
  wire aw_en_reg_n_0;
  wire [3:2]axi_araddr;
  wire \axi_araddr[2]_i_1_n_0 ;
  wire \axi_araddr[3]_i_1_n_0 ;
  wire axi_arready0;
  wire \axi_awaddr[2]_i_1_n_0 ;
  wire \axi_awaddr[3]_i_1_n_0 ;
  wire axi_awready0;
  wire axi_bvalid_i_1_n_0;
  wire axi_rvalid_i_1_n_0;
  wire axi_wready0;
  wire led;
  wire [1:0]p_0_in;
  wire [31:0]reg_data_out;
  wire s0_axi_aclk;
  wire [1:0]s0_axi_araddr;
  wire s0_axi_aresetn;
  wire s0_axi_arvalid;
  wire [1:0]s0_axi_awaddr;
  wire s0_axi_awvalid;
  wire s0_axi_bready;
  wire s0_axi_bvalid;
  wire [31:0]s0_axi_rdata;
  wire s0_axi_rready;
  wire s0_axi_rvalid;
  wire [31:0]s0_axi_wdata;
  wire [3:0]s0_axi_wstrb;
  wire s0_axi_wvalid;
  wire [0:0]slv_reg0;
  wire \slv_reg0[15]_i_1_n_0 ;
  wire \slv_reg0[23]_i_1_n_0 ;
  wire \slv_reg0[31]_i_1_n_0 ;
  wire \slv_reg0[7]_i_1_n_0 ;
  wire \slv_reg0_reg_n_0_[10] ;
  wire \slv_reg0_reg_n_0_[11] ;
  wire \slv_reg0_reg_n_0_[12] ;
  wire \slv_reg0_reg_n_0_[13] ;
  wire \slv_reg0_reg_n_0_[14] ;
  wire \slv_reg0_reg_n_0_[15] ;
  wire \slv_reg0_reg_n_0_[16] ;
  wire \slv_reg0_reg_n_0_[17] ;
  wire \slv_reg0_reg_n_0_[18] ;
  wire \slv_reg0_reg_n_0_[19] ;
  wire \slv_reg0_reg_n_0_[1] ;
  wire \slv_reg0_reg_n_0_[20] ;
  wire \slv_reg0_reg_n_0_[21] ;
  wire \slv_reg0_reg_n_0_[22] ;
  wire \slv_reg0_reg_n_0_[23] ;
  wire \slv_reg0_reg_n_0_[24] ;
  wire \slv_reg0_reg_n_0_[25] ;
  wire \slv_reg0_reg_n_0_[26] ;
  wire \slv_reg0_reg_n_0_[27] ;
  wire \slv_reg0_reg_n_0_[28] ;
  wire \slv_reg0_reg_n_0_[29] ;
  wire \slv_reg0_reg_n_0_[2] ;
  wire \slv_reg0_reg_n_0_[30] ;
  wire \slv_reg0_reg_n_0_[31] ;
  wire \slv_reg0_reg_n_0_[3] ;
  wire \slv_reg0_reg_n_0_[4] ;
  wire \slv_reg0_reg_n_0_[5] ;
  wire \slv_reg0_reg_n_0_[6] ;
  wire \slv_reg0_reg_n_0_[7] ;
  wire \slv_reg0_reg_n_0_[8] ;
  wire \slv_reg0_reg_n_0_[9] ;
  wire [31:31]slv_reg1;
  wire \slv_reg1[15]_i_1_n_0 ;
  wire \slv_reg1[23]_i_1_n_0 ;
  wire \slv_reg1[31]_i_1_n_0 ;
  wire \slv_reg1[7]_i_1_n_0 ;
  wire \slv_reg1_reg_n_0_[0] ;
  wire \slv_reg1_reg_n_0_[10] ;
  wire \slv_reg1_reg_n_0_[11] ;
  wire \slv_reg1_reg_n_0_[12] ;
  wire \slv_reg1_reg_n_0_[13] ;
  wire \slv_reg1_reg_n_0_[14] ;
  wire \slv_reg1_reg_n_0_[15] ;
  wire \slv_reg1_reg_n_0_[16] ;
  wire \slv_reg1_reg_n_0_[17] ;
  wire \slv_reg1_reg_n_0_[18] ;
  wire \slv_reg1_reg_n_0_[19] ;
  wire \slv_reg1_reg_n_0_[1] ;
  wire \slv_reg1_reg_n_0_[20] ;
  wire \slv_reg1_reg_n_0_[21] ;
  wire \slv_reg1_reg_n_0_[22] ;
  wire \slv_reg1_reg_n_0_[23] ;
  wire \slv_reg1_reg_n_0_[24] ;
  wire \slv_reg1_reg_n_0_[25] ;
  wire \slv_reg1_reg_n_0_[26] ;
  wire \slv_reg1_reg_n_0_[27] ;
  wire \slv_reg1_reg_n_0_[28] ;
  wire \slv_reg1_reg_n_0_[29] ;
  wire \slv_reg1_reg_n_0_[2] ;
  wire \slv_reg1_reg_n_0_[30] ;
  wire \slv_reg1_reg_n_0_[3] ;
  wire \slv_reg1_reg_n_0_[4] ;
  wire \slv_reg1_reg_n_0_[5] ;
  wire \slv_reg1_reg_n_0_[6] ;
  wire \slv_reg1_reg_n_0_[7] ;
  wire \slv_reg1_reg_n_0_[8] ;
  wire \slv_reg1_reg_n_0_[9] ;
  wire [31:0]slv_reg2;
  wire \slv_reg2[15]_i_1_n_0 ;
  wire \slv_reg2[23]_i_1_n_0 ;
  wire \slv_reg2[31]_i_1_n_0 ;
  wire \slv_reg2[7]_i_1_n_0 ;
  wire [31:0]slv_reg3;
  wire \slv_reg3[15]_i_1_n_0 ;
  wire \slv_reg3[23]_i_1_n_0 ;
  wire \slv_reg3[31]_i_1_n_0 ;
  wire \slv_reg3[7]_i_1_n_0 ;
  wire slv_reg_rden__0;
  wire slv_reg_wren__0;
  wire u_breath_led_n_0;

  LUT6 #(
    .INIT(64'hF7FFC4CCC4CCC4CC)) 
    aw_en_i_1
       (.I0(s0_axi_awvalid),
        .I1(aw_en_reg_n_0),
        .I2(S_AXI_AWREADY),
        .I3(s0_axi_wvalid),
        .I4(s0_axi_bready),
        .I5(s0_axi_bvalid),
        .O(aw_en_i_1_n_0));
  FDSE aw_en_reg
       (.C(s0_axi_aclk),
        .CE(1'b1),
        .D(aw_en_i_1_n_0),
        .Q(aw_en_reg_n_0),
        .S(u_breath_led_n_0));
  LUT4 #(
    .INIT(16'hFB08)) 
    \axi_araddr[2]_i_1 
       (.I0(s0_axi_araddr[0]),
        .I1(s0_axi_arvalid),
        .I2(S_AXI_ARREADY),
        .I3(axi_araddr[2]),
        .O(\axi_araddr[2]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT4 #(
    .INIT(16'hFB08)) 
    \axi_araddr[3]_i_1 
       (.I0(s0_axi_araddr[1]),
        .I1(s0_axi_arvalid),
        .I2(S_AXI_ARREADY),
        .I3(axi_araddr[3]),
        .O(\axi_araddr[3]_i_1_n_0 ));
  FDRE \axi_araddr_reg[2] 
       (.C(s0_axi_aclk),
        .CE(1'b1),
        .D(\axi_araddr[2]_i_1_n_0 ),
        .Q(axi_araddr[2]),
        .R(u_breath_led_n_0));
  FDRE \axi_araddr_reg[3] 
       (.C(s0_axi_aclk),
        .CE(1'b1),
        .D(\axi_araddr[3]_i_1_n_0 ),
        .Q(axi_araddr[3]),
        .R(u_breath_led_n_0));
  (* SOFT_HLUTNM = "soft_lutpair10" *) 
  LUT2 #(
    .INIT(4'h2)) 
    axi_arready_i_1
       (.I0(s0_axi_arvalid),
        .I1(S_AXI_ARREADY),
        .O(axi_arready0));
  FDRE axi_arready_reg
       (.C(s0_axi_aclk),
        .CE(1'b1),
        .D(axi_arready0),
        .Q(S_AXI_ARREADY),
        .R(u_breath_led_n_0));
  LUT6 #(
    .INIT(64'hFBFFFFFF08000000)) 
    \axi_awaddr[2]_i_1 
       (.I0(s0_axi_awaddr[0]),
        .I1(s0_axi_wvalid),
        .I2(S_AXI_AWREADY),
        .I3(aw_en_reg_n_0),
        .I4(s0_axi_awvalid),
        .I5(p_0_in[0]),
        .O(\axi_awaddr[2]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hFBFFFFFF08000000)) 
    \axi_awaddr[3]_i_1 
       (.I0(s0_axi_awaddr[1]),
        .I1(s0_axi_wvalid),
        .I2(S_AXI_AWREADY),
        .I3(aw_en_reg_n_0),
        .I4(s0_axi_awvalid),
        .I5(p_0_in[1]),
        .O(\axi_awaddr[3]_i_1_n_0 ));
  FDRE \axi_awaddr_reg[2] 
       (.C(s0_axi_aclk),
        .CE(1'b1),
        .D(\axi_awaddr[2]_i_1_n_0 ),
        .Q(p_0_in[0]),
        .R(u_breath_led_n_0));
  FDRE \axi_awaddr_reg[3] 
       (.C(s0_axi_aclk),
        .CE(1'b1),
        .D(\axi_awaddr[3]_i_1_n_0 ),
        .Q(p_0_in[1]),
        .R(u_breath_led_n_0));
  LUT4 #(
    .INIT(16'h2000)) 
    axi_awready_i_2
       (.I0(s0_axi_wvalid),
        .I1(S_AXI_AWREADY),
        .I2(aw_en_reg_n_0),
        .I3(s0_axi_awvalid),
        .O(axi_awready0));
  FDRE axi_awready_reg
       (.C(s0_axi_aclk),
        .CE(1'b1),
        .D(axi_awready0),
        .Q(S_AXI_AWREADY),
        .R(u_breath_led_n_0));
  LUT6 #(
    .INIT(64'h0000FFFF80008000)) 
    axi_bvalid_i_1
       (.I0(s0_axi_awvalid),
        .I1(s0_axi_wvalid),
        .I2(S_AXI_AWREADY),
        .I3(S_AXI_WREADY),
        .I4(s0_axi_bready),
        .I5(s0_axi_bvalid),
        .O(axi_bvalid_i_1_n_0));
  FDRE axi_bvalid_reg
       (.C(s0_axi_aclk),
        .CE(1'b1),
        .D(axi_bvalid_i_1_n_0),
        .Q(s0_axi_bvalid),
        .R(u_breath_led_n_0));
  LUT6 #(
    .INIT(64'hFFCCF0AA00CCF0AA)) 
    \axi_rdata[0]_i_1 
       (.I0(slv_reg0),
        .I1(\slv_reg1_reg_n_0_[0] ),
        .I2(slv_reg2[0]),
        .I3(axi_araddr[3]),
        .I4(axi_araddr[2]),
        .I5(slv_reg3[0]),
        .O(reg_data_out[0]));
  LUT6 #(
    .INIT(64'hFFCCAAF000CCAAF0)) 
    \axi_rdata[10]_i_1 
       (.I0(\slv_reg1_reg_n_0_[10] ),
        .I1(slv_reg2[10]),
        .I2(\slv_reg0_reg_n_0_[10] ),
        .I3(axi_araddr[2]),
        .I4(axi_araddr[3]),
        .I5(slv_reg3[10]),
        .O(reg_data_out[10]));
  LUT6 #(
    .INIT(64'hF0FFCCAAF000CCAA)) 
    \axi_rdata[11]_i_1 
       (.I0(\slv_reg0_reg_n_0_[11] ),
        .I1(\slv_reg1_reg_n_0_[11] ),
        .I2(slv_reg3[11]),
        .I3(axi_araddr[2]),
        .I4(axi_araddr[3]),
        .I5(slv_reg2[11]),
        .O(reg_data_out[11]));
  LUT6 #(
    .INIT(64'hFFCCF0AA00CCF0AA)) 
    \axi_rdata[12]_i_1 
       (.I0(\slv_reg0_reg_n_0_[12] ),
        .I1(\slv_reg1_reg_n_0_[12] ),
        .I2(slv_reg2[12]),
        .I3(axi_araddr[3]),
        .I4(axi_araddr[2]),
        .I5(slv_reg3[12]),
        .O(reg_data_out[12]));
  LUT6 #(
    .INIT(64'hFFCCF0AA00CCF0AA)) 
    \axi_rdata[13]_i_1 
       (.I0(\slv_reg0_reg_n_0_[13] ),
        .I1(\slv_reg1_reg_n_0_[13] ),
        .I2(slv_reg2[13]),
        .I3(axi_araddr[3]),
        .I4(axi_araddr[2]),
        .I5(slv_reg3[13]),
        .O(reg_data_out[13]));
  LUT6 #(
    .INIT(64'hFFCCF0AA00CCF0AA)) 
    \axi_rdata[14]_i_1 
       (.I0(\slv_reg0_reg_n_0_[14] ),
        .I1(\slv_reg1_reg_n_0_[14] ),
        .I2(slv_reg2[14]),
        .I3(axi_araddr[3]),
        .I4(axi_araddr[2]),
        .I5(slv_reg3[14]),
        .O(reg_data_out[14]));
  LUT6 #(
    .INIT(64'hF0FFCCAAF000CCAA)) 
    \axi_rdata[15]_i_1 
       (.I0(\slv_reg0_reg_n_0_[15] ),
        .I1(\slv_reg1_reg_n_0_[15] ),
        .I2(slv_reg3[15]),
        .I3(axi_araddr[2]),
        .I4(axi_araddr[3]),
        .I5(slv_reg2[15]),
        .O(reg_data_out[15]));
  LUT6 #(
    .INIT(64'hF0FFCCAAF000CCAA)) 
    \axi_rdata[16]_i_1 
       (.I0(\slv_reg0_reg_n_0_[16] ),
        .I1(\slv_reg1_reg_n_0_[16] ),
        .I2(slv_reg3[16]),
        .I3(axi_araddr[2]),
        .I4(axi_araddr[3]),
        .I5(slv_reg2[16]),
        .O(reg_data_out[16]));
  LUT6 #(
    .INIT(64'hF0FFCCAAF000CCAA)) 
    \axi_rdata[17]_i_1 
       (.I0(\slv_reg0_reg_n_0_[17] ),
        .I1(\slv_reg1_reg_n_0_[17] ),
        .I2(slv_reg3[17]),
        .I3(axi_araddr[2]),
        .I4(axi_araddr[3]),
        .I5(slv_reg2[17]),
        .O(reg_data_out[17]));
  LUT6 #(
    .INIT(64'hFFCCAAF000CCAAF0)) 
    \axi_rdata[18]_i_1 
       (.I0(\slv_reg1_reg_n_0_[18] ),
        .I1(slv_reg2[18]),
        .I2(\slv_reg0_reg_n_0_[18] ),
        .I3(axi_araddr[2]),
        .I4(axi_araddr[3]),
        .I5(slv_reg3[18]),
        .O(reg_data_out[18]));
  LUT6 #(
    .INIT(64'hF0FFCCAAF000CCAA)) 
    \axi_rdata[19]_i_1 
       (.I0(\slv_reg0_reg_n_0_[19] ),
        .I1(\slv_reg1_reg_n_0_[19] ),
        .I2(slv_reg3[19]),
        .I3(axi_araddr[2]),
        .I4(axi_araddr[3]),
        .I5(slv_reg2[19]),
        .O(reg_data_out[19]));
  LUT6 #(
    .INIT(64'hFFCCF0AA00CCF0AA)) 
    \axi_rdata[1]_i_1 
       (.I0(\slv_reg0_reg_n_0_[1] ),
        .I1(\slv_reg1_reg_n_0_[1] ),
        .I2(slv_reg2[1]),
        .I3(axi_araddr[3]),
        .I4(axi_araddr[2]),
        .I5(slv_reg3[1]),
        .O(reg_data_out[1]));
  LUT6 #(
    .INIT(64'hFFCCF0AA00CCF0AA)) 
    \axi_rdata[20]_i_1 
       (.I0(\slv_reg0_reg_n_0_[20] ),
        .I1(\slv_reg1_reg_n_0_[20] ),
        .I2(slv_reg2[20]),
        .I3(axi_araddr[3]),
        .I4(axi_araddr[2]),
        .I5(slv_reg3[20]),
        .O(reg_data_out[20]));
  LUT6 #(
    .INIT(64'hFFCCF0AA00CCF0AA)) 
    \axi_rdata[21]_i_1 
       (.I0(\slv_reg0_reg_n_0_[21] ),
        .I1(\slv_reg1_reg_n_0_[21] ),
        .I2(slv_reg2[21]),
        .I3(axi_araddr[3]),
        .I4(axi_araddr[2]),
        .I5(slv_reg3[21]),
        .O(reg_data_out[21]));
  LUT6 #(
    .INIT(64'hFFCCF0AA00CCF0AA)) 
    \axi_rdata[22]_i_1 
       (.I0(\slv_reg0_reg_n_0_[22] ),
        .I1(\slv_reg1_reg_n_0_[22] ),
        .I2(slv_reg2[22]),
        .I3(axi_araddr[3]),
        .I4(axi_araddr[2]),
        .I5(slv_reg3[22]),
        .O(reg_data_out[22]));
  LUT6 #(
    .INIT(64'hF0FFCCAAF000CCAA)) 
    \axi_rdata[23]_i_1 
       (.I0(\slv_reg0_reg_n_0_[23] ),
        .I1(\slv_reg1_reg_n_0_[23] ),
        .I2(slv_reg3[23]),
        .I3(axi_araddr[2]),
        .I4(axi_araddr[3]),
        .I5(slv_reg2[23]),
        .O(reg_data_out[23]));
  LUT6 #(
    .INIT(64'hF0FFCCAAF000CCAA)) 
    \axi_rdata[24]_i_1 
       (.I0(\slv_reg0_reg_n_0_[24] ),
        .I1(\slv_reg1_reg_n_0_[24] ),
        .I2(slv_reg3[24]),
        .I3(axi_araddr[2]),
        .I4(axi_araddr[3]),
        .I5(slv_reg2[24]),
        .O(reg_data_out[24]));
  LUT6 #(
    .INIT(64'hF0FFCCAAF000CCAA)) 
    \axi_rdata[25]_i_1 
       (.I0(\slv_reg0_reg_n_0_[25] ),
        .I1(\slv_reg1_reg_n_0_[25] ),
        .I2(slv_reg3[25]),
        .I3(axi_araddr[2]),
        .I4(axi_araddr[3]),
        .I5(slv_reg2[25]),
        .O(reg_data_out[25]));
  LUT6 #(
    .INIT(64'hFFCCAAF000CCAAF0)) 
    \axi_rdata[26]_i_1 
       (.I0(\slv_reg1_reg_n_0_[26] ),
        .I1(slv_reg2[26]),
        .I2(\slv_reg0_reg_n_0_[26] ),
        .I3(axi_araddr[2]),
        .I4(axi_araddr[3]),
        .I5(slv_reg3[26]),
        .O(reg_data_out[26]));
  LUT6 #(
    .INIT(64'hF0FFCCAAF000CCAA)) 
    \axi_rdata[27]_i_1 
       (.I0(\slv_reg0_reg_n_0_[27] ),
        .I1(\slv_reg1_reg_n_0_[27] ),
        .I2(slv_reg3[27]),
        .I3(axi_araddr[2]),
        .I4(axi_araddr[3]),
        .I5(slv_reg2[27]),
        .O(reg_data_out[27]));
  LUT6 #(
    .INIT(64'hFFCCF0AA00CCF0AA)) 
    \axi_rdata[28]_i_1 
       (.I0(\slv_reg0_reg_n_0_[28] ),
        .I1(\slv_reg1_reg_n_0_[28] ),
        .I2(slv_reg2[28]),
        .I3(axi_araddr[3]),
        .I4(axi_araddr[2]),
        .I5(slv_reg3[28]),
        .O(reg_data_out[28]));
  LUT6 #(
    .INIT(64'hFFCCF0AA00CCF0AA)) 
    \axi_rdata[29]_i_1 
       (.I0(\slv_reg0_reg_n_0_[29] ),
        .I1(\slv_reg1_reg_n_0_[29] ),
        .I2(slv_reg2[29]),
        .I3(axi_araddr[3]),
        .I4(axi_araddr[2]),
        .I5(slv_reg3[29]),
        .O(reg_data_out[29]));
  LUT6 #(
    .INIT(64'hF0FFCCAAF000CCAA)) 
    \axi_rdata[2]_i_1 
       (.I0(\slv_reg0_reg_n_0_[2] ),
        .I1(\slv_reg1_reg_n_0_[2] ),
        .I2(slv_reg3[2]),
        .I3(axi_araddr[2]),
        .I4(axi_araddr[3]),
        .I5(slv_reg2[2]),
        .O(reg_data_out[2]));
  LUT6 #(
    .INIT(64'hFFCCF0AA00CCF0AA)) 
    \axi_rdata[30]_i_1 
       (.I0(\slv_reg0_reg_n_0_[30] ),
        .I1(\slv_reg1_reg_n_0_[30] ),
        .I2(slv_reg2[30]),
        .I3(axi_araddr[3]),
        .I4(axi_araddr[2]),
        .I5(slv_reg3[30]),
        .O(reg_data_out[30]));
  LUT6 #(
    .INIT(64'hFFCCF0AA00CCF0AA)) 
    \axi_rdata[31]_i_1 
       (.I0(\slv_reg0_reg_n_0_[31] ),
        .I1(slv_reg1),
        .I2(slv_reg2[31]),
        .I3(axi_araddr[3]),
        .I4(axi_araddr[2]),
        .I5(slv_reg3[31]),
        .O(reg_data_out[31]));
  LUT6 #(
    .INIT(64'hF0FFCCAAF000CCAA)) 
    \axi_rdata[3]_i_1 
       (.I0(\slv_reg0_reg_n_0_[3] ),
        .I1(\slv_reg1_reg_n_0_[3] ),
        .I2(slv_reg3[3]),
        .I3(axi_araddr[2]),
        .I4(axi_araddr[3]),
        .I5(slv_reg2[3]),
        .O(reg_data_out[3]));
  LUT6 #(
    .INIT(64'hFFCCF0AA00CCF0AA)) 
    \axi_rdata[4]_i_1 
       (.I0(\slv_reg0_reg_n_0_[4] ),
        .I1(\slv_reg1_reg_n_0_[4] ),
        .I2(slv_reg2[4]),
        .I3(axi_araddr[3]),
        .I4(axi_araddr[2]),
        .I5(slv_reg3[4]),
        .O(reg_data_out[4]));
  LUT6 #(
    .INIT(64'hFFCCF0AA00CCF0AA)) 
    \axi_rdata[5]_i_1 
       (.I0(\slv_reg0_reg_n_0_[5] ),
        .I1(\slv_reg1_reg_n_0_[5] ),
        .I2(slv_reg2[5]),
        .I3(axi_araddr[3]),
        .I4(axi_araddr[2]),
        .I5(slv_reg3[5]),
        .O(reg_data_out[5]));
  LUT6 #(
    .INIT(64'hF0FFCCAAF000CCAA)) 
    \axi_rdata[6]_i_1 
       (.I0(\slv_reg0_reg_n_0_[6] ),
        .I1(\slv_reg1_reg_n_0_[6] ),
        .I2(slv_reg3[6]),
        .I3(axi_araddr[2]),
        .I4(axi_araddr[3]),
        .I5(slv_reg2[6]),
        .O(reg_data_out[6]));
  LUT6 #(
    .INIT(64'hF0FFCCAAF000CCAA)) 
    \axi_rdata[7]_i_1 
       (.I0(\slv_reg0_reg_n_0_[7] ),
        .I1(\slv_reg1_reg_n_0_[7] ),
        .I2(slv_reg3[7]),
        .I3(axi_araddr[2]),
        .I4(axi_araddr[3]),
        .I5(slv_reg2[7]),
        .O(reg_data_out[7]));
  LUT6 #(
    .INIT(64'hCCFFAAF0CC00AAF0)) 
    \axi_rdata[8]_i_1 
       (.I0(\slv_reg1_reg_n_0_[8] ),
        .I1(slv_reg3[8]),
        .I2(\slv_reg0_reg_n_0_[8] ),
        .I3(axi_araddr[2]),
        .I4(axi_araddr[3]),
        .I5(slv_reg2[8]),
        .O(reg_data_out[8]));
  LUT6 #(
    .INIT(64'hF0FFCCAAF000CCAA)) 
    \axi_rdata[9]_i_1 
       (.I0(\slv_reg0_reg_n_0_[9] ),
        .I1(\slv_reg1_reg_n_0_[9] ),
        .I2(slv_reg3[9]),
        .I3(axi_araddr[2]),
        .I4(axi_araddr[3]),
        .I5(slv_reg2[9]),
        .O(reg_data_out[9]));
  FDRE \axi_rdata_reg[0] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[0]),
        .Q(s0_axi_rdata[0]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[10] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[10]),
        .Q(s0_axi_rdata[10]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[11] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[11]),
        .Q(s0_axi_rdata[11]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[12] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[12]),
        .Q(s0_axi_rdata[12]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[13] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[13]),
        .Q(s0_axi_rdata[13]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[14] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[14]),
        .Q(s0_axi_rdata[14]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[15] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[15]),
        .Q(s0_axi_rdata[15]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[16] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[16]),
        .Q(s0_axi_rdata[16]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[17] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[17]),
        .Q(s0_axi_rdata[17]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[18] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[18]),
        .Q(s0_axi_rdata[18]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[19] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[19]),
        .Q(s0_axi_rdata[19]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[1] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[1]),
        .Q(s0_axi_rdata[1]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[20] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[20]),
        .Q(s0_axi_rdata[20]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[21] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[21]),
        .Q(s0_axi_rdata[21]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[22] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[22]),
        .Q(s0_axi_rdata[22]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[23] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[23]),
        .Q(s0_axi_rdata[23]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[24] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[24]),
        .Q(s0_axi_rdata[24]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[25] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[25]),
        .Q(s0_axi_rdata[25]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[26] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[26]),
        .Q(s0_axi_rdata[26]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[27] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[27]),
        .Q(s0_axi_rdata[27]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[28] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[28]),
        .Q(s0_axi_rdata[28]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[29] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[29]),
        .Q(s0_axi_rdata[29]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[2] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[2]),
        .Q(s0_axi_rdata[2]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[30] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[30]),
        .Q(s0_axi_rdata[30]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[31] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[31]),
        .Q(s0_axi_rdata[31]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[3] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[3]),
        .Q(s0_axi_rdata[3]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[4] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[4]),
        .Q(s0_axi_rdata[4]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[5] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[5]),
        .Q(s0_axi_rdata[5]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[6] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[6]),
        .Q(s0_axi_rdata[6]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[7] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[7]),
        .Q(s0_axi_rdata[7]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[8] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[8]),
        .Q(s0_axi_rdata[8]),
        .R(u_breath_led_n_0));
  FDRE \axi_rdata_reg[9] 
       (.C(s0_axi_aclk),
        .CE(slv_reg_rden__0),
        .D(reg_data_out[9]),
        .Q(s0_axi_rdata[9]),
        .R(u_breath_led_n_0));
  LUT4 #(
    .INIT(16'h08F8)) 
    axi_rvalid_i_1
       (.I0(S_AXI_ARREADY),
        .I1(s0_axi_arvalid),
        .I2(s0_axi_rvalid),
        .I3(s0_axi_rready),
        .O(axi_rvalid_i_1_n_0));
  FDRE axi_rvalid_reg
       (.C(s0_axi_aclk),
        .CE(1'b1),
        .D(axi_rvalid_i_1_n_0),
        .Q(s0_axi_rvalid),
        .R(u_breath_led_n_0));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT4 #(
    .INIT(16'h0800)) 
    axi_wready_i_1
       (.I0(s0_axi_awvalid),
        .I1(s0_axi_wvalid),
        .I2(S_AXI_WREADY),
        .I3(aw_en_reg_n_0),
        .O(axi_wready0));
  FDRE axi_wready_reg
       (.C(s0_axi_aclk),
        .CE(1'b1),
        .D(axi_wready0),
        .Q(S_AXI_WREADY),
        .R(u_breath_led_n_0));
  LUT4 #(
    .INIT(16'h0200)) 
    \slv_reg0[15]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[1]),
        .I2(p_0_in[0]),
        .I3(s0_axi_wstrb[1]),
        .O(\slv_reg0[15]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h0200)) 
    \slv_reg0[23]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[1]),
        .I2(p_0_in[0]),
        .I3(s0_axi_wstrb[2]),
        .O(\slv_reg0[23]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h0200)) 
    \slv_reg0[31]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[1]),
        .I2(p_0_in[0]),
        .I3(s0_axi_wstrb[3]),
        .O(\slv_reg0[31]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h0200)) 
    \slv_reg0[7]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[1]),
        .I2(p_0_in[0]),
        .I3(s0_axi_wstrb[0]),
        .O(\slv_reg0[7]_i_1_n_0 ));
  FDRE \slv_reg0_reg[0] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[7]_i_1_n_0 ),
        .D(s0_axi_wdata[0]),
        .Q(slv_reg0),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[10] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[15]_i_1_n_0 ),
        .D(s0_axi_wdata[10]),
        .Q(\slv_reg0_reg_n_0_[10] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[11] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[15]_i_1_n_0 ),
        .D(s0_axi_wdata[11]),
        .Q(\slv_reg0_reg_n_0_[11] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[12] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[15]_i_1_n_0 ),
        .D(s0_axi_wdata[12]),
        .Q(\slv_reg0_reg_n_0_[12] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[13] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[15]_i_1_n_0 ),
        .D(s0_axi_wdata[13]),
        .Q(\slv_reg0_reg_n_0_[13] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[14] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[15]_i_1_n_0 ),
        .D(s0_axi_wdata[14]),
        .Q(\slv_reg0_reg_n_0_[14] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[15] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[15]_i_1_n_0 ),
        .D(s0_axi_wdata[15]),
        .Q(\slv_reg0_reg_n_0_[15] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[16] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[23]_i_1_n_0 ),
        .D(s0_axi_wdata[16]),
        .Q(\slv_reg0_reg_n_0_[16] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[17] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[23]_i_1_n_0 ),
        .D(s0_axi_wdata[17]),
        .Q(\slv_reg0_reg_n_0_[17] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[18] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[23]_i_1_n_0 ),
        .D(s0_axi_wdata[18]),
        .Q(\slv_reg0_reg_n_0_[18] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[19] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[23]_i_1_n_0 ),
        .D(s0_axi_wdata[19]),
        .Q(\slv_reg0_reg_n_0_[19] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[1] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[7]_i_1_n_0 ),
        .D(s0_axi_wdata[1]),
        .Q(\slv_reg0_reg_n_0_[1] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[20] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[23]_i_1_n_0 ),
        .D(s0_axi_wdata[20]),
        .Q(\slv_reg0_reg_n_0_[20] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[21] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[23]_i_1_n_0 ),
        .D(s0_axi_wdata[21]),
        .Q(\slv_reg0_reg_n_0_[21] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[22] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[23]_i_1_n_0 ),
        .D(s0_axi_wdata[22]),
        .Q(\slv_reg0_reg_n_0_[22] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[23] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[23]_i_1_n_0 ),
        .D(s0_axi_wdata[23]),
        .Q(\slv_reg0_reg_n_0_[23] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[24] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[31]_i_1_n_0 ),
        .D(s0_axi_wdata[24]),
        .Q(\slv_reg0_reg_n_0_[24] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[25] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[31]_i_1_n_0 ),
        .D(s0_axi_wdata[25]),
        .Q(\slv_reg0_reg_n_0_[25] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[26] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[31]_i_1_n_0 ),
        .D(s0_axi_wdata[26]),
        .Q(\slv_reg0_reg_n_0_[26] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[27] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[31]_i_1_n_0 ),
        .D(s0_axi_wdata[27]),
        .Q(\slv_reg0_reg_n_0_[27] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[28] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[31]_i_1_n_0 ),
        .D(s0_axi_wdata[28]),
        .Q(\slv_reg0_reg_n_0_[28] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[29] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[31]_i_1_n_0 ),
        .D(s0_axi_wdata[29]),
        .Q(\slv_reg0_reg_n_0_[29] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[2] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[7]_i_1_n_0 ),
        .D(s0_axi_wdata[2]),
        .Q(\slv_reg0_reg_n_0_[2] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[30] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[31]_i_1_n_0 ),
        .D(s0_axi_wdata[30]),
        .Q(\slv_reg0_reg_n_0_[30] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[31] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[31]_i_1_n_0 ),
        .D(s0_axi_wdata[31]),
        .Q(\slv_reg0_reg_n_0_[31] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[3] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[7]_i_1_n_0 ),
        .D(s0_axi_wdata[3]),
        .Q(\slv_reg0_reg_n_0_[3] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[4] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[7]_i_1_n_0 ),
        .D(s0_axi_wdata[4]),
        .Q(\slv_reg0_reg_n_0_[4] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[5] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[7]_i_1_n_0 ),
        .D(s0_axi_wdata[5]),
        .Q(\slv_reg0_reg_n_0_[5] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[6] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[7]_i_1_n_0 ),
        .D(s0_axi_wdata[6]),
        .Q(\slv_reg0_reg_n_0_[6] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[7] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[7]_i_1_n_0 ),
        .D(s0_axi_wdata[7]),
        .Q(\slv_reg0_reg_n_0_[7] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[8] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[15]_i_1_n_0 ),
        .D(s0_axi_wdata[8]),
        .Q(\slv_reg0_reg_n_0_[8] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg0_reg[9] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg0[15]_i_1_n_0 ),
        .D(s0_axi_wdata[9]),
        .Q(\slv_reg0_reg_n_0_[9] ),
        .R(u_breath_led_n_0));
  LUT4 #(
    .INIT(16'h2000)) 
    \slv_reg1[15]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[1]),
        .I2(s0_axi_wstrb[1]),
        .I3(p_0_in[0]),
        .O(\slv_reg1[15]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h2000)) 
    \slv_reg1[23]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[1]),
        .I2(s0_axi_wstrb[2]),
        .I3(p_0_in[0]),
        .O(\slv_reg1[23]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h2000)) 
    \slv_reg1[31]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[1]),
        .I2(s0_axi_wstrb[3]),
        .I3(p_0_in[0]),
        .O(\slv_reg1[31]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair11" *) 
  LUT4 #(
    .INIT(16'h8000)) 
    \slv_reg1[31]_i_2 
       (.I0(S_AXI_WREADY),
        .I1(S_AXI_AWREADY),
        .I2(s0_axi_awvalid),
        .I3(s0_axi_wvalid),
        .O(slv_reg_wren__0));
  LUT4 #(
    .INIT(16'h2000)) 
    \slv_reg1[7]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[1]),
        .I2(s0_axi_wstrb[0]),
        .I3(p_0_in[0]),
        .O(\slv_reg1[7]_i_1_n_0 ));
  FDRE \slv_reg1_reg[0] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[7]_i_1_n_0 ),
        .D(s0_axi_wdata[0]),
        .Q(\slv_reg1_reg_n_0_[0] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[10] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[15]_i_1_n_0 ),
        .D(s0_axi_wdata[10]),
        .Q(\slv_reg1_reg_n_0_[10] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[11] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[15]_i_1_n_0 ),
        .D(s0_axi_wdata[11]),
        .Q(\slv_reg1_reg_n_0_[11] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[12] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[15]_i_1_n_0 ),
        .D(s0_axi_wdata[12]),
        .Q(\slv_reg1_reg_n_0_[12] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[13] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[15]_i_1_n_0 ),
        .D(s0_axi_wdata[13]),
        .Q(\slv_reg1_reg_n_0_[13] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[14] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[15]_i_1_n_0 ),
        .D(s0_axi_wdata[14]),
        .Q(\slv_reg1_reg_n_0_[14] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[15] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[15]_i_1_n_0 ),
        .D(s0_axi_wdata[15]),
        .Q(\slv_reg1_reg_n_0_[15] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[16] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[23]_i_1_n_0 ),
        .D(s0_axi_wdata[16]),
        .Q(\slv_reg1_reg_n_0_[16] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[17] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[23]_i_1_n_0 ),
        .D(s0_axi_wdata[17]),
        .Q(\slv_reg1_reg_n_0_[17] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[18] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[23]_i_1_n_0 ),
        .D(s0_axi_wdata[18]),
        .Q(\slv_reg1_reg_n_0_[18] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[19] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[23]_i_1_n_0 ),
        .D(s0_axi_wdata[19]),
        .Q(\slv_reg1_reg_n_0_[19] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[1] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[7]_i_1_n_0 ),
        .D(s0_axi_wdata[1]),
        .Q(\slv_reg1_reg_n_0_[1] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[20] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[23]_i_1_n_0 ),
        .D(s0_axi_wdata[20]),
        .Q(\slv_reg1_reg_n_0_[20] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[21] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[23]_i_1_n_0 ),
        .D(s0_axi_wdata[21]),
        .Q(\slv_reg1_reg_n_0_[21] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[22] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[23]_i_1_n_0 ),
        .D(s0_axi_wdata[22]),
        .Q(\slv_reg1_reg_n_0_[22] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[23] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[23]_i_1_n_0 ),
        .D(s0_axi_wdata[23]),
        .Q(\slv_reg1_reg_n_0_[23] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[24] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[31]_i_1_n_0 ),
        .D(s0_axi_wdata[24]),
        .Q(\slv_reg1_reg_n_0_[24] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[25] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[31]_i_1_n_0 ),
        .D(s0_axi_wdata[25]),
        .Q(\slv_reg1_reg_n_0_[25] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[26] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[31]_i_1_n_0 ),
        .D(s0_axi_wdata[26]),
        .Q(\slv_reg1_reg_n_0_[26] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[27] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[31]_i_1_n_0 ),
        .D(s0_axi_wdata[27]),
        .Q(\slv_reg1_reg_n_0_[27] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[28] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[31]_i_1_n_0 ),
        .D(s0_axi_wdata[28]),
        .Q(\slv_reg1_reg_n_0_[28] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[29] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[31]_i_1_n_0 ),
        .D(s0_axi_wdata[29]),
        .Q(\slv_reg1_reg_n_0_[29] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[2] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[7]_i_1_n_0 ),
        .D(s0_axi_wdata[2]),
        .Q(\slv_reg1_reg_n_0_[2] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[30] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[31]_i_1_n_0 ),
        .D(s0_axi_wdata[30]),
        .Q(\slv_reg1_reg_n_0_[30] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[31] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[31]_i_1_n_0 ),
        .D(s0_axi_wdata[31]),
        .Q(slv_reg1),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[3] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[7]_i_1_n_0 ),
        .D(s0_axi_wdata[3]),
        .Q(\slv_reg1_reg_n_0_[3] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[4] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[7]_i_1_n_0 ),
        .D(s0_axi_wdata[4]),
        .Q(\slv_reg1_reg_n_0_[4] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[5] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[7]_i_1_n_0 ),
        .D(s0_axi_wdata[5]),
        .Q(\slv_reg1_reg_n_0_[5] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[6] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[7]_i_1_n_0 ),
        .D(s0_axi_wdata[6]),
        .Q(\slv_reg1_reg_n_0_[6] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[7] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[7]_i_1_n_0 ),
        .D(s0_axi_wdata[7]),
        .Q(\slv_reg1_reg_n_0_[7] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[8] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[15]_i_1_n_0 ),
        .D(s0_axi_wdata[8]),
        .Q(\slv_reg1_reg_n_0_[8] ),
        .R(u_breath_led_n_0));
  FDRE \slv_reg1_reg[9] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg1[15]_i_1_n_0 ),
        .D(s0_axi_wdata[9]),
        .Q(\slv_reg1_reg_n_0_[9] ),
        .R(u_breath_led_n_0));
  LUT4 #(
    .INIT(16'h0080)) 
    \slv_reg2[15]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[1]),
        .I2(s0_axi_wstrb[1]),
        .I3(p_0_in[0]),
        .O(\slv_reg2[15]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h0080)) 
    \slv_reg2[23]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[1]),
        .I2(s0_axi_wstrb[2]),
        .I3(p_0_in[0]),
        .O(\slv_reg2[23]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h0080)) 
    \slv_reg2[31]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[1]),
        .I2(s0_axi_wstrb[3]),
        .I3(p_0_in[0]),
        .O(\slv_reg2[31]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h0080)) 
    \slv_reg2[7]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(p_0_in[1]),
        .I2(s0_axi_wstrb[0]),
        .I3(p_0_in[0]),
        .O(\slv_reg2[7]_i_1_n_0 ));
  FDRE \slv_reg2_reg[0] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[7]_i_1_n_0 ),
        .D(s0_axi_wdata[0]),
        .Q(slv_reg2[0]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[10] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[15]_i_1_n_0 ),
        .D(s0_axi_wdata[10]),
        .Q(slv_reg2[10]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[11] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[15]_i_1_n_0 ),
        .D(s0_axi_wdata[11]),
        .Q(slv_reg2[11]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[12] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[15]_i_1_n_0 ),
        .D(s0_axi_wdata[12]),
        .Q(slv_reg2[12]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[13] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[15]_i_1_n_0 ),
        .D(s0_axi_wdata[13]),
        .Q(slv_reg2[13]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[14] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[15]_i_1_n_0 ),
        .D(s0_axi_wdata[14]),
        .Q(slv_reg2[14]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[15] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[15]_i_1_n_0 ),
        .D(s0_axi_wdata[15]),
        .Q(slv_reg2[15]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[16] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[23]_i_1_n_0 ),
        .D(s0_axi_wdata[16]),
        .Q(slv_reg2[16]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[17] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[23]_i_1_n_0 ),
        .D(s0_axi_wdata[17]),
        .Q(slv_reg2[17]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[18] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[23]_i_1_n_0 ),
        .D(s0_axi_wdata[18]),
        .Q(slv_reg2[18]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[19] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[23]_i_1_n_0 ),
        .D(s0_axi_wdata[19]),
        .Q(slv_reg2[19]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[1] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[7]_i_1_n_0 ),
        .D(s0_axi_wdata[1]),
        .Q(slv_reg2[1]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[20] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[23]_i_1_n_0 ),
        .D(s0_axi_wdata[20]),
        .Q(slv_reg2[20]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[21] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[23]_i_1_n_0 ),
        .D(s0_axi_wdata[21]),
        .Q(slv_reg2[21]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[22] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[23]_i_1_n_0 ),
        .D(s0_axi_wdata[22]),
        .Q(slv_reg2[22]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[23] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[23]_i_1_n_0 ),
        .D(s0_axi_wdata[23]),
        .Q(slv_reg2[23]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[24] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[31]_i_1_n_0 ),
        .D(s0_axi_wdata[24]),
        .Q(slv_reg2[24]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[25] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[31]_i_1_n_0 ),
        .D(s0_axi_wdata[25]),
        .Q(slv_reg2[25]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[26] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[31]_i_1_n_0 ),
        .D(s0_axi_wdata[26]),
        .Q(slv_reg2[26]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[27] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[31]_i_1_n_0 ),
        .D(s0_axi_wdata[27]),
        .Q(slv_reg2[27]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[28] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[31]_i_1_n_0 ),
        .D(s0_axi_wdata[28]),
        .Q(slv_reg2[28]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[29] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[31]_i_1_n_0 ),
        .D(s0_axi_wdata[29]),
        .Q(slv_reg2[29]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[2] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[7]_i_1_n_0 ),
        .D(s0_axi_wdata[2]),
        .Q(slv_reg2[2]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[30] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[31]_i_1_n_0 ),
        .D(s0_axi_wdata[30]),
        .Q(slv_reg2[30]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[31] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[31]_i_1_n_0 ),
        .D(s0_axi_wdata[31]),
        .Q(slv_reg2[31]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[3] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[7]_i_1_n_0 ),
        .D(s0_axi_wdata[3]),
        .Q(slv_reg2[3]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[4] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[7]_i_1_n_0 ),
        .D(s0_axi_wdata[4]),
        .Q(slv_reg2[4]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[5] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[7]_i_1_n_0 ),
        .D(s0_axi_wdata[5]),
        .Q(slv_reg2[5]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[6] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[7]_i_1_n_0 ),
        .D(s0_axi_wdata[6]),
        .Q(slv_reg2[6]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[7] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[7]_i_1_n_0 ),
        .D(s0_axi_wdata[7]),
        .Q(slv_reg2[7]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[8] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[15]_i_1_n_0 ),
        .D(s0_axi_wdata[8]),
        .Q(slv_reg2[8]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg2_reg[9] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg2[15]_i_1_n_0 ),
        .D(s0_axi_wdata[9]),
        .Q(slv_reg2[9]),
        .R(u_breath_led_n_0));
  LUT4 #(
    .INIT(16'h8000)) 
    \slv_reg3[15]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(s0_axi_wstrb[1]),
        .I2(p_0_in[0]),
        .I3(p_0_in[1]),
        .O(\slv_reg3[15]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h8000)) 
    \slv_reg3[23]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(s0_axi_wstrb[2]),
        .I2(p_0_in[0]),
        .I3(p_0_in[1]),
        .O(\slv_reg3[23]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h8000)) 
    \slv_reg3[31]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(s0_axi_wstrb[3]),
        .I2(p_0_in[0]),
        .I3(p_0_in[1]),
        .O(\slv_reg3[31]_i_1_n_0 ));
  LUT4 #(
    .INIT(16'h8000)) 
    \slv_reg3[7]_i_1 
       (.I0(slv_reg_wren__0),
        .I1(s0_axi_wstrb[0]),
        .I2(p_0_in[0]),
        .I3(p_0_in[1]),
        .O(\slv_reg3[7]_i_1_n_0 ));
  FDRE \slv_reg3_reg[0] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[7]_i_1_n_0 ),
        .D(s0_axi_wdata[0]),
        .Q(slv_reg3[0]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[10] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[15]_i_1_n_0 ),
        .D(s0_axi_wdata[10]),
        .Q(slv_reg3[10]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[11] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[15]_i_1_n_0 ),
        .D(s0_axi_wdata[11]),
        .Q(slv_reg3[11]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[12] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[15]_i_1_n_0 ),
        .D(s0_axi_wdata[12]),
        .Q(slv_reg3[12]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[13] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[15]_i_1_n_0 ),
        .D(s0_axi_wdata[13]),
        .Q(slv_reg3[13]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[14] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[15]_i_1_n_0 ),
        .D(s0_axi_wdata[14]),
        .Q(slv_reg3[14]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[15] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[15]_i_1_n_0 ),
        .D(s0_axi_wdata[15]),
        .Q(slv_reg3[15]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[16] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[23]_i_1_n_0 ),
        .D(s0_axi_wdata[16]),
        .Q(slv_reg3[16]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[17] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[23]_i_1_n_0 ),
        .D(s0_axi_wdata[17]),
        .Q(slv_reg3[17]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[18] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[23]_i_1_n_0 ),
        .D(s0_axi_wdata[18]),
        .Q(slv_reg3[18]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[19] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[23]_i_1_n_0 ),
        .D(s0_axi_wdata[19]),
        .Q(slv_reg3[19]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[1] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[7]_i_1_n_0 ),
        .D(s0_axi_wdata[1]),
        .Q(slv_reg3[1]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[20] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[23]_i_1_n_0 ),
        .D(s0_axi_wdata[20]),
        .Q(slv_reg3[20]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[21] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[23]_i_1_n_0 ),
        .D(s0_axi_wdata[21]),
        .Q(slv_reg3[21]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[22] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[23]_i_1_n_0 ),
        .D(s0_axi_wdata[22]),
        .Q(slv_reg3[22]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[23] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[23]_i_1_n_0 ),
        .D(s0_axi_wdata[23]),
        .Q(slv_reg3[23]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[24] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[31]_i_1_n_0 ),
        .D(s0_axi_wdata[24]),
        .Q(slv_reg3[24]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[25] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[31]_i_1_n_0 ),
        .D(s0_axi_wdata[25]),
        .Q(slv_reg3[25]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[26] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[31]_i_1_n_0 ),
        .D(s0_axi_wdata[26]),
        .Q(slv_reg3[26]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[27] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[31]_i_1_n_0 ),
        .D(s0_axi_wdata[27]),
        .Q(slv_reg3[27]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[28] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[31]_i_1_n_0 ),
        .D(s0_axi_wdata[28]),
        .Q(slv_reg3[28]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[29] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[31]_i_1_n_0 ),
        .D(s0_axi_wdata[29]),
        .Q(slv_reg3[29]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[2] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[7]_i_1_n_0 ),
        .D(s0_axi_wdata[2]),
        .Q(slv_reg3[2]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[30] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[31]_i_1_n_0 ),
        .D(s0_axi_wdata[30]),
        .Q(slv_reg3[30]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[31] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[31]_i_1_n_0 ),
        .D(s0_axi_wdata[31]),
        .Q(slv_reg3[31]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[3] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[7]_i_1_n_0 ),
        .D(s0_axi_wdata[3]),
        .Q(slv_reg3[3]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[4] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[7]_i_1_n_0 ),
        .D(s0_axi_wdata[4]),
        .Q(slv_reg3[4]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[5] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[7]_i_1_n_0 ),
        .D(s0_axi_wdata[5]),
        .Q(slv_reg3[5]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[6] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[7]_i_1_n_0 ),
        .D(s0_axi_wdata[6]),
        .Q(slv_reg3[6]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[7] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[7]_i_1_n_0 ),
        .D(s0_axi_wdata[7]),
        .Q(slv_reg3[7]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[8] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[15]_i_1_n_0 ),
        .D(s0_axi_wdata[8]),
        .Q(slv_reg3[8]),
        .R(u_breath_led_n_0));
  FDRE \slv_reg3_reg[9] 
       (.C(s0_axi_aclk),
        .CE(\slv_reg3[15]_i_1_n_0 ),
        .D(s0_axi_wdata[9]),
        .Q(slv_reg3[9]),
        .R(u_breath_led_n_0));
  LUT3 #(
    .INIT(8'h20)) 
    slv_reg_rden
       (.I0(s0_axi_arvalid),
        .I1(s0_axi_rvalid),
        .I2(S_AXI_ARREADY),
        .O(slv_reg_rden__0));
  system_breath_led_ip_0_0_breath_led u_breath_led
       (.Q({slv_reg1,\slv_reg1_reg_n_0_[9] ,\slv_reg1_reg_n_0_[8] ,\slv_reg1_reg_n_0_[7] ,\slv_reg1_reg_n_0_[6] ,\slv_reg1_reg_n_0_[5] ,\slv_reg1_reg_n_0_[4] ,\slv_reg1_reg_n_0_[3] ,\slv_reg1_reg_n_0_[2] ,\slv_reg1_reg_n_0_[1] ,\slv_reg1_reg_n_0_[0] }),
        .led(led),
        .led_0(slv_reg0),
        .s0_axi_aclk(s0_axi_aclk),
        .s0_axi_aresetn(s0_axi_aresetn),
        .s0_axi_aresetn_0(u_breath_led_n_0));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;
    parameter GRES_WIDTH = 10000;
    parameter GRES_START = 10000;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    wire GRESTORE;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;
    reg GRESTORE_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;
    assign (strong1, weak0) GRESTORE = GRESTORE_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

    initial begin 
	GRESTORE_int = 1'b0;
	#(GRES_START);
	GRESTORE_int = 1'b1;
	#(GRES_WIDTH);
	GRESTORE_int = 1'b0;
    end

endmodule
`endif
