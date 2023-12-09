// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VTOP_H_
#define _VTOP_H_  // guard

#include "verilated_heavy.h"

//==========

class Vtop__Syms;

//----------

VL_MODULE(Vtop) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(sysclk,0,0);
    VL_IN8(cpu_resetn,0,0);
    VL_OUT8(uart_tx,0,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*4:0*/ top__DOT__rs1E1;
        CData/*4:0*/ top__DOT__rs2E1;
        CData/*4:0*/ top__DOT__rs1E2;
        CData/*4:0*/ top__DOT__rs2E2;
        CData/*4:0*/ top__DOT__rdE1;
        CData/*4:0*/ top__DOT__rdE2;
        CData/*4:0*/ top__DOT__rdM1;
        CData/*4:0*/ top__DOT__rdM2;
        CData/*4:0*/ top__DOT__rdW1;
        CData/*4:0*/ top__DOT__rdW2;
        CData/*1:0*/ top__DOT__branch_numberD;
        CData/*1:0*/ top__DOT__branch_numberE;
        CData/*1:0*/ top__DOT__jump_codeDj;
        CData/*1:0*/ top__DOT__jump_codeEj;
        CData/*2:0*/ top__DOT__branch_codeDj;
        CData/*2:0*/ top__DOT__branch_codeEj;
        CData/*0:0*/ top__DOT__fail_predictD;
        CData/*0:0*/ top__DOT__fail_predictE;
        CData/*0:0*/ top__DOT__fail_predict;
        CData/*0:0*/ top__DOT__hit_predict1;
        CData/*1:0*/ top__DOT__state1_in;
        CData/*1:0*/ top__DOT__state2_in;
        CData/*1:0*/ top__DOT__stateD1;
        CData/*1:0*/ top__DOT__stateD2;
        CData/*1:0*/ top__DOT__stateEj;
        CData/*0:0*/ top__DOT__is_depend;
        CData/*0:0*/ top__DOT__stall;
        CData/*5:0*/ top__DOT__alu_codeD1;
        CData/*5:0*/ top__DOT__alu_codeD2;
        CData/*5:0*/ top__DOT__alu_codeE1;
        CData/*5:0*/ top__DOT__alu_codeE2;
        CData/*0:0*/ top__DOT__alu_srcE1;
        CData/*0:0*/ top__DOT__alu_srcE2;
        CData/*0:0*/ top__DOT__reg_writeE1;
        CData/*0:0*/ top__DOT__reg_writeE2;
        CData/*0:0*/ top__DOT__reg_writeM1;
        CData/*0:0*/ top__DOT__reg_writeM2;
        CData/*0:0*/ top__DOT__reg_writeW1;
        CData/*0:0*/ top__DOT__reg_writeW2;
        CData/*1:0*/ top__DOT__mem_storeD1;
        CData/*1:0*/ top__DOT__mem_storeD2;
        CData/*1:0*/ top__DOT__mem_storeE1;
        CData/*1:0*/ top__DOT__mem_storeE2;
        CData/*1:0*/ top__DOT__mem_storeM1;
        CData/*1:0*/ top__DOT__mem_storeM2;
        CData/*2:0*/ top__DOT__mem_loadD1;
        CData/*2:0*/ top__DOT__mem_loadD2;
        CData/*2:0*/ top__DOT__mem_loadE1;
        CData/*2:0*/ top__DOT__mem_loadE2;
        CData/*2:0*/ top__DOT__mem_loadM1;
        CData/*2:0*/ top__DOT__mem_loadM2;
        CData/*1:0*/ top__DOT__jump_codeD1;
        CData/*1:0*/ top__DOT__jump_codeD2;
        CData/*0:0*/ top__DOT__cannot_calcpc;
        CData/*0:0*/ top__DOT__uart_we;
        CData/*0:0*/ top__DOT__uart_OUT_data;
        CData/*1:0*/ top__DOT__check__DOT__state2;
        CData/*1:0*/ top__DOT__check__DOT__state2_buffer;
        CData/*0:0*/ top__DOT__check__DOT__was_depend;
        CData/*0:0*/ top__DOT__check__DOT__store1;
        CData/*1:0*/ top__DOT__data_ram__DOT__mem_store;
        CData/*1:0*/ top__DOT__data_ram__DOT__offset;
        CData/*1:0*/ top__DOT__data_ram__DOT__mem_store_before;
        CData/*0:0*/ top__DOT__d_calcpc__DOT__flag;
    };
    struct {
        CData/*0:0*/ top__DOT__e_calcpc__DOT__flag;
        CData/*3:0*/ top__DOT__uart0__DOT__bitcount;
        CData/*0:0*/ top__DOT__uart0__DOT__uart_busy;
        CData/*0:0*/ top__DOT__uart0__DOT__sending;
        SData/*12:0*/ top__DOT__pcD1;
        SData/*12:0*/ top__DOT__pcD2;
        SData/*12:0*/ top__DOT__pcE1;
        SData/*12:0*/ top__DOT__pcE2;
        SData/*12:0*/ top__DOT__pc1_in;
        SData/*12:0*/ top__DOT__pc2_in;
        SData/*12:0*/ top__DOT__pcDj;
        SData/*12:0*/ top__DOT__pcEj;
        SData/*12:0*/ top__DOT__immDj;
        SData/*12:0*/ top__DOT__immEj;
        SData/*12:0*/ top__DOT__true_pcD;
        SData/*12:0*/ top__DOT__true_pcE;
        SData/*12:0*/ top__DOT__inst_rom__DOT__pc;
        SData/*12:0*/ top__DOT__inst_rom__DOT__PC;
        SData/*12:0*/ top__DOT__check__DOT__pc1;
        SData/*12:0*/ top__DOT__check__DOT__pc2;
        SData/*12:0*/ top__DOT__check__DOT__pc2_buffer;
        SData/*13:0*/ top__DOT__data_ram__DOT__resultM_before;
        SData/*12:0*/ top__DOT__e_calcpc__DOT__jump_pc;
        SData/*8:0*/ top__DOT__uart0__DOT__shifter;
        IData/*31:0*/ top__DOT__instF1;
        IData/*31:0*/ top__DOT__instF2;
        IData/*31:0*/ top__DOT__instD1;
        IData/*31:0*/ top__DOT__instD2;
        IData/*31:0*/ top__DOT__inst1_in;
        IData/*31:0*/ top__DOT__inst2_in;
        IData/*31:0*/ top__DOT__immD1;
        IData/*31:0*/ top__DOT__immD2;
        IData/*31:0*/ top__DOT__immE1;
        IData/*31:0*/ top__DOT__immE2;
        IData/*31:0*/ top__DOT__source1D1;
        IData/*31:0*/ top__DOT__source2D1;
        IData/*31:0*/ top__DOT__source1D2;
        IData/*31:0*/ top__DOT__source2D2;
        IData/*31:0*/ top__DOT__source1E1;
        IData/*31:0*/ top__DOT__source2E1;
        IData/*31:0*/ top__DOT__source1E2;
        IData/*31:0*/ top__DOT__source2E2;
        IData/*31:0*/ top__DOT__reg_data1E1;
        IData/*31:0*/ top__DOT__reg_data2E1;
        IData/*31:0*/ top__DOT__reg_data1E2;
        IData/*31:0*/ top__DOT__reg_data2E2;
        IData/*31:0*/ top__DOT__reg_data2M1;
        IData/*31:0*/ top__DOT__reg_data2M2;
        IData/*31:0*/ top__DOT__distM1;
        IData/*31:0*/ top__DOT__distM2;
        IData/*31:0*/ top__DOT__distW1;
        IData/*31:0*/ top__DOT__distW2;
        IData/*31:0*/ top__DOT__resultE1;
        IData/*31:0*/ top__DOT__resultE2;
        IData/*31:0*/ top__DOT__resultM1;
        IData/*31:0*/ top__DOT__resultM2;
        IData/*31:0*/ top__DOT__reg_data1Dj;
        IData/*31:0*/ top__DOT__reg_data2Dj;
        IData/*31:0*/ top__DOT__check__DOT__inst1;
        IData/*31:0*/ top__DOT__check__DOT__inst2;
        IData/*31:0*/ top__DOT__check__DOT__inst2_buffer;
        IData/*31:0*/ top__DOT__data_ram__DOT__r_data1;
        IData/*31:0*/ top__DOT__data_ram__DOT__r_data2;
        IData/*31:0*/ top__DOT__data_ram__DOT__resultM;
    };
    struct {
        IData/*31:0*/ top__DOT__data_ram__DOT__Source;
        IData/*31:0*/ top__DOT__data_ram__DOT__store_data;
        IData/*31:0*/ top__DOT__data_ram__DOT__store_data_before;
        IData/*31:0*/ top__DOT__data_ram__DOT__r_data1_true;
        IData/*31:0*/ top__DOT__data_ram__DOT__r_data2_true;
        IData/*31:0*/ top__DOT__data_ram__DOT__r_data_true;
        IData/*31:0*/ top__DOT__e_calcpc__DOT__reg_data1;
        IData/*17:0*/ top__DOT__predict__DOT__r_data1;
        IData/*17:0*/ top__DOT__predict__DOT__r_data2;
        IData/*28:0*/ top__DOT__uart0__DOT__d;
        IData/*28:0*/ top__DOT__uart0__DOT__dNxt;
        IData/*31:0*/ top__DOT__hardware_counter__DOT__cycles;
        IData/*31:0*/ top__DOT__inst_rom__DOT__inst_rom_block__DOT__mem[8192];
        IData/*31:0*/ top__DOT__regfile__DOT__reg_ram__DOT__mem1[32];
        IData/*31:0*/ top__DOT__regfile__DOT__reg_ram__DOT__mem2[32];
        IData/*31:0*/ top__DOT__data_ram__DOT__data_ram_block__DOT__mem[16384];
        IData/*17:0*/ top__DOT__predict__DOT__cache__DOT__mem[2048];
    };
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*5:0*/ __Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout;
    CData/*6:0*/ __Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode;
    CData/*2:0*/ __Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3;
    CData/*0:0*/ __Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct7;
    CData/*1:0*/ __Vfunc_top__DOT__decoder1__DOT__MemStore__2__Vfuncout;
    CData/*5:0*/ __Vfunc_top__DOT__decoder1__DOT__MemStore__2__alu_code;
    CData/*2:0*/ __Vfunc_top__DOT__decoder1__DOT__MemLoad__3__Vfuncout;
    CData/*5:0*/ __Vfunc_top__DOT__decoder1__DOT__MemLoad__3__alu_code;
    CData/*5:0*/ __Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout;
    CData/*6:0*/ __Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode;
    CData/*2:0*/ __Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3;
    CData/*0:0*/ __Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct7;
    CData/*1:0*/ __Vfunc_top__DOT__decoder2__DOT__MemStore__6__Vfuncout;
    CData/*5:0*/ __Vfunc_top__DOT__decoder2__DOT__MemStore__6__alu_code;
    CData/*2:0*/ __Vfunc_top__DOT__decoder2__DOT__MemLoad__7__Vfuncout;
    CData/*5:0*/ __Vfunc_top__DOT__decoder2__DOT__MemLoad__7__alu_code;
    CData/*5:0*/ __Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code;
    CData/*5:0*/ __Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code;
    CData/*0:0*/ __Vfunc_top__DOT__d_calcpc__DOT__Flag__10__Vfuncout;
    CData/*2:0*/ __Vfunc_top__DOT__d_calcpc__DOT__Flag__10__branch_code;
    CData/*0:0*/ __Vfunc_top__DOT__e_calcpc__DOT__Flag__11__Vfuncout;
    CData/*2:0*/ __Vfunc_top__DOT__e_calcpc__DOT__Flag__11__branch_code;
    CData/*0:0*/ __Vclklast__TOP__cpu_resetn;
    CData/*0:0*/ __Vclklast__TOP__sysclk;
    IData/*31:0*/ __Vfunc_top__DOT__decoder1__DOT__Imm__0__Vfuncout;
    IData/*31:0*/ __Vfunc_top__DOT__decoder1__DOT__Imm__0__inst;
    IData/*31:0*/ __Vfunc_top__DOT__decoder2__DOT__Imm__4__Vfuncout;
    IData/*31:0*/ __Vfunc_top__DOT__decoder2__DOT__Imm__4__inst;
    IData/*31:0*/ __Vfunc_top__DOT__alu1__DOT__RESULT__8__Vfuncout;
    IData/*31:0*/ __Vfunc_top__DOT__alu1__DOT__RESULT__8__src1;
    IData/*31:0*/ __Vfunc_top__DOT__alu1__DOT__RESULT__8__src2;
    IData/*31:0*/ __Vfunc_top__DOT__alu1__DOT__RESULT__8__PC;
    IData/*31:0*/ __Vfunc_top__DOT__alu2__DOT__RESULT__9__Vfuncout;
    IData/*31:0*/ __Vfunc_top__DOT__alu2__DOT__RESULT__9__src1;
    IData/*31:0*/ __Vfunc_top__DOT__alu2__DOT__RESULT__9__src2;
    IData/*31:0*/ __Vfunc_top__DOT__alu2__DOT__RESULT__9__PC;
    IData/*31:0*/ __Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data1;
    IData/*31:0*/ __Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data2;
    IData/*31:0*/ __Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data1;
    IData/*31:0*/ __Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data2;
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vtop__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vtop);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vtop(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vtop();
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vtop__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vtop__Syms* symsp, bool first);
  private:
    static QData _change_request(Vtop__Syms* __restrict vlSymsp);
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vtop__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vtop__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vtop__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _initial__TOP__4(Vtop__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _multiclk__TOP__7(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__1(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__2(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__3(Vtop__Syms* __restrict vlSymsp);
    static void _sequent__TOP__6(Vtop__Syms* __restrict vlSymsp);
    static void _settle__TOP__5(Vtop__Syms* __restrict vlSymsp) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
