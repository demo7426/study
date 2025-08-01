#ifndef IP_SYSTEM_AXI_SMC_0_SC_H_
#define IP_SYSTEM_AXI_SMC_0_SC_H_

// (c) Copyright 1995-2023 Xilinx, Inc. All rights reserved.
// 
// This file contains confidential and proprietary information
// of Xilinx, Inc. and is protected under U.S. and
// international copyright and other intellectual property
// laws.
// 
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// Xilinx, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
// WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) Xilinx shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or Xilinx had been advised of the
// possibility of the same.
// 
// CRITICAL APPLICATIONS
// Xilinx products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, "Critical
// Applications"). Customer assumes the sole risk and
// liability of any use of Xilinx products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
// 
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
// 
// DO NOT MODIFY THIS FILE.


#ifndef XTLM
#include "xtlm.h"
#endif
#ifndef SYSTEMC_INCLUDED
#include <systemc>
#endif

#if defined(_MSC_VER)
#define DllExport __declspec(dllexport)
#elif defined(__GNUC__)
#define DllExport __attribute__ ((visibility("default")))
#else
#define DllExport
#endif

class smartconnect;

class DllExport system_axi_smc_0_sc : public sc_core::sc_module
{
public:

  system_axi_smc_0_sc(const sc_core::sc_module_name& nm);
  virtual ~system_axi_smc_0_sc();

  // module socket-to-socket AXI TLM interfaces

  xtlm::xtlm_aximm_target_socket* S00_AXI_tlm_aximm_read_socket;
  xtlm::xtlm_aximm_target_socket* S00_AXI_tlm_aximm_write_socket;
  xtlm::xtlm_aximm_initiator_socket* M00_AXI_tlm_aximm_read_socket;
  xtlm::xtlm_aximm_initiator_socket* M00_AXI_tlm_aximm_write_socket;
  xtlm::xtlm_aximm_initiator_socket* M01_AXI_tlm_aximm_read_socket;
  xtlm::xtlm_aximm_initiator_socket* M01_AXI_tlm_aximm_write_socket;

  // module socket-to-socket TLM interfaces


protected:

  smartconnect* mp_impl;

private:

  system_axi_smc_0_sc(const system_axi_smc_0_sc&);
  const system_axi_smc_0_sc& operator=(const system_axi_smc_0_sc&);

};

#endif // IP_SYSTEM_AXI_SMC_0_SC_H_
