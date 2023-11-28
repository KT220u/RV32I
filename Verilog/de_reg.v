module de_reg(CLK, NRST, pcD, instD, rs1D, rs2D, rdD, source1D, source2D, immD, alu_codeD, alu_srcD, jump_codeD, branch_codeD, mem_storeD, mem_loadD, reg_writeD, cannot_predictD, 
		pcE, instE, rs1E, rs2E, rdE, source1E, source2E, immE, alu_codeE, alu_srcE, jump_codeE, branch_codeE, mem_storeE, mem_loadE, reg_writeE, cannot_predictE, stall, fail_predictE, nextpc);
	input CLK, NRST;
	input [12:0] pcD;
	input [31:0] instD;
	input [4:0] rs1D, rs2D, rdD;
	input [31:0] source1D, source2D, immD;
	input [5:0] alu_codeD;
	input alu_srcD;
	input [1:0] jump_codeD;
	input [2:0] branch_codeD;
	input [1:0] mem_storeD;
	input [2:0] mem_loadD;
	input reg_writeD;
	input cannot_predictD;
	
	output reg [12:0] pcE;
	output reg [31:0] instE;
	output reg [4:0] rs1E, rs2E, rdE;
	output reg [31:0] source1E, source2E, immE;
	output reg [5:0] alu_codeE;
	output reg alu_srcE;
	output reg [1:0] jump_codeE;
	output reg [2:0] branch_codeE;
	output reg [1:0] mem_storeE;
	output reg [2:0] mem_loadE;
	output reg  reg_writeE;
	output reg cannot_predictE;

	input stall;
	input fail_predictE;
	input [12:0] nextpc;

	always @(posedge CLK) begin
		if(!NRST) begin
			pcE <= 13'd0;
			instE <= 32'd0;
			rs1E <= 5'd0; 
			rs2E <= 5'd0;
			rdE <= 5'd0;
			source1E <= 32'd0;
			source2E <= 32'd0;
			immE <= 32'd0;
			alu_codeE <= 6'd0;
			alu_srcE <= 1'd0;
			jump_codeE <= 2'd0;
			branch_codeE <= 3'd0;
			mem_storeE <= 2'd0;
			mem_loadE <= 3'd0;
			reg_writeE <= 1'd0;
			cannot_predictE <= 1'b0;
		end else begin
			if(fail_predictE) begin
				instE <= 32'd0;
				pcE <= nextpc - 13'd2;	// 分岐予測ミス時は、新しいPC-2として、予測ミス判定となってしまうのを防ぐ。
			end else begin
				instE <= instD;
				pcE <= pcD;
			end
			rs1E <= rs1D; 
			rs2E <= rs2D;
			rdE <= rdD;
			source1E <= source1D;
			source2E <= source2D;
			immE <= immD;
			// stall or 分岐予測ミス時は、制御信号をすべて０にする
			if(stall | fail_predictE) begin
				alu_codeE <= 6'd0;
				alu_srcE <= 1'd0;
				jump_codeE <= 2'd0;
				branch_codeE <= 3'd0;
				mem_storeE <= 2'd0;
				mem_loadE <= 3'd0;
				reg_writeE <= 1'd0;
				cannot_predictE <= 1'b0;
			end else begin	
				alu_codeE <= alu_codeD;
				alu_srcE <= alu_srcD;
				jump_codeE <= jump_codeD;
				branch_codeE <= branch_codeD;
				mem_storeE <= mem_storeD;
				mem_loadE <= mem_loadD;
				reg_writeE <= reg_writeD;
				cannot_predictE <= cannot_predictD;
			end
		end
	end
endmodule
