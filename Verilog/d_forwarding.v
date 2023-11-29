module d_forwarding(rs1D, rs2D, source1D, source2D, rdE, rdM, resultM, reg_writeE, mem_loadE, reg_writeM, mem_loadM, reg_data1D, reg_data2D, jump_code,  cannot_calcpc, stall);
	input [4:0] rs1D, rs2D;
	input [31:0] source1D, source2D;
	input [4:0] rdE, rdM;
	input [31:0] resultM;
	input reg_writeE, reg_writeM;
	input [2:0] mem_loadE, mem_loadM;
	output [31:0] reg_data1D, reg_data2D;
	
	input [1:0] jump_code;

	// データハザードにより、分岐先アドレス計算ができない
	output cannot_calcpc;
	// データハザードにより、Eステージで演算ができない
	output stall;

	// ２つ前の命令がLOAD命令でない場合、フォワーディング可能
	assign reg_data1D = (rs1D == rdM & rdM != 5'd0 & mem_loadM == 3'b000 & reg_writeM) ? resultM : source1D;
	assign reg_data2D = (rs2D == rdM & rdM != 5'd0 & mem_loadM == 3'b000 & reg_writeM) ? resultM : source2D;

	// １つ前の命令 or ２つ前の命令がLOAD
	// jalr では rs1 が必要
	// branch では rs1, rs2 が必要
	assign cannot_calcpc = (((rs1D == rdE | rs2D == rdE) & rdE != 5'd0 & reg_writeE & jump_code == 2'b01) | 
							 ( rs1D == rdE & rdE != 5'd0 & reg_writeE & jump_code == 2'b11) |
							 ((rs1D == rdM | rs2D == rdM) & rdM != 5'd0 & mem_loadM >= 3'b001 & jump_code == 2'b01) | 
							 ( rs1D == rdM  & rdM != 5'd0 & mem_loadM >= 3'b001 & jump_code == 2'b11)) ? 1'b1 : 1'b0;

	// １つ前の命令がLOAD
	assign stall = ((rs1D == rdE | rs2D == rdE) & rdE != 5'd0 & mem_loadE >= 3'b001) ? 1'b1 : 1'b0;
endmodule

