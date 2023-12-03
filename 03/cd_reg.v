module cd_reg(CLK, pcC, instC, pcD, instD, stall, fail_predict);
	input CLK;
	input [12:0] pcC;
	input [31:0] instC;
	output reg [12:0] pcD;
	output reg [31:0] instD;
	input stall;
	input fail_predict;

	always @(posedge CLK) begin
		if(stall) begin
			pcD <= pcD;
			instD <= instD;
		end else if(fail_predict) begin
			pcD <= 13'd0;
			instD <= 32'd0;
		end else begin
			pcD <= pcC;
			instD <= instC;
		end
	end
endmodule
		
