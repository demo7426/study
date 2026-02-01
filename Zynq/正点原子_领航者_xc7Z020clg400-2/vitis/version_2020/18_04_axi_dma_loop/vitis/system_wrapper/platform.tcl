# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct D:\Zynq\vitis\version_2020\18_04_axi_dma_loop\vitis\system_wrapper\platform.tcl
# 
# OR launch xsct and run below command.
# source D:\Zynq\vitis\version_2020\18_04_axi_dma_loop\vitis\system_wrapper\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {system_wrapper}\
-hw {D:\Zynq\vitis\version_2020\18_04_axi_dma_loop\vitis\system_wrapper.xsa}\
-fsbl-target {psu_cortexa53_0} -out {D:/Zynq/vitis/version_2020/18_04_axi_dma_loop/vitis}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {empty_application}
platform generate -domains 
platform active {system_wrapper}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
domain active {zynq_fsbl}
bsp reload
domain active {standalone_ps7_cortexa9_0}
bsp reload
platform generate
platform clean
platform generate
platform active {system_wrapper}
bsp reload
domain active {zynq_fsbl}
bsp reload
platform config -updatehw {D:/Zynq/vitis/version_2020/18_04_axi_dma_loop/vitis/system_wrapper.xsa}
bsp reload
bsp reload
domain active {standalone_ps7_cortexa9_0}
bsp reload
platform clean
platform generate
platform clean
platform generate
platform clean
