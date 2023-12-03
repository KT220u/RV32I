`include "define.vh"

module decoder(inst, rs1, rs2, rd ,imm, alu_code, alu_src, reg_write, mem_store, mem_load, jump_code, branch_code);
	input [31:0] inst;
	output [4:0] rs1, rs2, rd;
	output [31:0] imm;

	output [5:0] alu_code;	// refer define.vh
	output alu_src;		// 0 : data from reg_file[rs2], 1 : imm
	output reg_write;	// 1 : write reg_file[rd] <= dist1
	output [1:0] mem_store;	// 01 : SB, 10 : SH, 11 : SW
	output [2:0] mem_load; // 001 : LB, 010 : LH, 011 : LW, 100 : LBU, 101 : LHU
	output [1:0] jump_code; // 01 : branch, 10 : jal, 11 : jalr
	output [2:0] branch_code; // 000 : beq, 001 : bne, 100 : blt, 101 : bge, 110 : bltu, 111 : bgeu, 010 : not branch

	wire [6:0] opcode;
	wire funct7;			// RV32I では、funct7の2bit目のみ見ればOK
	wire [2:0] funct3;	

	assign rs1 = inst[19:15];
	assign rs2 = inst[24:20];
	assign rd = inst[11:7];
	assign opcode = inst[6:0];
	assign funct7 = inst[30];
	assign funct3 = inst[14:12];
	assign imm = Imm(inst);
	assign alu_code = ALUcode(opcode, funct3, funct7);
	assign alu_src = (opcode == `OP | opcode == `BRANCH) ? 0 : 1;
	assign reg_write = (opcode == `LUI | opcode == `AUIPC | opcode == `JAL | opcode == `JALR | opcode == `LOAD | opcode == `OPIMM | opcode == `OP ) ? 1 : 0;
	assign mem_store = MemStore(alu_code);
	assign mem_load = MemLoad(alu_code);
	assign jump_code = (opcode == `BRANCH) ? 2'b01 : (opcode == `JAL) ? 2'b10 : (opcode == `JALR) ? 2'b11 : 2'b00;
	assign branch_code = (opcode != `BRANCH) ? 3'b010 : funct3;

	function [31:0] Imm;
		input [31:0] inst;
		case(inst[6:0])
			`LUI : Imm = {inst[31:12], 12'b0};
			`AUIPC : Imm = {inst[31:12], 12'b0}; 
			`JAL : Imm = {{12{inst[31]}}, inst[19:12], inst[20], inst[30:21], 1'b0};
			`JALR : Imm = {{20{inst[31]}}, inst[31:20]};
			`BRANCH : Imm = {{20{inst[31]}}, inst[7], inst[30:25], inst[11:8], 1'b0};
			`LOAD : Imm = {{20{inst[31]}}, inst[31:20]};
			`STORE : Imm = {{20{inst[31]}}, inst[31:25], inst[11:7]};
			`OPIMM : Imm = {{20{inst[31]}}, inst[31:20]};
			default : Imm = {32{1'b0}};
		endcase
	endfunction

	function [5:0] ALUcode;
		input [6:0] opcode;
		input [2:0] funct3;
		input funct7;
		
		case(opcode)
			`LUI : ALUcode = `ALU_LUI;
			`AUIPC : ALUcode = 6'd27; //`ALU_AUIPCがないため
			`JAL : ALUcode = `ALU_JAL;
			`JALR : ALUcode = `ALU_JALR;
			`BRANCH : begin
				if(funct3 == 3'b000) ALUcode = `ALU_BEQ;
				else if(funct3 == 3'b001) ALUcode = `ALU_BNE;
				else if(funct3 == 3'b100) ALUcode = `ALU_BLT;
				else if(funct3 == 3'b101) ALUcode = `ALU_BGE;
				else if(funct3 == 3'b110) ALUcode = `ALU_BLTU;
				else if(funct3 == 3'b111) ALUcode = `ALU_BGEU;
			end
			`LOAD : begin
				if(funct3 == 3'b000) ALUcode = `ALU_LB;
				else if(funct3 == 3'b001) ALUcode = `ALU_LH;
				else if(funct3 == 3'b010) ALUcode = `ALU_LW;
				else if(funct3 == 3'b100) ALUcode = `ALU_LBU;
				else if(funct3 == 3'b101) ALUcode = `ALU_LHU;
			end
			`STORE : begin
				if(funct3 == 3'b000) ALUcode = `ALU_SB;
				else if (funct3 == 3'b001) ALUcode = `ALU_SH;
				else if(funct3 == 3'b010) ALUcode = `ALU_SW;
			end
			`OPIMM : begin
				if(funct3 == 3'b000) ALUcode = `ALU_ADD;
				else if(funct3 == 3'b111) ALUcode = `ALU_AND;
				else if(funct3 == 3'b110) ALUcode = `ALU_OR;
				else if(funct3 == 3'b100) ALUcode = `ALU_XOR;
				else if(funct3 == 3'b001) ALUcode = `ALU_SLL;		
				else if(funct3 == 3'b101) ALUcode = (funct7) ? `ALU_SRA : `ALU_SRL;
				else if(funct3 == 3'b010) ALUcode = `ALU_SLT;
				else if(funct3 == 3'b011) ALUcode = `ALU_SLTU;
			end
			`OP : begin
				if(funct3 == 3'b000) ALUcode = (funct7) ? `ALU_SUB : `ALU_ADD;
				else if(funct3 == 3'b111) ALUcode = `ALU_AND;
				else if(funct3 == 3'b110) ALUcode = `ALU_OR;
				else if(funct3 == 3'b100) ALUcode = `ALU_XOR;
				else if(funct3 == 3'b001) ALUcode = `ALU_SLL;		
				else if(funct3 == 3'b101) ALUcode = (funct7) ? `ALU_SRL : `ALU_SRA;
				else if(funct3 == 3'b010) ALUcode = `ALU_SLT;
				else if(funct3 == 3'b011) ALUcode = `ALU_SLTU;
			end
			default : ALUcode = `ALU_NOP; 
		endcase
	endfunction

	function [1:0] MemStore;
		input [5:0] alu_code;
		case (alu_code)
			`ALU_SB : MemStore = 2'b01;
			`ALU_SH : MemStore = 2'b10;
			`ALU_SW : MemStore = 2'b11;
			default : MemStore = 2'b00;
		endcase
	endfunction

	function [2:0] MemLoad;
		input [5:0] alu_code;
		case (alu_code)
			`ALU_LB : MemLoad = 3'b001;
			`ALU_LH : MemLoad = 3'b010;
			`ALU_LW : MemLoad = 3'b011;
			`ALU_LBU : MemLoad = 3'b100;
			`ALU_LHU : MemLoad = 3'b101;
			default : MemLoad = 3'b000;
		endcase
	endfunction

endmodule
