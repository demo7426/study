# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct D:\Zynq\vitis\freertos\vitis\system_wrapper\platform.tcl
# 
# OR launch xsct and run below command.
# source D:\Zynq\vitis\freertos\vitis\system_wrapper\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {system_wrapper}\
-hw {D:\Zynq\vitis\freertos\vitis\system_wrapper.xsa}\
-fsbl-target {psu_cortexa53_0} -out {D:/Zynq/vitis/freertos/vitis}

platform write
domain create -name {freertos10_xilinx_ps7_cortexa9_0} -display-name {freertos10_xilinx_ps7_cortexa9_0} -os {freertos10_xilinx} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {freertos_hello_world}
platform generate -domains 
platform active {system_wrapper}
domain active {zynq_fsbl}
domain active {freertos10_xilinx_ps7_cortexa9_0}
platform generate -quick
platform generate
platform config -updatehw {D:/Zynq/vitis/freertos/vitis/system_wrapper.xsa}
bsp reload
catch {bsp regenerate}
domain active {zynq_fsbl}
bsp reload
catch {bsp regenerate}
platform generate -domains freertos10_xilinx_ps7_cortexa9_0,zynq_fsbl 
platform clean
platform generate
platform clean
