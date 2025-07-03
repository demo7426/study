// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.2 (win64) Build 3064766 Wed Nov 18 09:12:45 MST 2020
// Date        : Thu Jul  3 09:41:20 2025
// Host        : DESKTOP-D3LRDNP running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               d:/Zynq/vitis/ps_pl_bram/ps_pl_bram.gen/sources_1/bd/system/ip/system_blk_mem_gen_0_0/system_blk_mem_gen_0_0_sim_netlist.v
// Design      : system_blk_mem_gen_0_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7z020clg400-2
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "system_blk_mem_gen_0_0,blk_mem_gen_v8_4_4,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* x_core_info = "blk_mem_gen_v8_4_4,Vivado 2020.2" *) 
(* NotValidForBitStream *)
module system_blk_mem_gen_0_0
   (clka,
    rsta,
    ena,
    wea,
    addra,
    dina,
    douta,
    clkb,
    rstb,
    enb,
    web,
    addrb,
    dinb,
    doutb);
  (* x_interface_info = "xilinx.com:interface:bram:1.0 BRAM_PORTA CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME BRAM_PORTA, MEM_SIZE 8192, MEM_WIDTH 32, MEM_ECC NONE, MASTER_TYPE BRAM_CTRL, READ_WRITE_MODE READ_WRITE, READ_LATENCY 1" *) input clka;
  (* x_interface_info = "xilinx.com:interface:bram:1.0 BRAM_PORTA RST" *) input rsta;
  (* x_interface_info = "xilinx.com:interface:bram:1.0 BRAM_PORTA EN" *) input ena;
  (* x_interface_info = "xilinx.com:interface:bram:1.0 BRAM_PORTA WE" *) input [3:0]wea;
  (* x_interface_info = "xilinx.com:interface:bram:1.0 BRAM_PORTA ADDR" *) input [31:0]addra;
  (* x_interface_info = "xilinx.com:interface:bram:1.0 BRAM_PORTA DIN" *) input [31:0]dina;
  (* x_interface_info = "xilinx.com:interface:bram:1.0 BRAM_PORTA DOUT" *) output [31:0]douta;
  (* x_interface_info = "xilinx.com:interface:bram:1.0 BRAM_PORTB CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME BRAM_PORTB, MEM_SIZE 8192, MEM_WIDTH 32, MEM_ECC NONE, MASTER_TYPE BRAM_CTRL, READ_WRITE_MODE READ_WRITE, READ_LATENCY 1" *) input clkb;
  (* x_interface_info = "xilinx.com:interface:bram:1.0 BRAM_PORTB RST" *) input rstb;
  (* x_interface_info = "xilinx.com:interface:bram:1.0 BRAM_PORTB EN" *) input enb;
  (* x_interface_info = "xilinx.com:interface:bram:1.0 BRAM_PORTB WE" *) input [3:0]web;
  (* x_interface_info = "xilinx.com:interface:bram:1.0 BRAM_PORTB ADDR" *) input [31:0]addrb;
  (* x_interface_info = "xilinx.com:interface:bram:1.0 BRAM_PORTB DIN" *) input [31:0]dinb;
  (* x_interface_info = "xilinx.com:interface:bram:1.0 BRAM_PORTB DOUT" *) output [31:0]doutb;

  wire [31:0]addra;
  wire [31:0]addrb;
  wire clka;
  wire clkb;
  wire [31:0]dina;
  wire [31:0]dinb;
  wire [31:0]douta;
  wire [31:0]doutb;
  wire ena;
  wire enb;
  wire rsta;
  wire rstb;
  wire [3:0]wea;
  wire [3:0]web;
  wire NLW_U0_dbiterr_UNCONNECTED;
  wire NLW_U0_rsta_busy_UNCONNECTED;
  wire NLW_U0_rstb_busy_UNCONNECTED;
  wire NLW_U0_s_axi_arready_UNCONNECTED;
  wire NLW_U0_s_axi_awready_UNCONNECTED;
  wire NLW_U0_s_axi_bvalid_UNCONNECTED;
  wire NLW_U0_s_axi_dbiterr_UNCONNECTED;
  wire NLW_U0_s_axi_rlast_UNCONNECTED;
  wire NLW_U0_s_axi_rvalid_UNCONNECTED;
  wire NLW_U0_s_axi_sbiterr_UNCONNECTED;
  wire NLW_U0_s_axi_wready_UNCONNECTED;
  wire NLW_U0_sbiterr_UNCONNECTED;
  wire [31:0]NLW_U0_rdaddrecc_UNCONNECTED;
  wire [3:0]NLW_U0_s_axi_bid_UNCONNECTED;
  wire [1:0]NLW_U0_s_axi_bresp_UNCONNECTED;
  wire [31:0]NLW_U0_s_axi_rdaddrecc_UNCONNECTED;
  wire [31:0]NLW_U0_s_axi_rdata_UNCONNECTED;
  wire [3:0]NLW_U0_s_axi_rid_UNCONNECTED;
  wire [1:0]NLW_U0_s_axi_rresp_UNCONNECTED;

  (* C_ADDRA_WIDTH = "32" *) 
  (* C_ADDRB_WIDTH = "32" *) 
  (* C_ALGORITHM = "1" *) 
  (* C_AXI_ID_WIDTH = "4" *) 
  (* C_AXI_SLAVE_TYPE = "0" *) 
  (* C_AXI_TYPE = "1" *) 
  (* C_BYTE_SIZE = "8" *) 
  (* C_COMMON_CLK = "0" *) 
  (* C_COUNT_18K_BRAM = "0" *) 
  (* C_COUNT_36K_BRAM = "2" *) 
  (* C_CTRL_ECC_ALGO = "NONE" *) 
  (* C_DEFAULT_DATA = "0" *) 
  (* C_DISABLE_WARN_BHV_COLL = "0" *) 
  (* C_DISABLE_WARN_BHV_RANGE = "0" *) 
  (* C_ELABORATION_DIR = "./" *) 
  (* C_ENABLE_32BIT_ADDRESS = "1" *) 
  (* C_EN_DEEPSLEEP_PIN = "0" *) 
  (* C_EN_ECC_PIPE = "0" *) 
  (* C_EN_RDADDRA_CHG = "0" *) 
  (* C_EN_RDADDRB_CHG = "0" *) 
  (* C_EN_SAFETY_CKT = "0" *) 
  (* C_EN_SHUTDOWN_PIN = "0" *) 
  (* C_EN_SLEEP_PIN = "0" *) 
  (* C_EST_POWER_SUMMARY = "Estimated Power for IP     :     10.7492 mW" *) 
  (* C_FAMILY = "zynq" *) 
  (* C_HAS_AXI_ID = "0" *) 
  (* C_HAS_ENA = "1" *) 
  (* C_HAS_ENB = "1" *) 
  (* C_HAS_INJECTERR = "0" *) 
  (* C_HAS_MEM_OUTPUT_REGS_A = "0" *) 
  (* C_HAS_MEM_OUTPUT_REGS_B = "0" *) 
  (* C_HAS_MUX_OUTPUT_REGS_A = "0" *) 
  (* C_HAS_MUX_OUTPUT_REGS_B = "0" *) 
  (* C_HAS_REGCEA = "0" *) 
  (* C_HAS_REGCEB = "0" *) 
  (* C_HAS_RSTA = "1" *) 
  (* C_HAS_RSTB = "1" *) 
  (* C_HAS_SOFTECC_INPUT_REGS_A = "0" *) 
  (* C_HAS_SOFTECC_OUTPUT_REGS_B = "0" *) 
  (* C_INITA_VAL = "0" *) 
  (* C_INITB_VAL = "0" *) 
  (* C_INIT_FILE = "NONE" *) 
  (* C_INIT_FILE_NAME = "no_coe_file_loaded" *) 
  (* C_INTERFACE_TYPE = "0" *) 
  (* C_LOAD_INIT_FILE = "0" *) 
  (* C_MEM_TYPE = "2" *) 
  (* C_MUX_PIPELINE_STAGES = "0" *) 
  (* C_PRIM_TYPE = "1" *) 
  (* C_READ_DEPTH_A = "2048" *) 
  (* C_READ_DEPTH_B = "2048" *) 
  (* C_READ_LATENCY_A = "1" *) 
  (* C_READ_LATENCY_B = "1" *) 
  (* C_READ_WIDTH_A = "32" *) 
  (* C_READ_WIDTH_B = "32" *) 
  (* C_RSTRAM_A = "0" *) 
  (* C_RSTRAM_B = "0" *) 
  (* C_RST_PRIORITY_A = "CE" *) 
  (* C_RST_PRIORITY_B = "CE" *) 
  (* C_SIM_COLLISION_CHECK = "ALL" *) 
  (* C_USE_BRAM_BLOCK = "1" *) 
  (* C_USE_BYTE_WEA = "1" *) 
  (* C_USE_BYTE_WEB = "1" *) 
  (* C_USE_DEFAULT_DATA = "0" *) 
  (* C_USE_ECC = "0" *) 
  (* C_USE_SOFTECC = "0" *) 
  (* C_USE_URAM = "0" *) 
  (* C_WEA_WIDTH = "4" *) 
  (* C_WEB_WIDTH = "4" *) 
  (* C_WRITE_DEPTH_A = "2048" *) 
  (* C_WRITE_DEPTH_B = "2048" *) 
  (* C_WRITE_MODE_A = "WRITE_FIRST" *) 
  (* C_WRITE_MODE_B = "WRITE_FIRST" *) 
  (* C_WRITE_WIDTH_A = "32" *) 
  (* C_WRITE_WIDTH_B = "32" *) 
  (* C_XDEVICEFAMILY = "zynq" *) 
  (* downgradeipidentifiedwarnings = "yes" *) 
  (* is_du_within_envelope = "true" *) 
  system_blk_mem_gen_0_0_blk_mem_gen_v8_4_4 U0
       (.addra({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,addra[12:2],1'b0,1'b0}),
        .addrb({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,addrb[12:2],1'b0,1'b0}),
        .clka(clka),
        .clkb(clkb),
        .dbiterr(NLW_U0_dbiterr_UNCONNECTED),
        .deepsleep(1'b0),
        .dina(dina),
        .dinb(dinb),
        .douta(douta),
        .doutb(doutb),
        .eccpipece(1'b0),
        .ena(ena),
        .enb(enb),
        .injectdbiterr(1'b0),
        .injectsbiterr(1'b0),
        .rdaddrecc(NLW_U0_rdaddrecc_UNCONNECTED[31:0]),
        .regcea(1'b0),
        .regceb(1'b0),
        .rsta(rsta),
        .rsta_busy(NLW_U0_rsta_busy_UNCONNECTED),
        .rstb(rstb),
        .rstb_busy(NLW_U0_rstb_busy_UNCONNECTED),
        .s_aclk(1'b0),
        .s_aresetn(1'b0),
        .s_axi_araddr({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .s_axi_arburst({1'b0,1'b0}),
        .s_axi_arid({1'b0,1'b0,1'b0,1'b0}),
        .s_axi_arlen({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .s_axi_arready(NLW_U0_s_axi_arready_UNCONNECTED),
        .s_axi_arsize({1'b0,1'b0,1'b0}),
        .s_axi_arvalid(1'b0),
        .s_axi_awaddr({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .s_axi_awburst({1'b0,1'b0}),
        .s_axi_awid({1'b0,1'b0,1'b0,1'b0}),
        .s_axi_awlen({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .s_axi_awready(NLW_U0_s_axi_awready_UNCONNECTED),
        .s_axi_awsize({1'b0,1'b0,1'b0}),
        .s_axi_awvalid(1'b0),
        .s_axi_bid(NLW_U0_s_axi_bid_UNCONNECTED[3:0]),
        .s_axi_bready(1'b0),
        .s_axi_bresp(NLW_U0_s_axi_bresp_UNCONNECTED[1:0]),
        .s_axi_bvalid(NLW_U0_s_axi_bvalid_UNCONNECTED),
        .s_axi_dbiterr(NLW_U0_s_axi_dbiterr_UNCONNECTED),
        .s_axi_injectdbiterr(1'b0),
        .s_axi_injectsbiterr(1'b0),
        .s_axi_rdaddrecc(NLW_U0_s_axi_rdaddrecc_UNCONNECTED[31:0]),
        .s_axi_rdata(NLW_U0_s_axi_rdata_UNCONNECTED[31:0]),
        .s_axi_rid(NLW_U0_s_axi_rid_UNCONNECTED[3:0]),
        .s_axi_rlast(NLW_U0_s_axi_rlast_UNCONNECTED),
        .s_axi_rready(1'b0),
        .s_axi_rresp(NLW_U0_s_axi_rresp_UNCONNECTED[1:0]),
        .s_axi_rvalid(NLW_U0_s_axi_rvalid_UNCONNECTED),
        .s_axi_sbiterr(NLW_U0_s_axi_sbiterr_UNCONNECTED),
        .s_axi_wdata({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .s_axi_wlast(1'b0),
        .s_axi_wready(NLW_U0_s_axi_wready_UNCONNECTED),
        .s_axi_wstrb({1'b0,1'b0,1'b0,1'b0}),
        .s_axi_wvalid(1'b0),
        .sbiterr(NLW_U0_sbiterr_UNCONNECTED),
        .shutdown(1'b0),
        .sleep(1'b0),
        .wea(wea),
        .web(web));
endmodule
`pragma protect begin_protected
`pragma protect version = 1
`pragma protect encrypt_agent = "XILINX"
`pragma protect encrypt_agent_info = "Xilinx Encryption Tool 2020.2"
`pragma protect key_keyowner="Cadence Design Systems.", key_keyname="cds_rsa_key", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=64)
`pragma protect key_block
QGLtnqZzRetDH6gCWT4Js6wuLlZfrNx/VJp3sfR2NF+cxypO5AxN0oDKLJJtmdrtE/ueNDg+Qf7Z
TqBNRojORA==

`pragma protect key_keyowner="Synopsys", key_keyname="SNPS-VCS-RSA-2", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=128)
`pragma protect key_block
B6Ger3hRvfjHkaJ+W8639Kl3TzC9TogLuklOXEiMNdc4Im+DjEUzxb3DKlzu0VW3zxZqjJ3+wsW/
LnRmPCESi5Y9eRJaLFXg79EMfoj4X+nTdHAP6yCfltBADKegZ12gpnB/8ey5yn2KA74LUtPC7jna
iyjqSfsWLGnz6UdXzwk=

`pragma protect key_keyowner="Aldec", key_keyname="ALDEC15_001", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
BX+DxgMPRyZbYojCUR9Sk8Lq+3ZigBz4yMFHQkmurfdfDzyTPJCE827eGiPyTenK1QPVhEtf9g06
0BFXq/0COPuU1BWJwdkz1c4dE6/exDwhvEh+hPx3vRY6z8fDEf6aGVIXrHDvrmddehe7yMSIpo+k
aXHR06EEdfHCFY4TggYwhcJVXjkE+ApsVuyfmEfPmYjo8hCWyQyBsUWIOY03q1+MvUjjsmTwgs9g
fh5MY9ToaLfoJxPKdCpsqrBX4LJ+VDGFlAqIcqHTE2jCmPiToZAFXB7fzf1wDjFCBlJyFVDBGi0i
m+CouLSb7X1mvVhdDZgNrZDJMV688Bu3o54vew==

`pragma protect key_keyowner="ATRENTA", key_keyname="ATR-SG-2015-RSA-3", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
DaIU/Ddc8USbZ2mURzujJDWDH1JbHl5tFVOOQ2aVaUPIA71yyE38OXVLEtF8rNmujYH30nEeQ+FV
LVJ16aaHw+iiuaqorTM3K5KLohVlN+WlcEtSXHuPNHjw8ddqtzpaX7pH1zqZH+YmfCL5oaNLqDH4
rkBnUl0/Gm/hzSwKjYhXGQFYQ+gGP99OjXakzrAqZzp/Iq4gt+Z5902/JV9thd/isHQImJ0QyK8M
EKM579iPAfXGes2mbiNYHcvDmSPYmW1zlhOE++N1EKeea7j/msnKeyhlC+hGE4Xfn4TVvqgQexCT
rp/wS/MosY6WH1aKFQlFH2hEppA7KXUaQlvG+w==

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-VELOCE-RSA", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=128)
`pragma protect key_block
XmWoAt4X8hrCJ5yTyug4ajJW5UhfkLNibzjihWzZ4Cr9hQSvWZoTc8rjGsLPbz6Le+/9iI5KxecS
eR0wiAO+G2IkwhZgVBeZdKoFnlnTVAyLjk9wMAFXNyJZM6b1NDbfXlPcUsC6JePvPlwwdWknkSsC
r3KvgkWAS+O3xvRmaNw=

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-VERIF-SIM-RSA-2", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
Hw3Y+rShKrXiUViyNU1/O2qv6TgheLHBnFMj1i9MUGrHYqh9pLfLYUgWR7S2vj4jv4S+Ks0BpP4p
dKEqVAFmTCfQNEUHaVcFPkOHgig6L4mhLY6HUUKJoRgiQepgLi/W3V+ZZPQSQFkB3CU4MsJzhXvR
yLcpDriZy8cnAHD87Zi5DrNGBzj3kigJeM0du6lCQbxtF5aEdoaNP+YTnIFtcqYhoYnswQlYt0sV
HKgFA8VzqzL5WYnpH7+1IKmFkJBHkyqHCa9wPK0qCKnxkuDj70YzPVqQ+cocdKU+/gNdpCOdZlci
F2HTxrgfrXndJru3TiDqu4UavqAe0MNuFp3t0w==

`pragma protect key_keyowner="Real Intent", key_keyname="RI-RSA-KEY-1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
XPVggoWL6aXz+MpODTOZhEUQDa0vfEnUDaYeEHXm2vGyqKJujN2c/FFAFBeBYdJATLsIsQ+BqoPc
pBbcFYXDBfOtFIW2dH6Y1OoD65KyJ/hAq8coa21kFgq4hFat5vzZ2iIfkCpTUr4vDZO7Xne8cZO9
WsHffoTCt5rS59wWm2b8I5R8Eh2TUbQg3RCyrcnD66cvcEnlXe1CNMQ4/loVJpA4IBinBf820Wjc
vw2fZbGI0jXC+ACSHOviH63Xwmn+aRV5Ppkup7IYoon/ieKapRQeASu3TTY37xSBXiInSdtMTzJ6
+4GfO4eSHVriCk/sWbuTBzfRzoSShrnHjzz5LA==

`pragma protect key_keyowner="Xilinx", key_keyname="xilinxt_2020_08", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
L78XuiswVcgO2gtebzL7SA9BC/jJGAM0v6S9pzmyqL+QYzRneiYeGyDmsW33jEVVSTuNjTXkBLY7
yTOKQruatwe4V0OLi6174saSAmPgerSV1GyLP7KhmusLV/N61avC9TPam+tekhKeE0tds4EnJ3et
4JdLh+SE4Z4pcuqCjB5MFneIYKKWDx7siU6oesAQtoSJOesfMchX63MhOjOHFP/ch+1gHv3T45hg
IGF7V7TrdREVE4f9631tlVJ1o2Dypsmo/76Itz5WCGlTMjAnWXN8IXxKN+PZ3dyt1wjrZm2P/td+
xiGszFnSLrRvw/HferwtSmRx8q0fiHZ88roGTw==

`pragma protect key_keyowner="Metrics Technologies Inc.", key_keyname="DSim", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
kDX5kq2QEe25429T6vQqBCFvV1McKTJRYfK99ymVNK2GGvGLXSzgwJHwB2fj9rM0wme3zYYY0vQR
x+9F4L7KLlOVY6qY3LB59uDzyXBI3mMZaS905HXHJkdZHWtQWpfHhl27LqL+8FSluaD6F+KFfYOV
CwIOVuCIp/XjxFXpNBik7YiPt4kHOlDA97IXNLnYUn/g1csGqeNWce4UTne50ggWvLYGbTFGmTjT
N67TpUiGRVRCSv8Tax72GWFIMFZk3Tlp68ZUSQEybZMWX1U9XdMdtxfvNGhf8mi5jQJ2SupSzKu4
T/+53IN9T8aLePAiGBKKG1ZBj4y1ZyYA7XYvjw==

`pragma protect data_method = "AES128-CBC"
`pragma protect encoding = (enctype = "BASE64", line_length = 76, bytes = 52288)
`pragma protect data_block
+YNxZ6tM+tE7steYv5xFVGIqnb0rPnNTgfCpa5DPIikX9bZCu9of8uMsWCXvMp6dfEYNDin1hluK
tmb0IkaWAl0UVYl3MVbXhJihxusibb+bRS8WduQFyDcaCtWLAowhCkdyC0+CxVUX70PZ855jNljc
yT54TON4N8/x+DuYQFkOxDewCCMLFn40tLFqU3x7fP5JV67RMrwhffGgGuCDQIEln9QsEYEWwIa8
/V8/rVxu8Jw2IM3nJUafm3r5qNZOTm/EdT8UOKSyCiLlldknY3Sj5Uf3ik3AHtZ3wky62qFUI837
Gux+mRMx1TaeZwXDx8XG5xk30THeIdv//naZrejtF7pYftA1aEBmeFfNWw6UT/x+NhIJvWsA0eD+
syC2BEmgJX1Q80DHQY2duZYYvu0LdAVEoR37ZcUtQlpwQ1LH/2xUF1U8X992TdyQ2+CXd47YfMzv
bZ9IjEavA9CIwuJABh/Ql1E6iemlwjmrE7kevswUacYphPcpNW9cXX3V1u8Jb2eZv3AUgdA3tyXd
oZjv3hB7rS/mq0YoWT3Tq6ZAiGy6EN/eV+uJfTA0vD0lSPwoO74uEQIHIkSsy3lx1svEutwfvMLG
1vhTpnc1ONzRrcGZ6TBKt449QcdRAy+XK0z+DYvCUaPcMWFpXHyZvKWWaknkcz+hEUr9oIahzPLG
+dvza1Nzynzd4dyDSn6CRz4gOwz/sxZ6eczP2YlrZFF08/K2p2h5EM6Qvk4Fx5mCqnRUWPM77UC2
3SZ/FybqkmfJrU3iKxXMbm8f3pWH/dtVxN8s7LDi3W39c30IXRJhb+D1V2S/7wSRQKCdI9c/Rwfq
W8nRg+ShCZZh7iOWiQ4Xj5rN3qSx7COkujf949Ot8QWFDEQK2W2L4wUnDfW1dQn8ygC5yRXbYjCq
6+q8o3a6oR7W8X7juCHdnClghwpf2kL3Nyr5odxoexVmm6YzN20lMtDFYBdW9uw/JfCNQYU88Uwm
venH5/1h1Mbso2f35H7R8AXzVu7CS7jhbm/6eYtK/KskEc3FvsMxfUWtdQnQcpy07TQqu/gWauj8
JVmztuT/OsVxMNXG8Wj1hhgsHCA2EzFzJaH5FAzyZVlCcg4hTuYHrIQQ25ypo9omZpGeD3wiuZ7K
N6VbPEHV70swk0L7xE4ZOI2MNReYaUXj0VnWTACmO/VSbmnZrBy67GUVdQR42iaxDpl0KDGEKGfs
gVXB2Lv4OaOAf5PP2Tn42d8zBkmqHOv2n/6wwAFl17rGx83lfrgxO1KKj6nwWGiX+ASU0SH+P6eM
oHNO0K+qhFYY0v+8nE2Dp/2EJbwfT01eJ5+S4hfxgCkfIKj0ML3t8arC+n6fJioxtDCFOMsqa4F6
iEb3S3sSvqXUbZLqYFGtMR4k19rSB3ldnjQqX/pPn4u7ezYrIaBJmMFLaVEuQuAAT3NMISbztuAa
lmo5TlQNntqzTH2vL6Q8I5tHDxhGwRJB/wc5C3JHIichSrxRVqf/zJN3bMFifJ+UqSJW51sVIDQJ
FFeMhFKV8v4fTyYeqAXl9l9GjqOV2tVrYyuco85VWXJWBfqhkfQdiz40RbyZgRcnmhsW3ZXS+V33
a3iPA3WLup/+VKI0vCydWlBF5uug+eG0NFk5Dq98ICqpPvfI1vPcytjo11Y8BTcI1BTCMaHeJQLk
LjOouFYkQcp0X5LOLh5nVNeH98Nm6h/S5s2EwlDNTItjLtsnefobpo3gzOZp+xadJEDJbaF0fAQS
MFreMWm9zHRc9fn1EMG6dnwUNJtaoyw82UXRxKxY/J2LbIXcsGjxsFTmB0QznZPnSb07lcxHCho4
N7kaUPR8XRY5R+c/GxO78D/cE4vjbD7ymA0RypWbmZBH3pOOUdwVbPFP8FQaO1lVLPWtGvxNC0xj
7/Nbq+i7GuZn4QoYXM4+CJEhUOaoZ63Po+K9ClblWipU0m5yzyqltV0kLjLeeSnbqaFyZNzwQuzo
m+Hh8+shsmcZoj5vdLqgGx3CkcTdXBZah0WdRQ4Z6lMawU+n2NcqCl9slHQl3ze0/tyy2/5moE3H
1L2vY806WSO86sEJRFWG1LTFiOSWryBtTPuJ/6VboGasiMjtxHTycNQw0EedsmXYnyRuhNa13Re3
/cEHfG4sB3Qcb4VFwOBmVQ+bXV5Orsmaku8WeVaOXg8ZXpLOUAcz/j0GBGz/ZI0mQmMVlcUrbKjF
OJjMlIO9PClkaJU4omhVPAE8N4O6tP61IYnKORzmfWR9Nl/MfUbyunCYKk8Q7wt6RLvkje9aIfv3
E935Louh/+McLEHTF8B7psl7EFQqP8b22C+KqFWDKC+pfD3KhmvovmMMpZz2ogzRWYciC2QHT4Ox
N0vLXF0R7qpa84SRTz1mkHG83Is6R73d0rfhA3F41LBdSCFMdfLHwfxYEGgn5xfiraZmmCqX4X7S
uvYFVXLudzQbLWihxTsP05gmD4J/904abW0H1pIywfF+q0jHzhKu4xnopGOHsTXd9aYqW+MTIlia
oV/oK4vnOI9vRnRi8UbkPynFgmHKyFcdpvqsIetmVm5o9MSQpMdKwNUOu3RBgGAMXkuWq30BQzG/
Z+tMngHI3CerdZCPaEEqnmMdHIMzMixYxqIbH8McEf8bOfeFySod+P4qttw1krlWCeT09mHVJY8M
S0byghiagSP1eeyDiQOt1A6n+ooYAoiuWgA2koTcK3ptN0CYHrIFCP3RX7vmA8PcWBqW0mzhvdiB
nEXBwuwpW0vyElCjwrIZy4EdoXVQRZvyjjRYOFLum7yzxwYJX/WDdEhTkChtWd2MhXc3bdkhin2j
APh2T+5vyGX7RIsrtRc+OCFjTVfm806H0gWKsA+KwjwipaqdSNhq9neK5W6h+jB8v9hztDW7Tf5t
VKfX08xvx/SYUcMHXyuqf6CwLBa2qMtOhrlXpzIozCVMKWqgWXE43LHpwsOlXpwD0rONCR5BlNi/
8hFidUMUmu5LkSQkuDUEJJGZJ4QEStEWCU1azco3Urf+Q5thEXDPcmWUJRFTSmSNsOeuAW1E+Qyd
fC2iB1RuL7J/SF3Sqo3YR/L6U0IRU0/aBORST6gE5QIs0Jsbue6+8EDV+a2MDso4+I3Lgk1278So
G9GVfzg47mBu8LDTL6758PDMpxtJyTY1ycuDMNx6f4bYs8n2jMlAo56tpIHCqumdlVVGsbV7YOGt
tOH48wpuvBA+zGxiQx+v4P+SSPK2OD8gmM4Ztp/u1gmPiDKtdPz73Q5QJ+wj+XO7BbF2GJ6O9Z9r
3iL9QXtg9j42M/t7XrDcyh2J8FMLGIa0nygyEkc2SsJpE/TfrrLlxNWHT6B30gZzLJ5Fq7uiuP3y
FcZv8haJXrky1S3luLc1xNGO70J/etHR8uCYJcQKZVYzFDFjLlnUdY31wO5lC8E3CPXX2yPXmf3Y
UZkuVDOuwe2FM/CSUWU6/EWirhrQDrHib50ytXZ4mdyA+9Ly+QZft2kho2Ijas1qb0N4RNy8JzDk
op4lk3fUZDdHa/FrdAsAx1a2I0WXRASRRPi3+V4/WNifqqw0b9M2y30XMaOJeK+Nytll9WHxhx/F
vpYE+nS/RpQ4XeUn0bxhNx2SUkN1QZRF0TBxVKOuQrom3tbko1NVqTLqWL7Vset1Hybs3wVFOyHf
bF14vlJ80LUR3nsJJlcaTRPy51SGvOzHNRyFiJSlUDUqIgB6z1SUWopqZCRJ0Ih+6HXpZDa5Qa+7
sFNiyVHlGcHS2LDK1v4gkdsK0cFvnExznTJuQbnRGLVKUUiMoWdkyZBHuSQaZVOf9n3TUAnsmtnM
/HHQbDOW7tBcA0tSnMy+nGXUZsPpynB/fk4XnDp/dnnBQP1tFDBy2Fm0+8JeogUWN6XojENIMCoy
J7g67ioHDxzxu4MRyfswbS6AO8wzeQ2OOan+0tihsVahIXaTA5HIR76wWfLmb9aEpZXpcNDbEQDu
3PEu2Wl0pVkKhutMGUxL/hGL9N+lOkmoa6vmYp+Jqq8eRuzfMVGRQ2rhYz3WWoVbzZvEwgKEBSML
YfFtHA66I7//vUHvYDnn8c8quvD1JPY0FA+XGzRKICRU75FENMXzTBXlp1q0UkT12QNFZhNIxNEf
QkyZhRsYQQ7rf7D1PPHJmTRToZgPuJUneL+n7bqTqdZXlP9YIiTpdfD7oo5zo6KggfTTTZG/2iFT
dgdiUyS+TpB70w2PAV/Cg7YSfSNEJodPG8xkG7mLI2Eni4I5JJOzbQB8TU1io4oUQObO6rkG45y7
gm+3RMtcuuqCH7YCGlmykkZSAzUQF7dhpVg3K1mJyozoFq2KB2fzV8P9970HeGnWZ6nN60gKSyHi
w2oGIFueKoyT9j/YOBSg524FlDDJI7t6oVFCNZxXp89xRJe43UPUGYKbtRIlmULhfJ5EpB5eUT7z
HwNkHSJFCuXT40meUvptJ3D/gNaZJRxEszYetoaYC/mkInNaHFZquD0D8f8IHHdSqJhAGqkF62Zx
WRrst5YIDYgIGrFHsNw18y1TA5qnPUF34cNlWSbCX0tNnuqrxJgf4lec4xAXxzGfW6ehqXao2KAo
uZvDDI+1F9uoJcSe3Gdxzo4VcYaAAAlVe95FNlDk1dzxRUjjcFUiTW8IPB37O1LdOwoOva61/FsH
YdBjH4CxQDFf4H4Geukv4XFPd3rd4HmuJW/c6iWfKiVtKj++Pwxt94Q746gcqb4pMQYEUWZipWfT
F034xEFSwBDWCoupNNP9H0jkzKyciFtiGScHZf0SFoDBRrRCAdd1JfcB0hVZaHg6i5EleRH7ndnL
0T02Ye0dk9ZfdNgcVako64BOoC4q7AKCQx7F+QR0RDde4bFXxQnNW4OsVhrALDkSsUagJJ85Rn+e
iy1/4bsy570Q17jYlHHktb5aUr5mYSfYjHNWwsXorIHiwiWc6T7lJfI7qQGogwiNGXVoJ9H03ZZD
d1jkAqA20pCPcusZkY6tx/I4G8/xBn7tJKeuGuQzUDpr3g8DIK3/8oFkLdpFaHVGInWHuoxmBc50
9drvbDZ5fHIKG9uAMQNQaKeKb/g39p7u3fk52ZSZ/PcSN5CuVLEPMXGhQF7jL1yhtBGkN6OXAvHM
Koq4HHEnuWGEFzag8FEYLhQMhaCy1wc3o34Hj3wot6nUtU9xmx3pezd5Jc20FAWDKBKbMvpgSklk
6irzqU9TFo/oFn9KyC8Rovh85t66pkK9aRxHxracaP2X+EQxWdwu4H8QAz8kh3b+khUsnZx+0M/s
+wDzt8uQ7z0C7UrQxBntEWDtP+oHsb/W8TYCER+pQD0++X95jhbTXBR8rsNubSVvMMfzxeTuwWq7
TJWkVg4Ow05w3GuAlz1fUIFkNuypvtFO+xegeqxZwagoyskT6/ror21AfPmY6fkSG1SqujH4v9mm
XYdRItH+j6mkiW0c+p0/qnst/Jktd0GaULtC3JGXuHOES8X3/dlBsGvpJ4jOy7sNstPJKmJJwJY6
VX9494ItCB1vai+ZMRCzC2mx7nbGhD6VCUAcWm6epIqs49YuEvW0qoRqAdoFjkN9ZA5BEmw5vFrG
DRa3Lw5xk0lnlKSaxDqUZmNjvrddj/y1nQCf7rfeXbbMy1ot65cCv1QgkRXHX4i0j5mBNUwZqmWh
a731wl0Q7nQQJ8Z46CqCVfAXhbsowe4u5yYnq97PP6bznuQXG9t9k2b1m0Spb3ZQIUWxgZJ3BzYI
RM/gTcdp7EuNGuZNjaiJ2lOsrcCpfmpJNJm3R1Ci4XfyKEjwaElmsKZBD5VMMdDMSuEReApBtduE
FE6ZXknej7igK25OJV5XBMbS8zfuSzDcvkoKxPH288m31Rr0iGaOMCpuriVMq7x6ff1VMbbx6az4
FnQ+7Zu7yKjaakR+vznnV+NY6wueGrepVP8imFmBui1PHWdDznScTPlzbxWTDZpJroH0L2LLyS4w
dO4m3gqQ7E/HpJeXk/zpiCn7dFy/0jIaGvysBtonAXJLLneo6gGLZAEnNqTDNO48iWayM9iAF0Se
jb+/TMi3FIi0NuZzyEDbp+/SMkEeg+9fUCg0TEwCUWPD+3+3CWKd3qZs21WHR+y8HSml9RN1pA90
c39t4q0/5qKumSIR+m4OQrtJynOWNS0x6wYItNrLGJNh7aVf1snkDmzIbWn930Egt/wweRKBSXWk
uXsa5/HewP5CjR2o0jI+qwJWly91PLnHIP2rtKyyInz/UopWfbR9brfZnrX2vNgw7BphyQASCLxM
qRFNzMmLc0S+10IZ1dwJpjPi602t8TuAfn4E7fT+eJk3dcxjbiKbU8SHigCzsm9sMMM79SXQlee8
mivy6x+8FKSB4d7bTbJ40jfV62jBReHGUK4j2Qm0OZMUvLKVRiEmBZroHiCs0fyzUZqEewwm6OGl
+D8Ga2LxcZtqwSjrC5UjlaLekuU88jlPOrKNDA+KmZZpZwDhRYDMjCsy4M/V6zI58XDGuxsrM/iP
Y5LRMrrjdLDmv/J1I3hIlIDLasYSSbk64r/RFVVxToNa+8sa7bPCfHXp+l5qNHK3m8gI+4OiaWUb
bup3aWnF4TCvtmCP+mBt7DLNyCrpVAV8m0IGB+rxIa5zBHdQH1LLgPLp2JutiWeZhdADmhnv7rvR
Jsx9OGJLlbt66ocVYEhIbGbm9HMK0kewUBW3qdwk61ahgaHi/7ohhkV1ePF7asZyjVdT2T/96Xob
V4v3QViVQ+4xx+VcFl7/o7z+tJd6Vv6PJUwh+/ldRzf4M+iTAw9TRJUPsKu0WjNCn1q/K9ByPMn9
ypPYkgRt54sNgjzAYAXnK57XtBkx6FtYTF7PaPv/1Dw9IKkaFPM+xcR4Rl4rr8mJE1B7V+PZKomR
kN+PYI5CbqjufE5TioxYm3gBJNC8LeK1U6qt0NDX2kG84Oje9U8X038laMidY9JOJtFeUmMALLsa
rN/IBeAEKhAhN/TwqglKetFYbNqd8SN4iscjhu9bnYXpz80QuTh6xBTxNe9DsSfvEL5EaNKCskvS
3IKzTPeW0TtXJs2ezS4FxngeOikWnrfOZt1JAmkWvihnXbUlPKvUxOx9DO4jBYGlCoVH/V4yvCSR
clt7jmVGl1ZFp1vwWlljDc9ZC8HMZSGkgAdy2nKXkPD4F7Xj0sUd0xskCaljNQbG7ZmYDcSj+h3f
TQpDksjUiJMTRIvnQhiJUSmHeLzyCgh5E/HhiW8svSTc4zJ453Sj0nNKeNmxBiUf/Gmz3LIXAjj0
dIrOT/CPb5frqbyllV+RyWVEDiJXroK1CMxlqcehz4dQ98xLcr5he2UpmHnrrl/GzYn7s9nWaOop
nJ0D7x1yvDN5fj/fDRiRQUqMCRQAryujZLST3chDrtKU/AB/YJuOiwdc0LeIJX8XBLYI9O46szSG
VTcKsAQRIayQiJwpkqPe0ffQLqh0m0931kI0GtFT6NMA0PwRmeX01aMo3XVXJL95HhdfEPWOniJN
Pnn0hcAt9MxH1LLESCKSdsiBQOr4gmun2rfmcDAQaqujoEX/ePMSjnjKFKOxjGk3sO2b1Y8HqTet
Ar7yz5IBRyi0oEC9bbkGkgPkdctwDcVH8zwibi1JsHYNUk1lrd81l0AFThoAkTouyJueHe6lt4uA
EYCPzQ2qmtLB4Lp9FBraXNZBUHMUmk9JIb/xF4E1uoSgSp18ADwP9Awr3/+1iA3xK+rA+ON5hwO5
0MZj3vVSVUlrieb+hsrNXg4JFWlCAZCCXLgBmns1TkOOU5d2MhhTwYdHH9UHrSqqvw94QSRgtQZR
bHFa6gmHvVdFgRyCAqil34F01W1Q/U2bP0wFFwluBbVCy1JtJkMk83u3azmZ4zDniwbZHFqZJZ7m
QpT20ZIs/Rfx6Fnfx/Rg1jPHFwZ16DDlhOs2pbW53fSt+W5Bt9lohmjFLQ/OidRmKTorM6uvK8my
ZUmyLF2dy2yMpYrUCQYofcZ9AMyKsT3bIYh3Ztg2t6dnZABGJ6ogo69QbgDRFkxQ7tsOYB4nrxSR
QMvEUJOWj0+CY0E0+mXHXUKuTKVTuQCTaPnFAIzvTbpk9x/eT3fQLxv5DLqNwxuOTlQZ6WJ5v+EX
WO2S9eTUyHulT/jayjlv1OmOcKAdPTmotA+0h09Vtm2zjw5YgFSFotEmPfJTIqMTcMcu2dWzmsU+
9djWBGJGCC3dtb0LXMf/YtTc+lDBYF3EbRIVQXbtYw2bptxMXIxw6l9hU0cvhVDsSN06AsbwPcDp
/tTbF3IMiNgB4Hlmaww7DOmBRxrYxbL6lKQ1dfT7f4aubzBRYpl7E+XKLXDSVl/Rv96b/fLckJBn
iuXSZad5AHXbR7EHqPbBfqoRQeDZxV2CSfrInPeXeUh1HNxginiFl6m4xvZPGeVsZZ9k1FUSW3IM
nHLKdx4/6AN7b/TIrbDQqZEtx/jbZJHvyL/xryQX9ON6DF0s2K6BxoL7xTWuUjrslMVk/G3/3ODd
SrA8V1FRg4uxDqPZacoWgYznFfnQTScWPRf28AFAFzHxtrqrGhM2k+/RjtB58TOt7PEDEvwejjwA
sko+YRO3grcqMEXj9IDhDvfccVNBe1O0kh8usMlRFRuez0Qh7iV6o4IrVEzEeElWYHZFKB6vfreZ
cG46DSdVCKuJfKUqB1UYxAAGAg2ZxzRfZUrpH1MMjraIwRa7xDF3DNjhGBwHUscYzXl7i6DHa4N0
1UFpmuMv0n9huw3CeCoDMaXZd5X6pk+z9GlhOxkbdxPY5EeVJxhZ066npY6bwOuExncRDCDi4tqm
mPweYSZpmu0kk3JvzhqS0J457RwpfSo+iR5DgPrN3K5zZC1/uhQ58nOyuABguxNXSbmG0wImwNUT
4pSLS4+VOsiMYrB0SI6dFsWR0kJ7bfcMORjqflv5Qx68/DM/mFXCLJrJwXOsmQeevYt9dubUWK0q
5SbS5ZeuoaUUPLgvHBF62fLuix2WlQ7WziKeG9UYHVufQJ+tCOSa41exPO2XoMtVSApBZa7Nh5RI
U87smTdio2wWMiK3uo90J/69D7y+S1+Ecue4fttnU+rcrx1yPIicp6eJtIKoax2bJU8ou0ses1lO
5gp6vRjorgfvMfsBOK3shYpAYVsUYeMQed4kmWsUPexIO9rc8eIlw7hUhnJwKxgnHWR3JiTFPmIO
PG0h63vfDITfaGk7Pfjpgt6mnuB7PdLyKbx/pL7hUCfD3lqSbNwRv8GO0mMuNjn49Snpoi22hsG/
4lYut/eR012Je9BVVuz7u0VVmwj2EvktMT6DRldwKtZRkmPAWZ+aIhdamJTr27DynrlC3AF1N0ds
0AcFo/CkPObGVAM8+LiygfaGczFy3X+yr0pVb/9zZWkZqQ3+JQEAJNJo/vgxlymOrsxSgbHHkfpC
4jZz/9HD8HTMMykYTfirtAksZc3dHKJJQ+sKSF9ylpLURPjLHqJNcNXOnWl+OsslCxx8o7Q3wpsy
RUU9OGvLtWBdSLYI7f1UwlpRF6kiIAPLAeol+pMGBOORh5zMEghh/DuPiZZvjiOf2EPdW0LcUHzU
uJxg3/YvXkKlaQCqsXF9hokYTtAgUDxt2xmyqHoaDqqT0nGfUYEASt6JAEVDwHEjrU52n4f2B323
HjFLllzQAfuHhfbziOHrDYN2k2iVfxnQEOglMXi2uiud7houfYG8RHUxYkliVMN6umreHGB8cA74
CmWPYOEq/Bbj7rirlZRzpwt+jmppQe4JCfinyyTJiQ59Ak86DaBPJoKpZzhIeCdeOl0qkHkfqczM
Ix2r8z+m3skuymB22gICVsnnJZdyK7QzwIHJVw3jGyjr7WPQ+k7WwVhIDxR2Delt8NuQQrmcphFN
WMlwYSnp56pHULh9XlG0Brei/XMrYXWpSFvFh2vkidiBX4lrQwXY+s2H2pkwo663Rr8e32q3NFyn
oux++skuPVqAYvzlrh05d1bz43Iwzc8PgJF1Or/brollxCWQZy0DFY7/x1c+76Co9EJvYqpjcOz5
EXh1fDkMsKyIUaI+x2uMeJPVrI3qeQ2xN4bYC8a5NKgUx4l9ClSa/Qk8uLGIdIFxKHMRIJQJtpEu
fa4ToXvzt4HIqPR8oVtVNJ1sqkVLeEP/lwfJBCniKkCqBwgbmGbqxcPAzcUh5XzHVkFDK8KqXlHC
0IiJmPqMSSZeSc6b9DwhTpZvANPEdCkBDN+z9mcwWU5eFy33MyYhBPXry0dHsRZFXnlw+DhkKbXz
e/JrqNIDN488OKXXzWY2YaIeGfDPN7wnWNmVf/o6RrfRCI3WzcCAn8h6VqJLQeTRrkAOat9ZpD2B
95YU5lDVMWdN0ozAMTuyG/UcKPrcU0R0peQow61EVrXxvIr8hktC6Vt5GaICtbNECZUfJ7+kEKbC
qplyb/ZOP3Sdo2I+0bjz0NKwkCJWBMrK0fypukPUNXSWTtLu82dtvBCTlWDvvUv9Lt531cBZ1en9
9Lyb3y0aU02PpIesxTcmwzdo3PqAg1zBhLka3jAR5fxtp1kktsVqfyhcSWXDA9qxVzRduipBsiwb
rkmhSkWnKP8NCNTCY6m9/qWqhMHQ2ilLUW2lehGoku2n6yJxomPKmaIbwnbUVBYxU3qxYgILqKRv
Si+QMi+u7vTk8kRZBO16xhPRTU5wDlYoYcR2zwiZI7jSbDGgTvzwFwCDjdyCmT0U1GSYDoZufk8f
xvfI1nnAoWIUymTkwx385chiuJ1E724ra7+6NrgfbjhOlS2zds9X/XSne0YfoIUiIXQK0he7gFd3
4Nvsf8mXdcIKDrdI+lnFLA2rs6VtRXUGx/nUi18lPAA1MbTVlWrP9Ji4K2P88BhE4jNMetr73mVt
gJUUP2y/79SXvNkcSY21CfH8nBqrA0nyiQGn2ZCEDVXa9HjKmNANaLMkYIj0aT+zFAopZnUmN4C1
eGpPAqd+2r7Ctj1JfPsnLZpyYrIbMj9v3dFlG9frk/aDVnPLLbjzqWO6dPZ7k97BydUEn2Dh5QfN
uvcKZfE6sADBIGuE3c6+G8ks/0LIOibV7u8iWEHWDkkjjV9VFiA9u5vJeIaDJe3oA4S2M2kaMDMQ
qYCunlxj6fidHmbm+85sE4KmHAGU+bEXOGltF1gkRSKAGBoplyAcGG02+GdVrrewL0/8xSniWlzl
ufT6bLOgiEH3+cOWiycdJY2e3EqEHvGJAQo3mdkPVDUz4+ZN8RDx5rQ3znrRM7/yx5iXEExCWeFV
dGTqCxcemGCnK2oAwvHqBzij+0r2KVpCnuL6ogfroVqve/rmIIhcCt4LvY9RNz9/TQWg+8G6tdcd
tsVLkV35xE5gBwEXkeng76CIFGwMkNilQkn9l7OLQOG6+QTZ00AJ8VcB9i9sA9Z4pm2Vkh9njvdO
aKd5g1jqKjWN8wfTRDv/fc099lTaZAdQ3ykBLxWwvwLD0jlCv+lGiVAKzGQyjw5YiO1tInPkggTu
FwaHETo5uxl3hB+7iUGKS0bBG+y2yix+O+JBv7jWJ5CtgAOx0XG4ldcsRnYSfGWGifj97p1/Ptfc
aGtEbqMCJFZDjZ/cOUHmH/ohaJ2Sd6ZW7xWmkb589QhwrbHfNW+GzujqtAr0OKMD6o/zA+h59ujE
iBTWj8MEUos9HpoPiKkTYpjVACRj+zY7mgPcRsS9xw9b0oUwDPFbhXSk/S3IHZ7YszKLZZa5mq4l
mZCf1zjwC8PUP7K3gmtUcDfAfgsGA1q9rv26hdBYx3CVQWmO0MTpFrvBRc/PJ4WaVbgWeLCGH+SV
nlfjbCmTH9SuYKzk0ndFzFIruazULS4+hRP1Xr8BR52A6NDy8hl02vgLjP7URvgUiiyLLtD0qjgH
2NTWdXC4sr+VctqE4e1yUTkeU1pjLbLDFiwAtKpcMRCK9d8ne7fpjwJFdrkeBn0eVUKUtxLtl8+f
BAnKm1MY6KuRO61uLBmZmkplCSxL/9nloC44FlEcKPfBBJMsDlzrKS8uFFUV6mGe6dy205GFYzEg
1rkSPcelNm/iduPVZJp75Bhl2UX3u0FHLIh0eDCtV4PgQ6BGM3SLvQmk5k8LIovaSRIFWowdyVCm
wYzuBoBmag6EizV6ZTri97nZzD/RbjoopNnZOw4o+fUYCRbmB9TBFGU8tvbXISb/SUe+gx0Ed9M0
oppkB0Z3gdZm7Oqjr3mR+21na7MGUBk79f5BBAAS3rMqVtQYfdUniQ+ChOQX4jeMevw/EXp8nzJJ
uPVlcdv6h+8h3aiVFLLx6CJXfOqid7lCy7jKcjM6glsGCMqwqNOULb+gS0HVZfGkERKqk7aIh5o6
Fue7PyJvX2bjtZkmm6oApgPRfpIyezzP3xcKEzB270mqVNpjDglo+DrLoOjhmcfhnWl5BAJ0Brki
QzoB23NzJryXGe9wVM5keZ6IyldU1KalG8s84U7QpAyjJ4C22yZcJJ7drQ9S63sh55iYt7OehGaz
EkMgEdDTaGy4VX0fW5OFgcIWAWgSA2bwNq0SYZ95SC7Dea4+gP4rVJmcKuCaHx0oZ8jvLuaooCZk
b6RAXvBo9NTuc1JO/NVOiOqGWUP2T10u7/8C9Hxs2HdpR0aOz1uVP4VJHSJ07mAdQemsvWj5ZFgz
sGNxhQszMjikeF62dyoQtDVzVJhkORW3BLfXd5XEIdKjW52RXp2eTxSNmByjJUa7qjFp+QN0a4Qy
LFlsZwQQAlxhkfQn4VJfi1OvKI7YyYRbwAMtvOoKAIi58tE54/Xflgrkt0eI0Ghs81oIcZHb4T7Q
XvAV7TwT0US1XqvLT6ZVhn4dcmy3DQG5q5uR69jdx4blCMXnKhFqOsmMTD71QFqkkPv+gRERS+RB
2sVI9/ycO5G+fbsqXzTk1Z+cxVWprd7kLcyGVOzNqbLMrB/pfFrRbXBpIVvsl62lyxuFbEOV2yJe
RoZjs7manU2HsTjiNg++FRxVZfTKBblHLaxDzuoCpLqXvpBHQXsyEdRqMsfU8z0vXZlyGstSVFgm
x7khOdWEUtZFF2k3s79g57Axask1JD9tApOkYzNOl/ur3eigm3UEEK5RWVl66S1qE3CnSLSBf884
0x1eyS90Yh/8iUiMXd5x4U84F8ya7Y51j0NfMVd9uxlaf83QIBlX0gwoVE0hOdUwB39tgTEdc5lj
99Y2VBf+ohqfhJEPd4GqsquM5jlA2FJ7zUxczcl86Q/3OSGkcU9CsGMC7rUSVjsV+2ccvLCYl94V
nEFqXqu+dRcB1ASlPXb9JcT9qLktqiwAXvxBOG/Fs2eFw280bfINYtLmB4FgEis56wnwFlTG64Gu
n5dSf7p44HNbqafJZtubdHVj2vzKk7MbWUnN6IF5JmSR6FdcuhDeAF6kRe+vFr/GJQ7/pgRNj4Sa
w+yA1TLyqill0N3zNPpUHrpJVCYjNUpPyuOaUxqYlZpCbeY7Rp2dCENkxIeL1ruZThGWAhZlhe+k
c5CG9/ypdobewJHjKacOY/bZkjjn2mLgPeFSZeEvBgWvGAPfOccNdPzI69OgmnOr8dDvsm90OEr0
AAgv0kmRSvmqZZv7vebdfhdtPMHIu/w+Dvl5Uokpz1JjYtEnxl6XGqaahYw3VNdiQfwmLpBqhSjJ
NBeAVHgLrIki3aJPtKEGCDS5Jh58MdM8i1hDUbkcUzAueFyk1y8FL7V+DBo5Zs5wAXxm5OMia8RQ
SlCl8lWFrub4jmccRy0X3m94xFeXIWmw4J87/LGVPxbTjLwV6BNc0AuFP4CxplAzaxyIhHrUYlT1
g5uHy/g+v2zXIrk6NA19gfHN5D6+2xWYlxOfDrp3oSkLZYFd+ur/Aer5wVzdp1KdwHvJNbmc/blp
MhjRSwu0m4vqXgwvB+h0AhUXz0OLE8pdtRE6DXyf1Yttzvx5ZDfBOIe4fwgG+VkqXPRmroDr3T2p
7PaWlW9if97SS69ibBXtdZ0DB4TU3HdmQ+vNhkhaKrW2wS2B4PQPwgIeMZlPDeM4qKcXdFcJ5rR2
nXRdXBIIV4g6Z6rSm3kht6iM3RGYSfUR7LRtEFTJgLTmaHSk19I+QLEWeu3iWv6MBpVI9FmezPR6
UHUcnlxBxErk+Rfegw0UkpxqtzR6W3dF4tQgqN0Gy/gviTafxZcFnIi0sghVjJGYPQfCE9SomkhY
hrr+pWy3vKILJckiFvnxYtLhETyEhJYAYBLs+Hm3iEKiiShQBjO3DtyiG8MJgXlL8gdOiaAJ+iRd
/kLv7S8Zbh0rebpk8r3TC5o9FiuK/UHH8FoZqlwbV1URqcRrBiKumVRm2EtB44/X1QaW9YklMwns
G6F6ahe//mW8LR84nNhl1DYv0bPThvgmlJ8vuTKVPbGtiiIqtKg+rSKa53NgFWDbiAMOxLm1wxx6
Wwd3uWLKSWOecPXIOGFQBwbVDgydsX80D6wueDr7mHhUGI2l7Amc2BOLo6Tpd3mCqfXm0ZCXrGqH
DAeqTB3MVUfcgQ1U0++ODWF52d/89GQq9CS7Dj2G6xWZrhcUKL6k3S1CPAg3XtE4TaeQGwNkx/kW
kqow+ryBDAUaZA30jYU4FuomCJpG9rSp7BDEQ93+/BTK79gUCslZi8VkpG+cej3cighH7j9bcpyb
wrDQQfTcujsAr6uc7JaTil51PcgtqW+NFK4lDBppLMxicye+KV8poJX9SBEm23m/ULVCiNqHkbiR
rZ6RQefLOBovy1ze/Wf0t691GaH8dWUnBYkjMxNXvOIkWu1peP1HAxPAkV9+2NJEx2Mv7qpz+iN8
D1VcyTNaQ3m06J6EiIxBn5jhmzcOAT56iCgVPM1N18bPronQ4+l5AapC6z+iuKgRPHf7Zg8jnA8+
YhLKgCneBxKBLmKeOl0vDboxb/p+qhr1M37NDPV/JpsCYh4N5IzccsOTwhcswtT0QDVI3I3dWDWg
shf5zh/P9XvVQZQILgUhXw5WvpqgLoYbW/JPqQo+9tvSEcqiJ3amUZvh+/7ClM2JCvtM0hLJ+A1N
lZYmLlfab39HO9nQpw+TGPiEtftDvjyJIQGVPI78PCrni2cJ4seP9h1bNuSoJ8G6yS2QACnzhNJT
awMQio10Do+woNMRFwj+qH9kH1wAL/TA8k/0+T4hGywCwkwSmvRkOvisnrtMpSMakE2n8dYQhUSH
xKAuvWiZt4xYU+jVh2TbFAcBEVYngOWLc1GDcidbkSZE8VxQwCMM7qBtcQ7ozBhHtE3T5JtyNVPQ
senk7igsUPh1TiWYL+C7VR2teOvdExi2Lwdlo7jj6XzLUR8atx1skfirnVANq4XJg7blUYZXzOtg
dw6Ry+zRaIIXDs9330voDCx+qYcFmoC7FJxd3Gf+Kl9M7gI0dVFYuqLie0vxb1X1JPF87CzE+kdN
hRemFxN5fxrKGdT95jyy/1UP1kN9JIvPUs+qAKzfiMXyW81MW7GE+l6BOY/RTTF67Va+IxUkAhrt
uo94XQFmsiqgQp6C9VihvgBrqozqeB/AbrtiKyM0ipzrZaOQ1j3Pv+oF+2Mt73M5vHKlr7Vphjay
Y4eQ03rIg5NCFddbiH0rR4ZVqlCsoyl396C/Qj0ic8tggF/b6F11AZClJq12RACQsieR5S1gYGw3
f0vPpqx3jBKCaZaO491pEiV7jZwleM0daYoDnjBSR41r3ZzppSxlY741Uicr8DfVbDINLDk5U3gZ
lUU5Ha9okwFw1gIyy0kzjmQjRsqqaxvcn0yTe4CYkg7YWsJaJJiRpQEz8RG971v2XdxGvGwqvz3J
qtDb9mlZZbq1/m+i8R9t9Wo43AdAzM+WP67cIqoYWzO3ITLXli1Fj3Kw8d7e3lNiUJ/Hf5zwbl8H
cJSNjmdVJJHO+DS3yOWIO17747GDIAlgmvhEaLkkyGKHaOr9JBBlHnWSCTh5QxBtwgf1hvtCEC30
p82t+kmdl6HRFxT0pF5WuEsS3V7ylnEYBRgwUcIPjHF46htyH4i5REPsnPYZ8NSL3YsFPtMFpwv9
6EBWlinEq1uLPy9azndDk45jESsKVH1kvEANslvqFxdooWRZrUGG7xg9CWGCWPKJL2sIZeurKib+
hwHsutcNc+BRbwPJu03cp5Sf1xeaoUJK/4QbUj9zfMz1XVpRMC8b1/dV2+N3/ikD4zmU3Y4lFVHD
awEjzb8XdfGhBa9y59gOJsiJXEnA7KmbHuCwz3WzpFqEmFU8uHnQRUK2ZSdLy5MdiMsSowRXaHsv
bvYjAS7uHDYULkKy437RQlozsoPqVEQMnh0pFGIMOP/ZxVE2+tFE5yerdsOvD1vNCZZmAyePv0lL
tszH6riCDLmrvRylqmgXWlUALbMOQGdLxgVhDu5nOo63/jN1onivU/XE7KBmc4TwqtFAuE7gcM1N
8tkjyq8syoAFHyQIxpdljWVaNkIX5OXwXfEYFJ0u5UM5tiLUTvUDKb3nODtVWJ2nHNSHovmpVDnN
U15Ms4rgIYyq9xi7bJ8URz/yMJFNVFfOsiLyINpgO6BGwZ1NNZzJYHG35Qa+ZaE2aN5YRqTFMYAr
xsG0eCn/wi+NoIL5OWFJdPh/Lh8qvg7DnkUmQ08tJXmguuCO8+C1sqw59l/16dE7ZmagSpB2D3D3
5SydW5k9AKVnC8Hh75vXWjSSG5HRDRXE/1c1f9bg5YGdT4c/I03JYaDhiMOguj0R2vOYzLwfpQIo
Q2n+G5rhd0wP6GyjNGG0rAjQ8dlVrq4DQJI2WXoiSDuTkkR+VH36K5M40EoLiLEXvpryzWKcMkK5
D5Wq3dXj/UFFGR8Lfq7CTuS7w4vltd8RQqW4ZDHXPnRKhvBfXBqYgGZtZWxwasSK1AUHLnhA+3W8
5T2H4uGJ23ZRfjGqzFoY/Rt1WNrxeZygArelkL4kUgeBITAvkQDHFYx4GHF/P+eiMkVvuULzrBEe
8HPbYPjyRsVR5Fa2qebeJCfDJ7C6T3x6TPMGmoI6Sd8zZC2oQLHvyHwMIpyK5dt2OWJNDp+gFJ+r
HMPGtUAoAU/w5hNY1GqS1fgcCGMbomfD+ZTAA/EYByvLZCmv27H1fIIQMbwa4Km4UQTl7mjpM3oj
cOS9cImgT/5mRGhPDwxrDEMMonUtFsxdbUeq1+wF0DbsCeo6u7jRCysy1q+V1H5mT0cMzGG2c0X0
i+HCKIoMrbSrOK5B18XaehX6SshxdyO9WmpLYzHiabDcN/8IX7dgrOmbZHUCDt0GJKJdJNWlcGwj
Fbna+ARrM6js3fCh7cr4TyjnRMP1Ky9iE+mNkLPrewWNsVnZBBuS/FicdLyvWcDeqLM624CHopXn
4fJfLzWIgnM5FmJKB/6wxNQGf3k0ux5/Vk/0SXGQcDxi8k5o8yepXX/tt8VdKCH9OZiVtCfwzHwV
gbIHA/gMTt9XYXkwi+EJ58DuzYfkbADMLrqCkmhB/BNLJUKd4JxS4D7j4a8oW4nc4Z51A/1d6BuU
j1x1UZQ+HNbBLTrKBSvJ9PvXAEFuNRS2c5RhlRlM2M+3xU35OpSvVVpDGJDk1uWB2U/iwzNQRjtd
0Av2lTIJ5VsL/p0RmsrjOtJY6ZAwXVtEcr6gzFEoGFhdn3WcV9yRZlC/J7GHwde3Kkn66D3+xHTL
IaknEYlCv2c8XW4oujC4tm6vNaK+nlUD3+iEYH3/tADfIRur3nz9pznh/WocuGpC9/AhpCOOtSHe
4VYqVsG6bRIjDWNpXOvTOkUEPNxm69suJfpDivKlkXa0/SpK9okDBlj8nugwiJKHA2iWVp4a1e4w
quYwf5okePnmZ+pEFZ4F+A75CgDu5mLu9gmDQ70dvDiHHzGVhZl35fnYL6zbYMKQUFtVoTmSqpNb
DUupKtuWaLBqZWCPNr1V1aMf3DeUGZXPxCrP84e/IPX/C6Koybs3Fs+ZwxhLauMzBFhSciX9GNQh
oj0m/NiZPK32Yci9a6t+D+l37uyu0KgAX3ZNw5S4TIjP4fR6xPjRVId2ESN0awfMpFsKVpjdm+qq
xtRUfBh5GPHNu6x13tPJaGd7cpxbT1pQxHIpio73dTqWtDmY/Ss8ur5SZMaZGj58pXJAeCnbam0a
7iHXoNNZOl+EZV5pLuBQHNfcJ06RK2iiSJO4R1wJZ+tS9UOGAZ9z5Hojk8A/c07tEagH9xsUfCi4
77w02mi1wNWNdrb51mTEgZxNpEdT/86itfblXsOpEb6C04tc3N4UarlAp8cqEiZIUw9a/G91pJlW
l+gzyMy50ZwtbtPsUoUoT1A/tcrq+eFecmkSEAPFkZYMWy+GZUPddj6jPMVqdynyJ3nDcbc+4Lrk
y7czbCTOgbC5A6gwu6ohO5AZMMl1L4w2IBgQY30kec9oASdejhlONEG/dJAKKsXy/YPYA0eWa37d
xjiwkPZ8RZWY2YCxgLH1/tcRM7kXiwhPeQz3JPcdvQA4Rigw8q3T0/Ou/KkLt2oQJlcZTNlleQOc
xlqaTgyPIvAJLchA0a0QKbiZDpJNmmfGGM5hzEkImo5Qe0kO5Xy8AdHZaxLo6LiCaR3bB70RMqBH
uXhO112EeGbcqxJbafE2+wes1u32VswPCb6qkuELvXlgKE3tSdSJxKVl1BDSm8FjBSpESy9C5zw/
BSIzkjO2zioodroKx9BEjt681dQF2+VGHw0RXSyPQaKQ3A7+lDOTfzuEuXQnojed9MqApY2Ljd3Z
LknMF6bAVlNjGMHZ2owFyrdZiYx5oC3pqir1XIYqYgb7Eg7AUkjjIcVwYC37NGOCOFgEuIHcXeAD
w6Hj3r0WiJwnTgu82qknbAxCUuE87jMGQcLMyZTbsuqkYfjrWB7xREEsBNysRIMhFk6p/otPr4MH
l1LsBGY1YukX9vrso8QPRG09COPKP5ke2vdioxeTUR30lATnBnEZVltwd5cfE7mDKbDSPXxrSDIU
KkBM4nRAe758iNwqQCutrVDIxg6gWhvjIc59yvAexgvjCL4bD90TKIhuuAmQ0F0KTUd91VzkIkGd
l229snIxJjc6Kl1v4RDZ3CQsD48j/UT386twkSjYjcOoPUGMZRCNBcDnkNJNbyFXRJCNUSbSKoUf
Y6R/ioH0wQh5gFVwXbubJtwqAU7J9qeeGc6kEeP7Z6ok3s1iMRDp1OocUGrKWYfcjQEkjRV1joNM
ek4JEUXo/LM9c7N9kCYhpYXUhewookJdAhSAt9/GG1YOkbH3UB9x8MiLcCOAASbT4ZlG7f38bCqO
jZlR9IXICytFAXy5s2m6o0fMVw/2GEDe9pZ3YFsXG4Vp2ICyOY68TLE8w7xYEl4GCT2Onwj8bqbk
igjQOJj9meBWvCx3oVTySPRi0N34YoEKzCYtVLvKcuS0y3LWqr1LHutdn6WQDFDKhzQ6mnMbIJFW
16jLedlQjH8+SsKZUW9JY/FpSmGxqxBs6baASHMOg50YIHxVqUo5Ky+IO6/zz6g3UjKv8Cx4aYnh
kMpisMuSY4P9ACeHVF+NYUXVdfTydzOdsexiQ+rANbe73F07ah0Mp1LZcwaMdFiiNEW3Z1DkN9OH
D62NvrUOETkN/jSXLSsTAHMeVWn1pV7nbijYTpm1X2sgL1g9tgBKwfH+9m2L6mNlv0/YECs7OafN
GrQt4KkVhbP8SSRhtTNR0il8+OzhIyMXsOuhGUq58/h7BryGOBF9USL4YOTObynGBs1DLuqxeEdH
5FOTYOetrtEA03gVPQIvL5855rGA5ahizFwfutqRgOlCwgwkRRuMITvmA1EClTME0px9BUeXzTEL
fiOnIP9eAPoWEFuPvLrwQeBUhuXhRsygC57yG9ODXH8C44tfZWa60nN5naji0NtGXcyCe71VulAT
+b0Ng02uW5SyfOUxrQ5/xfZNpepuvA3+53rol/LZl/iC+uHoDGfQS/relToQ3hYCHc0r29OughFH
5ytUm6isV9pZ5JZjLB5Nex/n7aNbFOFjeo6mEVrPrTimHM5mMUtMClyDsmCmze4Z8QJHLBD1GQlM
gGt5Go9JRG/ThLtMfbTs5j3KqTwYUUkF4WSh2CZYYifbd9jM3Q/ozoLubM5gSFf6ReX08iTkp6ff
F4MS4SoUHuKM+f7l7/nPjui9bfa48eig/lyBumb93GxYIKaVXJHEPePAIfnIZrvOKd+770lwmE26
TSNrZXUnTqN8hGc2/Gwn368ZwJ66vh+AD/tM+i6rJ1DqgHxmlC463HV31e6DGyyrJ861n+8VRt3W
kN4eAaQ8BN83gXSxGTryDA0Cbgir9hByPN4TxJR1RCQZq01NayhjFxgctDyEVutN1mbfAh0+EVF5
0EOOpohqoDsjZ6q6pRUSyStD0seLaoPdtjNdzgk6TtQGbQC+fDcG1xpo6FzQ/L6RR5UDuniHgwvR
8WXM4L2QSmr2HMF1yRQyS5nYs2nnfIHBDjowxKp+mPGuP09TuCAqiewkugPsZ/USna2dHrAuho0q
f8B5X1tj6chex6zaO1HGmzpHAy7c4PlfSOOKXCQ7YHFYPVuNhM6UZf7bX4ydf8O1iBhlq8g4f7Co
uIK17wPOAstTwGmtkwdgY9pE07BR6wG4s+MTPua/mXX/h6tTH3KyFm/QAUT+xPaGdkAqODSmM5gB
287UXu1MFSPfr67g337/buetPGI1NFCxW3OnjKc1UinreIR0Mejj2zLyO8B0FIUkV/I/nvbYdc0C
WpTYH3qEwxWuSg3F5dm5U7puOhn3CKyOXaDiVBQT9LNXTO+68YlTfqZxvSkuL8am+kt66FnCdlxF
C0Oadpd4F+9bAeGFSBKI6L5vYDwW876Si9bxjq+5QZqLqF40XYtjv/TDN8SD03ipA2rWaHLa7Qv5
hksCLQpaPwzjd50y76D6MX9wA/AqW0V2v0AQsdMhpAQCzPCv7LhQkdt4VO9xTpfvdsmIqt22K0i0
BF8tHnwl1wEWAIE7HIdBSkX8fDFhSeByBYyL4OdqmYjB4+AOuqIQU3gsPpwFucJMYnWV1o27klyg
AM+RDn+dxuCyUYFzlIxyAciD/BvJcmu2o32c7JTxjnj1Q6R8KUPs1BBXGHUh1kmHMxTOFmq/932W
1oiaf480ymM5he9vf4CQO5DS+vsGU3rBK/941tvJeJCDRCWXtpdLw65kafQn/ZOKNQZQjM+/eNky
aZ8ClwSbenhzY53waugaofDvDXL5/Rx4YBVoVrrWWa2G1Pvr17mrl/kCnEMvvMsvyP8JueQ8IP7b
6dVNQtN2ooaWWTiC6YiuN0Fcuj5WQXvVqdWLKmyqJYSuDpJv5qXA8Skv9SkF7SHAOBJLv0NoMTpR
6aPRPsiEpJv/Wocld63sW+/BYz5d3RzZWed3btKKkRWuvncCHTabEGl0r8+E6iu5a+tpvHC50TrV
0TJroUbj1XD/vTL/4r+lHitxR+J+kyjdxs/HOM1X90w1YUFSr3ZMlUtOLn0Ljt562D01DSfkvZUl
Qn2qAQu4I5lolkUXRsFStJFsOOxlgL60AjBFRUWbPhFYK2mPPWzAkEENOuuPIw42i+F/yCb8spVu
gfvAy34aYZn8Gwzn5MPHv2i8+QjeUxFsl0aUWBBp1zZbOrwEKzp6L6sbifbhZpMiB/kIJY5MsGLs
+G8FYrSWOJ1l+1j6KhkPO+2a3Oy2SWQCFUPfUu/2RAYDdFWaY+8/1bpv6sSTVFYyXQQvXOS/JkoV
30ftKQT7rIugrGZ5bcNlLrxqXiNYs/tFoG2sK3dbu16oq6qEg8Unsb8SVldF45cHMnAgbs2lxt35
wJUQGoHQvFy4l7LnKMTrIh76PQgDJZ17Y/HMAuxBAcoocGRFwDZeY0hhKaSBaQc1M62Fqc3gUNZq
ZQINVPvGSubNYhKiWt03b0r9DnEEVFGzL6mvPS2hQL5xtd6xSRKjlcxG2KZzQWqbmGevu88ukh1M
Nco6XiMQMUnLuJXV2RCvr6iPKB5tbmLu3+LZ2REvAm6sR1oYLYZXIT3AfTB41fRU1cq2isgZUsn2
s2h1234D8bUmEcJU9LKyiw7yT1ExbeHDVC3y4R0c4f+4zeFoy+jaAWHVA7MOy4OI406NQV8SuetL
VTRXNkOpKCpHqufQAz9qB4Wci6QyazoIsNTWLSfbbgaJwq2dTt/Na7d33UEbF13kPQbK9x61/j86
CCpiGhbuxLiIDGJvdBfAN+SpLY82siGegZIxRx3J9XruYLp1L3ry9i9o2OiNPjwd9/btUkhsOCd1
NxRGqJU5fj+8xnpXMah5yZ5UWZ+cWlSFtPFjYVLxNMcRGh76kMLna5j6/DVKBQi6J157GJV2MolZ
pD2i1EJOP3eQIHjqEtyEyidsQuiPpqQV3BB2Ysfre9czd0yflHArJCiFTVLxM20uI2jKnTm+Ixgg
F1ar5HRp4TmB2PZI5/rFbtgFg0pIlRj66ToEcsnLI9o1slsegeUTxAStiFe8ZYMHcu7QFtKoW8Ek
IfLOzvmZWYDVhZ1ols9mlG9Q8lZlRCZ4e0CPnILPKo3ou/ParBRlhFCG+QnpoD6Q5yzIxMK0Wh3D
iSikynGMmOy1NftYlH3xfd7gCX5Hg6QodgGEl3Hy31o5toZO2Dd4E2jIdr80uKYPPdmFhS1s3QMA
45Y4pl2101T7iS0C75aZ+cG5bkiRQ3eXzO3lD+sE/gEuMZ6+4Bbfv3C9hb3A+J79NZc8lsW0rRF+
o5R0PnYrFMyTPs5w3wB8Wks9zbr5XcT/Pn0j67yZF7WFo//RJmtStq/asYMozXBlqDwh8EC7beRi
Xilkt+9daDCJlsfc+NtTDdlpg/xAdL+a+kw2FET3+V9/Y5YobYFjlWcnSWiP+t/C6lnG2BkNMPgN
bz8SmVSrFRkBycg4XybHINduf/pC7tKdbPw62FVxE3SMdMqzmzUB2K5ja8gydsDK08MeqLisMLke
2hvCoQzfl3lhUov0YWDNqp1v511NdVVxFFTPdOWCa3s2BEY/wdAFvr0k2QdgwHNOnEFpvbHX8fmb
CjFFnUKJ1BtWRzRpYMwy8F08uzTH3jxdbQDUGniEt2H7bOCzZbKkdGBLecZSfhnz1zNSAScdMmbh
Kcmti0Wlm07UTealq1dL8MZEpqGjSDqhx977+3+n+eCaUGh+V0pzK0DVvM26zuAM1pmgWdDRaCcb
zdv3xupjgSBgefm3rKkqexJDCsjPVJVYsT5L2iGRn9k3DYyf4Mb0l+HWikan43YJut2lYvTIr+fc
PoqE/HtEkyX/nUdRuNwRHHOwjwONTyYYy5WToy3gJFbIff88Ciu2/Wd8wj9dnL900bsnUbN352bG
J8UZeK8+lKxqTq8U/m2pUrjng8erM9nHQ/t8w7WxdsxjFzPRREP/nEUrN09h4mNfA0D4f5UJorEE
9Y9RcmmfLPeG2iy1I3K6Yf385ffPTcKrIV8apj0S37DjjSz0hjZiBlGQpvou4RywQx8sG4zCg1Ja
MbqiivXIaXn8vOpdfWi2movMW7UzIfQDava9zXgzdzXTAdTERmSP4KXRkwZSXjjMuG74ZlXD6xZa
MsJCyl627Jyyhi/+V503ro4krwYEoY6rged1XqGrxbY73oZ/pK+PI6iRiJNKkIgYHbYL8Yh/TSAK
lpjMVSx5ZG6sM+b5ME9epLVXJz5qJVTJ+Dbf25eGOZ4pC5PHz/DGG98QYRyyWNZL3T1k/tY24NXt
UR9ZmqMj1Eb2ngzr5yUDP6hl/bwtzYxUNH/G9XTaqp4ceoP2gf9KqaesE1CkoMIMXPC76OSvpVz9
0MMxet7Ul0RvfHVk+qciaWE3Smgo15Yvgf6ZIpPQtuzzC933cwL9GMWc/3WY7kjiGiGoNQlgrzD+
JT6RiuH2anzsFlsd1UiSwBj5QMchYn7DERpfTGtXuL0LzJIwvi1XlANsTExfOaUmh9MnbVCMNEto
8JgJnWml4tyPOCqxPKmjWD+R9BHbtDTY9gerYNVePHoa+lJYvz269ymtPZpW/4u2zWqj+I3+htFz
V1H8d62I9ephqha6uYPF5Hbesn3hJY1X8EovOzKaBzRTjv5/UPVLoytymWdcTcvZn3tVksqzMR4T
oiLa2eNGOyvmIYXvfPulsiywDxgEU9QeYvHDj3DDdFyPitrEElssP1tltX+CMuF11Fn0YjMLMe7y
oI8da/29LJwvp9bFQRTbBI7k1JLf7pEWge8g1tdtsMLdb8o7hy58PJaYzot59HzMHy/koucKd67k
QYogw9Y/zrJL0UaUKnDtzl1TKiQi3gxw+ytVD7du2MxdSjCb9t3txPWqevtCgs/TB560psQX0C+8
c+bCJPcanMFPT/dZJU0oOBe9BcwcXkEXH+H64+OXwBxOKSs4hHtpOqgQtJfC9bEWi1r1LcleWhAD
uNiOkxUUWLjTmawG3d4GMYAxKkw5smru6bYEqfSCkYeApJ6329r3iRIwzA2e/YZKGw6p7EV7cobR
m+WAVUoMMcl0YB14l8hQPozh4QWr/zpb94jVtjTYiceH+BCmH+StoiyMrS+EYRBW5aFh1a3V+YgW
tntcUt9Y7ECq5ELgNd2OfAQ9CjceUMgE8bc3TwlbuXgZT5hvArjz2UqKyyrxQG9r7PM74yD/uuHw
QfMkFd+DBVDk2fVAol23gMt74Qo5eB3fggBhdtiVXOnd7/HmPoMgpZlbsLxTgOfDMXd7a8Q+mGLR
CS0yDLKnhgD8l1L6TfI/gYOThcVN8XB+qsBT83WsNr0UuYxTnpxseMMFcVRqkkg3TwafpFJGIUVk
JrVTF7XOOyKXkvD7yaqqlUta8tJ4q4baSr8jVfj1g/h07S09apnGxjfIRCOZZjKGfK1GOc9FttE5
KWhD2zOFATe4AFJX353qaXPTIOdYJjdpRLuw0aO5ep140X3PybJaw880jpjfUjltqmtGTI+RZkVA
G5Fa6s1gPsxcQ7PAPeB7t7ArFkqgAZJ3A8ujYz98N0rypZuZcrkA2XLqPZAVNMtrssiGXv6mxXqK
jjUZHFXx6YS+vR+MjEQwFRQ+eom7/uGiAMU9F2r3XeFuK4pDrWa4nIarDTS5VwT4YktjKlq8QpAJ
Uop3DoPVMv8EsV6aYrRl8jMu9KVqR1/+FgRimEQzuc6g0fipMJjnpxWaaibJBC+nUrIYsAuS38rY
wn7Bw9F33Y9D0/MLiaUt5GUYLT9ZxLly+20ZH4VP5a7Gbab4TRm8zUehuuYp7UoPcAxC2dir3b83
tBMOP1hphRYndZbhM0PLyG6naHAmxfXlXSnH9H91mcvZjN9W0uLcUFRtVSA9+TjHaWzq9Oe9rFq0
D8SbboZCAognjoAr1fcpSbgpn/Y+5mM0j8oQzXQ6mWJ1G7IJJpfp0BRd1c5e2hmQUTVgGxpCtpqg
dxnAWmN+uygSnqfMQhzycM8PpDVZURFL8H3u6Gfkg4+0j6zrwD0tpJBs1y+KujzGNID9StjJONp9
gaZbO0q2BjrByhu6o3XevCyWbEadBgu6UdBbDv7f3MoHz6VSlz+90GstV5KRKYgaxdH679Zw1PhF
1ITpgZ+eK++jFaSEmIouc5RwZnlmOQWi/yxCZ7UEMEHoOGOJEAqaMAAjwq3O6wfQQXxgJ710E9ZH
Y4bRJxea1iWTE/4jVdXqjgXPC38tVP+Bt2+dDKefEaJxj8O/vJTHBniF6JXAaAME7C7hxVzi14Gm
9bHhZ2BY0Ub1qQ7R3UHM8+k4ZSD4cJETUbQAi48brJ+K+c422col6M4U3Lj4AOVk0PJTNJz0K+Su
4M+mkNCko95mcg8t2jDmgNm4mmHVwgWyi2ypqxu/3VBFoUWvJEQO0POKW9iDIUGX8nzWhnKhBqw3
NHqMwRxZyngRaU3Kn1JzFWKN8sx0x5U/eMeRY2oxC+1B8m7qJZOW318mPWnCY8ks/w31daH99FNb
uqgFH9CrbCcuL2xz952KWor4aX0uLWU4TuP3rtzaT6nKTZW6+DLV8kuqBOix/D9n1uRWjUzlf3fF
GpT2NTGX6FZF8MOAGCoj/76Rpabl1CuujOSLk8sy8n5RHWPc9ecCylZeWg09oWFYJ8bg+BQXJ8UW
jINDPTMpy1z5YgfMCVcecUIlU49QN0KNRL0Z7Y01yXFDyQPNHgvha6NQ2vWT3+RM2GxB/TvMQnUe
Ra2uvSdmF4yrNyGiLHznkcJ7R5hYCHOs0jfWbqOftZxCbh7A6XRNZqoCGjD/GtRraqDK2BXezPx0
uft2E4XhlP2n+uO32CmM5iXUlZlrFZjg6NBxyo+KcRCaWKfJv0t0rVIprCQkc9hawU3YaLYPM4HV
W3FF27xkuejKOPaVtilc2hMMHTaxuTbD04NnaVZ8NvryQUjXB2uR21IGmcdEjFBAc66KGStGwG2K
HiZy7H3mUGRzmUcn5NmzzQrIvvscXtaY84zar+EY8T48fLigg7XLwxV6IZivc8Mgx+5QEos2ekHg
LFnmt9wqhQHxOdeBYFmBCoM4Z23dPXdyLyIXVW9+N4PsBUxhd0ZavYz3Ek8eTxjWxS0DtldMqJz+
DV/EI7x9ygTWGI5oO/EMVJqQIjTtXyfdN4RUfoL3p1QrYQ5H+MqGsYlp8KMU7qCebtLet1KFWjeO
4U/Hr/BDBbmYJEJcC2P021CNrF1is8Qwi0XZBBOdl3CXmek5Evt8dwerTcWyRbxDtXHSBqXueseb
/EDsbKJo6rY7FPwlYv31GGLc7aeQoS27bAvA/2q4QgfNJF9291sxYxGQ2cm/IXBGny6TaR9zZBSI
bmpwRaPy/qYCbUMKegt9Gp4qhLZqkVMbUfmC1EIjnpdXuI553N17u4xlNLfqBVHoc0Yywb1H+D7M
95WPxTPNtcZNtSrj8tjwg9VEkbCpTTLcGBlBqBa+yeEN4tCeg26e1y9klIreKi4Eb7iNuFANv+0W
LVH25fuv5dmd4eaMVyBuvUxSmgN1wMbVVy9deu/7bV85xXwkvG78hCvtYE5cLo+CT31UtKpeI7do
n/EN0HVeAU2VGhglBM+Tc9Ma7pjPAfCkvHL9wOKzU2Bltpqgs/SBAKSWewqDGSH02HBAoiJm9mgX
7YypASevV0UoQ34mg2i+z05icEOCCURghXrthCcUJtxsHpm6Z18WwANwP4f+Dr7RTutX+b8diLJt
pz3ZuMfjWqXNPTI+vIUHk7Y3Mccfwc11kilG/UoZOtn2M+yZfWzTl6pwTWO4ZKanZEpXzb0kwLKK
JwsBKrQ5L5Rdp2GWXqD/seBfmcPy/EsopQ3Io323O48bnu+4PqWulFAzHvBFupIf6JF51QhEP1l2
1JKt1VFXvER1/mWLxnQsqYg0q+fFJeYUw3KAmANk80jOhusg/FW2/zkw7Rz2BlU0oYuGmnqgTjsq
aye+vRqxR7PRD8poTy331KbYqxmd5pgcfS9Up5wDs9arFMSrMwkHqdInCZtyqHqg4I2UGltyuoAs
APwiRG4dNuvPitI7h/spfbTg718Lx9qxhscEIDWCxFcMceh/J4+x0GOfhd8UdAr39NgZzwO9yCRD
canzvPz0JgZOHImKz6mFMz07d0NEg60Vg2/TmgrmoWQknvug25yRUXVrpzj8hJ6IgGIl+H0ua/Wu
qPI/LYbwWkJU/xziOQ1veasOplh/1b05mGjI2RJAsJVHIwCiUMJGvzEsDyhCJgaIcjpCJNuGjY7z
ewHmdWFRLdKNcUcmin+XLdZuqEpBawUJTmFtpwLEQs9/SsBrdd6yvBeBkA4jgNzuD0d9O7Jd3UPH
t9zF9lu59OCw0ShZs2WA5mYdlU0o9bnkzQfa6erXy5CBPpp+TSS9miuba94RiQwoG5VFdBEMMpN7
oo/PSV7jQTJS7Cc3BEuUPT5ILF4VrzLDvYcem2feg1ausRXbATUsGp9GaLZCCG8UhqJ5r3pi34sL
5exTasSZyNCragxQeUW5Kpk+032dIkwXCIjYRFFMaBWJKEOBaZ8SVRiKJqWYX2bsfBFcpJm2q74t
GNdNR4fO+4bTFhOnSyzO//pNbrpP7XP26kZ8NvFqhVVUPKu+6WV6QX9gBUop9qRd073pzqkbys2R
q9BErdXfaaH1PP7XJqg252mslGqbIw6DYWZv8/eK1pY9pHLDvahwF4fsuJgUfC6Uae2vUXDhpRyK
F6ozBnrhd048R9gzvUhRWrL3TtsYl0qWGA4qhCX4Sfp9hcHi4p21GUUjlBhg6SyPJl8R755H5CzT
batC+tw3oHjeU4ceZ1zGBR6nPO8/h1M/cbqumby3Y9m0V4yltykbRa2BMSb3wal19PqZZUGR9Haf
ooQGvxeOPSIcnV3GHo+lgFb5AaZoavtGr4fHHvQzOjwnzipo/88ZrTXCKUKOrr2dDC84f/tt0AGo
2uVqNex/q6xuc7d5EoEav9ANZ7SZGasf619gMejo1hOana2wET80IjwQKqAtprU5ROxudQafs3ds
by0U77oQ1E8zdH2AuyHkX37bFt+Nn0ZPnmR4cBLEwg412TyluNN1ZwreK74wQrb27bamn9ku1mWR
j+Dlghw5X8OJGVR1I0QPf/6dNY6nSN/xFGzYWuDTKPP7bp6/rQCkpcZbPucf+2yQyqQjR3YK4iDn
Bgxh0cQ1Sj+7aQ4ZX5oZfxZxQ75krV/fVnlMdg5I0+Vfklo0Ov6clRAnHwr5j6btN4Lx2H89nwe0
dc1etUT0t/X0SpNinDz6zqb1dmeBkCDlowAuwsu+SLXmLNiWy6XMSPf2XnyD4jEqS5d/8nkCxbsu
dM0RkiPQwoFpVoS8p1Vte7AfeA0+pHoWAhNrU2BDWEn3plmsD3jQMAH2pYlz/bst/am4wVYQ7hwy
GtDp2jau/wdOaSFN5T8PxfZCSdzAf6sEZA8+ybPF9fRruoZfitbSpfnpU2TMSJ3ccsQfcjN9oQpP
uXmHxCGGf2MFQRcFRplyzdvMNLTjakwDnCrHCbRG7WdB68r3ayQ86slnoUkMZQoKkqfUqeonDvQS
uu+5e91+dw+G2Ps0osEitDMRGQv9MsZXnwfBXyBk9kudx6HEBXG9NgFTMUKBmrbOkFrJqsW10haI
3T434OK97a0g6agCVHuTFv7m6m6Wz4VG/mol3dWbVWUIbvsXfoZvnI5fcfBz+4wR12YxlYWzOK/s
bTeR/UC3s+AUWHMl5ooEt2BGtALovYVdz8S+Yeg/v89ZOc3e0qY9MdTrsvpoQmPE9NHnrragtwPq
CXWW/zukMaTgUQAwbc9Ptmn3LLeta2QgrLjNiDjynJfcucxeTyy/LDK02dL2D0+NMCCQDEdCYn6D
XANzqnQpN2hUF+2RFMEApjaOH+UbAFriCCzgUzKH8vTtyoZyqWrsDEpMDGH7e/kNKwM1B8TyN+Vx
CVm8q90qyTtNRZThw7a8GohyVB29nz0VkqZx4YJbxACNYbjojF/Quucnt3ej/Cep50Ps6gAyyAai
XBx6oS8rrXHDnWkcnccwb3OfHnXnSo8cohDfSkvO7WGkxbGJ5usNNXuHen5Pvs0rTD3BOz2shX17
KRJwXQanaBpqiR9WcQrtrHJeBnxnRn41Acf6H7a5QttOORHZ/WzCorOkB46rMYAeo+rwXIR5Acos
qfcH8oc8pN0uwuSVDYP1Y7ebi228PxBdFRU1BJ+tACSp4vZmhRZfDrj9+1Sva3fn0eypZh3iLqny
ytv3+negIo/cqa15PQcpCTIns1okAx9GQq48/LVWId0lOSfERlp6h/31yPuCjTTd7HJb8CgDiibS
JXeTS8j2hEgIqFX1W+4WbiqH5oB6AHNwk8O4fkwgGiHadOINwg4YtHWoj8CH7xpa4EX8DhnNcwsV
jziuyLGg5AFWltuggjAj9T2p8qz4YQri7SZjr2VngN05JQwdCKr5JRX+yYJTNGEJZ9LQf8t6i67g
MQrHAS6z2gdNvQAtBnBr8Hd31ylGJtVCrk5HSB1L92XNMAabixmpcnc2rI8DYEXc+CzjVz2PtYGw
1/kKufa7HJU2Ns0iLftpJLZXakdxzpCA2akx1deIe1gcbPBPMB/wOFcDlSAUFmGk7fr0hD2ffXRI
DQ+05DiUyzL5c2Q8Sv/s5O/8Ku9NcuUDAxh/64q2WVbJjk4EIAA0u6YscWTH0x9dSFnUFptrWqa1
sNWwbJVLQIKpqF0MyoRQxq1TTuG7POXNX5ct5ovWuqWu+lZrLL3eZHf6HTbNAiPaFNdVm/EduvFs
Tavh+IZMZYN4XzyCEDXSg79xB5VCIQQHtB4k5jifnSsA6gA1Ls+u/RkQ/Sw0HiaghnUeYDegqqB5
RbF5VOAorK2WF/q5Kj7inl9lN7wf+0/VKidbKZx4Bz7+R+kZinZnCrODbuF1FF4RFjugV3WaY580
B3zQwe27OERyR3TyJL4lgksmIwQ6rNSe/DMHMjYSbOTHMsRoIceNKRt5WYDULMy74k2M1YnGKrDi
b0ufpVIKKFz4UX4iCXQKEUxbG9+/1EEDy0Qxbx4ii1kx4Bayfc7HILVFuGP3GI4dEcBnNZhkeeu5
05VgynBuU3DTsnK7cxg1GaKGdMbjhJJwZ2UvXmYvEDVAI2wIOMEeqzYWGPoIrY1PCXs7VKdCaZG7
BwzhkI/UmO2xvv0c6qiBFDuapZImOTixAYVqFKoR1V9aPBnX/4jZQ492Co6agQ+j80/VxMhiSpsC
4JyHYuXL81MJ8iuIQj/FLRWnjqgTrRqT2DJvfXqYOMkv6oaWYM7iZcrv72Z3NtRvHjZv458x5rGD
SZ/UmOsRrmLfUW/RFFL5C12B+iPG8gRvZK7iW8fKXDUXYBhwDOOt3fkcqBFkeyCPdbCNIiokgHub
gulQYP8SN0EVEXFrz/TzD2mOMHpaGj2Iru0xU6XgcIwAZmsLvOoQUHYU4BbnV3fj8GOaT50CnuQY
pusvkADJ131q5fVnWHW6N6d6mADN7LdSBiNGUbKFQpJRFAWShre8OOj2UpoW2GwYYx0/U5GOzrrc
hO2p887lI1k5WcEHmaBBRbBu79S/fotwzueNXrxyt2oXhGBop6Z5R7Q/80M68x/RZbhor1JBRK4s
ZLsEfy9gLx+wRxppbyemX7azVntoKufHHbk1ggmoP2FoZ2nc0+Egqpy0yqxzMNmnZxnrcgCtocqk
UblDkkIReWK34EQ/J8zXkmyJwEJuD6eltNQeurITaZgpIZvMWH1z3CxO7s5HwTX129K02mnNLh5V
EO6rGDH9QIh8PlsvpyWE/ChJRsJVpejMJ28HcN6MYMknLOvTsBWA6610Q0HKj4hzZzlEdJ0KZl0j
2Csa5KtsicTk9uhvqmyhGvw+eNjnbScWlngYdloGdz5nyYwKmje0TMs5JS8p1MW6VsraUxIcVpWV
sPd2J0/CTr/7A/oJoFsaxlT+8/S68/+0WvqTfAzf8ewEzB8I76mjVGWjezNgc5YKcs5fjrKFYYre
91RY4wL1SHk2j0gyd4VU3GLVRi/jQiX/glJZisSNra+okWNZEu6tVzCoYUUN0+or6ExoBZ5kO2JV
zy4vLGw6xgTLlja3N7bJWFsgft4/GXTFQgtDB3welH1uZ260qKlAbc43OpS3GoY0YNs//T1FPwJf
9HmAKGSNstoqNjUursree7hKe3hpHCtfMCBb+dMzo88uTV0o7Mj6ZubkAJIqNLkZazHOvtuORv8f
ZJUMSrjJnAFgPaWeRqKSHeIyHINj9gQ2GQJ/41M4/i2h1odP0PI1Eahf0HQcmvbaunZ+jfptVRsq
hDXnnG6dtZUBJjqNxuConfnbTOyxyUgV3ik+IiwLnzQrhov9EqdGJ5f1InUZ9k6vullG6FW7S7RJ
2ToCZ0zVPYynbFq5+HS3+8WUpoiW3RaGWNrjOLpzidvf9f0rb3MqrPsEW+JWbpKHCHrbaAoq3zLq
ECcH0kO6MeolDFKcCJPbTyooDz/zR0dCO7/3jHKOwUQHtPbHiL/xArQzQE6311vGANtJ+dbqYhBe
NXrkiV/I11t+5FmxmpSLADIC7eLQYnc1DtLxKz54KXEhGLA66ObKAZ6NpF0Wk6oomIWHUCr8iqc/
5rq7geRabKUxWsuBnHX9BWAc853wtK+gbjNT0z20aMhjs0wguFz/O6CoRqDkIEaKLftH355HojwK
3iabun5kTAGVDT6iZhUZk7bE/5MQae7lsteUEbFh0hsh0ck6VVX0CYcWKMCDF4OhDQYNxLdi8UZc
UEvyuvdsKSVE3DBQoeXrh1KtM3PTopj8kLg3Coh+UqovcjiR+mkMQUU0nviy3Hof7l5jWEy2KfeI
LRIRPJnL41T+XG6Iftxa/+1xyXiVGhZHOTO2IKcv76tZCV8YLvHR0EOpPK3PFGq8qHw4cMN/p+1j
5K17ZMUa7jIkeBxbkSk0ZlVLt78xGCJraHiERe77SQBQ7aP5xxoJ740DKHiolAvpW9m6/CFaBl+C
ZS05j2liB2IQucxVYm7/A6HlyDxF67So7+7ugM9pnspbLAIy+xBweVf2As2T6SJd93tt06NnZ0ut
w7deRpbcjps9F7D8zuzPFi2NXqyR8E5rlYDerEpMlyDkwQ9/dmPTeUDLkE2jtSj3/Z19MqtSC3ek
3/zUvKy/+kFFYpYvZlWuvDUCmUkb+HaR+f/A8SrA8VmCawsTDgC8eZ8ePqrmlrB1JQDJq4FC2sdt
B93JRUDntmXczMJY9dcIc5W13gggdLtrFRCanVfPwXO+ma9vKKpQGJHimfdbc4ZdiaRxLbnN4Kpj
VwYopmVghX0l9UnLPqIvn87gLdPDWYQVX71Zbn5FNX88oiKTY5lK9AEFSokRPm8zlbzvw+6+MtKb
8v5BO2Psvh7jRDVbGSTxWaWAsxWb9EXzRqKFZDAKtiB1M9FBgfNcT301mIT5OzjGfzThGPtd462t
v2+yYyUCY6OvP7OHmKeFvQAmS1zswjS/cIhvGm2+lGv67FZmME5MyQ0ZUNKbhk+DTX/Frt/c8Ckd
t+s+DF2Pl5Ul4j/k9NoaSvlD25LmO/9qR3QVgGa50/zw6L25CNhYnFVpoiprRDfDj/cEj/WnYn/E
nFrBArFfQhfjTkLxOlbz8wMdPcawcHRp2ulVOy4QL0uQtlEMKMnFFU4xsSdVLx9bHVVff38uI4mp
uvczMXO0TYH4vq3lg0yVaZGftMqg97E3DihnSr751j+Wh1oZ0cJaU868ofjhDIvoqEwxUYNmpQNH
ZPKb/TUx6HqPrEr6MrRR/BViLzv2dCSFCRlwf3W8vQNiP4PzgnmEwTExQ6muAGVMc4xVE6upR4pm
QEVOc5pzE0+JUOj+aFQiUigzkDTKAZPazKJzWi2WgeauKes5x/+EhhLe/F6a39WmGEgrJNYFFqqv
OBr7W8kitngg36h8iLCvxhHgEsY96bWrQ30BFD+lBkpaZz9jMsZcJVe5mcFtrG9AYBCrBt7cDVKB
f2loErbOMfF3OHTOp/FZnkpU7ciz4/e0J7BfqGs3fCST7qyDEA0r3//JbdMgrkMFsAzfPnphVmMd
6EsylaMW9NmFSUXdQVBVIMo2wgmjqTHzxOBRAA2FYLuXSktG4GvpjtxYQ5wiN3ZFTJKWFKtD/dQN
qgDQWGlfQ1mLyDbtArPhnK7BcJZc76OIlsGWm++wcNj6v5gZ7atJoUhLW/9A/Zq50u4WCVHvYSVl
LeBjsuvzSU/LtE9whAN1I68qWjAObon2Rg0jA0FNET6kuPJN31a0qT4k/hl4/BI+Akz5219a4FIh
hTw9qytjIl/Q+hT9e73GDx3Bxa3COJBM/mEe7+7KL8KEeR0wEbhQuKXn8vE8LWPE3O8KypQ7N40B
dgwKezXPb2b1cfm/JSsXreHi/121a1Vf9VMrbGvXZLmgDIkCwys2H+4ye1KVTsLXl94D9GbHh0dg
ViMgzEMNU8JFABf6O1YmNTU5P0HnO+AGhblxovLgCB4jv17vYX62UbfBktezj4nFToN9POqyLu7L
uvxST6UunuHuTGuZOMWQUGzJ7PVTv26R05F5pBRGp+Wt9qCvfzUuKS1wSODrYhcOS/2B4egT2dVn
2pA+UplsXADO0l1njpBTdr2FrtHbZ7WwNWc4S4PXRbaAwpj7dsoLgnuo05HymssV5E1KnFlrNcyi
oCpnbhTfTuh/HEwA9fVqvAzfHUVpXPw0JYa1Ucgs4yOaQ06TjYhpr7p0VctQXDfD/BOwASM18A5b
gBGsQtBpsgK4TzC/8Dn3lp7u6IBGBJzYRlMKgMUrn4e77KCe0ZbnvJ4xPmMMpm3L9FKSdM3nJwJp
aSMBO7iRm+8HJ04mjwepLA/6MwyCBaaLRhg1d4Ew5ZroCUnyjXs+d6+5Q8AmivPvHavvlNOu+whV
22xlVMMBBScGz16nLab+QLwnyfEu265+KqfflOyx/YYRnmAyWDYNU5I29C2cB8b1bZNP9b5b3kDn
Ty8OW7qCinBg5oOfFZNh/g74Hje1PHVHgdV3sKjAkmbGg+D8IOblsvCbSwCSpyzIFLgB9pRvORrd
amQPOMtgT9llJC/UrzBg5bNDzfd2IuoiK3AUOcUl0Y/PQ6bQMZ1YajOYkfRiH6bL4KJDZtFJqyj1
cSu1/qNCY3oPLKx3L9SBqt2LZAsY0HAHfQsakMNl7k8jkXxihpd1yW0ZBmmfBlOJXSNfUjmdceqV
lToXBcivMksl6/PjBs0BZILVklEE6dF+WG0AAHMHHdPuzlSRk7SOGzlhCrLdr1AyY5PZedywlDoc
ANorDN92j9Ij0RYB3Q9b1fWhzxRp1WNApnvHL8va4/0FCpx1bw8bFAN8QUTz+KeXnndOtzxmGbKY
dFO9zat149WJz3qubBoj/wkO2nQDZyEFkTb2bIyE/Uj/MzV30OFEMEYILTxd96OODm4BH9PQhb5A
fmWajr15jgUGdhqo0m0jUb7ihR2LfbUuBA1MyZhxyT0+TIl4DMq322K1pgrYnoqw9E/qIa26eqby
ZVuabPNs40wmnTWnmwUl5dm4xz+dyMILtc+RtLPL1uIL+wIoV1Bz4AH0ew1pLJvFQlalvrfhEXC5
xTAAu21xBwbybbHZPkBwQHuQbekDlfePW0VQVoGsy1l4xPzYLJNgUNSkJKLy/MUUHtxYfTasOwGU
fI340T1q79CV7C+i37UD4VVzc9+e7wS7RqIKOk/jNNaq7lSZOqZqwq65yBEh0Yy7Brqm5Yyyf2Yq
5wXXb/nOkSxp8GiNNlxYeLacpkjSE9lQ2gD9/UbXxvyLGmSYDlmtnlthAipXTw30tcxP5NmIN114
sXp187lz/db0qI6yrGk6ZprLMbpdXORZZjMuHQTOi943RduJpWCA0cLgQ9kx3Vn5nk1C6Or0XTsl
3gKsgDmNqvX8NkEcevsQH2pNHUZdmwtOIJExptuSDfPEakC5/UPH6gV0CnQrGbkynwbC3Bw8ERiK
jdFaEhj7oPsIm6i7Xu8rZN8QkH8bz3kFlqAD9t/7rihQMliLPZmyRc65kWK+HiCpLSqsBbYdjIZc
fSkvH6YCA6opHSv0/cMftM9yytES2175ILpaTIBcOoMrpYgAl4GY5h9Kcx9YuD8+u6d4BI2OtVvR
YPjUlZAwF8O6oaZdZtQplCp/9FjG9V7egUxoRFLQtdG/4PP19u4Wg7ZexwixOEUKIAmqctH2p9pS
1qhE2N9JJwExfNoAQu2vk7nVm7Fsy/o1BJ0K5zzpOnjVE96AC0xoQMXOcArjzHzribkZcUKIEKjd
TxYs43X7nwtHzMi64493IgEp0IwLHq2cLiCjrN/oXPKVPg6L/U9sJh5U0NEfjNrSwH3ctNz1l7Uv
yV9aOXax7FUS5F60ogmv0BNqLMqqNf94dh7ojq1hgGi1mN44PnUWkWqNy0D/jRoLuH5kfimATiEd
kbymO63Q+Q8M2sA2F+fNwxrMy93QGqMt/u8IKqbD+bJrYKb94RDcDH2jG3iULKZ/0cytcrp7oVwN
pn/t7BJZXF8lZqQp5atLMtCHXb8nZ0Sqqzny+3EJW6RgTxR/trW8ZFvaE4liz2ir2vrg2tI+RHdd
1T/xzw01+VTSitKsZ4I40n5/naJ63mmNuqctou1PIes56hRVjmPub4R7CWKX1zLwlTiFzo3wJbK2
CJ9rtoYJJg0W2JCwU1Z0i+hKrKN0itCyGx8WtV6l1XIFj6OrDANx6nWayQgvzPHi73DDMTy0x2/2
HqBzfKRWJ+0X1Gij6EzbJUl+H8KGP222qHAs4SYHSQhkaex4SBsl44GnrO4HyAfXRanxNnrBXLMR
fhY0cuhJonwMHxbVQKu7bH8wLTGBxuv08mYqtp3r/i77Lm2XNevYUyPKF4hEEgjSTfKYsnmRfXJu
+QkYMSqYam46E5N5rrNmXB6IhdRrIPwBLlOpbvuJjkH2M/LstWdB/8C005k0n2PLL67F10K7F1OX
YjtkPQ/C1uYmdq4U/4gkNk1wV2BS2S8CO4cUem5Jj9GSDczK000ZN/W+lGWE2FaBLKTcIWJJF/+p
prAfqmQ6k11iekuSk/NSsivBOjd0eQyMAiP6lPAZ06rI9N0dDyhqOva2mV5VpSzLgaX8f2vFAX3F
QgoS7MYbfAdHKwBxIjSHPFwLEMytKGs/nx0QMDABsYX6f2TRknVvoyGYPsW44cdun04YDrLeqf+k
AzAI9mtuHzh7Y4OivpBGKNuU6cZh6vN/AKv30K8iVdHRcVjofb/jwt/YsOptWGV4vlMWPWnHsT/k
PSO9XF5n39h0OHS1xEwKpu8STNVqf6sHiAez8YXiEri62VnOhKlii99OdeB3LydthQs7HWkrNH4K
3N65NXQpcgdDTfn/WsX/CFrvq/06HIG439T30tcSHvve6yFj5bcervnJ0Y4hXtBaarS36ZaZlRG0
ORwwpiioNvDfJH4jX5+GZjmqQSOu01PPeGtzZz1LPYN1Db2///fOVgU9D0ZVUf78HZqrhPZu47Bx
p8SK0OJ9IC0OtJnj4l+/8Jl99/9MqlqUZXVnlmLKuwboCaBJFYxywol31IaThiuYzcxcvza3ihai
1aU16qxlxiGQH+5FFXMM2dxv8jbDTqSBizRvlF77U9VTXwrS3mk6HtzkRVn7GOBtsMjH87K1EAi5
WHEZcKXAJuM1mCKOYHfPrdZQHvSGe2Vu3RKkNgnrdxF5COa6LAdPE2C4KRbsLCJylbVz9Ti5Bseq
DaDZZtCVZ5rPvo24URyhiVkxTD7wtoviJmqS+H1KnJY2u8pDBJIxEcbQmekZDhk+Rk+vyzK4QqLV
kFLO46gO8AwyNBA6lwAIHhrP0IuaMQeC/IKj6Hi/Pzkb6gVCJ4nCZw47rWCIlPX62ujse5y/dZCZ
SjFIJvsRrHjfzC8nRpr3NODpkQzt4UEah6n8ylkjw5QgLnaWlSP48H/b3C81qj6h+Ttcwp+ydPx6
djXEXM/URWD694zDr59ZGocJLM7NxUmXkY3WQuDuaSyccuvCyY1vnLe117dBFp7RMzZupXwrWd8i
Jmsm6aCZ/94I68YraRe+h3h9eCZUYTRUOjnE394NXKH4qet+s6IP9+zrk8QbhNKNb5X6pY1YyDme
S06gkRAVKB4OZ/dZLDGKK+KJKdB1xAxsvSOOamCknG73knfB8MgM2Sef0BTlVP5tKpy8UBiXa5+n
YrOPNGw35QdXZ985t0g6Q1cOVdrM7xvcfyCmeZ/NXWjcS/tFjn95ICA3jyX+Pt7YFq5oETDLGOmy
nJMyHDCPeQWMEXTH3dx0IJ/zqgSJwW1BG5SuygUFU3HYSzmWQrNd6gs0e92owI2OdXh/Caus84aQ
nwU32UeaRKoAT3zjgmBac7j43R890ksh5+jx0rM/7maYSZ3gLpcdDgKzGJuQ3x/aT1gXBpSmEMur
lkOA7JZxyqvMEsrbwf4RuAKo1oe4jOb2FDMgoySzu88ZOyIUhUX2EDU66+w4h5Aj0aY/Vnrec3pc
enzs8aSTHiCKDhfiG3ogJTMZ1lzhZVeWRSPZvWOsuhgDpGM81WmeG71dNV5G/B82MkFj+nqVh1UT
J8dkziD0OJkhTrW3iknQWbH1VWHBWOn4WQ0ywSwDlPb/e2K9wqJ45pozwiB8Xpift4rjN3IAY92y
W9mySFBaqBQPOGV8u2Xi0BDgG8U/3rU9RyzzVnswL2XVMugoM3lMAiq1rlXtpLPTIhA7L0Pqwtfg
gvMva+/RFViC9Z/HLI4Tnk+aTpzwg9X1mEwWUkW4cQj3ZqfMZpphGMeNh2ElMu46mKTzW0xBsYKj
lXymcRchkT+8nn6IIbkXfz7j1jPpg5dhXbhzbuATg83upIgcPuoGZEUm8kYweLNygG+UUeQ+ILmj
/+XrnJt6gJKfjrKdsPE7vUFt16ijFpWU8Al9UOSTDwqrLo1tB8AxA36s29mt9tvYEpo4rHh9bnec
wxJbpdZaSMHW1sLFxt1/E+zVJnGUvsw/S2at4pO4BdhWV4qU89GjznxdI7WLowPLj/zbtL+GHc04
SYu7S0CObR6rnX2We/B0xfddNIfTAsOGAxeqDcvSoytiaRH9NyxdMQhdSXVH/WUF9m0rbE5BSdm6
Ln9DCT8WQQUrZAPkI0919DjBT7RyQXehGttXSh0fWGbAfTMm44K5rz7Msggw2lJ3AULsKg9+8oM+
FjZOkCCZYi3VECYAeL7quWw/QlU1XD7pt9147TU5XaVRB6uE7LI+AjzAFNGnlpk9e7ZtvHFl6S5q
gdycVN7GXdcjSRcOcjXXrzpv0fYoFCzYoyJKenm2lWGHmTx9UTrPS/6U0w6ZylgA7v9DSee9Lvrv
dmFCERDfRM5wrnVpTbq0Pxoyruhh8uV2jAMcKm8OfFnwEO5k32dUgbZsoUtjL4wBu7NG+RoSHBNa
UBV+CynaOCVpO3pH9fEDJWZENuM2DgRRs1Yma6klIoGOIwrgP/gFc2u4DrZlf07QkZyAHBVUQsSp
et2soU8aQc8njfpFszGJCLYnC9ynRXrDr07tMw+knvIr5YWJeaZ6L4jYSjf/B3NkgwOP37sGJVSV
LDSkG0gZOHD2Webl6BlfiWHcfLyuQR2Qg+0kEnWh/x2ynnjzS3fb1V2+VcUKuhxo8lPMucji981v
T9aBDlYL/CvpO6M7w+Vanh2RyoL9FbTGYnuraEautzjY3JMy2nFJI0MhRli5Q3jLlWT42BuRZykE
thd41tyhqm/9Lzi9/y8nDfJtETFNEZbaxkzfIHQ2imwObJ6MXBP+wuSvjfmrb6qUIbzqNFYvju38
wgXUZHWfOiETlLoM50sdTfnN3LbcDt/cAWeh9cLbRsJszpFXWJFINB7/vFU58PgVHcBrQ7l3NtRD
2sdOhWQFWqPdJYo7jgb6mmdLQCzVxHZXv0BEhPJWZNDWACN8ZwMu4r9zBEqRygQxCU/H7ANsez+Z
oiihjJycI2UIGfAxW7yQDfhVtJTfACHwPaA+MDmwtXIAAerNpbUaZWh96imOqra1Mj2kcOMq4DAr
cGKLiAUJ4+Tbas8dKcGjprlnSM9onHGfMdBA6EufeFRqrJLQbs7RmX2V/KVn1MAguoU0CvJVk23g
cH254VQupL+dzad8havEmvuBwnrKJn9BYC/UAN6OrjlNxtxDVhPu0ZbBfMczJp+63EuiPBXOUiH0
4wC91qcUbiQwoK3UOwIsA9eRc/SlVnXLrK5LdJsUdWzWoprGgaL7hIi2Plewe6ciUN5Gnt6q8Vm1
vCdQTFpb9d48sr0n6fRRasbFnuzTLruAH0NB5rvrj3mJwsveVupsxPkktLJjaK2DTHrDjKDMIIr5
TBiat/WzBUY82gtP28jN3j6w9Tq/sfTM67VQZ2iisA4SaorAEhlAdmYfrwQ886aZ/PBPDuxOa5hA
r1T6ojIRi1fI4ecuMWs8d73W6SuCu2RGv2KMww4qmeyGxiniRSswxtNeZf39VhHS9IJjGCh1tJIU
nfx8GPey5tZa1ABuXizf0sEearClZiBVHGglbyUfQuNFPLQ3ToOLGlFDZ7+OBNZH0iRbUQ9K2qdj
DwU31Oz+Xp6OgLWwTfYL2FBwabo3rCCIHawmbvsEvECrvfF9CVOc4hHeELRKlQeSFPtIo2JmbCyb
Sgf4trZzC4ZRC/vKQEdN1SGWeZv7SbOkKHmkUuCSMW6Ljbiz24kpnAQwuB9s3VjvDHc6b7seD7Fn
GEYabl/lLkbv4HHg6Jyr0Sk2d0rD35Nk5B9abEyw9OyP23FgGuW28aYueQYbZkUkNNZoAj1KfJgc
+oYbAqnQvjM1IjmXMjGY2ARS303h/U1jdYztw0LLT32Wko+HZcoMv/nQZWSOzYwrt4K7sXV2ezf4
neQJH7++dGUgTzLXeaw4hiRuY9ZsGIxYqc9DJlHQ/F1ypyQ/Q+N9rTHTBxp5bTpJguJXo9PEJU4S
p7268xx+AOTKo0AI+DcPMWbdtSrjZKF5gRFdJb7rIOhAJ0OKy4FZfwKc7bQgyc8dWGCEYDbNQjqm
ZMww6oiBxxSre3Tmeyxs1FWRln8XKV3ZgGe6PkImE+41L5K8ooCYWMTet7tajyXuuZiLIs9Fn5io
OwktPocAn4Uyc0I6wuMD0OKvTWmnJKvmCl/INYYoaGSTZXRGM6VvvMyFbmGkH2rezqLoh+efZTUj
+qCqh5OPwnVYoj0CpS5PSdo5WHlOVVgsDQZSdtPq8fCVkN5S9Spvj9vJGrdGxifWZQCyIxprMLku
OA7J/2/arfOwnmttBGAflDcIFGWXf64OnG27PWlaMzajAnNTC4aHZ4n1aDoM8j/NIb+LfihuKN2c
1+U+iSzIJkSDcNJ9Ma1w5Nz0y3x8fAzVJc6KFZeGAqdcLI3IU71XEFxjAV3CSTDmFY7/7hi/Ppl/
WwLVhQ4+xi+Qr+2fCRxUMeI4MkzosN969mTGKKwA8teC7R604F+x4uBR8SUsByIs2tOHf6bbcuVy
GE/eMRzSRr85W+lPln3OyZHaNPFp4mgUFv2/ViNpkawaQlGHXhkiZ8koBUbCHprgopYuKx0zXzQN
uaLosILQ+alKexWqqdLq+GcsoaiICIEGCxiC2v5or33K0PcYVRE/nXi/hGG3a0lSQOobskkwP4ml
XGHH+IIQUA2/FE2RTXdr281EE0onKyr5mqSe34TMoPh6gObMJWqZRihlCCM3yWG0QDUL/DFtGLtF
T9Kt/yWuW8bx6uKgv8yhIR320yaCY4cXR5us9+7iK88gpRZd1NtgFEYFREylZsCnmZU6EqICGHn7
InllvU4qDON9rpk+grHHkblZC+H6qEnCTZAOaESJIu0QZNw3xLHDdGks+LIanCL6pTCl5YluTocQ
gdXd/KF4j55nw4R2QCl2MjtwHU34I2Fw9iOdP1f7kZUSH2ISSiYrhER+GPn7fm5UHwOvuL2MIUbg
FixsnzYUf9tUCssO0huvkgTe9/ikNQOvml9eud8EoAgAhXJOdNI3LMadSSkOp2sbY1Iwis4qXKuL
qqiwzUtmgaXH3CSIitgEVwpJLL34iFM/nYnvZCY4JHC7VOqJYclUS+/bAnAQZVyOrwraQYMX4ZCF
/QzkNIg1VxmucFu9UsDHrS+GZ1qby6G7E8+yVh0EXJZyxLRbfKevfqyPvwVCTmQwcVueb2joasX5
KQW8s1wbOOr5mTrte9ATpQOgk/5uyevZ1H7BTKq5FIb7ElXBm2NApkuFyPv311CM6d+c9XkYqprd
JMJ6ty1G7bqvkJjRVbOcM6tDjwIUtk3116Rt6UmDULa2ijShwpZPC84K5a1h5vfOinWuhd1RtPgU
4KsyDaVHamxJqP9XjcRtMIYDKNV3o3zUshyQJ8INRpNu3rJms5lgJJOs4hIWc28ENGjcgcr0ascQ
jhnVAeowzpisei9v8kUnsctDOvkJRnSyMNTRb5fKhk8JJv2q2wwpNO34ZzcmHdZrgL1C4XWAf2Ko
Qpf2CoiDjpo15Sxsa5CERK3SNBSgLlnIHWP6JOum3/ytVr2N/a9cdMt5F7xwXExjvH4tPZJ60+Xs
VTTJUlfAi5pizQ8HuxwZ06PQgNpHrt2UGGHMrXnnjGR58Eu8L2vEGdjYwxA2r6/pGHEqjH3ftTjX
Mj+J38T1gmqT4A3N9rKAjYO3gh14WPmOLG5KifF3ldnRO2Wq9DR94+EcKTUx2OZ1Zx3iNgRKmUF5
DHpLhEt99UOqjEH5c1YXrPiIs9NvdDXgRZM+CmsjcJtqq4KHrunUpaCPYDlGd61/F/R+iAPXDoQf
6KVI516gj3+5KaRJsYo4N9UreD51vyPQx58aCGVgbFMm3i2qLyvziVQIIij2Pjqae5apTNlFbxDk
6oqockoX54pMlAuTzsOLPl+KuJZMmZVo4o7wOKGJPlxt6x1o37yxFkibi4wmhTRC+DM0jq1iyvZ/
wlHjYzWQ8FAMbLjabTD8xBOacuYLKEqhye65CWkgOOpVG6znlxylODp6zCHmiI8ycVpcfqOflzxq
K6qQ1ulpng6/IhT9BRrxI2BKXWW/fYvX26/VI8uEEwVETl1rtBKV6sKP9yeql1uz27WpYy+QrzCv
hCqEXDNgSRm4eK1Uq69zlsnNO11m2iSvOWipWXQIiDQ/902BMNsc2cLi6aJyzwP2NTjd+XK6ZFAA
eQ+wju9dSjVM9NvQ9c1d4iKpAWq7OYBUvZ9JaomNGqivHiBJQXjzkArL2fJYYb7OgjGz8wfdeHus
6/PlIHyimXzwXzA3SUeCNxLie9NnHADPw4Kg61AxkY1IceFN2NuiP28o+S9gNpvOBFwPbhdbKUid
nYTkGtuk7t3uvH9+OArmkNNLhXAZcA+wOUqj40Vi00H0zJv029VI/0pT5X+5gJs4p0aMfe1noFID
HgIDwC/qw7TxkniX8xpS2G1bJPvw77svdLRgqz95qcvwMqV9kU/ek0KX2X9loUf11A7L/2TPNBF3
OuTmIxarEzD9QYdOuLWszrGpvQKfL93PJROSxlqt1ZwazkUSHxDYDqrhiosbH9LXbmB52+TszdiB
bDUlFVH3ducWOX2F+kfwRz4yfVO31SdbLcA+eBiDLdr9e+G8AuL8celeRMYgZ81pE8n2PWoG24B4
8XjjknNj6aDtbvnv8pW90Z5c3/9JiwUfkW7lAsPREyT8Oe1SSzVd6M22Ow4RDJQM/1bfwE7vzLEU
/Iy8CFqmzKLYcsP5fnhlc5KUlCSFjlZYEdARNyBOS7tP/b0EktRYAUR4WwY+8QPo9X+ejPEGdwRy
l/+uJA6WGLK3JX18EhYbXnhhy3ODHiU0RMzpcrJU2aH4A9zvk8Y8LiNNBiJ7e1aCWUBuin3eTAJm
eMW9cLCuRR7TuPMOLjwa77wEOPYKj/AcgpMj0VsPIyZWou/XVSnZlqf5D5IA1WX601whSeINcjZc
TS2PnxvUTSArUfyv+iaZNcPahfdUnmRqoWpqnDYOao6sYHTCvVrZLKHhyapBRSUdEOQliOk2q/+C
CbCNl/bfv163EVMBhB8CbsTSbf4ROOTeTLo7251qvLCOCi15q94/dtzTOy1lfmn0nz8e3gHwD6yE
ftqefIP8dV3gHnlysdHQkx5Q0DqFPmJILIACATe0a42Hw8B5Rrhdcza0p88rMmLqM6fIdy0Hpv+I
j00lbOnNGqg1QIuZdqzHY3v4SJPHFkl9Z3r/XOi2Z8eUME4bT/Tku/0cABDs1n4Jq+02qNT+bIRU
uz3d1IXd3b5caq/V2ln/Tfewg5d4DkG5TvPs5+Mi8Pa0eZsDe3TLi2zUY1iTU/zZY+8jpQCABldK
9ipN2X5LzF21IYiOtITq/GA7p6WcQclb75wbc7ZtAF6+IGhxsDnPmYWOLqXVYtoJY6HgewVKUGyU
gQmMPS0eE5VjtURcLnBUupQFO1m4MQG9ie08vZF1beV+MvT0TfBdsxhtAmQ0YR1kFOZwKolFQCh1
pM2B7y84cUU4/AwxermQRWOA6lk3F1wTXrD63zoG6WEGn0dZIWHApK5K/uENLBQ1q/NUP2r7+OA/
JoHNjTaZRLQFG4wA3NdERy8Yy6kAQGBBDAgveTsUn9+BshrAttOZ6+1RF+FUjYwtf9FgbSdpRHMP
FS2pjGRa3syJUrENRMmtaFatl6jIM1JdjEbfA7/Y9aawVuwZm+UCbqEcLIMeMI1PFMVbfvqFjPcU
jTAvNsl1M7w+YX21NAtiiEAMUCxfxJn0ZYa0cwmLwF4lV6ODOgvOQ56E0ztiYyVCXm4DFxXq9K5w
1s1gxb2Q+/WaJQkEl89B78juVYkZm8F8nTcZxWA1XUp3U4VjGDqtJhwick0lO3bmHqjslCQ2Ol2c
Cpp3KAgL66KkGL9j7e7Xqvqf/PU+aeFMQjN5Qm9H8+Fzgb00X0MfTc665duNSs/o+ZKR4AIaKN4J
ndIEJ8hPm+p6UJzbRCGlpfCIomjvww1KtKSUnbO1em3xM4D8/vfHd3gBI7lbjh3OWp5x1y29tZ+w
fqbUPyABZ3uF+uUzvNvQTIUAWmd2WT+xeRaJHbq+STob4iW9rdc1pvGNKqgPNmhsLnl5TWN2IyFg
LYal9oS8ypTcg+Ch6MDBU9/Xz9Z1gPtNXuuZDzd38Oms32Ukn0D682zgl/QcdPeWvsTGTF3ftLPj
kGcrbsNHrqCB85R5vgC9pbzmKTpZqwqdSYDibD4RLoZ8/n0Ssyvy64m6/AyipmBVRojJz1SiFCiw
6JAOLpGIUHPheba6Vw3ELph0Zx7H+XM6SUkX71AL8VStYXuvz6pEuYTpUve2cstY2m1v21aH+ZRB
X8Hf4b52ELJPl8vYZz3XGYCsk/DNSvxxhL38RzLNOQGStteUQl+49qnO9q5sxYihQEiLyn2VYDIB
ikPTafnjnuJvU/ZDhPFVxs8byz77HzhgpAcEY3D8f2WTIJ5TKcqc022LZPRjN5iSD42ULh0K9Zuu
R6jiVJxeVJoEy71Zs2CwKLz1T7iATtTZdmPWpRw69uD3um59vKiVVEY+Rhbhwmq5y7u4jICloCST
gHxnxT81oXc8GOw7hGvQJIqG1/pxtct/hfSktiiKuEHNWFqvq8HmuR7QFxopyfsDXBAJSoy6NNXz
T8wbCcu9bCAJzQmE41Iq8Ykh+i6SIKJdxxVfdWcA72DIFEtzLy6Va7XYeqn2cGFz08yVGuMRQQMa
jqxjea6U1NAqPowj5Xbcieyii4TlHN/Tave3U7rB7ODDuECOrtLVliqwtu4SsMj+IzEYo9vEMYZ7
3yONeMh2blEgSlrFR5xq2ZX/zI0Nji8Y4CBX5TlTddLvmnsu5/AHSM3qGFjTPMOcCAfjCg9LoPF7
qg7NDq4LQfscGRkZpX60hmifl9pQSumnf89wSleSuyIebxj2aLpDQ0aOGdmrNZyMZ3W8rD8KowgN
AqvqIKdf0zs0RWJbNAlZl7rYCgEY4UxF5OC08H7R5NevOPdla7kFt0h3sT5KoCcqydcBEaUu0rn8
oVXDUfA4OTl1qwgCZLzQ2hssJwAohI/exfYs3jpzrD6no2PEskiB8cMF4oUSzV0rJx+ROaUK69rQ
XCpU9foekIHICQZ3wZVv7Y90o2m76aNx//j8D5yCsTPEo8zNFrsxP40T5G9JDrXwjRtPVbtgkY5N
pdXPlepnTX5ZvMwUF28lIq0CIfMyHmNd5TpkiLyd+c2Ck+8UOUaRDDbzwuONRbz04SINZzW95BGP
ngPS1AMIRWAGggznZiUy+1Lghl2AttTytk/TPsUN76oK8eNdbq+xrleC38AcIXYNkS5rdcs6Gq9W
87Ji68nVpWw5x5FMDSI7TNSHLqpF/b9Oiujs3QK3BcdjS1YnDXvmyhI4CcLHgMKkixzZmOHm0FcQ
O+/IWRJLgfuxmvOHMZPKNM/m0AdRPvqGXm8zU28TvR/Vg9npCTMuJsAkfkUGnnMHbQwr3aGk8Pr6
zl44lozregFOKGCnAqraPw9CX+lypr1RDiSCBlKxiMRj1K8akjHikJade87QlelUKKv35c9+LZaC
PnU4dtYz6p8DR01l3w6STxfWd5PZCCVPqPxrxzmwKuQOvV1+xskv+8KJXH2WiHHMI5rjYAS60kZW
SFJ4HL6NclypDsiz6Sxiq3AeA0O+TOOmr0uq3gedY8OYXiD9g7usUYR7noJPGcIVSLWUkUHTr3m1
Qnu03apP85npLkW/o+lQIl1lH8KWZfOzVL3Qi2j5mmkJxIs2hGsyGfWFSDgF/f/T0ZaAENiiQKF0
83Jv6sEfOXo/KqYMD6033kgXSDoIk5XS8LMd58UABesIyDaf7chpvTDMSYTebkZPxgqugNuQa0ip
0o6CX7RJwdxj2YLG+Lh/MdIa8/sxiK5ZLa76u76l+r19LDi6pfmcz0Tbof2SqJfsQYZ+Qj8x9dlU
l/Hx77wuMleGFH3qWgxEJ4mV8IPoKu27klafT68R+4jUOleI00OIuRu6B2hjbRRHf7pTu8KkgkPf
mTm5UzVyeXRAhNN65Ib1BoicCmjpneUOXAAocp8oIn4B3IPJrdQUkecVo7HQ7Vb/ge7KeCih1o3g
KcyfUqkWuwOVMlijwVwwzXPoxz3AM/4n+KBMeYyGPHinLgaXwQIKhcSknUVqL28DfFe1kVzU0ySO
h1yeYpC8j4X082m9xdy3fgpdGraqkQHnoqTrhvr9jmr6wDmFEh3nUB5ZCkH+5P05szjz7x/XKdbr
BJ6U8BNzB4NYC8sFPeqQHh8alovzAYtuKFvBobgCX9ZG03asfL+w8N1toQR13pfqal6Nz77h6sdm
m2sdHAF1ovjJBQjfXU/R3Mu+4JJzBjs8OCku6WNwTtB7EOcznFJmbrYZFjGlhwDqpgQXRuh2wSAJ
/hMbRS1Sc0QgwIVjdDtUEAspr2E4mRk9TiHQA1gPg6TMhiMhSE4Q6w5L0AzI5oKsrStZ9jifsTb9
1CZpcSVrCK3ZZuopI2WV8opj4JSmp6o+Mzh5oMl0Iqp7y3y5T5qfkXJzfLhikj4MjxYaPdqX7t5Z
HrvJoJTOeeybiPwNWdE8pw0ZxqN+M38aAYSK9p9e9TTqVSfP6In7sAYqrORh/Zfkd+0B/YABRf2g
iyjyFRuPWnWy5BfD3MHpFm/Ploykt8Oq2nIxUzvk+R7kG1P3TMJOfycOxhhBvr6vBHywMOdWNr9n
XwUhYemqJa6mK2yRc8Try6eiE1ESuL/7V8gE1WD2zDQQwBTB8toSL2jgWDzHI86q2yl1xryzMi4z
Etb5a4bZY+8p7jPeWQ2SSxo1WuDZeogezHtXtxh2leQgs8TysRzpSx7J1/wWxsUnAoFAIW/h7V1h
ibwH7LeCQ9t3UDjReTbF7PQpJc4PfwgMbScFl8w+PdVBYjk4ZCOOLUKxoTVFz5D2t1ttUScWWMb/
QtSsVC+4jHMOYW8f2b61SjVfcDChKi8CR426COyfniv9U8LwNlnqnbvylcMy8YFjfAD9sHVuGijD
f2gDaT0mjaZdt/lEd0lJyOjr8ziPSH3cBtiQOXPNLd26itkbUVqlprJPtrLbpJvfvaaQFWyKZhwp
CvMjnPWLzphF2EZki24uYxNjcqKVS7nSNwm33ABrkTBpUxwghn4Aui8azOxKeZXFm0NKZequSyJO
y06nBtPi/9KzUrBegqKjXLAAjBnK4lWggfH57+fuGo4WWQViblgbVGRM/WDEEKhwfVKOvEUhT+uv
2Yvs3ylmZZk9u9vahZZYpGfAP8K3A9Zp9J/m5Fh9mM3fgP/INwBFEB88qCjjDGiTx/t9f+3euJ6G
2XsT9LD4rhLgryJA6UY8sjWBWji+uSoRwOLOnNpxnwIQDIiEvARfjOlIc83ehrrfcHBFH2SgtP7i
2mK6UInurAoB176YX2vac1P2eO1TU+8URepPfg+56KsWnPpKNFDVWN0f8T13jif8qRe3AhGwn/aK
YjMyTKQahFT/a5sQmANiWtkCwjRHKvR/y29H0PitWqd/NJpNJ8U6EUra59Iw54wAn/ni0p4GPcmd
juWKNog5Cee1jIrqJQoJoRnLi09/J9LZ1u08vdjmP6uLhD4gBz4nQrMCc+56zpxqDmCvkgRn+zSL
TtM01QGTW8vSpeNpfZriH9yHOCSPZtUwXRu8nQceLqfpzq61NvD9srajo94KXNzIzn+kb37WMhdh
YGSG41lgF3oHI1y2LghfGAR94PGYmxjUKaMgPzvFQjWV9DtUy+Kz9QAsRKbLvuz+jMTy1Tn1Ql3O
61UIE6fLhdHiYPMl8krmDzcbki86yjIF3XHiHhLnmFjAbfWHMWrpMI0c7kSSDg+4+YjZTh7h9D/5
z0db2GmZtO6qIR9CCiC6BC4itbel2oxYZ+bCWzXT88XaVqH89BPScsz1OLEM1LkXBRflnpKE42Ky
+5NR6w87H795k1ZMY056SpdNuh1Er+Y0C9qa8mLfvbjDJIhjlqGdnix8JuUMyukdGhFpMGZOKlP1
pJrPGOJILUui3bKOUYjNaekrF+uv9/bGxw/nCO4FXdfnFNscr8Xuizcat6AphR3pWVok1yBuDMGe
vWNW7nQPs7u2LTc6vPSdM3TT4seV2kp2xXmkCKCdcy68XSH015xeXFRAun0qmU6nhjIB44VsBgRo
ZuJM9isFHPM6wYpALmxEkjQeCbcDRRbl9Ar3rqaOKbVCO4yDXSV7rsIDjY7u9Skyp9eDYj74OHgT
adQtQcGi6IpTo11WQI9QoF8kRzICkiUKvNR4zlD/D/MyGmnnCV86FKbHoWMH/fwqGxbJNp6iNyvy
IyjQo7LJaWjkpso7KavzraAO0uRjPqfKNcr75AQ7BbGvsXS7i9AYmLGfMp8wpwmZKolWN9yaNCrH
hIVEuniY6B9D0D/dVNRIONNCV2/TRKs25AXJVFZHTQoasDhJtiLO0JocM8ha8COjfp3eE5DZ6oUj
hhw4p4hpB4VoqyXnq/Ws4PmbakkCWkZZiw2NDp1xrVNxzeSolg2THcB/zynFbSt16cNxPhe6lkrN
87b7uOxZMEPGRJ0tOLFahf4g9hJdF3ibYVZ//Y+PBxw2EGHuc1pfojAwh9QlC/cEs0+GaDxmufqS
p15ciBFQfMYDqkioOQ2dKziNRlAQOQTSCHlIHTvUm/69TPsJXEu6hDNfNMNFCPrLu5PzJVx+gAWo
1x5619F1w6glelwiQDlgP0rBVdqZSENYUKBWXM65gRhXJVwVinCdPWAkWWgQugb1P75tJRscVA71
iTTgsJYWbBPJsu+pZUdgkNo0ENcUwsTEoTqwg0dFYkKL+tRLy5XNr9m0g2twlFiHdeL50kqRC4Fs
eGK8D8p53A0YczYlLwy3z5db+oq7OEnrzLU8U+Ac9a77Dadg7lICedohRPuqdyk2gF8bGtNXiAP7
irteFldvnSWE3UMabj6oQ8lXDbPOHGGqMcEBB8rMsdzL35CSmmOdw4oFDfPxJOJJfXCbgi7HZMqL
0/LOpuDqc/rBSQROf0o5lH4sPZiE6yazCe2C2WJwYrIGkqwFH7ApZlDEX35zeMwUaY/M7MG1yi4T
GwidkrOWGgerCy6ZbfFG4uwLkLownnnxhDT58zpAgyVYOjVl/zvu4k4wD5fyHKlTXY+Ec0Phgikx
1FAthUKtvN39cCP3ndVQKrzLq/E4Yt5v1EB3Vw37bMOyKghR1Nz4Ij9/2c4fA3FykztsD1za8KGk
xpgVTNDw0SVg71A93fOKT/ocM3mrZj6trqDn7sap8at7rNb/kfx0KSjYUmNtQyIdnwWOmiBuKqTX
z28zl8gz62MMsAh+YnJkMresFB+CUD4FqKrkbBfPgSV5CsbrRlsnRCVrwB+NVBFuX5y3LxpkI9RY
zaA6TTWNGid3gst3yzn84YxbAoWAW6vG+nZaeVXS3rPZdBTTW5sDpyxncsPhLDplp9PdVWhz3Du2
QYkQ1I4dJPhhqv+ti779Iaa4IafCjP5KgRP4j5nZzrnt1Dt5hUElryRnujEugdOzTjjPmUoHYL6z
ex8RADWFufVQi9qsttDBMZY1MfEzveLFQ8LnQMdZyhiDLubbNscZhzW08SYCAfN4C4QAhkZkMKfc
SdKDhLfZRp6krYU5lnmWwmiNnIsJk5jwr2oAIPjrOphTYOzcg6abAzaZPJjCsUks+Jcj1PYWILci
RN5h9PkhW5eJp+Q5E3vRr3toNaCsrkvANCxXU+Th4X+XI0723L4qSrPxC2XyjTQcN0JuQ6O8bWvR
hGqAyNcT/w8lalFkzIID3txkdS/rtnfMww5oOSId5WktQoxjYV9pXkfRVOLImZzE5uj+aP+ELjTl
0Uq1Yv7nxCfRJyJBzJxiY2hbYI6jwYxxSHe8B52ee05YaC36+7v2KODznDUYlDms8NKGJUPdC7m3
UWFHZMRiteG8w7jX4qmV8UU+AHQTc5G0qUKwzywBL3VUjxKLtb/K/b2+/kwCEH3kPKsyOSqsgsCX
5GyKsYFq/g61ZJAMeoOV6UoiugvdjCdjN/HVIGNYxWbI3ECWk84Vim7k8pVL9GU1hMsPea1jktxf
9LSDmTc3F4UJjkHUn8/lvqDSfCA+f/EHRgbelKEBIcDirfl+V1+OB16m/29dGqi7TtpkQ50xIkln
y/9cxyV+B007MJZ7eDkElkvIZk8fIT+B3DJ1L4L8oljAdmVqgJNiF5jgZiUyvkx6jMfZZk19eA+B
3P9QUWjiNDav+LFLtbCnxyVxgx2KspxdASBC5fK8MHedcdK6fVCNi3C+KDk7jA9bpW3YXnDqiwlp
rfoKmkhImT34COSRAAFsLiZZWIJ4pKPmLIlBIPlhiJmfQe+BJZSDQ4d1TjbXgANHR34X9rvU072e
Y1U22JAkHvX2fCK390qAZGz/9YOJX4XKapT/PcNCLtGqdvMPBTiyumZUQawJ8shGxAG6TN1DrgF2
JzI0svFD98YS/1yEm3FGZknTwHlgN8a4v1UyHo5fbckPvWNmLwmAcNHoNdlf9y6GjTZ6y9mXKqFd
25TdK3/PTbiU0mv7Xb4qxCAVQbp2ihR88khHe6ojGi0Aj1aNyNZGYAWjd3FuTOToLTYGTRW5MpzR
LoBJxaomQ4CyGR0wva32g+/wK50T9P0b8gPxJSpchuhYikZ5MGEUiAgHUU9N2UAzwP1K4wj+enNL
ZpFwv/Fh6412GgZpL10de2ElfUJVAVsFtg4E55tI6EICESrKIoeS+RSUnM5XH6dKx6LqmnP1HO8g
qYaqatsO1UfS/Pa0KPoD1KlRNGtpVGJMudIlAyjdsr6tVXa02+tRzMb50P0Uq2Dch+JXvaxsdJYU
BOGqe8FvkyN5Owf9mlQR06W3GYf7M85K/dCBgJOCFtOB+cKeiYftwvLXvFRFEb2a5kV00zBw4Yx2
EcRwFEw9XwrcvV+i6w47RKryNA6y7TNoFiqpo3pq0W7941dAHzTZZWxAbk5VJdJuoAka9GXnIXtp
T1U7OvW5zbdXAYL6JFIolRC9V2oRkLth+oGmJaIU/1PgwdZbGKJuLoV9hrtnAE0JEbdx9mKztY60
yCbdBUDXinzvzfFATPH239gDhtuJfHljqJe7iyUgYFHh/kMyuxMHYTkiT6RgSAGDPiWUAeRwFp7R
ZgLlJKWjwJtcKw5aB+25PD4QuMzdAXpL5//R616NNSe9GK5T/dsicgnzus1qe5GCIqxyz7SihzAK
fYFs5/ErYpJgl/Ml2xCfClI/f0TzMZIWb6yGHA2K1Zh+kqy78V/OosDqozRmnTf4jtPzIaL+N8Vi
Fu/ewYoZZ1Wnlr6TgFe6jznmWWzDTUj/AgsLYWz0KMikc04R1jLTh/0xARFV+nzrmU8uila8I/Au
lG3amLojrQfpaib8S/lqxjM/Wq2XtbMeTQh81eCVnzZaCfybQSeVS45L1FPVKc4xxhzmTS6C0clz
cqG7X05voQm+U7Mt/ODpjTUMDL61rAtAV7Mm0nB7/wpEuhFAxiL2LG5WCqVPtI4i1BKqS34rQSkz
q9ppvXZcMHCRFYpZqUPq66IUd3Cs6pVjguhQGhNQWUZyg0mnw/ml5u4e6FaDrf/PumTDasBtXYe8
lXbZFGvraFtJKFli/Q5a7a6Q+NxruIb+oTzEe7O8REmOe9tulg9GdH+G9ABhPSthq2XC9XUpGGMp
SJMSg1+IcXEY/vjg1yfWYGJt2/ZY7klIk7+SC9wiJag+6Mt2BElk8F9q4ZLCVlTjSHusJzjFv4dc
aJaSklt4jz9NvpdXiBA/s0Qm7nVppaEK41VXzGcFxLhQ+9YMjYTlFQ4748yX9BCLlWmGbJT+s+qu
oSv1a8CR+BmlYa0odvcRIduVBBGSybJZ+kkm166WIQfYcjwnZ4cfMPnFJprGvqCGm5QmiRErd5JQ
FBkwfJz51F+XhIpUyxcveZRlpWdPi+1M6h0KpbwnCcXo55NrnhAPxJ3NNjNz96jhIccL87CeAQH/
v9+p+hpP7/kK4vqTEbuHJtBoNxPmhl7Cd9RyHX3JesVqYzfqik8DoP+mQ3skpj29AjogRPdv+qpf
Gs+c54GR99LQAUscQsUWUcC+GAJHuqFgdXI/uH8k5mmgzIyyoVS/6J9MnziQ0ec0xoh/scCl+6TG
sBeczZlUbhgHIouPUTAMN7DO/PS5zZnMLIfS+JBBPwqgdKkBVcOPQ6rwiHrUm8Sy73/ae+dMDSlQ
As01yCwhpdb+VTfFt5D0H2+ITTDRgkTV23pD7E+oICVhvPbCl5zHJUFe/5nqYRlxbYsDB2cNPuIA
4rRa0QhPXLcq6pA5JQYAtbVgvqi4hMV9fiDB370IEVFp4liDKH2NlVHyz09d8ubH4wz8f4jG58TQ
lWxBY2PmcXpW4VbNP5fhV7FqU5cO/OG1jJ1lE1mkwpKmokhaJz2H/CyAPS4Vk1hG77O6+UCQV1Vl
bnM80Jn3XniveHUqjnmuCSP+1+Zpmhx0iRZMS9R8C0Z45UozxmC/1J2Enjmm25ArSEX5F5TWGZKi
1cZSdvqj49+R0q1WxIRjBOHHoYMjrVSawGxMYOtt8qi/epgGJOm6j1nOACgv3GnShjUnyiiavuGP
2q6zhx8+z5ESX7JHVeqqivQSLi/tcYnnu4BeYmNk/fYt+f+9FBaR5WLaPSebQOMGYrKE7YVy4UWj
gTmgcUCDRYVCGmu4N2kPziv8SKGwGlRlu1EJlaFcWtQMTV8Jk+P5zGvlmY5AEEobf1w47S4WA43p
/D0HHehFcUBa2Y6X5960Uxx+IJkaXvGhTZQUawioZrqQGnDUz0k3/q/PRwoyFXLCJolXX2gzyBcF
CYzQllyxP97mWJEG6Btkl0NmlPQGOw0FX/huyzryQj4/Nr9KvZFbsPUcM1Fb04U2ffFvIwndPZJ1
PzZU1cZELz/ckg3ojeAKcIvvfIzVxXn7C0wD2Bnmeoh8xgJKmEZD4BVqjKK+wURU9nU3hrF9+R/w
SBsgknAnARhIu/eyCnRt0TDCcha0wzmSma2OGh8Aw61acAFpwHTdjBD19gsE31BkKdV9Ey1FyeKL
X5Ooae9iS10WeimTDWUI49Uo112F8IypGVczKixdHcx1g5Tg7msBQY9XYmarxkp7qz0gTrkcFFt5
Rh+Vz/XmVlnBcZu5knXaIaAnOlGQ7uYDw6QgU49ky2kdYRo8JI0ZFrJ18U97uwGY8AxNMEtHS1xH
ve7pkTTwH5SAxSl2NCNOKpLhkVxNNBo+UPNXyz6EuCceotTPAiXKjkc1TrEarHOGitZr4+OA+0da
I+5NxxqG04Ws/aRO1QE89HcFuNY8NcaE0Q8ZVDQpRnQ8fOweFs0ur5xptk3ue8LzpeoBpwck1qly
R2TCVFWXQzb/hFkMcQZsVhP4c/gogZMmrG0tlUHwnHsNAnct5gDe2QMjQY3BPDi3o+eu+mRHITRH
mJTx4JBJOgySZw9pWwjC5fzRA5d/++km3cEiM1QTx2jhbzn9V2s69xGff2wD2GH3ot+9mswacDo0
96HaHQeGg/N0JZq2wFphuiXz4KOEvjlDz9M/RNlUiFPkH82rdYBjcYZsh86TMxQT0A1Xe4tqNtyT
JetKgPngBeu1zgrbNXjTgeqdyjCqUbupTy2rxx4oDVvqDaJ/MJZU0mJCcBWyswbt1GSUx0JaD7cl
0+hO6qAImp2QlXKMuvp5F2aGEnTSD3LpZYGu/4NCWTVJIGljj9SCI9AAiLviLj2BikBZMXCY+07R
qC+5F5irpGzd2ZHinLw4A100EhE8C2HLi8w2ywDQrdDfLleZunrMf/nz+qV95/DJc/+bX+b1o3jz
5svZUsA+G3GqgpCAX6FIWeSuXfgQz+OYkCrMsfLm00+IAg39T75a5jeV5YPn8m8YDbl07ciqezH0
CwCruK9VhxCKyMuqKZqQjpcdHs1IusrG7k3FGKIlkq/APFrweMFbar12gTC40TFyy1oGmPlGAVRY
2fS8BIgHABYl4rKHzvR6McXjJFb+YBPWfAA0VTyvTHN3e8jd2oqH6aESD7lOqwnSPhcaDkibkyiA
eSBlOg1hYBrU7dTjmXDPc/+Tm92yyqZS3/cwo1GsuRgurMA50FAGQ16DL7eKMqIue5FcbZ/T5bIK
G29UIYSkLHLwDyE2WHflWoszZ2nnaaQm8sEFT7nqTYR44DpAqyg4HfGnx+bS22cq+sysErLDZVjN
FAwyeMSApCKWEN36MdE4kSUgPiF7UWZjQX4N3eHrZ5x7nu3oFwkMaiSJhd3627WURTacWDczJAV1
BnqqpHnNs8DU/ONwoq3Yieb7Ke8KfGnxmJLXjkNDCRiedRDCsoBxpxXGb34p3+eMMz6yzxHurjCW
o8tj8mXKtBP5VeGaB/HhzZ01Z3NMgQBsEfQ16fwUZ+ZcaVoqtKpPzT/HoS36UrZzQkVIpEEvww8g
/7iYYZEKbsybmWqnswk3I6YctxjDO2Y8OP3bUovxVYNphN2b8ye7s3klkGXeYvJrtWysfrmxEApH
7qGt2XSDYfWABKhKvqIu5AjUD37msCGDIn4RPmiFsc+Ul8NCCmOm8/dLWahB4bbDt5+ReL+ajG0R
ZSdT+1XdbrkrYXbyFfJrBh1AYHmae75cGVQ/CV+HyH/b7VmZBOAyu3mQIjIQ+9Sntb04xC8iDpvY
hRBN7aYXEWYPZQKuQfwPhHm+QoIRXBaMSXeQ4CcpplxgCtvP5NFSikYMegLIHUq7yQQP6NlEz5Db
LEUxdAIio3uaxZe0dVt9F7DKWDTBafWphJSFObtjWBHo5sBBeHXGo+oVXxTWb9YR6mTrmqlsoRFa
mWnu7mgz3aXn3Ab2d7Q6FbwJjGb+wqrrnct+Do/S7dZaxMl/jJyRvBD85sxf3KYfypjIT1n8LKgR
WoPOfLvAViw9lf5K0/mHZ9qsdlcGkDAugJpWjmdEfo7ZcLUfkEhf7oBK9VgzSTk1OHdhjq45iStq
Sez55M0qON8jmalewSD3Tpa1GCgwLW3N0yz8d5Vz6QqxvAqKVPVwLn4CFidkns298yRjd6awB68x
r+em1ASgGdKYCav1HyR3dO8bTgD/rpyZkfwcuni7JKNBjRlrWUM3WaociZwXXmgC1sIIuLZQatUO
QIpSog97NObzLBfsi8Vy6ukpjILgqSd5JE5yxA1M2kGHd+PBuLYr3sX/NLoPoDVHn17Wn303sT4L
yEL5+08cB9UFEKPuC9dpjZMQABYREHUgIBVpx79JvFP/hc3a13aZFaH10YBTZ/q6SRg6elFe5xHf
1EKdoKcJa6qMhoFbmNpHsOtUK/KATEHIVGRKlE0FOUxlkFiFtbC2t30aLzBv4gyamYQ7QN5ORJOH
PIMDWBo/dcfPWzlRwCObEdQjaUJ0g8pKPfd4H4emjzVdeH7cE6qtcg6tvGGTpmnLxAfg28DVQiGP
v2UPpQzse/0vygxYufiNHMIxTob8EQs7Cn/bY4Lw4Jw7cV7+7BoSI9bSCOunWjV8tgZplUX/EeFg
Jhrgjp/XBWOuAT5VvR6NI19+mNBRKl6NOe1Ha4EA+M/mcfAbCvusCPdibLMV/RcPd9J7f2n7VJE5
nNfRvrC/6g8b++vtLnouyN/bFiWf+f7CzJ8jw7fmBpBNXpe4KsZ0yHbpL1czzFGtI9DPwBKcsofR
rwSBZi9jNvPMaH6j6Nubm3jZ/0E9GkiRrQBRDVrO2rxA5cQ9whsk4e3jdGv5nFu6NYx3YX/VHtWP
88UOK0IsCJtx0ZE1hnG/koMjT0ElcQUpXVyxB3GKYm3TBE37DoqJGvHOZXCN3K19Uel0jJ4jJek5
gDklouLJlqpzyx4YUtP1nLpBeORLVPEBsh51byth2z3YQJHyYsuEvLSyJkiVqzFiTMT726eF5Q/Q
1xpFj4+BjixHtjTg23dYFa4eSDFZ7F/eiIe3g8I+OTf6V3kvUVjCV+NmE1OLgPhw9HIxa606OwIh
sWmTuYU2oltMauHvwmN7qbsRSnpcr0dk1oiIStC8jorWV9XpPU98dHX1Xt6CPDorhagxtL0a3OOz
pE19tjsZOBzQ8EjAtd7FBvkePkw0rGMCdoLkDTfpDLQJNIR/TBUbNJVY9vNMdbUxKElSb6u6oKbP
Sosj56unKP5rYH3ay94P7hZ3hSS+9MUbN7lLFcU3ushudeS0lROiFHV6I2vOU/5erUWw2Zhevl8w
IG2B//4k+JktLsXj6F/UAc5EXde4lWHyq3QZlq/9Sa2OKTrGply2rLFItrP5VQ4TcLyE46WET5cK
9S/4vjpqX4Aoinr2pwk0ijiBvlXjXFs4r7YkgSZotDF+6h+tmoSdwK0z6AMBiY55YKiEmXkjgYf2
6+R+HJB8HpgBgN45Q2e+Y0Os2ckPYzBBLC95cmSrleTzIqoSowms3nycl3zT/xKM86VEFj+mJ2sB
icJi7/ocG7kAeHEWMie13n2tBJXNGweNxEZMxpyHZhDYprjiJsLJFUzQlGh+ZDnoDs41oxJSFrlw
17D8/13BU5Kew/aHnBmZdOjTdTO1fFK24buN1nbTs1mmYT/yxPZ2UFdM7O9+PNGHe34Zg3RUaTo/
H5oHnu+S5mJAvEopOeVsg673hbYI24nb2v+igvcodJEQtoF/6ubU2v6kscrRvSKIKgX8aqSrCz3i
AiXdFU6c1RAmwolw+03vUrOYMYR1iUCIbRSEA/w6NYGeydmJRydysuGVCAydJGKZkFii7T4iae0y
7jdx0eLGCCMjeAxFpF2tV6aiVFMkQOewfS9xE5lF5S5OuD0Uf0OsP7UaRyI0BTnXxG09FpKruvz2
EidMUBkxp5uKXy9qQowqvLYgq7SWjvI++qh0xlDaQi8nihwRoSeG032IIzAd4ypVlmHAaLyNrtlT
d29lqAXnqVCXKyk5lxKmR919QaPMCghR94X7pQkPwjicWExXN31v8alcYTpy1IVC1u54PZ7cX/nw
Lup0WqB/2PaG4K3f3XfbbdR+3hwDtUi9YDhjpaHXoxy0lUYPZktjHi6NmxfIdhCdHVXgg8RNqLmz
h02iXz4uKJB9UnsL0gAfqBDTGKRN0OFHkOt7GXYm3f4AAzZ2GCD+Uild1JQjIZS7EclAhNMFzCZT
nUeudxG7rFf1quGANCmIIBiWb40Ynq586NZwr96JJIliwNISvWEfpCRga9Tdha3mgWVS7qbLEy72
XquGWLvILelTKhAG/cf6x9+BHydj2h0kR94rzZHWVOzriqDy4JwUVLtoNKznAuQqMwq4+JidPR/g
23GRizYn1LiU0m1qbSn1XvwE+Da0LipJX+iF+uS6QGPJ/Ls7xJauO/VKOm9ocucaW5C9qG0TZHgV
SPXZffGDcBJrpkdkrqJusHjgDVhzfIQ2j13SIPIw6Q2Dg/EGk3FDw2NDcY1kTnQ/50Z7z3jk5WfQ
hIoXoj3L43AZ0xH8NVEBJHwzT3YYnG0pA8j/HIRkOMPXPxz41QyshPYcRS/Sh1lmyTP9o4riFfOA
Xq/VbfkdpNAxACCgGzbfSvOvQBxiVgxNSQCw1ASY+1v6AuYduzBTED0QeQE2uc0xNzenFfQbPX9E
GtT6vbyxu8rU4Km/n2wMzoxjQnP9n9vC3cJjSYpN6nmyIgjZM2I63BGFlVT9rSXyAKBSsKCnJkya
apZHnRTgPbpBJ41pERCP1jB0moSjQaV+BmL6pd3P9twSocvXQYi/V1JAPdMSmN7YxXcfcAQ0uicE
jBHK81YhPjNujvoq2mi2k8KGa4/XcjsJfb4q3HUlYVJEZmRFqbF4hKyMRqDd4oKcAo3PzfnEMxiQ
I3QdFN6De5McNAzgh1O9kpGZB+v7W1gRULBLKSfMqKY78lqXHsUDR6L4lj6/j09TTKKjSyTUWFTf
BVxWTdW5ww2jJN/KfpZte1KTXgSUC5GLN0rOnH0KI0ey9bpJMrz4PI7VyX9LYMyDqLht8D8dVIpI
AF9DXL8U9KAiim6IKzli8YXFckFtYig7ANAYN0jgY3u+iSq5n08XmKa75nH6DWxVeLIomg51aKE3
4Kr3l4lVk7SwtxP8DOUlgtcarC0w0jTAJl7PuukkWmTC/PxX5AEKlBAoSVZ+JHA1GZ1Bl5Dzt/if
nlYrPY+s96cCzY8jychvUWVl2Atrxip8vwbEOK7758RQKhiwHfq+JyFHPgOrsx6dIuscWRXdJjbH
ljnL0mtwAeiJq0i6YUHjzr1Ih++DnwF/Z7nWAMBZUrKEhZ3wMYLeX+y6NUXWLmV2EZO5+0KQw6Yi
L0OMZSE9QuOd18ANFcSN8hzdSb444lrpBAtpZNCNkYmGcJf3e1+TK5ynUFwNkrW9Dv2h1uqcAGDj
v9sO8t0NYLkllO+8lQQU5LoscUHBCklDklA4mJ/Le0cdgr0j6gB8HpZBmCS7hg5EHddqCs13ve4C
xkwt2/nnRhapvmSK+f7G/mkzf0CYLrBU+YHKGb61TgV7oaOl6O3TERY7qjFAOjQFMG33F34eHflw
wvoG9NgFxMJ0LIG9r7ys4y71Gdss08mRqOrB8yanv2Dcy2BVzxVg+kzk34T9ysuk/3tzvsJdQnRi
0sIB6wst0FtspyMuTtMupKX6YyEP8Gc7xUrQuZq8XhiRsy2h6nXqXyQ+xPmude9sIPE78sEU15Ik
nbBNpIKFW8K5O4gk9vwtYRtfZLiB9P6BLrVoZDeL784aZgh9WwHGjIfSPCe2XeiTxThuM5sjF3/s
NXemEubwfwL29htRJlZEiQwlTzAkKSOADnupmJ9v23z5mev/0Put06Q+5YOdl8X9hefTtqC71A+6
CJZE7Dx4S4bq97W9tBxZAlOBRQLAq2EBHhiIHUFymYjDa2SBMqRHppTXOuowx8aY7qxUrgFiu6W7
E1Zurjp5OpZxiI7iEjGxITkaxMpqV64nRMJXg6ZWhDz4JwFC/spbC/yDCzIE8L4lzevhB59EfEeq
b+fV+wGkLVsSgr65Bt4tQopaz+brvQcepVmFEJBzRNUlOGTQlDor/OzF6peGL/0VqB2YxiosSaen
Cmpp4G4KXL/s+1qJi1vyf5a+QLo7MQq+bFMkKCQB79HxRu3OfJ4mvFxjzYaBlqPpbPOoRCbqugR1
xccIBNt6CRyKPOMHGbJVWHVwdBz7wscUC6rFceoVYIT0SROK59nUps1IvwvYOelBGEWzbNe2e0yG
pXQXsUF143tZxVucItpVIYzIhfmpMqxWq8XMD0TgTy51uDBWf27Ks8KoJm/2bjhE98HUANLGyf+a
bIsxxR3ofkO227Gf4Tsh/E2RfqdMeVTZYgMuwRGk6ietLQPU5ZUObBItTPDT9C4AXpNFxACX+Pzb
CZN6DNxE2702rV9jPIifJC7GqEvvT5yZjmKZ7IBtPgvVhBLT21rdwP5UzlnKB9sjpwtedBhBvPS3
oXr6ccEsafJtikmNPXtArV1hUvuwGVdpjfFfS9/NO3C21s3V+G23qgLVaG8trVZmHEHIFOfnm89C
QOC38HW3zJCskiCZFQm09eHjlFd6h2bjpz1XoI22/tK4DEEtc+EJCRy6c8tD+p+GB3xQ0pSTKynk
l/RpbmP4Bwfkfu8kUb8+tgEVwcsKtEK69EMtJE2fCwdqtWzuUC9wjijO1sfe/uzEDWKwq9y+8xd+
UM2RlDdLoJM7Fl1tx8nlM4WYUz46ODhcZipgUTuF3QL17BA2J5GaeCahJpEGf2A5cvyZ5Pw+xAsh
4mn77pv5DoiRCeRRCa2f0/9zWIPBebdBfF3UIit0ow9fPjOcM9UMoQBA9gWS1UmIGNnd0SzQUBaQ
ID8dlQCuu+XfvC9usd1u5TxERqstOY4uPZUOMG0nFldZ9FptJepA6aMINGaaY30zAYIrtf/fJhE/
09JDXLiCb1LPwmvwTIgYO1uuqOtjpkncbkXTJJJc25Klnle2Q+VWC2uZ9WePnp2xFn0vrRuqn8tT
Fg0rPSFr0hUGTsUNeQn1fxlDTnY4FMAzWrXOD2VfUQiQCwu+xHWrqVU6OSUfYVadtRs3Y5y+6KmQ
MJ8CSufGt0rCenlDtjiNujNnvyIVy6qUtFJtekFsZj0wjSVBnDFNo4QmOheqngvpouxjJfu8bxKH
fQRlj0x6gDpNhpawX2mG3YBv1SXFxVdCfJohfAHi9uofJIu/wQ0Xk8PbeuJV1vcyvMcBwMFuiG5z
iSg7ToqAVVibXpOmMoabgM4lRvTrtj9sbsMlnhRSiYSgfxYlan3FDoKqQlXVuF/LTTTLlftkkiEu
NAPzQ34affSfsagCqhf0qPVFHzZhb9KWdcyvxlTFS59S4xnBRaCc5HkiJYnsbrS8Ckar9NNJh5Zo
BJMZmBxQteOhr27NQRWE6Ngx5ZQD3h84Ww8xLdoywEjJ7FNzsQvZgukfKnqCCjn9ONkhW0cZEmOc
FFfT3bgnRXXdgkc4aokSq2U/s/KP612/bax/zhPAXM4a/xaYV04V9e5GeGHbY6DHfZQDd0qtHGY6
RxdSIgcGpJe8P3uPHQL/YFTnHDVFtkpMkjiMqHzZtMhXPYS8a4Kdh4OG66Bmzj622964QsbeQr08
wGeXSNGqN4JN4Hqe6fHCEYYw7uB2NYTSqUy/vhlFSWelBd2ZazNFIr6SNFgEvaTKZAmZ7dMLYuCt
1HL6ZNL9Q6ln1SCLMq5fQFczgWMI5Nm3sPvBU3JQqeKi4Y2KWXzUhCw+gSrxEmK40ni18iu39NY+
uTnu1S8CQN4prPcWYa/jBnWIc7pD/S0qvr2muWLLqOy2GpjLVMhjDtIQTpAaYb0+QQ0J+/boWbNB
JAsc4N714C0AXptTNIQn6UunQqAM+zfgBD85YCF4Q4JorgyflCkyyM2S50ix4mTpBECMmE7KlYjl
54B6QXPRrrKYAhZojsdof9ynCkkT/obI6YtWTQhvptdaZz3BNPU23tjNP01OFbvlDJX+VqDz4wkj
wWF73PLaKqD9hPsrjx1DVbY6xUrtfgY87OunHp7ovTNo/trGUZimQ8FX7UOoFI2DkBOftbJYWsxd
zrREx96OQN2t+M0pjr/FKUfFBnzaKbypSkGUc5ZSjC4OSDIneVzqJACRopJZRTIkTiNB+SK+Sq3y
PSDkMVpuK0PtlAnUkmV/wh+1aVAC2p1BTdPPM+Xjlihp6U8DGzXwqmQ+BtTBe/cBL3o2Ewc7am5c
LDdPkE2quw9r/2baNwt7Mz06ZvE/glOb6pq+jFNhSsHL6kAK3A/UgB+Af5WtqeVLOhy92nE8Clhq
UxE6B9VPQOl3vpNIeN67YEm/yA55hFJ2uVv/0E5NWT7yJgPb+jOOb0IWyTdMdSgZObG4cYCYpuVI
85BLVk93dGACT4lTA/FeNZ52TaX4bYxBw2aKHqa6G4XhSYaQEVpGc4lz7+1JtF/BwpZcB9pV/F85
nnIWT5ihDGWKBR/atjWvyas/bB/A/O9x6p9sRXuJeg1QKqWoRX1n10qf6ZPrM4+NPY0mUcai3VDw
27j7+YLYI2i6CFYm1YO8+tyNcIFbSdJxYSCG30w7RqvXjWOGwt3fNdRsIyh20C55iVLE+lebdb3N
I8AiFH702MWCUpzvoTFfpwt9xDW0iQ3meLwdDbGLuaMVuMnifLdCewSpHdLrQpKFqtNKCgyxDeqq
0Jsa8vcQiXTtQ7nIlnfJrpGf3wSfsGBTZvViw92nd2C1TD2qPoTdyG8gJakPKzg3EYTLjhwc8J8J
T3GkjmV0XhTJUeOWdQDYejrn8raOCshOvDVt/j5Vy4iApRyIkgmV+7xvA8QY2S18/aFWS9AUpGXy
yj0M8miOk/3vJbcOYPtDzU64hyrIAUm4KeT0OI4gHvJFiF18+o20tN2wdt7iT9iB8rQ8fG1Z5OSc
HlsLgHDCtb7C+kIoDNmCEgsqpLZ+QwpuTjjZOmT3+TtaK9lwNGSs6lpOpWSS1RAnp0mUJh9m+h3B
KbxPp8OWO9ptWT6ZYcmNGzRYlDFbCPDj9C4KUCoP6xfDJ/lfyxVaZSTszE7xcGr2pq8lHTeILY2O
jNLFMhtV9IWjyX7GK/E9Pyyb8RGLm7/4GQUqDolSEzWpeH/4to99D6txR1QVqQJ9KKi+nG8hFC3u
dI6aZTDehsGBwkcYWo/Vtpmnd1MsUEJ5HDvxkSmeKbkMkAX3CPcn9eGim1KlNsFXnTBzTBy4ABJ2
581m62nap1od4sj+YO04SBjs22z+Gx5SZDliDMCLe0WK2o3ZXAf5vl3p+ZlynI1kaNroLpvaLMkQ
TTQGVjNY8ty7gBPXofp5ecnr0ShoqOC9cmERUB/5uoZo9DyASb+G1OsBE5FKFazX4JtkNJsao9rt
gK3L+pYXYskY2oP/w9fGGBcSdfZyxr4ENwpub8kmag0m2GnjmPQ4i4Yc6N/YKQJ3tCGXmbR8khZK
/szqpJScBA0tZTFeRwNZDwnVzfGdGe+EHVGhDH88/B4UOaRI2OsIysbPGOdbWZWqf0aeaMn5+Hhl
kfNmEcWBZwIcNmj9TM9YtD3x/v4C2Gti5eLN7+YYPn0AI6pv1t9F8ao1HxS6O0SZ/xSNUJaJGb9c
z4RPsM28Cn9SMYGRgRu7o450hjyi6PJpsA8K8kY4YoVjePKRA/KXdir03+md7ydz+ZxKH0Ec1cAM
ZKExoRiDAnPb0UGS9l4MH2Tugxfubwp75QF/bKaG72PdY/nYWvlh9bHfvh93PowthV5gAuoqSAAy
KOqLmcO8UXxUJTfmXRLrT4hHP8zCKnQezomus4y2qaXAmPJ3DJJC5VnUhniYblGtxEPoO+diGY1K
wP/mSbCZ1GRPjsmlA2zqTslEzcOZgDCILaHb06jL2sx8soObL/JKWi8+G9il53n0WuR1dIZjWkyS
ptj5kqDkI01YoInIQbK3Qx6PXheztweDxYguIu3Fdk5Lp1GLtkz0Sp57UWtAEXNtMqkM+a+WJ7JI
+0EPsMUsRcYCRLD3lX2LbNj6le+Fd8eTUeblE4uCXc9aWuJ5bKOqypZshTzhbxMqWXTg64xYwHYD
RfkTfJPSXFpIOfEFss2KbgYPPZYpWdmUv31NRQ8xvmpy1QNeWWrQdA86H17gRe/nybXPfphAcl9G
6Tys08S+MvjNejOmDPuyDUGc/0SXljRns66ypTQhBTO8ELLPfc/HPYsVQ4eXntMvIejK9gb8kOCw
ZLJQeO6ZHwhWibpoSw+WNIQp24h9TphANO4IUrOLIXvhcSZLBxwPft/7GXZjpkmqY0aqNxpzBpkM
GfWLYVMAlDlcUrxota3OySeUcyCXmZxNDzeg8xbUNFCvmw7mlJm5vWd1YTJYdljXnBHQSMCBMI9D
BpNsoESIeqy4H3ra2baGMnEt+dzaHzJp9TwxActxKIBYDJIx4W3U/aOhj4lEXCujW93iIWhUxZrY
wmrm+SQSPyHRlnSO72uQZLw5czDAZmU+9so42Pc5j6EoQ6MGUrKSChDcmW42UFLHn8afe6pq8U96
29fTbzH/7BYtK3MzdgMo1UUlCc262injrP0MEPKQ68WibDJlpc4fxQEzub6Dlgh5lCeeRCTufUtq
OfSPxHeePMpFEXfKCujM7rti+xcHm/UMdzXktsV8j7Yc1zwF55yucVr51/ZLVhhe4aybNnh/5G+b
rWn3CavqnwZMkmBfOq8eN8osZIjAtkC3tEnarQmuKB683mQlUoTUuj9mvBAQ/Nqbqwp3dTtKG7lL
rJM7XbdPuGOuowPJDOQC+cYYCkbJx6JrAU2QZAdxl7G059wWXEF7nEe1F7usd68REceaTWiLPNrT
Rbmm1PuaTEZwFjnHM4bdUPoioe2WBPOgIYCsl8jSXpfA9Q3jtIJ0YhdGsMuZcaqclLyhRXl9J7DO
0IRPzWuaT5iGd/1u5aMFe0ncKrKmcr5tQnHAVoJl9ybm3kRT9rEd2Vq1W00m8M5DwtVmXbS7Hu7k
ZSqiIyK0Wb7RUdZdP+9qQMMvY/iodSMbKbhKziTkhXC5O7b2VxsmWvWB0BwVWfFeWUvz/MNbkBTE
qBoYvkmkNa0uxf7oLKLLPEp3cVti7sLQTzNpZ1T/ynm/Ak+Yha17CfGmSSEgKK6BIFODGUzZpwGc
kIPEN04JAEBemXKbAekXLUA6OntDhJXN1Yh3GguV0J+ERCRpD93e7p5/VpGQCaUdVAkU7bmKzF9v
PCx67slZUPyY+9aOYrKQ0QirSe796sY8kFyg5Bw3XkY4QOYrTmgLq4n29Eb65iTX1ZidKwgbeJyO
qI3MW81MdZlrTAE4O2w4whlig4Q5bNY3Kxf+VreMHgHYDWR8eSzSpKwhM/qMuglStJDDP3BgJt+A
eP4DqpARDbV6dLqSPbtld7IGH+zFD6KFC1rvgXPWb4Ct0oHdi+MacHELllHfCwN/t2jfLA6RhKG4
Rio9KxG4ROvSH2uG/SfCAc0cvq4jl9wxPX0/gJ9hR2gZTzv45etO6Mwma6eS37cnljuIQikWnjOM
1NOUYnb5MrUYYXLs1+Jre7BcH0hsYeV5xO7Y39LIsQtOgCW3BOFcJFC3uNEfIF/m4ASgH/MPwSjm
zHxOm84azwsRLHbC5IlEJz46HMdGyfiJEj1YLqmWAkoWqeQmeVPeQgy7b7Xxsj+tFotGfxqC8QcO
5gDNX9kxDFTdkdTqV4Trf172pQ2rW+2BdvS80boQK2pnyE5Rvv1Wu1BGVwfCzh+8bjhvM3UaMJ87
Trmrl8oPbEojqs8Rpri/2WtTT7r14uZd6f/UY8bABeSY6f7ISAR4WCip2/CtHu/Nxc9pMV3SgRhS
RuL2ckdUOleVYfiASRzv+U+jg+2ydPqzy2kNIdmzfpCx5ZUF4qWpQJoLuGWsyJthAzIh6OaJqHLV
nVU8WXXcqYkw8xNMqeOtHzjDqiNUcpV3YhX2qWHFElydVuJEpXquJ1XPoIWLpUUtIA+MWXHEfoZw
sHDmhnjMqPsYgxoj4AAFsB8pea+n/SA6wWUgaektq0+Sm2ilw0C89ZrBy5KSad4hR6bfv0fOUEsR
A1U3HP/qkNhdPUo8O+sLTWn/Z8MGya3WVm08UtHVIsFBjCww6ggp6ax7Fx1BfaHcikOwHN0KxAeE
tFevbWIHymQfv9lpyakicDq4R4tjsrRIsRI5+VvfRlPLIF9hboSB6kzDDGAYrN5sVCUeM5yTF93Y
XyHGziFHDJXPjau2FytHPzriVjIuW1LSvZtPeQbrYnI36np680rIshRYuaCUcUh7FrxfBG3hAqLC
gUEO8nNCtKTOrIWWhF1OGSUNh1v0Jk9hCaaP+doHgH2uipA9no4HNDMLQSEuJ/SWzRsuQ18jfDsD
8dtO2uof8Dyzl4Wx61hMdJJTPkWPmV7xH01y1UAmUWL1xTuKDSbylHf7/CAzasCMcxw4A2GAZij8
ot8soOD5Q4OCtxkkC9BT4R/VNkh80+1AISeJZsYd1ZQ2YqRk/E6LF8xeIhHFdy7yt8SBJMZ2Xsq5
XaybW7kSt64e2urP4gIWjrV1lMJHFlXuzWuOz2CBUk0J6yu7NCMUDYiDW5KTSmZDcYksdJH9pFZE
aJj5OAo7VgA4DCp10eCM3bQ4gdR1rPo0C+o2cKSSwV1D/Bni7txNpBar/mV2yNY71k2JR9f7kaxn
z3LSf0K3B6GXcHs7yNZWfyrqHe59JaiVFkW1KCoaUXFZx+PfqHLOGZ7rNOjJkZYsuwBWf2u0/Tp8
gQfcAeebR9E0gHP/UbtPen/ah9+2eZSWHwYS8qwY1fHRi+B3GTx+5IXrhlamfXrzmacQfBsKf7jg
c6ru9GxXiutnnUCpUBtcytPBLZ63xZFv8/metsoqsJtLUwyb7Jepml1jNDDa27qNPvrqYa5zmmzJ
onpVkaQAA7u7GrZaztATTvZkQvBYrZEtJDD4DnRvZypoDoCownzHN5J/Yt84Aeo0gXLNDnmbYffd
28/GLiXHPJyZcLGWQoWfoCSSKsn3IekrK95ZRcqMs+M35s83tA395S4JZMTlyMR+C1qO1u0/j1/b
sTB5dyF0Imx4qfiEQLfE+EQkOvrPcB81Dni0iuH2oMTc21CReoeL6HSTk7NYoNZgI70Qa6/t8dmx
zPrxEZUUiwj/tfaZC8SRrDRxTM4DLJZAmmSUcDt2np35k8J/JizHQpVgBtHaarKdHKoQYhd0ReY6
5CDenOAZaLNmHyttL6GT7tulky9S5PjXYy+03BSebb2/argKXMIHuZnWWy5QylkPLIERvi8DzNWg
OjZ/8VUYAOWnYhtPTBZVPhokeJ2Q7F2u+X3YqoEgEUbY1ZGB8FLIF3Coce8ecf1IKhOQdpspYWB+
nUJDQJCPIlwbuB4lVu26z8sle2u6CKmk/ru/1Mc5yi7DHBJEAbhz4aDz7fJsordbXw1URvyJ8dni
kziYMvHXK9p56YAtwbdUq9IyEWKtBKVz+iihSdGDjvA7NUQzwv7dvIdU2FqjXXaVw6BNhKVveL0u
9gXZwO8I4qUEPz4Jcoxfy7oKXZJEq970tbO1HUzFyBB7lmZKCRSa4U1Vi5sXgdaSamN9HIKxcTWC
ihnsUSkVI82dcLswOhpH7ofF0C3o7f6Ta6Obfcy6sjXjFdabIR8Qk18QmhMYFK7ykx0/XILvtbJt
lMKVTsUHJF8Q1Hpujt073CObEwmnSp4X2F6hmmvVq85xru5MJiQsDX2liBuDG1ydkUwK/7jat0nY
8GmN+ssUl+0kLkponFw5yeaAlUOfoI8KqFlZx/MEnErO8T/+dqJRNAQu+MK5CX+0RCWTyMlsQRSE
S7712HMC7YbiOg8krsTv2QbM/xE3QAfGJpACPmYC83QQMx8YP+Ojmil2w47Zlcq8Y1p2a8wLE8ck
+fcoy3VCqjzBin335egW35l5hd28r6K7BWIVP0V2/ytZDLXAXRY7q52V6784CY7SGj8Rat/k27Or
jWVNMHb1e05ucIUw5mYJiqfwZa4qmOq3DN+HiNhXsJV58/MWWhagkvJUkw62JmbL7KAIivN0uiSD
3RUdYtQh/12ZSUfz7gx0ng9oR4okSmuD/vQkxicoW/pdsW21TXYuXzb1ZusMsTyP1M/vLxeyXjah
D03LzyJyNPbejeA7Borunw9StGEyp2g3Wv+Ewbtuav2hu3bguvvgc3uQ0FL6Q9JjyCDqUD74FFZ2
uyXe69IH/h0wI1hnf8RUGswJmJz4rG5XXgVJ/sIXfN5KfJCtryHRwY30qrXz3mDX/UX7p/VcMHoQ
el5bsMTmtZtqe4KUg0cmMt054AyQdLNWzNHkxCFDqxpIESafQdpBx/0IBmBYe70Pokw8UJ0dFFtI
FsYK+qJKeg81CcaZOfgBCt9HdLUzJdnSHIQMLvkMifvJmctdm5Hwx4Zv8xCu6BxwhcXCaPBK+RtH
qEuZ6IU5bE0niLLNaHFZ9b8xDMjO/34WZK8vwgBCbfsXbr4ip0kGATs7bTn53RZgCCP3sM2cc4OE
/n1KVVMRLbmuQrdVv7zwaxacePHMxxh5lGt80FqrafxC+5z3SesJyemn3p0e+wRCm8xqzXixNatW
eKJhrHXSrjWM5SCNsliU0sguatu8FVcAALccX5QcsdBgRXX026oqAWWzr8aldTGJa35S0jEvu0sI
U0KMJ+MInDgJwTnwGgTnDa+7UB8INw9PkBKW3OHrcwD3BK/0R8Xo7/h8nXyQ081QVWUlDR4bbrrz
alVrGZIhFB/gQ0sEZvmVGLsRZLFPQZdeazrEwvnQ9dJJj2HmjTNZOsz3TsI72wlv/QPld3aECA2a
OSZ0NT5r9BfQyeQMbr9jGPvwH3ErqeYSl89+IZo5WEV94zWYHVfwGIT21v0znwyYrTrKNrHdR3MD
5F1TLQjEQa/CP5RjrAAOJsPsxL7Qi2rGOFiueOAsu3m7a7Xfyk/mTmEThSG4XnL8FjoezXJFD6q1
UcUNl6LUHzEB/mjSpaq8QS03JAOSm9RsFrVZ0FAsxY0iST4RPH6Ie2iIAMjRal5Ii/1pZNaQ5PS+
0UJ2P3Pz/jTrvJ0VO9omjPjBItNrWXkTrrRcyf8H0P8f8qHuZTNCBv3Tf80+rn+tXnwq4ValKpZz
odcipUIkZGEhDQB4qR05BCvy6HGW0izW1oCHVVKwL/U/efmMhV2RRh+YtIjlpWBivCukttpcB4BE
N6iqN3OwHssoGqpw8uljQPXVWOJYBE0V5jWzENrp0RCxTD/wXM8Zr0KwsrUr0JUmHwnbb5jnZfFK
gebAUC5NRXlwT7twBcBbsyJUUXcyGfZepAxipsutEwYUxnXvhnPHf6/N5wqlP5PnNkGU8iLjtgZl
+QLY6FiBpr3RStzZ8TIt0zXMCQAj5Va4az3mQlNjrl5QBKpKgea2BBK4lFb4BPwCc2sqW3DLX6Oe
3rq2bKZl7oCGWZlHi+x4+IXpcYg/Cbe7DhhH8H8uiY0h3oBrIwBH7dQfqRMGTzJZHLPuvD2YEOnR
V3J9q72zV26tdBsgofQNe7Mx9ldEBiltJOt+OZCpSqNYAw8hnXq4tcmNbRMnGWtLsJhOFiVQOE7p
JuLkt8ezpmAfux+D4kwRbY6B8zxcFRNAkSkjEJKE/2veeFC5kzaF8KUhBKmhK5Zf7Y0PvNdTDXNr
PrbhFpa397eK+DQrsqDt6k/RiTD5w6KLD5cdS+ZjeG6kzV1HYx2XMdvtezOORDvkGhH3FlQqD3Fh
fmqTCK9Z22vPwD8WNHT4zdeiNmuGQRbcLoHsdwnZHHOy17TEx5yTN9vR0lG+u9nO2eSkWiFj9+dV
MOuSs78Gw8gYpCHFrQkY6yAIucPGTs2U8SGJ+PaJBHMVh+vxXmfiZGyeZ8bVkihNzQqI8Y/iCHNr
+ZHpg/0mtEyl1k/4fvdM70Lq1PuPsrq55rYb9yAhuijAWAP86irDgtKPUP6Fop4gzHHOzg90THSZ
yi33sujQAhlLHCpbRNXAmf7VVDOmrX9aMCXlIC1+/CN37z9MGb/+RrBpyUfUwr/nINwZkH8/F26F
2/AU5eLxevYEv1uzidloKM2qcFbLtX25IFOsfYdIrHnsHyyDaPcA73mZ1dT8izs/OX8fJSIWM1be
KqhSuCGnqPa4SIZcfxOYdHkygIdRQlfDWaoJxM/Bz6qzyOtrajJhUAuNJpDYYQkPFo0eLV25bCwg
PTevl488ne9KwDi/pv+bziC1DugJspK1GRkpG9/jddtCchba4ZyPOtu3DyhfwJs7g/1No3g87omF
xYws4qZwy7yeyDh1puEDObX1mz6gsVaOz+b0ScF3QqqYJynGSfIkKaQOpc7K3AZyAozOYY7/R7oB
O9xl1ZyAnkR87t8hrT228znbfcJNSUvw6CDLyy6zq5QaCBVab0M603sk1UJfIX3rU2guweuJcf6a
1oB2uvXA7oIS6Jz+efi5zNELyPghHK6zYYG8PYRkA95z21UXpZCEG4MOg19VvChmeMFYOVgPIxfg
SuN8hqCOghnDyg9DV+xfm2oMWmhBUNyWrivzuFGg8AvGZu4DZZvivjj1xHr/ggUGYcWNXs9ygT0Y
bDmBVV2Osc61ZHGuI79eMRtSWrXVCRVKI44J7RnY0+045BSjgMkdv84sXGdiLvWY8+6wxHiQwZel
2mhCHANMTJrLl5qLlJHEEjQgJH1OFkwYPVvUjEiAQszBR4QSszlBt3U7KdcW5tIlYLKDXDKS97m4
ddwiRYiXnxeL//nAtclY50CHE/8UJHcK220JYTfDZ75KmexHK0BctWk1K67gwQ3zYHLKNpZnwxrN
lpxwugLHoQcCW38j0YlVOI4vhImiwIdugBx50+N0DB95VnqBBBzEF935LiVD70U6vuv3v49LQ/Gg
NxL9ra/qJE5xk/y2Jm2APTxq1Q==
`pragma protect end_protected
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
