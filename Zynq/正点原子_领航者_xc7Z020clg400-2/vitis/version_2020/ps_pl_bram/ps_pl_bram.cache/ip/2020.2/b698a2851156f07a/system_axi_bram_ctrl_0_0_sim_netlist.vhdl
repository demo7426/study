-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.2 (win64) Build 3064766 Wed Nov 18 09:12:45 MST 2020
-- Date        : Fri Jun  9 17:31:52 2023
-- Host        : DESKTOP-KG2JVSE running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
--               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ system_axi_bram_ctrl_0_0_sim_netlist.vhdl
-- Design      : system_axi_bram_ctrl_0_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xc7z020clg400-2
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_lite is
  port (
    s_axi_aresetn_0 : out STD_LOGIC;
    bram_en_a : out STD_LOGIC;
    bram_we_a : out STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_bvalid : out STD_LOGIC;
    bram_addr_a : out STD_LOGIC_VECTOR ( 9 downto 0 );
    s_axi_rvalid : out STD_LOGIC;
    s_axi_arready : out STD_LOGIC;
    s_axi_wready : out STD_LOGIC;
    s_axi_arvalid : in STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    s_axi_aresetn : in STD_LOGIC;
    s_axi_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_awvalid : in STD_LOGIC;
    s_axi_wvalid : in STD_LOGIC;
    s_axi_bready : in STD_LOGIC;
    s_axi_araddr : in STD_LOGIC_VECTOR ( 9 downto 0 );
    s_axi_awaddr : in STD_LOGIC_VECTOR ( 9 downto 0 );
    s_axi_rready : in STD_LOGIC
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_lite;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_lite is
  signal \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs[0]_i_1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs[4]_i_1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs[5]_i_1_n_0\ : STD_LOGIC;
  signal \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[0]\ : STD_LOGIC;
  signal \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[5]\ : STD_LOGIC;
  signal \GEN_NO_RD_CMD_OPT.GEN_ARREADY.axi_arready_int_i_1_n_0\ : STD_LOGIC;
  signal \GEN_NO_RD_CMD_OPT.GEN_ARREADY.axi_arready_int_i_2_n_0\ : STD_LOGIC;
  signal \GEN_NO_RD_CMD_OPT.GEN_R.axi_rvalid_int_i_1_n_0\ : STD_LOGIC;
  signal \GEN_NO_RD_CMD_OPT.axi_bvalid_int_i_1_n_0\ : STD_LOGIC;
  signal \GEN_NO_RD_CMD_OPT.axi_wready_int_i_1_n_0\ : STD_LOGIC;
  signal \GEN_NO_RD_CMD_OPT.bvalid_cnt[0]_i_1_n_0\ : STD_LOGIC;
  signal \GEN_NO_RD_CMD_OPT.bvalid_cnt[1]_i_1_n_0\ : STD_LOGIC;
  signal \GEN_NO_RD_CMD_OPT.bvalid_cnt[2]_i_1_n_0\ : STD_LOGIC;
  signal axi_aresetn_d1 : STD_LOGIC;
  signal axi_aresetn_d2 : STD_LOGIC;
  signal bram_en_a_INST_0_i_1_n_0 : STD_LOGIC;
  signal bvalid_cnt : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal bvalid_cnt_dec2_out : STD_LOGIC;
  signal p_0_in : STD_LOGIC;
  signal \^s_axi_aresetn_0\ : STD_LOGIC;
  signal \^s_axi_arready\ : STD_LOGIC;
  signal \^s_axi_bvalid\ : STD_LOGIC;
  signal \^s_axi_rvalid\ : STD_LOGIC;
  attribute FSM_ENCODED_STATES : string;
  attribute FSM_ENCODED_STATES of \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg[0]\ : label is "rmw_rd_data:001000,rmw_mod_data:000100,rmw_wr_data:000010,sng_wr_data:100000,idle:000001,rd_data:010000";
  attribute FSM_ENCODED_STATES of \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg[4]\ : label is "rmw_rd_data:001000,rmw_mod_data:000100,rmw_wr_data:000010,sng_wr_data:100000,idle:000001,rd_data:010000";
  attribute FSM_ENCODED_STATES of \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg[5]\ : label is "rmw_rd_data:001000,rmw_mod_data:000100,rmw_wr_data:000010,sng_wr_data:100000,idle:000001,rd_data:010000";
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \GEN_NO_RD_CMD_OPT.axi_wready_int_i_1\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \GEN_NO_RD_CMD_OPT.bvalid_cnt[0]_i_1\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \GEN_NO_RD_CMD_OPT.bvalid_cnt[1]_i_1\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of bram_en_a_INST_0 : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \bram_we_a[0]_INST_0\ : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of \bram_we_a[1]_INST_0\ : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of \bram_we_a[2]_INST_0\ : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of \bram_we_a[3]_INST_0\ : label is "soft_lutpair3";
begin
  s_axi_aresetn_0 <= \^s_axi_aresetn_0\;
  s_axi_arready <= \^s_axi_arready\;
  s_axi_bvalid <= \^s_axi_bvalid\;
  s_axi_rvalid <= \^s_axi_rvalid\;
\FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CCCCCC4CFFEEFF4C"
    )
        port map (
      I0 => bram_en_a_INST_0_i_1_n_0,
      I1 => p_0_in,
      I2 => \GEN_NO_RD_CMD_OPT.GEN_ARREADY.axi_arready_int_i_2_n_0\,
      I3 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[5]\,
      I4 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[0]\,
      I5 => s_axi_arvalid,
      O => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs[0]_i_1_n_0\
    );
\FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFF8000800080"
    )
        port map (
      I0 => bram_en_a_INST_0_i_1_n_0,
      I1 => p_0_in,
      I2 => \GEN_NO_RD_CMD_OPT.GEN_ARREADY.axi_arready_int_i_2_n_0\,
      I3 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[5]\,
      I4 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[0]\,
      I5 => s_axi_arvalid,
      O => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs[4]_i_1_n_0\
    );
\FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"00000000FF5D0000"
    )
        port map (
      I0 => bram_en_a_INST_0_i_1_n_0,
      I1 => p_0_in,
      I2 => \GEN_NO_RD_CMD_OPT.GEN_ARREADY.axi_arready_int_i_2_n_0\,
      I3 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[5]\,
      I4 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[0]\,
      I5 => s_axi_arvalid,
      O => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs[5]_i_1_n_0\
    );
\FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg[0]\: unisim.vcomponents.FDSE
    generic map(
      INIT => '1'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs[0]_i_1_n_0\,
      Q => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[0]\,
      S => \^s_axi_aresetn_0\
    );
\FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg[4]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs[4]_i_1_n_0\,
      Q => p_0_in,
      R => \^s_axi_aresetn_0\
    );
\FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg[5]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs[5]_i_1_n_0\,
      Q => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[5]\,
      R => \^s_axi_aresetn_0\
    );
\GEN_NO_RD_CMD_OPT.GEN_ARREADY.axi_arready_int_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000AAAA22A222A2"
    )
        port map (
      I0 => s_axi_aresetn,
      I1 => \GEN_NO_RD_CMD_OPT.GEN_ARREADY.axi_arready_int_i_2_n_0\,
      I2 => axi_aresetn_d1,
      I3 => axi_aresetn_d2,
      I4 => s_axi_arvalid,
      I5 => \^s_axi_arready\,
      O => \GEN_NO_RD_CMD_OPT.GEN_ARREADY.axi_arready_int_i_1_n_0\
    );
\GEN_NO_RD_CMD_OPT.GEN_ARREADY.axi_arready_int_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"7"
    )
        port map (
      I0 => \^s_axi_rvalid\,
      I1 => s_axi_rready,
      O => \GEN_NO_RD_CMD_OPT.GEN_ARREADY.axi_arready_int_i_2_n_0\
    );
\GEN_NO_RD_CMD_OPT.GEN_ARREADY.axi_arready_int_reg\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => \GEN_NO_RD_CMD_OPT.GEN_ARREADY.axi_arready_int_i_1_n_0\,
      Q => \^s_axi_arready\,
      R => '0'
    );
\GEN_NO_RD_CMD_OPT.GEN_R.axi_rvalid_int_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000AAAA88808880"
    )
        port map (
      I0 => s_axi_aresetn,
      I1 => s_axi_arvalid,
      I2 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[5]\,
      I3 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[0]\,
      I4 => s_axi_rready,
      I5 => \^s_axi_rvalid\,
      O => \GEN_NO_RD_CMD_OPT.GEN_R.axi_rvalid_int_i_1_n_0\
    );
\GEN_NO_RD_CMD_OPT.GEN_R.axi_rvalid_int_reg\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => \GEN_NO_RD_CMD_OPT.GEN_R.axi_rvalid_int_i_1_n_0\,
      Q => \^s_axi_rvalid\,
      R => '0'
    );
\GEN_NO_RD_CMD_OPT.axi_aresetn_d1_reg\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => s_axi_aresetn,
      Q => axi_aresetn_d1,
      R => '0'
    );
\GEN_NO_RD_CMD_OPT.axi_aresetn_d2_reg\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => axi_aresetn_d1,
      Q => axi_aresetn_d2,
      R => '0'
    );
\GEN_NO_RD_CMD_OPT.axi_bvalid_int_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A8AAAAAAA8A8A8A8"
    )
        port map (
      I0 => s_axi_aresetn,
      I1 => bvalid_cnt(1),
      I2 => bvalid_cnt(2),
      I3 => s_axi_bready,
      I4 => \^s_axi_bvalid\,
      I5 => bvalid_cnt(0),
      O => \GEN_NO_RD_CMD_OPT.axi_bvalid_int_i_1_n_0\
    );
\GEN_NO_RD_CMD_OPT.axi_bvalid_int_reg\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => \GEN_NO_RD_CMD_OPT.axi_bvalid_int_i_1_n_0\,
      Q => \^s_axi_bvalid\,
      R => '0'
    );
\GEN_NO_RD_CMD_OPT.axi_wready_int_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"10"
    )
        port map (
      I0 => bram_en_a_INST_0_i_1_n_0,
      I1 => s_axi_arvalid,
      I2 => s_axi_aresetn,
      O => \GEN_NO_RD_CMD_OPT.axi_wready_int_i_1_n_0\
    );
\GEN_NO_RD_CMD_OPT.axi_wready_int_reg\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => \GEN_NO_RD_CMD_OPT.axi_wready_int_i_1_n_0\,
      Q => s_axi_wready,
      R => '0'
    );
\GEN_NO_RD_CMD_OPT.bvalid_cnt[0]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"1EE1"
    )
        port map (
      I0 => s_axi_arvalid,
      I1 => bram_en_a_INST_0_i_1_n_0,
      I2 => bvalid_cnt_dec2_out,
      I3 => bvalid_cnt(0),
      O => \GEN_NO_RD_CMD_OPT.bvalid_cnt[0]_i_1_n_0\
    );
\GEN_NO_RD_CMD_OPT.bvalid_cnt[1]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"BBBD4442"
    )
        port map (
      I0 => bvalid_cnt(0),
      I1 => bvalid_cnt_dec2_out,
      I2 => bram_en_a_INST_0_i_1_n_0,
      I3 => s_axi_arvalid,
      I4 => bvalid_cnt(1),
      O => \GEN_NO_RD_CMD_OPT.bvalid_cnt[1]_i_1_n_0\
    );
\GEN_NO_RD_CMD_OPT.bvalid_cnt[2]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"EFEFEFF710101008"
    )
        port map (
      I0 => bvalid_cnt(1),
      I1 => bvalid_cnt(0),
      I2 => bvalid_cnt_dec2_out,
      I3 => bram_en_a_INST_0_i_1_n_0,
      I4 => s_axi_arvalid,
      I5 => bvalid_cnt(2),
      O => \GEN_NO_RD_CMD_OPT.bvalid_cnt[2]_i_1_n_0\
    );
\GEN_NO_RD_CMD_OPT.bvalid_cnt[2]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"88888880"
    )
        port map (
      I0 => \^s_axi_bvalid\,
      I1 => s_axi_bready,
      I2 => bvalid_cnt(0),
      I3 => bvalid_cnt(1),
      I4 => bvalid_cnt(2),
      O => bvalid_cnt_dec2_out
    );
\GEN_NO_RD_CMD_OPT.bvalid_cnt_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => \GEN_NO_RD_CMD_OPT.bvalid_cnt[0]_i_1_n_0\,
      Q => bvalid_cnt(0),
      R => \^s_axi_aresetn_0\
    );
\GEN_NO_RD_CMD_OPT.bvalid_cnt_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => \GEN_NO_RD_CMD_OPT.bvalid_cnt[1]_i_1_n_0\,
      Q => bvalid_cnt(1),
      R => \^s_axi_aresetn_0\
    );
\GEN_NO_RD_CMD_OPT.bvalid_cnt_reg[2]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => s_axi_aclk,
      CE => '1',
      D => \GEN_NO_RD_CMD_OPT.bvalid_cnt[2]_i_1_n_0\,
      Q => bvalid_cnt(2),
      R => \^s_axi_aresetn_0\
    );
\bram_addr_a[10]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAABBBFAAAA8880"
    )
        port map (
      I0 => s_axi_araddr(8),
      I1 => s_axi_arvalid,
      I2 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[5]\,
      I3 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[0]\,
      I4 => p_0_in,
      I5 => s_axi_awaddr(8),
      O => bram_addr_a(8)
    );
\bram_addr_a[11]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAABBBFAAAA8880"
    )
        port map (
      I0 => s_axi_araddr(9),
      I1 => s_axi_arvalid,
      I2 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[5]\,
      I3 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[0]\,
      I4 => p_0_in,
      I5 => s_axi_awaddr(9),
      O => bram_addr_a(9)
    );
\bram_addr_a[2]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAABBBFAAAA8880"
    )
        port map (
      I0 => s_axi_araddr(0),
      I1 => s_axi_arvalid,
      I2 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[5]\,
      I3 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[0]\,
      I4 => p_0_in,
      I5 => s_axi_awaddr(0),
      O => bram_addr_a(0)
    );
\bram_addr_a[3]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAABBBFAAAA8880"
    )
        port map (
      I0 => s_axi_araddr(1),
      I1 => s_axi_arvalid,
      I2 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[5]\,
      I3 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[0]\,
      I4 => p_0_in,
      I5 => s_axi_awaddr(1),
      O => bram_addr_a(1)
    );
\bram_addr_a[4]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAABBBFAAAA8880"
    )
        port map (
      I0 => s_axi_araddr(2),
      I1 => s_axi_arvalid,
      I2 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[5]\,
      I3 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[0]\,
      I4 => p_0_in,
      I5 => s_axi_awaddr(2),
      O => bram_addr_a(2)
    );
\bram_addr_a[5]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAABBBFAAAA8880"
    )
        port map (
      I0 => s_axi_araddr(3),
      I1 => s_axi_arvalid,
      I2 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[5]\,
      I3 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[0]\,
      I4 => p_0_in,
      I5 => s_axi_awaddr(3),
      O => bram_addr_a(3)
    );
\bram_addr_a[6]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAABBBFAAAA8880"
    )
        port map (
      I0 => s_axi_araddr(4),
      I1 => s_axi_arvalid,
      I2 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[5]\,
      I3 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[0]\,
      I4 => p_0_in,
      I5 => s_axi_awaddr(4),
      O => bram_addr_a(4)
    );
\bram_addr_a[7]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAABBBFAAAA8880"
    )
        port map (
      I0 => s_axi_araddr(5),
      I1 => s_axi_arvalid,
      I2 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[5]\,
      I3 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[0]\,
      I4 => p_0_in,
      I5 => s_axi_awaddr(5),
      O => bram_addr_a(5)
    );
\bram_addr_a[8]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAABBBFAAAA8880"
    )
        port map (
      I0 => s_axi_araddr(6),
      I1 => s_axi_arvalid,
      I2 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[5]\,
      I3 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[0]\,
      I4 => p_0_in,
      I5 => s_axi_awaddr(6),
      O => bram_addr_a(6)
    );
\bram_addr_a[9]_INST_0\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AAAABBBFAAAA8880"
    )
        port map (
      I0 => s_axi_araddr(7),
      I1 => s_axi_arvalid,
      I2 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[5]\,
      I3 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[0]\,
      I4 => p_0_in,
      I5 => s_axi_awaddr(7),
      O => bram_addr_a(7)
    );
bram_en_a_INST_0: unisim.vcomponents.LUT5
    generic map(
      INIT => X"E0FF0000"
    )
        port map (
      I0 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[0]\,
      I1 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[5]\,
      I2 => s_axi_arvalid,
      I3 => bram_en_a_INST_0_i_1_n_0,
      I4 => s_axi_aresetn,
      O => bram_en_a
    );
bram_en_a_INST_0_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"D555FFFFFFFFFFFF"
    )
        port map (
      I0 => \FSM_onehot_GEN_NO_RD_CMD_OPT.lite_sm_cs_reg_n_0_[0]\,
      I1 => bvalid_cnt(0),
      I2 => bvalid_cnt(1),
      I3 => bvalid_cnt(2),
      I4 => s_axi_awvalid,
      I5 => s_axi_wvalid,
      O => bram_en_a_INST_0_i_1_n_0
    );
bram_rst_a_INST_0: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => s_axi_aresetn,
      O => \^s_axi_aresetn_0\
    );
\bram_we_a[0]_INST_0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => s_axi_wstrb(0),
      I1 => s_axi_arvalid,
      I2 => bram_en_a_INST_0_i_1_n_0,
      O => bram_we_a(0)
    );
\bram_we_a[1]_INST_0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => s_axi_wstrb(1),
      I1 => s_axi_arvalid,
      I2 => bram_en_a_INST_0_i_1_n_0,
      O => bram_we_a(1)
    );
\bram_we_a[2]_INST_0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => s_axi_wstrb(2),
      I1 => s_axi_arvalid,
      I2 => bram_en_a_INST_0_i_1_n_0,
      O => bram_we_a(2)
    );
\bram_we_a[3]_INST_0\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"02"
    )
        port map (
      I0 => s_axi_wstrb(3),
      I1 => s_axi_arvalid,
      I2 => bram_en_a_INST_0_i_1_n_0,
      O => bram_we_a(3)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl_top is
  port (
    s_axi_aresetn_0 : out STD_LOGIC;
    bram_en_a : out STD_LOGIC;
    bram_we_a : out STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_bvalid : out STD_LOGIC;
    bram_addr_a : out STD_LOGIC_VECTOR ( 9 downto 0 );
    s_axi_rvalid : out STD_LOGIC;
    s_axi_arready : out STD_LOGIC;
    s_axi_wready : out STD_LOGIC;
    s_axi_arvalid : in STD_LOGIC;
    s_axi_aclk : in STD_LOGIC;
    s_axi_aresetn : in STD_LOGIC;
    s_axi_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_awvalid : in STD_LOGIC;
    s_axi_wvalid : in STD_LOGIC;
    s_axi_bready : in STD_LOGIC;
    s_axi_araddr : in STD_LOGIC_VECTOR ( 9 downto 0 );
    s_axi_awaddr : in STD_LOGIC_VECTOR ( 9 downto 0 );
    s_axi_rready : in STD_LOGIC
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl_top;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl_top is
begin
\GEN_AXI4LITE.I_AXI_LITE\: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_lite
     port map (
      bram_addr_a(9 downto 0) => bram_addr_a(9 downto 0),
      bram_en_a => bram_en_a,
      bram_we_a(3 downto 0) => bram_we_a(3 downto 0),
      s_axi_aclk => s_axi_aclk,
      s_axi_araddr(9 downto 0) => s_axi_araddr(9 downto 0),
      s_axi_aresetn => s_axi_aresetn,
      s_axi_aresetn_0 => s_axi_aresetn_0,
      s_axi_arready => s_axi_arready,
      s_axi_arvalid => s_axi_arvalid,
      s_axi_awaddr(9 downto 0) => s_axi_awaddr(9 downto 0),
      s_axi_awvalid => s_axi_awvalid,
      s_axi_bready => s_axi_bready,
      s_axi_bvalid => s_axi_bvalid,
      s_axi_rready => s_axi_rready,
      s_axi_rvalid => s_axi_rvalid,
      s_axi_wready => s_axi_wready,
      s_axi_wstrb(3 downto 0) => s_axi_wstrb(3 downto 0),
      s_axi_wvalid => s_axi_wvalid
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl is
  port (
    s_axi_aclk : in STD_LOGIC;
    s_axi_aresetn : in STD_LOGIC;
    ecc_interrupt : out STD_LOGIC;
    ecc_ue : out STD_LOGIC;
    s_axi_awid : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_awaddr : in STD_LOGIC_VECTOR ( 11 downto 0 );
    s_axi_awlen : in STD_LOGIC_VECTOR ( 7 downto 0 );
    s_axi_awsize : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s_axi_awburst : in STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_awlock : in STD_LOGIC;
    s_axi_awcache : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_awprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s_axi_awvalid : in STD_LOGIC;
    s_axi_awready : out STD_LOGIC;
    s_axi_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_wlast : in STD_LOGIC;
    s_axi_wvalid : in STD_LOGIC;
    s_axi_wready : out STD_LOGIC;
    s_axi_bid : out STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_bvalid : out STD_LOGIC;
    s_axi_bready : in STD_LOGIC;
    s_axi_arid : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_araddr : in STD_LOGIC_VECTOR ( 11 downto 0 );
    s_axi_arlen : in STD_LOGIC_VECTOR ( 7 downto 0 );
    s_axi_arsize : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s_axi_arburst : in STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_arlock : in STD_LOGIC;
    s_axi_arcache : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_arprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s_axi_arvalid : in STD_LOGIC;
    s_axi_arready : out STD_LOGIC;
    s_axi_rid : out STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_rlast : out STD_LOGIC;
    s_axi_rvalid : out STD_LOGIC;
    s_axi_rready : in STD_LOGIC;
    s_axi_ctrl_awvalid : in STD_LOGIC;
    s_axi_ctrl_awready : out STD_LOGIC;
    s_axi_ctrl_awaddr : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_ctrl_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_ctrl_wvalid : in STD_LOGIC;
    s_axi_ctrl_wready : out STD_LOGIC;
    s_axi_ctrl_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_ctrl_bvalid : out STD_LOGIC;
    s_axi_ctrl_bready : in STD_LOGIC;
    s_axi_ctrl_araddr : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_ctrl_arvalid : in STD_LOGIC;
    s_axi_ctrl_arready : out STD_LOGIC;
    s_axi_ctrl_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_ctrl_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_ctrl_rvalid : out STD_LOGIC;
    s_axi_ctrl_rready : in STD_LOGIC;
    bram_rst_a : out STD_LOGIC;
    bram_clk_a : out STD_LOGIC;
    bram_en_a : out STD_LOGIC;
    bram_we_a : out STD_LOGIC_VECTOR ( 3 downto 0 );
    bram_addr_a : out STD_LOGIC_VECTOR ( 11 downto 0 );
    bram_wrdata_a : out STD_LOGIC_VECTOR ( 31 downto 0 );
    bram_rddata_a : in STD_LOGIC_VECTOR ( 31 downto 0 );
    bram_rst_b : out STD_LOGIC;
    bram_clk_b : out STD_LOGIC;
    bram_en_b : out STD_LOGIC;
    bram_we_b : out STD_LOGIC_VECTOR ( 3 downto 0 );
    bram_addr_b : out STD_LOGIC_VECTOR ( 11 downto 0 );
    bram_wrdata_b : out STD_LOGIC_VECTOR ( 31 downto 0 );
    bram_rddata_b : in STD_LOGIC_VECTOR ( 31 downto 0 )
  );
  attribute C_BRAM_ADDR_WIDTH : integer;
  attribute C_BRAM_ADDR_WIDTH of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl : entity is 10;
  attribute C_BRAM_INST_MODE : string;
  attribute C_BRAM_INST_MODE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl : entity is "EXTERNAL";
  attribute C_ECC : integer;
  attribute C_ECC of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl : entity is 0;
  attribute C_ECC_ONOFF_RESET_VALUE : integer;
  attribute C_ECC_ONOFF_RESET_VALUE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl : entity is 0;
  attribute C_ECC_TYPE : integer;
  attribute C_ECC_TYPE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl : entity is 0;
  attribute C_FAMILY : string;
  attribute C_FAMILY of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl : entity is "zynq";
  attribute C_FAULT_INJECT : integer;
  attribute C_FAULT_INJECT of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl : entity is 0;
  attribute C_MEMORY_DEPTH : integer;
  attribute C_MEMORY_DEPTH of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl : entity is 1024;
  attribute C_RD_CMD_OPTIMIZATION : integer;
  attribute C_RD_CMD_OPTIMIZATION of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl : entity is 0;
  attribute C_READ_LATENCY : integer;
  attribute C_READ_LATENCY of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl : entity is 1;
  attribute C_SINGLE_PORT_BRAM : integer;
  attribute C_SINGLE_PORT_BRAM of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl : entity is 1;
  attribute C_S_AXI_ADDR_WIDTH : integer;
  attribute C_S_AXI_ADDR_WIDTH of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl : entity is 12;
  attribute C_S_AXI_CTRL_ADDR_WIDTH : integer;
  attribute C_S_AXI_CTRL_ADDR_WIDTH of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl : entity is 32;
  attribute C_S_AXI_CTRL_DATA_WIDTH : integer;
  attribute C_S_AXI_CTRL_DATA_WIDTH of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl : entity is 32;
  attribute C_S_AXI_DATA_WIDTH : integer;
  attribute C_S_AXI_DATA_WIDTH of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl : entity is 32;
  attribute C_S_AXI_ID_WIDTH : integer;
  attribute C_S_AXI_ID_WIDTH of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl : entity is 1;
  attribute C_S_AXI_PROTOCOL : string;
  attribute C_S_AXI_PROTOCOL of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl : entity is "AXI4LITE";
  attribute C_S_AXI_SUPPORTS_NARROW_BURST : integer;
  attribute C_S_AXI_SUPPORTS_NARROW_BURST of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl : entity is 0;
  attribute downgradeipidentifiedwarnings : string;
  attribute downgradeipidentifiedwarnings of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl : entity is "yes";
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl is
  signal \<const0>\ : STD_LOGIC;
  signal \^bram_addr_a\ : STD_LOGIC_VECTOR ( 11 downto 2 );
  signal \^bram_rddata_a\ : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \^s_axi_aclk\ : STD_LOGIC;
  signal \^s_axi_wdata\ : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \^s_axi_wready\ : STD_LOGIC;
begin
  \^bram_rddata_a\(31 downto 0) <= bram_rddata_a(31 downto 0);
  \^s_axi_aclk\ <= s_axi_aclk;
  \^s_axi_wdata\(31 downto 0) <= s_axi_wdata(31 downto 0);
  bram_addr_a(11 downto 2) <= \^bram_addr_a\(11 downto 2);
  bram_addr_a(1) <= \<const0>\;
  bram_addr_a(0) <= \<const0>\;
  bram_addr_b(11) <= \<const0>\;
  bram_addr_b(10) <= \<const0>\;
  bram_addr_b(9) <= \<const0>\;
  bram_addr_b(8) <= \<const0>\;
  bram_addr_b(7) <= \<const0>\;
  bram_addr_b(6) <= \<const0>\;
  bram_addr_b(5) <= \<const0>\;
  bram_addr_b(4) <= \<const0>\;
  bram_addr_b(3) <= \<const0>\;
  bram_addr_b(2) <= \<const0>\;
  bram_addr_b(1) <= \<const0>\;
  bram_addr_b(0) <= \<const0>\;
  bram_clk_a <= \^s_axi_aclk\;
  bram_clk_b <= \<const0>\;
  bram_en_b <= \<const0>\;
  bram_rst_b <= \<const0>\;
  bram_we_b(3) <= \<const0>\;
  bram_we_b(2) <= \<const0>\;
  bram_we_b(1) <= \<const0>\;
  bram_we_b(0) <= \<const0>\;
  bram_wrdata_a(31 downto 0) <= \^s_axi_wdata\(31 downto 0);
  bram_wrdata_b(31) <= \<const0>\;
  bram_wrdata_b(30) <= \<const0>\;
  bram_wrdata_b(29) <= \<const0>\;
  bram_wrdata_b(28) <= \<const0>\;
  bram_wrdata_b(27) <= \<const0>\;
  bram_wrdata_b(26) <= \<const0>\;
  bram_wrdata_b(25) <= \<const0>\;
  bram_wrdata_b(24) <= \<const0>\;
  bram_wrdata_b(23) <= \<const0>\;
  bram_wrdata_b(22) <= \<const0>\;
  bram_wrdata_b(21) <= \<const0>\;
  bram_wrdata_b(20) <= \<const0>\;
  bram_wrdata_b(19) <= \<const0>\;
  bram_wrdata_b(18) <= \<const0>\;
  bram_wrdata_b(17) <= \<const0>\;
  bram_wrdata_b(16) <= \<const0>\;
  bram_wrdata_b(15) <= \<const0>\;
  bram_wrdata_b(14) <= \<const0>\;
  bram_wrdata_b(13) <= \<const0>\;
  bram_wrdata_b(12) <= \<const0>\;
  bram_wrdata_b(11) <= \<const0>\;
  bram_wrdata_b(10) <= \<const0>\;
  bram_wrdata_b(9) <= \<const0>\;
  bram_wrdata_b(8) <= \<const0>\;
  bram_wrdata_b(7) <= \<const0>\;
  bram_wrdata_b(6) <= \<const0>\;
  bram_wrdata_b(5) <= \<const0>\;
  bram_wrdata_b(4) <= \<const0>\;
  bram_wrdata_b(3) <= \<const0>\;
  bram_wrdata_b(2) <= \<const0>\;
  bram_wrdata_b(1) <= \<const0>\;
  bram_wrdata_b(0) <= \<const0>\;
  ecc_interrupt <= \<const0>\;
  ecc_ue <= \<const0>\;
  s_axi_awready <= \^s_axi_wready\;
  s_axi_bid(0) <= \<const0>\;
  s_axi_bresp(1) <= \<const0>\;
  s_axi_bresp(0) <= \<const0>\;
  s_axi_ctrl_arready <= \<const0>\;
  s_axi_ctrl_awready <= \<const0>\;
  s_axi_ctrl_bresp(1) <= \<const0>\;
  s_axi_ctrl_bresp(0) <= \<const0>\;
  s_axi_ctrl_bvalid <= \<const0>\;
  s_axi_ctrl_rdata(31) <= \<const0>\;
  s_axi_ctrl_rdata(30) <= \<const0>\;
  s_axi_ctrl_rdata(29) <= \<const0>\;
  s_axi_ctrl_rdata(28) <= \<const0>\;
  s_axi_ctrl_rdata(27) <= \<const0>\;
  s_axi_ctrl_rdata(26) <= \<const0>\;
  s_axi_ctrl_rdata(25) <= \<const0>\;
  s_axi_ctrl_rdata(24) <= \<const0>\;
  s_axi_ctrl_rdata(23) <= \<const0>\;
  s_axi_ctrl_rdata(22) <= \<const0>\;
  s_axi_ctrl_rdata(21) <= \<const0>\;
  s_axi_ctrl_rdata(20) <= \<const0>\;
  s_axi_ctrl_rdata(19) <= \<const0>\;
  s_axi_ctrl_rdata(18) <= \<const0>\;
  s_axi_ctrl_rdata(17) <= \<const0>\;
  s_axi_ctrl_rdata(16) <= \<const0>\;
  s_axi_ctrl_rdata(15) <= \<const0>\;
  s_axi_ctrl_rdata(14) <= \<const0>\;
  s_axi_ctrl_rdata(13) <= \<const0>\;
  s_axi_ctrl_rdata(12) <= \<const0>\;
  s_axi_ctrl_rdata(11) <= \<const0>\;
  s_axi_ctrl_rdata(10) <= \<const0>\;
  s_axi_ctrl_rdata(9) <= \<const0>\;
  s_axi_ctrl_rdata(8) <= \<const0>\;
  s_axi_ctrl_rdata(7) <= \<const0>\;
  s_axi_ctrl_rdata(6) <= \<const0>\;
  s_axi_ctrl_rdata(5) <= \<const0>\;
  s_axi_ctrl_rdata(4) <= \<const0>\;
  s_axi_ctrl_rdata(3) <= \<const0>\;
  s_axi_ctrl_rdata(2) <= \<const0>\;
  s_axi_ctrl_rdata(1) <= \<const0>\;
  s_axi_ctrl_rdata(0) <= \<const0>\;
  s_axi_ctrl_rresp(1) <= \<const0>\;
  s_axi_ctrl_rresp(0) <= \<const0>\;
  s_axi_ctrl_rvalid <= \<const0>\;
  s_axi_ctrl_wready <= \<const0>\;
  s_axi_rdata(31 downto 0) <= \^bram_rddata_a\(31 downto 0);
  s_axi_rid(0) <= \<const0>\;
  s_axi_rlast <= \<const0>\;
  s_axi_rresp(1) <= \<const0>\;
  s_axi_rresp(0) <= \<const0>\;
  s_axi_wready <= \^s_axi_wready\;
GND: unisim.vcomponents.GND
     port map (
      G => \<const0>\
    );
\gext_inst.abcv4_0_ext_inst\: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl_top
     port map (
      bram_addr_a(9 downto 0) => \^bram_addr_a\(11 downto 2),
      bram_en_a => bram_en_a,
      bram_we_a(3 downto 0) => bram_we_a(3 downto 0),
      s_axi_aclk => \^s_axi_aclk\,
      s_axi_araddr(9 downto 0) => s_axi_araddr(11 downto 2),
      s_axi_aresetn => s_axi_aresetn,
      s_axi_aresetn_0 => bram_rst_a,
      s_axi_arready => s_axi_arready,
      s_axi_arvalid => s_axi_arvalid,
      s_axi_awaddr(9 downto 0) => s_axi_awaddr(11 downto 2),
      s_axi_awvalid => s_axi_awvalid,
      s_axi_bready => s_axi_bready,
      s_axi_bvalid => s_axi_bvalid,
      s_axi_rready => s_axi_rready,
      s_axi_rvalid => s_axi_rvalid,
      s_axi_wready => \^s_axi_wready\,
      s_axi_wstrb(3 downto 0) => s_axi_wstrb(3 downto 0),
      s_axi_wvalid => s_axi_wvalid
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  port (
    s_axi_aclk : in STD_LOGIC;
    s_axi_aresetn : in STD_LOGIC;
    s_axi_awaddr : in STD_LOGIC_VECTOR ( 11 downto 0 );
    s_axi_awprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s_axi_awvalid : in STD_LOGIC;
    s_axi_awready : out STD_LOGIC;
    s_axi_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_wvalid : in STD_LOGIC;
    s_axi_wready : out STD_LOGIC;
    s_axi_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_bvalid : out STD_LOGIC;
    s_axi_bready : in STD_LOGIC;
    s_axi_araddr : in STD_LOGIC_VECTOR ( 11 downto 0 );
    s_axi_arprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s_axi_arvalid : in STD_LOGIC;
    s_axi_arready : out STD_LOGIC;
    s_axi_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_rvalid : out STD_LOGIC;
    s_axi_rready : in STD_LOGIC;
    bram_rst_a : out STD_LOGIC;
    bram_clk_a : out STD_LOGIC;
    bram_en_a : out STD_LOGIC;
    bram_we_a : out STD_LOGIC_VECTOR ( 3 downto 0 );
    bram_addr_a : out STD_LOGIC_VECTOR ( 11 downto 0 );
    bram_wrdata_a : out STD_LOGIC_VECTOR ( 31 downto 0 );
    bram_rddata_a : in STD_LOGIC_VECTOR ( 31 downto 0 )
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "system_axi_bram_ctrl_0_0,axi_bram_ctrl,{}";
  attribute downgradeipidentifiedwarnings : string;
  attribute downgradeipidentifiedwarnings of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "yes";
  attribute x_core_info : string;
  attribute x_core_info of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "axi_bram_ctrl,Vivado 2020.2";
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  signal \<const0>\ : STD_LOGIC;
  signal \^bram_addr_a\ : STD_LOGIC_VECTOR ( 11 downto 2 );
  signal NLW_U0_bram_clk_b_UNCONNECTED : STD_LOGIC;
  signal NLW_U0_bram_en_b_UNCONNECTED : STD_LOGIC;
  signal NLW_U0_bram_rst_b_UNCONNECTED : STD_LOGIC;
  signal NLW_U0_ecc_interrupt_UNCONNECTED : STD_LOGIC;
  signal NLW_U0_ecc_ue_UNCONNECTED : STD_LOGIC;
  signal NLW_U0_s_axi_ctrl_arready_UNCONNECTED : STD_LOGIC;
  signal NLW_U0_s_axi_ctrl_awready_UNCONNECTED : STD_LOGIC;
  signal NLW_U0_s_axi_ctrl_bvalid_UNCONNECTED : STD_LOGIC;
  signal NLW_U0_s_axi_ctrl_rvalid_UNCONNECTED : STD_LOGIC;
  signal NLW_U0_s_axi_ctrl_wready_UNCONNECTED : STD_LOGIC;
  signal NLW_U0_s_axi_rlast_UNCONNECTED : STD_LOGIC;
  signal NLW_U0_bram_addr_a_UNCONNECTED : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal NLW_U0_bram_addr_b_UNCONNECTED : STD_LOGIC_VECTOR ( 11 downto 0 );
  signal NLW_U0_bram_we_b_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_U0_bram_wrdata_b_UNCONNECTED : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal NLW_U0_s_axi_bid_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_U0_s_axi_bresp_UNCONNECTED : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal NLW_U0_s_axi_ctrl_bresp_UNCONNECTED : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal NLW_U0_s_axi_ctrl_rdata_UNCONNECTED : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal NLW_U0_s_axi_ctrl_rresp_UNCONNECTED : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal NLW_U0_s_axi_rid_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_U0_s_axi_rresp_UNCONNECTED : STD_LOGIC_VECTOR ( 1 downto 0 );
  attribute C_BRAM_ADDR_WIDTH : integer;
  attribute C_BRAM_ADDR_WIDTH of U0 : label is 10;
  attribute C_BRAM_INST_MODE : string;
  attribute C_BRAM_INST_MODE of U0 : label is "EXTERNAL";
  attribute C_ECC : integer;
  attribute C_ECC of U0 : label is 0;
  attribute C_ECC_ONOFF_RESET_VALUE : integer;
  attribute C_ECC_ONOFF_RESET_VALUE of U0 : label is 0;
  attribute C_ECC_TYPE : integer;
  attribute C_ECC_TYPE of U0 : label is 0;
  attribute C_FAMILY : string;
  attribute C_FAMILY of U0 : label is "zynq";
  attribute C_FAULT_INJECT : integer;
  attribute C_FAULT_INJECT of U0 : label is 0;
  attribute C_MEMORY_DEPTH : integer;
  attribute C_MEMORY_DEPTH of U0 : label is 1024;
  attribute C_RD_CMD_OPTIMIZATION : integer;
  attribute C_RD_CMD_OPTIMIZATION of U0 : label is 0;
  attribute C_READ_LATENCY : integer;
  attribute C_READ_LATENCY of U0 : label is 1;
  attribute C_SINGLE_PORT_BRAM : integer;
  attribute C_SINGLE_PORT_BRAM of U0 : label is 1;
  attribute C_S_AXI_ADDR_WIDTH : integer;
  attribute C_S_AXI_ADDR_WIDTH of U0 : label is 12;
  attribute C_S_AXI_CTRL_ADDR_WIDTH : integer;
  attribute C_S_AXI_CTRL_ADDR_WIDTH of U0 : label is 32;
  attribute C_S_AXI_CTRL_DATA_WIDTH : integer;
  attribute C_S_AXI_CTRL_DATA_WIDTH of U0 : label is 32;
  attribute C_S_AXI_DATA_WIDTH : integer;
  attribute C_S_AXI_DATA_WIDTH of U0 : label is 32;
  attribute C_S_AXI_ID_WIDTH : integer;
  attribute C_S_AXI_ID_WIDTH of U0 : label is 1;
  attribute C_S_AXI_PROTOCOL : string;
  attribute C_S_AXI_PROTOCOL of U0 : label is "AXI4LITE";
  attribute C_S_AXI_SUPPORTS_NARROW_BURST : integer;
  attribute C_S_AXI_SUPPORTS_NARROW_BURST of U0 : label is 0;
  attribute downgradeipidentifiedwarnings of U0 : label is "yes";
  attribute x_interface_info : string;
  attribute x_interface_info of bram_clk_a : signal is "xilinx.com:interface:bram:1.0 BRAM_PORTA CLK";
  attribute x_interface_info of bram_en_a : signal is "xilinx.com:interface:bram:1.0 BRAM_PORTA EN";
  attribute x_interface_info of bram_rst_a : signal is "xilinx.com:interface:bram:1.0 BRAM_PORTA RST";
  attribute x_interface_parameter : string;
  attribute x_interface_parameter of bram_rst_a : signal is "XIL_INTERFACENAME BRAM_PORTA, MASTER_TYPE BRAM_CTRL, MEM_SIZE 4096, MEM_WIDTH 32, MEM_ECC NONE, READ_WRITE_MODE READ_WRITE, READ_LATENCY 1";
  attribute x_interface_info of s_axi_aclk : signal is "xilinx.com:signal:clock:1.0 CLKIF CLK";
  attribute x_interface_parameter of s_axi_aclk : signal is "XIL_INTERFACENAME CLKIF, ASSOCIATED_BUSIF S_AXI:S_AXI_CTRL, ASSOCIATED_RESET s_axi_aresetn, FREQ_HZ 50000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN system_processing_system7_0_0_FCLK_CLK0, INSERT_VIP 0";
  attribute x_interface_info of s_axi_aresetn : signal is "xilinx.com:signal:reset:1.0 RSTIF RST";
  attribute x_interface_parameter of s_axi_aresetn : signal is "XIL_INTERFACENAME RSTIF, POLARITY ACTIVE_LOW, INSERT_VIP 0";
  attribute x_interface_info of s_axi_arready : signal is "xilinx.com:interface:aximm:1.0 S_AXI ARREADY";
  attribute x_interface_info of s_axi_arvalid : signal is "xilinx.com:interface:aximm:1.0 S_AXI ARVALID";
  attribute x_interface_info of s_axi_awready : signal is "xilinx.com:interface:aximm:1.0 S_AXI AWREADY";
  attribute x_interface_info of s_axi_awvalid : signal is "xilinx.com:interface:aximm:1.0 S_AXI AWVALID";
  attribute x_interface_info of s_axi_bready : signal is "xilinx.com:interface:aximm:1.0 S_AXI BREADY";
  attribute x_interface_info of s_axi_bvalid : signal is "xilinx.com:interface:aximm:1.0 S_AXI BVALID";
  attribute x_interface_info of s_axi_rready : signal is "xilinx.com:interface:aximm:1.0 S_AXI RREADY";
  attribute x_interface_info of s_axi_rvalid : signal is "xilinx.com:interface:aximm:1.0 S_AXI RVALID";
  attribute x_interface_info of s_axi_wready : signal is "xilinx.com:interface:aximm:1.0 S_AXI WREADY";
  attribute x_interface_info of s_axi_wvalid : signal is "xilinx.com:interface:aximm:1.0 S_AXI WVALID";
  attribute x_interface_info of bram_addr_a : signal is "xilinx.com:interface:bram:1.0 BRAM_PORTA ADDR";
  attribute x_interface_info of bram_rddata_a : signal is "xilinx.com:interface:bram:1.0 BRAM_PORTA DOUT";
  attribute x_interface_info of bram_we_a : signal is "xilinx.com:interface:bram:1.0 BRAM_PORTA WE";
  attribute x_interface_info of bram_wrdata_a : signal is "xilinx.com:interface:bram:1.0 BRAM_PORTA DIN";
  attribute x_interface_info of s_axi_araddr : signal is "xilinx.com:interface:aximm:1.0 S_AXI ARADDR";
  attribute x_interface_info of s_axi_arprot : signal is "xilinx.com:interface:aximm:1.0 S_AXI ARPROT";
  attribute x_interface_info of s_axi_awaddr : signal is "xilinx.com:interface:aximm:1.0 S_AXI AWADDR";
  attribute x_interface_parameter of s_axi_awaddr : signal is "XIL_INTERFACENAME S_AXI, DATA_WIDTH 32, PROTOCOL AXI4LITE, FREQ_HZ 50000000, ID_WIDTH 0, ADDR_WIDTH 12, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 1, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 8, NUM_WRITE_OUTSTANDING 8, MAX_BURST_LENGTH 1, PHASE 0.000, CLK_DOMAIN system_processing_system7_0_0_FCLK_CLK0, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0";
  attribute x_interface_info of s_axi_awprot : signal is "xilinx.com:interface:aximm:1.0 S_AXI AWPROT";
  attribute x_interface_info of s_axi_bresp : signal is "xilinx.com:interface:aximm:1.0 S_AXI BRESP";
  attribute x_interface_info of s_axi_rdata : signal is "xilinx.com:interface:aximm:1.0 S_AXI RDATA";
  attribute x_interface_info of s_axi_rresp : signal is "xilinx.com:interface:aximm:1.0 S_AXI RRESP";
  attribute x_interface_info of s_axi_wdata : signal is "xilinx.com:interface:aximm:1.0 S_AXI WDATA";
  attribute x_interface_info of s_axi_wstrb : signal is "xilinx.com:interface:aximm:1.0 S_AXI WSTRB";
begin
  bram_addr_a(11 downto 2) <= \^bram_addr_a\(11 downto 2);
  bram_addr_a(1) <= \<const0>\;
  bram_addr_a(0) <= \<const0>\;
  s_axi_bresp(1) <= \<const0>\;
  s_axi_bresp(0) <= \<const0>\;
  s_axi_rresp(1) <= \<const0>\;
  s_axi_rresp(0) <= \<const0>\;
GND: unisim.vcomponents.GND
     port map (
      G => \<const0>\
    );
U0: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_axi_bram_ctrl
     port map (
      bram_addr_a(11 downto 2) => \^bram_addr_a\(11 downto 2),
      bram_addr_a(1 downto 0) => NLW_U0_bram_addr_a_UNCONNECTED(1 downto 0),
      bram_addr_b(11 downto 0) => NLW_U0_bram_addr_b_UNCONNECTED(11 downto 0),
      bram_clk_a => bram_clk_a,
      bram_clk_b => NLW_U0_bram_clk_b_UNCONNECTED,
      bram_en_a => bram_en_a,
      bram_en_b => NLW_U0_bram_en_b_UNCONNECTED,
      bram_rddata_a(31 downto 0) => bram_rddata_a(31 downto 0),
      bram_rddata_b(31 downto 0) => B"00000000000000000000000000000000",
      bram_rst_a => bram_rst_a,
      bram_rst_b => NLW_U0_bram_rst_b_UNCONNECTED,
      bram_we_a(3 downto 0) => bram_we_a(3 downto 0),
      bram_we_b(3 downto 0) => NLW_U0_bram_we_b_UNCONNECTED(3 downto 0),
      bram_wrdata_a(31 downto 0) => bram_wrdata_a(31 downto 0),
      bram_wrdata_b(31 downto 0) => NLW_U0_bram_wrdata_b_UNCONNECTED(31 downto 0),
      ecc_interrupt => NLW_U0_ecc_interrupt_UNCONNECTED,
      ecc_ue => NLW_U0_ecc_ue_UNCONNECTED,
      s_axi_aclk => s_axi_aclk,
      s_axi_araddr(11 downto 2) => s_axi_araddr(11 downto 2),
      s_axi_araddr(1 downto 0) => B"00",
      s_axi_arburst(1 downto 0) => B"00",
      s_axi_arcache(3 downto 0) => B"0000",
      s_axi_aresetn => s_axi_aresetn,
      s_axi_arid(0) => '0',
      s_axi_arlen(7 downto 0) => B"00000000",
      s_axi_arlock => '0',
      s_axi_arprot(2 downto 0) => B"000",
      s_axi_arready => s_axi_arready,
      s_axi_arsize(2 downto 0) => B"000",
      s_axi_arvalid => s_axi_arvalid,
      s_axi_awaddr(11 downto 2) => s_axi_awaddr(11 downto 2),
      s_axi_awaddr(1 downto 0) => B"00",
      s_axi_awburst(1 downto 0) => B"00",
      s_axi_awcache(3 downto 0) => B"0000",
      s_axi_awid(0) => '0',
      s_axi_awlen(7 downto 0) => B"00000000",
      s_axi_awlock => '0',
      s_axi_awprot(2 downto 0) => B"000",
      s_axi_awready => s_axi_awready,
      s_axi_awsize(2 downto 0) => B"000",
      s_axi_awvalid => s_axi_awvalid,
      s_axi_bid(0) => NLW_U0_s_axi_bid_UNCONNECTED(0),
      s_axi_bready => s_axi_bready,
      s_axi_bresp(1 downto 0) => NLW_U0_s_axi_bresp_UNCONNECTED(1 downto 0),
      s_axi_bvalid => s_axi_bvalid,
      s_axi_ctrl_araddr(31 downto 0) => B"00000000000000000000000000000000",
      s_axi_ctrl_arready => NLW_U0_s_axi_ctrl_arready_UNCONNECTED,
      s_axi_ctrl_arvalid => '0',
      s_axi_ctrl_awaddr(31 downto 0) => B"00000000000000000000000000000000",
      s_axi_ctrl_awready => NLW_U0_s_axi_ctrl_awready_UNCONNECTED,
      s_axi_ctrl_awvalid => '0',
      s_axi_ctrl_bready => '0',
      s_axi_ctrl_bresp(1 downto 0) => NLW_U0_s_axi_ctrl_bresp_UNCONNECTED(1 downto 0),
      s_axi_ctrl_bvalid => NLW_U0_s_axi_ctrl_bvalid_UNCONNECTED,
      s_axi_ctrl_rdata(31 downto 0) => NLW_U0_s_axi_ctrl_rdata_UNCONNECTED(31 downto 0),
      s_axi_ctrl_rready => '0',
      s_axi_ctrl_rresp(1 downto 0) => NLW_U0_s_axi_ctrl_rresp_UNCONNECTED(1 downto 0),
      s_axi_ctrl_rvalid => NLW_U0_s_axi_ctrl_rvalid_UNCONNECTED,
      s_axi_ctrl_wdata(31 downto 0) => B"00000000000000000000000000000000",
      s_axi_ctrl_wready => NLW_U0_s_axi_ctrl_wready_UNCONNECTED,
      s_axi_ctrl_wvalid => '0',
      s_axi_rdata(31 downto 0) => s_axi_rdata(31 downto 0),
      s_axi_rid(0) => NLW_U0_s_axi_rid_UNCONNECTED(0),
      s_axi_rlast => NLW_U0_s_axi_rlast_UNCONNECTED,
      s_axi_rready => s_axi_rready,
      s_axi_rresp(1 downto 0) => NLW_U0_s_axi_rresp_UNCONNECTED(1 downto 0),
      s_axi_rvalid => s_axi_rvalid,
      s_axi_wdata(31 downto 0) => s_axi_wdata(31 downto 0),
      s_axi_wlast => '0',
      s_axi_wready => s_axi_wready,
      s_axi_wstrb(3 downto 0) => s_axi_wstrb(3 downto 0),
      s_axi_wvalid => s_axi_wvalid
    );
end STRUCTURE;
