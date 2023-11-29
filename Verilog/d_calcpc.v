`include "define.vh"

module d_calcpc(pc, pc_predicted, imm, reg_data1, reg_data2, jump_code, branch_code, nextpc, cannot_calcpc, fail_predict);
	input [12:0] pc;

	// 予測したPC、nextpcの結果と後で比較する
	input [12:0] pc_predicted;
	input [31:0] imm, reg_data1, reg_data2;
	input [1:0] jump_code;
	input [2:0] branch_code;
	output [12:0] nextpc;

	// データハザードにより、PC計算できなかった。
	input cannot_calcpc;

	// 分岐予測ミス
	output fail_predict;
	
	// jal or jalr or branch条件を満たす
	wire flag;
	
	// 分岐PC　分岐キャッシュにこれを書き込む
	wire [12:0] jumppc;

	assign fail_predict = (nextpc == pc_predicted | cannot_calcpc) ? 1'b0 : 1'b1;
	assign flag = Flag(branch_code, reg_data1, reg_data2);
	assign jumppc = Jumppc(pc, reg_data1[14:2], imm[14:2], jump_code);
	assign nextpc = (flag | jump_code[1]) ? jumppc : pc + 13'b1;

	// jump_codeに応じて、分岐時のPCを計算する。
	// 実際に分岐するPC(Nextpc)とは異なる。
	function [12:0] Jumppc;
		input [12:0] pc, reg_data1, imm;
		input [1:0] jump_code;
		if(jump_code == 2'b11) Jumppc = reg_data1 + imm;
		else if(jump_code == 2'b10) Jumppc = pc + imm;
		else Jumppc = pc + imm;
	endfunction

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

