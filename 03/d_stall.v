module d_stall(rs1D1, rs2D1, rs1D2, rs2D2, rdE1, rdE2, rdM1, rdM2, reg_writeE1, reg_writeE2, mem_loadE1,  mem_loadE2, mem_loadM1, mem_loadM2, branch_number, jump_codeD1, jump_codeD2, stall, cannot_calcpc);
	input [4:0] rs1D1, rs2D1, rs1D2, rs2D2, rdE1, rdE2, rdM1, rdM2;
	input reg_writeE1, reg_writeE2;
	input [2:0] mem_loadE1, mem_loadE2, mem_loadM1, mem_loadM2;
	input [1:0] branch_number;
	input [1:0] jump_codeD1, jump_codeD2;
	
	output stall;
	output cannot_calcpc;

	// ストールの条件　：　１つ前のステージがLOAD命令
	assign stall  = ((rs1D1 == rdE1 | rs2D1 == rdE1) & rdE1 != 5'd0 & reg_writeE1 & mem_loadE1 >= 3'b001) |
					((rs1D1 == rdE2 | rs2D1 == rdE2) & rdE2 != 5'd0 & reg_writeE2 & mem_loadE2 >= 3'b001) |
					((rs1D2 == rdE1 | rs2D2 == rdE1) & rdE1 != 5'd0 & reg_writeE1 & mem_loadE1 >= 3'b001) | 
					((rs1D2 == rdE2 | rs2D2 == rdE2) & rdE2 != 5'd0 & reg_writeE2 & mem_loadE2 >= 3'b001); 

	// DステージでPC計算ができない条件
	// 1. jalr 
		// 1.1 rs1D == rdE
		// 1.2 rs1D == rdM & mem_loadM (LOADでなければフォワーディングが可能）
	// 2. branch
		// 2.1 rs1D/rs2D == rdE
		// 2.2 rs1D/rs2D == rdM & mem_loadM
	assign cannot_calcpc = (branch_number[0] & (jump_codeD1 == 2'b11) & (rs1D1 == rdE1 | ((rs1D1 == rdM1) & mem_loadM1 >= 3'b001))) | 
						   (branch_number[1] & (jump_codeD2 == 2'b11) & (rs1D2 == rdE2 | ((rs1D2 == rdM2) & mem_loadM2 >= 3'b001))) |
						   (branch_number[0] & (jump_codeD1 == 2'b01) & (rs1D1 == rdE1 | rs2D1 == rdE1 | ((rs1D1 == rdM1 | rs2D1 == rdM1) & mem_loadM1 >= 3'b001))) | 
						   (branch_number[1] & (jump_codeD2 == 2'b01) & (rs1D2 == rdE2 | rs2D2 == rdE2 | ((rs1D2 == rdM2 | rs2D2 == rdM2) & mem_loadM2 >= 3'b001)));

endmodule
/*
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

	// jalr で rs1 が使えない（データハザード） or branch
	// クリティカルパス改善中

	assign cannot_calcpc = ((rs1D == rdE & rdE != 5'd0 & reg_writeE & jump_code == 2'b11) |
							(rs1D == rdM & rdM != 5'd0 & reg_writeM & jump_code == 2'b11) | 
							(jump_code == 2'b01)) ? 1'b1 : 1'b0;
	
	//assign cannot_calcpc = (jump_code == 2'b10) ? 1'b0 : 1'b1;

	// １つ前の命令がLOAD
	assign stall = ((rs1D == rdE | rs2D == rdE) & rdE != 5'd0 & mem_loadE >= 3'b001) ? 1'b1 : 1'b0;
endmodule

*/
