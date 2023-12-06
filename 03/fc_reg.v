module fc_reg(CLK, NRST, pcF, instF, pcC, instC, stall, fail_predict, hit_predict1);
	input CLK;
	input NRST;
	input [12:0] pcF;
	input [31:0] instF;
	output reg [12:0] pcC;
	output reg [31:0] instC;
	input stall;
	input fail_predict;
	input hit_predict1;

	always @(posedge CLK) begin
		if(!NRST | fail_predict | (~stall & hit_predict1)) begin
			instC <= 32'd0;
			pcC <= 13'd0;
		end else begin
			instC <= (stall) ? instC : instF;
			pcC <= (stall) ? pcC : pcF;
		end
	end
endmodule
		
