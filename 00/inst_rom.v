`include "define.vh"

module inst_rom(CLK, NRST, nextPC, PC, inst);
	input CLK, NRST;
	input [31:0] nextPC;
	output reg [31:0] PC;
	output [31:0] inst;
	
	// instruction memory
	parameter startPC = 32768;
	always @(negedge CLK) begin
		if(!NRST) PC <= startPC;
		else PC <= nextPC;
	end

	inst_rom_block inst_rom_block(CLK, PC[16:2], inst);		//PCの下２ビットは除く
endmodule

module inst_rom_block(clk, r_addr, r_data);
	input clk;
	input [14:0] r_addr;
	output reg [31:0] r_data;
	reg [31:0] mem [0:32767];
	initial begin
		$readmemh("/home/denjo/RV32I/00/code.hex", mem);
	end
	always @(posedge clk) begin
		r_data <= mem[r_addr];
	end
endmodule
