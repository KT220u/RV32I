`include "define.vh"

module top(sysclk, cpu_resetn, uart_tx);

	input sysclk, cpu_resetn;
	wire CLK, NRST;
	output uart_tx;

	assign CLK = sysclk;
	assign NRST = cpu_resetn;

	wire [12:0] pcF1, pcF2, pcD1, pcD2, pcE1, pcE2, pcM1, pcM2;
	wire [12:0] pc1_in, pc2_in, pc1_out, pc2_out;
	wire [31:0] instF1, instF2, instD1, instD2, instE1, instE2, instM1, instM2;
	wire [31:0] inst1_in, inst2_in, inst1_out, inst2_out;
	wire [4:0] rs1D1, rs2D1, rs1D2, rs2D2, rs1E1, rs2E1, rs1E2, rs2E2;
	wire [4:0] rdD1, rdD2, rdE1, rdE2, rdM1, rdM2, rdW1, rdW2;
	wire [31:0] immD1, immD2, immE1, immE2;
	wire [31:0] source1D1, source2D1, source1D2, source2D2, source1E1, source2E1, source1E2, source2E2;
	wire [31:0] reg_data1E1, reg_data2E1, reg_data1E2, reg_data2E2, reg_data2M1, reg_data2M2;
	wire [31:0] distM1, distM2, distW1, distW2;
	wire [31:0] resultE1, resultE2, resultM1, resultM2;

	wire [1:0] branch_numberD, branch_numberE;
	wire [12:0] pcDj, pcEj;
	wire [31:0] reg_data1D1, reg_data2D1, reg_data1D2, reg_data2D2;
	wire [31:0] reg_data1Dj, reg_data2Dj, reg_data1Ej, reg_data2Ej;
	wire [12:0] immDj, immEj;
	wire [1:0] jump_codeDj, jump_codeEj;
	wire [2:0] branch_codeDj, branch_codeEj;

	wire [12:0] true_pcD, true_pcE;
	wire fail_predictD, fail_predictE; 
	wire fail_predict;				
	assign fail_predict = fail_predictE | fail_predictD;

	wire hit_predict1, hit_predict2;
	wire [12:0] pre_pc1, pre_pc2;
	wire [17:0] predict_w_data;
	wire [10:0] predict_w_addr;
	wire predict_wen;
	wire [1:0] stateF1, stateF2, state1_in, state2_in, state1_out, state2_out, stateD1, stateD2, stateDj, stateEj;


// for test
/*
	assign reg_data1E1 = source1E1;V
	assign reg_data2E1 = source2E1;
	assign reg_data1E2 = source1E2;
	assign reg_data2E2 = source2E2;
*/
	wire is_depend;
	wire stall;
	wire [5:0] alu_codeD1, alu_codeD2, alu_codeE1, alu_codeE2;
	wire alu_srcD1, alu_srcD2, alu_srcE1, alu_srcE2;
	wire reg_writeD1, reg_writeD2, reg_writeE1, reg_writeE2, reg_writeM1, reg_writeM2, reg_writeW1, reg_writeW2;
	wire [1:0] mem_storeD1, mem_storeD2, mem_storeE1, mem_storeE2, mem_storeM1, mem_storeM2;
	wire [2:0]  mem_loadD1, mem_loadD2, mem_loadE1, mem_loadE2, mem_loadM1, mem_loadM2;
	wire [1:0] jump_codeD1, jump_codeD2, jump_codeE1, jump_codeE2;
	wire [2:0] branch_codeD1, branch_codeD2, branch_codeE1, branch_codeE2;
	wire cannot_calcpc;

	// uart
	wire [7:0] uart_IN_data;
	wire uart_we;
	wire uart_OUT_data;

	assign uart_IN_data = (mem_storeM1 >= 2'b01) ? reg_data2M1[7:0] : reg_data2M2[7:0];
    assign uart_we = (((resultM1 == `UART_ADDR) && (mem_storeM1 >= 2'b01)) | ((resultM2 == `UART_ADDR) && (mem_storeM2 >= 2'b01))) ? 1'b1 : 1'b0;  
    assign uart_tx = uart_OUT_data; 

	wire [31:0] hc_OUT_data;

/*
	always begin
		#20 $display("%b, %h, %h, %h, %h, %h, %h, %h, %h, %h", CLK, inst_rom.pc, inst1_out, inst2_out, alu1.src1, alu1.src2, alu2.src1, alu2.src2, alu1.result, alu2.result);
		$display("%h, %h, %h", regfile.dist1, regfile.we1, regfile.rd1);
		$display("%h, %h", regfile.reg_ram.w_addr1, regfile.reg_ram.w_data1);
	end
*/


	inst_rom inst_rom(CLK, NRST, pcF1, pcF2, instF1, instF2, stall, fail_predictD, true_pcD, fail_predictE, true_pcE, hit_predict1, hit_predict2, pre_pc1, pre_pc2, is_depend);
	check check(CLK, NRST, pc1_in, pc2_in, inst1_in, inst2_in, state1_in, state2_in, pc1_out, pc2_out, inst1_out, inst2_out, state1_out, state2_out, is_depend, branch_numberD, stall, fail_predictD, fail_predictE, hit_predict1);
	decoder decoder1(instD1, rs1D1, rs2D1, rdD1, immD1, alu_codeD1, alu_srcD1, reg_writeD1, mem_storeD1, mem_loadD1, jump_codeD1, branch_codeD1);
	decoder decoder2(instD2, rs1D2, rs2D2, rdD2, immD2, alu_codeD2, alu_srcD2, reg_writeD2, mem_storeD2, mem_loadD2, jump_codeD2, branch_codeD2);
	regfile regfile(CLK, rs1D1, rs2D1, rs1D2, rs2D2, source1D1, source2D1, source1D2, source2D2, rdM1, rdM2, distM1, distM2, reg_writeM1, reg_writeM2);
	alu alu1(CLK, pcE1, alu_codeE1, alu_srcE1, reg_data1E1, reg_data2E1, immE1, resultE1);
	alu alu2(CLK, pcE2, alu_codeE2, alu_srcE2, reg_data1E2, reg_data2E2, immE2, resultE2);
	data_ram data_ram(CLK, NRST, resultE1, resultE2, resultM1, resultM2, reg_data2M1, reg_data2M2, distM1, distM2, mem_storeM1, mem_storeM2, mem_loadM1, mem_loadM2, hc_OUT_data);

	
	d_stall d_stall(rs1D1, rs2D1, rs1D2, rs2D2, rdE1, rdE2, rdM1, rdM2, reg_writeE1, reg_writeE2, mem_loadE1, mem_loadE2, mem_loadM1, mem_loadM2, branch_numberD, jump_codeD1, jump_codeD2, stall, cannot_calcpc);
	d_forwarding d_forwarding1(rs1D1, rs2D1, source1D1, source2D1, rdM1, resultM1, reg_writeM1, mem_loadM1, reg_data1D1, reg_data2D1);
	d_forwarding d_forwarding2(rs1D2, rs2D2, source1D2, source2D2, rdM2, resultM2, reg_writeM2, mem_loadM2, reg_data1D2, reg_data2D2);
	e_forwarding e_forwarding1(rs1E1, rs2E1, source1E1, source2E1, rdM1, resultM1, rdW1, distW1, reg_writeM1, mem_loadM1, reg_writeW1, reg_data1E1, reg_data2E1,
																rdM2, resultM2, rdW2, distW2, reg_writeM2, mem_loadM2, reg_writeW2);
	e_forwarding e_forwarding2(rs1E2, rs2E2, source1E2, source2E2, rdM1, resultM1, rdW1, distW1, reg_writeM1, mem_loadM1, reg_writeW1, reg_data1E2, reg_data2E2,
																rdM2, resultM2, rdW2, distW2, reg_writeM2, mem_loadM2, reg_writeW2);
	
	d_calcpc d_calcpc(branch_numberD, pcD1, pcD2, pc1_out, reg_data1D1, reg_data2D1, reg_data1D2, reg_data2D2, immD1, immD2, jump_codeD1, jump_codeD2, branch_codeD1, branch_codeD2, stateD1, stateD2, 
									pcDj, reg_data1Dj, reg_data2Dj, immDj, jump_codeDj, branch_codeDj, stateDj, true_pcD, fail_predictD, cannot_calcpc);
	e_calcpc e_calcpc(branch_numberE, pcEj, pcD1, immEj, reg_data1E1, reg_data2E1, reg_data1E2, reg_data2E2, 
					  jump_codeEj, branch_codeEj, true_pcE, fail_predictE, stateEj, predict_w_data, predict_w_addr, predict_wen);	
	predict predict(CLK, pcF1, pcF2, hit_predict1, hit_predict2, stateF1, stateF2, pre_pc1, pre_pc2, predict_w_data, predict_w_addr, predict_wen);
	
	fc_reg fc_reg1(CLK, NRST, pcF1, instF1, stateF1, pc1_in, inst1_in, state1_in, stall, fail_predict, 1'b0);
	fc_reg fc_reg2(CLK, NRST, pcF2, instF2, stateF2, pc2_in, inst2_in, state2_in, stall, fail_predict, hit_predict1);

	// Fステージで命令１が分岐キャッシュヒットした場合は、命令２を破棄する。
	cd_reg cd_reg1(CLK, pc1_out, inst1_out, state1_out, pcD1, instD1, stateD1, stall, fail_predict);
	cd_reg cd_reg2(CLK, pc2_out, inst2_out, state2_out, pcD2, instD2, stateD2, stall, fail_predict);
	
	de_reg de_reg1(CLK, pcD1, instD1, alu_codeD1, alu_srcD1, source1D1, source2D1, immD1, rs1D1, rs2D1, rdD1, mem_storeD1, mem_loadD1, reg_writeD1,
			  	pcE1, instE1, alu_codeE1, alu_srcE1, source1E1, source2E1, immE1, rs1E1, rs2E1, rdE1, mem_storeE1, mem_loadE1, reg_writeE1, stall, fail_predictE);
	de_reg de_reg2(CLK, pcD2, instD2, alu_codeD2, alu_srcD2, source1D2, source2D2, immD2, rs1D2, rs2D2, rdD2, mem_storeD2, mem_loadD2, reg_writeD2,
			    pcE2, instE2, alu_codeE2, alu_srcE2, source1E2, source2E2, immE2, rs1E2, rs2E2, rdE2, mem_storeE2, mem_loadE2, reg_writeE2, stall, fail_predictE);
	de_reg_calcpc de_reg_calcpc(CLK, NRST, branch_numberD, pcDj, reg_data1Dj, reg_data2Dj, immDj, jump_codeDj, branch_codeDj, stateDj,
							 branch_numberE, pcEj, reg_data1Ej, reg_data2Ej, immEj, jump_codeEj, branch_codeEj, stateEj, stall, fail_predictE);

	em_reg em_reg1(CLK, pcE1, instE1, rdE1, resultE1, reg_data2E1, mem_storeE1, mem_loadE1, reg_writeE1,
				pcM1, instM1, rdM1, resultM1, reg_data2M1, mem_storeM1, mem_loadM1, reg_writeM1);
	em_reg em_reg2(CLK, pcE2, instE2, rdE2, resultE2, reg_data2E2, mem_storeE2, mem_loadE2, reg_writeE2,
				pcM2, instM2, rdM2, resultM2, reg_data2M2, mem_storeM2, mem_loadM2, reg_writeM2);

	mw_reg mw_reg1(CLK, NRST, rdM1, distM1, reg_writeM1, rdW1, distW1, reg_writeW1);
	mw_reg mw_reg2(CLK, NRST, rdM2, distM2, reg_writeM2, rdW2, distW2, reg_writeW2);

    uart uart0(.uart_tx(uart_OUT_data),.uart_wr_i(uart_we), .uart_dat_i(uart_IN_data), .sys_clk_i(CLK), .sys_rstn_i(NRST));
    hardware_counter hardware_counter(.CLK_IP(CLK),.RSTN_IP(NRST), .COUNTER_OP(hc_OUT_data));

endmodule
