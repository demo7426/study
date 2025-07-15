# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct D:\Zynq\vitis\version_2020\dual_core_amp_system\vivado\vitis\system_wrapper\platform.tcl
# 
# OR launch xsct and run below command.
# source D:\Zynq\vitis\version_2020\dual_core_amp_system\vivado\vitis\system_wrapper\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {system_wrapper}\
-hw {D:\Zynq\vitis\version_2020\dual_core_amp_system\vivado\vitis\system_wrapper.xsa}\
-fsbl-target {psu_cortexa53_0} -out {D:/Zynq/vitis/version_2020/dual_core_amp_system/vivado/vitis}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {hello_world}
platform generate -domains 
platform active {system_wrapper}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
domain create -name {standalone_ps7_cortexa9_1} -os {standalone} -proc {ps7_cortexa9_1} -arch {32-bit} -display-name {standalone_ps7_cortexa9_1} -desc {} -runtime {cpp}
platform generate -domains 
platform write
domain -report -json
platform generate
bsp reload
platform active {system_wrapper}
platform clean
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
domain active {standalone_ps7_cortexa9_1}
bsp reload
bsp reload
bsp reload
