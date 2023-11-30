`include "define.vh"

module e_calcpc(pc, pc_predicted, imm, reg_data1, reg_data2, jump_code, branch_code, state, nextpc, jumppc, cannot_calcpc, fail_predict, w_data, w_addr, wen);
	input [12:0] pc;
	
	// 予測したPC、nextpcの結果と後で比較する
	input [12:0] pc_predicted;
	input [31:0] imm, reg_data1, reg_data2;
	input [1:0] jump_code;
	input [2:0] branch_code;
	input [1:0] state;
	output [12:0] nextpc;
	
	// 分岐PC　分岐キャッシュにこれを書き込む
	output [12:0] jumppc;
	
	// Dステージで分岐先PC計算ができなかった
	input cannot_calcpc;

	// 分岐予測ミス
	output fail_predict;
	
	// jal or jalr or branch条件を満たす
	wire flag;

	wire [1:0] newstate;

	assign fail_predict = (nextpc == pc_predicted | !cannot_calcpc) ? 1'b0 : 1'b1;
	assign flag = Flag(branch_code, reg_data1, reg_data2);
	assign nextpc = (flag | jump_code[1]) ? jumppc : pc + 13'd1;
	assign newstate = (flag | jump_code[1]) ? state + ((state == 2'b11) ? 2'd0 : 2'd1) :
											  state - ((state == 2'b00) ? 2'd0 : 2'd1);

	// branch & flag | jal : pc + imm
	// jalr : imm + reg_data1
	assign jumppc = imm[14:2] + ((jump_code == 2'b11) ? reg_data1[14:2] : pc);
	//assign nextpc = (flag | jump_code[1]) ? jumppc : pc + 13'b1;

	// 分岐予測キャッシュに書き込み
	output [17:0] w_data;
	output [10:0] w_addr;
	output wen;

	assign w_data = {1'b1, newstate, pc[12:11], jumppc};
	assign w_addr = pc[10:0];
	assign wen = (jump_code >= 2'b01) ? 1'b1 : 1'b0;


	// jump_codeに応じて、分岐時のPCを計算する。
	// 実際に分岐するPC(Nextpc)とは異なる。
	function [12:0] Jumppc;
		input [12:0] pc, reg_data1, imm;
		input [1:0] jump_code;
		if(jump_code == 2'b11) Jumppc = reg_data1 + imm;
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

