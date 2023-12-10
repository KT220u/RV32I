#include <cstdio>
#include <verilated.h>
#include "Vtop.h"

// Set the clock speed of your processor.
static constexpr std::size_t clock_Hz = 40000000;
// UART baudrate
static constexpr std::size_t uart_Hz = 115200;
// The number of CoreMark iterations is depend on clock speed.
// Max: 30 seconds
static constexpr std::size_t max_cycle = 30 * clock_Hz;

std::size_t timer_ps = 0;

void uart_rx(unsigned int u) {
    static std::size_t s = 0;
    static std::size_t b = 0;
    static char c = 0;
    if( s == 0 && u == 0 ) {
        s = timer_ps;
        b = 0;
        c = 0;
    } else if( s != 0 && s + 1000000000000 / uart_Hz / 2 * (2*b+3) < timer_ps ) {
        if( b < 8 ) {
            c += u << b;
            ++b;
        } else {
            std::putchar(c);
            std::fflush(stdout);
            s = 0;
        }
    }
}


int main() {
    Vtop top;
    top.sysclk = 0;
    top.eval();
    top.cpu_resetn = 0;
    top.eval();
    top.sysclk = 1;
    top.eval();
    top.sysclk = 0;
    top.eval();
    top.cpu_resetn = 1;
    top.eval();

    for( std::size_t cycle = 0; cycle < max_cycle; ++cycle ) {
        top.sysclk = 0;
        top.eval();
        top.sysclk = 1;
        top.eval();
        uart_rx(top.uart_tx);
		
        timer_ps += 1000000000000 / clock_Hz;
    }
}

