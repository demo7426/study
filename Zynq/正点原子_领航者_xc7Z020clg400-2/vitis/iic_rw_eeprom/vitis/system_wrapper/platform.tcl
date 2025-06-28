# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct D:\Zynq\vitis\iic_rw_eeprom\vitis\system_wrapper\platform.tcl
# 
# OR launch xsct and run below command.
# source D:\Zynq\vitis\iic_rw_eeprom\vitis\system_wrapper\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {system_wrapper}\
-hw {D:\Zynq\vitis\iic_rw_eeprom\vitis\system_wrapper.xsa}\
-fsbl-target {psu_cortexa53_0} -out {D:/Zynq/vitis/iic_rw_eeprom/vitis}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {empty_application}
platform generate -domains 
platform active {system_wrapper}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
bsp reload
domain active {zynq_fsbl}
bsp reload
platform generate
platform config -updatehw {D:/Zynq/vitis/iic_rw_eeprom/vitis/system_wrapper.xsa}
domain active {standalone_ps7_cortexa9_0}
bsp reload
catch {bsp regenerate}
domain active {zynq_fsbl}
bsp reload
catch {bsp regenerate}
platform generate
platform clean
platform generate
platform clean
