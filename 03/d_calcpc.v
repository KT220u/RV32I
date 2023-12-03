`include "define.vh"

module d_calcpc(branch_number, pc1, pc2, pc_predicted, imm1, imm2, jump_code1, jump_code2, branch_code1, branch_code2, pc, imm, jump_code, branch_code, true_pc, fail_predict);
	input [1:0] branch_number;	// 01 : inst1 is branch, 10 : inst2 is branch
	input [12:0] pc1, pc2;

	// 予測したPC、nextpcの結果と後で比較する
	input [12:0] pc_predicted;
	input [31:0] imm1, imm2;
	input [1:0] jump_code1, jump_code2;
	input [2:0] branch_code1, branch_code2;

	output [12:0] pc;
	output [12:0] imm;
	output [1:0] jump_code;
	output [2:0] branch_code;

	assign pc = (branch_number[1]) ? pc2 : pc1;
	assign imm = (branch_number[1]) ? imm2[14:2] : imm1[14:2];
	assign jump_code = (branch_number[1]) ? jump_code2 : jump_code1;
	assign branch_code = (branch_number[1]) ? branch_code2 : branch_code1;
	
	output [12:0] true_pc;
	
	// jal 命令のみDステージでPC計算する
	// e_calcpcモジュールでは、jump_code[1] == 1 (jalr or branch) ならPC計算をする
	assign true_pc = pc + imm;

	// 分岐予測ミス
	output [1:0] fail_predict;
	assign fail_predict[0] = (true_pc != pc_predicted & jump_code == 2'b10);
	assign fail_predict[1] = fail_predict[0] & branch_number[0];
	
endmodule

