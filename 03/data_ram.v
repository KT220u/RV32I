`include "define.vh"

module data_ram(CLK, NRST, resultE1, resultE2, resultM1, resultM2, Source1, Source2, Dist1, Dist2, mem_store1, mem_store2, mem_load1, mem_load2, hc_OUT_data);
	input CLK, NRST;
	input [31:0] resultE1, resultE2, resultM1, resultM2;	// ALUの結果
	input [31:0] Source1, Source2;	// メモリに書き込むデータ
	output [31:0] Dist1, Dist2; // レジスタに書き込むデータ
	input [1:0] mem_store1, mem_store2; // 01:SB, 10:SH, 11:SW, 00:NotSTORE
	input [2:0] mem_load1, mem_load2;  // 001:LB, 010:LH, 011:LW, 100:LBU, 101:LHU 000:NotLOAD
	input [31:0] hc_OUT_data;

	wire [31:0] resultM;
	wire [31:0] Source;
	wire [1:0] mem_store;
	wire [1:0] offset1, offset2, offset;
	wire [31:0] store_data; // offset に応じて、書き込むデータをシフトさせる
	wire [3:0] store_flag; // ４バイトのどこに書き込むか

	assign resultM = (mem_store1 >= 2'b01) ? resultM1 : resultM2;
	assign Source = (mem_store1 >= 2'b01) ? Source1 : Source2;
	assign mem_store = mem_store1 | mem_store2; // どちらかは０なので、ORをとればOK
	assign offset1 = resultM1[1:0];
	assign offset2 = resultM2[1:0];
	assign offset = (mem_store >= 2'b01) ? offset1 : offset2;
	assign store_data = Source << {offset, 3'b000};
	assign store_flag = ((mem_store == 2'b11) ? 4'b1111 : 
						(mem_store == 2'b10) ? 4'b0011 : 
						(mem_store == 2'b01) ? 4'b0001 : 
						4'b0000) << offset;
	wire [31:0] r_data1, r_data2;
	wire [31:0] r_data1_true, r_data2_true;

	reg [15:2] resultM_before;
	reg [31:0] Source_before;
	reg [1:0] mem_store_before;
	wire load_after_store;


	always @(posedge CLK) begin
		Source_before<= Source;
		mem_store_before <= mem_store;
		resultM_before <= resultM;
	end

	// １つ前のストア命令の結果はメモリにはまだ書かれていないので、バッファから読み込む
	assign load_after_store = resultM_before[15:2] == resultM[15:2] & mem_store_before >= 2'b01;
	assign r_data1_true = (load_after_store) ? Source_before : r_data1; 
	assign r_data2_true = (load_after_store) ? Source_before : r_data2; 

	
	assign Dist1 = (mem_load1 == 3'b001) ? ((offset1== 2'b00) ? {{24{r_data1_true[7]}}, r_data1_true[7:0]} :
											  (offset1== 2'b01) ? {{24{r_data1_true[15]}}, r_data1_true[15:8]} :
											  (offset1== 2'b10) ? {{24{r_data1_true[23]}}, r_data1_true[23:16]} :
											  {{24{r_data1_true[31]}}, r_data1_true[31:24]}) : 
					   (mem_load1 == 3'b010) ? ((offset1== 2'b00) ? {{16{r_data1_true[15]}}, r_data1_true[15:0]} :
					   						  (offset1== 2'b01) ? {{16{r_data1_true[23]}}, r_data1_true[23:8]} :
					   						  (offset1== 2'b10) ? {{16{r_data1_true[31]}}, r_data1_true[31:16]} :
					   					      {{24{r_data1_true[31]}}, r_data1_true[31:24]}) :
					   (mem_load1 == 3'b011) ? (resultM1 == `HARDWARE_COUNTER_ADDR) ? hc_OUT_data : r_data1_true:
					   (mem_load1 == 3'b100) ? ((offset1== 2'b00) ? {24'd0, r_data1_true[7:0]} : 
					   						  (offset1== 2'b01) ? {24'd0, r_data1_true[15:8]} :  
					   						  (offset1== 2'b10) ? {24'd0, r_data1_true[23:16]} :  
					   						  {24'd0, r_data1_true[31:24]}) :  
					   (mem_load1 == 3'b101) ? ((offset1== 2'b00) ? {16'd0, r_data1_true[15:0]} :
					   						  (offset1== 2'b01) ? {16'd0, r_data1_true[23:8]} : 
					   						  (offset1== 2'b10) ? {16'd0, r_data1_true[31:16]} : 
					   						  {24'd0, r_data1_true[31:24]}) : 
					   resultM1;
	assign Dist2 = (mem_load2 == 3'b001) ? ((offset2== 2'b00) ? {{24{r_data2_true[7]}}, r_data2_true[7:0]} :
											  (offset2== 2'b01) ? {{24{r_data2_true[15]}}, r_data2_true[15:8]} :
											  (offset2== 2'b10) ? {{24{r_data2_true[23]}}, r_data2_true[23:16]} :
											  {{24{r_data2_true[31]}}, r_data2_true[31:24]}) : 
					   (mem_load2 == 3'b010) ? ((offset2== 2'b00) ? {{16{r_data2_true[15]}}, r_data2_true[15:0]} :
					   						  (offset2== 2'b01) ? {{16{r_data2_true[23]}}, r_data2_true[23:8]} :
					   						  (offset2== 2'b10) ? {{16{r_data2_true[31]}}, r_data2_true[31:16]} :
					   					      {{24{r_data2_true[31]}}, r_data2_true[31:24]}) :
					   (mem_load2 == 3'b011) ? (resultM2 == `HARDWARE_COUNTER_ADDR) ? hc_OUT_data : r_data2_true:
					   (mem_load2 == 3'b100) ? ((offset2== 2'b00) ? {24'd0, r_data2_true[7:0]} : 
					   						  (offset2== 2'b01) ? {24'd0, r_data2_true[15:8]} :  
					   						  (offset2== 2'b10) ? {24'd0, r_data2_true[23:16]} :  
					   						  {24'd0, r_data2_true[31:24]}) :  
					   (mem_load2 == 3'b101) ? ((offset2== 2'b00) ? {16'd0, r_data2_true[15:0]} :
					   						  (offset2== 2'b01) ? {16'd0, r_data2_true[23:8]} : 
					   						  (offset2== 2'b10) ? {16'd0, r_data2_true[31:16]} : 
					   						  {24'd0, r_data2_true[31:24]}) : 
					   resultM2;
	data_ram_block data_ram_block(CLK, resultE1[15:2], resultE2[15:2], r_data1, r_data2, resultM[15:2], store_data, store_flag);

endmodule

module data_ram_block(clk, r_addr1, r_addr2, r_data1, r_data2, w_addr, w_data, store_flag);
	input clk;
	input [13:0] r_addr1, r_addr2;
	output reg [31:0] r_data1, r_data2;
	input [13:0] w_addr;
	input [31:0] w_data;
	input [3:0] store_flag;

	reg [31:0] mem [0:16383];
	initial begin
		$readmemh("/home/denjo/RV32I/03/data.hex", mem);
	end

	always @(posedge clk) begin
		r_data1 <= mem[r_addr1];
		r_data2 <= mem[r_addr2];
	end
	
	always @(posedge clk) begin
		if(store_flag[0]) mem[w_addr][7:0] <= w_data[7:0];
		if(store_flag[1]) mem[w_addr][15:8] <= w_data[15:8];
		if(store_flag[2]) mem[w_addr][23:16] <= w_data[23:16];
		if(store_flag[3]) mem[w_addr][31:24] <= w_data[31:24];
	end
endmodule	
