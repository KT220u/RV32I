`include "define.vh"

module data_ram(CLK, NRST, resultE, resultM, write_data, dist1, mem_store, mem_load, hc_OUT_data);
	input CLK, NRST;
	input [31:0] resultE, resultM;
	input [31:0] write_data;
	output [31:0] dist1;
	input [1:0] mem_store; // 01:SB, 10:SH, 11:SW, 00:NotSTORE
	input [2:0] mem_load;  // 001:LB, 010:LH, 011:LW, 100:LBU, 101:LHU 000:NotLOAD
	input [31:0] hc_OUT_data;
	
	// data memory
	wire [31:0] r_data;
	wire [31:0] w_data;
	wire store_enable;
	wire [1:0] word_offset;
	
	wire [31:0] r_data0;
	reg [31:0] w_data0;
	reg [1:0] mem_store0;
	reg [31:0] resultW;
	always @(posedge CLK) begin
		w_data0 <= w_data;
		mem_store0 <= mem_store;
		resultW <= resultM;
	end

	assign r_data = (resultW[15:2] == resultM[15:2] & mem_store0 >= 2'b01) ? w_data0 : r_data0;

	
	assign dist1 = (mem_load == 3'b001) ? ((word_offset == 2'b00) ? {{24{r_data[7]}}, r_data[7:0]} :
											  (word_offset == 2'b01) ? {{24{r_data[15]}}, r_data[15:8]} :
											  (word_offset == 2'b10) ? {{24{r_data[23]}}, r_data[23:16]} :
											  {{24{r_data[31]}}, r_data[31:24]}) : 
					   (mem_load == 3'b010) ? ((word_offset == 2'b00) ? {{16{r_data[15]}}, r_data[15:0]} :
					   						  (word_offset == 2'b01) ? {{16{r_data[23]}}, r_data[23:8]} :
					   						  (word_offset == 2'b10) ? {{16{r_data[31]}}, r_data[31:16]} :
					   					      {{24{r_data[31]}}, r_data[31:24]}) :
					   (mem_load == 3'b011) ? (resultM == `HARDWARE_COUNTER_ADDR) ? hc_OUT_data : r_data :
					   (mem_load == 3'b100) ? ((word_offset == 2'b00) ? {24'd0, r_data[7:0]} : 
					   						  (word_offset == 2'b01) ? {24'd0, r_data[15:8]} :  
					   						  (word_offset == 2'b10) ? {24'd0, r_data[23:16]} :  
					   						  {24'd0, r_data[31:24]}) :  
					   (mem_load == 3'b101) ? ((word_offset == 2'b00) ? {16'd0, r_data[15:0]} :
					   						  (word_offset == 2'b01) ? {16'd0, r_data[23:8]} : 
					   						  (word_offset == 2'b10) ? {16'd0, r_data[31:16]} : 
					   						  {24'd0, r_data[31:24]}) : 
					   resultM;
	
	// ストアのビット幅やアドレスの下２ビットに応じて書き込み３２ビット値を変える。
	assign w_data = (mem_store == 2'b01) ?  ((word_offset == 2'b00) ? {r_data[31:8], write_data[7:0]} : 
											(word_offset == 2'b01) ? {r_data[31:16], write_data[7:0], r_data[7:0]} :
											(word_offset == 2'b10) ? {r_data[31:24], write_data[7:0], r_data[15:0]} :
											{write_data[7:0], r_data[23:0]}) :
					(mem_store == 2'b10) ?  ((word_offset == 2'b00) ? {r_data[31:16], write_data[15:0]} :
											(word_offset == 2'b01) ? {r_data[31:24], write_data[15:0], r_data[7:0]} :
											(word_offset == 2'b10) ? {write_data[15:0], r_data[15:0]} :
											{write_data[7:0], r_data[23:0]}) :
					(mem_store == 2'b11) ? write_data[31:0] : 32'hffffffff;
	assign store_enable = (mem_store >= 2'b01) ? 1'b1 : 1'b0;
	assign word_offset = resultM[1:0];

	data_ram_block data_ram_block(CLK, store_enable, resultE[15:2], r_data0, resultM[15:2], w_data); 
endmodule

module data_ram_block(clk, store_enable, r_addr, r_data, w_addr, w_data);
	input clk;
	input store_enable;
	input [13:0] r_addr, w_addr;
	input [31:0] w_data;
	output reg [31:0] r_data;
	reg [31:0] mem [0:16383];
	initial begin
		$readmemh("/home/denjo/RV32I/Verilog/data.hex", mem);
	end
	always @(posedge clk) begin
		r_data <= mem[r_addr];
	end
	
	always @(posedge clk) begin
		if(store_enable == 1'b1) begin
			mem[w_addr] <= w_data;
		end
	end
endmodule
		
