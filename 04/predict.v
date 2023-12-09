// negedge CLK で、pc1, pc2 から hit_predict1, hit_predict2, pre_pc1, pre_pc2 を出力する。
// posedge CLK で、Eステージの e_calcpc から、w_data を書き込む
// 常に分岐する予測
module predict(CLK, pc1, pc2, hit_predict1, hit_predict2, state1, state2, pre_pc1, pre_pc2, w_data, w_addr, wen);
	input CLK;
	input [12:0] pc1, pc2;
	output hit_predict1, hit_predict2;
	output [1:0] state1, state2;
	output [12:0] pre_pc1, pre_pc2;
	
	// e_calcpc で計算されたデータを書き込む
	input [17:0] w_data;
	input [10:0] w_addr;
	input wen;

	// PCは0x8000 ~ 0x10000(15bit)で、さらに下２bitは無視できる
	// PC 13bitのうち、下11bitをインデックス、上2bitをタグとする
	// ダイレクトマップ型
	// 有効1bit, 状態2bit, タグ2bit, 値13bit

	wire [1:0] tag1, tag2;
	wire [10:0] r_addr1, r_addr2;
	wire [17:0] r_data1, r_data2;
	
	// 予測結果の読み出し
	assign tag1 = pc1[12:11];
	assign state1 = r_data1[16:15];
	assign r_addr1 = pc1[10:0];
	assign hit_predict1 = r_data1[17] & (r_data1[16:15] >= 2'b10) & (r_data1[14:13] == tag1);
	assign pre_pc1 = r_data1[12:0];
	
	assign tag2 = pc2[12:11];	
	assign state2 = r_data2[16:15];
	assign r_addr2 = pc2[10:0];
	assign hit_predict2 = r_data2[17] & (r_data2[16:15] >= 2'b10) & (r_data2[14:13] == tag2);
	assign pre_pc2 = r_data2[12:0];
	
	cache cache(CLK, r_addr1, r_addr2, r_data1, r_data2, w_addr, w_data, wen);

endmodule

module cache(CLK, r_addr1, r_addr2, r_data1, r_data2, w_addr, w_data, wen);
	input CLK;
	input [10:0] r_addr1, r_addr2;
	output reg [17:0] r_data1, r_data2;
	input [10:0] w_addr;
	input [17:0] w_data;
	input wen;

	always @(posedge CLK) begin
		if(wen) begin
			mem[w_addr] <= w_data;
		end
	end

	always @(negedge CLK) begin
		r_data1 <= mem[r_addr1];
		r_data2 <= mem[r_addr2];
	end
	
	reg [17:0] mem [0:2047];

	initial begin
		$readmemb("/home/denjo/RV32I/02/cache.hex", mem);
	end
endmodule

