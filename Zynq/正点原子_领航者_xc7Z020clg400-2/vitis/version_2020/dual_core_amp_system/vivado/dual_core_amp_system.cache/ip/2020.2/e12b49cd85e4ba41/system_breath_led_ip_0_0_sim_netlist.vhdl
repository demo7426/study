-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.2 (win64) Build 3064766 Wed Nov 18 09:12:45 MST 2020
-- Date        : Tue Jul 15 16:03:21 2025
-- Host        : DESKTOP-D3LRDNP running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
--               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ system_breath_led_ip_0_0_sim_netlist.vhdl
-- Design      : system_breath_led_ip_0_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xc7z020clg400-2
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_breath_led is
  port (
    s0_axi_aresetn_0 : out STD_LOGIC;
    led : out STD_LOGIC;
    s0_axi_aclk : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 10 downto 0 );
    s0_axi_aresetn : in STD_LOGIC;
    led_0 : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_breath_led;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_breath_led is
  signal cnt_2ms0 : STD_LOGIC;
  signal \cnt_2ms[6]_i_2_n_0\ : STD_LOGIC;
  signal \cnt_2ms[8]_i_2_n_0\ : STD_LOGIC;
  signal \cnt_2ms[9]_i_3_n_0\ : STD_LOGIC;
  signal \cnt_2ms[9]_i_4_n_0\ : STD_LOGIC;
  signal \cnt_2ms[9]_i_5_n_0\ : STD_LOGIC;
  signal \cnt_2ms[9]_i_6_n_0\ : STD_LOGIC;
  signal \cnt_2ms[9]_i_7_n_0\ : STD_LOGIC;
  signal cnt_2ms_reg : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal \cnt_2s[9]_i_1_n_0\ : STD_LOGIC;
  signal \cnt_2s[9]_i_2_n_0\ : STD_LOGIC;
  signal \cnt_2s[9]_i_3_n_0\ : STD_LOGIC;
  signal \cnt_2s[9]_i_4_n_0\ : STD_LOGIC;
  signal \cnt_2s_inferred__0/i__carry__0_n_0\ : STD_LOGIC;
  signal \cnt_2s_inferred__0/i__carry__0_n_1\ : STD_LOGIC;
  signal \cnt_2s_inferred__0/i__carry__0_n_2\ : STD_LOGIC;
  signal \cnt_2s_inferred__0/i__carry__0_n_3\ : STD_LOGIC;
  signal \cnt_2s_inferred__0/i__carry__0_n_4\ : STD_LOGIC;
  signal \cnt_2s_inferred__0/i__carry__0_n_5\ : STD_LOGIC;
  signal \cnt_2s_inferred__0/i__carry__0_n_6\ : STD_LOGIC;
  signal \cnt_2s_inferred__0/i__carry__0_n_7\ : STD_LOGIC;
  signal \cnt_2s_inferred__0/i__carry__1_n_3\ : STD_LOGIC;
  signal \cnt_2s_inferred__0/i__carry__1_n_6\ : STD_LOGIC;
  signal \cnt_2s_inferred__0/i__carry__1_n_7\ : STD_LOGIC;
  signal \cnt_2s_inferred__0/i__carry_n_0\ : STD_LOGIC;
  signal \cnt_2s_inferred__0/i__carry_n_1\ : STD_LOGIC;
  signal \cnt_2s_inferred__0/i__carry_n_2\ : STD_LOGIC;
  signal \cnt_2s_inferred__0/i__carry_n_3\ : STD_LOGIC;
  signal \cnt_2s_inferred__0/i__carry_n_4\ : STD_LOGIC;
  signal \cnt_2s_inferred__0/i__carry_n_5\ : STD_LOGIC;
  signal \cnt_2s_inferred__0/i__carry_n_6\ : STD_LOGIC;
  signal \cnt_2s_inferred__0/i__carry_n_7\ : STD_LOGIC;
  signal cnt_2s_reg : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal cnt_2us : STD_LOGIC_VECTOR ( 6 downto 0 );
  signal \cnt_2us[6]_i_2_n_0\ : STD_LOGIC;
  signal cnt_2us_0 : STD_LOGIC_VECTOR ( 6 downto 0 );
  signal \freq_step[0]_i_1_n_0\ : STD_LOGIC;
  signal \freq_step[0]_i_2_n_0\ : STD_LOGIC;
  signal \freq_step[0]_i_3_n_0\ : STD_LOGIC;
  signal \freq_step[0]_i_4_n_0\ : STD_LOGIC;
  signal \freq_step[3]_i_1_n_0\ : STD_LOGIC;
  signal \freq_step[3]_i_3_n_0\ : STD_LOGIC;
  signal \freq_step[3]_i_4_n_0\ : STD_LOGIC;
  signal \i__carry__0_i_1__0_n_0\ : STD_LOGIC;
  signal \i__carry__0_i_1_n_0\ : STD_LOGIC;
  signal \i__carry__0_i_2__0_n_0\ : STD_LOGIC;
  signal \i__carry__0_i_2_n_0\ : STD_LOGIC;
  signal \i__carry__0_i_3_n_0\ : STD_LOGIC;
  signal \i__carry__0_i_4_n_0\ : STD_LOGIC;
  signal \i__carry__1_i_1_n_0\ : STD_LOGIC;
  signal \i__carry__1_i_2_n_0\ : STD_LOGIC;
  signal \i__carry_i_10_n_0\ : STD_LOGIC;
  signal \i__carry_i_1__0_n_0\ : STD_LOGIC;
  signal \i__carry_i_1_n_0\ : STD_LOGIC;
  signal \i__carry_i_2__0_n_0\ : STD_LOGIC;
  signal \i__carry_i_2_n_0\ : STD_LOGIC;
  signal \i__carry_i_3__0_n_0\ : STD_LOGIC;
  signal \i__carry_i_3_n_0\ : STD_LOGIC;
  signal \i__carry_i_4__0_n_0\ : STD_LOGIC;
  signal \i__carry_i_4_n_0\ : STD_LOGIC;
  signal \i__carry_i_5__0_n_0\ : STD_LOGIC;
  signal \i__carry_i_5_n_0\ : STD_LOGIC;
  signal \i__carry_i_6__0_n_0\ : STD_LOGIC;
  signal \i__carry_i_6_n_0\ : STD_LOGIC;
  signal \i__carry_i_7__0_n_0\ : STD_LOGIC;
  signal \i__carry_i_7_n_0\ : STD_LOGIC;
  signal \i__carry_i_8__0_n_0\ : STD_LOGIC;
  signal \i__carry_i_8_n_0\ : STD_LOGIC;
  signal \i__carry_i_9_n_0\ : STD_LOGIC;
  signal \in\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal inc_dec_flag : STD_LOGIC;
  signal inc_dec_flag_i_1_n_0 : STD_LOGIC;
  signal led_t : STD_LOGIC;
  signal led_t2 : STD_LOGIC;
  signal led_t21_in : STD_LOGIC;
  signal \led_t2_carry__0_i_1_n_0\ : STD_LOGIC;
  signal \led_t2_carry__0_i_2_n_0\ : STD_LOGIC;
  signal led_t2_carry_i_1_n_0 : STD_LOGIC;
  signal led_t2_carry_i_2_n_0 : STD_LOGIC;
  signal led_t2_carry_i_3_n_0 : STD_LOGIC;
  signal led_t2_carry_i_4_n_0 : STD_LOGIC;
  signal led_t2_carry_i_5_n_0 : STD_LOGIC;
  signal led_t2_carry_i_6_n_0 : STD_LOGIC;
  signal led_t2_carry_i_7_n_0 : STD_LOGIC;
  signal led_t2_carry_i_8_n_0 : STD_LOGIC;
  signal led_t2_carry_n_0 : STD_LOGIC;
  signal led_t2_carry_n_1 : STD_LOGIC;
  signal led_t2_carry_n_2 : STD_LOGIC;
  signal led_t2_carry_n_3 : STD_LOGIC;
  signal \led_t2_inferred__0/i__carry_n_0\ : STD_LOGIC;
  signal \led_t2_inferred__0/i__carry_n_1\ : STD_LOGIC;
  signal \led_t2_inferred__0/i__carry_n_2\ : STD_LOGIC;
  signal \led_t2_inferred__0/i__carry_n_3\ : STD_LOGIC;
  signal led_t_i_1_n_0 : STD_LOGIC;
  signal \p_0_in__0\ : STD_LOGIC_VECTOR ( 9 downto 0 );
  signal p_1_in : STD_LOGIC_VECTOR ( 3 downto 1 );
  signal \^s0_axi_aresetn_0\ : STD_LOGIC;
  signal \NLW_cnt_2s_inferred__0/i__carry__1_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 1 );
  signal \NLW_cnt_2s_inferred__0/i__carry__1_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 2 );
  signal NLW_led_t2_carry_O_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_led_t2_carry__0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 1 );
  signal \NLW_led_t2_carry__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_led_t2_inferred__0/i__carry_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_led_t2_inferred__0/i__carry__0_CO_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 1 );
  signal \NLW_led_t2_inferred__0/i__carry__0_O_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \cnt_2ms[0]_i_1\ : label is "soft_lutpair8";
  attribute SOFT_HLUTNM of \cnt_2ms[1]_i_1\ : label is "soft_lutpair8";
  attribute SOFT_HLUTNM of \cnt_2ms[2]_i_1\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \cnt_2ms[3]_i_1\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \cnt_2ms[4]_i_1\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \cnt_2ms[6]_i_2\ : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of \cnt_2ms[8]_i_2\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \cnt_2ms[9]_i_5\ : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of \cnt_2ms[9]_i_6\ : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of \cnt_2ms[9]_i_7\ : label is "soft_lutpair5";
  attribute SOFT_HLUTNM of \cnt_2s[9]_i_3\ : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of \cnt_2us[0]_i_1\ : label is "soft_lutpair9";
  attribute SOFT_HLUTNM of \cnt_2us[1]_i_1\ : label is "soft_lutpair9";
  attribute SOFT_HLUTNM of \cnt_2us[3]_i_1\ : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of \cnt_2us[4]_i_1\ : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of \cnt_2us[6]_i_2\ : label is "soft_lutpair5";
  attribute SOFT_HLUTNM of \freq_step[1]_i_1\ : label is "soft_lutpair7";
  attribute SOFT_HLUTNM of \freq_step[3]_i_2\ : label is "soft_lutpair7";
  attribute SOFT_HLUTNM of inc_dec_flag_i_1 : label is "soft_lutpair6";
  attribute COMPARATOR_THRESHOLD : integer;
  attribute COMPARATOR_THRESHOLD of led_t2_carry : label is 11;
  attribute COMPARATOR_THRESHOLD of \led_t2_carry__0\ : label is 11;
  attribute COMPARATOR_THRESHOLD of \led_t2_inferred__0/i__carry\ : label is 11;
  attribute COMPARATOR_THRESHOLD of \led_t2_inferred__0/i__carry__0\ : label is 11;
  attribute SOFT_HLUTNM of led_t_i_1 : label is "soft_lutpair6";
begin
  s0_axi_aresetn_0 <= \^s0_axi_aresetn_0\;
axi_awready_i_1: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => s0_axi_aresetn,
      O => \^s0_axi_aresetn_0\
    );
\cnt_2ms[0]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => cnt_2ms_reg(0),
      O => \p_0_in__0\(0)
    );
\cnt_2ms[1]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => cnt_2ms_reg(1),
      I1 => cnt_2ms_reg(0),
      O => \p_0_in__0\(1)
    );
\cnt_2ms[2]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"6A"
    )
        port map (
      I0 => cnt_2ms_reg(2),
      I1 => cnt_2ms_reg(1),
      I2 => cnt_2ms_reg(0),
      O => \p_0_in__0\(2)
    );
\cnt_2ms[3]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"2AAA8000"
    )
        port map (
      I0 => \cnt_2ms[9]_i_4_n_0\,
      I1 => cnt_2ms_reg(0),
      I2 => cnt_2ms_reg(1),
      I3 => cnt_2ms_reg(2),
      I4 => cnt_2ms_reg(3),
      O => \p_0_in__0\(3)
    );
\cnt_2ms[4]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"6AAAAAAA"
    )
        port map (
      I0 => cnt_2ms_reg(4),
      I1 => cnt_2ms_reg(2),
      I2 => cnt_2ms_reg(1),
      I3 => cnt_2ms_reg(0),
      I4 => cnt_2ms_reg(3),
      O => \p_0_in__0\(4)
    );
\cnt_2ms[5]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"A2AA0800"
    )
        port map (
      I0 => \cnt_2ms[9]_i_4_n_0\,
      I1 => cnt_2ms_reg(3),
      I2 => \cnt_2ms[6]_i_2_n_0\,
      I3 => cnt_2ms_reg(4),
      I4 => cnt_2ms_reg(5),
      O => \p_0_in__0\(5)
    );
\cnt_2ms[6]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"A2AAAAAA08000000"
    )
        port map (
      I0 => \cnt_2ms[9]_i_4_n_0\,
      I1 => cnt_2ms_reg(4),
      I2 => \cnt_2ms[6]_i_2_n_0\,
      I3 => cnt_2ms_reg(3),
      I4 => cnt_2ms_reg(5),
      I5 => cnt_2ms_reg(6),
      O => \p_0_in__0\(6)
    );
\cnt_2ms[6]_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"7F"
    )
        port map (
      I0 => cnt_2ms_reg(0),
      I1 => cnt_2ms_reg(1),
      I2 => cnt_2ms_reg(2),
      O => \cnt_2ms[6]_i_2_n_0\
    );
\cnt_2ms[7]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"A2AA0800"
    )
        port map (
      I0 => \cnt_2ms[9]_i_4_n_0\,
      I1 => cnt_2ms_reg(5),
      I2 => \cnt_2ms[8]_i_2_n_0\,
      I3 => cnt_2ms_reg(6),
      I4 => cnt_2ms_reg(7),
      O => \p_0_in__0\(7)
    );
\cnt_2ms[8]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"AA2AAAAA00800000"
    )
        port map (
      I0 => \cnt_2ms[9]_i_4_n_0\,
      I1 => cnt_2ms_reg(7),
      I2 => cnt_2ms_reg(6),
      I3 => \cnt_2ms[8]_i_2_n_0\,
      I4 => cnt_2ms_reg(5),
      I5 => cnt_2ms_reg(8),
      O => \p_0_in__0\(8)
    );
\cnt_2ms[8]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"7FFFFFFF"
    )
        port map (
      I0 => cnt_2ms_reg(3),
      I1 => cnt_2ms_reg(0),
      I2 => cnt_2ms_reg(1),
      I3 => cnt_2ms_reg(2),
      I4 => cnt_2ms_reg(4),
      O => \cnt_2ms[8]_i_2_n_0\
    );
\cnt_2ms[9]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000010000000000"
    )
        port map (
      I0 => \cnt_2us[6]_i_2_n_0\,
      I1 => cnt_2us(2),
      I2 => cnt_2us(4),
      I3 => cnt_2us(6),
      I4 => cnt_2us(3),
      I5 => cnt_2us(5),
      O => cnt_2ms0
    );
\cnt_2ms[9]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"BFFF400000000000"
    )
        port map (
      I0 => \cnt_2ms[9]_i_3_n_0\,
      I1 => cnt_2ms_reg(6),
      I2 => cnt_2ms_reg(7),
      I3 => cnt_2ms_reg(8),
      I4 => cnt_2ms_reg(9),
      I5 => \cnt_2ms[9]_i_4_n_0\,
      O => \p_0_in__0\(9)
    );
\cnt_2ms[9]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7FFFFFFFFFFFFFFF"
    )
        port map (
      I0 => cnt_2ms_reg(4),
      I1 => cnt_2ms_reg(2),
      I2 => cnt_2ms_reg(1),
      I3 => cnt_2ms_reg(0),
      I4 => cnt_2ms_reg(3),
      I5 => cnt_2ms_reg(5),
      O => \cnt_2ms[9]_i_3_n_0\
    );
\cnt_2ms[9]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFEFFFFFFFF"
    )
        port map (
      I0 => \cnt_2ms[9]_i_5_n_0\,
      I1 => \cnt_2ms[9]_i_6_n_0\,
      I2 => cnt_2ms_reg(3),
      I3 => cnt_2ms_reg(4),
      I4 => \cnt_2s[9]_i_2_n_0\,
      I5 => \cnt_2ms[9]_i_7_n_0\,
      O => \cnt_2ms[9]_i_4_n_0\
    );
\cnt_2ms[9]_i_5\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"7FFF"
    )
        port map (
      I0 => cnt_2ms_reg(0),
      I1 => cnt_2ms_reg(1),
      I2 => cnt_2ms_reg(9),
      I3 => cnt_2ms_reg(2),
      O => \cnt_2ms[9]_i_5_n_0\
    );
\cnt_2ms[9]_i_6\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"7FFF"
    )
        port map (
      I0 => cnt_2ms_reg(7),
      I1 => cnt_2ms_reg(5),
      I2 => cnt_2ms_reg(8),
      I3 => cnt_2ms_reg(6),
      O => \cnt_2ms[9]_i_6_n_0\
    );
\cnt_2ms[9]_i_7\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => cnt_2us(2),
      I1 => cnt_2us(1),
      I2 => cnt_2us(0),
      O => \cnt_2ms[9]_i_7_n_0\
    );
\cnt_2ms_reg[0]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => cnt_2ms0,
      CLR => \^s0_axi_aresetn_0\,
      D => \p_0_in__0\(0),
      Q => cnt_2ms_reg(0)
    );
\cnt_2ms_reg[1]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => cnt_2ms0,
      CLR => \^s0_axi_aresetn_0\,
      D => \p_0_in__0\(1),
      Q => cnt_2ms_reg(1)
    );
\cnt_2ms_reg[2]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => cnt_2ms0,
      CLR => \^s0_axi_aresetn_0\,
      D => \p_0_in__0\(2),
      Q => cnt_2ms_reg(2)
    );
\cnt_2ms_reg[3]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => cnt_2ms0,
      CLR => \^s0_axi_aresetn_0\,
      D => \p_0_in__0\(3),
      Q => cnt_2ms_reg(3)
    );
\cnt_2ms_reg[4]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => cnt_2ms0,
      CLR => \^s0_axi_aresetn_0\,
      D => \p_0_in__0\(4),
      Q => cnt_2ms_reg(4)
    );
\cnt_2ms_reg[5]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => cnt_2ms0,
      CLR => \^s0_axi_aresetn_0\,
      D => \p_0_in__0\(5),
      Q => cnt_2ms_reg(5)
    );
\cnt_2ms_reg[6]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => cnt_2ms0,
      CLR => \^s0_axi_aresetn_0\,
      D => \p_0_in__0\(6),
      Q => cnt_2ms_reg(6)
    );
\cnt_2ms_reg[7]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => cnt_2ms0,
      CLR => \^s0_axi_aresetn_0\,
      D => \p_0_in__0\(7),
      Q => cnt_2ms_reg(7)
    );
\cnt_2ms_reg[8]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => cnt_2ms0,
      CLR => \^s0_axi_aresetn_0\,
      D => \p_0_in__0\(8),
      Q => cnt_2ms_reg(8)
    );
\cnt_2ms_reg[9]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => cnt_2ms0,
      CLR => \^s0_axi_aresetn_0\,
      D => \p_0_in__0\(9),
      Q => cnt_2ms_reg(9)
    );
\cnt_2s[9]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000001"
    )
        port map (
      I0 => \cnt_2s[9]_i_2_n_0\,
      I1 => cnt_2us(2),
      I2 => \cnt_2us[6]_i_2_n_0\,
      I3 => \cnt_2s[9]_i_3_n_0\,
      I4 => \cnt_2s[9]_i_4_n_0\,
      I5 => \cnt_2ms[6]_i_2_n_0\,
      O => \cnt_2s[9]_i_1_n_0\
    );
\cnt_2s[9]_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFDF"
    )
        port map (
      I0 => cnt_2us(5),
      I1 => cnt_2us(3),
      I2 => cnt_2us(6),
      I3 => cnt_2us(4),
      O => \cnt_2s[9]_i_2_n_0\
    );
\cnt_2s[9]_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"DF"
    )
        port map (
      I0 => cnt_2ms_reg(6),
      I1 => cnt_2ms_reg(3),
      I2 => cnt_2ms_reg(5),
      O => \cnt_2s[9]_i_3_n_0\
    );
\cnt_2s[9]_i_4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FF7F"
    )
        port map (
      I0 => cnt_2ms_reg(9),
      I1 => cnt_2ms_reg(7),
      I2 => cnt_2ms_reg(8),
      I3 => cnt_2ms_reg(4),
      O => \cnt_2s[9]_i_4_n_0\
    );
\cnt_2s_inferred__0/i__carry\: unisim.vcomponents.CARRY4
     port map (
      CI => '0',
      CO(3) => \cnt_2s_inferred__0/i__carry_n_0\,
      CO(2) => \cnt_2s_inferred__0/i__carry_n_1\,
      CO(1) => \cnt_2s_inferred__0/i__carry_n_2\,
      CO(0) => \cnt_2s_inferred__0/i__carry_n_3\,
      CYINIT => '0',
      DI(3) => \i__carry_i_1_n_0\,
      DI(2) => \i__carry_i_2_n_0\,
      DI(1) => \i__carry_i_3_n_0\,
      DI(0) => \i__carry_i_4_n_0\,
      O(3) => \cnt_2s_inferred__0/i__carry_n_4\,
      O(2) => \cnt_2s_inferred__0/i__carry_n_5\,
      O(1) => \cnt_2s_inferred__0/i__carry_n_6\,
      O(0) => \cnt_2s_inferred__0/i__carry_n_7\,
      S(3) => \i__carry_i_5__0_n_0\,
      S(2) => \i__carry_i_6__0_n_0\,
      S(1) => \i__carry_i_7__0_n_0\,
      S(0) => \i__carry_i_8__0_n_0\
    );
\cnt_2s_inferred__0/i__carry__0\: unisim.vcomponents.CARRY4
     port map (
      CI => \cnt_2s_inferred__0/i__carry_n_0\,
      CO(3) => \cnt_2s_inferred__0/i__carry__0_n_0\,
      CO(2) => \cnt_2s_inferred__0/i__carry__0_n_1\,
      CO(1) => \cnt_2s_inferred__0/i__carry__0_n_2\,
      CO(0) => \cnt_2s_inferred__0/i__carry__0_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => B"0000",
      O(3) => \cnt_2s_inferred__0/i__carry__0_n_4\,
      O(2) => \cnt_2s_inferred__0/i__carry__0_n_5\,
      O(1) => \cnt_2s_inferred__0/i__carry__0_n_6\,
      O(0) => \cnt_2s_inferred__0/i__carry__0_n_7\,
      S(3) => \i__carry__0_i_1_n_0\,
      S(2) => \i__carry__0_i_2_n_0\,
      S(1) => \i__carry__0_i_3_n_0\,
      S(0) => \i__carry__0_i_4_n_0\
    );
\cnt_2s_inferred__0/i__carry__1\: unisim.vcomponents.CARRY4
     port map (
      CI => \cnt_2s_inferred__0/i__carry__0_n_0\,
      CO(3 downto 1) => \NLW_cnt_2s_inferred__0/i__carry__1_CO_UNCONNECTED\(3 downto 1),
      CO(0) => \cnt_2s_inferred__0/i__carry__1_n_3\,
      CYINIT => '0',
      DI(3 downto 0) => B"0000",
      O(3 downto 2) => \NLW_cnt_2s_inferred__0/i__carry__1_O_UNCONNECTED\(3 downto 2),
      O(1) => \cnt_2s_inferred__0/i__carry__1_n_6\,
      O(0) => \cnt_2s_inferred__0/i__carry__1_n_7\,
      S(3 downto 2) => B"00",
      S(1) => \i__carry__1_i_1_n_0\,
      S(0) => \i__carry__1_i_2_n_0\
    );
\cnt_2s_reg[0]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => \cnt_2s[9]_i_1_n_0\,
      CLR => \^s0_axi_aresetn_0\,
      D => \cnt_2s_inferred__0/i__carry_n_7\,
      Q => cnt_2s_reg(0)
    );
\cnt_2s_reg[1]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => \cnt_2s[9]_i_1_n_0\,
      CLR => \^s0_axi_aresetn_0\,
      D => \cnt_2s_inferred__0/i__carry_n_6\,
      Q => cnt_2s_reg(1)
    );
\cnt_2s_reg[2]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => \cnt_2s[9]_i_1_n_0\,
      CLR => \^s0_axi_aresetn_0\,
      D => \cnt_2s_inferred__0/i__carry_n_5\,
      Q => cnt_2s_reg(2)
    );
\cnt_2s_reg[3]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => \cnt_2s[9]_i_1_n_0\,
      CLR => \^s0_axi_aresetn_0\,
      D => \cnt_2s_inferred__0/i__carry_n_4\,
      Q => cnt_2s_reg(3)
    );
\cnt_2s_reg[4]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => \cnt_2s[9]_i_1_n_0\,
      CLR => \^s0_axi_aresetn_0\,
      D => \cnt_2s_inferred__0/i__carry__0_n_7\,
      Q => cnt_2s_reg(4)
    );
\cnt_2s_reg[5]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => \cnt_2s[9]_i_1_n_0\,
      CLR => \^s0_axi_aresetn_0\,
      D => \cnt_2s_inferred__0/i__carry__0_n_6\,
      Q => cnt_2s_reg(5)
    );
\cnt_2s_reg[6]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => \cnt_2s[9]_i_1_n_0\,
      CLR => \^s0_axi_aresetn_0\,
      D => \cnt_2s_inferred__0/i__carry__0_n_5\,
      Q => cnt_2s_reg(6)
    );
\cnt_2s_reg[7]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => \cnt_2s[9]_i_1_n_0\,
      CLR => \^s0_axi_aresetn_0\,
      D => \cnt_2s_inferred__0/i__carry__0_n_4\,
      Q => cnt_2s_reg(7)
    );
\cnt_2s_reg[8]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => \cnt_2s[9]_i_1_n_0\,
      CLR => \^s0_axi_aresetn_0\,
      D => \cnt_2s_inferred__0/i__carry__1_n_7\,
      Q => cnt_2s_reg(8)
    );
\cnt_2s_reg[9]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => \cnt_2s[9]_i_1_n_0\,
      CLR => \^s0_axi_aresetn_0\,
      D => \cnt_2s_inferred__0/i__carry__1_n_6\,
      Q => cnt_2s_reg(9)
    );
\cnt_2us[0]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => cnt_2us(0),
      O => cnt_2us_0(0)
    );
\cnt_2us[1]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => cnt_2us(0),
      I1 => cnt_2us(1),
      O => cnt_2us_0(1)
    );
\cnt_2us[2]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFF00000000FFDF"
    )
        port map (
      I0 => cnt_2us(5),
      I1 => cnt_2us(3),
      I2 => cnt_2us(6),
      I3 => cnt_2us(4),
      I4 => cnt_2us(2),
      I5 => \cnt_2us[6]_i_2_n_0\,
      O => cnt_2us_0(2)
    );
\cnt_2us[3]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"6AAA"
    )
        port map (
      I0 => cnt_2us(3),
      I1 => cnt_2us(1),
      I2 => cnt_2us(0),
      I3 => cnt_2us(2),
      O => cnt_2us_0(3)
    );
\cnt_2us[4]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"6AAAAAAA"
    )
        port map (
      I0 => cnt_2us(4),
      I1 => cnt_2us(2),
      I2 => cnt_2us(0),
      I3 => cnt_2us(1),
      I4 => cnt_2us(3),
      O => cnt_2us_0(4)
    );
\cnt_2us[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F7FE0800F7FF0800"
    )
        port map (
      I0 => cnt_2us(4),
      I1 => cnt_2us(2),
      I2 => \cnt_2us[6]_i_2_n_0\,
      I3 => cnt_2us(3),
      I4 => cnt_2us(5),
      I5 => cnt_2us(6),
      O => cnt_2us_0(5)
    );
\cnt_2us[6]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F7FEFFFF08000000"
    )
        port map (
      I0 => cnt_2us(4),
      I1 => cnt_2us(2),
      I2 => \cnt_2us[6]_i_2_n_0\,
      I3 => cnt_2us(3),
      I4 => cnt_2us(5),
      I5 => cnt_2us(6),
      O => cnt_2us_0(6)
    );
\cnt_2us[6]_i_2\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"7"
    )
        port map (
      I0 => cnt_2us(0),
      I1 => cnt_2us(1),
      O => \cnt_2us[6]_i_2_n_0\
    );
\cnt_2us_reg[0]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => '1',
      CLR => \^s0_axi_aresetn_0\,
      D => cnt_2us_0(0),
      Q => cnt_2us(0)
    );
\cnt_2us_reg[1]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => '1',
      CLR => \^s0_axi_aresetn_0\,
      D => cnt_2us_0(1),
      Q => cnt_2us(1)
    );
\cnt_2us_reg[2]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => '1',
      CLR => \^s0_axi_aresetn_0\,
      D => cnt_2us_0(2),
      Q => cnt_2us(2)
    );
\cnt_2us_reg[3]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => '1',
      CLR => \^s0_axi_aresetn_0\,
      D => cnt_2us_0(3),
      Q => cnt_2us(3)
    );
\cnt_2us_reg[4]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => '1',
      CLR => \^s0_axi_aresetn_0\,
      D => cnt_2us_0(4),
      Q => cnt_2us(4)
    );
\cnt_2us_reg[5]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => '1',
      CLR => \^s0_axi_aresetn_0\,
      D => cnt_2us_0(5),
      Q => cnt_2us(5)
    );
\cnt_2us_reg[6]\: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => '1',
      CLR => \^s0_axi_aresetn_0\,
      D => cnt_2us_0(6),
      Q => cnt_2us(6)
    );
\freq_step[0]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"F200FFFF"
    )
        port map (
      I0 => Q(0),
      I1 => \freq_step[3]_i_3_n_0\,
      I2 => \freq_step[0]_i_2_n_0\,
      I3 => \freq_step[0]_i_3_n_0\,
      I4 => s0_axi_aresetn,
      O => \freq_step[0]_i_1_n_0\
    );
\freq_step[0]_i_2\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"00000001"
    )
        port map (
      I0 => Q(8),
      I1 => Q(0),
      I2 => Q(9),
      I3 => Q(5),
      I4 => \freq_step[0]_i_4_n_0\,
      O => \freq_step[0]_i_2_n_0\
    );
\freq_step[0]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F1F0F1F0F1F0F1F1"
    )
        port map (
      I0 => Q(8),
      I1 => Q(7),
      I2 => Q(9),
      I3 => Q(6),
      I4 => Q(5),
      I5 => Q(4),
      O => \freq_step[0]_i_3_n_0\
    );
\freq_step[0]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFF44F4"
    )
        port map (
      I0 => Q(7),
      I1 => Q(6),
      I2 => Q(3),
      I3 => Q(4),
      I4 => Q(1),
      I5 => Q(2),
      O => \freq_step[0]_i_4_n_0\
    );
\freq_step[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A8"
    )
        port map (
      I0 => s0_axi_aresetn,
      I1 => \freq_step[3]_i_3_n_0\,
      I2 => Q(1),
      O => p_1_in(1)
    );
\freq_step[2]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => Q(2),
      I1 => s0_axi_aresetn,
      I2 => \freq_step[3]_i_3_n_0\,
      O => p_1_in(2)
    );
\freq_step[3]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"B"
    )
        port map (
      I0 => Q(10),
      I1 => s0_axi_aresetn,
      O => \freq_step[3]_i_1_n_0\
    );
\freq_step[3]_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A8"
    )
        port map (
      I0 => s0_axi_aresetn,
      I1 => \freq_step[3]_i_3_n_0\,
      I2 => Q(3),
      O => p_1_in(3)
    );
\freq_step[3]_i_3\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFFFFE"
    )
        port map (
      I0 => Q(9),
      I1 => Q(6),
      I2 => Q(8),
      I3 => Q(7),
      I4 => \freq_step[3]_i_4_n_0\,
      O => \freq_step[3]_i_3_n_0\
    );
\freq_step[3]_i_4\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FEFEFEEE"
    )
        port map (
      I0 => Q(4),
      I1 => Q(5),
      I2 => Q(3),
      I3 => Q(1),
      I4 => Q(2),
      O => \freq_step[3]_i_4_n_0\
    );
\freq_step_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \freq_step[3]_i_1_n_0\,
      D => \freq_step[0]_i_1_n_0\,
      Q => \in\(0),
      R => '0'
    );
\freq_step_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \freq_step[3]_i_1_n_0\,
      D => p_1_in(1),
      Q => \in\(1),
      R => '0'
    );
\freq_step_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \freq_step[3]_i_1_n_0\,
      D => p_1_in(2),
      Q => \in\(2),
      R => '0'
    );
\freq_step_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \freq_step[3]_i_1_n_0\,
      D => p_1_in(3),
      Q => \in\(3),
      R => '0'
    );
\i__carry__0_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A8"
    )
        port map (
      I0 => cnt_2s_reg(7),
      I1 => \cnt_2ms[9]_i_4_n_0\,
      I2 => \i__carry_i_9_n_0\,
      O => \i__carry__0_i_1_n_0\
    );
\i__carry__0_i_1__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => cnt_2ms_reg(8),
      I1 => cnt_2s_reg(8),
      I2 => cnt_2s_reg(9),
      I3 => cnt_2ms_reg(9),
      O => \i__carry__0_i_1__0_n_0\
    );
\i__carry__0_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A8"
    )
        port map (
      I0 => cnt_2s_reg(6),
      I1 => \cnt_2ms[9]_i_4_n_0\,
      I2 => \i__carry_i_9_n_0\,
      O => \i__carry__0_i_2_n_0\
    );
\i__carry__0_i_2__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => cnt_2ms_reg(8),
      I1 => cnt_2s_reg(8),
      I2 => cnt_2s_reg(9),
      I3 => cnt_2ms_reg(9),
      O => \i__carry__0_i_2__0_n_0\
    );
\i__carry__0_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A8"
    )
        port map (
      I0 => cnt_2s_reg(5),
      I1 => \cnt_2ms[9]_i_4_n_0\,
      I2 => \i__carry_i_9_n_0\,
      O => \i__carry__0_i_3_n_0\
    );
\i__carry__0_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A8"
    )
        port map (
      I0 => cnt_2s_reg(4),
      I1 => \cnt_2ms[9]_i_4_n_0\,
      I2 => \i__carry_i_9_n_0\,
      O => \i__carry__0_i_4_n_0\
    );
\i__carry__1_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"8A"
    )
        port map (
      I0 => cnt_2s_reg(9),
      I1 => \i__carry_i_9_n_0\,
      I2 => \cnt_2s[9]_i_1_n_0\,
      O => \i__carry__1_i_1_n_0\
    );
\i__carry__1_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A8"
    )
        port map (
      I0 => cnt_2s_reg(8),
      I1 => \cnt_2ms[9]_i_4_n_0\,
      I2 => \i__carry_i_9_n_0\,
      O => \i__carry__1_i_2_n_0\
    );
\i__carry_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A8"
    )
        port map (
      I0 => \in\(3),
      I1 => \cnt_2ms[9]_i_4_n_0\,
      I2 => \i__carry_i_9_n_0\,
      O => \i__carry_i_1_n_0\
    );
\i__carry_i_10\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"0000007F"
    )
        port map (
      I0 => cnt_2s_reg(2),
      I1 => cnt_2s_reg(0),
      I2 => cnt_2s_reg(1),
      I3 => cnt_2s_reg(3),
      I4 => cnt_2s_reg(4),
      O => \i__carry_i_10_n_0\
    );
\i__carry_i_1__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => cnt_2ms_reg(6),
      I1 => cnt_2s_reg(6),
      I2 => cnt_2s_reg(7),
      I3 => cnt_2ms_reg(7),
      O => \i__carry_i_1__0_n_0\
    );
\i__carry_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A8"
    )
        port map (
      I0 => \in\(2),
      I1 => \cnt_2ms[9]_i_4_n_0\,
      I2 => \i__carry_i_9_n_0\,
      O => \i__carry_i_2_n_0\
    );
\i__carry_i_2__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => cnt_2ms_reg(4),
      I1 => cnt_2s_reg(4),
      I2 => cnt_2s_reg(5),
      I3 => cnt_2ms_reg(5),
      O => \i__carry_i_2__0_n_0\
    );
\i__carry_i_3\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A8"
    )
        port map (
      I0 => \in\(1),
      I1 => \cnt_2ms[9]_i_4_n_0\,
      I2 => \i__carry_i_9_n_0\,
      O => \i__carry_i_3_n_0\
    );
\i__carry_i_3__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => cnt_2ms_reg(2),
      I1 => cnt_2s_reg(2),
      I2 => cnt_2s_reg(3),
      I3 => cnt_2ms_reg(3),
      O => \i__carry_i_3__0_n_0\
    );
\i__carry_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"A8"
    )
        port map (
      I0 => \in\(0),
      I1 => \cnt_2ms[9]_i_4_n_0\,
      I2 => \i__carry_i_9_n_0\,
      O => \i__carry_i_4_n_0\
    );
\i__carry_i_4__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => cnt_2ms_reg(0),
      I1 => cnt_2s_reg(0),
      I2 => cnt_2s_reg(1),
      I3 => cnt_2ms_reg(1),
      O => \i__carry_i_4__0_n_0\
    );
\i__carry_i_5\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => cnt_2ms_reg(6),
      I1 => cnt_2s_reg(6),
      I2 => cnt_2s_reg(7),
      I3 => cnt_2ms_reg(7),
      O => \i__carry_i_5_n_0\
    );
\i__carry_i_5__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"54A8"
    )
        port map (
      I0 => \in\(3),
      I1 => \i__carry_i_9_n_0\,
      I2 => \cnt_2ms[9]_i_4_n_0\,
      I3 => cnt_2s_reg(3),
      O => \i__carry_i_5__0_n_0\
    );
\i__carry_i_6\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => cnt_2ms_reg(4),
      I1 => cnt_2s_reg(4),
      I2 => cnt_2s_reg(5),
      I3 => cnt_2ms_reg(5),
      O => \i__carry_i_6_n_0\
    );
\i__carry_i_6__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"54A8"
    )
        port map (
      I0 => \in\(2),
      I1 => \i__carry_i_9_n_0\,
      I2 => \cnt_2ms[9]_i_4_n_0\,
      I3 => cnt_2s_reg(2),
      O => \i__carry_i_6__0_n_0\
    );
\i__carry_i_7\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => cnt_2ms_reg(2),
      I1 => cnt_2s_reg(2),
      I2 => cnt_2s_reg(3),
      I3 => cnt_2ms_reg(3),
      O => \i__carry_i_7_n_0\
    );
\i__carry_i_7__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"54A8"
    )
        port map (
      I0 => \in\(1),
      I1 => \i__carry_i_9_n_0\,
      I2 => \cnt_2ms[9]_i_4_n_0\,
      I3 => cnt_2s_reg(1),
      O => \i__carry_i_7__0_n_0\
    );
\i__carry_i_8\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => cnt_2ms_reg(0),
      I1 => cnt_2s_reg(0),
      I2 => cnt_2s_reg(1),
      I3 => cnt_2ms_reg(1),
      O => \i__carry_i_8_n_0\
    );
\i__carry_i_8__0\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"54A8"
    )
        port map (
      I0 => \in\(0),
      I1 => \i__carry_i_9_n_0\,
      I2 => \cnt_2ms[9]_i_4_n_0\,
      I3 => cnt_2s_reg(0),
      O => \i__carry_i_8__0_n_0\
    );
\i__carry_i_9\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFF7FFFFFFF"
    )
        port map (
      I0 => cnt_2s_reg(8),
      I1 => cnt_2s_reg(5),
      I2 => cnt_2s_reg(6),
      I3 => cnt_2s_reg(7),
      I4 => cnt_2s_reg(9),
      I5 => \i__carry_i_10_n_0\,
      O => \i__carry_i_9_n_0\
    );
inc_dec_flag_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B4"
    )
        port map (
      I0 => \i__carry_i_9_n_0\,
      I1 => \cnt_2s[9]_i_1_n_0\,
      I2 => inc_dec_flag,
      O => inc_dec_flag_i_1_n_0
    );
inc_dec_flag_reg: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => '1',
      CLR => \^s0_axi_aresetn_0\,
      D => inc_dec_flag_i_1_n_0,
      Q => inc_dec_flag
    );
led_INST_0: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => led_t,
      I1 => led_0(0),
      O => led
    );
led_t2_carry: unisim.vcomponents.CARRY4
     port map (
      CI => '0',
      CO(3) => led_t2_carry_n_0,
      CO(2) => led_t2_carry_n_1,
      CO(1) => led_t2_carry_n_2,
      CO(0) => led_t2_carry_n_3,
      CYINIT => '1',
      DI(3) => led_t2_carry_i_1_n_0,
      DI(2) => led_t2_carry_i_2_n_0,
      DI(1) => led_t2_carry_i_3_n_0,
      DI(0) => led_t2_carry_i_4_n_0,
      O(3 downto 0) => NLW_led_t2_carry_O_UNCONNECTED(3 downto 0),
      S(3) => led_t2_carry_i_5_n_0,
      S(2) => led_t2_carry_i_6_n_0,
      S(1) => led_t2_carry_i_7_n_0,
      S(0) => led_t2_carry_i_8_n_0
    );
\led_t2_carry__0\: unisim.vcomponents.CARRY4
     port map (
      CI => led_t2_carry_n_0,
      CO(3 downto 1) => \NLW_led_t2_carry__0_CO_UNCONNECTED\(3 downto 1),
      CO(0) => led_t2,
      CYINIT => '0',
      DI(3 downto 1) => B"000",
      DI(0) => \led_t2_carry__0_i_1_n_0\,
      O(3 downto 0) => \NLW_led_t2_carry__0_O_UNCONNECTED\(3 downto 0),
      S(3 downto 1) => B"000",
      S(0) => \led_t2_carry__0_i_2_n_0\
    );
\led_t2_carry__0_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => cnt_2s_reg(8),
      I1 => cnt_2ms_reg(8),
      I2 => cnt_2ms_reg(9),
      I3 => cnt_2s_reg(9),
      O => \led_t2_carry__0_i_1_n_0\
    );
\led_t2_carry__0_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => cnt_2ms_reg(8),
      I1 => cnt_2s_reg(8),
      I2 => cnt_2s_reg(9),
      I3 => cnt_2ms_reg(9),
      O => \led_t2_carry__0_i_2_n_0\
    );
led_t2_carry_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => cnt_2s_reg(6),
      I1 => cnt_2ms_reg(6),
      I2 => cnt_2ms_reg(7),
      I3 => cnt_2s_reg(7),
      O => led_t2_carry_i_1_n_0
    );
led_t2_carry_i_2: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => cnt_2s_reg(4),
      I1 => cnt_2ms_reg(4),
      I2 => cnt_2ms_reg(5),
      I3 => cnt_2s_reg(5),
      O => led_t2_carry_i_2_n_0
    );
led_t2_carry_i_3: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => cnt_2s_reg(2),
      I1 => cnt_2ms_reg(2),
      I2 => cnt_2ms_reg(3),
      I3 => cnt_2s_reg(3),
      O => led_t2_carry_i_3_n_0
    );
led_t2_carry_i_4: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2F02"
    )
        port map (
      I0 => cnt_2s_reg(0),
      I1 => cnt_2ms_reg(0),
      I2 => cnt_2ms_reg(1),
      I3 => cnt_2s_reg(1),
      O => led_t2_carry_i_4_n_0
    );
led_t2_carry_i_5: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => cnt_2ms_reg(6),
      I1 => cnt_2s_reg(6),
      I2 => cnt_2s_reg(7),
      I3 => cnt_2ms_reg(7),
      O => led_t2_carry_i_5_n_0
    );
led_t2_carry_i_6: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => cnt_2ms_reg(4),
      I1 => cnt_2s_reg(4),
      I2 => cnt_2s_reg(5),
      I3 => cnt_2ms_reg(5),
      O => led_t2_carry_i_6_n_0
    );
led_t2_carry_i_7: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => cnt_2ms_reg(2),
      I1 => cnt_2s_reg(2),
      I2 => cnt_2s_reg(3),
      I3 => cnt_2ms_reg(3),
      O => led_t2_carry_i_7_n_0
    );
led_t2_carry_i_8: unisim.vcomponents.LUT4
    generic map(
      INIT => X"9009"
    )
        port map (
      I0 => cnt_2ms_reg(0),
      I1 => cnt_2s_reg(0),
      I2 => cnt_2s_reg(1),
      I3 => cnt_2ms_reg(1),
      O => led_t2_carry_i_8_n_0
    );
\led_t2_inferred__0/i__carry\: unisim.vcomponents.CARRY4
     port map (
      CI => '0',
      CO(3) => \led_t2_inferred__0/i__carry_n_0\,
      CO(2) => \led_t2_inferred__0/i__carry_n_1\,
      CO(1) => \led_t2_inferred__0/i__carry_n_2\,
      CO(0) => \led_t2_inferred__0/i__carry_n_3\,
      CYINIT => '1',
      DI(3) => \i__carry_i_1__0_n_0\,
      DI(2) => \i__carry_i_2__0_n_0\,
      DI(1) => \i__carry_i_3__0_n_0\,
      DI(0) => \i__carry_i_4__0_n_0\,
      O(3 downto 0) => \NLW_led_t2_inferred__0/i__carry_O_UNCONNECTED\(3 downto 0),
      S(3) => \i__carry_i_5_n_0\,
      S(2) => \i__carry_i_6_n_0\,
      S(1) => \i__carry_i_7_n_0\,
      S(0) => \i__carry_i_8_n_0\
    );
\led_t2_inferred__0/i__carry__0\: unisim.vcomponents.CARRY4
     port map (
      CI => \led_t2_inferred__0/i__carry_n_0\,
      CO(3 downto 1) => \NLW_led_t2_inferred__0/i__carry__0_CO_UNCONNECTED\(3 downto 1),
      CO(0) => led_t21_in,
      CYINIT => '0',
      DI(3 downto 1) => B"000",
      DI(0) => \i__carry__0_i_1__0_n_0\,
      O(3 downto 0) => \NLW_led_t2_inferred__0/i__carry__0_O_UNCONNECTED\(3 downto 0),
      S(3 downto 1) => B"000",
      S(0) => \i__carry__0_i_2__0_n_0\
    );
led_t_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => led_t21_in,
      I1 => inc_dec_flag,
      I2 => led_t2,
      O => led_t_i_1_n_0
    );
led_t_reg: unisim.vcomponents.FDCE
     port map (
      C => s0_axi_aclk,
      CE => '1',
      CLR => \^s0_axi_aresetn_0\,
      D => led_t_i_1_n_0,
      Q => led_t
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_breath_led_ip_v1_0_S0_AXI is
  port (
    S_AXI_AWREADY : out STD_LOGIC;
    S_AXI_WREADY : out STD_LOGIC;
    S_AXI_ARREADY : out STD_LOGIC;
    s0_axi_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    led : out STD_LOGIC;
    s0_axi_rvalid : out STD_LOGIC;
    s0_axi_bvalid : out STD_LOGIC;
    s0_axi_aresetn : in STD_LOGIC;
    s0_axi_aclk : in STD_LOGIC;
    s0_axi_awaddr : in STD_LOGIC_VECTOR ( 1 downto 0 );
    s0_axi_wvalid : in STD_LOGIC;
    s0_axi_awvalid : in STD_LOGIC;
    s0_axi_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s0_axi_araddr : in STD_LOGIC_VECTOR ( 1 downto 0 );
    s0_axi_arvalid : in STD_LOGIC;
    s0_axi_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s0_axi_bready : in STD_LOGIC;
    s0_axi_rready : in STD_LOGIC
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_breath_led_ip_v1_0_S0_AXI;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_breath_led_ip_v1_0_S0_AXI is
  signal \^s_axi_arready\ : STD_LOGIC;
  signal \^s_axi_awready\ : STD_LOGIC;
  signal \^s_axi_wready\ : STD_LOGIC;
  signal aw_en_i_1_n_0 : STD_LOGIC;
  signal aw_en_reg_n_0 : STD_LOGIC;
  signal axi_araddr : STD_LOGIC_VECTOR ( 3 downto 2 );
  signal \axi_araddr[2]_i_1_n_0\ : STD_LOGIC;
  signal \axi_araddr[3]_i_1_n_0\ : STD_LOGIC;
  signal axi_arready0 : STD_LOGIC;
  signal \axi_awaddr[2]_i_1_n_0\ : STD_LOGIC;
  signal \axi_awaddr[3]_i_1_n_0\ : STD_LOGIC;
  signal axi_awready0 : STD_LOGIC;
  signal axi_bvalid_i_1_n_0 : STD_LOGIC;
  signal axi_rvalid_i_1_n_0 : STD_LOGIC;
  signal axi_wready0 : STD_LOGIC;
  signal p_0_in : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal reg_data_out : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \^s0_axi_bvalid\ : STD_LOGIC;
  signal \^s0_axi_rvalid\ : STD_LOGIC;
  signal slv_reg0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal \slv_reg0[15]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg0[23]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg0[31]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg0[7]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[10]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[11]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[12]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[13]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[14]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[15]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[16]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[17]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[18]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[19]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[1]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[20]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[21]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[22]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[23]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[24]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[25]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[26]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[27]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[28]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[29]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[2]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[30]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[31]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[3]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[4]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[5]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[6]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[7]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[8]\ : STD_LOGIC;
  signal \slv_reg0_reg_n_0_[9]\ : STD_LOGIC;
  signal slv_reg1 : STD_LOGIC_VECTOR ( 31 to 31 );
  signal \slv_reg1[15]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg1[23]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg1[31]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg1[7]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[0]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[10]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[11]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[12]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[13]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[14]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[15]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[16]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[17]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[18]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[19]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[1]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[20]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[21]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[22]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[23]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[24]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[25]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[26]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[27]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[28]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[29]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[2]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[30]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[3]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[4]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[5]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[6]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[7]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[8]\ : STD_LOGIC;
  signal \slv_reg1_reg_n_0_[9]\ : STD_LOGIC;
  signal slv_reg2 : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \slv_reg2[15]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg2[23]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg2[31]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg2[7]_i_1_n_0\ : STD_LOGIC;
  signal slv_reg3 : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \slv_reg3[15]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg3[23]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg3[31]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg3[7]_i_1_n_0\ : STD_LOGIC;
  signal \slv_reg_rden__0\ : STD_LOGIC;
  signal \slv_reg_wren__0\ : STD_LOGIC;
  signal u_breath_led_n_0 : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \axi_araddr[3]_i_1\ : label is "soft_lutpair10";
  attribute SOFT_HLUTNM of axi_arready_i_1 : label is "soft_lutpair10";
  attribute SOFT_HLUTNM of axi_wready_i_1 : label is "soft_lutpair11";
  attribute SOFT_HLUTNM of \slv_reg1[31]_i_2\ : label is "soft_lutpair11";
begin
  S_AXI_ARREADY <= \^s_axi_arready\;
  S_AXI_AWREADY <= \^s_axi_awready\;
  S_AXI_WREADY <= \^s_axi_wready\;
  s0_axi_bvalid <= \^s0_axi_bvalid\;
  s0_axi_rvalid <= \^s0_axi_rvalid\;
aw_en_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F7FFC4CCC4CCC4CC"
    )
        port map (
      I0 => s0_axi_awvalid,
      I1 => aw_en_reg_n_0,
      I2 => \^s_axi_awready\,
      I3 => s0_axi_wvalid,
      I4 => s0_axi_bready,
      I5 => \^s0_axi_bvalid\,
      O => aw_en_i_1_n_0
    );
aw_en_reg: unisim.vcomponents.FDSE
     port map (
      C => s0_axi_aclk,
      CE => '1',
      D => aw_en_i_1_n_0,
      Q => aw_en_reg_n_0,
      S => u_breath_led_n_0
    );
\axi_araddr[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FB08"
    )
        port map (
      I0 => s0_axi_araddr(0),
      I1 => s0_axi_arvalid,
      I2 => \^s_axi_arready\,
      I3 => axi_araddr(2),
      O => \axi_araddr[2]_i_1_n_0\
    );
\axi_araddr[3]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FB08"
    )
        port map (
      I0 => s0_axi_araddr(1),
      I1 => s0_axi_arvalid,
      I2 => \^s_axi_arready\,
      I3 => axi_araddr(3),
      O => \axi_araddr[3]_i_1_n_0\
    );
\axi_araddr_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => '1',
      D => \axi_araddr[2]_i_1_n_0\,
      Q => axi_araddr(2),
      R => u_breath_led_n_0
    );
\axi_araddr_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => '1',
      D => \axi_araddr[3]_i_1_n_0\,
      Q => axi_araddr(3),
      R => u_breath_led_n_0
    );
axi_arready_i_1: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => s0_axi_arvalid,
      I1 => \^s_axi_arready\,
      O => axi_arready0
    );
axi_arready_reg: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => '1',
      D => axi_arready0,
      Q => \^s_axi_arready\,
      R => u_breath_led_n_0
    );
\axi_awaddr[2]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FBFFFFFF08000000"
    )
        port map (
      I0 => s0_axi_awaddr(0),
      I1 => s0_axi_wvalid,
      I2 => \^s_axi_awready\,
      I3 => aw_en_reg_n_0,
      I4 => s0_axi_awvalid,
      I5 => p_0_in(0),
      O => \axi_awaddr[2]_i_1_n_0\
    );
\axi_awaddr[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FBFFFFFF08000000"
    )
        port map (
      I0 => s0_axi_awaddr(1),
      I1 => s0_axi_wvalid,
      I2 => \^s_axi_awready\,
      I3 => aw_en_reg_n_0,
      I4 => s0_axi_awvalid,
      I5 => p_0_in(1),
      O => \axi_awaddr[3]_i_1_n_0\
    );
\axi_awaddr_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => '1',
      D => \axi_awaddr[2]_i_1_n_0\,
      Q => p_0_in(0),
      R => u_breath_led_n_0
    );
\axi_awaddr_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => '1',
      D => \axi_awaddr[3]_i_1_n_0\,
      Q => p_0_in(1),
      R => u_breath_led_n_0
    );
axi_awready_i_2: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2000"
    )
        port map (
      I0 => s0_axi_wvalid,
      I1 => \^s_axi_awready\,
      I2 => aw_en_reg_n_0,
      I3 => s0_axi_awvalid,
      O => axi_awready0
    );
axi_awready_reg: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => '1',
      D => axi_awready0,
      Q => \^s_axi_awready\,
      R => u_breath_led_n_0
    );
axi_bvalid_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000FFFF80008000"
    )
        port map (
      I0 => s0_axi_awvalid,
      I1 => s0_axi_wvalid,
      I2 => \^s_axi_awready\,
      I3 => \^s_axi_wready\,
      I4 => s0_axi_bready,
      I5 => \^s0_axi_bvalid\,
      O => axi_bvalid_i_1_n_0
    );
axi_bvalid_reg: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => '1',
      D => axi_bvalid_i_1_n_0,
      Q => \^s0_axi_bvalid\,
      R => u_breath_led_n_0
    );
\axi_rdata[0]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCCF0AA00CCF0AA"
    )
        port map (
      I0 => slv_reg0(0),
      I1 => \slv_reg1_reg_n_0_[0]\,
      I2 => slv_reg2(0),
      I3 => axi_araddr(3),
      I4 => axi_araddr(2),
      I5 => slv_reg3(0),
      O => reg_data_out(0)
    );
\axi_rdata[10]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCCAAF000CCAAF0"
    )
        port map (
      I0 => \slv_reg1_reg_n_0_[10]\,
      I1 => slv_reg2(10),
      I2 => \slv_reg0_reg_n_0_[10]\,
      I3 => axi_araddr(2),
      I4 => axi_araddr(3),
      I5 => slv_reg3(10),
      O => reg_data_out(10)
    );
\axi_rdata[11]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F0FFCCAAF000CCAA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[11]\,
      I1 => \slv_reg1_reg_n_0_[11]\,
      I2 => slv_reg3(11),
      I3 => axi_araddr(2),
      I4 => axi_araddr(3),
      I5 => slv_reg2(11),
      O => reg_data_out(11)
    );
\axi_rdata[12]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCCF0AA00CCF0AA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[12]\,
      I1 => \slv_reg1_reg_n_0_[12]\,
      I2 => slv_reg2(12),
      I3 => axi_araddr(3),
      I4 => axi_araddr(2),
      I5 => slv_reg3(12),
      O => reg_data_out(12)
    );
\axi_rdata[13]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCCF0AA00CCF0AA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[13]\,
      I1 => \slv_reg1_reg_n_0_[13]\,
      I2 => slv_reg2(13),
      I3 => axi_araddr(3),
      I4 => axi_araddr(2),
      I5 => slv_reg3(13),
      O => reg_data_out(13)
    );
\axi_rdata[14]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCCF0AA00CCF0AA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[14]\,
      I1 => \slv_reg1_reg_n_0_[14]\,
      I2 => slv_reg2(14),
      I3 => axi_araddr(3),
      I4 => axi_araddr(2),
      I5 => slv_reg3(14),
      O => reg_data_out(14)
    );
\axi_rdata[15]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F0FFCCAAF000CCAA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[15]\,
      I1 => \slv_reg1_reg_n_0_[15]\,
      I2 => slv_reg3(15),
      I3 => axi_araddr(2),
      I4 => axi_araddr(3),
      I5 => slv_reg2(15),
      O => reg_data_out(15)
    );
\axi_rdata[16]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F0FFCCAAF000CCAA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[16]\,
      I1 => \slv_reg1_reg_n_0_[16]\,
      I2 => slv_reg3(16),
      I3 => axi_araddr(2),
      I4 => axi_araddr(3),
      I5 => slv_reg2(16),
      O => reg_data_out(16)
    );
\axi_rdata[17]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F0FFCCAAF000CCAA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[17]\,
      I1 => \slv_reg1_reg_n_0_[17]\,
      I2 => slv_reg3(17),
      I3 => axi_araddr(2),
      I4 => axi_araddr(3),
      I5 => slv_reg2(17),
      O => reg_data_out(17)
    );
\axi_rdata[18]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCCAAF000CCAAF0"
    )
        port map (
      I0 => \slv_reg1_reg_n_0_[18]\,
      I1 => slv_reg2(18),
      I2 => \slv_reg0_reg_n_0_[18]\,
      I3 => axi_araddr(2),
      I4 => axi_araddr(3),
      I5 => slv_reg3(18),
      O => reg_data_out(18)
    );
\axi_rdata[19]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F0FFCCAAF000CCAA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[19]\,
      I1 => \slv_reg1_reg_n_0_[19]\,
      I2 => slv_reg3(19),
      I3 => axi_araddr(2),
      I4 => axi_araddr(3),
      I5 => slv_reg2(19),
      O => reg_data_out(19)
    );
\axi_rdata[1]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCCF0AA00CCF0AA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[1]\,
      I1 => \slv_reg1_reg_n_0_[1]\,
      I2 => slv_reg2(1),
      I3 => axi_araddr(3),
      I4 => axi_araddr(2),
      I5 => slv_reg3(1),
      O => reg_data_out(1)
    );
\axi_rdata[20]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCCF0AA00CCF0AA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[20]\,
      I1 => \slv_reg1_reg_n_0_[20]\,
      I2 => slv_reg2(20),
      I3 => axi_araddr(3),
      I4 => axi_araddr(2),
      I5 => slv_reg3(20),
      O => reg_data_out(20)
    );
\axi_rdata[21]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCCF0AA00CCF0AA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[21]\,
      I1 => \slv_reg1_reg_n_0_[21]\,
      I2 => slv_reg2(21),
      I3 => axi_araddr(3),
      I4 => axi_araddr(2),
      I5 => slv_reg3(21),
      O => reg_data_out(21)
    );
\axi_rdata[22]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCCF0AA00CCF0AA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[22]\,
      I1 => \slv_reg1_reg_n_0_[22]\,
      I2 => slv_reg2(22),
      I3 => axi_araddr(3),
      I4 => axi_araddr(2),
      I5 => slv_reg3(22),
      O => reg_data_out(22)
    );
\axi_rdata[23]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F0FFCCAAF000CCAA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[23]\,
      I1 => \slv_reg1_reg_n_0_[23]\,
      I2 => slv_reg3(23),
      I3 => axi_araddr(2),
      I4 => axi_araddr(3),
      I5 => slv_reg2(23),
      O => reg_data_out(23)
    );
\axi_rdata[24]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F0FFCCAAF000CCAA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[24]\,
      I1 => \slv_reg1_reg_n_0_[24]\,
      I2 => slv_reg3(24),
      I3 => axi_araddr(2),
      I4 => axi_araddr(3),
      I5 => slv_reg2(24),
      O => reg_data_out(24)
    );
\axi_rdata[25]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F0FFCCAAF000CCAA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[25]\,
      I1 => \slv_reg1_reg_n_0_[25]\,
      I2 => slv_reg3(25),
      I3 => axi_araddr(2),
      I4 => axi_araddr(3),
      I5 => slv_reg2(25),
      O => reg_data_out(25)
    );
\axi_rdata[26]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCCAAF000CCAAF0"
    )
        port map (
      I0 => \slv_reg1_reg_n_0_[26]\,
      I1 => slv_reg2(26),
      I2 => \slv_reg0_reg_n_0_[26]\,
      I3 => axi_araddr(2),
      I4 => axi_araddr(3),
      I5 => slv_reg3(26),
      O => reg_data_out(26)
    );
\axi_rdata[27]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F0FFCCAAF000CCAA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[27]\,
      I1 => \slv_reg1_reg_n_0_[27]\,
      I2 => slv_reg3(27),
      I3 => axi_araddr(2),
      I4 => axi_araddr(3),
      I5 => slv_reg2(27),
      O => reg_data_out(27)
    );
\axi_rdata[28]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCCF0AA00CCF0AA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[28]\,
      I1 => \slv_reg1_reg_n_0_[28]\,
      I2 => slv_reg2(28),
      I3 => axi_araddr(3),
      I4 => axi_araddr(2),
      I5 => slv_reg3(28),
      O => reg_data_out(28)
    );
\axi_rdata[29]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCCF0AA00CCF0AA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[29]\,
      I1 => \slv_reg1_reg_n_0_[29]\,
      I2 => slv_reg2(29),
      I3 => axi_araddr(3),
      I4 => axi_araddr(2),
      I5 => slv_reg3(29),
      O => reg_data_out(29)
    );
\axi_rdata[2]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F0FFCCAAF000CCAA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[2]\,
      I1 => \slv_reg1_reg_n_0_[2]\,
      I2 => slv_reg3(2),
      I3 => axi_araddr(2),
      I4 => axi_araddr(3),
      I5 => slv_reg2(2),
      O => reg_data_out(2)
    );
\axi_rdata[30]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCCF0AA00CCF0AA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[30]\,
      I1 => \slv_reg1_reg_n_0_[30]\,
      I2 => slv_reg2(30),
      I3 => axi_araddr(3),
      I4 => axi_araddr(2),
      I5 => slv_reg3(30),
      O => reg_data_out(30)
    );
\axi_rdata[31]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCCF0AA00CCF0AA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[31]\,
      I1 => slv_reg1(31),
      I2 => slv_reg2(31),
      I3 => axi_araddr(3),
      I4 => axi_araddr(2),
      I5 => slv_reg3(31),
      O => reg_data_out(31)
    );
\axi_rdata[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F0FFCCAAF000CCAA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[3]\,
      I1 => \slv_reg1_reg_n_0_[3]\,
      I2 => slv_reg3(3),
      I3 => axi_araddr(2),
      I4 => axi_araddr(3),
      I5 => slv_reg2(3),
      O => reg_data_out(3)
    );
\axi_rdata[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCCF0AA00CCF0AA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[4]\,
      I1 => \slv_reg1_reg_n_0_[4]\,
      I2 => slv_reg2(4),
      I3 => axi_araddr(3),
      I4 => axi_araddr(2),
      I5 => slv_reg3(4),
      O => reg_data_out(4)
    );
\axi_rdata[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFCCF0AA00CCF0AA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[5]\,
      I1 => \slv_reg1_reg_n_0_[5]\,
      I2 => slv_reg2(5),
      I3 => axi_araddr(3),
      I4 => axi_araddr(2),
      I5 => slv_reg3(5),
      O => reg_data_out(5)
    );
\axi_rdata[6]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F0FFCCAAF000CCAA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[6]\,
      I1 => \slv_reg1_reg_n_0_[6]\,
      I2 => slv_reg3(6),
      I3 => axi_araddr(2),
      I4 => axi_araddr(3),
      I5 => slv_reg2(6),
      O => reg_data_out(6)
    );
\axi_rdata[7]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F0FFCCAAF000CCAA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[7]\,
      I1 => \slv_reg1_reg_n_0_[7]\,
      I2 => slv_reg3(7),
      I3 => axi_araddr(2),
      I4 => axi_araddr(3),
      I5 => slv_reg2(7),
      O => reg_data_out(7)
    );
\axi_rdata[8]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"CCFFAAF0CC00AAF0"
    )
        port map (
      I0 => \slv_reg1_reg_n_0_[8]\,
      I1 => slv_reg3(8),
      I2 => \slv_reg0_reg_n_0_[8]\,
      I3 => axi_araddr(2),
      I4 => axi_araddr(3),
      I5 => slv_reg2(8),
      O => reg_data_out(8)
    );
\axi_rdata[9]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"F0FFCCAAF000CCAA"
    )
        port map (
      I0 => \slv_reg0_reg_n_0_[9]\,
      I1 => \slv_reg1_reg_n_0_[9]\,
      I2 => slv_reg3(9),
      I3 => axi_araddr(2),
      I4 => axi_araddr(3),
      I5 => slv_reg2(9),
      O => reg_data_out(9)
    );
\axi_rdata_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(0),
      Q => s0_axi_rdata(0),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(10),
      Q => s0_axi_rdata(10),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(11),
      Q => s0_axi_rdata(11),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(12),
      Q => s0_axi_rdata(12),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(13),
      Q => s0_axi_rdata(13),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(14),
      Q => s0_axi_rdata(14),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(15),
      Q => s0_axi_rdata(15),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(16),
      Q => s0_axi_rdata(16),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(17),
      Q => s0_axi_rdata(17),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(18),
      Q => s0_axi_rdata(18),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(19),
      Q => s0_axi_rdata(19),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(1),
      Q => s0_axi_rdata(1),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(20),
      Q => s0_axi_rdata(20),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(21),
      Q => s0_axi_rdata(21),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(22),
      Q => s0_axi_rdata(22),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(23),
      Q => s0_axi_rdata(23),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(24),
      Q => s0_axi_rdata(24),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(25),
      Q => s0_axi_rdata(25),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(26),
      Q => s0_axi_rdata(26),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(27),
      Q => s0_axi_rdata(27),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(28),
      Q => s0_axi_rdata(28),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(29),
      Q => s0_axi_rdata(29),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(2),
      Q => s0_axi_rdata(2),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(30),
      Q => s0_axi_rdata(30),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(31),
      Q => s0_axi_rdata(31),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(3),
      Q => s0_axi_rdata(3),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(4),
      Q => s0_axi_rdata(4),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(5),
      Q => s0_axi_rdata(5),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(6),
      Q => s0_axi_rdata(6),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(7),
      Q => s0_axi_rdata(7),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(8),
      Q => s0_axi_rdata(8),
      R => u_breath_led_n_0
    );
\axi_rdata_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg_rden__0\,
      D => reg_data_out(9),
      Q => s0_axi_rdata(9),
      R => u_breath_led_n_0
    );
axi_rvalid_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"08F8"
    )
        port map (
      I0 => \^s_axi_arready\,
      I1 => s0_axi_arvalid,
      I2 => \^s0_axi_rvalid\,
      I3 => s0_axi_rready,
      O => axi_rvalid_i_1_n_0
    );
axi_rvalid_reg: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => '1',
      D => axi_rvalid_i_1_n_0,
      Q => \^s0_axi_rvalid\,
      R => u_breath_led_n_0
    );
axi_wready_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0800"
    )
        port map (
      I0 => s0_axi_awvalid,
      I1 => s0_axi_wvalid,
      I2 => \^s_axi_wready\,
      I3 => aw_en_reg_n_0,
      O => axi_wready0
    );
axi_wready_reg: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => '1',
      D => axi_wready0,
      Q => \^s_axi_wready\,
      R => u_breath_led_n_0
    );
\slv_reg0[15]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0200"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(1),
      I2 => p_0_in(0),
      I3 => s0_axi_wstrb(1),
      O => \slv_reg0[15]_i_1_n_0\
    );
\slv_reg0[23]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0200"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(1),
      I2 => p_0_in(0),
      I3 => s0_axi_wstrb(2),
      O => \slv_reg0[23]_i_1_n_0\
    );
\slv_reg0[31]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0200"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(1),
      I2 => p_0_in(0),
      I3 => s0_axi_wstrb(3),
      O => \slv_reg0[31]_i_1_n_0\
    );
\slv_reg0[7]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0200"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(1),
      I2 => p_0_in(0),
      I3 => s0_axi_wstrb(0),
      O => \slv_reg0[7]_i_1_n_0\
    );
\slv_reg0_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[7]_i_1_n_0\,
      D => s0_axi_wdata(0),
      Q => slv_reg0(0),
      R => u_breath_led_n_0
    );
\slv_reg0_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[15]_i_1_n_0\,
      D => s0_axi_wdata(10),
      Q => \slv_reg0_reg_n_0_[10]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[15]_i_1_n_0\,
      D => s0_axi_wdata(11),
      Q => \slv_reg0_reg_n_0_[11]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[15]_i_1_n_0\,
      D => s0_axi_wdata(12),
      Q => \slv_reg0_reg_n_0_[12]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[15]_i_1_n_0\,
      D => s0_axi_wdata(13),
      Q => \slv_reg0_reg_n_0_[13]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[15]_i_1_n_0\,
      D => s0_axi_wdata(14),
      Q => \slv_reg0_reg_n_0_[14]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[15]_i_1_n_0\,
      D => s0_axi_wdata(15),
      Q => \slv_reg0_reg_n_0_[15]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[23]_i_1_n_0\,
      D => s0_axi_wdata(16),
      Q => \slv_reg0_reg_n_0_[16]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[23]_i_1_n_0\,
      D => s0_axi_wdata(17),
      Q => \slv_reg0_reg_n_0_[17]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[23]_i_1_n_0\,
      D => s0_axi_wdata(18),
      Q => \slv_reg0_reg_n_0_[18]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[23]_i_1_n_0\,
      D => s0_axi_wdata(19),
      Q => \slv_reg0_reg_n_0_[19]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[7]_i_1_n_0\,
      D => s0_axi_wdata(1),
      Q => \slv_reg0_reg_n_0_[1]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[23]_i_1_n_0\,
      D => s0_axi_wdata(20),
      Q => \slv_reg0_reg_n_0_[20]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[23]_i_1_n_0\,
      D => s0_axi_wdata(21),
      Q => \slv_reg0_reg_n_0_[21]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[23]_i_1_n_0\,
      D => s0_axi_wdata(22),
      Q => \slv_reg0_reg_n_0_[22]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[23]_i_1_n_0\,
      D => s0_axi_wdata(23),
      Q => \slv_reg0_reg_n_0_[23]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[31]_i_1_n_0\,
      D => s0_axi_wdata(24),
      Q => \slv_reg0_reg_n_0_[24]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[31]_i_1_n_0\,
      D => s0_axi_wdata(25),
      Q => \slv_reg0_reg_n_0_[25]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[31]_i_1_n_0\,
      D => s0_axi_wdata(26),
      Q => \slv_reg0_reg_n_0_[26]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[31]_i_1_n_0\,
      D => s0_axi_wdata(27),
      Q => \slv_reg0_reg_n_0_[27]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[31]_i_1_n_0\,
      D => s0_axi_wdata(28),
      Q => \slv_reg0_reg_n_0_[28]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[31]_i_1_n_0\,
      D => s0_axi_wdata(29),
      Q => \slv_reg0_reg_n_0_[29]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[7]_i_1_n_0\,
      D => s0_axi_wdata(2),
      Q => \slv_reg0_reg_n_0_[2]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[31]_i_1_n_0\,
      D => s0_axi_wdata(30),
      Q => \slv_reg0_reg_n_0_[30]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[31]_i_1_n_0\,
      D => s0_axi_wdata(31),
      Q => \slv_reg0_reg_n_0_[31]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[7]_i_1_n_0\,
      D => s0_axi_wdata(3),
      Q => \slv_reg0_reg_n_0_[3]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[7]_i_1_n_0\,
      D => s0_axi_wdata(4),
      Q => \slv_reg0_reg_n_0_[4]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[7]_i_1_n_0\,
      D => s0_axi_wdata(5),
      Q => \slv_reg0_reg_n_0_[5]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[7]_i_1_n_0\,
      D => s0_axi_wdata(6),
      Q => \slv_reg0_reg_n_0_[6]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[7]_i_1_n_0\,
      D => s0_axi_wdata(7),
      Q => \slv_reg0_reg_n_0_[7]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[15]_i_1_n_0\,
      D => s0_axi_wdata(8),
      Q => \slv_reg0_reg_n_0_[8]\,
      R => u_breath_led_n_0
    );
\slv_reg0_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg0[15]_i_1_n_0\,
      D => s0_axi_wdata(9),
      Q => \slv_reg0_reg_n_0_[9]\,
      R => u_breath_led_n_0
    );
\slv_reg1[15]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(1),
      I2 => s0_axi_wstrb(1),
      I3 => p_0_in(0),
      O => \slv_reg1[15]_i_1_n_0\
    );
\slv_reg1[23]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(1),
      I2 => s0_axi_wstrb(2),
      I3 => p_0_in(0),
      O => \slv_reg1[23]_i_1_n_0\
    );
\slv_reg1[31]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(1),
      I2 => s0_axi_wstrb(3),
      I3 => p_0_in(0),
      O => \slv_reg1[31]_i_1_n_0\
    );
\slv_reg1[31]_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8000"
    )
        port map (
      I0 => \^s_axi_wready\,
      I1 => \^s_axi_awready\,
      I2 => s0_axi_awvalid,
      I3 => s0_axi_wvalid,
      O => \slv_reg_wren__0\
    );
\slv_reg1[7]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"2000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(1),
      I2 => s0_axi_wstrb(0),
      I3 => p_0_in(0),
      O => \slv_reg1[7]_i_1_n_0\
    );
\slv_reg1_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[7]_i_1_n_0\,
      D => s0_axi_wdata(0),
      Q => \slv_reg1_reg_n_0_[0]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[15]_i_1_n_0\,
      D => s0_axi_wdata(10),
      Q => \slv_reg1_reg_n_0_[10]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[15]_i_1_n_0\,
      D => s0_axi_wdata(11),
      Q => \slv_reg1_reg_n_0_[11]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[15]_i_1_n_0\,
      D => s0_axi_wdata(12),
      Q => \slv_reg1_reg_n_0_[12]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[15]_i_1_n_0\,
      D => s0_axi_wdata(13),
      Q => \slv_reg1_reg_n_0_[13]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[15]_i_1_n_0\,
      D => s0_axi_wdata(14),
      Q => \slv_reg1_reg_n_0_[14]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[15]_i_1_n_0\,
      D => s0_axi_wdata(15),
      Q => \slv_reg1_reg_n_0_[15]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[23]_i_1_n_0\,
      D => s0_axi_wdata(16),
      Q => \slv_reg1_reg_n_0_[16]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[23]_i_1_n_0\,
      D => s0_axi_wdata(17),
      Q => \slv_reg1_reg_n_0_[17]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[23]_i_1_n_0\,
      D => s0_axi_wdata(18),
      Q => \slv_reg1_reg_n_0_[18]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[23]_i_1_n_0\,
      D => s0_axi_wdata(19),
      Q => \slv_reg1_reg_n_0_[19]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[7]_i_1_n_0\,
      D => s0_axi_wdata(1),
      Q => \slv_reg1_reg_n_0_[1]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[23]_i_1_n_0\,
      D => s0_axi_wdata(20),
      Q => \slv_reg1_reg_n_0_[20]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[23]_i_1_n_0\,
      D => s0_axi_wdata(21),
      Q => \slv_reg1_reg_n_0_[21]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[23]_i_1_n_0\,
      D => s0_axi_wdata(22),
      Q => \slv_reg1_reg_n_0_[22]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[23]_i_1_n_0\,
      D => s0_axi_wdata(23),
      Q => \slv_reg1_reg_n_0_[23]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[31]_i_1_n_0\,
      D => s0_axi_wdata(24),
      Q => \slv_reg1_reg_n_0_[24]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[31]_i_1_n_0\,
      D => s0_axi_wdata(25),
      Q => \slv_reg1_reg_n_0_[25]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[31]_i_1_n_0\,
      D => s0_axi_wdata(26),
      Q => \slv_reg1_reg_n_0_[26]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[31]_i_1_n_0\,
      D => s0_axi_wdata(27),
      Q => \slv_reg1_reg_n_0_[27]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[31]_i_1_n_0\,
      D => s0_axi_wdata(28),
      Q => \slv_reg1_reg_n_0_[28]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[31]_i_1_n_0\,
      D => s0_axi_wdata(29),
      Q => \slv_reg1_reg_n_0_[29]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[7]_i_1_n_0\,
      D => s0_axi_wdata(2),
      Q => \slv_reg1_reg_n_0_[2]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[31]_i_1_n_0\,
      D => s0_axi_wdata(30),
      Q => \slv_reg1_reg_n_0_[30]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[31]_i_1_n_0\,
      D => s0_axi_wdata(31),
      Q => slv_reg1(31),
      R => u_breath_led_n_0
    );
\slv_reg1_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[7]_i_1_n_0\,
      D => s0_axi_wdata(3),
      Q => \slv_reg1_reg_n_0_[3]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[7]_i_1_n_0\,
      D => s0_axi_wdata(4),
      Q => \slv_reg1_reg_n_0_[4]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[7]_i_1_n_0\,
      D => s0_axi_wdata(5),
      Q => \slv_reg1_reg_n_0_[5]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[7]_i_1_n_0\,
      D => s0_axi_wdata(6),
      Q => \slv_reg1_reg_n_0_[6]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[7]_i_1_n_0\,
      D => s0_axi_wdata(7),
      Q => \slv_reg1_reg_n_0_[7]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[15]_i_1_n_0\,
      D => s0_axi_wdata(8),
      Q => \slv_reg1_reg_n_0_[8]\,
      R => u_breath_led_n_0
    );
\slv_reg1_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg1[15]_i_1_n_0\,
      D => s0_axi_wdata(9),
      Q => \slv_reg1_reg_n_0_[9]\,
      R => u_breath_led_n_0
    );
\slv_reg2[15]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0080"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(1),
      I2 => s0_axi_wstrb(1),
      I3 => p_0_in(0),
      O => \slv_reg2[15]_i_1_n_0\
    );
\slv_reg2[23]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0080"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(1),
      I2 => s0_axi_wstrb(2),
      I3 => p_0_in(0),
      O => \slv_reg2[23]_i_1_n_0\
    );
\slv_reg2[31]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0080"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(1),
      I2 => s0_axi_wstrb(3),
      I3 => p_0_in(0),
      O => \slv_reg2[31]_i_1_n_0\
    );
\slv_reg2[7]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"0080"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => p_0_in(1),
      I2 => s0_axi_wstrb(0),
      I3 => p_0_in(0),
      O => \slv_reg2[7]_i_1_n_0\
    );
\slv_reg2_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[7]_i_1_n_0\,
      D => s0_axi_wdata(0),
      Q => slv_reg2(0),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[15]_i_1_n_0\,
      D => s0_axi_wdata(10),
      Q => slv_reg2(10),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[15]_i_1_n_0\,
      D => s0_axi_wdata(11),
      Q => slv_reg2(11),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[15]_i_1_n_0\,
      D => s0_axi_wdata(12),
      Q => slv_reg2(12),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[15]_i_1_n_0\,
      D => s0_axi_wdata(13),
      Q => slv_reg2(13),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[15]_i_1_n_0\,
      D => s0_axi_wdata(14),
      Q => slv_reg2(14),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[15]_i_1_n_0\,
      D => s0_axi_wdata(15),
      Q => slv_reg2(15),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[23]_i_1_n_0\,
      D => s0_axi_wdata(16),
      Q => slv_reg2(16),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[23]_i_1_n_0\,
      D => s0_axi_wdata(17),
      Q => slv_reg2(17),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[23]_i_1_n_0\,
      D => s0_axi_wdata(18),
      Q => slv_reg2(18),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[23]_i_1_n_0\,
      D => s0_axi_wdata(19),
      Q => slv_reg2(19),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[7]_i_1_n_0\,
      D => s0_axi_wdata(1),
      Q => slv_reg2(1),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[23]_i_1_n_0\,
      D => s0_axi_wdata(20),
      Q => slv_reg2(20),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[23]_i_1_n_0\,
      D => s0_axi_wdata(21),
      Q => slv_reg2(21),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[23]_i_1_n_0\,
      D => s0_axi_wdata(22),
      Q => slv_reg2(22),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[23]_i_1_n_0\,
      D => s0_axi_wdata(23),
      Q => slv_reg2(23),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[31]_i_1_n_0\,
      D => s0_axi_wdata(24),
      Q => slv_reg2(24),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[31]_i_1_n_0\,
      D => s0_axi_wdata(25),
      Q => slv_reg2(25),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[31]_i_1_n_0\,
      D => s0_axi_wdata(26),
      Q => slv_reg2(26),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[31]_i_1_n_0\,
      D => s0_axi_wdata(27),
      Q => slv_reg2(27),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[31]_i_1_n_0\,
      D => s0_axi_wdata(28),
      Q => slv_reg2(28),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[31]_i_1_n_0\,
      D => s0_axi_wdata(29),
      Q => slv_reg2(29),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[7]_i_1_n_0\,
      D => s0_axi_wdata(2),
      Q => slv_reg2(2),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[31]_i_1_n_0\,
      D => s0_axi_wdata(30),
      Q => slv_reg2(30),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[31]_i_1_n_0\,
      D => s0_axi_wdata(31),
      Q => slv_reg2(31),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[7]_i_1_n_0\,
      D => s0_axi_wdata(3),
      Q => slv_reg2(3),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[7]_i_1_n_0\,
      D => s0_axi_wdata(4),
      Q => slv_reg2(4),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[7]_i_1_n_0\,
      D => s0_axi_wdata(5),
      Q => slv_reg2(5),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[7]_i_1_n_0\,
      D => s0_axi_wdata(6),
      Q => slv_reg2(6),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[7]_i_1_n_0\,
      D => s0_axi_wdata(7),
      Q => slv_reg2(7),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[15]_i_1_n_0\,
      D => s0_axi_wdata(8),
      Q => slv_reg2(8),
      R => u_breath_led_n_0
    );
\slv_reg2_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg2[15]_i_1_n_0\,
      D => s0_axi_wdata(9),
      Q => slv_reg2(9),
      R => u_breath_led_n_0
    );
\slv_reg3[15]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => s0_axi_wstrb(1),
      I2 => p_0_in(0),
      I3 => p_0_in(1),
      O => \slv_reg3[15]_i_1_n_0\
    );
\slv_reg3[23]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => s0_axi_wstrb(2),
      I2 => p_0_in(0),
      I3 => p_0_in(1),
      O => \slv_reg3[23]_i_1_n_0\
    );
\slv_reg3[31]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => s0_axi_wstrb(3),
      I2 => p_0_in(0),
      I3 => p_0_in(1),
      O => \slv_reg3[31]_i_1_n_0\
    );
\slv_reg3[7]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"8000"
    )
        port map (
      I0 => \slv_reg_wren__0\,
      I1 => s0_axi_wstrb(0),
      I2 => p_0_in(0),
      I3 => p_0_in(1),
      O => \slv_reg3[7]_i_1_n_0\
    );
\slv_reg3_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[7]_i_1_n_0\,
      D => s0_axi_wdata(0),
      Q => slv_reg3(0),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[15]_i_1_n_0\,
      D => s0_axi_wdata(10),
      Q => slv_reg3(10),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[15]_i_1_n_0\,
      D => s0_axi_wdata(11),
      Q => slv_reg3(11),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[15]_i_1_n_0\,
      D => s0_axi_wdata(12),
      Q => slv_reg3(12),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[15]_i_1_n_0\,
      D => s0_axi_wdata(13),
      Q => slv_reg3(13),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[15]_i_1_n_0\,
      D => s0_axi_wdata(14),
      Q => slv_reg3(14),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[15]_i_1_n_0\,
      D => s0_axi_wdata(15),
      Q => slv_reg3(15),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[23]_i_1_n_0\,
      D => s0_axi_wdata(16),
      Q => slv_reg3(16),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[23]_i_1_n_0\,
      D => s0_axi_wdata(17),
      Q => slv_reg3(17),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[23]_i_1_n_0\,
      D => s0_axi_wdata(18),
      Q => slv_reg3(18),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[23]_i_1_n_0\,
      D => s0_axi_wdata(19),
      Q => slv_reg3(19),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[7]_i_1_n_0\,
      D => s0_axi_wdata(1),
      Q => slv_reg3(1),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[23]_i_1_n_0\,
      D => s0_axi_wdata(20),
      Q => slv_reg3(20),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[23]_i_1_n_0\,
      D => s0_axi_wdata(21),
      Q => slv_reg3(21),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[23]_i_1_n_0\,
      D => s0_axi_wdata(22),
      Q => slv_reg3(22),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[23]_i_1_n_0\,
      D => s0_axi_wdata(23),
      Q => slv_reg3(23),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[31]_i_1_n_0\,
      D => s0_axi_wdata(24),
      Q => slv_reg3(24),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[31]_i_1_n_0\,
      D => s0_axi_wdata(25),
      Q => slv_reg3(25),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[31]_i_1_n_0\,
      D => s0_axi_wdata(26),
      Q => slv_reg3(26),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[31]_i_1_n_0\,
      D => s0_axi_wdata(27),
      Q => slv_reg3(27),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[31]_i_1_n_0\,
      D => s0_axi_wdata(28),
      Q => slv_reg3(28),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[31]_i_1_n_0\,
      D => s0_axi_wdata(29),
      Q => slv_reg3(29),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[7]_i_1_n_0\,
      D => s0_axi_wdata(2),
      Q => slv_reg3(2),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[31]_i_1_n_0\,
      D => s0_axi_wdata(30),
      Q => slv_reg3(30),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[31]_i_1_n_0\,
      D => s0_axi_wdata(31),
      Q => slv_reg3(31),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[7]_i_1_n_0\,
      D => s0_axi_wdata(3),
      Q => slv_reg3(3),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[7]_i_1_n_0\,
      D => s0_axi_wdata(4),
      Q => slv_reg3(4),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[7]_i_1_n_0\,
      D => s0_axi_wdata(5),
      Q => slv_reg3(5),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[7]_i_1_n_0\,
      D => s0_axi_wdata(6),
      Q => slv_reg3(6),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[7]_i_1_n_0\,
      D => s0_axi_wdata(7),
      Q => slv_reg3(7),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[15]_i_1_n_0\,
      D => s0_axi_wdata(8),
      Q => slv_reg3(8),
      R => u_breath_led_n_0
    );
\slv_reg3_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => s0_axi_aclk,
      CE => \slv_reg3[15]_i_1_n_0\,
      D => s0_axi_wdata(9),
      Q => slv_reg3(9),
      R => u_breath_led_n_0
    );
slv_reg_rden: unisim.vcomponents.LUT3
    generic map(
      INIT => X"20"
    )
        port map (
      I0 => s0_axi_arvalid,
      I1 => \^s0_axi_rvalid\,
      I2 => \^s_axi_arready\,
      O => \slv_reg_rden__0\
    );
u_breath_led: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_breath_led
     port map (
      Q(10) => slv_reg1(31),
      Q(9) => \slv_reg1_reg_n_0_[9]\,
      Q(8) => \slv_reg1_reg_n_0_[8]\,
      Q(7) => \slv_reg1_reg_n_0_[7]\,
      Q(6) => \slv_reg1_reg_n_0_[6]\,
      Q(5) => \slv_reg1_reg_n_0_[5]\,
      Q(4) => \slv_reg1_reg_n_0_[4]\,
      Q(3) => \slv_reg1_reg_n_0_[3]\,
      Q(2) => \slv_reg1_reg_n_0_[2]\,
      Q(1) => \slv_reg1_reg_n_0_[1]\,
      Q(0) => \slv_reg1_reg_n_0_[0]\,
      led => led,
      led_0(0) => slv_reg0(0),
      s0_axi_aclk => s0_axi_aclk,
      s0_axi_aresetn => s0_axi_aresetn,
      s0_axi_aresetn_0 => u_breath_led_n_0
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_breath_led_ip_v1_0 is
  port (
    S_AXI_AWREADY : out STD_LOGIC;
    S_AXI_WREADY : out STD_LOGIC;
    S_AXI_ARREADY : out STD_LOGIC;
    s0_axi_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    led : out STD_LOGIC;
    s0_axi_rvalid : out STD_LOGIC;
    s0_axi_bvalid : out STD_LOGIC;
    s0_axi_aresetn : in STD_LOGIC;
    s0_axi_aclk : in STD_LOGIC;
    s0_axi_awaddr : in STD_LOGIC_VECTOR ( 1 downto 0 );
    s0_axi_wvalid : in STD_LOGIC;
    s0_axi_awvalid : in STD_LOGIC;
    s0_axi_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s0_axi_araddr : in STD_LOGIC_VECTOR ( 1 downto 0 );
    s0_axi_arvalid : in STD_LOGIC;
    s0_axi_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s0_axi_bready : in STD_LOGIC;
    s0_axi_rready : in STD_LOGIC
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_breath_led_ip_v1_0;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_breath_led_ip_v1_0 is
begin
breath_led_ip_v1_0_S0_AXI_inst: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_breath_led_ip_v1_0_S0_AXI
     port map (
      S_AXI_ARREADY => S_AXI_ARREADY,
      S_AXI_AWREADY => S_AXI_AWREADY,
      S_AXI_WREADY => S_AXI_WREADY,
      led => led,
      s0_axi_aclk => s0_axi_aclk,
      s0_axi_araddr(1 downto 0) => s0_axi_araddr(1 downto 0),
      s0_axi_aresetn => s0_axi_aresetn,
      s0_axi_arvalid => s0_axi_arvalid,
      s0_axi_awaddr(1 downto 0) => s0_axi_awaddr(1 downto 0),
      s0_axi_awvalid => s0_axi_awvalid,
      s0_axi_bready => s0_axi_bready,
      s0_axi_bvalid => s0_axi_bvalid,
      s0_axi_rdata(31 downto 0) => s0_axi_rdata(31 downto 0),
      s0_axi_rready => s0_axi_rready,
      s0_axi_rvalid => s0_axi_rvalid,
      s0_axi_wdata(31 downto 0) => s0_axi_wdata(31 downto 0),
      s0_axi_wstrb(3 downto 0) => s0_axi_wstrb(3 downto 0),
      s0_axi_wvalid => s0_axi_wvalid
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  port (
    led : out STD_LOGIC;
    s0_axi_aclk : in STD_LOGIC;
    s0_axi_aresetn : in STD_LOGIC;
    s0_axi_awaddr : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s0_axi_awprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s0_axi_awvalid : in STD_LOGIC;
    s0_axi_awready : out STD_LOGIC;
    s0_axi_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s0_axi_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s0_axi_wvalid : in STD_LOGIC;
    s0_axi_wready : out STD_LOGIC;
    s0_axi_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s0_axi_bvalid : out STD_LOGIC;
    s0_axi_bready : in STD_LOGIC;
    s0_axi_araddr : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s0_axi_arprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s0_axi_arvalid : in STD_LOGIC;
    s0_axi_arready : out STD_LOGIC;
    s0_axi_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s0_axi_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s0_axi_rvalid : out STD_LOGIC;
    s0_axi_rready : in STD_LOGIC
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "system_breath_led_ip_0_0,breath_led_ip_v1_0,{}";
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "yes";
  attribute X_CORE_INFO : string;
  attribute X_CORE_INFO of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "breath_led_ip_v1_0,Vivado 2020.2";
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  signal \<const0>\ : STD_LOGIC;
  attribute X_INTERFACE_INFO : string;
  attribute X_INTERFACE_INFO of s0_axi_aclk : signal is "xilinx.com:signal:clock:1.0 S0_AXI_CLK CLK";
  attribute X_INTERFACE_PARAMETER : string;
  attribute X_INTERFACE_PARAMETER of s0_axi_aclk : signal is "XIL_INTERFACENAME S0_AXI_CLK, ASSOCIATED_BUSIF S0_AXI, ASSOCIATED_RESET s0_axi_aresetn, FREQ_HZ 50000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, CLK_DOMAIN system_processing_system7_0_0_FCLK_CLK0, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of s0_axi_aresetn : signal is "xilinx.com:signal:reset:1.0 S0_AXI_RST RST";
  attribute X_INTERFACE_PARAMETER of s0_axi_aresetn : signal is "XIL_INTERFACENAME S0_AXI_RST, POLARITY ACTIVE_LOW, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of s0_axi_arready : signal is "xilinx.com:interface:aximm:1.0 S0_AXI ARREADY";
  attribute X_INTERFACE_INFO of s0_axi_arvalid : signal is "xilinx.com:interface:aximm:1.0 S0_AXI ARVALID";
  attribute X_INTERFACE_INFO of s0_axi_awready : signal is "xilinx.com:interface:aximm:1.0 S0_AXI AWREADY";
  attribute X_INTERFACE_INFO of s0_axi_awvalid : signal is "xilinx.com:interface:aximm:1.0 S0_AXI AWVALID";
  attribute X_INTERFACE_INFO of s0_axi_bready : signal is "xilinx.com:interface:aximm:1.0 S0_AXI BREADY";
  attribute X_INTERFACE_INFO of s0_axi_bvalid : signal is "xilinx.com:interface:aximm:1.0 S0_AXI BVALID";
  attribute X_INTERFACE_INFO of s0_axi_rready : signal is "xilinx.com:interface:aximm:1.0 S0_AXI RREADY";
  attribute X_INTERFACE_PARAMETER of s0_axi_rready : signal is "XIL_INTERFACENAME S0_AXI, WIZ_DATA_WIDTH 32, WIZ_NUM_REG 4, SUPPORTS_NARROW_BURST 0, DATA_WIDTH 32, PROTOCOL AXI4LITE, FREQ_HZ 50000000, ID_WIDTH 0, ADDR_WIDTH 4, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 1, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, NUM_READ_OUTSTANDING 8, NUM_WRITE_OUTSTANDING 8, MAX_BURST_LENGTH 1, PHASE 0.000, CLK_DOMAIN system_processing_system7_0_0_FCLK_CLK0, NUM_READ_THREADS 4, NUM_WRITE_THREADS 4, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of s0_axi_rvalid : signal is "xilinx.com:interface:aximm:1.0 S0_AXI RVALID";
  attribute X_INTERFACE_INFO of s0_axi_wready : signal is "xilinx.com:interface:aximm:1.0 S0_AXI WREADY";
  attribute X_INTERFACE_INFO of s0_axi_wvalid : signal is "xilinx.com:interface:aximm:1.0 S0_AXI WVALID";
  attribute X_INTERFACE_INFO of s0_axi_araddr : signal is "xilinx.com:interface:aximm:1.0 S0_AXI ARADDR";
  attribute X_INTERFACE_INFO of s0_axi_arprot : signal is "xilinx.com:interface:aximm:1.0 S0_AXI ARPROT";
  attribute X_INTERFACE_INFO of s0_axi_awaddr : signal is "xilinx.com:interface:aximm:1.0 S0_AXI AWADDR";
  attribute X_INTERFACE_INFO of s0_axi_awprot : signal is "xilinx.com:interface:aximm:1.0 S0_AXI AWPROT";
  attribute X_INTERFACE_INFO of s0_axi_bresp : signal is "xilinx.com:interface:aximm:1.0 S0_AXI BRESP";
  attribute X_INTERFACE_INFO of s0_axi_rdata : signal is "xilinx.com:interface:aximm:1.0 S0_AXI RDATA";
  attribute X_INTERFACE_INFO of s0_axi_rresp : signal is "xilinx.com:interface:aximm:1.0 S0_AXI RRESP";
  attribute X_INTERFACE_INFO of s0_axi_wdata : signal is "xilinx.com:interface:aximm:1.0 S0_AXI WDATA";
  attribute X_INTERFACE_INFO of s0_axi_wstrb : signal is "xilinx.com:interface:aximm:1.0 S0_AXI WSTRB";
begin
  s0_axi_bresp(1) <= \<const0>\;
  s0_axi_bresp(0) <= \<const0>\;
  s0_axi_rresp(1) <= \<const0>\;
  s0_axi_rresp(0) <= \<const0>\;
GND: unisim.vcomponents.GND
     port map (
      G => \<const0>\
    );
inst: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_breath_led_ip_v1_0
     port map (
      S_AXI_ARREADY => s0_axi_arready,
      S_AXI_AWREADY => s0_axi_awready,
      S_AXI_WREADY => s0_axi_wready,
      led => led,
      s0_axi_aclk => s0_axi_aclk,
      s0_axi_araddr(1 downto 0) => s0_axi_araddr(3 downto 2),
      s0_axi_aresetn => s0_axi_aresetn,
      s0_axi_arvalid => s0_axi_arvalid,
      s0_axi_awaddr(1 downto 0) => s0_axi_awaddr(3 downto 2),
      s0_axi_awvalid => s0_axi_awvalid,
      s0_axi_bready => s0_axi_bready,
      s0_axi_bvalid => s0_axi_bvalid,
      s0_axi_rdata(31 downto 0) => s0_axi_rdata(31 downto 0),
      s0_axi_rready => s0_axi_rready,
      s0_axi_rvalid => s0_axi_rvalid,
      s0_axi_wdata(31 downto 0) => s0_axi_wdata(31 downto 0),
      s0_axi_wstrb(3 downto 0) => s0_axi_wstrb(3 downto 0),
      s0_axi_wvalid => s0_axi_wvalid
    );
end STRUCTURE;
