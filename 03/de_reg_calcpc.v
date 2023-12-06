module de_reg_calcpc(CLK, NRST, branch_numberD, pcDj, reg_data1Dj, reg_data2Dj, immDj, jump_codeDj, branch_codeDj, stateDj, 
								branch_numberE, pcEj, reg_data1Ej, reg_data2Ej, immEj, jump_codeEj, branch_codeEj, stateEj, stall, fail_predict);
	input CLK, NRST;
	input [1:0] branch_numberD;
	input [12:0] pcDj;
	input [31:0] reg_data1Dj, reg_data2Dj;
	input [12:0] immDj;
	input [1:0] jump_codeDj;
	input [2:0] branch_codeDj;
	input [1:0] stateDj;
	output reg [1:0] branch_numberE;
	output reg [12:0] pcEj;
	output reg [31:0] reg_data1Ej, reg_data2Ej;
	output reg [12:0] immEj;
	output reg [1:0] jump_codeEj;
	output reg [2:0] branch_codeEj;
	output reg [1:0] stateEj;

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
		reg_data1Ej <= reg_data1Dj;
		reg_data2Ej <= reg_data2Dj;
		immEj <= immDj;
		stateEj <= stateDj;
	end
endmodule

