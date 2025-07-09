# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: D:\Zynq\vitis\custom_ip\vivado\vitis\custom_ip_system\_ide\scripts\debugger_custom_ip-default.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source D:\Zynq\vitis\custom_ip\vivado\vitis\custom_ip_system\_ide\scripts\debugger_custom_ip-default.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent JTAG-SMT2 C306AFE5ABCD" && level==0 && jtag_device_ctx=="jsn-JTAG-SMT2-C306AFE5ABCD-23727093-0"}
fpga -file D:/Zynq/vitis/custom_ip/vivado/vitis/custom_ip/_ide/bitstream/system_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw D:/Zynq/vitis/custom_ip/vivado/vitis/system_wrapper/export/system_wrapper/hw/system_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source D:/Zynq/vitis/custom_ip/vivado/vitis/custom_ip/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow D:/Zynq/vitis/custom_ip/vivado/vitis/custom_ip/Debug/custom_ip.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A9*#0"}
con
