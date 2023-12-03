module fc_reg(CLK, NRST, pcF, instF, pcC, instC, stall);
	input CLK;
	input NRST;
	input [12:0] pcF;
	input [31:0] instF;
	output reg [12:0] pcC;
	output reg [31:0] instC;
	input stall;

	always @(posedge CLK) begin
		pcC <= pcF;
		if(!NRST) instC <= 32'd0;
		else instC <= (stall) ? instC : instF;

	end
endmodule
		
