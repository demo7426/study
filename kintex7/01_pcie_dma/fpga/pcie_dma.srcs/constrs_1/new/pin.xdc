#BANK116
set_property PACKAGE_PIN L8 [get_ports {pcie_ref_clk_p[0]}]
set_property PACKAGE_PIN L7 [get_ports {pcie_ref_clk_n[0]}]
create_clock -period 10.000 -name pcie_refclk_1 [get_ports pcie_ref_clk_p]

# PCIe MGT interface
#set_property PACKAGE_PIN {} [get_ports {pcie_mgt_rxp[4]}]
#set_property PACKAGE_PIN {} [get_ports {pcie_mgt_rxp[5]}]
#set_property PACKAGE_PIN {} [get_ports {pcie_mgt_rxp[6]}]
#set_property PACKAGE_PIN {} [get_ports {pcie_mgt_rxp[7]}]
set_property PACKAGE_PIN M6 [get_ports {pcie_mgt_rxp[3]}]
set_property PACKAGE_PIN P6 [get_ports {pcie_mgt_rxp[2]}]
set_property PACKAGE_PIN R4 [get_ports {pcie_mgt_rxp[1]}]
set_property PACKAGE_PIN T6 [get_ports {pcie_mgt_rxp[0]}]

set_property PACKAGE_PIN L21 [get_ports reset_rst_n]
set_property IOSTANDARD LVCMOS33 [get_ports reset_rst_n]

set_property PULLUP true [get_ports reset_rst_n]
#set_property PULLUP true [get_ports {pcie_rst_n[0]}]

#SPI 相关设置用于程序固化
set_property BITSTREAM.CONFIG.SPI_BUSWIDTH 4 [current_design]
set_property CONFIG_MODE SPIx4 [current_design]
set_property BITSTREAM.CONFIG.CONFIGRATE 50 [current_design]
set_property BITSTREAM.GENERAL.COMPRESS TRUE [current_design]
set_property BITSTREAM.CONFIG.SPI_FALL_EDGE Yes [current_design]
set_property CFGBVS VCCO [current_design]
set_property CONFIG_VOLTAGE 3.3 [current_design]

