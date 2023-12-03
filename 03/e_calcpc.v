`include "define.vh"
//  d_calcpc(inst_number, pc, pc_predicted, imm1, imm2, jump_code1, jump_code2, branch_code1, branch_code2, imm, jump_code, branch_code, true_pc, fail_predict);

module e_calcpc(inst_number, pc, pc_predicted, imm, reg_data11, reg_data21, reg_data12, reg_data22, jump_code, branch_code, true_pc, fail_predict, w_data, w_addr, wen);
	input inst_number;
	input [12:0] pc;
	
	// 予測したPC、nextpcの結果と後で比較する
	input [12:0] pc_predicted;
	input [12:0] imm;
	input [31:0] reg_data11, reg_data21, reg_data12, reg_data22;
	input [1:0] jump_code;
	input [2:0] branch_code;
	output [12:0] true_pc;
	
	// 分岐予測ミス
	output fail_predict;
	
	// jal or jalr or branch条件を満たす
	wire [12:0] jump_pc;
	wire flag;
	wire [31:0] reg_data1, reg_data2;
	assign reg_data1 = (inst_number) ? reg_data12 : reg_data11;
	assign reg_data2 = (inst_number) ? reg_data22 : reg_data21;

	assign fail_predict = (true_pc != pc_predicted & jump_code[1]);
	assign flag = Flag(branch_code, reg_data1, reg_data2);
	assign true_pc = (flag | jump_code[1]) ? jump_pc : pc + 13'd1;

	// branch & flag | jal : pc + imm
	// jalr : imm + reg_data1
	assign jump_pc = imm + ((jump_code == 2'b11) ? reg_data1[14:2] : pc);

	// 分岐予測キャッシュに書き込み
	output [15:0] w_data;
	output [10:0] w_addr;
	output wen;

	assign w_data = {1'b1, pc[12:11], jump_pc};
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
