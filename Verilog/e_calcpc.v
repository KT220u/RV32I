`include "define.vh"

module e_calcpc(pc, pc_predicted, imm, reg_data1, reg_data2, jump_code, branch_code, nextpc, cannot_predict, fail_predict);
	input [31:0] pc;
	
	// 予測したPC、nextpcの結果と後で比較する
	input [31:0] pc_predicted;
	input [31:0] imm, reg_data1, reg_data2;
	input [1:0] jump_code;
	input [2:0] branch_code;
	output [31:0] nextpc;
	
	// Dステージで分岐先PC計算ができなかった
	input cannot_predict;

	// 分岐予測ミス
	output fail_predict;
	
	// ブランチの条件判定
	wire flag;

	// PC予測結果と一致 or Dステージで予測結果の判定が済んでいるなら０
	assign fail_predict = (nextpc == pc_predicted | !cannot_predict) ? 1'b0 : 1'b1;

	assign flag = Flag(branch_code, reg_data1, reg_data2);
	assign nextpc = Nextpc(pc, reg_data1, imm, jump_code,  flag);

	function [31:0] Nextpc;
		input [31:0] pc, reg_data1, imm;
		input [1:0] jump_code;
		input flag;
		if(jump_code == 2'b11) Nextpc = reg_data1 + imm;
		else if(jump_code == 2'b10) Nextpc = pc + imm;
		else if(jump_code == 2'b01 & flag) Nextpc = pc + imm;
		else Nextpc = pc + 32'd4;
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

