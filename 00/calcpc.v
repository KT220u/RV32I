`include "define.vh"

module calcpc(PC, imm, reg_data1, jalr, jal, branch, flag, nextPC);
	input [31:0] PC;
	input [31:0] imm, reg_data1;
	input jalr, jal, branch;
	input flag;
	output [31:0] nextPC;

	assign nextPC = (jalr) ? reg_data1 + imm : 
					(jal) ? PC + imm :
					(branch & flag) ? PC + imm :
					PC + 4;
endmodule

