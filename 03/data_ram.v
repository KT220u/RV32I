`include "define.vh"

// 2つの命令の関係性
// 1. ２つともSTORE : Cステージで検出し、2つ目を１サイクル遅らせてある。
// 2. 同じアドレスに対して、１つ目がLOAD、２つ目がSTORE : タイミング的に問題ない
// 3. 同じアドレスに対して、１つ目がSTORE、２つ目がLOAD : Cステージで検出、２つ目を１サイクル遅らせてある。 

module data_ram(CLK, NRST, resultE1, resultE2, resultM1, resultM2, Source1, Source2, Dist1, Dist2, mem_store1, mem_store2, mem_load1, mem_load2, hc_OUT_data);
	input CLK, NRST;
	input [31:0] resultE1, resultE2, resultM1, resultM2;	// ALUの結果
	input [31:0] Source1, Source2;	// レジスタから読んできたデータ
	output [31:0] Dist1, Dist2; // レジスタに書き込むデータ
	input [1:0] mem_store1, mem_store2; // 01:SB, 10:SH, 11:SW, 00:NotSTORE
	input [2:0] mem_load1, mem_load2;  // 001:LB, 010:LH, 011:LW, 100:LBU, 101:LHU 000:NotLOAD
	input [31:0] hc_OUT_data;
	
	wire [31:0] r_data1, r_data2;
	wire [31:0] w_data;

	wire [1:0] offset1, offset2;
	assign offset1 = resultM1[1:0];
	assign offset2 = resultM2[1:0];
	

	// どちらか一方の命令はストアの可能性があるので、それを判定する。
	// 両方ストアの場合は、Cステージで除外されている。
	wire [31:0] resultM;
	wire [31:0] Source;
	wire [1:0] mem_store;
	wire [1:0] offset;
	wire [31:0] r_data;
	wire [31:0] store_data; // メモリにストアするデータ
	wire store_en;	// STORE ENABLE
	
	assign resultM = (mem_store1 >= 2'b01) ? resultM1 : resultM2;
	assign Source = (mem_store1 >= 2'b01) ? Source1 : Source2;
	assign mem_store = mem_store1 | mem_store2; // どちらかは０なので、ORをとればOK
	assign offset = (mem_store1 >= 2'b01) ? resultM1[1:0] : resultM2[1:0];
	assign r_data = (mem_store1 >= 2'b01) ? r_data1 : r_data2;
	assign store_en = (mem_store >= 2'b01);


	// １サイクル前のSTOREの値をLOADするのは、メモリアクセスタイミング的にできないので、
	// バッファを用意しておく。
	reg [13:0] resultM_before;
	reg [31:0] store_data_before;
	reg [1:0] mem_store_before;
	wire load_after_store1, load_after_store2;
	assign load_after_store1 = (resultM_before == resultM1[15:2]) & (mem_store_before >= 2'b01);
	assign load_after_store2 = (resultM_before == resultM2[15:2]) & (mem_store_before >= 2'b01);

	always @(posedge CLK) begin
		store_data_before<= store_data;
		mem_store_before <= mem_store;
		resultM_before <= resultM[15:2];
	end

	// アドレスをもとに読み込んできたものが r_data1, r_data2 で、これに対して、
	// 上の２つのケースを考慮した読み込みデータが r_data1_ture, r_data2_true である。
	wire [31:0] r_data1_true, r_data2_true;
	assign r_data1_true = (load_after_store1) ? store_data_before : r_data1; 
	assign r_data2_true = (load_after_store2) ? store_data_before : r_data2; 
	
	// store_data 計算用に用いる r_data
	wire [31:0] r_data_true;
	assign r_data_true = (mem_store1 >=2'b01) ? r_data1_true : r_data2_true;

	assign store_data = (mem_store == 2'b01) ?  ((offset == 2'b00) ? {r_data_true[31:8], Source[7:0]} : 
											(offset == 2'b01) ? {r_data_true[31:16], Source[7:0],r_data_true[7:0]} :
											(offset == 2'b10) ? {r_data_true[31:24], Source[7:0],r_data_true[15:0]} :
											{Source[7:0],r_data_true[23:0]}) :
					(mem_store == 2'b10) ?  ((offset == 2'b00) ? {r_data_true[31:16], Source[15:0]} :
											(offset == 2'b01) ? {r_data_true[31:24], Source[15:0],r_data_true[7:0]} :
											(offset == 2'b10) ? { Source[15:0],r_data_true[15:0]} :
											{Source[7:0],r_data_true[23:0]}) :
					(mem_store == 2'b11) ? Source[31:0] : 32'hffffffff;
	

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
	data_ram_block data_ram_block(CLK, resultE1[15:2], resultE2[15:2], r_data1, r_data2, resultM[15:2], store_data, store_en);

endmodule

module data_ram_block(clk, r_addr1, r_addr2, r_data1, r_data2, w_addr, w_data, wen);
	input clk;
	input [13:0] r_addr1, r_addr2;
	output reg [31:0] r_data1, r_data2;
	input [13:0] w_addr;
	input [31:0] w_data;
	input wen;

	reg [31:0] mem [0:16383];
	initial begin
		$readmemh("/home/denjo/RV32I/03/data.hex", mem);
	end

	always @(posedge clk) begin
		r_data1 <= mem[r_addr1];
		r_data2 <= mem[r_addr2];
	end
	
	always @(posedge clk) begin
		if(wen) mem[w_addr] <= w_data;
	end
endmodule	
