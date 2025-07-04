-makelib xcelium_lib/xilinx_vip -sv \
  "C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
  "C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
  "C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
  "C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
  "C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
  "C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
  "C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/axi_vip_if.sv" \
  "C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/clk_vip_if.sv" \
  "C:/Xilinx/Vivado/2020.2/data/xilinx_vip/hdl/rst_vip_if.sv" \
-endlib
-makelib xcelium_lib/xpm -sv \
  "C:/Xilinx/Vivado/2020.2/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
  "C:/Xilinx/Vivado/2020.2/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
  "C:/Xilinx/Vivado/2020.2/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \
-endlib
-makelib xcelium_lib/xpm \
  "C:/Xilinx/Vivado/2020.2/data/ip/xpm/xpm_VCOMP.vhd" \
-endlib
-makelib xcelium_lib/axi_infrastructure_v1_1_0 \
  "../../../../ps_pl_bram.srcs/sources_1/bd/system/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/axi_vip_v1_1_8 -sv \
  "../../../../ps_pl_bram.srcs/sources_1/bd/system/ipshared/94c3/hdl/axi_vip_v1_1_vl_rfs.sv" \
-endlib
-makelib xcelium_lib/processing_system7_vip_v1_0_10 -sv \
  "../../../../ps_pl_bram.srcs/sources_1/bd/system/ipshared/34f8/hdl/processing_system7_vip_v1_0_vl_rfs.sv" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/system/ip/system_processing_system7_0_0/sim/system_processing_system7_0_0.v" \
-endlib
-makelib xcelium_lib/axi_bram_ctrl_v4_1_4 \
  "../../../../ps_pl_bram.srcs/sources_1/bd/system/ipshared/c9f0/hdl/axi_bram_ctrl_v4_1_rfs.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/system/ip/system_axi_bram_ctrl_0_0/sim/system_axi_bram_ctrl_0_0.vhd" \
-endlib
-makelib xcelium_lib/blk_mem_gen_v8_4_4 \
  "../../../../ps_pl_bram.srcs/sources_1/bd/system/ipshared/2985/simulation/blk_mem_gen_v8_4.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/system/ip/system_blk_mem_gen_0_0/sim/system_blk_mem_gen_0_0.v" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/sim/bd_44e3.v" \
-endlib
-makelib xcelium_lib/xlconstant_v1_1_7 \
  "../../../../ps_pl_bram.srcs/sources_1/bd/system/ipshared/fcfc/hdl/xlconstant_v1_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_0/sim/bd_44e3_one_0.v" \
-endlib
-makelib xcelium_lib/lib_cdc_v1_0_2 \
  "../../../../ps_pl_bram.srcs/sources_1/bd/system/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \
-endlib
-makelib xcelium_lib/proc_sys_reset_v5_0_13 \
  "../../../../ps_pl_bram.srcs/sources_1/bd/system/ipshared/8842/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_1/sim/bd_44e3_psr_aclk_0.vhd" \
-endlib
-makelib xcelium_lib/smartconnect_v1_0 -sv \
  "../../../../ps_pl_bram.srcs/sources_1/bd/system/ipshared/25b7/hdl/sc_util_v1_0_vl_rfs.sv" \
  "../../../../ps_pl_bram.srcs/sources_1/bd/system/ipshared/c012/hdl/sc_switchboard_v1_0_vl_rfs.sv" \
-endlib
-makelib xcelium_lib/xil_defaultlib -sv \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_2/sim/bd_44e3_arinsw_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_3/sim/bd_44e3_rinsw_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_4/sim/bd_44e3_awinsw_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_5/sim/bd_44e3_winsw_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_6/sim/bd_44e3_binsw_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_7/sim/bd_44e3_aroutsw_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_8/sim/bd_44e3_routsw_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_9/sim/bd_44e3_awoutsw_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_10/sim/bd_44e3_woutsw_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_11/sim/bd_44e3_boutsw_0.sv" \
-endlib
-makelib xcelium_lib/smartconnect_v1_0 -sv \
  "../../../../ps_pl_bram.srcs/sources_1/bd/system/ipshared/896c/hdl/sc_node_v1_0_vl_rfs.sv" \
-endlib
-makelib xcelium_lib/xil_defaultlib -sv \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_12/sim/bd_44e3_arni_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_13/sim/bd_44e3_rni_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_14/sim/bd_44e3_awni_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_15/sim/bd_44e3_wni_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_16/sim/bd_44e3_bni_0.sv" \
-endlib
-makelib xcelium_lib/smartconnect_v1_0 -sv \
  "../../../../ps_pl_bram.srcs/sources_1/bd/system/ipshared/ea34/hdl/sc_mmu_v1_0_vl_rfs.sv" \
-endlib
-makelib xcelium_lib/xil_defaultlib -sv \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_17/sim/bd_44e3_s00mmu_0.sv" \
-endlib
-makelib xcelium_lib/smartconnect_v1_0 -sv \
  "../../../../ps_pl_bram.srcs/sources_1/bd/system/ipshared/4fd2/hdl/sc_transaction_regulator_v1_0_vl_rfs.sv" \
-endlib
-makelib xcelium_lib/xil_defaultlib -sv \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_18/sim/bd_44e3_s00tr_0.sv" \
-endlib
-makelib xcelium_lib/smartconnect_v1_0 -sv \
  "../../../../ps_pl_bram.srcs/sources_1/bd/system/ipshared/8047/hdl/sc_si_converter_v1_0_vl_rfs.sv" \
-endlib
-makelib xcelium_lib/xil_defaultlib -sv \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_19/sim/bd_44e3_s00sic_0.sv" \
-endlib
-makelib xcelium_lib/smartconnect_v1_0 -sv \
  "../../../../ps_pl_bram.srcs/sources_1/bd/system/ipshared/b89e/hdl/sc_axi2sc_v1_0_vl_rfs.sv" \
-endlib
-makelib xcelium_lib/xil_defaultlib -sv \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_20/sim/bd_44e3_s00a2s_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_21/sim/bd_44e3_sarn_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_22/sim/bd_44e3_srn_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_23/sim/bd_44e3_sawn_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_24/sim/bd_44e3_swn_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_25/sim/bd_44e3_sbn_0.sv" \
-endlib
-makelib xcelium_lib/smartconnect_v1_0 -sv \
  "../../../../ps_pl_bram.srcs/sources_1/bd/system/ipshared/7005/hdl/sc_sc2axi_v1_0_vl_rfs.sv" \
-endlib
-makelib xcelium_lib/xil_defaultlib -sv \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_26/sim/bd_44e3_m00s2a_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_27/sim/bd_44e3_m00arn_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_28/sim/bd_44e3_m00rn_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_29/sim/bd_44e3_m00awn_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_30/sim/bd_44e3_m00wn_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_31/sim/bd_44e3_m00bn_0.sv" \
-endlib
-makelib xcelium_lib/smartconnect_v1_0 -sv \
  "../../../../ps_pl_bram.srcs/sources_1/bd/system/ipshared/7bd7/hdl/sc_exit_v1_0_vl_rfs.sv" \
-endlib
-makelib xcelium_lib/xil_defaultlib -sv \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_32/sim/bd_44e3_m00e_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_33/sim/bd_44e3_m01s2a_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_34/sim/bd_44e3_m01arn_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_35/sim/bd_44e3_m01rn_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_36/sim/bd_44e3_m01awn_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_37/sim/bd_44e3_m01wn_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_38/sim/bd_44e3_m01bn_0.sv" \
  "../../../bd/system/ip/system_axi_smc_0/bd_0/ip/ip_39/sim/bd_44e3_m01e_0.sv" \
-endlib
-makelib xcelium_lib/axi_register_slice_v2_1_22 \
  "../../../../ps_pl_bram.srcs/sources_1/bd/system/ipshared/af2c/hdl/axi_register_slice_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/system/ip/system_axi_smc_0/sim/system_axi_smc_0.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/system/ip/system_rst_ps7_0_50M_0/sim/system_rst_ps7_0_50M_0.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/system/ipshared/fe34/hdl/bram_rd.v" \
  "../../../bd/system/ipshared/fe34/hdl/pl_bram_rd_v1_0_S00_AXI.v" \
  "../../../bd/system/ipshared/fe34/hdl/pl_bram_rd_v1_0.v" \
  "../../../bd/system/ip/system_pl_bram_rd_0_1/sim/system_pl_bram_rd_0_1.v" \
  "../../../bd/system/sim/system.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  glbl.v
-endlib

