module regfile(CLK, rs1, rs2, source1, source2, rd, dist1, reg_write);
	input CLK;
	input [4:0] rs1, rs2;
	output [31:0] source1, source2;
	input [4:0] rd;
	input [31:0] dist1;
	input reg_write;
	
	wire we;
	wire [31:0] read1, read2;

	
	assign we = reg_write & (rd != 5'd0);
	assign source1 = (rs1 == 5'd0) ? 32'd0 : read1;
	assign source2 = (rs2 == 5'd0) ? 32'd0 : read2;

	reg_ram reg_ram1(CLK, we, rs1, read1, rd, dist1);
	reg_ram reg_ram2(CLK, we, rs2, read2, rd, dist1);

endmodule

module reg_ram(CLK, we, rs, source, rd, dist1);
	input CLK;
	input we;
	input [4:0] rs, rd;
	output [31:0] source;
	input [31:0] dist1;
	
	reg [31:0] mem [0:31];

	always @(posedge CLK) begin
		if(we) begin
			mem[rd] <= dist1;
		end
	end

	assign source = mem[rs];
endmodule
