# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: D:\Zynq\vitis\gpio_mio_interrupt\vitis\gpio_mio_interrupt_system\_ide\scripts\debugger_gpio_mio_interrupt-default.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source D:\Zynq\vitis\gpio_mio_interrupt\vitis\gpio_mio_interrupt_system\_ide\scripts\debugger_gpio_mio_interrupt-default.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw D:/Zynq/vitis/gpio_mio_interrupt/vitis/system_wrapper/export/system_wrapper/hw/system_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source D:/Zynq/vitis/gpio_mio_interrupt/vitis/gpio_mio_interrupt/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow D:/Zynq/vitis/gpio_mio_interrupt/vitis/gpio_mio_interrupt/Debug/gpio_mio_interrupt.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A9*#0"}
con
