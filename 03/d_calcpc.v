`include "define.vh"

module d_calcpc(branch_number, pc1, pc2, pc_predicted, reg_data11, reg_data21, reg_data12, reg_data22, imm1, imm2, jump_code1, jump_code2, branch_code1, branch_code2, pc, reg_data1, reg_data2, imm, jump_code, branch_code, true_pc, fail_predict, cannot_calcpc);
	input [1:0] branch_number;	// 01 : inst1 is branch, 10 : inst2 is branch
	input [12:0] pc1, pc2;

	// 予測したPC、nextpcの結果と後で比較する
	input [12:0] pc_predicted;
	input [31:0] reg_data11, reg_data21, reg_data12, reg_data22;
	input [31:0] imm1, imm2;
	input [1:0] jump_code1, jump_code2;
	input [2:0] branch_code1, branch_code2;

	output [12:0] pc;
	output [31:0] reg_data1, reg_data2;
	output [12:0] imm;
	output [1:0] jump_code;
	output [2:0] branch_code;

	assign pc = (branch_number[1]) ? pc2 : pc1;
	assign reg_data1 = (branch_number[1]) ? reg_data12 : reg_data11;
	assign reg_data2 = (branch_number[1]) ? reg_data22 : reg_data21;
	assign imm = (branch_number[1]) ? imm2[14:2] : imm1[14:2];
	assign jump_code = (branch_number[1]) ? jump_code2 : jump_code1;
	assign branch_code = (branch_number[1]) ? branch_code2 : branch_code1;
	
	output [12:0] true_pc;

	// 分岐予測ミス
	output fail_predict;

	// d_stallモジュールで、DステージでPC計算が可能かどうか（データハザードがないか）を調べてもらう。
	// この信号が立っていたら、fail_predict は必ず０
	input cannot_calcpc;
	
	wire [12:0] jump_pc;
	wire flag;

	// PCが一致しない、かつ、jal | jalr | (branch & flag)
	assign fail_predict = (true_pc != pc_predicted & jump_code >= 2'b01 & !cannot_calcpc);
	assign flag = Flag(branch_code, reg_data1, reg_data2);
	assign true_pc = (flag | jump_code[1]) ? jump_pc : pc + 13'd1;

	// jal : pc + imm
	// jalr : reg + imm
	// branch : pc + imm
	assign jump_pc = imm + ((jump_code == 2'b11) ? reg_data1[14:2] : pc);
	
	function Flag;
		input [2:0] branch_code;
		input [31:0] reg_data1, reg_data2;
		if(branch_code == 3'b000) begin	
			Flag = (reg_data1 == reg_data2) ? 1'b1 : 1'b0;
		end else if(branch_code == 3'b001) begin	
			Flag = (reg_data1 != reg_data2) ? 1'b1 : 1'b0;
		end else if(branch_code == 3'b100) begin	
			Flag = ($signed(reg_data1) < $signed(reg_data2)) ? 1'b1 : 1'b0;
		end else if(branch_code == 3'b101) begin	
			Flag = ($signed(reg_data1) >= $signed(reg_data2)) ? 1'b1 : 1'b0;
		end else if(branch_code == 3'b110) begin	
			Flag = (reg_data1 < reg_data2) ? 1'b1 : 1'b0;
		end else if(branch_code == 3'b111) begin	
			Flag = (reg_data1 >= reg_data2) ? 1'b1 : 1'b0;
		end else begin
			Flag = 1'b0;
		end
	endfunction
endmodule

