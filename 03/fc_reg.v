module fc_reg(CLK, NRST, pcF, instF, stateF, pcC, instC, stateC, stall, fail_predict, hit_predict1);
	input CLK;
	input NRST;
	input [12:0] pcF;
	input [31:0] instF;
	input [1:0] stateF;
	output reg [12:0] pcC;
	output reg [31:0] instC;
	output reg [1:0] stateC;
	input stall;
	input fail_predict;
	input hit_predict1;

	always @(posedge CLK) begin
		if(!NRST | fail_predict | (~stall & hit_predict1)) begin
			instC <= 32'd0;
			pcC <= 13'd0;
			stateC <= 2'b00;
		end else begin
			instC <= (stall) ? instC : instF;
			pcC <= (stall) ? pcC : pcF;
			stateC <= (stall) ? stateC : stateF;
		end
	end
endmodule
		
