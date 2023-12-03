//alu alu1(CLK, pcE1, alu_codeE1, alu_srcE1, reg_data1E1, reg_data2E1, immE1, resultE1);
module de_reg(CLK, pcD, instD, alu_codeD, alu_srcD, reg_data1D, reg_data2D, immD, rs1D, rs2D, rdD, mem_storeD, mem_loadD, reg_writeD,
			  pcE, instE, alu_codeE, alu_srcE, reg_data1E, reg_data2E, immE, rs1E, rs2E, rdE, mem_storeE, mem_loadE, reg_writeE, stall);
	input CLK;
	input [12:0] pcD;
	input [31:0] instD;
	input [5:0] alu_codeD;
	input alu_srcD;
	input [31:0] reg_data1D, reg_data2D;
	input [31:0] immD;
	input [4:0] rs1D, rs2D, rdD;
	input [1:0] mem_storeD;
	input [2:0] mem_loadD;
	input reg_writeD;

	output reg [12:0] pcE;
	output reg [31:0] instE;
	output reg [5:0] alu_codeE;
	output reg alu_srcE;
	output reg [31:0] reg_data1E, reg_data2E;
	output reg [31:0] immE;
	output reg [4:0] rs1E, rs2E, rdE;
	output reg [1:0] mem_storeE;
	output reg [2:0] mem_loadE;
	output reg reg_writeE;

	input stall;

	always @(posedge CLK) begin
		if(stall) begin
			pcE <= 13'd0;
			instE <= 32'd0;
			alu_codeE <= 6'd0;
			alu_srcE <= 1'b0;
			mem_storeE <= 2'd0;
			mem_loadE <= 3'd0;
			reg_writeE <= 1'b0;
		end else begin
			pcE <= pcD;
			instE <= instD;
			alu_codeE <= alu_codeD;
			alu_srcE <= alu_srcD;
			mem_storeE <= mem_storeD;
			mem_loadE <= mem_loadD;
			reg_writeE <= reg_writeD;
		end
		reg_data1E <= reg_data1D;
		reg_data2E <= reg_data2D;
		immE <= immD;
		rs1E <= rs1D;
		rs2E <= rs2D;
		rdE <= rdD;	
	end
endmodule
