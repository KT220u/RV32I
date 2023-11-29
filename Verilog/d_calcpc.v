`include "define.vh"

module d_calcpc(pc, pc_predicted, imm, reg_data1, jump_code, branch_code, nextpc, cannot_calcpc, fail_predict);
	input [12:0] pc;

	// 予測したPC、nextpcの結果と後で比較する
	input [12:0] pc_predicted;
	input [31:0] imm, reg_data1;
	input [1:0] jump_code;
	input [2:0] branch_code;
	output [12:0] nextpc;
	
	wire [12:0] imm_13, reg_data1_13;
	assign imm_13 = imm[14:2];
	assign reg_data1_13 = reg_data1[14:2];

	// jal : pc + imm
	// jalr : reg_data1 + imm
	assign nextpc = imm_13 + ((jump_code == 2'b10) ? pc : reg_data1_13);

	// DステージでPC計算できない。
	input cannot_calcpc;

	// 分岐予測ミス
	output fail_predict;
	assign fail_predict = (nextpc != pc_predicted & !cannot_calcpc & jump_code >= 2'b01) ? 1'b1 : 1'b0;
	

endmodule

