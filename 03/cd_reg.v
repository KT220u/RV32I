module cd_reg(CLK, pcC, instC, stateC, pcD, instD, stateD,  stall, fail_predict);
	input CLK;
	input [12:0] pcC;
	input [31:0] instC;
	input [1:0] stateC;
	output reg [12:0] pcD;
	output reg [31:0] instD;
	output reg [1:0] stateD;
	input stall;
	input fail_predict;

	always @(posedge CLK) begin
		if(stall) begin
			pcD <= pcD;
			instD <= instD;
			stateD <= stateD;
		end else if(fail_predict) begin
			pcD <= 13'd0;
			instD <= 32'd0;
			stateD <= 2'd0;
		end else begin
			pcD <= pcC;
			instD <= instC;
			stateD <= stateC;
		end
	end
endmodule
		
