module e_forwarding(rs1E, rs2E, source1E, source2E, rdM1, resultM1, rdW1, distW1, reg_writeM1, mem_loadM1, reg_writeW1, reg_data1E, reg_data2E,
													rdM2, resultM2, rdW2, distW2, reg_writeM2, mem_loadM2, reg_writeW2);
	input [4:0] rs1E, rs2E;
	input [31:0] source1E, source2E;
	input [4:0] rdM1, rdM2;
	input [31:0] resultM1, resultM2;
	input [4:0] rdW1, rdW2;
	input [31:0] distW1, distW2;
	input reg_writeM1, reg_writeM2;
	input [2:0] mem_loadM1, mem_loadM2;
	input reg_writeW1, reg_writeW2;

	output [31:0] reg_data1E, reg_data2E;

	// とりあえず
	assign reg_data1E = (rs1E == rdM2 & rdM2 != 5'd0 & reg_writeM2 & mem_loadM2 == 3'b000) ? resultM2 : 
						(rs1E == rdM1 & rdM1 != 5'd0 & reg_writeM1 & mem_loadM1 == 3'b000) ? resultM1 :
						(rs1E == rdW2 & rdW2 != 5'd0 & reg_writeW2) ? distW2 : 
						(rs1E == rdW1 & rdW1 != 5'd0 & reg_writeW1) ? distW1 : source1E;
	assign reg_data2E = (rs2E == rdM2 & rdM2 != 5'd0 & reg_writeM2 & mem_loadM2 == 3'b000) ? resultM2 : 
						(rs2E == rdM1 & rdM1 != 5'd0 & reg_writeM1 & mem_loadM1 == 3'b000) ? resultM1 :
						(rs2E == rdW2 & rdW2 != 5'd0 & reg_writeW2) ? distW2 : 
						(rs2E == rdW1 & rdW1 != 5'd0 & reg_writeW1) ? distW1 : source2E;
endmodule
