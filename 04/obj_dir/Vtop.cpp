// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop.h"
#include "Vtop__Syms.h"

//==========

VL_CTOR_IMP(Vtop) {
    Vtop__Syms* __restrict vlSymsp = __VlSymsp = new Vtop__Syms(this, name());
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vtop::__Vconfigure(Vtop__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vtop::~Vtop() {
    delete __VlSymsp; __VlSymsp=NULL;
}

void Vtop::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtop::eval\n"); );
    Vtop__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("top.v", 3, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vtop::_eval_initial_loop(Vtop__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("top.v", 3, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vtop::_sequent__TOP__1(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_sequent__TOP__1\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*3:0*/ __Vdly__top__DOT__uart0__DOT__bitcount;
    SData/*8:0*/ __Vdly__top__DOT__uart0__DOT__shifter;
    // Body
    __Vdly__top__DOT__uart0__DOT__bitcount = vlTOPp->top__DOT__uart0__DOT__bitcount;
    __Vdly__top__DOT__uart0__DOT__shifter = vlTOPp->top__DOT__uart0__DOT__shifter;
    vlTOPp->top__DOT__hardware_counter__DOT__cycles 
        = ((IData)(vlTOPp->cpu_resetn) ? ((IData)(1U) 
                                          + vlTOPp->top__DOT__hardware_counter__DOT__cycles)
            : 0U);
    if (vlTOPp->cpu_resetn) {
        if (((IData)(vlTOPp->top__DOT__uart_we) & (~ (IData)(vlTOPp->top__DOT__uart0__DOT__uart_busy)))) {
            __Vdly__top__DOT__uart0__DOT__bitcount = 0xbU;
        }
        if (((IData)(vlTOPp->top__DOT__uart0__DOT__sending) 
             & (~ (vlTOPp->top__DOT__uart0__DOT__d 
                   >> 0x1cU)))) {
            __Vdly__top__DOT__uart0__DOT__bitcount 
                = (0xfU & ((IData)(vlTOPp->top__DOT__uart0__DOT__bitcount) 
                           - (IData)(1U)));
        }
    } else {
        __Vdly__top__DOT__uart0__DOT__bitcount = 0U;
    }
    if (vlTOPp->cpu_resetn) {
        if (((IData)(vlTOPp->top__DOT__uart_we) & (~ (IData)(
                                                             (0U 
                                                              != 
                                                              (7U 
                                                               & ((IData)(vlTOPp->top__DOT__uart0__DOT__bitcount) 
                                                                  >> 1U))))))) {
            __Vdly__top__DOT__uart0__DOT__shifter = 
                (0x1feU & (((1U <= (IData)(vlTOPp->top__DOT__mem_storeM1))
                             ? vlTOPp->top__DOT__reg_data2M1
                             : vlTOPp->top__DOT__reg_data2M2) 
                           << 1U));
        }
        if (((0U != (IData)(vlTOPp->top__DOT__uart0__DOT__bitcount)) 
             & (~ (vlTOPp->top__DOT__uart0__DOT__d 
                   >> 0x1cU)))) {
            __Vdly__top__DOT__uart0__DOT__shifter = 
                (0x100U | (0xffU & ((IData)(vlTOPp->top__DOT__uart0__DOT__shifter) 
                                    >> 1U)));
            vlTOPp->top__DOT__uart_OUT_data = (1U & (IData)(vlTOPp->top__DOT__uart0__DOT__shifter));
        }
    } else {
        __Vdly__top__DOT__uart0__DOT__shifter = 0U;
        vlTOPp->top__DOT__uart_OUT_data = 1U;
    }
    vlTOPp->top__DOT__uart0__DOT__shifter = __Vdly__top__DOT__uart0__DOT__shifter;
    vlTOPp->top__DOT__uart0__DOT__bitcount = __Vdly__top__DOT__uart0__DOT__bitcount;
    vlTOPp->uart_tx = vlTOPp->top__DOT__uart_OUT_data;
    vlTOPp->top__DOT__uart0__DOT__uart_busy = (0U != 
                                               (7U 
                                                & ((IData)(vlTOPp->top__DOT__uart0__DOT__bitcount) 
                                                   >> 1U)));
    vlTOPp->top__DOT__uart0__DOT__sending = (0U != (IData)(vlTOPp->top__DOT__uart0__DOT__bitcount));
    vlTOPp->top__DOT__uart0__DOT__d = ((IData)(vlTOPp->cpu_resetn)
                                        ? vlTOPp->top__DOT__uart0__DOT__dNxt
                                        : 0U);
    vlTOPp->top__DOT__uart0__DOT__dNxt = (0x1fffffffU 
                                          & (vlTOPp->top__DOT__uart0__DOT__d 
                                             + ((0x10000000U 
                                                 & vlTOPp->top__DOT__uart0__DOT__d)
                                                 ? 0x1c200U
                                                 : 0xfb3d0e00U)));
}

VL_INLINE_OPT void Vtop::_sequent__TOP__2(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_sequent__TOP__2\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*1:0*/ __Vdly__top__DOT__branch_numberD;
    CData/*1:0*/ __Vdly__top__DOT__check__DOT__state2_buffer;
    CData/*4:0*/ __Vdlyvdim0__top__DOT__regfile__DOT__reg_ram__DOT__mem1__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__regfile__DOT__reg_ram__DOT__mem1__v0;
    CData/*4:0*/ __Vdlyvdim0__top__DOT__regfile__DOT__reg_ram__DOT__mem2__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__regfile__DOT__reg_ram__DOT__mem2__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__data_ram__DOT__data_ram_block__DOT__mem__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__predict__DOT__cache__DOT__mem__v0;
    CData/*1:0*/ __Vdly__top__DOT__state1_in;
    CData/*1:0*/ __Vdly__top__DOT__stateD1;
    CData/*1:0*/ __Vdly__top__DOT__stateD2;
    SData/*13:0*/ __Vdlyvdim0__top__DOT__data_ram__DOT__data_ram_block__DOT__mem__v0;
    SData/*10:0*/ __Vdlyvdim0__top__DOT__predict__DOT__cache__DOT__mem__v0;
    IData/*31:0*/ __Vdlyvval__top__DOT__regfile__DOT__reg_ram__DOT__mem1__v0;
    IData/*31:0*/ __Vdlyvval__top__DOT__regfile__DOT__reg_ram__DOT__mem2__v0;
    IData/*31:0*/ __Vdlyvval__top__DOT__data_ram__DOT__data_ram_block__DOT__mem__v0;
    IData/*17:0*/ __Vdlyvval__top__DOT__predict__DOT__cache__DOT__mem__v0;
    IData/*31:0*/ __Vdly__top__DOT__instD1;
    IData/*31:0*/ __Vdly__top__DOT__instD2;
    // Body
    __Vdlyvset__top__DOT__data_ram__DOT__data_ram_block__DOT__mem__v0 = 0U;
    __Vdly__top__DOT__stateD2 = vlTOPp->top__DOT__stateD2;
    __Vdly__top__DOT__check__DOT__state2_buffer = vlTOPp->top__DOT__check__DOT__state2_buffer;
    __Vdly__top__DOT__state1_in = vlTOPp->top__DOT__state1_in;
    __Vdly__top__DOT__stateD1 = vlTOPp->top__DOT__stateD1;
    __Vdlyvset__top__DOT__predict__DOT__cache__DOT__mem__v0 = 0U;
    __Vdly__top__DOT__branch_numberD = vlTOPp->top__DOT__branch_numberD;
    __Vdly__top__DOT__instD2 = vlTOPp->top__DOT__instD2;
    __Vdly__top__DOT__instD1 = vlTOPp->top__DOT__instD1;
    __Vdlyvset__top__DOT__regfile__DOT__reg_ram__DOT__mem1__v0 = 0U;
    __Vdlyvset__top__DOT__regfile__DOT__reg_ram__DOT__mem2__v0 = 0U;
    if ((1U <= (IData)(vlTOPp->top__DOT__data_ram__DOT__mem_store))) {
        __Vdlyvval__top__DOT__data_ram__DOT__data_ram_block__DOT__mem__v0 
            = vlTOPp->top__DOT__data_ram__DOT__store_data;
        __Vdlyvset__top__DOT__data_ram__DOT__data_ram_block__DOT__mem__v0 = 1U;
        __Vdlyvdim0__top__DOT__data_ram__DOT__data_ram_block__DOT__mem__v0 
            = (0x3fffU & (vlTOPp->top__DOT__data_ram__DOT__resultM 
                          >> 2U));
    }
    __Vdly__top__DOT__stateD2 = ((IData)(vlTOPp->top__DOT__stall)
                                  ? (IData)(vlTOPp->top__DOT__stateD2)
                                  : ((IData)(vlTOPp->top__DOT__fail_predict)
                                      ? 0U : ((IData)(vlTOPp->top__DOT__is_depend)
                                               ? 0U
                                               : (IData)(vlTOPp->top__DOT__check__DOT__state2))));
    __Vdly__top__DOT__check__DOT__state2_buffer = (
                                                   (1U 
                                                    & (((~ (IData)(vlTOPp->cpu_resetn)) 
                                                        | (IData)(vlTOPp->top__DOT__fail_predictE)) 
                                                       | ((IData)(vlTOPp->top__DOT__fail_predictD) 
                                                          & (~ (IData)(vlTOPp->top__DOT__stall)))))
                                                    ? 0U
                                                    : 
                                                   ((IData)(vlTOPp->top__DOT__stall)
                                                     ? (IData)(vlTOPp->top__DOT__check__DOT__state2_buffer)
                                                     : (IData)(vlTOPp->top__DOT__check__DOT__state2)));
    vlTOPp->top__DOT__data_ram__DOT__r_data2 = vlTOPp->top__DOT__data_ram__DOT__data_ram_block__DOT__mem
        [(0x3fffU & (vlTOPp->top__DOT__resultE2 >> 2U))];
    vlTOPp->top__DOT__data_ram__DOT__r_data1 = vlTOPp->top__DOT__data_ram__DOT__data_ram_block__DOT__mem
        [(0x3fffU & (vlTOPp->top__DOT__resultE1 >> 2U))];
    vlTOPp->top__DOT__mem_storeM2 = vlTOPp->top__DOT__mem_storeE2;
    vlTOPp->top__DOT__alu_codeE2 = (((IData)(vlTOPp->top__DOT__stall) 
                                     | (IData)(vlTOPp->top__DOT__fail_predictE))
                                     ? 0U : (IData)(vlTOPp->top__DOT__alu_codeD2));
    vlTOPp->top__DOT__alu_codeE1 = (((IData)(vlTOPp->top__DOT__stall) 
                                     | (IData)(vlTOPp->top__DOT__fail_predictE))
                                     ? 0U : (IData)(vlTOPp->top__DOT__alu_codeD1));
    vlTOPp->top__DOT__pc2_in = ((1U & (((~ (IData)(vlTOPp->cpu_resetn)) 
                                        | (IData)(vlTOPp->top__DOT__fail_predict)) 
                                       | ((~ (IData)(vlTOPp->top__DOT__stall)) 
                                          & (IData)(vlTOPp->top__DOT__hit_predict1))))
                                 ? 0U : (0x1fffU & 
                                         ((IData)(vlTOPp->top__DOT__stall)
                                           ? (IData)(vlTOPp->top__DOT__pc2_in)
                                           : ((IData)(1U) 
                                              + (IData)(vlTOPp->top__DOT__inst_rom__DOT__pc)))));
    vlTOPp->top__DOT__data_ram__DOT__resultM_before 
        = (0x3fffU & (vlTOPp->top__DOT__data_ram__DOT__resultM 
                      >> 2U));
    vlTOPp->top__DOT__data_ram__DOT__store_data_before 
        = vlTOPp->top__DOT__data_ram__DOT__store_data;
    vlTOPp->top__DOT__data_ram__DOT__mem_store_before 
        = vlTOPp->top__DOT__data_ram__DOT__mem_store;
    vlTOPp->top__DOT__state2_in = ((1U & (((~ (IData)(vlTOPp->cpu_resetn)) 
                                           | (IData)(vlTOPp->top__DOT__fail_predict)) 
                                          | ((~ (IData)(vlTOPp->top__DOT__stall)) 
                                             & (IData)(vlTOPp->top__DOT__hit_predict1))))
                                    ? 0U : (3U & ((IData)(vlTOPp->top__DOT__stall)
                                                   ? (IData)(vlTOPp->top__DOT__state2_in)
                                                   : 
                                                  (vlTOPp->top__DOT__predict__DOT__r_data2 
                                                   >> 0xfU))));
    vlTOPp->top__DOT__mem_storeM1 = vlTOPp->top__DOT__mem_storeE1;
    vlTOPp->top__DOT__pcE2 = (((IData)(vlTOPp->top__DOT__stall) 
                               | (IData)(vlTOPp->top__DOT__fail_predictE))
                               ? 0U : (IData)(vlTOPp->top__DOT__pcD2));
    __Vdly__top__DOT__state1_in = ((1U & ((~ (IData)(vlTOPp->cpu_resetn)) 
                                          | (IData)(vlTOPp->top__DOT__fail_predict)))
                                    ? 0U : (3U & ((IData)(vlTOPp->top__DOT__stall)
                                                   ? (IData)(vlTOPp->top__DOT__state1_in)
                                                   : 
                                                  (vlTOPp->top__DOT__predict__DOT__r_data1 
                                                   >> 0xfU))));
    __Vdly__top__DOT__stateD1 = ((IData)(vlTOPp->top__DOT__stall)
                                  ? (IData)(vlTOPp->top__DOT__stateD1)
                                  : ((IData)(vlTOPp->top__DOT__fail_predict)
                                      ? 0U : ((IData)(vlTOPp->top__DOT__check__DOT__was_depend)
                                               ? (IData)(vlTOPp->top__DOT__check__DOT__state2_buffer)
                                               : (IData)(vlTOPp->top__DOT__state1_in))));
    vlTOPp->top__DOT__pcE1 = (((IData)(vlTOPp->top__DOT__stall) 
                               | (IData)(vlTOPp->top__DOT__fail_predictE))
                               ? 0U : (IData)(vlTOPp->top__DOT__pcD1));
    vlTOPp->top__DOT__immE2 = vlTOPp->top__DOT__immD2;
    vlTOPp->top__DOT__immE1 = vlTOPp->top__DOT__immD1;
    vlTOPp->top__DOT__check__DOT__pc2_buffer = ((1U 
                                                 & (((~ (IData)(vlTOPp->cpu_resetn)) 
                                                     | (IData)(vlTOPp->top__DOT__fail_predictE)) 
                                                    | ((IData)(vlTOPp->top__DOT__fail_predictD) 
                                                       & (~ (IData)(vlTOPp->top__DOT__stall)))))
                                                 ? 0U
                                                 : 
                                                ((IData)(vlTOPp->top__DOT__stall)
                                                  ? (IData)(vlTOPp->top__DOT__check__DOT__pc2_buffer)
                                                  : (IData)(vlTOPp->top__DOT__check__DOT__pc2)));
    vlTOPp->top__DOT__inst2_in = ((1U & (((~ (IData)(vlTOPp->cpu_resetn)) 
                                          | (IData)(vlTOPp->top__DOT__fail_predict)) 
                                         | ((~ (IData)(vlTOPp->top__DOT__stall)) 
                                            & (IData)(vlTOPp->top__DOT__hit_predict1))))
                                   ? 0U : ((IData)(vlTOPp->top__DOT__stall)
                                            ? vlTOPp->top__DOT__inst2_in
                                            : vlTOPp->top__DOT__instF2));
    vlTOPp->top__DOT__reg_data2M2 = vlTOPp->top__DOT__reg_data2E2;
    vlTOPp->top__DOT__reg_data2M1 = vlTOPp->top__DOT__reg_data2E1;
    vlTOPp->top__DOT__pc1_in = ((1U & ((~ (IData)(vlTOPp->cpu_resetn)) 
                                       | (IData)(vlTOPp->top__DOT__fail_predict)))
                                 ? 0U : ((IData)(vlTOPp->top__DOT__stall)
                                          ? (IData)(vlTOPp->top__DOT__pc1_in)
                                          : (IData)(vlTOPp->top__DOT__inst_rom__DOT__pc)));
    vlTOPp->top__DOT__immEj = vlTOPp->top__DOT__immDj;
    vlTOPp->top__DOT__check__DOT__inst2_buffer = ((1U 
                                                   & (((~ (IData)(vlTOPp->cpu_resetn)) 
                                                       | (IData)(vlTOPp->top__DOT__fail_predictE)) 
                                                      | ((IData)(vlTOPp->top__DOT__fail_predictD) 
                                                         & (~ (IData)(vlTOPp->top__DOT__stall)))))
                                                   ? 0U
                                                   : 
                                                  ((IData)(vlTOPp->top__DOT__stall)
                                                    ? vlTOPp->top__DOT__check__DOT__inst2_buffer
                                                    : vlTOPp->top__DOT__check__DOT__inst2));
    vlTOPp->top__DOT__pcD2 = ((IData)(vlTOPp->top__DOT__stall)
                               ? (IData)(vlTOPp->top__DOT__pcD2)
                               : ((IData)(vlTOPp->top__DOT__fail_predict)
                                   ? 0U : ((IData)(vlTOPp->top__DOT__is_depend)
                                            ? 0U : (IData)(vlTOPp->top__DOT__check__DOT__pc2))));
    vlTOPp->top__DOT__pcD1 = ((IData)(vlTOPp->top__DOT__stall)
                               ? (IData)(vlTOPp->top__DOT__pcD1)
                               : ((IData)(vlTOPp->top__DOT__fail_predict)
                                   ? 0U : (IData)(vlTOPp->top__DOT__check__DOT__pc1)));
    vlTOPp->top__DOT__inst1_in = ((1U & ((~ (IData)(vlTOPp->cpu_resetn)) 
                                         | (IData)(vlTOPp->top__DOT__fail_predict)))
                                   ? 0U : ((IData)(vlTOPp->top__DOT__stall)
                                            ? vlTOPp->top__DOT__inst1_in
                                            : vlTOPp->top__DOT__instF1));
    vlTOPp->top__DOT__branch_codeEj = (((IData)(vlTOPp->top__DOT__stall) 
                                        | (IData)(vlTOPp->top__DOT__fail_predictE))
                                        ? 0U : (IData)(vlTOPp->top__DOT__branch_codeDj));
    vlTOPp->top__DOT__check__DOT__was_depend = ((~ 
                                                 (((~ (IData)(vlTOPp->cpu_resetn)) 
                                                   | (IData)(vlTOPp->top__DOT__fail_predictE)) 
                                                  | ((IData)(vlTOPp->top__DOT__fail_predictD) 
                                                     & (~ (IData)(vlTOPp->top__DOT__stall))))) 
                                                & ((IData)(vlTOPp->top__DOT__stall)
                                                    ? (IData)(vlTOPp->top__DOT__check__DOT__was_depend)
                                                    : (IData)(vlTOPp->top__DOT__is_depend)));
    vlTOPp->top__DOT__source2E2 = vlTOPp->top__DOT__source2D2;
    vlTOPp->top__DOT__source2E1 = vlTOPp->top__DOT__source2D1;
    vlTOPp->top__DOT__alu_srcE2 = (1U & ((~ ((IData)(vlTOPp->top__DOT__stall) 
                                             | (IData)(vlTOPp->top__DOT__fail_predictE))) 
                                         & (((0x33U 
                                              == (0x7fU 
                                                  & vlTOPp->top__DOT__instD2)) 
                                             | (0x63U 
                                                == 
                                                (0x7fU 
                                                 & vlTOPp->top__DOT__instD2)))
                                             ? 0U : 1U)));
    vlTOPp->top__DOT__alu_srcE1 = (1U & ((~ ((IData)(vlTOPp->top__DOT__stall) 
                                             | (IData)(vlTOPp->top__DOT__fail_predictE))) 
                                         & (((0x33U 
                                              == (0x7fU 
                                                  & vlTOPp->top__DOT__instD1)) 
                                             | (0x63U 
                                                == 
                                                (0x7fU 
                                                 & vlTOPp->top__DOT__instD1)))
                                             ? 0U : 1U)));
    if ((1U <= (IData)(vlTOPp->top__DOT__jump_codeEj))) {
        __Vdlyvval__top__DOT__predict__DOT__cache__DOT__mem__v0 
            = (0x20000U | ((0x18000U & (((1U & ((IData)(vlTOPp->top__DOT__e_calcpc__DOT__flag) 
                                                | ((IData)(vlTOPp->top__DOT__jump_codeEj) 
                                                   >> 1U)))
                                          ? ((IData)(vlTOPp->top__DOT__stateEj) 
                                             + ((3U 
                                                 == (IData)(vlTOPp->top__DOT__stateEj))
                                                 ? 0U
                                                 : 1U))
                                          : ((IData)(vlTOPp->top__DOT__stateEj) 
                                             - ((0U 
                                                 == (IData)(vlTOPp->top__DOT__stateEj))
                                                 ? 0U
                                                 : 1U))) 
                                        << 0xfU)) | 
                           ((0x6000U & ((IData)(vlTOPp->top__DOT__pcEj) 
                                        << 2U)) | (IData)(vlTOPp->top__DOT__e_calcpc__DOT__jump_pc))));
        __Vdlyvset__top__DOT__predict__DOT__cache__DOT__mem__v0 = 1U;
        __Vdlyvdim0__top__DOT__predict__DOT__cache__DOT__mem__v0 
            = (0x7ffU & (IData)(vlTOPp->top__DOT__pcEj));
    }
    vlTOPp->top__DOT__branch_numberE = vlTOPp->top__DOT__branch_numberD;
    vlTOPp->top__DOT__source1E2 = vlTOPp->top__DOT__source1D2;
    vlTOPp->top__DOT__source1E1 = vlTOPp->top__DOT__source1D1;
    vlTOPp->top__DOT__rs2E2 = (0x1fU & (vlTOPp->top__DOT__instD2 
                                        >> 0x14U));
    vlTOPp->top__DOT__rs2E1 = (0x1fU & (vlTOPp->top__DOT__instD1 
                                        >> 0x14U));
    __Vdly__top__DOT__branch_numberD = ((1U & (((~ (IData)(vlTOPp->cpu_resetn)) 
                                                | (IData)(vlTOPp->top__DOT__fail_predictE)) 
                                               | ((IData)(vlTOPp->top__DOT__fail_predictD) 
                                                  & (~ (IData)(vlTOPp->top__DOT__stall)))))
                                         ? 0U : ((IData)(vlTOPp->top__DOT__stall)
                                                  ? (IData)(vlTOPp->top__DOT__branch_numberD)
                                                  : 
                                                 ((0x40U 
                                                   & vlTOPp->top__DOT__check__DOT__inst1)
                                                   ? 1U
                                                   : 
                                                  ((0x40U 
                                                    & vlTOPp->top__DOT__check__DOT__inst2)
                                                    ? 2U
                                                    : 0U))));
    vlTOPp->top__DOT__rs1E2 = (0x1fU & (vlTOPp->top__DOT__instD2 
                                        >> 0xfU));
    vlTOPp->top__DOT__rs1E1 = (0x1fU & (vlTOPp->top__DOT__instD1 
                                        >> 0xfU));
    vlTOPp->top__DOT__distW2 = ((IData)(vlTOPp->cpu_resetn)
                                 ? vlTOPp->top__DOT__distM2
                                 : 0U);
    vlTOPp->top__DOT__distW1 = ((IData)(vlTOPp->cpu_resetn)
                                 ? vlTOPp->top__DOT__distM1
                                 : 0U);
    vlTOPp->top__DOT__resultM2 = vlTOPp->top__DOT__resultE2;
    vlTOPp->top__DOT__resultM1 = vlTOPp->top__DOT__resultE1;
    vlTOPp->top__DOT__mem_loadM2 = vlTOPp->top__DOT__mem_loadE2;
    vlTOPp->top__DOT__mem_loadM1 = vlTOPp->top__DOT__mem_loadE1;
    __Vdly__top__DOT__instD2 = ((IData)(vlTOPp->top__DOT__stall)
                                 ? vlTOPp->top__DOT__instD2
                                 : ((IData)(vlTOPp->top__DOT__fail_predict)
                                     ? 0U : ((IData)(vlTOPp->top__DOT__is_depend)
                                              ? 0U : vlTOPp->top__DOT__check__DOT__inst2)));
    __Vdly__top__DOT__instD1 = ((IData)(vlTOPp->top__DOT__stall)
                                 ? vlTOPp->top__DOT__instD1
                                 : ((IData)(vlTOPp->top__DOT__fail_predict)
                                     ? 0U : vlTOPp->top__DOT__check__DOT__inst1));
    vlTOPp->top__DOT__reg_writeW2 = ((IData)(vlTOPp->cpu_resetn) 
                                     & (IData)(vlTOPp->top__DOT__reg_writeM2));
    vlTOPp->top__DOT__reg_writeW1 = ((IData)(vlTOPp->cpu_resetn) 
                                     & (IData)(vlTOPp->top__DOT__reg_writeM1));
    vlTOPp->top__DOT__rdW2 = ((IData)(vlTOPp->cpu_resetn)
                               ? (IData)(vlTOPp->top__DOT__rdM2)
                               : 0U);
    vlTOPp->top__DOT__rdW1 = ((IData)(vlTOPp->cpu_resetn)
                               ? (IData)(vlTOPp->top__DOT__rdM1)
                               : 0U);
    if (((IData)(vlTOPp->top__DOT__reg_writeM1) & (0U 
                                                   != (IData)(vlTOPp->top__DOT__rdM1)))) {
        __Vdlyvval__top__DOT__regfile__DOT__reg_ram__DOT__mem1__v0 
            = (vlTOPp->top__DOT__distM1 ^ vlTOPp->top__DOT__regfile__DOT__reg_ram__DOT__mem2
               [vlTOPp->top__DOT__rdM1]);
        __Vdlyvset__top__DOT__regfile__DOT__reg_ram__DOT__mem1__v0 = 1U;
        __Vdlyvdim0__top__DOT__regfile__DOT__reg_ram__DOT__mem1__v0 
            = vlTOPp->top__DOT__rdM1;
    }
    if ((((IData)(vlTOPp->top__DOT__reg_writeM2) & 
          (0U != (IData)(vlTOPp->top__DOT__rdM2))) 
         & ((IData)(vlTOPp->top__DOT__rdM1) != (IData)(vlTOPp->top__DOT__rdM2)))) {
        __Vdlyvval__top__DOT__regfile__DOT__reg_ram__DOT__mem2__v0 
            = (vlTOPp->top__DOT__distM2 ^ vlTOPp->top__DOT__regfile__DOT__reg_ram__DOT__mem1
               [vlTOPp->top__DOT__rdM2]);
        __Vdlyvset__top__DOT__regfile__DOT__reg_ram__DOT__mem2__v0 = 1U;
        __Vdlyvdim0__top__DOT__regfile__DOT__reg_ram__DOT__mem2__v0 
            = vlTOPp->top__DOT__rdM2;
    }
    if (__Vdlyvset__top__DOT__data_ram__DOT__data_ram_block__DOT__mem__v0) {
        vlTOPp->top__DOT__data_ram__DOT__data_ram_block__DOT__mem[__Vdlyvdim0__top__DOT__data_ram__DOT__data_ram_block__DOT__mem__v0] 
            = __Vdlyvval__top__DOT__data_ram__DOT__data_ram_block__DOT__mem__v0;
    }
    vlTOPp->top__DOT__check__DOT__state2_buffer = __Vdly__top__DOT__check__DOT__state2_buffer;
    vlTOPp->top__DOT__state1_in = __Vdly__top__DOT__state1_in;
    if (__Vdlyvset__top__DOT__predict__DOT__cache__DOT__mem__v0) {
        vlTOPp->top__DOT__predict__DOT__cache__DOT__mem[__Vdlyvdim0__top__DOT__predict__DOT__cache__DOT__mem__v0] 
            = __Vdlyvval__top__DOT__predict__DOT__cache__DOT__mem__v0;
    }
    if (__Vdlyvset__top__DOT__regfile__DOT__reg_ram__DOT__mem2__v0) {
        vlTOPp->top__DOT__regfile__DOT__reg_ram__DOT__mem2[__Vdlyvdim0__top__DOT__regfile__DOT__reg_ram__DOT__mem2__v0] 
            = __Vdlyvval__top__DOT__regfile__DOT__reg_ram__DOT__mem2__v0;
    }
    if (__Vdlyvset__top__DOT__regfile__DOT__reg_ram__DOT__mem1__v0) {
        vlTOPp->top__DOT__regfile__DOT__reg_ram__DOT__mem1[__Vdlyvdim0__top__DOT__regfile__DOT__reg_ram__DOT__mem1__v0] 
            = __Vdlyvval__top__DOT__regfile__DOT__reg_ram__DOT__mem1__v0;
    }
    vlTOPp->top__DOT__mem_storeE2 = (((IData)(vlTOPp->top__DOT__stall) 
                                      | (IData)(vlTOPp->top__DOT__fail_predictE))
                                      ? 0U : (IData)(vlTOPp->top__DOT__mem_storeD2));
    vlTOPp->top__DOT__data_ram__DOT__mem_store = ((IData)(vlTOPp->top__DOT__mem_storeM1) 
                                                  | (IData)(vlTOPp->top__DOT__mem_storeM2));
    vlTOPp->top__DOT__mem_storeE1 = (((IData)(vlTOPp->top__DOT__stall) 
                                      | (IData)(vlTOPp->top__DOT__fail_predictE))
                                      ? 0U : (IData)(vlTOPp->top__DOT__mem_storeD1));
    vlTOPp->top__DOT__data_ram__DOT__Source = ((1U 
                                                <= (IData)(vlTOPp->top__DOT__mem_storeM1))
                                                ? vlTOPp->top__DOT__reg_data2M1
                                                : vlTOPp->top__DOT__reg_data2M2);
    vlTOPp->top__DOT__inst_rom__DOT__pc = ((IData)(vlTOPp->cpu_resetn)
                                            ? (IData)(vlTOPp->top__DOT__inst_rom__DOT__PC)
                                            : 0U);
    vlTOPp->top__DOT__check__DOT__pc2 = ((IData)(vlTOPp->top__DOT__check__DOT__was_depend)
                                          ? (IData)(vlTOPp->top__DOT__pc1_in)
                                          : (IData)(vlTOPp->top__DOT__pc2_in));
    vlTOPp->top__DOT__check__DOT__state2 = ((IData)(vlTOPp->top__DOT__check__DOT__was_depend)
                                             ? (IData)(vlTOPp->top__DOT__state1_in)
                                             : (IData)(vlTOPp->top__DOT__state2_in));
    vlTOPp->top__DOT__check__DOT__inst2 = ((IData)(vlTOPp->top__DOT__check__DOT__was_depend)
                                            ? vlTOPp->top__DOT__inst1_in
                                            : vlTOPp->top__DOT__inst2_in);
    vlTOPp->top__DOT__check__DOT__pc1 = ((IData)(vlTOPp->top__DOT__check__DOT__was_depend)
                                          ? (IData)(vlTOPp->top__DOT__check__DOT__pc2_buffer)
                                          : (IData)(vlTOPp->top__DOT__pc1_in));
    vlTOPp->top__DOT__check__DOT__inst1 = ((IData)(vlTOPp->top__DOT__check__DOT__was_depend)
                                            ? vlTOPp->top__DOT__check__DOT__inst2_buffer
                                            : vlTOPp->top__DOT__inst1_in);
    vlTOPp->top__DOT__pcEj = vlTOPp->top__DOT__pcDj;
    vlTOPp->top__DOT__jump_codeEj = (((IData)(vlTOPp->top__DOT__stall) 
                                      | (IData)(vlTOPp->top__DOT__fail_predictE))
                                      ? 0U : (IData)(vlTOPp->top__DOT__jump_codeDj));
    vlTOPp->top__DOT__stateEj = ((2U & (IData)(vlTOPp->top__DOT__branch_numberD))
                                  ? (IData)(vlTOPp->top__DOT__stateD2)
                                  : (IData)(vlTOPp->top__DOT__stateD1));
    vlTOPp->top__DOT__data_ram__DOT__r_data2_true = 
        ((((IData)(vlTOPp->top__DOT__data_ram__DOT__resultM_before) 
           == (0x3fffU & (vlTOPp->top__DOT__resultM2 
                          >> 2U))) & (1U <= (IData)(vlTOPp->top__DOT__data_ram__DOT__mem_store_before)))
          ? vlTOPp->top__DOT__data_ram__DOT__store_data_before
          : vlTOPp->top__DOT__data_ram__DOT__r_data2);
    vlTOPp->top__DOT__data_ram__DOT__r_data1_true = 
        ((((IData)(vlTOPp->top__DOT__data_ram__DOT__resultM_before) 
           == (0x3fffU & (vlTOPp->top__DOT__resultM1 
                          >> 2U))) & (1U <= (IData)(vlTOPp->top__DOT__data_ram__DOT__mem_store_before)))
          ? vlTOPp->top__DOT__data_ram__DOT__store_data_before
          : vlTOPp->top__DOT__data_ram__DOT__r_data1);
    vlTOPp->top__DOT__data_ram__DOT__resultM = ((1U 
                                                 <= (IData)(vlTOPp->top__DOT__mem_storeM1))
                                                 ? vlTOPp->top__DOT__resultM1
                                                 : vlTOPp->top__DOT__resultM2);
    vlTOPp->top__DOT__uart_we = (((0xf6fff070U == vlTOPp->top__DOT__resultM1) 
                                  & (1U <= (IData)(vlTOPp->top__DOT__mem_storeM1))) 
                                 | ((0xf6fff070U == vlTOPp->top__DOT__resultM2) 
                                    & (1U <= (IData)(vlTOPp->top__DOT__mem_storeM2))));
    vlTOPp->top__DOT__data_ram__DOT__offset = (3U & 
                                               ((1U 
                                                 <= (IData)(vlTOPp->top__DOT__mem_storeM1))
                                                 ? vlTOPp->top__DOT__resultM1
                                                 : vlTOPp->top__DOT__resultM2));
    vlTOPp->top__DOT__mem_loadE2 = (((IData)(vlTOPp->top__DOT__stall) 
                                     | (IData)(vlTOPp->top__DOT__fail_predictE))
                                     ? 0U : (IData)(vlTOPp->top__DOT__mem_loadD2));
    vlTOPp->top__DOT__mem_loadE1 = (((IData)(vlTOPp->top__DOT__stall) 
                                     | (IData)(vlTOPp->top__DOT__fail_predictE))
                                     ? 0U : (IData)(vlTOPp->top__DOT__mem_loadD1));
    vlTOPp->top__DOT__reg_writeM1 = vlTOPp->top__DOT__reg_writeE1;
    vlTOPp->top__DOT__reg_writeM2 = vlTOPp->top__DOT__reg_writeE2;
    vlTOPp->top__DOT__rdM2 = vlTOPp->top__DOT__rdE2;
    vlTOPp->top__DOT__rdM1 = vlTOPp->top__DOT__rdE1;
    vlTOPp->top__DOT__check__DOT__store1 = (1U & ((
                                                   (~ 
                                                    (vlTOPp->top__DOT__check__DOT__inst1 
                                                     >> 6U)) 
                                                   & (vlTOPp->top__DOT__check__DOT__inst1 
                                                      >> 5U)) 
                                                  & (~ 
                                                     (vlTOPp->top__DOT__check__DOT__inst1 
                                                      >> 4U))));
    vlTOPp->top__DOT__stateD2 = __Vdly__top__DOT__stateD2;
    vlTOPp->top__DOT__stateD1 = __Vdly__top__DOT__stateD1;
    vlTOPp->top__DOT__branch_numberD = __Vdly__top__DOT__branch_numberD;
    vlTOPp->top__DOT__data_ram__DOT__r_data_true = 
        ((1U <= (IData)(vlTOPp->top__DOT__mem_storeM1))
          ? vlTOPp->top__DOT__data_ram__DOT__r_data1_true
          : vlTOPp->top__DOT__data_ram__DOT__r_data2_true);
    vlTOPp->top__DOT__is_depend = (((((((((vlTOPp->top__DOT__check__DOT__inst1 
                                           >> 2U) | 
                                          (vlTOPp->top__DOT__check__DOT__inst1 
                                           >> 4U)) 
                                         | (~ (vlTOPp->top__DOT__check__DOT__inst1 
                                               >> 5U))) 
                                        & (0U != (0x1fU 
                                                  & (vlTOPp->top__DOT__check__DOT__inst1 
                                                     >> 7U)))) 
                                       & ((((~ (vlTOPp->top__DOT__check__DOT__inst2 
                                                >> 2U)) 
                                            | ((~ (vlTOPp->top__DOT__check__DOT__inst2 
                                                   >> 3U)) 
                                               & (~ 
                                                  (vlTOPp->top__DOT__check__DOT__inst2 
                                                   >> 3U)))) 
                                           & ((0x1fU 
                                               & (vlTOPp->top__DOT__check__DOT__inst2 
                                                  >> 0xfU)) 
                                              == (0x1fU 
                                                  & (vlTOPp->top__DOT__check__DOT__inst1 
                                                     >> 7U)))) 
                                          | (((~ (vlTOPp->top__DOT__check__DOT__inst2 
                                                  >> 2U)) 
                                              & (vlTOPp->top__DOT__check__DOT__inst2 
                                                 >> 5U)) 
                                             & ((0x1fU 
                                                 & (vlTOPp->top__DOT__check__DOT__inst2 
                                                    >> 0x14U)) 
                                                == 
                                                (0x1fU 
                                                 & (vlTOPp->top__DOT__check__DOT__inst1 
                                                    >> 7U)))))) 
                                      | (vlTOPp->top__DOT__check__DOT__inst1 
                                         >> 6U)) | 
                                     ((IData)(vlTOPp->top__DOT__check__DOT__store1) 
                                      & (((~ (vlTOPp->top__DOT__check__DOT__inst2 
                                              >> 6U)) 
                                          & (vlTOPp->top__DOT__check__DOT__inst2 
                                             >> 5U)) 
                                         & (~ (vlTOPp->top__DOT__check__DOT__inst2 
                                               >> 4U))))) 
                                    | ((IData)(vlTOPp->top__DOT__check__DOT__store1) 
                                       & ((~ (vlTOPp->top__DOT__check__DOT__inst2 
                                              >> 5U)) 
                                          & (~ (vlTOPp->top__DOT__check__DOT__inst2 
                                                >> 2U))))) 
                                   & (0U != vlTOPp->top__DOT__check__DOT__inst2));
    vlTOPp->top__DOT__pcDj = ((2U & (IData)(vlTOPp->top__DOT__branch_numberD))
                               ? (IData)(vlTOPp->top__DOT__pcD2)
                               : (IData)(vlTOPp->top__DOT__pcD1));
    vlTOPp->top__DOT__data_ram__DOT__store_data = (
                                                   (1U 
                                                    == (IData)(vlTOPp->top__DOT__data_ram__DOT__mem_store))
                                                    ? 
                                                   ((0U 
                                                     == (IData)(vlTOPp->top__DOT__data_ram__DOT__offset))
                                                     ? 
                                                    ((0xffffff00U 
                                                      & vlTOPp->top__DOT__data_ram__DOT__r_data_true) 
                                                     | (0xffU 
                                                        & vlTOPp->top__DOT__data_ram__DOT__Source))
                                                     : 
                                                    ((1U 
                                                      == (IData)(vlTOPp->top__DOT__data_ram__DOT__offset))
                                                      ? 
                                                     ((0xffff0000U 
                                                       & vlTOPp->top__DOT__data_ram__DOT__r_data_true) 
                                                      | ((0xff00U 
                                                          & (vlTOPp->top__DOT__data_ram__DOT__Source 
                                                             << 8U)) 
                                                         | (0xffU 
                                                            & vlTOPp->top__DOT__data_ram__DOT__r_data_true)))
                                                      : 
                                                     ((2U 
                                                       == (IData)(vlTOPp->top__DOT__data_ram__DOT__offset))
                                                       ? 
                                                      ((0xff000000U 
                                                        & vlTOPp->top__DOT__data_ram__DOT__r_data_true) 
                                                       | ((0xff0000U 
                                                           & (vlTOPp->top__DOT__data_ram__DOT__Source 
                                                              << 0x10U)) 
                                                          | (0xffffU 
                                                             & vlTOPp->top__DOT__data_ram__DOT__r_data_true)))
                                                       : 
                                                      ((0xff000000U 
                                                        & (vlTOPp->top__DOT__data_ram__DOT__Source 
                                                           << 0x18U)) 
                                                       | (0xffffffU 
                                                          & vlTOPp->top__DOT__data_ram__DOT__r_data_true)))))
                                                    : 
                                                   ((2U 
                                                     == (IData)(vlTOPp->top__DOT__data_ram__DOT__mem_store))
                                                     ? 
                                                    ((0U 
                                                      == (IData)(vlTOPp->top__DOT__data_ram__DOT__offset))
                                                      ? 
                                                     ((0xffff0000U 
                                                       & vlTOPp->top__DOT__data_ram__DOT__r_data_true) 
                                                      | (0xffffU 
                                                         & vlTOPp->top__DOT__data_ram__DOT__Source))
                                                      : 
                                                     ((1U 
                                                       == (IData)(vlTOPp->top__DOT__data_ram__DOT__offset))
                                                       ? 
                                                      ((0xff000000U 
                                                        & vlTOPp->top__DOT__data_ram__DOT__r_data_true) 
                                                       | ((0xffff00U 
                                                           & (vlTOPp->top__DOT__data_ram__DOT__Source 
                                                              << 8U)) 
                                                          | (0xffU 
                                                             & vlTOPp->top__DOT__data_ram__DOT__r_data_true)))
                                                       : 
                                                      ((2U 
                                                        == (IData)(vlTOPp->top__DOT__data_ram__DOT__offset))
                                                        ? 
                                                       ((0xffff0000U 
                                                         & (vlTOPp->top__DOT__data_ram__DOT__Source 
                                                            << 0x10U)) 
                                                        | (0xffffU 
                                                           & vlTOPp->top__DOT__data_ram__DOT__r_data_true))
                                                        : 
                                                       ((0xff000000U 
                                                         & (vlTOPp->top__DOT__data_ram__DOT__Source 
                                                            << 0x18U)) 
                                                        | (0xffffffU 
                                                           & vlTOPp->top__DOT__data_ram__DOT__r_data_true)))))
                                                     : 
                                                    ((3U 
                                                      == (IData)(vlTOPp->top__DOT__data_ram__DOT__mem_store))
                                                      ? vlTOPp->top__DOT__data_ram__DOT__Source
                                                      : 0xffffffffU)));
    vlTOPp->top__DOT__reg_writeE1 = (1U & ((~ ((IData)(vlTOPp->top__DOT__stall) 
                                               | (IData)(vlTOPp->top__DOT__fail_predictE))) 
                                           & ((((((((0x37U 
                                                     == 
                                                     (0x7fU 
                                                      & vlTOPp->top__DOT__instD1)) 
                                                    | (0x17U 
                                                       == 
                                                       (0x7fU 
                                                        & vlTOPp->top__DOT__instD1))) 
                                                   | (0x6fU 
                                                      == 
                                                      (0x7fU 
                                                       & vlTOPp->top__DOT__instD1))) 
                                                  | (0x67U 
                                                     == 
                                                     (0x7fU 
                                                      & vlTOPp->top__DOT__instD1))) 
                                                 | (3U 
                                                    == 
                                                    (0x7fU 
                                                     & vlTOPp->top__DOT__instD1))) 
                                                | (0x13U 
                                                   == 
                                                   (0x7fU 
                                                    & vlTOPp->top__DOT__instD1))) 
                                               | (0x33U 
                                                  == 
                                                  (0x7fU 
                                                   & vlTOPp->top__DOT__instD1)))
                                               ? 1U
                                               : 0U)));
    vlTOPp->top__DOT__reg_writeE2 = (1U & ((~ ((IData)(vlTOPp->top__DOT__stall) 
                                               | (IData)(vlTOPp->top__DOT__fail_predictE))) 
                                           & ((((((((0x37U 
                                                     == 
                                                     (0x7fU 
                                                      & vlTOPp->top__DOT__instD2)) 
                                                    | (0x17U 
                                                       == 
                                                       (0x7fU 
                                                        & vlTOPp->top__DOT__instD2))) 
                                                   | (0x6fU 
                                                      == 
                                                      (0x7fU 
                                                       & vlTOPp->top__DOT__instD2))) 
                                                  | (0x67U 
                                                     == 
                                                     (0x7fU 
                                                      & vlTOPp->top__DOT__instD2))) 
                                                 | (3U 
                                                    == 
                                                    (0x7fU 
                                                     & vlTOPp->top__DOT__instD2))) 
                                                | (0x13U 
                                                   == 
                                                   (0x7fU 
                                                    & vlTOPp->top__DOT__instD2))) 
                                               | (0x33U 
                                                  == 
                                                  (0x7fU 
                                                   & vlTOPp->top__DOT__instD2)))
                                               ? 1U
                                               : 0U)));
    vlTOPp->top__DOT__rdE2 = (0x1fU & (vlTOPp->top__DOT__instD2 
                                       >> 7U));
    vlTOPp->top__DOT__rdE1 = (0x1fU & (vlTOPp->top__DOT__instD1 
                                       >> 7U));
    vlTOPp->top__DOT__reg_data2E1 = ((((((IData)(vlTOPp->top__DOT__rs2E1) 
                                         == (IData)(vlTOPp->top__DOT__rdM2)) 
                                        & (0U != (IData)(vlTOPp->top__DOT__rdM2))) 
                                       & (IData)(vlTOPp->top__DOT__reg_writeM2)) 
                                      & (0U == (IData)(vlTOPp->top__DOT__mem_loadM2)))
                                      ? vlTOPp->top__DOT__resultM2
                                      : ((((((IData)(vlTOPp->top__DOT__rs2E1) 
                                             == (IData)(vlTOPp->top__DOT__rdM1)) 
                                            & (0U != (IData)(vlTOPp->top__DOT__rdM1))) 
                                           & (IData)(vlTOPp->top__DOT__reg_writeM1)) 
                                          & (0U == (IData)(vlTOPp->top__DOT__mem_loadM1)))
                                          ? vlTOPp->top__DOT__resultM1
                                          : (((((IData)(vlTOPp->top__DOT__rs2E1) 
                                                == (IData)(vlTOPp->top__DOT__rdW2)) 
                                               & (0U 
                                                  != (IData)(vlTOPp->top__DOT__rdW2))) 
                                              & (IData)(vlTOPp->top__DOT__reg_writeW2))
                                              ? vlTOPp->top__DOT__distW2
                                              : (((
                                                   ((IData)(vlTOPp->top__DOT__rs2E1) 
                                                    == (IData)(vlTOPp->top__DOT__rdW1)) 
                                                   & (0U 
                                                      != (IData)(vlTOPp->top__DOT__rdW1))) 
                                                  & (IData)(vlTOPp->top__DOT__reg_writeW1))
                                                  ? vlTOPp->top__DOT__distW1
                                                  : vlTOPp->top__DOT__source2E1))));
    vlTOPp->top__DOT__reg_data2E2 = ((((((IData)(vlTOPp->top__DOT__rs2E2) 
                                         == (IData)(vlTOPp->top__DOT__rdM2)) 
                                        & (0U != (IData)(vlTOPp->top__DOT__rdM2))) 
                                       & (IData)(vlTOPp->top__DOT__reg_writeM2)) 
                                      & (0U == (IData)(vlTOPp->top__DOT__mem_loadM2)))
                                      ? vlTOPp->top__DOT__resultM2
                                      : ((((((IData)(vlTOPp->top__DOT__rs2E2) 
                                             == (IData)(vlTOPp->top__DOT__rdM1)) 
                                            & (0U != (IData)(vlTOPp->top__DOT__rdM1))) 
                                           & (IData)(vlTOPp->top__DOT__reg_writeM1)) 
                                          & (0U == (IData)(vlTOPp->top__DOT__mem_loadM1)))
                                          ? vlTOPp->top__DOT__resultM1
                                          : (((((IData)(vlTOPp->top__DOT__rs2E2) 
                                                == (IData)(vlTOPp->top__DOT__rdW2)) 
                                               & (0U 
                                                  != (IData)(vlTOPp->top__DOT__rdW2))) 
                                              & (IData)(vlTOPp->top__DOT__reg_writeW2))
                                              ? vlTOPp->top__DOT__distW2
                                              : (((
                                                   ((IData)(vlTOPp->top__DOT__rs2E2) 
                                                    == (IData)(vlTOPp->top__DOT__rdW1)) 
                                                   & (0U 
                                                      != (IData)(vlTOPp->top__DOT__rdW1))) 
                                                  & (IData)(vlTOPp->top__DOT__reg_writeW1))
                                                  ? vlTOPp->top__DOT__distW1
                                                  : vlTOPp->top__DOT__source2E2))));
    vlTOPp->top__DOT__reg_data1E1 = ((((((IData)(vlTOPp->top__DOT__rs1E1) 
                                         == (IData)(vlTOPp->top__DOT__rdM2)) 
                                        & (0U != (IData)(vlTOPp->top__DOT__rdM2))) 
                                       & (IData)(vlTOPp->top__DOT__reg_writeM2)) 
                                      & (0U == (IData)(vlTOPp->top__DOT__mem_loadM2)))
                                      ? vlTOPp->top__DOT__resultM2
                                      : ((((((IData)(vlTOPp->top__DOT__rs1E1) 
                                             == (IData)(vlTOPp->top__DOT__rdM1)) 
                                            & (0U != (IData)(vlTOPp->top__DOT__rdM1))) 
                                           & (IData)(vlTOPp->top__DOT__reg_writeM1)) 
                                          & (0U == (IData)(vlTOPp->top__DOT__mem_loadM1)))
                                          ? vlTOPp->top__DOT__resultM1
                                          : (((((IData)(vlTOPp->top__DOT__rs1E1) 
                                                == (IData)(vlTOPp->top__DOT__rdW2)) 
                                               & (0U 
                                                  != (IData)(vlTOPp->top__DOT__rdW2))) 
                                              & (IData)(vlTOPp->top__DOT__reg_writeW2))
                                              ? vlTOPp->top__DOT__distW2
                                              : (((
                                                   ((IData)(vlTOPp->top__DOT__rs1E1) 
                                                    == (IData)(vlTOPp->top__DOT__rdW1)) 
                                                   & (0U 
                                                      != (IData)(vlTOPp->top__DOT__rdW1))) 
                                                  & (IData)(vlTOPp->top__DOT__reg_writeW1))
                                                  ? vlTOPp->top__DOT__distW1
                                                  : vlTOPp->top__DOT__source1E1))));
    vlTOPp->top__DOT__reg_data1E2 = ((((((IData)(vlTOPp->top__DOT__rs1E2) 
                                         == (IData)(vlTOPp->top__DOT__rdM2)) 
                                        & (0U != (IData)(vlTOPp->top__DOT__rdM2))) 
                                       & (IData)(vlTOPp->top__DOT__reg_writeM2)) 
                                      & (0U == (IData)(vlTOPp->top__DOT__mem_loadM2)))
                                      ? vlTOPp->top__DOT__resultM2
                                      : ((((((IData)(vlTOPp->top__DOT__rs1E2) 
                                             == (IData)(vlTOPp->top__DOT__rdM1)) 
                                            & (0U != (IData)(vlTOPp->top__DOT__rdM1))) 
                                           & (IData)(vlTOPp->top__DOT__reg_writeM1)) 
                                          & (0U == (IData)(vlTOPp->top__DOT__mem_loadM1)))
                                          ? vlTOPp->top__DOT__resultM1
                                          : (((((IData)(vlTOPp->top__DOT__rs1E2) 
                                                == (IData)(vlTOPp->top__DOT__rdW2)) 
                                               & (0U 
                                                  != (IData)(vlTOPp->top__DOT__rdW2))) 
                                              & (IData)(vlTOPp->top__DOT__reg_writeW2))
                                              ? vlTOPp->top__DOT__distW2
                                              : (((
                                                   ((IData)(vlTOPp->top__DOT__rs1E2) 
                                                    == (IData)(vlTOPp->top__DOT__rdW1)) 
                                                   & (0U 
                                                      != (IData)(vlTOPp->top__DOT__rdW1))) 
                                                  & (IData)(vlTOPp->top__DOT__reg_writeW1))
                                                  ? vlTOPp->top__DOT__distW1
                                                  : vlTOPp->top__DOT__source1E2))));
    vlTOPp->top__DOT__instD2 = __Vdly__top__DOT__instD2;
    vlTOPp->top__DOT__instD1 = __Vdly__top__DOT__instD1;
    vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__PC 
        = (0x8000U | ((IData)(vlTOPp->top__DOT__pcE1) 
                      << 2U));
    vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code 
        = vlTOPp->top__DOT__alu_codeE1;
    vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2 
        = ((IData)(vlTOPp->top__DOT__alu_srcE1) ? vlTOPp->top__DOT__immE1
            : vlTOPp->top__DOT__reg_data2E1);
    vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
        = vlTOPp->top__DOT__reg_data1E1;
    vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__Vfuncout 
        = ((0x20U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
            ? 0U : ((0x10U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                     ? ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                         ? ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                             ? 0U : ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                      ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                          ? (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__PC 
                                             + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                          : VL_SHIFTRS_III(32,32,5, vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1, 
                                                           (0x1fU 
                                                            & vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)))
                                      : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                          ? (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                             >> (0x1fU 
                                                 & vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2))
                                          : (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                             << (0x1fU 
                                                 & vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)))))
                         : ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                             ? ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                 ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        & vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                     : (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        | vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2))
                                 : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        ^ vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                     : ((vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                         < vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                         ? 1U : 0U)))
                             : ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                 ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                     ? (VL_LTS_III(1,32,32, vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1, vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                         ? 1U : 0U)
                                     : (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        - vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2))
                                 : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                     : (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)))))
                     : ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                         ? ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                             ? ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                 ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                     : (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2))
                                 : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                     : (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)))
                             : ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                 ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                     : (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2))
                                 : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                     : ((0xfffffffeU 
                                         & vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__Vfuncout) 
                                        | ((vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                            >= vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                            ? 1U : 0U)))))
                         : ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                             ? ((0xfffffffeU & vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__Vfuncout) 
                                | (1U & ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                          ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                              ? ((vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                                  < vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                                  ? 1U
                                                  : 0U)
                                              : (VL_GTES_III(1,32,32, vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1, vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                                  ? 1U
                                                  : 0U))
                                          : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                              ? (VL_LTS_III(1,32,32, vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1, vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                                  ? 1U
                                                  : 0U)
                                              : ((vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                                  != vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                                  ? 1U
                                                  : 0U)))))
                             : ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                 ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                     ? ((0xfffffffeU 
                                         & vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__Vfuncout) 
                                        | ((vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                            == vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                            ? 1U : 0U))
                                     : ((IData)(4U) 
                                        + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__PC))
                                 : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                     ? ((IData)(4U) 
                                        + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__PC)
                                     : vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2))))));
    vlTOPp->top__DOT__resultE1 = vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__Vfuncout;
    vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__PC 
        = (0x8000U | ((IData)(vlTOPp->top__DOT__pcE2) 
                      << 2U));
    vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code 
        = vlTOPp->top__DOT__alu_codeE2;
    vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2 
        = ((IData)(vlTOPp->top__DOT__alu_srcE2) ? vlTOPp->top__DOT__immE2
            : vlTOPp->top__DOT__reg_data2E2);
    vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
        = vlTOPp->top__DOT__reg_data1E2;
    vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__Vfuncout 
        = ((0x20U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
            ? 0U : ((0x10U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                     ? ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                         ? ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                             ? 0U : ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                      ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                          ? (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__PC 
                                             + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                          : VL_SHIFTRS_III(32,32,5, vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1, 
                                                           (0x1fU 
                                                            & vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)))
                                      : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                          ? (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                             >> (0x1fU 
                                                 & vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2))
                                          : (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                             << (0x1fU 
                                                 & vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)))))
                         : ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                             ? ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                 ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        & vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                     : (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        | vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2))
                                 : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        ^ vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                     : ((vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                         < vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                         ? 1U : 0U)))
                             : ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                 ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                     ? (VL_LTS_III(1,32,32, vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1, vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                         ? 1U : 0U)
                                     : (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        - vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2))
                                 : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                     : (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)))))
                     : ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                         ? ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                             ? ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                 ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                     : (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2))
                                 : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                     : (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)))
                             : ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                 ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                     : (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2))
                                 : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                     : ((0xfffffffeU 
                                         & vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__Vfuncout) 
                                        | ((vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                            >= vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                            ? 1U : 0U)))))
                         : ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                             ? ((0xfffffffeU & vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__Vfuncout) 
                                | (1U & ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                          ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                              ? ((vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                                  < vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                                  ? 1U
                                                  : 0U)
                                              : (VL_GTES_III(1,32,32, vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1, vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                                  ? 1U
                                                  : 0U))
                                          : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                              ? (VL_LTS_III(1,32,32, vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1, vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                                  ? 1U
                                                  : 0U)
                                              : ((vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                                  != vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                                  ? 1U
                                                  : 0U)))))
                             : ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                 ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                     ? ((0xfffffffeU 
                                         & vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__Vfuncout) 
                                        | ((vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                            == vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                            ? 1U : 0U))
                                     : ((IData)(4U) 
                                        + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__PC))
                                 : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                     ? ((IData)(4U) 
                                        + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__PC)
                                     : vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2))))));
    vlTOPp->top__DOT__resultE2 = vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__Vfuncout;
    vlTOPp->top__DOT__e_calcpc__DOT__reg_data1 = ((2U 
                                                   & (IData)(vlTOPp->top__DOT__branch_numberE))
                                                   ? vlTOPp->top__DOT__reg_data1E2
                                                   : vlTOPp->top__DOT__reg_data1E1);
    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct7 
        = (1U & (vlTOPp->top__DOT__instD2 >> 0x1eU));
    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3 
        = (7U & (vlTOPp->top__DOT__instD2 >> 0xcU));
    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode 
        = (0x7fU & vlTOPp->top__DOT__instD2);
    if ((0x40U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
        if ((0x20U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
            if ((0x10U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
            } else {
                if ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout 
                        = ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))
                            ? ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))
                                ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))
                                    ? 1U : 0x3fU) : 0x3fU)
                            : 0x3fU);
                } else {
                    if ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout 
                            = ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))
                                ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))
                                    ? 2U : 0x3fU) : 0x3fU);
                    } else {
                        if ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                            if ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                                if ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 3U;
                                } else {
                                    if ((1U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 4U;
                                    } else {
                                        if ((4U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 5U;
                                        } else {
                                            if ((5U 
                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 6U;
                                            } else {
                                                if (
                                                    (6U 
                                                     == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 7U;
                                                } else {
                                                    if (
                                                        (7U 
                                                         == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 8U;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                            }
                        } else {
                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                        }
                    }
                }
            }
        } else {
            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
        }
    } else {
        if ((0x20U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
            if ((0x10U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                if ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                } else {
                    if ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout 
                            = ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))
                                ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))
                                    ? 0U : 0x3fU) : 0x3fU);
                    } else {
                        if ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                            if ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                                if ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout 
                                        = ((IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct7)
                                            ? 0x12U
                                            : 0x11U);
                                } else {
                                    if ((7U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x17U;
                                    } else {
                                        if ((6U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x16U;
                                        } else {
                                            if ((4U 
                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x15U;
                                            } else {
                                                if (
                                                    (1U 
                                                     == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x18U;
                                                } else {
                                                    if (
                                                        (5U 
                                                         == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout 
                                                            = 
                                                            ((IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct7)
                                                              ? 0x19U
                                                              : 0x1aU);
                                                    } else {
                                                        if (
                                                            (2U 
                                                             == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x13U;
                                                        } else {
                                                            if (
                                                                (3U 
                                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x14U;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                            }
                        } else {
                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                        }
                    }
                }
            } else {
                if ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                } else {
                    if ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                    } else {
                        if ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                            if ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                                if ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0xeU;
                                } else {
                                    if ((1U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0xfU;
                                    } else {
                                        if ((2U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x10U;
                                        }
                                    }
                                }
                            } else {
                                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                            }
                        } else {
                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                        }
                    }
                }
            }
        } else {
            if ((0x10U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                if ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                } else {
                    if ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout 
                            = ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))
                                ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))
                                    ? 0x1bU : 0x3fU)
                                : 0x3fU);
                    } else {
                        if ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                            if ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                                if ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x11U;
                                } else {
                                    if ((7U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x17U;
                                    } else {
                                        if ((6U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x16U;
                                        } else {
                                            if ((4U 
                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x15U;
                                            } else {
                                                if (
                                                    (1U 
                                                     == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x18U;
                                                } else {
                                                    if (
                                                        (5U 
                                                         == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout 
                                                            = 
                                                            ((IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct7)
                                                              ? 0x1aU
                                                              : 0x19U);
                                                    } else {
                                                        if (
                                                            (2U 
                                                             == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x13U;
                                                        } else {
                                                            if (
                                                                (3U 
                                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x14U;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                            }
                        } else {
                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                        }
                    }
                }
            } else {
                if ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                } else {
                    if ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                    } else {
                        if ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                            if ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                                if ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 9U;
                                } else {
                                    if ((1U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0xaU;
                                    } else {
                                        if ((2U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0xbU;
                                        } else {
                                            if ((4U 
                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0xcU;
                                            } else {
                                                if (
                                                    (5U 
                                                     == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0xdU;
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                            }
                        } else {
                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->top__DOT__alu_codeD2 = vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout;
    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
        = vlTOPp->top__DOT__instD2;
    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__Vfuncout 
        = ((0x40U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
            ? ((0x20U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                ? ((0x10U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                    ? 0U : ((8U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                             ? ((4U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                 ? ((2U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                     ? ((1U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                         ? ((0xfff00000U 
                                             & (VL_NEGATE_I((IData)(
                                                                    (1U 
                                                                     & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                                        >> 0x1fU)))) 
                                                << 0x14U)) 
                                            | ((0xff000U 
                                                & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst) 
                                               | ((0x800U 
                                                   & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                      >> 9U)) 
                                                  | (0x7feU 
                                                     & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                        >> 0x14U)))))
                                         : 0U) : 0U)
                                 : 0U) : ((4U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                           ? ((2U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                               ? ((1U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                                   ? 
                                                  ((0xfffff000U 
                                                    & (VL_NEGATE_I((IData)(
                                                                           (1U 
                                                                            & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                                               >> 0x1fU)))) 
                                                       << 0xcU)) 
                                                   | (0xfffU 
                                                      & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                         >> 0x14U)))
                                                   : 0U)
                                               : 0U)
                                           : ((2U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                               ? ((1U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                                   ? 
                                                  ((0xfffff000U 
                                                    & (VL_NEGATE_I((IData)(
                                                                           (1U 
                                                                            & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                                               >> 0x1fU)))) 
                                                       << 0xcU)) 
                                                   | ((0x800U 
                                                       & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                          << 4U)) 
                                                      | ((0x7e0U 
                                                          & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                             >> 0x14U)) 
                                                         | (0x1eU 
                                                            & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                               >> 7U)))))
                                                   : 0U)
                                               : 0U))))
                : 0U) : ((0x20U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                          ? ((0x10U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                              ? ((8U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                  ? 0U : ((4U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                           ? ((2U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                               ? ((1U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                                   ? 
                                                  (0xfffff000U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                                   : 0U)
                                               : 0U)
                                           : 0U)) : 
                             ((8U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                               ? 0U : ((4U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                        ? 0U : ((2U 
                                                 & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                                 ? 
                                                ((1U 
                                                  & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                                  ? 
                                                 ((0xfffff000U 
                                                   & (VL_NEGATE_I((IData)(
                                                                          (1U 
                                                                           & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                                              >> 0x1fU)))) 
                                                      << 0xcU)) 
                                                  | ((0xfe0U 
                                                      & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                         >> 0x14U)) 
                                                     | (0x1fU 
                                                        & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                           >> 7U))))
                                                  : 0U)
                                                 : 0U))))
                          : ((0x10U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                              ? ((8U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                  ? 0U : ((4U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                           ? ((2U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                               ? ((1U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                                   ? 
                                                  (0xfffff000U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                                   : 0U)
                                               : 0U)
                                           : ((2U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                               ? ((1U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                                   ? 
                                                  ((0xfffff000U 
                                                    & (VL_NEGATE_I((IData)(
                                                                           (1U 
                                                                            & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                                               >> 0x1fU)))) 
                                                       << 0xcU)) 
                                                   | (0xfffU 
                                                      & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                         >> 0x14U)))
                                                   : 0U)
                                               : 0U)))
                              : ((8U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                  ? 0U : ((4U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                           ? 0U : (
                                                   (2U 
                                                    & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                                    ? 
                                                   ((1U 
                                                     & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                                     ? 
                                                    ((0xfffff000U 
                                                      & (VL_NEGATE_I((IData)(
                                                                             (1U 
                                                                              & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                                                >> 0x1fU)))) 
                                                         << 0xcU)) 
                                                     | (0xfffU 
                                                        & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                           >> 0x14U)))
                                                     : 0U)
                                                    : 0U))))));
    vlTOPp->top__DOT__immD2 = vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__Vfuncout;
    vlTOPp->top__DOT__jump_codeD2 = ((0x63U == (0x7fU 
                                                & vlTOPp->top__DOT__instD2))
                                      ? 1U : ((0x6fU 
                                               == (0x7fU 
                                                   & vlTOPp->top__DOT__instD2))
                                               ? 2U
                                               : ((0x67U 
                                                   == 
                                                   (0x7fU 
                                                    & vlTOPp->top__DOT__instD2))
                                                   ? 3U
                                                   : 0U)));
    vlTOPp->top__DOT__source2D2 = ((0U == (0x1fU & 
                                           (vlTOPp->top__DOT__instD2 
                                            >> 0x14U)))
                                    ? 0U : (vlTOPp->top__DOT__regfile__DOT__reg_ram__DOT__mem1
                                            [(0x1fU 
                                              & (vlTOPp->top__DOT__instD2 
                                                 >> 0x14U))] 
                                            ^ vlTOPp->top__DOT__regfile__DOT__reg_ram__DOT__mem2
                                            [(0x1fU 
                                              & (vlTOPp->top__DOT__instD2 
                                                 >> 0x14U))]));
    vlTOPp->top__DOT__source1D2 = ((0U == (0x1fU & 
                                           (vlTOPp->top__DOT__instD2 
                                            >> 0xfU)))
                                    ? 0U : (vlTOPp->top__DOT__regfile__DOT__reg_ram__DOT__mem1
                                            [(0x1fU 
                                              & (vlTOPp->top__DOT__instD2 
                                                 >> 0xfU))] 
                                            ^ vlTOPp->top__DOT__regfile__DOT__reg_ram__DOT__mem2
                                            [(0x1fU 
                                              & (vlTOPp->top__DOT__instD2 
                                                 >> 0xfU))]));
    vlTOPp->top__DOT__stall = (((((((((0x1fU & (vlTOPp->top__DOT__instD1 
                                                >> 0xfU)) 
                                      == (IData)(vlTOPp->top__DOT__rdE1)) 
                                     | ((0x1fU & (vlTOPp->top__DOT__instD1 
                                                  >> 0x14U)) 
                                        == (IData)(vlTOPp->top__DOT__rdE1))) 
                                    & (0U != (IData)(vlTOPp->top__DOT__rdE1))) 
                                   & (IData)(vlTOPp->top__DOT__reg_writeE1)) 
                                  & (1U <= (IData)(vlTOPp->top__DOT__mem_loadE1))) 
                                 | ((((((0x1fU & (vlTOPp->top__DOT__instD1 
                                                  >> 0xfU)) 
                                        == (IData)(vlTOPp->top__DOT__rdE2)) 
                                       | ((0x1fU & 
                                           (vlTOPp->top__DOT__instD1 
                                            >> 0x14U)) 
                                          == (IData)(vlTOPp->top__DOT__rdE2))) 
                                      & (0U != (IData)(vlTOPp->top__DOT__rdE2))) 
                                     & (IData)(vlTOPp->top__DOT__reg_writeE2)) 
                                    & (1U <= (IData)(vlTOPp->top__DOT__mem_loadE2)))) 
                                | ((((((0x1fU & (vlTOPp->top__DOT__instD2 
                                                 >> 0xfU)) 
                                       == (IData)(vlTOPp->top__DOT__rdE1)) 
                                      | ((0x1fU & (vlTOPp->top__DOT__instD2 
                                                   >> 0x14U)) 
                                         == (IData)(vlTOPp->top__DOT__rdE1))) 
                                     & (0U != (IData)(vlTOPp->top__DOT__rdE1))) 
                                    & (IData)(vlTOPp->top__DOT__reg_writeE1)) 
                                   & (1U <= (IData)(vlTOPp->top__DOT__mem_loadE1)))) 
                               | ((((((0x1fU & (vlTOPp->top__DOT__instD2 
                                                >> 0xfU)) 
                                      == (IData)(vlTOPp->top__DOT__rdE2)) 
                                     | ((0x1fU & (vlTOPp->top__DOT__instD2 
                                                  >> 0x14U)) 
                                        == (IData)(vlTOPp->top__DOT__rdE2))) 
                                    & (0U != (IData)(vlTOPp->top__DOT__rdE2))) 
                                   & (IData)(vlTOPp->top__DOT__reg_writeE2)) 
                                  & (1U <= (IData)(vlTOPp->top__DOT__mem_loadE2))));
    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct7 
        = (1U & (vlTOPp->top__DOT__instD1 >> 0x1eU));
    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3 
        = (7U & (vlTOPp->top__DOT__instD1 >> 0xcU));
    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode 
        = (0x7fU & vlTOPp->top__DOT__instD1);
    if ((0x40U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
        if ((0x20U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
            if ((0x10U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
            } else {
                if ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout 
                        = ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))
                            ? ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))
                                ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))
                                    ? 1U : 0x3fU) : 0x3fU)
                            : 0x3fU);
                } else {
                    if ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout 
                            = ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))
                                ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))
                                    ? 2U : 0x3fU) : 0x3fU);
                    } else {
                        if ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                            if ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                                if ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 3U;
                                } else {
                                    if ((1U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 4U;
                                    } else {
                                        if ((4U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 5U;
                                        } else {
                                            if ((5U 
                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 6U;
                                            } else {
                                                if (
                                                    (6U 
                                                     == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 7U;
                                                } else {
                                                    if (
                                                        (7U 
                                                         == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 8U;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                            }
                        } else {
                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                        }
                    }
                }
            }
        } else {
            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
        }
    } else {
        if ((0x20U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
            if ((0x10U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                if ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                } else {
                    if ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout 
                            = ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))
                                ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))
                                    ? 0U : 0x3fU) : 0x3fU);
                    } else {
                        if ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                            if ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                                if ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout 
                                        = ((IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct7)
                                            ? 0x12U
                                            : 0x11U);
                                } else {
                                    if ((7U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x17U;
                                    } else {
                                        if ((6U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x16U;
                                        } else {
                                            if ((4U 
                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x15U;
                                            } else {
                                                if (
                                                    (1U 
                                                     == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x18U;
                                                } else {
                                                    if (
                                                        (5U 
                                                         == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout 
                                                            = 
                                                            ((IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct7)
                                                              ? 0x19U
                                                              : 0x1aU);
                                                    } else {
                                                        if (
                                                            (2U 
                                                             == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x13U;
                                                        } else {
                                                            if (
                                                                (3U 
                                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x14U;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                            }
                        } else {
                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                        }
                    }
                }
            } else {
                if ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                } else {
                    if ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                    } else {
                        if ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                            if ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                                if ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0xeU;
                                } else {
                                    if ((1U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0xfU;
                                    } else {
                                        if ((2U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x10U;
                                        }
                                    }
                                }
                            } else {
                                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                            }
                        } else {
                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                        }
                    }
                }
            }
        } else {
            if ((0x10U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                if ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                } else {
                    if ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout 
                            = ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))
                                ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))
                                    ? 0x1bU : 0x3fU)
                                : 0x3fU);
                    } else {
                        if ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                            if ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                                if ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x11U;
                                } else {
                                    if ((7U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x17U;
                                    } else {
                                        if ((6U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x16U;
                                        } else {
                                            if ((4U 
                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x15U;
                                            } else {
                                                if (
                                                    (1U 
                                                     == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x18U;
                                                } else {
                                                    if (
                                                        (5U 
                                                         == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout 
                                                            = 
                                                            ((IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct7)
                                                              ? 0x1aU
                                                              : 0x19U);
                                                    } else {
                                                        if (
                                                            (2U 
                                                             == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x13U;
                                                        } else {
                                                            if (
                                                                (3U 
                                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x14U;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                            }
                        } else {
                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                        }
                    }
                }
            } else {
                if ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                } else {
                    if ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                    } else {
                        if ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                            if ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                                if ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 9U;
                                } else {
                                    if ((1U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0xaU;
                                    } else {
                                        if ((2U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0xbU;
                                        } else {
                                            if ((4U 
                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0xcU;
                                            } else {
                                                if (
                                                    (5U 
                                                     == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0xdU;
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                            }
                        } else {
                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->top__DOT__alu_codeD1 = vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout;
    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
        = vlTOPp->top__DOT__instD1;
    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__Vfuncout 
        = ((0x40U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
            ? ((0x20U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                ? ((0x10U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                    ? 0U : ((8U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                             ? ((4U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                 ? ((2U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                     ? ((1U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                         ? ((0xfff00000U 
                                             & (VL_NEGATE_I((IData)(
                                                                    (1U 
                                                                     & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                                        >> 0x1fU)))) 
                                                << 0x14U)) 
                                            | ((0xff000U 
                                                & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst) 
                                               | ((0x800U 
                                                   & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                      >> 9U)) 
                                                  | (0x7feU 
                                                     & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                        >> 0x14U)))))
                                         : 0U) : 0U)
                                 : 0U) : ((4U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                           ? ((2U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                               ? ((1U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                                   ? 
                                                  ((0xfffff000U 
                                                    & (VL_NEGATE_I((IData)(
                                                                           (1U 
                                                                            & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                                               >> 0x1fU)))) 
                                                       << 0xcU)) 
                                                   | (0xfffU 
                                                      & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                         >> 0x14U)))
                                                   : 0U)
                                               : 0U)
                                           : ((2U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                               ? ((1U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                                   ? 
                                                  ((0xfffff000U 
                                                    & (VL_NEGATE_I((IData)(
                                                                           (1U 
                                                                            & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                                               >> 0x1fU)))) 
                                                       << 0xcU)) 
                                                   | ((0x800U 
                                                       & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                          << 4U)) 
                                                      | ((0x7e0U 
                                                          & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                             >> 0x14U)) 
                                                         | (0x1eU 
                                                            & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                               >> 7U)))))
                                                   : 0U)
                                               : 0U))))
                : 0U) : ((0x20U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                          ? ((0x10U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                              ? ((8U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                  ? 0U : ((4U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                           ? ((2U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                               ? ((1U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                                   ? 
                                                  (0xfffff000U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                                   : 0U)
                                               : 0U)
                                           : 0U)) : 
                             ((8U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                               ? 0U : ((4U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                        ? 0U : ((2U 
                                                 & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                                 ? 
                                                ((1U 
                                                  & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                                  ? 
                                                 ((0xfffff000U 
                                                   & (VL_NEGATE_I((IData)(
                                                                          (1U 
                                                                           & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                                              >> 0x1fU)))) 
                                                      << 0xcU)) 
                                                  | ((0xfe0U 
                                                      & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                         >> 0x14U)) 
                                                     | (0x1fU 
                                                        & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                           >> 7U))))
                                                  : 0U)
                                                 : 0U))))
                          : ((0x10U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                              ? ((8U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                  ? 0U : ((4U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                           ? ((2U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                               ? ((1U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                                   ? 
                                                  (0xfffff000U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                                   : 0U)
                                               : 0U)
                                           : ((2U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                               ? ((1U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                                   ? 
                                                  ((0xfffff000U 
                                                    & (VL_NEGATE_I((IData)(
                                                                           (1U 
                                                                            & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                                               >> 0x1fU)))) 
                                                       << 0xcU)) 
                                                   | (0xfffU 
                                                      & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                         >> 0x14U)))
                                                   : 0U)
                                               : 0U)))
                              : ((8U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                  ? 0U : ((4U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                           ? 0U : (
                                                   (2U 
                                                    & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                                    ? 
                                                   ((1U 
                                                     & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                                     ? 
                                                    ((0xfffff000U 
                                                      & (VL_NEGATE_I((IData)(
                                                                             (1U 
                                                                              & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                                                >> 0x1fU)))) 
                                                         << 0xcU)) 
                                                     | (0xfffU 
                                                        & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                           >> 0x14U)))
                                                     : 0U)
                                                    : 0U))))));
    vlTOPp->top__DOT__immD1 = vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__Vfuncout;
    vlTOPp->top__DOT__branch_codeDj = (7U & ((2U & (IData)(vlTOPp->top__DOT__branch_numberD))
                                              ? ((0x63U 
                                                  != 
                                                  (0x7fU 
                                                   & vlTOPp->top__DOT__instD2))
                                                  ? 2U
                                                  : 
                                                 (vlTOPp->top__DOT__instD2 
                                                  >> 0xcU))
                                              : ((0x63U 
                                                  != 
                                                  (0x7fU 
                                                   & vlTOPp->top__DOT__instD1))
                                                  ? 2U
                                                  : 
                                                 (vlTOPp->top__DOT__instD1 
                                                  >> 0xcU))));
    vlTOPp->top__DOT__jump_codeD1 = ((0x63U == (0x7fU 
                                                & vlTOPp->top__DOT__instD1))
                                      ? 1U : ((0x6fU 
                                               == (0x7fU 
                                                   & vlTOPp->top__DOT__instD1))
                                               ? 2U
                                               : ((0x67U 
                                                   == 
                                                   (0x7fU 
                                                    & vlTOPp->top__DOT__instD1))
                                                   ? 3U
                                                   : 0U)));
    vlTOPp->top__DOT__source2D1 = ((0U == (0x1fU & 
                                           (vlTOPp->top__DOT__instD1 
                                            >> 0x14U)))
                                    ? 0U : (vlTOPp->top__DOT__regfile__DOT__reg_ram__DOT__mem1
                                            [(0x1fU 
                                              & (vlTOPp->top__DOT__instD1 
                                                 >> 0x14U))] 
                                            ^ vlTOPp->top__DOT__regfile__DOT__reg_ram__DOT__mem2
                                            [(0x1fU 
                                              & (vlTOPp->top__DOT__instD1 
                                                 >> 0x14U))]));
    vlTOPp->top__DOT__source1D1 = ((0U == (0x1fU & 
                                           (vlTOPp->top__DOT__instD1 
                                            >> 0xfU)))
                                    ? 0U : (vlTOPp->top__DOT__regfile__DOT__reg_ram__DOT__mem1
                                            [(0x1fU 
                                              & (vlTOPp->top__DOT__instD1 
                                                 >> 0xfU))] 
                                            ^ vlTOPp->top__DOT__regfile__DOT__reg_ram__DOT__mem2
                                            [(0x1fU 
                                              & (vlTOPp->top__DOT__instD1 
                                                 >> 0xfU))]));
    vlTOPp->top__DOT__e_calcpc__DOT__jump_pc = (0x1fffU 
                                                & ((IData)(vlTOPp->top__DOT__immEj) 
                                                   + 
                                                   ((3U 
                                                     == (IData)(vlTOPp->top__DOT__jump_codeEj))
                                                     ? 
                                                    (vlTOPp->top__DOT__e_calcpc__DOT__reg_data1 
                                                     >> 2U)
                                                     : (IData)(vlTOPp->top__DOT__pcEj))));
    vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data2 
        = ((2U & (IData)(vlTOPp->top__DOT__branch_numberE))
            ? vlTOPp->top__DOT__reg_data2E2 : vlTOPp->top__DOT__reg_data2E1);
    vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data1 
        = vlTOPp->top__DOT__e_calcpc__DOT__reg_data1;
    vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__branch_code 
        = vlTOPp->top__DOT__branch_codeEj;
    vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__Vfuncout 
        = ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__branch_code))
            ? (vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data1 
               == vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data2)
            : ((1U == (IData)(vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__branch_code))
                ? (vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data1 
                   != vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data2)
                : ((4U == (IData)(vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__branch_code))
                    ? VL_LTS_III(1,32,32, vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data1, vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data2)
                    : ((5U == (IData)(vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__branch_code))
                        ? VL_GTES_III(1,32,32, vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data1, vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data2)
                        : ((6U == (IData)(vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__branch_code))
                            ? (vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data1 
                               < vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data2)
                            : ((7U == (IData)(vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__branch_code)) 
                               & (vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data1 
                                  >= vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data2)))))));
    vlTOPp->top__DOT__e_calcpc__DOT__flag = vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__Vfuncout;
    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemStore__6__alu_code 
        = vlTOPp->top__DOT__alu_codeD2;
    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemStore__6__Vfuncout 
        = ((0xeU == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemStore__6__alu_code))
            ? 1U : ((0xfU == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemStore__6__alu_code))
                     ? 2U : ((0x10U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemStore__6__alu_code))
                              ? 3U : 0U)));
    vlTOPp->top__DOT__mem_storeD2 = vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemStore__6__Vfuncout;
    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__alu_code 
        = vlTOPp->top__DOT__alu_codeD2;
    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__Vfuncout 
        = ((0x20U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__alu_code))
            ? 0U : ((0x10U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__alu_code))
                     ? 0U : ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__alu_code))
                              ? ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__alu_code))
                                  ? ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__alu_code))
                                      ? 0U : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__alu_code))
                                               ? 5U
                                               : 4U))
                                  : ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__alu_code))
                                      ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__alu_code))
                                          ? 3U : 2U)
                                      : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__alu_code))
                                          ? 1U : 0U)))
                              : 0U)));
    vlTOPp->top__DOT__mem_loadD2 = vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__Vfuncout;
    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemStore__2__alu_code 
        = vlTOPp->top__DOT__alu_codeD1;
    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemStore__2__Vfuncout 
        = ((0xeU == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemStore__2__alu_code))
            ? 1U : ((0xfU == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemStore__2__alu_code))
                     ? 2U : ((0x10U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemStore__2__alu_code))
                              ? 3U : 0U)));
    vlTOPp->top__DOT__mem_storeD1 = vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemStore__2__Vfuncout;
    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__alu_code 
        = vlTOPp->top__DOT__alu_codeD1;
    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__Vfuncout 
        = ((0x20U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__alu_code))
            ? 0U : ((0x10U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__alu_code))
                     ? 0U : ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__alu_code))
                              ? ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__alu_code))
                                  ? ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__alu_code))
                                      ? 0U : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__alu_code))
                                               ? 5U
                                               : 4U))
                                  : ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__alu_code))
                                      ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__alu_code))
                                          ? 3U : 2U)
                                      : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__alu_code))
                                          ? 1U : 0U)))
                              : 0U)));
    vlTOPp->top__DOT__mem_loadD1 = vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__Vfuncout;
    vlTOPp->top__DOT__immDj = (0x1fffU & ((2U & (IData)(vlTOPp->top__DOT__branch_numberD))
                                           ? (vlTOPp->top__DOT__immD2 
                                              >> 2U)
                                           : (vlTOPp->top__DOT__immD1 
                                              >> 2U)));
    vlTOPp->top__DOT__cannot_calcpc = ((((((IData)(vlTOPp->top__DOT__branch_numberD) 
                                           & (3U == (IData)(vlTOPp->top__DOT__jump_codeD1))) 
                                          & (((0x1fU 
                                               & (vlTOPp->top__DOT__instD1 
                                                  >> 0xfU)) 
                                              == (IData)(vlTOPp->top__DOT__rdE1)) 
                                             | (((0x1fU 
                                                  & (vlTOPp->top__DOT__instD1 
                                                     >> 0xfU)) 
                                                 == (IData)(vlTOPp->top__DOT__rdM1)) 
                                                & (1U 
                                                   <= (IData)(vlTOPp->top__DOT__mem_loadM1))))) 
                                         | ((((IData)(vlTOPp->top__DOT__branch_numberD) 
                                              >> 1U) 
                                             & (3U 
                                                == (IData)(vlTOPp->top__DOT__jump_codeD2))) 
                                            & (((0x1fU 
                                                 & (vlTOPp->top__DOT__instD2 
                                                    >> 0xfU)) 
                                                == (IData)(vlTOPp->top__DOT__rdE2)) 
                                               | (((0x1fU 
                                                    & (vlTOPp->top__DOT__instD2 
                                                       >> 0xfU)) 
                                                   == (IData)(vlTOPp->top__DOT__rdM2)) 
                                                  & (1U 
                                                     <= (IData)(vlTOPp->top__DOT__mem_loadM2)))))) 
                                        | (((IData)(vlTOPp->top__DOT__branch_numberD) 
                                            & (1U == (IData)(vlTOPp->top__DOT__jump_codeD1))) 
                                           & ((((0x1fU 
                                                 & (vlTOPp->top__DOT__instD1 
                                                    >> 0xfU)) 
                                                == (IData)(vlTOPp->top__DOT__rdE1)) 
                                               | ((0x1fU 
                                                   & (vlTOPp->top__DOT__instD1 
                                                      >> 0x14U)) 
                                                  == (IData)(vlTOPp->top__DOT__rdE1))) 
                                              | ((((0x1fU 
                                                    & (vlTOPp->top__DOT__instD1 
                                                       >> 0xfU)) 
                                                   == (IData)(vlTOPp->top__DOT__rdM1)) 
                                                  | ((0x1fU 
                                                      & (vlTOPp->top__DOT__instD1 
                                                         >> 0x14U)) 
                                                     == (IData)(vlTOPp->top__DOT__rdM1))) 
                                                 & (1U 
                                                    <= (IData)(vlTOPp->top__DOT__mem_loadM1)))))) 
                                       | ((((IData)(vlTOPp->top__DOT__branch_numberD) 
                                            >> 1U) 
                                           & (1U == (IData)(vlTOPp->top__DOT__jump_codeD2))) 
                                          & ((((0x1fU 
                                                & (vlTOPp->top__DOT__instD2 
                                                   >> 0xfU)) 
                                               == (IData)(vlTOPp->top__DOT__rdE2)) 
                                              | ((0x1fU 
                                                  & (vlTOPp->top__DOT__instD2 
                                                     >> 0x14U)) 
                                                 == (IData)(vlTOPp->top__DOT__rdE2))) 
                                             | ((((0x1fU 
                                                   & (vlTOPp->top__DOT__instD2 
                                                      >> 0xfU)) 
                                                  == (IData)(vlTOPp->top__DOT__rdM2)) 
                                                 | ((0x1fU 
                                                     & (vlTOPp->top__DOT__instD2 
                                                        >> 0x14U)) 
                                                    == (IData)(vlTOPp->top__DOT__rdM2))) 
                                                & (1U 
                                                   <= (IData)(vlTOPp->top__DOT__mem_loadM2))))));
    vlTOPp->top__DOT__jump_codeDj = ((2U & (IData)(vlTOPp->top__DOT__branch_numberD))
                                      ? (IData)(vlTOPp->top__DOT__jump_codeD2)
                                      : (IData)(vlTOPp->top__DOT__jump_codeD1));
    vlTOPp->top__DOT__reg_data2Dj = ((2U & (IData)(vlTOPp->top__DOT__branch_numberD))
                                      ? ((((((0x1fU 
                                              & (vlTOPp->top__DOT__instD2 
                                                 >> 0x14U)) 
                                             == (IData)(vlTOPp->top__DOT__rdM2)) 
                                            & (0U != (IData)(vlTOPp->top__DOT__rdM2))) 
                                           & (0U == (IData)(vlTOPp->top__DOT__mem_loadM2))) 
                                          & (IData)(vlTOPp->top__DOT__reg_writeM2))
                                          ? vlTOPp->top__DOT__resultM2
                                          : vlTOPp->top__DOT__source2D2)
                                      : ((((((0x1fU 
                                              & (vlTOPp->top__DOT__instD1 
                                                 >> 0x14U)) 
                                             == (IData)(vlTOPp->top__DOT__rdM1)) 
                                            & (0U != (IData)(vlTOPp->top__DOT__rdM1))) 
                                           & (0U == (IData)(vlTOPp->top__DOT__mem_loadM1))) 
                                          & (IData)(vlTOPp->top__DOT__reg_writeM1))
                                          ? vlTOPp->top__DOT__resultM1
                                          : vlTOPp->top__DOT__source2D1));
    vlTOPp->top__DOT__reg_data1Dj = ((2U & (IData)(vlTOPp->top__DOT__branch_numberD))
                                      ? ((((((0x1fU 
                                              & (vlTOPp->top__DOT__instD2 
                                                 >> 0xfU)) 
                                             == (IData)(vlTOPp->top__DOT__rdM2)) 
                                            & (0U != (IData)(vlTOPp->top__DOT__rdM2))) 
                                           & (0U == (IData)(vlTOPp->top__DOT__mem_loadM2))) 
                                          & (IData)(vlTOPp->top__DOT__reg_writeM2))
                                          ? vlTOPp->top__DOT__resultM2
                                          : vlTOPp->top__DOT__source1D2)
                                      : ((((((0x1fU 
                                              & (vlTOPp->top__DOT__instD1 
                                                 >> 0xfU)) 
                                             == (IData)(vlTOPp->top__DOT__rdM1)) 
                                            & (0U != (IData)(vlTOPp->top__DOT__rdM1))) 
                                           & (0U == (IData)(vlTOPp->top__DOT__mem_loadM1))) 
                                          & (IData)(vlTOPp->top__DOT__reg_writeM1))
                                          ? vlTOPp->top__DOT__resultM1
                                          : vlTOPp->top__DOT__source1D1));
    vlTOPp->top__DOT__true_pcE = (0x1fffU & ((1U & 
                                              ((IData)(vlTOPp->top__DOT__e_calcpc__DOT__flag) 
                                               | ((IData)(vlTOPp->top__DOT__jump_codeEj) 
                                                  >> 1U)))
                                              ? (IData)(vlTOPp->top__DOT__e_calcpc__DOT__jump_pc)
                                              : ((IData)(1U) 
                                                 + (IData)(vlTOPp->top__DOT__pcEj))));
    vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data2 
        = vlTOPp->top__DOT__reg_data2Dj;
    vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data1 
        = vlTOPp->top__DOT__reg_data1Dj;
    vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__branch_code 
        = vlTOPp->top__DOT__branch_codeDj;
    vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__Vfuncout 
        = ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__branch_code))
            ? (vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data1 
               == vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data2)
            : ((1U == (IData)(vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__branch_code))
                ? (vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data1 
                   != vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data2)
                : ((4U == (IData)(vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__branch_code))
                    ? VL_LTS_III(1,32,32, vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data1, vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data2)
                    : ((5U == (IData)(vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__branch_code))
                        ? VL_GTES_III(1,32,32, vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data1, vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data2)
                        : ((6U == (IData)(vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__branch_code))
                            ? (vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data1 
                               < vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data2)
                            : ((7U == (IData)(vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__branch_code)) 
                               & (vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data1 
                                  >= vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data2)))))));
    vlTOPp->top__DOT__d_calcpc__DOT__flag = vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__Vfuncout;
    vlTOPp->top__DOT__fail_predictE = (((IData)(vlTOPp->top__DOT__true_pcE) 
                                        != (IData)(vlTOPp->top__DOT__pcD1)) 
                                       & (IData)(vlTOPp->top__DOT__jump_codeEj));
    vlTOPp->top__DOT__true_pcD = (0x1fffU & ((1U & 
                                              ((IData)(vlTOPp->top__DOT__d_calcpc__DOT__flag) 
                                               | ((IData)(vlTOPp->top__DOT__jump_codeDj) 
                                                  >> 1U)))
                                              ? ((IData)(vlTOPp->top__DOT__immDj) 
                                                 + 
                                                 ((3U 
                                                   == (IData)(vlTOPp->top__DOT__jump_codeDj))
                                                   ? 
                                                  (vlTOPp->top__DOT__reg_data1Dj 
                                                   >> 2U)
                                                   : (IData)(vlTOPp->top__DOT__pcDj)))
                                              : ((IData)(1U) 
                                                 + (IData)(vlTOPp->top__DOT__pcDj))));
    vlTOPp->top__DOT__fail_predictD = ((((IData)(vlTOPp->top__DOT__true_pcD) 
                                         != (IData)(vlTOPp->top__DOT__check__DOT__pc1)) 
                                        & (1U <= (IData)(vlTOPp->top__DOT__jump_codeDj))) 
                                       & (~ (IData)(vlTOPp->top__DOT__cannot_calcpc)));
    vlTOPp->top__DOT__fail_predict = ((IData)(vlTOPp->top__DOT__fail_predictE) 
                                      | (IData)(vlTOPp->top__DOT__fail_predictD));
}

VL_INLINE_OPT void Vtop::_sequent__TOP__3(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_sequent__TOP__3\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->top__DOT__instF2 = vlTOPp->top__DOT__inst_rom__DOT__inst_rom_block__DOT__mem
        [(0x1fffU & ((IData)(1U) + (IData)(vlTOPp->top__DOT__inst_rom__DOT__pc)))];
    vlTOPp->top__DOT__instF1 = vlTOPp->top__DOT__inst_rom__DOT__inst_rom_block__DOT__mem
        [vlTOPp->top__DOT__inst_rom__DOT__pc];
    vlTOPp->top__DOT__predict__DOT__r_data2 = vlTOPp->top__DOT__predict__DOT__cache__DOT__mem
        [(0x7ffU & ((IData)(1U) + (IData)(vlTOPp->top__DOT__inst_rom__DOT__pc)))];
    vlTOPp->top__DOT__predict__DOT__r_data1 = vlTOPp->top__DOT__predict__DOT__cache__DOT__mem
        [(0x7ffU & (IData)(vlTOPp->top__DOT__inst_rom__DOT__pc))];
}

void Vtop::_initial__TOP__4(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_initial__TOP__4\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    WData/*255:0*/ __Vtemp12[8];
    WData/*95:0*/ __Vtemp13[3];
    WData/*95:0*/ __Vtemp14[3];
    WData/*255:0*/ __Vtemp15[8];
    WData/*255:0*/ __Vtemp16[8];
    // Body
    __Vtemp12[0U] = 0x2e686578U;
    __Vtemp12[1U] = 0x64617461U;
    __Vtemp12[2U] = 0x2f30332fU;
    __Vtemp12[3U] = 0x56333249U;
    __Vtemp12[4U] = 0x6a6f2f52U;
    __Vtemp12[5U] = 0x2f64656eU;
    __Vtemp12[6U] = 0x686f6d65U;
    __Vtemp12[7U] = 0x2fU;
    VL_READMEM_N(true, 32, 16384, 0, VL_CVT_PACK_STR_NW(8, __Vtemp12)
                 , vlTOPp->top__DOT__data_ram__DOT__data_ram_block__DOT__mem
                 , 0, ~VL_ULL(0));
    __Vtemp13[0U] = 0x2e686578U;
    __Vtemp13[1U] = 0x5f726567U;
    __Vtemp13[2U] = 0x696e6974U;
    VL_READMEM_N(true, 32, 32, 0, VL_CVT_PACK_STR_NW(3, __Vtemp13)
                 , vlTOPp->top__DOT__regfile__DOT__reg_ram__DOT__mem1
                 , 0, ~VL_ULL(0));
    __Vtemp14[0U] = 0x2e686578U;
    __Vtemp14[1U] = 0x5f726567U;
    __Vtemp14[2U] = 0x696e6974U;
    VL_READMEM_N(true, 32, 32, 0, VL_CVT_PACK_STR_NW(3, __Vtemp14)
                 , vlTOPp->top__DOT__regfile__DOT__reg_ram__DOT__mem2
                 , 0, ~VL_ULL(0));
    __Vtemp15[0U] = 0x2e686578U;
    __Vtemp15[1U] = 0x636f6465U;
    __Vtemp15[2U] = 0x2f30332fU;
    __Vtemp15[3U] = 0x56333249U;
    __Vtemp15[4U] = 0x6a6f2f52U;
    __Vtemp15[5U] = 0x2f64656eU;
    __Vtemp15[6U] = 0x686f6d65U;
    __Vtemp15[7U] = 0x2fU;
    VL_READMEM_N(true, 32, 8192, 0, VL_CVT_PACK_STR_NW(8, __Vtemp15)
                 , vlTOPp->top__DOT__inst_rom__DOT__inst_rom_block__DOT__mem
                 , 0, ~VL_ULL(0));
    __Vtemp16[0U] = 0x2e686578U;
    __Vtemp16[1U] = 0x61636865U;
    __Vtemp16[2U] = 0x30322f63U;
    __Vtemp16[3U] = 0x3332492fU;
    __Vtemp16[4U] = 0x6f2f5256U;
    __Vtemp16[5U] = 0x64656e6aU;
    __Vtemp16[6U] = 0x6f6d652fU;
    __Vtemp16[7U] = 0x2f68U;
    VL_READMEM_N(false, 18, 2048, 0, VL_CVT_PACK_STR_NW(8, __Vtemp16)
                 , vlTOPp->top__DOT__predict__DOT__cache__DOT__mem
                 , 0, ~VL_ULL(0));
}

void Vtop::_settle__TOP__5(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_settle__TOP__5\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->uart_tx = vlTOPp->top__DOT__uart_OUT_data;
    vlTOPp->top__DOT__uart0__DOT__uart_busy = (0U != 
                                               (7U 
                                                & ((IData)(vlTOPp->top__DOT__uart0__DOT__bitcount) 
                                                   >> 1U)));
    vlTOPp->top__DOT__uart0__DOT__sending = (0U != (IData)(vlTOPp->top__DOT__uart0__DOT__bitcount));
    vlTOPp->top__DOT__check__DOT__pc2 = ((IData)(vlTOPp->top__DOT__check__DOT__was_depend)
                                          ? (IData)(vlTOPp->top__DOT__pc1_in)
                                          : (IData)(vlTOPp->top__DOT__pc2_in));
    vlTOPp->top__DOT__check__DOT__state2 = ((IData)(vlTOPp->top__DOT__check__DOT__was_depend)
                                             ? (IData)(vlTOPp->top__DOT__state1_in)
                                             : (IData)(vlTOPp->top__DOT__state2_in));
    vlTOPp->top__DOT__data_ram__DOT__r_data1_true = 
        ((((IData)(vlTOPp->top__DOT__data_ram__DOT__resultM_before) 
           == (0x3fffU & (vlTOPp->top__DOT__resultM1 
                          >> 2U))) & (1U <= (IData)(vlTOPp->top__DOT__data_ram__DOT__mem_store_before)))
          ? vlTOPp->top__DOT__data_ram__DOT__store_data_before
          : vlTOPp->top__DOT__data_ram__DOT__r_data1);
    vlTOPp->top__DOT__data_ram__DOT__r_data2_true = 
        ((((IData)(vlTOPp->top__DOT__data_ram__DOT__resultM_before) 
           == (0x3fffU & (vlTOPp->top__DOT__resultM2 
                          >> 2U))) & (1U <= (IData)(vlTOPp->top__DOT__data_ram__DOT__mem_store_before)))
          ? vlTOPp->top__DOT__data_ram__DOT__store_data_before
          : vlTOPp->top__DOT__data_ram__DOT__r_data2);
    vlTOPp->top__DOT__check__DOT__inst2 = ((IData)(vlTOPp->top__DOT__check__DOT__was_depend)
                                            ? vlTOPp->top__DOT__inst1_in
                                            : vlTOPp->top__DOT__inst2_in);
    vlTOPp->top__DOT__check__DOT__pc1 = ((IData)(vlTOPp->top__DOT__check__DOT__was_depend)
                                          ? (IData)(vlTOPp->top__DOT__check__DOT__pc2_buffer)
                                          : (IData)(vlTOPp->top__DOT__pc1_in));
    vlTOPp->top__DOT__check__DOT__inst1 = ((IData)(vlTOPp->top__DOT__check__DOT__was_depend)
                                            ? vlTOPp->top__DOT__check__DOT__inst2_buffer
                                            : vlTOPp->top__DOT__inst1_in);
    vlTOPp->top__DOT__uart0__DOT__dNxt = (0x1fffffffU 
                                          & (vlTOPp->top__DOT__uart0__DOT__d 
                                             + ((0x10000000U 
                                                 & vlTOPp->top__DOT__uart0__DOT__d)
                                                 ? 0x1c200U
                                                 : 0xfb3d0e00U)));
    vlTOPp->top__DOT__data_ram__DOT__resultM = ((1U 
                                                 <= (IData)(vlTOPp->top__DOT__mem_storeM1))
                                                 ? vlTOPp->top__DOT__resultM1
                                                 : vlTOPp->top__DOT__resultM2);
    vlTOPp->top__DOT__uart_we = (((0xf6fff070U == vlTOPp->top__DOT__resultM1) 
                                  & (1U <= (IData)(vlTOPp->top__DOT__mem_storeM1))) 
                                 | ((0xf6fff070U == vlTOPp->top__DOT__resultM2) 
                                    & (1U <= (IData)(vlTOPp->top__DOT__mem_storeM2))));
    vlTOPp->top__DOT__data_ram__DOT__mem_store = ((IData)(vlTOPp->top__DOT__mem_storeM1) 
                                                  | (IData)(vlTOPp->top__DOT__mem_storeM2));
    vlTOPp->top__DOT__data_ram__DOT__Source = ((1U 
                                                <= (IData)(vlTOPp->top__DOT__mem_storeM1))
                                                ? vlTOPp->top__DOT__reg_data2M1
                                                : vlTOPp->top__DOT__reg_data2M2);
    vlTOPp->top__DOT__data_ram__DOT__offset = (3U & 
                                               ((1U 
                                                 <= (IData)(vlTOPp->top__DOT__mem_storeM1))
                                                 ? vlTOPp->top__DOT__resultM1
                                                 : vlTOPp->top__DOT__resultM2));
    vlTOPp->top__DOT__pcDj = ((2U & (IData)(vlTOPp->top__DOT__branch_numberD))
                               ? (IData)(vlTOPp->top__DOT__pcD2)
                               : (IData)(vlTOPp->top__DOT__pcD1));
    vlTOPp->top__DOT__reg_data2E1 = ((((((IData)(vlTOPp->top__DOT__rs2E1) 
                                         == (IData)(vlTOPp->top__DOT__rdM2)) 
                                        & (0U != (IData)(vlTOPp->top__DOT__rdM2))) 
                                       & (IData)(vlTOPp->top__DOT__reg_writeM2)) 
                                      & (0U == (IData)(vlTOPp->top__DOT__mem_loadM2)))
                                      ? vlTOPp->top__DOT__resultM2
                                      : ((((((IData)(vlTOPp->top__DOT__rs2E1) 
                                             == (IData)(vlTOPp->top__DOT__rdM1)) 
                                            & (0U != (IData)(vlTOPp->top__DOT__rdM1))) 
                                           & (IData)(vlTOPp->top__DOT__reg_writeM1)) 
                                          & (0U == (IData)(vlTOPp->top__DOT__mem_loadM1)))
                                          ? vlTOPp->top__DOT__resultM1
                                          : (((((IData)(vlTOPp->top__DOT__rs2E1) 
                                                == (IData)(vlTOPp->top__DOT__rdW2)) 
                                               & (0U 
                                                  != (IData)(vlTOPp->top__DOT__rdW2))) 
                                              & (IData)(vlTOPp->top__DOT__reg_writeW2))
                                              ? vlTOPp->top__DOT__distW2
                                              : (((
                                                   ((IData)(vlTOPp->top__DOT__rs2E1) 
                                                    == (IData)(vlTOPp->top__DOT__rdW1)) 
                                                   & (0U 
                                                      != (IData)(vlTOPp->top__DOT__rdW1))) 
                                                  & (IData)(vlTOPp->top__DOT__reg_writeW1))
                                                  ? vlTOPp->top__DOT__distW1
                                                  : vlTOPp->top__DOT__source2E1))));
    vlTOPp->top__DOT__reg_data2E2 = ((((((IData)(vlTOPp->top__DOT__rs2E2) 
                                         == (IData)(vlTOPp->top__DOT__rdM2)) 
                                        & (0U != (IData)(vlTOPp->top__DOT__rdM2))) 
                                       & (IData)(vlTOPp->top__DOT__reg_writeM2)) 
                                      & (0U == (IData)(vlTOPp->top__DOT__mem_loadM2)))
                                      ? vlTOPp->top__DOT__resultM2
                                      : ((((((IData)(vlTOPp->top__DOT__rs2E2) 
                                             == (IData)(vlTOPp->top__DOT__rdM1)) 
                                            & (0U != (IData)(vlTOPp->top__DOT__rdM1))) 
                                           & (IData)(vlTOPp->top__DOT__reg_writeM1)) 
                                          & (0U == (IData)(vlTOPp->top__DOT__mem_loadM1)))
                                          ? vlTOPp->top__DOT__resultM1
                                          : (((((IData)(vlTOPp->top__DOT__rs2E2) 
                                                == (IData)(vlTOPp->top__DOT__rdW2)) 
                                               & (0U 
                                                  != (IData)(vlTOPp->top__DOT__rdW2))) 
                                              & (IData)(vlTOPp->top__DOT__reg_writeW2))
                                              ? vlTOPp->top__DOT__distW2
                                              : (((
                                                   ((IData)(vlTOPp->top__DOT__rs2E2) 
                                                    == (IData)(vlTOPp->top__DOT__rdW1)) 
                                                   & (0U 
                                                      != (IData)(vlTOPp->top__DOT__rdW1))) 
                                                  & (IData)(vlTOPp->top__DOT__reg_writeW1))
                                                  ? vlTOPp->top__DOT__distW1
                                                  : vlTOPp->top__DOT__source2E2))));
    vlTOPp->top__DOT__reg_data1E1 = ((((((IData)(vlTOPp->top__DOT__rs1E1) 
                                         == (IData)(vlTOPp->top__DOT__rdM2)) 
                                        & (0U != (IData)(vlTOPp->top__DOT__rdM2))) 
                                       & (IData)(vlTOPp->top__DOT__reg_writeM2)) 
                                      & (0U == (IData)(vlTOPp->top__DOT__mem_loadM2)))
                                      ? vlTOPp->top__DOT__resultM2
                                      : ((((((IData)(vlTOPp->top__DOT__rs1E1) 
                                             == (IData)(vlTOPp->top__DOT__rdM1)) 
                                            & (0U != (IData)(vlTOPp->top__DOT__rdM1))) 
                                           & (IData)(vlTOPp->top__DOT__reg_writeM1)) 
                                          & (0U == (IData)(vlTOPp->top__DOT__mem_loadM1)))
                                          ? vlTOPp->top__DOT__resultM1
                                          : (((((IData)(vlTOPp->top__DOT__rs1E1) 
                                                == (IData)(vlTOPp->top__DOT__rdW2)) 
                                               & (0U 
                                                  != (IData)(vlTOPp->top__DOT__rdW2))) 
                                              & (IData)(vlTOPp->top__DOT__reg_writeW2))
                                              ? vlTOPp->top__DOT__distW2
                                              : (((
                                                   ((IData)(vlTOPp->top__DOT__rs1E1) 
                                                    == (IData)(vlTOPp->top__DOT__rdW1)) 
                                                   & (0U 
                                                      != (IData)(vlTOPp->top__DOT__rdW1))) 
                                                  & (IData)(vlTOPp->top__DOT__reg_writeW1))
                                                  ? vlTOPp->top__DOT__distW1
                                                  : vlTOPp->top__DOT__source1E1))));
    vlTOPp->top__DOT__reg_data1E2 = ((((((IData)(vlTOPp->top__DOT__rs1E2) 
                                         == (IData)(vlTOPp->top__DOT__rdM2)) 
                                        & (0U != (IData)(vlTOPp->top__DOT__rdM2))) 
                                       & (IData)(vlTOPp->top__DOT__reg_writeM2)) 
                                      & (0U == (IData)(vlTOPp->top__DOT__mem_loadM2)))
                                      ? vlTOPp->top__DOT__resultM2
                                      : ((((((IData)(vlTOPp->top__DOT__rs1E2) 
                                             == (IData)(vlTOPp->top__DOT__rdM1)) 
                                            & (0U != (IData)(vlTOPp->top__DOT__rdM1))) 
                                           & (IData)(vlTOPp->top__DOT__reg_writeM1)) 
                                          & (0U == (IData)(vlTOPp->top__DOT__mem_loadM1)))
                                          ? vlTOPp->top__DOT__resultM1
                                          : (((((IData)(vlTOPp->top__DOT__rs1E2) 
                                                == (IData)(vlTOPp->top__DOT__rdW2)) 
                                               & (0U 
                                                  != (IData)(vlTOPp->top__DOT__rdW2))) 
                                              & (IData)(vlTOPp->top__DOT__reg_writeW2))
                                              ? vlTOPp->top__DOT__distW2
                                              : (((
                                                   ((IData)(vlTOPp->top__DOT__rs1E2) 
                                                    == (IData)(vlTOPp->top__DOT__rdW1)) 
                                                   & (0U 
                                                      != (IData)(vlTOPp->top__DOT__rdW1))) 
                                                  & (IData)(vlTOPp->top__DOT__reg_writeW1))
                                                  ? vlTOPp->top__DOT__distW1
                                                  : vlTOPp->top__DOT__source1E2))));
    vlTOPp->top__DOT__hit_predict1 = (((vlTOPp->top__DOT__predict__DOT__r_data1 
                                        >> 0x11U) & 
                                       (2U <= (3U & 
                                               (vlTOPp->top__DOT__predict__DOT__r_data1 
                                                >> 0xfU)))) 
                                      & ((3U & (vlTOPp->top__DOT__predict__DOT__r_data1 
                                                >> 0xdU)) 
                                         == (3U & ((IData)(vlTOPp->top__DOT__inst_rom__DOT__pc) 
                                                   >> 0xbU))));
    vlTOPp->top__DOT__stall = (((((((((0x1fU & (vlTOPp->top__DOT__instD1 
                                                >> 0xfU)) 
                                      == (IData)(vlTOPp->top__DOT__rdE1)) 
                                     | ((0x1fU & (vlTOPp->top__DOT__instD1 
                                                  >> 0x14U)) 
                                        == (IData)(vlTOPp->top__DOT__rdE1))) 
                                    & (0U != (IData)(vlTOPp->top__DOT__rdE1))) 
                                   & (IData)(vlTOPp->top__DOT__reg_writeE1)) 
                                  & (1U <= (IData)(vlTOPp->top__DOT__mem_loadE1))) 
                                 | ((((((0x1fU & (vlTOPp->top__DOT__instD1 
                                                  >> 0xfU)) 
                                        == (IData)(vlTOPp->top__DOT__rdE2)) 
                                       | ((0x1fU & 
                                           (vlTOPp->top__DOT__instD1 
                                            >> 0x14U)) 
                                          == (IData)(vlTOPp->top__DOT__rdE2))) 
                                      & (0U != (IData)(vlTOPp->top__DOT__rdE2))) 
                                     & (IData)(vlTOPp->top__DOT__reg_writeE2)) 
                                    & (1U <= (IData)(vlTOPp->top__DOT__mem_loadE2)))) 
                                | ((((((0x1fU & (vlTOPp->top__DOT__instD2 
                                                 >> 0xfU)) 
                                       == (IData)(vlTOPp->top__DOT__rdE1)) 
                                      | ((0x1fU & (vlTOPp->top__DOT__instD2 
                                                   >> 0x14U)) 
                                         == (IData)(vlTOPp->top__DOT__rdE1))) 
                                     & (0U != (IData)(vlTOPp->top__DOT__rdE1))) 
                                    & (IData)(vlTOPp->top__DOT__reg_writeE1)) 
                                   & (1U <= (IData)(vlTOPp->top__DOT__mem_loadE1)))) 
                               | ((((((0x1fU & (vlTOPp->top__DOT__instD2 
                                                >> 0xfU)) 
                                      == (IData)(vlTOPp->top__DOT__rdE2)) 
                                     | ((0x1fU & (vlTOPp->top__DOT__instD2 
                                                  >> 0x14U)) 
                                        == (IData)(vlTOPp->top__DOT__rdE2))) 
                                    & (0U != (IData)(vlTOPp->top__DOT__rdE2))) 
                                   & (IData)(vlTOPp->top__DOT__reg_writeE2)) 
                                  & (1U <= (IData)(vlTOPp->top__DOT__mem_loadE2))));
    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct7 
        = (1U & (vlTOPp->top__DOT__instD1 >> 0x1eU));
    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3 
        = (7U & (vlTOPp->top__DOT__instD1 >> 0xcU));
    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode 
        = (0x7fU & vlTOPp->top__DOT__instD1);
    if ((0x40U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
        if ((0x20U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
            if ((0x10U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
            } else {
                if ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout 
                        = ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))
                            ? ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))
                                ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))
                                    ? 1U : 0x3fU) : 0x3fU)
                            : 0x3fU);
                } else {
                    if ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout 
                            = ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))
                                ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))
                                    ? 2U : 0x3fU) : 0x3fU);
                    } else {
                        if ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                            if ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                                if ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 3U;
                                } else {
                                    if ((1U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 4U;
                                    } else {
                                        if ((4U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 5U;
                                        } else {
                                            if ((5U 
                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 6U;
                                            } else {
                                                if (
                                                    (6U 
                                                     == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 7U;
                                                } else {
                                                    if (
                                                        (7U 
                                                         == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 8U;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                            }
                        } else {
                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                        }
                    }
                }
            }
        } else {
            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
        }
    } else {
        if ((0x20U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
            if ((0x10U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                if ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                } else {
                    if ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout 
                            = ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))
                                ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))
                                    ? 0U : 0x3fU) : 0x3fU);
                    } else {
                        if ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                            if ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                                if ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout 
                                        = ((IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct7)
                                            ? 0x12U
                                            : 0x11U);
                                } else {
                                    if ((7U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x17U;
                                    } else {
                                        if ((6U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x16U;
                                        } else {
                                            if ((4U 
                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x15U;
                                            } else {
                                                if (
                                                    (1U 
                                                     == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x18U;
                                                } else {
                                                    if (
                                                        (5U 
                                                         == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout 
                                                            = 
                                                            ((IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct7)
                                                              ? 0x19U
                                                              : 0x1aU);
                                                    } else {
                                                        if (
                                                            (2U 
                                                             == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x13U;
                                                        } else {
                                                            if (
                                                                (3U 
                                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x14U;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                            }
                        } else {
                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                        }
                    }
                }
            } else {
                if ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                } else {
                    if ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                    } else {
                        if ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                            if ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                                if ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0xeU;
                                } else {
                                    if ((1U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0xfU;
                                    } else {
                                        if ((2U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x10U;
                                        }
                                    }
                                }
                            } else {
                                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                            }
                        } else {
                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                        }
                    }
                }
            }
        } else {
            if ((0x10U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                if ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                } else {
                    if ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout 
                            = ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))
                                ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))
                                    ? 0x1bU : 0x3fU)
                                : 0x3fU);
                    } else {
                        if ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                            if ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                                if ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x11U;
                                } else {
                                    if ((7U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x17U;
                                    } else {
                                        if ((6U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x16U;
                                        } else {
                                            if ((4U 
                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x15U;
                                            } else {
                                                if (
                                                    (1U 
                                                     == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x18U;
                                                } else {
                                                    if (
                                                        (5U 
                                                         == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout 
                                                            = 
                                                            ((IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct7)
                                                              ? 0x1aU
                                                              : 0x19U);
                                                    } else {
                                                        if (
                                                            (2U 
                                                             == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x13U;
                                                        } else {
                                                            if (
                                                                (3U 
                                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x14U;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                            }
                        } else {
                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                        }
                    }
                }
            } else {
                if ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                } else {
                    if ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                    } else {
                        if ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                            if ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode))) {
                                if ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 9U;
                                } else {
                                    if ((1U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                        vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0xaU;
                                    } else {
                                        if ((2U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0xbU;
                                        } else {
                                            if ((4U 
                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0xcU;
                                            } else {
                                                if (
                                                    (5U 
                                                     == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3))) {
                                                    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0xdU;
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                            }
                        } else {
                            vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = 0x3fU;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->top__DOT__alu_codeD1 = vlTOPp->__Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout;
    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct7 
        = (1U & (vlTOPp->top__DOT__instD2 >> 0x1eU));
    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3 
        = (7U & (vlTOPp->top__DOT__instD2 >> 0xcU));
    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode 
        = (0x7fU & vlTOPp->top__DOT__instD2);
    if ((0x40U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
        if ((0x20U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
            if ((0x10U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
            } else {
                if ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout 
                        = ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))
                            ? ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))
                                ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))
                                    ? 1U : 0x3fU) : 0x3fU)
                            : 0x3fU);
                } else {
                    if ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout 
                            = ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))
                                ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))
                                    ? 2U : 0x3fU) : 0x3fU);
                    } else {
                        if ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                            if ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                                if ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 3U;
                                } else {
                                    if ((1U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 4U;
                                    } else {
                                        if ((4U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 5U;
                                        } else {
                                            if ((5U 
                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 6U;
                                            } else {
                                                if (
                                                    (6U 
                                                     == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 7U;
                                                } else {
                                                    if (
                                                        (7U 
                                                         == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 8U;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                            }
                        } else {
                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                        }
                    }
                }
            }
        } else {
            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
        }
    } else {
        if ((0x20U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
            if ((0x10U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                if ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                } else {
                    if ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout 
                            = ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))
                                ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))
                                    ? 0U : 0x3fU) : 0x3fU);
                    } else {
                        if ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                            if ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                                if ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout 
                                        = ((IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct7)
                                            ? 0x12U
                                            : 0x11U);
                                } else {
                                    if ((7U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x17U;
                                    } else {
                                        if ((6U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x16U;
                                        } else {
                                            if ((4U 
                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x15U;
                                            } else {
                                                if (
                                                    (1U 
                                                     == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x18U;
                                                } else {
                                                    if (
                                                        (5U 
                                                         == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout 
                                                            = 
                                                            ((IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct7)
                                                              ? 0x19U
                                                              : 0x1aU);
                                                    } else {
                                                        if (
                                                            (2U 
                                                             == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x13U;
                                                        } else {
                                                            if (
                                                                (3U 
                                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x14U;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                            }
                        } else {
                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                        }
                    }
                }
            } else {
                if ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                } else {
                    if ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                    } else {
                        if ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                            if ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                                if ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0xeU;
                                } else {
                                    if ((1U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0xfU;
                                    } else {
                                        if ((2U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x10U;
                                        }
                                    }
                                }
                            } else {
                                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                            }
                        } else {
                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                        }
                    }
                }
            }
        } else {
            if ((0x10U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                if ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                } else {
                    if ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout 
                            = ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))
                                ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))
                                    ? 0x1bU : 0x3fU)
                                : 0x3fU);
                    } else {
                        if ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                            if ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                                if ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x11U;
                                } else {
                                    if ((7U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x17U;
                                    } else {
                                        if ((6U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x16U;
                                        } else {
                                            if ((4U 
                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x15U;
                                            } else {
                                                if (
                                                    (1U 
                                                     == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x18U;
                                                } else {
                                                    if (
                                                        (5U 
                                                         == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout 
                                                            = 
                                                            ((IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct7)
                                                              ? 0x1aU
                                                              : 0x19U);
                                                    } else {
                                                        if (
                                                            (2U 
                                                             == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x13U;
                                                        } else {
                                                            if (
                                                                (3U 
                                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x14U;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                            }
                        } else {
                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                        }
                    }
                }
            } else {
                if ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                } else {
                    if ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                    } else {
                        if ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                            if ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode))) {
                                if ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 9U;
                                } else {
                                    if ((1U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                        vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0xaU;
                                    } else {
                                        if ((2U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0xbU;
                                        } else {
                                            if ((4U 
                                                 == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0xcU;
                                            } else {
                                                if (
                                                    (5U 
                                                     == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3))) {
                                                    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0xdU;
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                            }
                        } else {
                            vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = 0x3fU;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->top__DOT__alu_codeD2 = vlTOPp->__Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout;
    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
        = vlTOPp->top__DOT__instD1;
    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__Vfuncout 
        = ((0x40U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
            ? ((0x20U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                ? ((0x10U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                    ? 0U : ((8U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                             ? ((4U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                 ? ((2U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                     ? ((1U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                         ? ((0xfff00000U 
                                             & (VL_NEGATE_I((IData)(
                                                                    (1U 
                                                                     & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                                        >> 0x1fU)))) 
                                                << 0x14U)) 
                                            | ((0xff000U 
                                                & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst) 
                                               | ((0x800U 
                                                   & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                      >> 9U)) 
                                                  | (0x7feU 
                                                     & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                        >> 0x14U)))))
                                         : 0U) : 0U)
                                 : 0U) : ((4U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                           ? ((2U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                               ? ((1U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                                   ? 
                                                  ((0xfffff000U 
                                                    & (VL_NEGATE_I((IData)(
                                                                           (1U 
                                                                            & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                                               >> 0x1fU)))) 
                                                       << 0xcU)) 
                                                   | (0xfffU 
                                                      & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                         >> 0x14U)))
                                                   : 0U)
                                               : 0U)
                                           : ((2U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                               ? ((1U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                                   ? 
                                                  ((0xfffff000U 
                                                    & (VL_NEGATE_I((IData)(
                                                                           (1U 
                                                                            & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                                               >> 0x1fU)))) 
                                                       << 0xcU)) 
                                                   | ((0x800U 
                                                       & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                          << 4U)) 
                                                      | ((0x7e0U 
                                                          & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                             >> 0x14U)) 
                                                         | (0x1eU 
                                                            & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                               >> 7U)))))
                                                   : 0U)
                                               : 0U))))
                : 0U) : ((0x20U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                          ? ((0x10U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                              ? ((8U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                  ? 0U : ((4U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                           ? ((2U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                               ? ((1U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                                   ? 
                                                  (0xfffff000U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                                   : 0U)
                                               : 0U)
                                           : 0U)) : 
                             ((8U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                               ? 0U : ((4U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                        ? 0U : ((2U 
                                                 & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                                 ? 
                                                ((1U 
                                                  & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                                  ? 
                                                 ((0xfffff000U 
                                                   & (VL_NEGATE_I((IData)(
                                                                          (1U 
                                                                           & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                                              >> 0x1fU)))) 
                                                      << 0xcU)) 
                                                  | ((0xfe0U 
                                                      & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                         >> 0x14U)) 
                                                     | (0x1fU 
                                                        & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                           >> 7U))))
                                                  : 0U)
                                                 : 0U))))
                          : ((0x10U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                              ? ((8U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                  ? 0U : ((4U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                           ? ((2U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                               ? ((1U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                                   ? 
                                                  (0xfffff000U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                                   : 0U)
                                               : 0U)
                                           : ((2U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                               ? ((1U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                                   ? 
                                                  ((0xfffff000U 
                                                    & (VL_NEGATE_I((IData)(
                                                                           (1U 
                                                                            & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                                               >> 0x1fU)))) 
                                                       << 0xcU)) 
                                                   | (0xfffU 
                                                      & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                         >> 0x14U)))
                                                   : 0U)
                                               : 0U)))
                              : ((8U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                  ? 0U : ((4U & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                           ? 0U : (
                                                   (2U 
                                                    & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                                    ? 
                                                   ((1U 
                                                     & vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst)
                                                     ? 
                                                    ((0xfffff000U 
                                                      & (VL_NEGATE_I((IData)(
                                                                             (1U 
                                                                              & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                                                >> 0x1fU)))) 
                                                         << 0xcU)) 
                                                     | (0xfffU 
                                                        & (vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__inst 
                                                           >> 0x14U)))
                                                     : 0U)
                                                    : 0U))))));
    vlTOPp->top__DOT__immD1 = vlTOPp->__Vfunc_top__DOT__decoder1__DOT__Imm__0__Vfuncout;
    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
        = vlTOPp->top__DOT__instD2;
    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__Vfuncout 
        = ((0x40U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
            ? ((0x20U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                ? ((0x10U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                    ? 0U : ((8U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                             ? ((4U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                 ? ((2U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                     ? ((1U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                         ? ((0xfff00000U 
                                             & (VL_NEGATE_I((IData)(
                                                                    (1U 
                                                                     & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                                        >> 0x1fU)))) 
                                                << 0x14U)) 
                                            | ((0xff000U 
                                                & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst) 
                                               | ((0x800U 
                                                   & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                      >> 9U)) 
                                                  | (0x7feU 
                                                     & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                        >> 0x14U)))))
                                         : 0U) : 0U)
                                 : 0U) : ((4U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                           ? ((2U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                               ? ((1U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                                   ? 
                                                  ((0xfffff000U 
                                                    & (VL_NEGATE_I((IData)(
                                                                           (1U 
                                                                            & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                                               >> 0x1fU)))) 
                                                       << 0xcU)) 
                                                   | (0xfffU 
                                                      & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                         >> 0x14U)))
                                                   : 0U)
                                               : 0U)
                                           : ((2U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                               ? ((1U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                                   ? 
                                                  ((0xfffff000U 
                                                    & (VL_NEGATE_I((IData)(
                                                                           (1U 
                                                                            & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                                               >> 0x1fU)))) 
                                                       << 0xcU)) 
                                                   | ((0x800U 
                                                       & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                          << 4U)) 
                                                      | ((0x7e0U 
                                                          & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                             >> 0x14U)) 
                                                         | (0x1eU 
                                                            & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                               >> 7U)))))
                                                   : 0U)
                                               : 0U))))
                : 0U) : ((0x20U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                          ? ((0x10U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                              ? ((8U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                  ? 0U : ((4U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                           ? ((2U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                               ? ((1U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                                   ? 
                                                  (0xfffff000U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                                   : 0U)
                                               : 0U)
                                           : 0U)) : 
                             ((8U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                               ? 0U : ((4U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                        ? 0U : ((2U 
                                                 & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                                 ? 
                                                ((1U 
                                                  & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                                  ? 
                                                 ((0xfffff000U 
                                                   & (VL_NEGATE_I((IData)(
                                                                          (1U 
                                                                           & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                                              >> 0x1fU)))) 
                                                      << 0xcU)) 
                                                  | ((0xfe0U 
                                                      & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                         >> 0x14U)) 
                                                     | (0x1fU 
                                                        & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                           >> 7U))))
                                                  : 0U)
                                                 : 0U))))
                          : ((0x10U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                              ? ((8U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                  ? 0U : ((4U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                           ? ((2U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                               ? ((1U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                                   ? 
                                                  (0xfffff000U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                                   : 0U)
                                               : 0U)
                                           : ((2U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                               ? ((1U 
                                                   & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                                   ? 
                                                  ((0xfffff000U 
                                                    & (VL_NEGATE_I((IData)(
                                                                           (1U 
                                                                            & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                                               >> 0x1fU)))) 
                                                       << 0xcU)) 
                                                   | (0xfffU 
                                                      & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                         >> 0x14U)))
                                                   : 0U)
                                               : 0U)))
                              : ((8U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                  ? 0U : ((4U & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                           ? 0U : (
                                                   (2U 
                                                    & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                                    ? 
                                                   ((1U 
                                                     & vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst)
                                                     ? 
                                                    ((0xfffff000U 
                                                      & (VL_NEGATE_I((IData)(
                                                                             (1U 
                                                                              & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                                                >> 0x1fU)))) 
                                                         << 0xcU)) 
                                                     | (0xfffU 
                                                        & (vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__inst 
                                                           >> 0x14U)))
                                                     : 0U)
                                                    : 0U))))));
    vlTOPp->top__DOT__immD2 = vlTOPp->__Vfunc_top__DOT__decoder2__DOT__Imm__4__Vfuncout;
    vlTOPp->top__DOT__branch_codeDj = (7U & ((2U & (IData)(vlTOPp->top__DOT__branch_numberD))
                                              ? ((0x63U 
                                                  != 
                                                  (0x7fU 
                                                   & vlTOPp->top__DOT__instD2))
                                                  ? 2U
                                                  : 
                                                 (vlTOPp->top__DOT__instD2 
                                                  >> 0xcU))
                                              : ((0x63U 
                                                  != 
                                                  (0x7fU 
                                                   & vlTOPp->top__DOT__instD1))
                                                  ? 2U
                                                  : 
                                                 (vlTOPp->top__DOT__instD1 
                                                  >> 0xcU))));
    vlTOPp->top__DOT__jump_codeD1 = ((0x63U == (0x7fU 
                                                & vlTOPp->top__DOT__instD1))
                                      ? 1U : ((0x6fU 
                                               == (0x7fU 
                                                   & vlTOPp->top__DOT__instD1))
                                               ? 2U
                                               : ((0x67U 
                                                   == 
                                                   (0x7fU 
                                                    & vlTOPp->top__DOT__instD1))
                                                   ? 3U
                                                   : 0U)));
    vlTOPp->top__DOT__jump_codeD2 = ((0x63U == (0x7fU 
                                                & vlTOPp->top__DOT__instD2))
                                      ? 1U : ((0x6fU 
                                               == (0x7fU 
                                                   & vlTOPp->top__DOT__instD2))
                                               ? 2U
                                               : ((0x67U 
                                                   == 
                                                   (0x7fU 
                                                    & vlTOPp->top__DOT__instD2))
                                                   ? 3U
                                                   : 0U)));
    vlTOPp->top__DOT__source2D1 = ((0U == (0x1fU & 
                                           (vlTOPp->top__DOT__instD1 
                                            >> 0x14U)))
                                    ? 0U : (vlTOPp->top__DOT__regfile__DOT__reg_ram__DOT__mem1
                                            [(0x1fU 
                                              & (vlTOPp->top__DOT__instD1 
                                                 >> 0x14U))] 
                                            ^ vlTOPp->top__DOT__regfile__DOT__reg_ram__DOT__mem2
                                            [(0x1fU 
                                              & (vlTOPp->top__DOT__instD1 
                                                 >> 0x14U))]));
    vlTOPp->top__DOT__source2D2 = ((0U == (0x1fU & 
                                           (vlTOPp->top__DOT__instD2 
                                            >> 0x14U)))
                                    ? 0U : (vlTOPp->top__DOT__regfile__DOT__reg_ram__DOT__mem1
                                            [(0x1fU 
                                              & (vlTOPp->top__DOT__instD2 
                                                 >> 0x14U))] 
                                            ^ vlTOPp->top__DOT__regfile__DOT__reg_ram__DOT__mem2
                                            [(0x1fU 
                                              & (vlTOPp->top__DOT__instD2 
                                                 >> 0x14U))]));
    vlTOPp->top__DOT__source1D1 = ((0U == (0x1fU & 
                                           (vlTOPp->top__DOT__instD1 
                                            >> 0xfU)))
                                    ? 0U : (vlTOPp->top__DOT__regfile__DOT__reg_ram__DOT__mem1
                                            [(0x1fU 
                                              & (vlTOPp->top__DOT__instD1 
                                                 >> 0xfU))] 
                                            ^ vlTOPp->top__DOT__regfile__DOT__reg_ram__DOT__mem2
                                            [(0x1fU 
                                              & (vlTOPp->top__DOT__instD1 
                                                 >> 0xfU))]));
    vlTOPp->top__DOT__source1D2 = ((0U == (0x1fU & 
                                           (vlTOPp->top__DOT__instD2 
                                            >> 0xfU)))
                                    ? 0U : (vlTOPp->top__DOT__regfile__DOT__reg_ram__DOT__mem1
                                            [(0x1fU 
                                              & (vlTOPp->top__DOT__instD2 
                                                 >> 0xfU))] 
                                            ^ vlTOPp->top__DOT__regfile__DOT__reg_ram__DOT__mem2
                                            [(0x1fU 
                                              & (vlTOPp->top__DOT__instD2 
                                                 >> 0xfU))]));
    vlTOPp->top__DOT__distM1 = ((1U == (IData)(vlTOPp->top__DOT__mem_loadM1))
                                 ? ((0U == (3U & vlTOPp->top__DOT__resultM1))
                                     ? ((0xffffff00U 
                                         & (VL_NEGATE_I((IData)(
                                                                (1U 
                                                                 & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                                    >> 7U)))) 
                                            << 8U)) 
                                        | (0xffU & vlTOPp->top__DOT__data_ram__DOT__r_data1_true))
                                     : ((1U == (3U 
                                                & vlTOPp->top__DOT__resultM1))
                                         ? ((0xffffff00U 
                                             & (VL_NEGATE_I((IData)(
                                                                    (1U 
                                                                     & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                                        >> 0xfU)))) 
                                                << 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                  >> 8U)))
                                         : ((2U == 
                                             (3U & vlTOPp->top__DOT__resultM1))
                                             ? ((0xffffff00U 
                                                 & (VL_NEGATE_I((IData)(
                                                                        (1U 
                                                                         & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                                            >> 0x17U)))) 
                                                    << 8U)) 
                                                | (0xffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                      >> 0x10U)))
                                             : ((0xffffff00U 
                                                 & (VL_NEGATE_I((IData)(
                                                                        (1U 
                                                                         & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                                            >> 0x1fU)))) 
                                                    << 8U)) 
                                                | (0xffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                      >> 0x18U))))))
                                 : ((2U == (IData)(vlTOPp->top__DOT__mem_loadM1))
                                     ? ((0U == (3U 
                                                & vlTOPp->top__DOT__resultM1))
                                         ? ((0xffff0000U 
                                             & (VL_NEGATE_I((IData)(
                                                                    (1U 
                                                                     & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                                        >> 0xfU)))) 
                                                << 0x10U)) 
                                            | (0xffffU 
                                               & vlTOPp->top__DOT__data_ram__DOT__r_data1_true))
                                         : ((1U == 
                                             (3U & vlTOPp->top__DOT__resultM1))
                                             ? ((0xffff0000U 
                                                 & (VL_NEGATE_I((IData)(
                                                                        (1U 
                                                                         & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                                            >> 0x17U)))) 
                                                    << 0x10U)) 
                                                | (0xffffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                      >> 8U)))
                                             : ((2U 
                                                 == 
                                                 (3U 
                                                  & vlTOPp->top__DOT__resultM1))
                                                 ? 
                                                ((0xffff0000U 
                                                  & (VL_NEGATE_I((IData)(
                                                                         (1U 
                                                                          & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                                             >> 0x1fU)))) 
                                                     << 0x10U)) 
                                                 | (0xffffU 
                                                    & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                       >> 0x10U)))
                                                 : 
                                                ((0xffffff00U 
                                                  & (VL_NEGATE_I((IData)(
                                                                         (1U 
                                                                          & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                                             >> 0x1fU)))) 
                                                     << 8U)) 
                                                 | (0xffU 
                                                    & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                       >> 0x18U))))))
                                     : ((3U == (IData)(vlTOPp->top__DOT__mem_loadM1))
                                         ? ((0xffffff00U 
                                             == vlTOPp->top__DOT__resultM1)
                                             ? vlTOPp->top__DOT__hardware_counter__DOT__cycles
                                             : vlTOPp->top__DOT__data_ram__DOT__r_data1_true)
                                         : ((4U == (IData)(vlTOPp->top__DOT__mem_loadM1))
                                             ? ((0U 
                                                 == 
                                                 (3U 
                                                  & vlTOPp->top__DOT__resultM1))
                                                 ? 
                                                (0xffU 
                                                 & vlTOPp->top__DOT__data_ram__DOT__r_data1_true)
                                                 : 
                                                ((1U 
                                                  == 
                                                  (3U 
                                                   & vlTOPp->top__DOT__resultM1))
                                                  ? 
                                                 (0xffU 
                                                  & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                     >> 8U))
                                                  : 
                                                 ((2U 
                                                   == 
                                                   (3U 
                                                    & vlTOPp->top__DOT__resultM1))
                                                   ? 
                                                  (0xffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                      >> 0x10U))
                                                   : 
                                                  (0xffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                      >> 0x18U)))))
                                             : ((5U 
                                                 == (IData)(vlTOPp->top__DOT__mem_loadM1))
                                                 ? 
                                                ((0U 
                                                  == 
                                                  (3U 
                                                   & vlTOPp->top__DOT__resultM1))
                                                  ? 
                                                 (0xffffU 
                                                  & vlTOPp->top__DOT__data_ram__DOT__r_data1_true)
                                                  : 
                                                 ((1U 
                                                   == 
                                                   (3U 
                                                    & vlTOPp->top__DOT__resultM1))
                                                   ? 
                                                  (0xffffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                      >> 8U))
                                                   : 
                                                  ((2U 
                                                    == 
                                                    (3U 
                                                     & vlTOPp->top__DOT__resultM1))
                                                    ? 
                                                   (0xffffU 
                                                    & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                       >> 0x10U))
                                                    : 
                                                   (0xffU 
                                                    & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                       >> 0x18U)))))
                                                 : vlTOPp->top__DOT__resultM1)))));
    vlTOPp->top__DOT__distM2 = ((1U == (IData)(vlTOPp->top__DOT__mem_loadM2))
                                 ? ((0U == (3U & vlTOPp->top__DOT__resultM2))
                                     ? ((0xffffff00U 
                                         & (VL_NEGATE_I((IData)(
                                                                (1U 
                                                                 & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                                    >> 7U)))) 
                                            << 8U)) 
                                        | (0xffU & vlTOPp->top__DOT__data_ram__DOT__r_data2_true))
                                     : ((1U == (3U 
                                                & vlTOPp->top__DOT__resultM2))
                                         ? ((0xffffff00U 
                                             & (VL_NEGATE_I((IData)(
                                                                    (1U 
                                                                     & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                                        >> 0xfU)))) 
                                                << 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                  >> 8U)))
                                         : ((2U == 
                                             (3U & vlTOPp->top__DOT__resultM2))
                                             ? ((0xffffff00U 
                                                 & (VL_NEGATE_I((IData)(
                                                                        (1U 
                                                                         & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                                            >> 0x17U)))) 
                                                    << 8U)) 
                                                | (0xffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                      >> 0x10U)))
                                             : ((0xffffff00U 
                                                 & (VL_NEGATE_I((IData)(
                                                                        (1U 
                                                                         & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                                            >> 0x1fU)))) 
                                                    << 8U)) 
                                                | (0xffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                      >> 0x18U))))))
                                 : ((2U == (IData)(vlTOPp->top__DOT__mem_loadM2))
                                     ? ((0U == (3U 
                                                & vlTOPp->top__DOT__resultM2))
                                         ? ((0xffff0000U 
                                             & (VL_NEGATE_I((IData)(
                                                                    (1U 
                                                                     & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                                        >> 0xfU)))) 
                                                << 0x10U)) 
                                            | (0xffffU 
                                               & vlTOPp->top__DOT__data_ram__DOT__r_data2_true))
                                         : ((1U == 
                                             (3U & vlTOPp->top__DOT__resultM2))
                                             ? ((0xffff0000U 
                                                 & (VL_NEGATE_I((IData)(
                                                                        (1U 
                                                                         & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                                            >> 0x17U)))) 
                                                    << 0x10U)) 
                                                | (0xffffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                      >> 8U)))
                                             : ((2U 
                                                 == 
                                                 (3U 
                                                  & vlTOPp->top__DOT__resultM2))
                                                 ? 
                                                ((0xffff0000U 
                                                  & (VL_NEGATE_I((IData)(
                                                                         (1U 
                                                                          & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                                             >> 0x1fU)))) 
                                                     << 0x10U)) 
                                                 | (0xffffU 
                                                    & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                       >> 0x10U)))
                                                 : 
                                                ((0xffffff00U 
                                                  & (VL_NEGATE_I((IData)(
                                                                         (1U 
                                                                          & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                                             >> 0x1fU)))) 
                                                     << 8U)) 
                                                 | (0xffU 
                                                    & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                       >> 0x18U))))))
                                     : ((3U == (IData)(vlTOPp->top__DOT__mem_loadM2))
                                         ? ((0xffffff00U 
                                             == vlTOPp->top__DOT__resultM2)
                                             ? vlTOPp->top__DOT__hardware_counter__DOT__cycles
                                             : vlTOPp->top__DOT__data_ram__DOT__r_data2_true)
                                         : ((4U == (IData)(vlTOPp->top__DOT__mem_loadM2))
                                             ? ((0U 
                                                 == 
                                                 (3U 
                                                  & vlTOPp->top__DOT__resultM2))
                                                 ? 
                                                (0xffU 
                                                 & vlTOPp->top__DOT__data_ram__DOT__r_data2_true)
                                                 : 
                                                ((1U 
                                                  == 
                                                  (3U 
                                                   & vlTOPp->top__DOT__resultM2))
                                                  ? 
                                                 (0xffU 
                                                  & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                     >> 8U))
                                                  : 
                                                 ((2U 
                                                   == 
                                                   (3U 
                                                    & vlTOPp->top__DOT__resultM2))
                                                   ? 
                                                  (0xffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                      >> 0x10U))
                                                   : 
                                                  (0xffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                      >> 0x18U)))))
                                             : ((5U 
                                                 == (IData)(vlTOPp->top__DOT__mem_loadM2))
                                                 ? 
                                                ((0U 
                                                  == 
                                                  (3U 
                                                   & vlTOPp->top__DOT__resultM2))
                                                  ? 
                                                 (0xffffU 
                                                  & vlTOPp->top__DOT__data_ram__DOT__r_data2_true)
                                                  : 
                                                 ((1U 
                                                   == 
                                                   (3U 
                                                    & vlTOPp->top__DOT__resultM2))
                                                   ? 
                                                  (0xffffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                      >> 8U))
                                                   : 
                                                  ((2U 
                                                    == 
                                                    (3U 
                                                     & vlTOPp->top__DOT__resultM2))
                                                    ? 
                                                   (0xffffU 
                                                    & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                       >> 0x10U))
                                                    : 
                                                   (0xffU 
                                                    & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                       >> 0x18U)))))
                                                 : vlTOPp->top__DOT__resultM2)))));
    vlTOPp->top__DOT__data_ram__DOT__r_data_true = 
        ((1U <= (IData)(vlTOPp->top__DOT__mem_storeM1))
          ? vlTOPp->top__DOT__data_ram__DOT__r_data1_true
          : vlTOPp->top__DOT__data_ram__DOT__r_data2_true);
    vlTOPp->top__DOT__check__DOT__store1 = (1U & ((
                                                   (~ 
                                                    (vlTOPp->top__DOT__check__DOT__inst1 
                                                     >> 6U)) 
                                                   & (vlTOPp->top__DOT__check__DOT__inst1 
                                                      >> 5U)) 
                                                  & (~ 
                                                     (vlTOPp->top__DOT__check__DOT__inst1 
                                                      >> 4U))));
    vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__PC 
        = (0x8000U | ((IData)(vlTOPp->top__DOT__pcE1) 
                      << 2U));
    vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code 
        = vlTOPp->top__DOT__alu_codeE1;
    vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2 
        = ((IData)(vlTOPp->top__DOT__alu_srcE1) ? vlTOPp->top__DOT__immE1
            : vlTOPp->top__DOT__reg_data2E1);
    vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
        = vlTOPp->top__DOT__reg_data1E1;
    vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__Vfuncout 
        = ((0x20U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
            ? 0U : ((0x10U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                     ? ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                         ? ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                             ? 0U : ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                      ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                          ? (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__PC 
                                             + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                          : VL_SHIFTRS_III(32,32,5, vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1, 
                                                           (0x1fU 
                                                            & vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)))
                                      : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                          ? (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                             >> (0x1fU 
                                                 & vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2))
                                          : (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                             << (0x1fU 
                                                 & vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)))))
                         : ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                             ? ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                 ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        & vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                     : (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        | vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2))
                                 : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        ^ vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                     : ((vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                         < vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                         ? 1U : 0U)))
                             : ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                 ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                     ? (VL_LTS_III(1,32,32, vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1, vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                         ? 1U : 0U)
                                     : (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        - vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2))
                                 : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                     : (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)))))
                     : ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                         ? ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                             ? ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                 ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                     : (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2))
                                 : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                     : (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)))
                             : ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                 ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                     : (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2))
                                 : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                     : ((0xfffffffeU 
                                         & vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__Vfuncout) 
                                        | ((vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                            >= vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                            ? 1U : 0U)))))
                         : ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                             ? ((0xfffffffeU & vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__Vfuncout) 
                                | (1U & ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                          ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                              ? ((vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                                  < vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                                  ? 1U
                                                  : 0U)
                                              : (VL_GTES_III(1,32,32, vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1, vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                                  ? 1U
                                                  : 0U))
                                          : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                              ? (VL_LTS_III(1,32,32, vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1, vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                                  ? 1U
                                                  : 0U)
                                              : ((vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                                  != vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                                  ? 1U
                                                  : 0U)))))
                             : ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                 ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                     ? ((0xfffffffeU 
                                         & vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__Vfuncout) 
                                        | ((vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 
                                            == vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2)
                                            ? 1U : 0U))
                                     : ((IData)(4U) 
                                        + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__PC))
                                 : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code))
                                     ? ((IData)(4U) 
                                        + vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__PC)
                                     : vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__src2))))));
    vlTOPp->top__DOT__resultE1 = vlTOPp->__Vfunc_top__DOT__alu1__DOT__RESULT__8__Vfuncout;
    vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__PC 
        = (0x8000U | ((IData)(vlTOPp->top__DOT__pcE2) 
                      << 2U));
    vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code 
        = vlTOPp->top__DOT__alu_codeE2;
    vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2 
        = ((IData)(vlTOPp->top__DOT__alu_srcE2) ? vlTOPp->top__DOT__immE2
            : vlTOPp->top__DOT__reg_data2E2);
    vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
        = vlTOPp->top__DOT__reg_data1E2;
    vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__Vfuncout 
        = ((0x20U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
            ? 0U : ((0x10U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                     ? ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                         ? ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                             ? 0U : ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                      ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                          ? (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__PC 
                                             + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                          : VL_SHIFTRS_III(32,32,5, vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1, 
                                                           (0x1fU 
                                                            & vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)))
                                      : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                          ? (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                             >> (0x1fU 
                                                 & vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2))
                                          : (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                             << (0x1fU 
                                                 & vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)))))
                         : ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                             ? ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                 ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        & vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                     : (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        | vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2))
                                 : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        ^ vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                     : ((vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                         < vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                         ? 1U : 0U)))
                             : ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                 ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                     ? (VL_LTS_III(1,32,32, vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1, vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                         ? 1U : 0U)
                                     : (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        - vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2))
                                 : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                     : (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)))))
                     : ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                         ? ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                             ? ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                 ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                     : (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2))
                                 : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                     : (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)))
                             : ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                 ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                     : (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2))
                                 : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                     ? (vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                        + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                     : ((0xfffffffeU 
                                         & vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__Vfuncout) 
                                        | ((vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                            >= vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                            ? 1U : 0U)))))
                         : ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                             ? ((0xfffffffeU & vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__Vfuncout) 
                                | (1U & ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                          ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                              ? ((vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                                  < vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                                  ? 1U
                                                  : 0U)
                                              : (VL_GTES_III(1,32,32, vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1, vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                                  ? 1U
                                                  : 0U))
                                          : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                              ? (VL_LTS_III(1,32,32, vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1, vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                                  ? 1U
                                                  : 0U)
                                              : ((vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                                  != vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                                  ? 1U
                                                  : 0U)))))
                             : ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                 ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                     ? ((0xfffffffeU 
                                         & vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__Vfuncout) 
                                        | ((vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 
                                            == vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2)
                                            ? 1U : 0U))
                                     : ((IData)(4U) 
                                        + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__PC))
                                 : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code))
                                     ? ((IData)(4U) 
                                        + vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__PC)
                                     : vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__src2))))));
    vlTOPp->top__DOT__resultE2 = vlTOPp->__Vfunc_top__DOT__alu2__DOT__RESULT__9__Vfuncout;
    vlTOPp->top__DOT__e_calcpc__DOT__reg_data1 = ((2U 
                                                   & (IData)(vlTOPp->top__DOT__branch_numberE))
                                                   ? vlTOPp->top__DOT__reg_data1E2
                                                   : vlTOPp->top__DOT__reg_data1E1);
    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemStore__2__alu_code 
        = vlTOPp->top__DOT__alu_codeD1;
    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemStore__2__Vfuncout 
        = ((0xeU == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemStore__2__alu_code))
            ? 1U : ((0xfU == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemStore__2__alu_code))
                     ? 2U : ((0x10U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemStore__2__alu_code))
                              ? 3U : 0U)));
    vlTOPp->top__DOT__mem_storeD1 = vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemStore__2__Vfuncout;
    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__alu_code 
        = vlTOPp->top__DOT__alu_codeD1;
    vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__Vfuncout 
        = ((0x20U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__alu_code))
            ? 0U : ((0x10U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__alu_code))
                     ? 0U : ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__alu_code))
                              ? ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__alu_code))
                                  ? ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__alu_code))
                                      ? 0U : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__alu_code))
                                               ? 5U
                                               : 4U))
                                  : ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__alu_code))
                                      ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__alu_code))
                                          ? 3U : 2U)
                                      : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__alu_code))
                                          ? 1U : 0U)))
                              : 0U)));
    vlTOPp->top__DOT__mem_loadD1 = vlTOPp->__Vfunc_top__DOT__decoder1__DOT__MemLoad__3__Vfuncout;
    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemStore__6__alu_code 
        = vlTOPp->top__DOT__alu_codeD2;
    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemStore__6__Vfuncout 
        = ((0xeU == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemStore__6__alu_code))
            ? 1U : ((0xfU == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemStore__6__alu_code))
                     ? 2U : ((0x10U == (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemStore__6__alu_code))
                              ? 3U : 0U)));
    vlTOPp->top__DOT__mem_storeD2 = vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemStore__6__Vfuncout;
    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__alu_code 
        = vlTOPp->top__DOT__alu_codeD2;
    vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__Vfuncout 
        = ((0x20U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__alu_code))
            ? 0U : ((0x10U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__alu_code))
                     ? 0U : ((8U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__alu_code))
                              ? ((4U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__alu_code))
                                  ? ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__alu_code))
                                      ? 0U : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__alu_code))
                                               ? 5U
                                               : 4U))
                                  : ((2U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__alu_code))
                                      ? ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__alu_code))
                                          ? 3U : 2U)
                                      : ((1U & (IData)(vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__alu_code))
                                          ? 1U : 0U)))
                              : 0U)));
    vlTOPp->top__DOT__mem_loadD2 = vlTOPp->__Vfunc_top__DOT__decoder2__DOT__MemLoad__7__Vfuncout;
    vlTOPp->top__DOT__immDj = (0x1fffU & ((2U & (IData)(vlTOPp->top__DOT__branch_numberD))
                                           ? (vlTOPp->top__DOT__immD2 
                                              >> 2U)
                                           : (vlTOPp->top__DOT__immD1 
                                              >> 2U)));
    vlTOPp->top__DOT__cannot_calcpc = ((((((IData)(vlTOPp->top__DOT__branch_numberD) 
                                           & (3U == (IData)(vlTOPp->top__DOT__jump_codeD1))) 
                                          & (((0x1fU 
                                               & (vlTOPp->top__DOT__instD1 
                                                  >> 0xfU)) 
                                              == (IData)(vlTOPp->top__DOT__rdE1)) 
                                             | (((0x1fU 
                                                  & (vlTOPp->top__DOT__instD1 
                                                     >> 0xfU)) 
                                                 == (IData)(vlTOPp->top__DOT__rdM1)) 
                                                & (1U 
                                                   <= (IData)(vlTOPp->top__DOT__mem_loadM1))))) 
                                         | ((((IData)(vlTOPp->top__DOT__branch_numberD) 
                                              >> 1U) 
                                             & (3U 
                                                == (IData)(vlTOPp->top__DOT__jump_codeD2))) 
                                            & (((0x1fU 
                                                 & (vlTOPp->top__DOT__instD2 
                                                    >> 0xfU)) 
                                                == (IData)(vlTOPp->top__DOT__rdE2)) 
                                               | (((0x1fU 
                                                    & (vlTOPp->top__DOT__instD2 
                                                       >> 0xfU)) 
                                                   == (IData)(vlTOPp->top__DOT__rdM2)) 
                                                  & (1U 
                                                     <= (IData)(vlTOPp->top__DOT__mem_loadM2)))))) 
                                        | (((IData)(vlTOPp->top__DOT__branch_numberD) 
                                            & (1U == (IData)(vlTOPp->top__DOT__jump_codeD1))) 
                                           & ((((0x1fU 
                                                 & (vlTOPp->top__DOT__instD1 
                                                    >> 0xfU)) 
                                                == (IData)(vlTOPp->top__DOT__rdE1)) 
                                               | ((0x1fU 
                                                   & (vlTOPp->top__DOT__instD1 
                                                      >> 0x14U)) 
                                                  == (IData)(vlTOPp->top__DOT__rdE1))) 
                                              | ((((0x1fU 
                                                    & (vlTOPp->top__DOT__instD1 
                                                       >> 0xfU)) 
                                                   == (IData)(vlTOPp->top__DOT__rdM1)) 
                                                  | ((0x1fU 
                                                      & (vlTOPp->top__DOT__instD1 
                                                         >> 0x14U)) 
                                                     == (IData)(vlTOPp->top__DOT__rdM1))) 
                                                 & (1U 
                                                    <= (IData)(vlTOPp->top__DOT__mem_loadM1)))))) 
                                       | ((((IData)(vlTOPp->top__DOT__branch_numberD) 
                                            >> 1U) 
                                           & (1U == (IData)(vlTOPp->top__DOT__jump_codeD2))) 
                                          & ((((0x1fU 
                                                & (vlTOPp->top__DOT__instD2 
                                                   >> 0xfU)) 
                                               == (IData)(vlTOPp->top__DOT__rdE2)) 
                                              | ((0x1fU 
                                                  & (vlTOPp->top__DOT__instD2 
                                                     >> 0x14U)) 
                                                 == (IData)(vlTOPp->top__DOT__rdE2))) 
                                             | ((((0x1fU 
                                                   & (vlTOPp->top__DOT__instD2 
                                                      >> 0xfU)) 
                                                  == (IData)(vlTOPp->top__DOT__rdM2)) 
                                                 | ((0x1fU 
                                                     & (vlTOPp->top__DOT__instD2 
                                                        >> 0x14U)) 
                                                    == (IData)(vlTOPp->top__DOT__rdM2))) 
                                                & (1U 
                                                   <= (IData)(vlTOPp->top__DOT__mem_loadM2))))));
    vlTOPp->top__DOT__jump_codeDj = ((2U & (IData)(vlTOPp->top__DOT__branch_numberD))
                                      ? (IData)(vlTOPp->top__DOT__jump_codeD2)
                                      : (IData)(vlTOPp->top__DOT__jump_codeD1));
    vlTOPp->top__DOT__reg_data2Dj = ((2U & (IData)(vlTOPp->top__DOT__branch_numberD))
                                      ? ((((((0x1fU 
                                              & (vlTOPp->top__DOT__instD2 
                                                 >> 0x14U)) 
                                             == (IData)(vlTOPp->top__DOT__rdM2)) 
                                            & (0U != (IData)(vlTOPp->top__DOT__rdM2))) 
                                           & (0U == (IData)(vlTOPp->top__DOT__mem_loadM2))) 
                                          & (IData)(vlTOPp->top__DOT__reg_writeM2))
                                          ? vlTOPp->top__DOT__resultM2
                                          : vlTOPp->top__DOT__source2D2)
                                      : ((((((0x1fU 
                                              & (vlTOPp->top__DOT__instD1 
                                                 >> 0x14U)) 
                                             == (IData)(vlTOPp->top__DOT__rdM1)) 
                                            & (0U != (IData)(vlTOPp->top__DOT__rdM1))) 
                                           & (0U == (IData)(vlTOPp->top__DOT__mem_loadM1))) 
                                          & (IData)(vlTOPp->top__DOT__reg_writeM1))
                                          ? vlTOPp->top__DOT__resultM1
                                          : vlTOPp->top__DOT__source2D1));
    vlTOPp->top__DOT__reg_data1Dj = ((2U & (IData)(vlTOPp->top__DOT__branch_numberD))
                                      ? ((((((0x1fU 
                                              & (vlTOPp->top__DOT__instD2 
                                                 >> 0xfU)) 
                                             == (IData)(vlTOPp->top__DOT__rdM2)) 
                                            & (0U != (IData)(vlTOPp->top__DOT__rdM2))) 
                                           & (0U == (IData)(vlTOPp->top__DOT__mem_loadM2))) 
                                          & (IData)(vlTOPp->top__DOT__reg_writeM2))
                                          ? vlTOPp->top__DOT__resultM2
                                          : vlTOPp->top__DOT__source1D2)
                                      : ((((((0x1fU 
                                              & (vlTOPp->top__DOT__instD1 
                                                 >> 0xfU)) 
                                             == (IData)(vlTOPp->top__DOT__rdM1)) 
                                            & (0U != (IData)(vlTOPp->top__DOT__rdM1))) 
                                           & (0U == (IData)(vlTOPp->top__DOT__mem_loadM1))) 
                                          & (IData)(vlTOPp->top__DOT__reg_writeM1))
                                          ? vlTOPp->top__DOT__resultM1
                                          : vlTOPp->top__DOT__source1D1));
    vlTOPp->top__DOT__data_ram__DOT__store_data = (
                                                   (1U 
                                                    == (IData)(vlTOPp->top__DOT__data_ram__DOT__mem_store))
                                                    ? 
                                                   ((0U 
                                                     == (IData)(vlTOPp->top__DOT__data_ram__DOT__offset))
                                                     ? 
                                                    ((0xffffff00U 
                                                      & vlTOPp->top__DOT__data_ram__DOT__r_data_true) 
                                                     | (0xffU 
                                                        & vlTOPp->top__DOT__data_ram__DOT__Source))
                                                     : 
                                                    ((1U 
                                                      == (IData)(vlTOPp->top__DOT__data_ram__DOT__offset))
                                                      ? 
                                                     ((0xffff0000U 
                                                       & vlTOPp->top__DOT__data_ram__DOT__r_data_true) 
                                                      | ((0xff00U 
                                                          & (vlTOPp->top__DOT__data_ram__DOT__Source 
                                                             << 8U)) 
                                                         | (0xffU 
                                                            & vlTOPp->top__DOT__data_ram__DOT__r_data_true)))
                                                      : 
                                                     ((2U 
                                                       == (IData)(vlTOPp->top__DOT__data_ram__DOT__offset))
                                                       ? 
                                                      ((0xff000000U 
                                                        & vlTOPp->top__DOT__data_ram__DOT__r_data_true) 
                                                       | ((0xff0000U 
                                                           & (vlTOPp->top__DOT__data_ram__DOT__Source 
                                                              << 0x10U)) 
                                                          | (0xffffU 
                                                             & vlTOPp->top__DOT__data_ram__DOT__r_data_true)))
                                                       : 
                                                      ((0xff000000U 
                                                        & (vlTOPp->top__DOT__data_ram__DOT__Source 
                                                           << 0x18U)) 
                                                       | (0xffffffU 
                                                          & vlTOPp->top__DOT__data_ram__DOT__r_data_true)))))
                                                    : 
                                                   ((2U 
                                                     == (IData)(vlTOPp->top__DOT__data_ram__DOT__mem_store))
                                                     ? 
                                                    ((0U 
                                                      == (IData)(vlTOPp->top__DOT__data_ram__DOT__offset))
                                                      ? 
                                                     ((0xffff0000U 
                                                       & vlTOPp->top__DOT__data_ram__DOT__r_data_true) 
                                                      | (0xffffU 
                                                         & vlTOPp->top__DOT__data_ram__DOT__Source))
                                                      : 
                                                     ((1U 
                                                       == (IData)(vlTOPp->top__DOT__data_ram__DOT__offset))
                                                       ? 
                                                      ((0xff000000U 
                                                        & vlTOPp->top__DOT__data_ram__DOT__r_data_true) 
                                                       | ((0xffff00U 
                                                           & (vlTOPp->top__DOT__data_ram__DOT__Source 
                                                              << 8U)) 
                                                          | (0xffU 
                                                             & vlTOPp->top__DOT__data_ram__DOT__r_data_true)))
                                                       : 
                                                      ((2U 
                                                        == (IData)(vlTOPp->top__DOT__data_ram__DOT__offset))
                                                        ? 
                                                       ((0xffff0000U 
                                                         & (vlTOPp->top__DOT__data_ram__DOT__Source 
                                                            << 0x10U)) 
                                                        | (0xffffU 
                                                           & vlTOPp->top__DOT__data_ram__DOT__r_data_true))
                                                        : 
                                                       ((0xff000000U 
                                                         & (vlTOPp->top__DOT__data_ram__DOT__Source 
                                                            << 0x18U)) 
                                                        | (0xffffffU 
                                                           & vlTOPp->top__DOT__data_ram__DOT__r_data_true)))))
                                                     : 
                                                    ((3U 
                                                      == (IData)(vlTOPp->top__DOT__data_ram__DOT__mem_store))
                                                      ? vlTOPp->top__DOT__data_ram__DOT__Source
                                                      : 0xffffffffU)));
    vlTOPp->top__DOT__is_depend = (((((((((vlTOPp->top__DOT__check__DOT__inst1 
                                           >> 2U) | 
                                          (vlTOPp->top__DOT__check__DOT__inst1 
                                           >> 4U)) 
                                         | (~ (vlTOPp->top__DOT__check__DOT__inst1 
                                               >> 5U))) 
                                        & (0U != (0x1fU 
                                                  & (vlTOPp->top__DOT__check__DOT__inst1 
                                                     >> 7U)))) 
                                       & ((((~ (vlTOPp->top__DOT__check__DOT__inst2 
                                                >> 2U)) 
                                            | ((~ (vlTOPp->top__DOT__check__DOT__inst2 
                                                   >> 3U)) 
                                               & (~ 
                                                  (vlTOPp->top__DOT__check__DOT__inst2 
                                                   >> 3U)))) 
                                           & ((0x1fU 
                                               & (vlTOPp->top__DOT__check__DOT__inst2 
                                                  >> 0xfU)) 
                                              == (0x1fU 
                                                  & (vlTOPp->top__DOT__check__DOT__inst1 
                                                     >> 7U)))) 
                                          | (((~ (vlTOPp->top__DOT__check__DOT__inst2 
                                                  >> 2U)) 
                                              & (vlTOPp->top__DOT__check__DOT__inst2 
                                                 >> 5U)) 
                                             & ((0x1fU 
                                                 & (vlTOPp->top__DOT__check__DOT__inst2 
                                                    >> 0x14U)) 
                                                == 
                                                (0x1fU 
                                                 & (vlTOPp->top__DOT__check__DOT__inst1 
                                                    >> 7U)))))) 
                                      | (vlTOPp->top__DOT__check__DOT__inst1 
                                         >> 6U)) | 
                                     ((IData)(vlTOPp->top__DOT__check__DOT__store1) 
                                      & (((~ (vlTOPp->top__DOT__check__DOT__inst2 
                                              >> 6U)) 
                                          & (vlTOPp->top__DOT__check__DOT__inst2 
                                             >> 5U)) 
                                         & (~ (vlTOPp->top__DOT__check__DOT__inst2 
                                               >> 4U))))) 
                                    | ((IData)(vlTOPp->top__DOT__check__DOT__store1) 
                                       & ((~ (vlTOPp->top__DOT__check__DOT__inst2 
                                              >> 5U)) 
                                          & (~ (vlTOPp->top__DOT__check__DOT__inst2 
                                                >> 2U))))) 
                                   & (0U != vlTOPp->top__DOT__check__DOT__inst2));
    vlTOPp->top__DOT__e_calcpc__DOT__jump_pc = (0x1fffU 
                                                & ((IData)(vlTOPp->top__DOT__immEj) 
                                                   + 
                                                   ((3U 
                                                     == (IData)(vlTOPp->top__DOT__jump_codeEj))
                                                     ? 
                                                    (vlTOPp->top__DOT__e_calcpc__DOT__reg_data1 
                                                     >> 2U)
                                                     : (IData)(vlTOPp->top__DOT__pcEj))));
    vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data2 
        = ((2U & (IData)(vlTOPp->top__DOT__branch_numberE))
            ? vlTOPp->top__DOT__reg_data2E2 : vlTOPp->top__DOT__reg_data2E1);
    vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data1 
        = vlTOPp->top__DOT__e_calcpc__DOT__reg_data1;
    vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__branch_code 
        = vlTOPp->top__DOT__branch_codeEj;
    vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__Vfuncout 
        = ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__branch_code))
            ? (vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data1 
               == vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data2)
            : ((1U == (IData)(vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__branch_code))
                ? (vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data1 
                   != vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data2)
                : ((4U == (IData)(vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__branch_code))
                    ? VL_LTS_III(1,32,32, vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data1, vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data2)
                    : ((5U == (IData)(vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__branch_code))
                        ? VL_GTES_III(1,32,32, vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data1, vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data2)
                        : ((6U == (IData)(vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__branch_code))
                            ? (vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data1 
                               < vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data2)
                            : ((7U == (IData)(vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__branch_code)) 
                               & (vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data1 
                                  >= vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data2)))))));
    vlTOPp->top__DOT__e_calcpc__DOT__flag = vlTOPp->__Vfunc_top__DOT__e_calcpc__DOT__Flag__11__Vfuncout;
    vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data2 
        = vlTOPp->top__DOT__reg_data2Dj;
    vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data1 
        = vlTOPp->top__DOT__reg_data1Dj;
    vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__branch_code 
        = vlTOPp->top__DOT__branch_codeDj;
    vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__Vfuncout 
        = ((0U == (IData)(vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__branch_code))
            ? (vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data1 
               == vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data2)
            : ((1U == (IData)(vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__branch_code))
                ? (vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data1 
                   != vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data2)
                : ((4U == (IData)(vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__branch_code))
                    ? VL_LTS_III(1,32,32, vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data1, vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data2)
                    : ((5U == (IData)(vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__branch_code))
                        ? VL_GTES_III(1,32,32, vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data1, vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data2)
                        : ((6U == (IData)(vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__branch_code))
                            ? (vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data1 
                               < vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data2)
                            : ((7U == (IData)(vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__branch_code)) 
                               & (vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data1 
                                  >= vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data2)))))));
    vlTOPp->top__DOT__d_calcpc__DOT__flag = vlTOPp->__Vfunc_top__DOT__d_calcpc__DOT__Flag__10__Vfuncout;
    vlTOPp->top__DOT__true_pcE = (0x1fffU & ((1U & 
                                              ((IData)(vlTOPp->top__DOT__e_calcpc__DOT__flag) 
                                               | ((IData)(vlTOPp->top__DOT__jump_codeEj) 
                                                  >> 1U)))
                                              ? (IData)(vlTOPp->top__DOT__e_calcpc__DOT__jump_pc)
                                              : ((IData)(1U) 
                                                 + (IData)(vlTOPp->top__DOT__pcEj))));
    vlTOPp->top__DOT__true_pcD = (0x1fffU & ((1U & 
                                              ((IData)(vlTOPp->top__DOT__d_calcpc__DOT__flag) 
                                               | ((IData)(vlTOPp->top__DOT__jump_codeDj) 
                                                  >> 1U)))
                                              ? ((IData)(vlTOPp->top__DOT__immDj) 
                                                 + 
                                                 ((3U 
                                                   == (IData)(vlTOPp->top__DOT__jump_codeDj))
                                                   ? 
                                                  (vlTOPp->top__DOT__reg_data1Dj 
                                                   >> 2U)
                                                   : (IData)(vlTOPp->top__DOT__pcDj)))
                                              : ((IData)(1U) 
                                                 + (IData)(vlTOPp->top__DOT__pcDj))));
    vlTOPp->top__DOT__fail_predictE = (((IData)(vlTOPp->top__DOT__true_pcE) 
                                        != (IData)(vlTOPp->top__DOT__pcD1)) 
                                       & (IData)(vlTOPp->top__DOT__jump_codeEj));
    vlTOPp->top__DOT__fail_predictD = ((((IData)(vlTOPp->top__DOT__true_pcD) 
                                         != (IData)(vlTOPp->top__DOT__check__DOT__pc1)) 
                                        & (1U <= (IData)(vlTOPp->top__DOT__jump_codeDj))) 
                                       & (~ (IData)(vlTOPp->top__DOT__cannot_calcpc)));
    vlTOPp->top__DOT__fail_predict = ((IData)(vlTOPp->top__DOT__fail_predictE) 
                                      | (IData)(vlTOPp->top__DOT__fail_predictD));
    vlTOPp->top__DOT__inst_rom__DOT__PC = (0x1fffU 
                                           & ((IData)(vlTOPp->top__DOT__stall)
                                               ? (IData)(vlTOPp->top__DOT__inst_rom__DOT__pc)
                                               : ((IData)(vlTOPp->top__DOT__fail_predictE)
                                                   ? (IData)(vlTOPp->top__DOT__true_pcE)
                                                   : 
                                                  ((IData)(vlTOPp->top__DOT__fail_predictD)
                                                    ? (IData)(vlTOPp->top__DOT__true_pcD)
                                                    : 
                                                   ((IData)(vlTOPp->top__DOT__hit_predict1)
                                                     ? vlTOPp->top__DOT__predict__DOT__r_data1
                                                     : 
                                                    ((IData)(vlTOPp->top__DOT__is_depend)
                                                      ? 
                                                     ((IData)(1U) 
                                                      + (IData)(vlTOPp->top__DOT__inst_rom__DOT__pc))
                                                      : 
                                                     ((((vlTOPp->top__DOT__predict__DOT__r_data2 
                                                         >> 0x11U) 
                                                        & (2U 
                                                           <= 
                                                           (3U 
                                                            & (vlTOPp->top__DOT__predict__DOT__r_data2 
                                                               >> 0xfU)))) 
                                                       & ((3U 
                                                           & (vlTOPp->top__DOT__predict__DOT__r_data2 
                                                              >> 0xdU)) 
                                                          == 
                                                          (3U 
                                                           & (((IData)(1U) 
                                                               + (IData)(vlTOPp->top__DOT__inst_rom__DOT__pc)) 
                                                              >> 0xbU))))
                                                       ? vlTOPp->top__DOT__predict__DOT__r_data2
                                                       : 
                                                      ((IData)(2U) 
                                                       + (IData)(vlTOPp->top__DOT__inst_rom__DOT__pc)))))))));
}

VL_INLINE_OPT void Vtop::_sequent__TOP__6(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_sequent__TOP__6\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->top__DOT__distM2 = ((1U == (IData)(vlTOPp->top__DOT__mem_loadM2))
                                 ? ((0U == (3U & vlTOPp->top__DOT__resultM2))
                                     ? ((0xffffff00U 
                                         & (VL_NEGATE_I((IData)(
                                                                (1U 
                                                                 & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                                    >> 7U)))) 
                                            << 8U)) 
                                        | (0xffU & vlTOPp->top__DOT__data_ram__DOT__r_data2_true))
                                     : ((1U == (3U 
                                                & vlTOPp->top__DOT__resultM2))
                                         ? ((0xffffff00U 
                                             & (VL_NEGATE_I((IData)(
                                                                    (1U 
                                                                     & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                                        >> 0xfU)))) 
                                                << 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                  >> 8U)))
                                         : ((2U == 
                                             (3U & vlTOPp->top__DOT__resultM2))
                                             ? ((0xffffff00U 
                                                 & (VL_NEGATE_I((IData)(
                                                                        (1U 
                                                                         & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                                            >> 0x17U)))) 
                                                    << 8U)) 
                                                | (0xffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                      >> 0x10U)))
                                             : ((0xffffff00U 
                                                 & (VL_NEGATE_I((IData)(
                                                                        (1U 
                                                                         & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                                            >> 0x1fU)))) 
                                                    << 8U)) 
                                                | (0xffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                      >> 0x18U))))))
                                 : ((2U == (IData)(vlTOPp->top__DOT__mem_loadM2))
                                     ? ((0U == (3U 
                                                & vlTOPp->top__DOT__resultM2))
                                         ? ((0xffff0000U 
                                             & (VL_NEGATE_I((IData)(
                                                                    (1U 
                                                                     & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                                        >> 0xfU)))) 
                                                << 0x10U)) 
                                            | (0xffffU 
                                               & vlTOPp->top__DOT__data_ram__DOT__r_data2_true))
                                         : ((1U == 
                                             (3U & vlTOPp->top__DOT__resultM2))
                                             ? ((0xffff0000U 
                                                 & (VL_NEGATE_I((IData)(
                                                                        (1U 
                                                                         & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                                            >> 0x17U)))) 
                                                    << 0x10U)) 
                                                | (0xffffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                      >> 8U)))
                                             : ((2U 
                                                 == 
                                                 (3U 
                                                  & vlTOPp->top__DOT__resultM2))
                                                 ? 
                                                ((0xffff0000U 
                                                  & (VL_NEGATE_I((IData)(
                                                                         (1U 
                                                                          & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                                             >> 0x1fU)))) 
                                                     << 0x10U)) 
                                                 | (0xffffU 
                                                    & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                       >> 0x10U)))
                                                 : 
                                                ((0xffffff00U 
                                                  & (VL_NEGATE_I((IData)(
                                                                         (1U 
                                                                          & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                                             >> 0x1fU)))) 
                                                     << 8U)) 
                                                 | (0xffU 
                                                    & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                       >> 0x18U))))))
                                     : ((3U == (IData)(vlTOPp->top__DOT__mem_loadM2))
                                         ? ((0xffffff00U 
                                             == vlTOPp->top__DOT__resultM2)
                                             ? vlTOPp->top__DOT__hardware_counter__DOT__cycles
                                             : vlTOPp->top__DOT__data_ram__DOT__r_data2_true)
                                         : ((4U == (IData)(vlTOPp->top__DOT__mem_loadM2))
                                             ? ((0U 
                                                 == 
                                                 (3U 
                                                  & vlTOPp->top__DOT__resultM2))
                                                 ? 
                                                (0xffU 
                                                 & vlTOPp->top__DOT__data_ram__DOT__r_data2_true)
                                                 : 
                                                ((1U 
                                                  == 
                                                  (3U 
                                                   & vlTOPp->top__DOT__resultM2))
                                                  ? 
                                                 (0xffU 
                                                  & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                     >> 8U))
                                                  : 
                                                 ((2U 
                                                   == 
                                                   (3U 
                                                    & vlTOPp->top__DOT__resultM2))
                                                   ? 
                                                  (0xffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                      >> 0x10U))
                                                   : 
                                                  (0xffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                      >> 0x18U)))))
                                             : ((5U 
                                                 == (IData)(vlTOPp->top__DOT__mem_loadM2))
                                                 ? 
                                                ((0U 
                                                  == 
                                                  (3U 
                                                   & vlTOPp->top__DOT__resultM2))
                                                  ? 
                                                 (0xffffU 
                                                  & vlTOPp->top__DOT__data_ram__DOT__r_data2_true)
                                                  : 
                                                 ((1U 
                                                   == 
                                                   (3U 
                                                    & vlTOPp->top__DOT__resultM2))
                                                   ? 
                                                  (0xffffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                      >> 8U))
                                                   : 
                                                  ((2U 
                                                    == 
                                                    (3U 
                                                     & vlTOPp->top__DOT__resultM2))
                                                    ? 
                                                   (0xffffU 
                                                    & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                       >> 0x10U))
                                                    : 
                                                   (0xffU 
                                                    & (vlTOPp->top__DOT__data_ram__DOT__r_data2_true 
                                                       >> 0x18U)))))
                                                 : vlTOPp->top__DOT__resultM2)))));
    vlTOPp->top__DOT__distM1 = ((1U == (IData)(vlTOPp->top__DOT__mem_loadM1))
                                 ? ((0U == (3U & vlTOPp->top__DOT__resultM1))
                                     ? ((0xffffff00U 
                                         & (VL_NEGATE_I((IData)(
                                                                (1U 
                                                                 & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                                    >> 7U)))) 
                                            << 8U)) 
                                        | (0xffU & vlTOPp->top__DOT__data_ram__DOT__r_data1_true))
                                     : ((1U == (3U 
                                                & vlTOPp->top__DOT__resultM1))
                                         ? ((0xffffff00U 
                                             & (VL_NEGATE_I((IData)(
                                                                    (1U 
                                                                     & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                                        >> 0xfU)))) 
                                                << 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                  >> 8U)))
                                         : ((2U == 
                                             (3U & vlTOPp->top__DOT__resultM1))
                                             ? ((0xffffff00U 
                                                 & (VL_NEGATE_I((IData)(
                                                                        (1U 
                                                                         & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                                            >> 0x17U)))) 
                                                    << 8U)) 
                                                | (0xffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                      >> 0x10U)))
                                             : ((0xffffff00U 
                                                 & (VL_NEGATE_I((IData)(
                                                                        (1U 
                                                                         & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                                            >> 0x1fU)))) 
                                                    << 8U)) 
                                                | (0xffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                      >> 0x18U))))))
                                 : ((2U == (IData)(vlTOPp->top__DOT__mem_loadM1))
                                     ? ((0U == (3U 
                                                & vlTOPp->top__DOT__resultM1))
                                         ? ((0xffff0000U 
                                             & (VL_NEGATE_I((IData)(
                                                                    (1U 
                                                                     & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                                        >> 0xfU)))) 
                                                << 0x10U)) 
                                            | (0xffffU 
                                               & vlTOPp->top__DOT__data_ram__DOT__r_data1_true))
                                         : ((1U == 
                                             (3U & vlTOPp->top__DOT__resultM1))
                                             ? ((0xffff0000U 
                                                 & (VL_NEGATE_I((IData)(
                                                                        (1U 
                                                                         & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                                            >> 0x17U)))) 
                                                    << 0x10U)) 
                                                | (0xffffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                      >> 8U)))
                                             : ((2U 
                                                 == 
                                                 (3U 
                                                  & vlTOPp->top__DOT__resultM1))
                                                 ? 
                                                ((0xffff0000U 
                                                  & (VL_NEGATE_I((IData)(
                                                                         (1U 
                                                                          & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                                             >> 0x1fU)))) 
                                                     << 0x10U)) 
                                                 | (0xffffU 
                                                    & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                       >> 0x10U)))
                                                 : 
                                                ((0xffffff00U 
                                                  & (VL_NEGATE_I((IData)(
                                                                         (1U 
                                                                          & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                                             >> 0x1fU)))) 
                                                     << 8U)) 
                                                 | (0xffU 
                                                    & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                       >> 0x18U))))))
                                     : ((3U == (IData)(vlTOPp->top__DOT__mem_loadM1))
                                         ? ((0xffffff00U 
                                             == vlTOPp->top__DOT__resultM1)
                                             ? vlTOPp->top__DOT__hardware_counter__DOT__cycles
                                             : vlTOPp->top__DOT__data_ram__DOT__r_data1_true)
                                         : ((4U == (IData)(vlTOPp->top__DOT__mem_loadM1))
                                             ? ((0U 
                                                 == 
                                                 (3U 
                                                  & vlTOPp->top__DOT__resultM1))
                                                 ? 
                                                (0xffU 
                                                 & vlTOPp->top__DOT__data_ram__DOT__r_data1_true)
                                                 : 
                                                ((1U 
                                                  == 
                                                  (3U 
                                                   & vlTOPp->top__DOT__resultM1))
                                                  ? 
                                                 (0xffU 
                                                  & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                     >> 8U))
                                                  : 
                                                 ((2U 
                                                   == 
                                                   (3U 
                                                    & vlTOPp->top__DOT__resultM1))
                                                   ? 
                                                  (0xffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                      >> 0x10U))
                                                   : 
                                                  (0xffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                      >> 0x18U)))))
                                             : ((5U 
                                                 == (IData)(vlTOPp->top__DOT__mem_loadM1))
                                                 ? 
                                                ((0U 
                                                  == 
                                                  (3U 
                                                   & vlTOPp->top__DOT__resultM1))
                                                  ? 
                                                 (0xffffU 
                                                  & vlTOPp->top__DOT__data_ram__DOT__r_data1_true)
                                                  : 
                                                 ((1U 
                                                   == 
                                                   (3U 
                                                    & vlTOPp->top__DOT__resultM1))
                                                   ? 
                                                  (0xffffU 
                                                   & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                      >> 8U))
                                                   : 
                                                  ((2U 
                                                    == 
                                                    (3U 
                                                     & vlTOPp->top__DOT__resultM1))
                                                    ? 
                                                   (0xffffU 
                                                    & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                       >> 0x10U))
                                                    : 
                                                   (0xffU 
                                                    & (vlTOPp->top__DOT__data_ram__DOT__r_data1_true 
                                                       >> 0x18U)))))
                                                 : vlTOPp->top__DOT__resultM1)))));
}

VL_INLINE_OPT void Vtop::_multiclk__TOP__7(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_multiclk__TOP__7\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->top__DOT__hit_predict1 = (((vlTOPp->top__DOT__predict__DOT__r_data1 
                                        >> 0x11U) & 
                                       (2U <= (3U & 
                                               (vlTOPp->top__DOT__predict__DOT__r_data1 
                                                >> 0xfU)))) 
                                      & ((3U & (vlTOPp->top__DOT__predict__DOT__r_data1 
                                                >> 0xdU)) 
                                         == (3U & ((IData)(vlTOPp->top__DOT__inst_rom__DOT__pc) 
                                                   >> 0xbU))));
    vlTOPp->top__DOT__inst_rom__DOT__PC = (0x1fffU 
                                           & ((IData)(vlTOPp->top__DOT__stall)
                                               ? (IData)(vlTOPp->top__DOT__inst_rom__DOT__pc)
                                               : ((IData)(vlTOPp->top__DOT__fail_predictE)
                                                   ? (IData)(vlTOPp->top__DOT__true_pcE)
                                                   : 
                                                  ((IData)(vlTOPp->top__DOT__fail_predictD)
                                                    ? (IData)(vlTOPp->top__DOT__true_pcD)
                                                    : 
                                                   ((IData)(vlTOPp->top__DOT__hit_predict1)
                                                     ? vlTOPp->top__DOT__predict__DOT__r_data1
                                                     : 
                                                    ((IData)(vlTOPp->top__DOT__is_depend)
                                                      ? 
                                                     ((IData)(1U) 
                                                      + (IData)(vlTOPp->top__DOT__inst_rom__DOT__pc))
                                                      : 
                                                     ((((vlTOPp->top__DOT__predict__DOT__r_data2 
                                                         >> 0x11U) 
                                                        & (2U 
                                                           <= 
                                                           (3U 
                                                            & (vlTOPp->top__DOT__predict__DOT__r_data2 
                                                               >> 0xfU)))) 
                                                       & ((3U 
                                                           & (vlTOPp->top__DOT__predict__DOT__r_data2 
                                                              >> 0xdU)) 
                                                          == 
                                                          (3U 
                                                           & (((IData)(1U) 
                                                               + (IData)(vlTOPp->top__DOT__inst_rom__DOT__pc)) 
                                                              >> 0xbU))))
                                                       ? vlTOPp->top__DOT__predict__DOT__r_data2
                                                       : 
                                                      ((IData)(2U) 
                                                       + (IData)(vlTOPp->top__DOT__inst_rom__DOT__pc)))))))));
}

void Vtop::_eval(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_eval\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((((~ (IData)(vlTOPp->cpu_resetn)) & (IData)(vlTOPp->__Vclklast__TOP__cpu_resetn)) 
         | ((IData)(vlTOPp->sysclk) & (~ (IData)(vlTOPp->__Vclklast__TOP__sysclk))))) {
        vlTOPp->_sequent__TOP__1(vlSymsp);
    }
    if (((IData)(vlTOPp->sysclk) & (~ (IData)(vlTOPp->__Vclklast__TOP__sysclk)))) {
        vlTOPp->_sequent__TOP__2(vlSymsp);
    }
    if (((~ (IData)(vlTOPp->sysclk)) & (IData)(vlTOPp->__Vclklast__TOP__sysclk))) {
        vlTOPp->_sequent__TOP__3(vlSymsp);
    }
    if ((((~ (IData)(vlTOPp->cpu_resetn)) & (IData)(vlTOPp->__Vclklast__TOP__cpu_resetn)) 
         | ((IData)(vlTOPp->sysclk) & (~ (IData)(vlTOPp->__Vclklast__TOP__sysclk))))) {
        vlTOPp->_sequent__TOP__6(vlSymsp);
    }
    if (((IData)(vlTOPp->sysclk) ^ (IData)(vlTOPp->__Vclklast__TOP__sysclk))) {
        vlTOPp->_multiclk__TOP__7(vlSymsp);
    }
    // Final
    vlTOPp->__Vclklast__TOP__cpu_resetn = vlTOPp->cpu_resetn;
    vlTOPp->__Vclklast__TOP__sysclk = vlTOPp->sysclk;
}

void Vtop::_eval_initial(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_eval_initial\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vclklast__TOP__cpu_resetn = vlTOPp->cpu_resetn;
    vlTOPp->__Vclklast__TOP__sysclk = vlTOPp->sysclk;
    vlTOPp->_initial__TOP__4(vlSymsp);
}

void Vtop::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::final\n"); );
    // Variables
    Vtop__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vtop::_eval_settle(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_eval_settle\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__5(vlSymsp);
}

VL_INLINE_OPT QData Vtop::_change_request(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_change_request\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vtop::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((sysclk & 0xfeU))) {
        Verilated::overWidthError("sysclk");}
    if (VL_UNLIKELY((cpu_resetn & 0xfeU))) {
        Verilated::overWidthError("cpu_resetn");}
}
#endif  // VL_DEBUG

void Vtop::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop::_ctor_var_reset\n"); );
    // Body
    sysclk = VL_RAND_RESET_I(1);
    cpu_resetn = VL_RAND_RESET_I(1);
    uart_tx = VL_RAND_RESET_I(1);
    top__DOT__pcD1 = VL_RAND_RESET_I(13);
    top__DOT__pcD2 = VL_RAND_RESET_I(13);
    top__DOT__pcE1 = VL_RAND_RESET_I(13);
    top__DOT__pcE2 = VL_RAND_RESET_I(13);
    top__DOT__pc1_in = VL_RAND_RESET_I(13);
    top__DOT__pc2_in = VL_RAND_RESET_I(13);
    top__DOT__instF1 = VL_RAND_RESET_I(32);
    top__DOT__instF2 = VL_RAND_RESET_I(32);
    top__DOT__instD1 = VL_RAND_RESET_I(32);
    top__DOT__instD2 = VL_RAND_RESET_I(32);
    top__DOT__inst1_in = VL_RAND_RESET_I(32);
    top__DOT__inst2_in = VL_RAND_RESET_I(32);
    top__DOT__rs1E1 = VL_RAND_RESET_I(5);
    top__DOT__rs2E1 = VL_RAND_RESET_I(5);
    top__DOT__rs1E2 = VL_RAND_RESET_I(5);
    top__DOT__rs2E2 = VL_RAND_RESET_I(5);
    top__DOT__rdE1 = VL_RAND_RESET_I(5);
    top__DOT__rdE2 = VL_RAND_RESET_I(5);
    top__DOT__rdM1 = VL_RAND_RESET_I(5);
    top__DOT__rdM2 = VL_RAND_RESET_I(5);
    top__DOT__rdW1 = VL_RAND_RESET_I(5);
    top__DOT__rdW2 = VL_RAND_RESET_I(5);
    top__DOT__immD1 = VL_RAND_RESET_I(32);
    top__DOT__immD2 = VL_RAND_RESET_I(32);
    top__DOT__immE1 = VL_RAND_RESET_I(32);
    top__DOT__immE2 = VL_RAND_RESET_I(32);
    top__DOT__source1D1 = VL_RAND_RESET_I(32);
    top__DOT__source2D1 = VL_RAND_RESET_I(32);
    top__DOT__source1D2 = VL_RAND_RESET_I(32);
    top__DOT__source2D2 = VL_RAND_RESET_I(32);
    top__DOT__source1E1 = VL_RAND_RESET_I(32);
    top__DOT__source2E1 = VL_RAND_RESET_I(32);
    top__DOT__source1E2 = VL_RAND_RESET_I(32);
    top__DOT__source2E2 = VL_RAND_RESET_I(32);
    top__DOT__reg_data1E1 = VL_RAND_RESET_I(32);
    top__DOT__reg_data2E1 = VL_RAND_RESET_I(32);
    top__DOT__reg_data1E2 = VL_RAND_RESET_I(32);
    top__DOT__reg_data2E2 = VL_RAND_RESET_I(32);
    top__DOT__reg_data2M1 = VL_RAND_RESET_I(32);
    top__DOT__reg_data2M2 = VL_RAND_RESET_I(32);
    top__DOT__distM1 = VL_RAND_RESET_I(32);
    top__DOT__distM2 = VL_RAND_RESET_I(32);
    top__DOT__distW1 = VL_RAND_RESET_I(32);
    top__DOT__distW2 = VL_RAND_RESET_I(32);
    top__DOT__resultE1 = VL_RAND_RESET_I(32);
    top__DOT__resultE2 = VL_RAND_RESET_I(32);
    top__DOT__resultM1 = VL_RAND_RESET_I(32);
    top__DOT__resultM2 = VL_RAND_RESET_I(32);
    top__DOT__branch_numberD = VL_RAND_RESET_I(2);
    top__DOT__branch_numberE = VL_RAND_RESET_I(2);
    top__DOT__pcDj = VL_RAND_RESET_I(13);
    top__DOT__pcEj = VL_RAND_RESET_I(13);
    top__DOT__reg_data1Dj = VL_RAND_RESET_I(32);
    top__DOT__reg_data2Dj = VL_RAND_RESET_I(32);
    top__DOT__immDj = VL_RAND_RESET_I(13);
    top__DOT__immEj = VL_RAND_RESET_I(13);
    top__DOT__jump_codeDj = VL_RAND_RESET_I(2);
    top__DOT__jump_codeEj = VL_RAND_RESET_I(2);
    top__DOT__branch_codeDj = VL_RAND_RESET_I(3);
    top__DOT__branch_codeEj = VL_RAND_RESET_I(3);
    top__DOT__true_pcD = VL_RAND_RESET_I(13);
    top__DOT__true_pcE = VL_RAND_RESET_I(13);
    top__DOT__fail_predictD = VL_RAND_RESET_I(1);
    top__DOT__fail_predictE = VL_RAND_RESET_I(1);
    top__DOT__fail_predict = VL_RAND_RESET_I(1);
    top__DOT__hit_predict1 = VL_RAND_RESET_I(1);
    top__DOT__state1_in = VL_RAND_RESET_I(2);
    top__DOT__state2_in = VL_RAND_RESET_I(2);
    top__DOT__stateD1 = VL_RAND_RESET_I(2);
    top__DOT__stateD2 = VL_RAND_RESET_I(2);
    top__DOT__stateEj = VL_RAND_RESET_I(2);
    top__DOT__is_depend = VL_RAND_RESET_I(1);
    top__DOT__stall = VL_RAND_RESET_I(1);
    top__DOT__alu_codeD1 = VL_RAND_RESET_I(6);
    top__DOT__alu_codeD2 = VL_RAND_RESET_I(6);
    top__DOT__alu_codeE1 = VL_RAND_RESET_I(6);
    top__DOT__alu_codeE2 = VL_RAND_RESET_I(6);
    top__DOT__alu_srcE1 = VL_RAND_RESET_I(1);
    top__DOT__alu_srcE2 = VL_RAND_RESET_I(1);
    top__DOT__reg_writeE1 = VL_RAND_RESET_I(1);
    top__DOT__reg_writeE2 = VL_RAND_RESET_I(1);
    top__DOT__reg_writeM1 = VL_RAND_RESET_I(1);
    top__DOT__reg_writeM2 = VL_RAND_RESET_I(1);
    top__DOT__reg_writeW1 = VL_RAND_RESET_I(1);
    top__DOT__reg_writeW2 = VL_RAND_RESET_I(1);
    top__DOT__mem_storeD1 = VL_RAND_RESET_I(2);
    top__DOT__mem_storeD2 = VL_RAND_RESET_I(2);
    top__DOT__mem_storeE1 = VL_RAND_RESET_I(2);
    top__DOT__mem_storeE2 = VL_RAND_RESET_I(2);
    top__DOT__mem_storeM1 = VL_RAND_RESET_I(2);
    top__DOT__mem_storeM2 = VL_RAND_RESET_I(2);
    top__DOT__mem_loadD1 = VL_RAND_RESET_I(3);
    top__DOT__mem_loadD2 = VL_RAND_RESET_I(3);
    top__DOT__mem_loadE1 = VL_RAND_RESET_I(3);
    top__DOT__mem_loadE2 = VL_RAND_RESET_I(3);
    top__DOT__mem_loadM1 = VL_RAND_RESET_I(3);
    top__DOT__mem_loadM2 = VL_RAND_RESET_I(3);
    top__DOT__jump_codeD1 = VL_RAND_RESET_I(2);
    top__DOT__jump_codeD2 = VL_RAND_RESET_I(2);
    top__DOT__cannot_calcpc = VL_RAND_RESET_I(1);
    top__DOT__uart_we = VL_RAND_RESET_I(1);
    top__DOT__uart_OUT_data = VL_RAND_RESET_I(1);
    top__DOT__inst_rom__DOT__pc = VL_RAND_RESET_I(13);
    top__DOT__inst_rom__DOT__PC = VL_RAND_RESET_I(13);
    { int __Vi0=0; for (; __Vi0<8192; ++__Vi0) {
            top__DOT__inst_rom__DOT__inst_rom_block__DOT__mem[__Vi0] = VL_RAND_RESET_I(32);
    }}
    top__DOT__check__DOT__inst1 = VL_RAND_RESET_I(32);
    top__DOT__check__DOT__inst2 = VL_RAND_RESET_I(32);
    top__DOT__check__DOT__pc1 = VL_RAND_RESET_I(13);
    top__DOT__check__DOT__pc2 = VL_RAND_RESET_I(13);
    top__DOT__check__DOT__state2 = VL_RAND_RESET_I(2);
    top__DOT__check__DOT__inst2_buffer = VL_RAND_RESET_I(32);
    top__DOT__check__DOT__pc2_buffer = VL_RAND_RESET_I(13);
    top__DOT__check__DOT__state2_buffer = VL_RAND_RESET_I(2);
    top__DOT__check__DOT__was_depend = VL_RAND_RESET_I(1);
    top__DOT__check__DOT__store1 = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<32; ++__Vi0) {
            top__DOT__regfile__DOT__reg_ram__DOT__mem1[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<32; ++__Vi0) {
            top__DOT__regfile__DOT__reg_ram__DOT__mem2[__Vi0] = VL_RAND_RESET_I(32);
    }}
    top__DOT__data_ram__DOT__r_data1 = VL_RAND_RESET_I(32);
    top__DOT__data_ram__DOT__r_data2 = VL_RAND_RESET_I(32);
    top__DOT__data_ram__DOT__resultM = VL_RAND_RESET_I(32);
    top__DOT__data_ram__DOT__Source = VL_RAND_RESET_I(32);
    top__DOT__data_ram__DOT__mem_store = VL_RAND_RESET_I(2);
    top__DOT__data_ram__DOT__offset = VL_RAND_RESET_I(2);
    top__DOT__data_ram__DOT__store_data = VL_RAND_RESET_I(32);
    top__DOT__data_ram__DOT__resultM_before = VL_RAND_RESET_I(14);
    top__DOT__data_ram__DOT__store_data_before = VL_RAND_RESET_I(32);
    top__DOT__data_ram__DOT__mem_store_before = VL_RAND_RESET_I(2);
    top__DOT__data_ram__DOT__r_data1_true = VL_RAND_RESET_I(32);
    top__DOT__data_ram__DOT__r_data2_true = VL_RAND_RESET_I(32);
    top__DOT__data_ram__DOT__r_data_true = VL_RAND_RESET_I(32);
    { int __Vi0=0; for (; __Vi0<16384; ++__Vi0) {
            top__DOT__data_ram__DOT__data_ram_block__DOT__mem[__Vi0] = VL_RAND_RESET_I(32);
    }}
    top__DOT__d_calcpc__DOT__flag = VL_RAND_RESET_I(1);
    top__DOT__e_calcpc__DOT__reg_data1 = VL_RAND_RESET_I(32);
    top__DOT__e_calcpc__DOT__jump_pc = VL_RAND_RESET_I(13);
    top__DOT__e_calcpc__DOT__flag = VL_RAND_RESET_I(1);
    top__DOT__predict__DOT__r_data1 = VL_RAND_RESET_I(18);
    top__DOT__predict__DOT__r_data2 = VL_RAND_RESET_I(18);
    { int __Vi0=0; for (; __Vi0<2048; ++__Vi0) {
            top__DOT__predict__DOT__cache__DOT__mem[__Vi0] = VL_RAND_RESET_I(18);
    }}
    top__DOT__uart0__DOT__bitcount = VL_RAND_RESET_I(4);
    top__DOT__uart0__DOT__shifter = VL_RAND_RESET_I(9);
    top__DOT__uart0__DOT__uart_busy = VL_RAND_RESET_I(1);
    top__DOT__uart0__DOT__sending = VL_RAND_RESET_I(1);
    top__DOT__uart0__DOT__d = VL_RAND_RESET_I(29);
    top__DOT__uart0__DOT__dNxt = VL_RAND_RESET_I(29);
    top__DOT__hardware_counter__DOT__cycles = VL_RAND_RESET_I(32);
    __Vfunc_top__DOT__decoder1__DOT__Imm__0__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_top__DOT__decoder1__DOT__Imm__0__inst = VL_RAND_RESET_I(32);
    __Vfunc_top__DOT__decoder1__DOT__ALUcode__1__Vfuncout = VL_RAND_RESET_I(6);
    __Vfunc_top__DOT__decoder1__DOT__ALUcode__1__opcode = VL_RAND_RESET_I(7);
    __Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct3 = VL_RAND_RESET_I(3);
    __Vfunc_top__DOT__decoder1__DOT__ALUcode__1__funct7 = VL_RAND_RESET_I(1);
    __Vfunc_top__DOT__decoder1__DOT__MemStore__2__Vfuncout = VL_RAND_RESET_I(2);
    __Vfunc_top__DOT__decoder1__DOT__MemStore__2__alu_code = VL_RAND_RESET_I(6);
    __Vfunc_top__DOT__decoder1__DOT__MemLoad__3__Vfuncout = VL_RAND_RESET_I(3);
    __Vfunc_top__DOT__decoder1__DOT__MemLoad__3__alu_code = VL_RAND_RESET_I(6);
    __Vfunc_top__DOT__decoder2__DOT__Imm__4__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_top__DOT__decoder2__DOT__Imm__4__inst = VL_RAND_RESET_I(32);
    __Vfunc_top__DOT__decoder2__DOT__ALUcode__5__Vfuncout = VL_RAND_RESET_I(6);
    __Vfunc_top__DOT__decoder2__DOT__ALUcode__5__opcode = VL_RAND_RESET_I(7);
    __Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct3 = VL_RAND_RESET_I(3);
    __Vfunc_top__DOT__decoder2__DOT__ALUcode__5__funct7 = VL_RAND_RESET_I(1);
    __Vfunc_top__DOT__decoder2__DOT__MemStore__6__Vfuncout = VL_RAND_RESET_I(2);
    __Vfunc_top__DOT__decoder2__DOT__MemStore__6__alu_code = VL_RAND_RESET_I(6);
    __Vfunc_top__DOT__decoder2__DOT__MemLoad__7__Vfuncout = VL_RAND_RESET_I(3);
    __Vfunc_top__DOT__decoder2__DOT__MemLoad__7__alu_code = VL_RAND_RESET_I(6);
    __Vfunc_top__DOT__alu1__DOT__RESULT__8__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_top__DOT__alu1__DOT__RESULT__8__src1 = VL_RAND_RESET_I(32);
    __Vfunc_top__DOT__alu1__DOT__RESULT__8__src2 = VL_RAND_RESET_I(32);
    __Vfunc_top__DOT__alu1__DOT__RESULT__8__alu_code = VL_RAND_RESET_I(6);
    __Vfunc_top__DOT__alu1__DOT__RESULT__8__PC = VL_RAND_RESET_I(32);
    __Vfunc_top__DOT__alu2__DOT__RESULT__9__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_top__DOT__alu2__DOT__RESULT__9__src1 = VL_RAND_RESET_I(32);
    __Vfunc_top__DOT__alu2__DOT__RESULT__9__src2 = VL_RAND_RESET_I(32);
    __Vfunc_top__DOT__alu2__DOT__RESULT__9__alu_code = VL_RAND_RESET_I(6);
    __Vfunc_top__DOT__alu2__DOT__RESULT__9__PC = VL_RAND_RESET_I(32);
    __Vfunc_top__DOT__d_calcpc__DOT__Flag__10__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_top__DOT__d_calcpc__DOT__Flag__10__branch_code = VL_RAND_RESET_I(3);
    __Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data1 = VL_RAND_RESET_I(32);
    __Vfunc_top__DOT__d_calcpc__DOT__Flag__10__reg_data2 = VL_RAND_RESET_I(32);
    __Vfunc_top__DOT__e_calcpc__DOT__Flag__11__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_top__DOT__e_calcpc__DOT__Flag__11__branch_code = VL_RAND_RESET_I(3);
    __Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data1 = VL_RAND_RESET_I(32);
    __Vfunc_top__DOT__e_calcpc__DOT__Flag__11__reg_data2 = VL_RAND_RESET_I(32);
}
