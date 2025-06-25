# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: D:\Zynq\vitis\uart_intr_loop\vitis\uart_intr_loop_system\_ide\scripts\debugger_uart_intr_loop-default.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source D:\Zynq\vitis\uart_intr_loop\vitis\uart_intr_loop_system\_ide\scripts\debugger_uart_intr_loop-default.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw D:/Zynq/vitis/uart_intr_loop/vitis/system_wrapper/export/system_wrapper/hw/system_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source D:/Zynq/vitis/uart_intr_loop/vitis/uart_intr_loop/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow D:/Zynq/vitis/uart_intr_loop/vitis/uart_intr_loop/Debug/uart_intr_loop.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A9*#0"}
con
