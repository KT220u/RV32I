module em_reg(CLK, NRST, pcE, instE, rdE, resultE, store_dataE, mem_storeE, mem_loadE, reg_writeE, pcM, instM, rdM, resultM, store_dataM, mem_storeM, mem_loadM, reg_writeM);
	input CLK, NRST;
	input [12:0] pcE;
	input [31:0] instE;
	input [4:0] rdE;
	input [31:0] resultE, store_dataE; 
	input [1:0] mem_storeE;
	input [2:0] mem_loadE;
	input reg_writeE;

	output reg [12:0] pcM;
	output reg [31:0] instM;
	output reg [4:0] rdM;
	output reg [31:0] resultM, store_dataM; 
	output reg [1:0] mem_storeM;
	output reg [2:0] mem_loadM;
	output reg reg_writeM;

	always @(posedge CLK) begin
		if(!NRST) begin
			pcM <= 13'd0;
			instM <= 32'd0;
			rdM <= 5'd0;
			resultM <= 32'd0;
			store_dataM <= 32'd0;
			mem_storeM <= 2'd0;
			mem_loadM <= 3'd0;
			reg_writeM <= 1'd0;
		end else begin
			pcM <= pcE;
			instM <= instE;
			rdM <= rdE;
			resultM <= resultE;
			store_dataM <= store_dataE;
			mem_storeM <= mem_storeE;
			mem_loadM <= mem_loadE;
			reg_writeM <= reg_writeE;
		end
	end
endmodule
