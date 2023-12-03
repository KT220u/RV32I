module em_reg(CLK, pcE, instE, rdE, resultE, reg_data2E, mem_storeE, mem_loadE, reg_writeE,
				   pcM, instM, rdM, resultM, reg_data2M, mem_storeM, mem_loadM, reg_writeM);
	input CLK;
	input [12:0] pcE;
	input [31:0] instE;
	input [4:0] rdE;
	input [31:0] resultE, reg_data2E;
	input [1:0] mem_storeE;
	input [2:0] mem_loadE;
	input reg_writeE;
	output reg [12:0] pcM;
	output reg [31:0] instM;
	output reg [4:0] rdM;
	output reg [31:0] resultM, reg_data2M;
	output reg [1:0] mem_storeM;
	output reg [2:0] mem_loadM;
	output reg reg_writeM;


	always @(posedge CLK) begin
		pcM <= pcE;
		instM <= instE;
		rdM <= rdE;
		resultM <= resultE;
		reg_data2M <= reg_data2E;
		mem_storeM <= mem_storeE;
		mem_loadM <= mem_loadE;
		reg_writeM <= reg_writeE;
	end
endmodule
