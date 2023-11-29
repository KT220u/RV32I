module e_forwarding(rs1E, rs2E, source1E, source2E, rdM, resultM, rdW, distW, reg_writeM, mem_loadM, reg_writeW, reg_data1E, reg_data2E);
	input [4:0] rs1E, rs2E;
	input [31:0] source1E, source2E;
	input [4:0] rdM;
	input [31:0] resultM;
	input [4:0] rdW;
	input [31:0] distW;
	input reg_writeM;
	input [2:0] mem_loadM;
	input reg_writeW;

	output [31:0] reg_data1E, reg_data2E;

	// とりあえず
	assign reg_data1E = (rs1E == rdM & rdM != 5'd0 & reg_writeM & mem_loadM == 3'b000) ? resultM : 
						(rs1E == rdW & rdW != 5'd0 & reg_writeW) ? distW : source1E;
	assign reg_data2E = (rs2E == rdM & rdM != 5'd0 & reg_writeM & mem_loadM == 3'b000) ? resultM : 
						(rs2E == rdW & rdW != 5'd0 & reg_writeW) ? distW : source2E;
endmodule
