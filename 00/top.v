`include "define.vh"

module top(sysclk, cpu_resetn,  led, uart_tx);

	input sysclk;
	//input [7:0] sw;
	input cpu_resetn;	// for Verilator
	output [7:0] led;
	output uart_tx;

	wire CLK;
	wire NRST;

	
	assign CLK = sysclk;
	assign NRST = cpu_resetn;
	//assign NRST = sw[0];
    //assign led[0] = sw[0];
    assign led[1] = 1'b1;
    assign led[2] = 1'b0;
    

	wire [31:0] inst;
	wire [31:0] PC;
	wire [31:0] nextPC;
	wire [4:0] rs1, rs2, rd;
	wire [31:0] imm;
	wire [31:0] reg_data1, reg_data2, reg_data3;
	wire [31:0] result;
	wire flag;
	
	assign flag = result[0];

	// control signal
	wire [5:0] alu_code;
	wire alu_src;
	wire reg_write;
	wire jalr, jal, branch;
	wire [1:0] mem_store;
	wire [2:0] mem_load;


	// uart
	wire [7:0] uart_IN_data;
	wire uart_we;
	wire uart_OUT_data;

	assign uart_IN_data = reg_data2[7:0];
    assign uart_we = ((result == `UART_ADDR) && (mem_store <= 2'b10)) ? 1'b1 : 1'b0;  
    assign uart_tx = uart_OUT_data; 

	wire [31:0] hc_OUT_data;

	decoder decoder(inst, rs1, rs2, rd, imm, alu_code,  alu_src, reg_write, jalr, jal, branch, mem_store, mem_load);
	regfile regfile( CLK, rs1, rs2, reg_data1, reg_data2, rd, reg_data3, reg_write);
	alu alu(CLK, PC, alu_code, alu_src, reg_data1, reg_data2, imm, result);
	calcpc calcpc(PC, imm, reg_data1, jalr, jal, branch, flag, nextPC);
	inst_rom inst_rom(CLK, NRST, nextPC, PC, inst);
	data_ram data_ram(CLK, NRST, result, reg_data2, reg_data3, mem_store, mem_load, hc_OUT_data);
    uart uart0(.uart_tx(uart_OUT_data),.uart_wr_i(uart_we), .uart_dat_i(uart_IN_data), .sys_clk_i(CLK), .sys_rstn_i(NRST));
    hardware_counter hardware_counter(.CLK_IP(CLK),.RSTN_IP(NRST), .COUNTER_OP(hc_OUT_data));

endmodule
