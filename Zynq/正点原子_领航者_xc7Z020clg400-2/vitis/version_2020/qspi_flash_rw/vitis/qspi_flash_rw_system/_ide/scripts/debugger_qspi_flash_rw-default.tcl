# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: D:\Zynq\vitis\version_2020\qspi_flash_rw\vitis\qspi_flash_rw_system\_ide\scripts\debugger_qspi_flash_rw-default.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source D:\Zynq\vitis\version_2020\qspi_flash_rw\vitis\qspi_flash_rw_system\_ide\scripts\debugger_qspi_flash_rw-default.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw D:/Zynq/vitis/version_2020/qspi_flash_rw/vitis/system_wrapper/export/system_wrapper/hw/system_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source D:/Zynq/vitis/version_2020/qspi_flash_rw/vitis/qspi_flash_rw/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow D:/Zynq/vitis/version_2020/qspi_flash_rw/vitis/qspi_flash_rw/Debug/qspi_flash_rw.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A9*#0"}
con
