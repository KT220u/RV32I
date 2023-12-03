module de_reg_calcpc(CLK, NRST, branch_numberD, pcDj, immDj, jump_codeDj, branch_codeDj,
								branch_numberE, pcEj, immEj, jump_codeEj, branch_codeEj, stall, fail_predict);
	input CLK, NRST;
	input [1:0] branch_numberD;
	input [12:0] pcDj;
	input [12:0] immDj;
	input [1:0] jump_codeDj;
	input [2:0] branch_codeDj;
	output reg [1:0] branch_numberE;
	output reg [12:0] pcEj;
	output reg [12:0] immEj;
	output reg [1:0] jump_codeEj;
	output reg [2:0] branch_codeEj;

	input stall;
	input fail_predict;

	always @(posedge CLK) begin
		if(stall | fail_predict) begin
			jump_codeEj <= 2'b00;
			branch_codeEj <= 3'b000;
		end else begin
			jump_codeEj <= jump_codeDj;
			branch_codeEj <= branch_codeDj;
		end
		branch_numberE <= branch_numberD;
		pcEj <= pcDj;
		immEj <= immDj;
	end
endmodule

