module cd_reg(CLK, pcC, instC, pcD, instD, stall);
	input CLK;
	input [12:0] pcC;
	input [31:0] instC;
	output reg [12:0] pcD;
	output reg [31:0] instD;
	input stall;

	always @(posedge CLK) begin
		if(stall) begin
			pcD <= pcD;
			instD <= instD;
		end else begin
			pcD <= pcC;
			instD <= instC;
		end
	end
endmodule
		
