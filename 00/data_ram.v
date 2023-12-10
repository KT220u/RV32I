`include "define.vh"

module data_ram(CLK, NRST, result, write_data, reg_data3, mem_store, mem_load, hc_OUT_data);
	input CLK, NRST;
	input [31:0] result;
	input [31:0] write_data;
	output [31:0] reg_data3;
	input [1:0] mem_store; // 00:SB, 01:SH, 10:SW
	input [2:0] mem_load;  // 000:LB, 001:LH, 010:LW, 011:LBU, 100:LHU 111:NotLOAD
	input [31:0] hc_OUT_data;
	
	// data memory
	wire [31:0] r_data;
	wire [31:0] w_data;
	wire store_enable;
	wire [1:0] word_offset;
	
	
	assign reg_data3 = (mem_load == 3'b000) ? ((word_offset == 2'b00) ? {{24{r_data[7]}}, r_data[7:0]} :
											  (word_offset == 2'b01) ? {{24{r_data[15]}}, r_data[15:8]} :
											  (word_offset == 2'b10) ? {{24{r_data[23]}}, r_data[23:16]} :
											  {{24{r_data[31]}}, r_data[31:24]}) : 
					   (mem_load == 3'b001) ? ((word_offset == 2'b00) ? {{16{r_data[15]}}, r_data[15:0]} :
					   						  (word_offset == 2'b01) ? {{16{r_data[23]}}, r_data[23:8]} :
					   						  (word_offset == 2'b10) ? {{16{r_data[31]}}, r_data[31:16]} :
					   					      {{24{r_data[31]}}, r_data[31:24]}) :
					   (mem_load == 3'b010) ? (result == `HARDWARE_COUNTER_ADDR) ? hc_OUT_data : r_data :
					   (mem_load == 3'b011) ? ((word_offset == 2'b00) ? {24'd0, r_data[7:0]} : 
					   						  (word_offset == 2'b01) ? {24'd0, r_data[15:8]} :  
					   						  (word_offset == 2'b10) ? {24'd0, r_data[23:16]} :  
					   						  {24'd0, r_data[31:24]}) :  
					   (mem_load == 3'b100) ? ((word_offset == 2'b00) ? {16'd0, r_data[15:0]} :
					   						  (word_offset == 2'b01) ? {16'd0, r_data[23:8]} : 
					   						  (word_offset == 2'b10) ? {16'd0, r_data[31:16]} : 
					   						  {24'd0, r_data[31:24]}) : 
					   result;
	
	// ストアのビット幅やアドレスの下２ビットに応じて書き込み３２ビット値を変える。
	assign w_data = (mem_store == 2'b00) ?  ((word_offset == 2'b00) ? {r_data[31:8], write_data[7:0]} : 
											(word_offset == 2'b01) ? {r_data[31:16], write_data[7:0], r_data[7:0]} :
											(word_offset == 2'b10) ? {r_data[31:24], write_data[7:0], r_data[15:0]} :
											{write_data[7:0], r_data[23:0]}) :
					(mem_store == 2'b01) ?  ((word_offset == 2'b00) ? {r_data[31:16], write_data[15:0]} :
											(word_offset == 2'b01) ? {r_data[31:24], write_data[15:0], r_data[7:0]} :
											(word_offset == 2'b10) ? {write_data[15:0], r_data[15:0]} :
											{write_data[7:0], r_data[23:0]}) :
					(mem_store == 2'b10) ? write_data[31:0] : 32'hffffffff;
	assign store_enable = (mem_store <= 2'b10) ? 1'b1 : 1'b0;
	assign word_offset = result[1:0];

	data_ram_block data_ram_block(CLK, store_enable, result[16:2], r_data, result[16:2], w_data); 
endmodule

module data_ram_block(clk, store_enable, r_addr, r_data, w_addr, w_data);
	input clk;
	input store_enable;
	input [14:0] r_addr, w_addr;
	input [31:0] w_data;
	output reg [31:0] r_data;
	reg [31:0] mem [0:32767];
	initial begin
		$readmemh("/home/denjo/RV32I/00/data.hex", mem);
	end
	always @(negedge clk) begin
		r_data <= mem[r_addr];
	end
	
	always @(posedge clk) begin
		if(store_enable == 1'b1) begin
			mem[w_addr] <= w_data;
		end
	end
endmodule
		
