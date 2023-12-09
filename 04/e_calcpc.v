`include "define.vh"
//  d_calcpc(inst_number, pc, pc_predicted, imm1, imm2, jump_code1, jump_code2, branch_code1, branch_code2, imm, jump_code, branch_code, true_pc, fail_predict);

module e_calcpc(branch_number, pc, pc_predicted, imm, reg_data11, reg_data21, reg_data12, reg_data22, jump_code, branch_code, true_pc, fail_predict, state, w_data, w_addr, wen);
	input [1:0] branch_number;
	input [12:0] pc;
	
	// 予測したPC、nextpcの結果と後で比較する
	input [12:0] pc_predicted;
	input [12:0] imm;
	input [31:0] reg_data11, reg_data21, reg_data12, reg_data22;
	input [1:0] jump_code;
	input [2:0] branch_code;
	output [12:0] true_pc;

	wire [31:0] reg_data1, reg_data2;
	assign reg_data1 = (branch_number[1]) ? reg_data12 : reg_data11;
	assign reg_data2 = (branch_number[1]) ? reg_data22 : reg_data21;

	// 分岐予測ミス
	output fail_predict;
	
	// jal or jalr or branch条件を満たす
	wire [12:0] jump_pc;
	wire flag;

	// jal 命令は、必ずDステージでPC計算が完了しているので、考えなくて良い
	// PCが一致しない、かつ、jalr / branch (jump_code == 11 / 01)
	assign fail_predict = (true_pc != pc_predicted & jump_code[0]);
	assign flag = Flag(branch_code, reg_data1, reg_data2);
	assign true_pc = (flag | jump_code[1]) ? jump_pc : pc + 13'd1;

	// branch & flag | jal : pc + imm
	// jalr : imm + reg_data1
	assign jump_pc = imm + ((jump_code == 2'b11) ? reg_data1[14:2] : pc);

	// 分岐予測キャッシュに書き込み
	input [1:0] state;
	output [17:0] w_data;
	output [10:0] w_addr;
	output wen;

	wire [1:0] new_state;
	assign new_state = (flag | jump_code[1]) ? state + ((state == 2'b11) ? 2'b00 : 2'b01) : 
											   state - ((state == 2'b00) ? 2'b00 : 2'b01);
	assign w_data = {1'b1, new_state, pc[12:11], jump_pc};
	assign w_addr = pc[10:0];
	assign wen = (jump_code >= 2'b01) ? 1'b1 : 1'b0;


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

