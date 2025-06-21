# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: D:\Zynq\vitis\axi_gpio_fsbl\vitis\axi_gpio_fsbl_system\_ide\scripts\debugger_axi_gpio_fsbl-default.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source D:\Zynq\vitis\axi_gpio_fsbl\vitis\axi_gpio_fsbl_system\_ide\scripts\debugger_axi_gpio_fsbl-default.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -filter {jtag_cable_name =~ "Digilent JTAG-SMT2 C306AFE5ABCD" && level==0 && jtag_device_ctx=="jsn-JTAG-SMT2-C306AFE5ABCD-23727093-0"}
fpga -file D:/Zynq/vitis/axi_gpio_fsbl/vitis/axi_gpio_fsbl/_ide/bitstream/system_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw D:/Zynq/vitis/axi_gpio_fsbl/vitis/system_wrapper/export/system_wrapper/hw/system_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
stop
source D:/Zynq/vitis/axi_gpio_fsbl/vitis/axi_gpio_fsbl/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
rst -processor
targets -set -nocase -filter {name =~ "*A9*#0"}
dow D:/Zynq/vitis/axi_gpio_fsbl/vitis/axi_gpio_fsbl/Debug/axi_gpio_fsbl.elf
configparams force-mem-access 0
bpadd -addr &main
