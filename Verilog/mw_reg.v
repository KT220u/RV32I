module mw_reg(CLK, NRST, rdM, distM, reg_writeM, rdW, distW, reg_writeW);
	input CLK, NRST;
	input [4:0] rdM;
	input [31:0] distM;
	input reg_writeM;

	output reg [4:0] rdW;
	output reg [31:0] distW;
	output reg reg_writeW;

	always @(posedge CLK) begin
		if(!NRST) begin
			rdW <= 5'd0;
			distW <= 32'd0;
			reg_writeW <= 1'd0;
		end else begin
			rdW <= rdM;
			distW <= distM;
			reg_writeW <= reg_writeM;
		end
	end
endmodule
			
