`include "define.vh"

module alu(CLK, pc, alu_code, alu_src, reg_data1, reg_data2, imm, result);
	input CLK;
	input [12:0] pc;
	input [5:0] alu_code;
	input alu_src;
	input [31:0] reg_data1, reg_data2, imm;
	output [31:0] result;

/*
	reg [31:0] PCbuffer;	// PC can be changed at clock negedge, so save PC value in buffer
	always @(posedge CLK) begin
		PCbuffer <= PC;
	end
*/
	wire [31:0] PC;		// PCをALU演算のために32bit拡張
	wire [31:0] src1, src2;
	
	assign PC = {16'd0, 1'b1, pc, 2'b00};
	assign src1 = reg_data1;
	assign src2 = (alu_src) ? imm : reg_data2;


	assign result = RESULT(src1, src2, alu_code, PC);

	function [31:0] RESULT;
		input [31:0] src1, src2;
		input [5:0] alu_code;
		input [31:0] PC;
		case(alu_code)
			`ALU_LUI : RESULT = src2;
			6'd27 : RESULT = PC + src2;
			`ALU_JAL : RESULT = PC + 4;
			`ALU_JALR : RESULT = PC + 4;
			`ALU_BEQ : RESULT[0] = (src1 == src2) ? 1 : 0;
			`ALU_BNE : RESULT[0] = (src1 !== src2) ? 1 : 0;
			`ALU_BLT : RESULT[0] = ($signed(src1) < $signed(src2)) ? 1 : 0;
			`ALU_BGE : RESULT[0] = ($signed(src1) >= $signed(src2)) ? 1 : 0; 
			`ALU_BLTU : RESULT[0] = (src1 < src2) ? 1 : 0;
			`ALU_BGEU : RESULT[0] = (src1 >= src2) ? 1 : 0;
			`ALU_LB : RESULT = src1 + src2; // LOAD : calc address (rs1 + offset)
			`ALU_LH : RESULT = src1 + src2;
			`ALU_LW : RESULT = src1 + src2;
			`ALU_LBU : RESULT = src1 + src2;
			`ALU_LHU : RESULT = src1 + src2;
			`ALU_SB : RESULT = src1 + src2;
			`ALU_SH : RESULT = src1 + src2;
			`ALU_SW : RESULT = src1 + src2;
			`ALU_ADD : RESULT = src1 + src2;
			`ALU_SUB : RESULT = src1 - src2;
			`ALU_SLT : RESULT = ($signed(src1) < $signed(src2)) ? 1 : 0;
			`ALU_SLTU : RESULT = (src1 < src2) ? 1 : 0;
			`ALU_XOR : RESULT = src1 ^ src2;
			`ALU_OR : RESULT = src1 | src2;
			`ALU_AND : RESULT = src1 & src2;
			`ALU_SLL : RESULT = src1 << src2[4:0];	// shamt = imm[4:0] or reg_data2
			`ALU_SRL : RESULT = src1 >> src2[4:0];
			`ALU_SRA : RESULT = $signed(src1) >>> src2[4:0];
			default : RESULT = 32'd0;
		endcase
	endfunction
endmodule
