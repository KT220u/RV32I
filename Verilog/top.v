`include "define.vh"

module top(sysclk, cpu_resetn,  led, uart_tx);

	input sysclk;
	input cpu_resetn;
	output [7:0] led;
	output uart_tx;

	wire CLK;
	wire NRST;
	
	assign CLK = sysclk;
	assign NRST = cpu_resetn;
	assign led[0] = cpu_resetn;
    assign led[1] = 1'b1;
    assign led[2] = 1'b0;
    

	wire [31:0] instF, instD, instE, instM;
	wire [12:0] pcF, pcD, pcE, pcM;
	wire [12:0] prepc;
	wire [12:0] nextpc, nextpcD, nextpcE;
	wire [12:0] jumppcE;
	wire [4:0] rs1D, rs1E, rs1M, rs2D, rs2E, rs2M, rdD, rdE, rdM, rdW;
	wire [31:0] immD, immE;
	wire [31:0] reg_data1D, reg_data1E, reg_data2D, reg_data2E;
	wire [31:0] resultE, resultM;
	wire [31:0] source1D, source1E, source2D, source2E;
	wire [31:0] distM, distW;
	wire [31:0] store_dataE, store_dataM;
	

	// control signal
	wire [5:0] alu_codeD, alu_codeE;
	wire alu_srcD, alu_srcE;
	wire [1:0] jump_codeD, jump_codeE;
	wire [2:0] branch_codeD, branch_codeE;
	wire reg_writeD, reg_writeE, reg_writeM, reg_writeW;
	wire [1:0] mem_storeD, mem_storeE, mem_storeM;
	wire [2:0] mem_loadD, mem_loadE, mem_loadM;
	wire cannot_calcpcD, cannot_calcpcE;
	wire hit_predict;
	wire stall;
	wire fail_predict, fail_predictD, fail_predictE;


	// uart
	wire [7:0] uart_IN_data;
	wire uart_we;
	wire uart_OUT_data;

	assign uart_IN_data = store_dataM[7:0];
    assign uart_we = ((resultM == `UART_ADDR) && (mem_storeM >= 2'b01)) ? 1'b1 : 1'b0;  
    assign uart_tx = uart_OUT_data; 

	wire [31:0] hc_OUT_data;

	inst_rom inst_rom(.CLK(CLK), .NRST(NRST), .prepc(prepc), .nextpc(nextpc), 
					  .pc(pcF), .inst(instF), .stall(stall), .hit_predict(hit_predict), 
					  .fail_predict(fail_predict));

	decoder decoder(.inst(instD), .rs1(rs1D), .rs2(rs2D), .rd(rdD), .imm(immD), 
			.alu_code(alu_codeD), .alu_src(alu_srcD), .reg_write(reg_writeD),
			.mem_store(mem_storeD), .mem_load(mem_loadD), .jump_code(jump_codeD), .branch_code(branch_codeD));

	regfile regfile(.CLK(CLK), .rs1(rs1D), .rs2(rs2D), .source1(source1D), .source2(source2D), 
					.rd(rdM), .dist1(distM), .reg_write(reg_writeM));

	d_calcpc d_calcpc(.pc(pcD), .pc_predicted(pcF), .imm(immD), .reg_data1(reg_data1D), .reg_data2(reg_data2D),
					  .jump_code(jump_codeD), .branch_code(branch_codeD), 
					  .nextpc(nextpcD), .cannot_calcpc(cannot_calcpcD), .fail_predict(fail_predictD));

	e_calcpc e_calcpc(.pc(pcE), .pc_predicted(pcD), .imm(immE), .reg_data1(reg_data1E), .reg_data2(reg_data2E),
					  .jump_code(jump_codeE), .branch_code(branch_codeE), 
					  .nextpc(nextpcE), .jumppc(jumppcE), .cannot_calcpc(cannot_calcpcE), .fail_predict(fail_predictE));

	d_forwarding  d_forwarding(.rs1D(rs1D), .rs2D(rs2D), .source1D(source1D), .source2D(source2D), .rdE(rdE), .rdM(rdM), .resultM(resultM), .reg_writeE(reg_writeE), .mem_loadE(mem_loadE), .reg_writeM(reg_writeM), .mem_loadM(mem_loadM), .reg_data1D(reg_data1D), .reg_data2D(reg_data2D), .jump_code(jump_codeD), .cannot_calcpc(cannot_calcpcD), .stall(stall));
	
	predict predict(.CLK(CLK), .pcF(pcF), .prepc(prepc), .hit_predict(hit_predict), 
			.pcD(pcD), .nextpcD(nextpcD), .fail_predictD(fail_predictD), 
			.pcE(pcE), .nextpcE(nextpcE), .fail_predictE(fail_predictE),
			.nextpc(nextpc), .fail_predict(fail_predict));

	alu alu(CLK, pcE, alu_codeE, alu_srcE, reg_data1E, reg_data2E, immE, resultE);
	e_forwarding e_forwarding(rs1E, rs2E, source1E, source2E, rdM, resultM, rdW, distW, reg_writeM, mem_loadM, reg_writeW, reg_data1E, reg_data2E);
	data_ram data_ram(CLK, NRST, resultE, resultM, store_dataM, distM, mem_storeM, mem_loadM, hc_OUT_data);
    uart uart0(.uart_tx(uart_OUT_data),.uart_wr_i(uart_we), .uart_dat_i(uart_IN_data), .sys_clk_i(CLK), .sys_rstn_i(NRST));
    hardware_counter hardware_counter(.CLK_IP(CLK),.RSTN_IP(NRST), .COUNTER_OP(hc_OUT_data));

	fd_reg fd_reg(CLK, NRST, pcF, instF, pcD, instD, stall, fail_predictD, fail_predictE, nextpc);
	de_reg de_reg(CLK, NRST, pcD, instD, rs1D, rs2D, rdD, source1D, source2D, immD, alu_codeD, alu_srcD, jump_codeD, branch_codeD,  mem_storeD, mem_loadD, reg_writeD, cannot_calcpcD,  
			pcE, instE, rs1E, rs2E, rdE, source1E, source2E, immE, alu_codeE, alu_srcE, jump_codeE, branch_codeE, mem_storeE, mem_loadE, reg_writeE, cannot_calcpcE, stall, fail_predictE, nextpc);
	em_reg em_reg(CLK, NRST, pcE, instE, rdE, resultE,  reg_data2E, mem_storeE, mem_loadE, reg_writeE, 
			pcM, instM, rdM, resultM, store_dataM, mem_storeM, mem_loadM, reg_writeM);
	mw_reg mw_reg(CLK, NRST, rdM, distM, reg_writeM, rdW, distW, reg_writeW);


endmodule
