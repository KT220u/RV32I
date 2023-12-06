module d_forwarding(rs1D, rs2D, source1D, source2D, rdM, resultM, reg_writeM, mem_loadM, reg_data1D, reg_data2D);
	input [4:0] rs1D, rs2D;
	input [31:0] source1D, source2D;
	input [4:0] rdM;
	input [31:0] resultM;
	input reg_writeM;
	input [2:0] mem_loadM;
	output [31:0] reg_data1D, reg_data2D;

	// ２つ前の命令をフォワーディングしてくる。
	assign reg_data1D = (rs1D == rdM & rdM != 5'd0 & mem_loadM == 3'b000 & reg_writeM) ? resultM : source1D;
	assign reg_data2D = (rs2D == rdM & rdM != 5'd0 & mem_loadM == 3'b000 & reg_writeM) ? resultM : source2D;

endmodule


