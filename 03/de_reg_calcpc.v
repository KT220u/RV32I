module de_reg_calcpc(CLK, NRST, inst_numberD, pcDj, immDj, jump_codeDj, branch_codeDj,
								inst_numberE, pcEj, immEj, jump_codeEj, branch_codeEj, stall);
	input CLK, NRST;
	input inst_numberD;
	input [12:0] pcDj;
	input [12:0] immDj;
	input [1:0] jump_codeDj;
	input [2:0] branch_codeDj;
	output reg inst_numberE;
	output reg [12:0] pcEj;
	output reg [12:0] immEj;
	output reg [1:0] jump_codeEj;
	output reg [2:0] branch_codeEj;

	input stall;

	always @(posedge CLK) begin
		if(stall) begin
			jump_codeEj <= 2'b00;
			branch_codeEj <= 3'b000;
		end else begin
			jump_codeEj <= jump_codeDj;
			branch_codeEj <= branch_codeDj;
		end
		inst_numberE <= inst_numberD;
		pcEj <= pcDj;
		immEj <= immDj;
	end
endmodule

