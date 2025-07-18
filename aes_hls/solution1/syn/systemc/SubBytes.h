// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and OpenCL
// Version: 2020.1.1
// Copyright (C) 1986-2020 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

#ifndef _SubBytes_HH_
#define _SubBytes_HH_

#include "systemc.h"
#include "AESL_pkg.h"

#include "SubBytes_sbox_V.h"

namespace ap_rtl {

struct SubBytes : public sc_module {
    // Port declarations 11
    sc_in_clk ap_clk;
    sc_in< sc_logic > ap_rst;
    sc_in< sc_logic > ap_start;
    sc_out< sc_logic > ap_done;
    sc_out< sc_logic > ap_idle;
    sc_out< sc_logic > ap_ready;
    sc_out< sc_lv<4> > state_V_address0;
    sc_out< sc_logic > state_V_ce0;
    sc_out< sc_logic > state_V_we0;
    sc_out< sc_lv<8> > state_V_d0;
    sc_in< sc_lv<8> > state_V_q0;


    // Module declarations
    SubBytes(sc_module_name name);
    SC_HAS_PROCESS(SubBytes);

    ~SubBytes();

    sc_trace_file* mVcdFile;

    SubBytes_sbox_V* sbox_V_U;
    sc_signal< sc_lv<5> > ap_CS_fsm;
    sc_signal< sc_logic > ap_CS_fsm_state1;
    sc_signal< sc_lv<8> > sbox_V_address0;
    sc_signal< sc_logic > sbox_V_ce0;
    sc_signal< sc_lv<8> > sbox_V_q0;
    sc_signal< sc_lv<3> > r_fu_75_p2;
    sc_signal< sc_lv<3> > r_reg_127;
    sc_signal< sc_logic > ap_CS_fsm_state2;
    sc_signal< sc_lv<6> > zext_ln80_fu_89_p1;
    sc_signal< sc_lv<6> > zext_ln80_reg_132;
    sc_signal< sc_lv<1> > icmp_ln79_fu_69_p2;
    sc_signal< sc_lv<3> > c_fu_99_p2;
    sc_signal< sc_lv<3> > c_reg_140;
    sc_signal< sc_logic > ap_CS_fsm_state3;
    sc_signal< sc_lv<4> > state_V_addr_reg_145;
    sc_signal< sc_lv<1> > icmp_ln80_fu_93_p2;
    sc_signal< sc_logic > ap_CS_fsm_state4;
    sc_signal< sc_lv<3> > r_0_reg_47;
    sc_signal< sc_lv<3> > c_0_reg_58;
    sc_signal< sc_logic > ap_CS_fsm_state5;
    sc_signal< sc_lv<64> > zext_ln544_2_fu_114_p1;
    sc_signal< sc_lv<64> > zext_ln544_fu_119_p1;
    sc_signal< sc_lv<5> > tmp_fu_81_p3;
    sc_signal< sc_lv<6> > zext_ln544_1_fu_105_p1;
    sc_signal< sc_lv<6> > add_ln544_fu_109_p2;
    sc_signal< sc_lv<5> > ap_NS_fsm;
    static const sc_logic ap_const_logic_1;
    static const sc_logic ap_const_logic_0;
    static const sc_lv<5> ap_ST_fsm_state1;
    static const sc_lv<5> ap_ST_fsm_state2;
    static const sc_lv<5> ap_ST_fsm_state3;
    static const sc_lv<5> ap_ST_fsm_state4;
    static const sc_lv<5> ap_ST_fsm_state5;
    static const sc_lv<32> ap_const_lv32_0;
    static const sc_lv<32> ap_const_lv32_1;
    static const sc_lv<1> ap_const_lv1_0;
    static const sc_lv<32> ap_const_lv32_2;
    static const sc_lv<32> ap_const_lv32_3;
    static const sc_lv<3> ap_const_lv3_0;
    static const sc_lv<1> ap_const_lv1_1;
    static const sc_lv<32> ap_const_lv32_4;
    static const sc_lv<3> ap_const_lv3_4;
    static const sc_lv<3> ap_const_lv3_1;
    static const sc_lv<2> ap_const_lv2_0;
    static const bool ap_const_boolean_1;
    // Thread declarations
    void thread_ap_clk_no_reset_();
    void thread_add_ln544_fu_109_p2();
    void thread_ap_CS_fsm_state1();
    void thread_ap_CS_fsm_state2();
    void thread_ap_CS_fsm_state3();
    void thread_ap_CS_fsm_state4();
    void thread_ap_CS_fsm_state5();
    void thread_ap_done();
    void thread_ap_idle();
    void thread_ap_ready();
    void thread_c_fu_99_p2();
    void thread_icmp_ln79_fu_69_p2();
    void thread_icmp_ln80_fu_93_p2();
    void thread_r_fu_75_p2();
    void thread_sbox_V_address0();
    void thread_sbox_V_ce0();
    void thread_state_V_address0();
    void thread_state_V_ce0();
    void thread_state_V_d0();
    void thread_state_V_we0();
    void thread_tmp_fu_81_p3();
    void thread_zext_ln544_1_fu_105_p1();
    void thread_zext_ln544_2_fu_114_p1();
    void thread_zext_ln544_fu_119_p1();
    void thread_zext_ln80_fu_89_p1();
    void thread_ap_NS_fsm();
};

}

using namespace ap_rtl;

#endif
