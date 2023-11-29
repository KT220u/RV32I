module predict(CLK, pcF, prepc, hit_predict, pcD, nextpcD, fail_predictD, pcE, nextpcE, fail_predictE, nextpc, fail_predict, w_data, w_addr, wen);
	input CLK;
	input [12:0] pcF;
	output [12:0] prepc;
	output hit_predict;

	input [12:0] pcD, nextpcD;
	input fail_predictD;
	input [12:0] pcE, nextpcE;
	input fail_predictE;

	// DとEどちらかのnextpcを採用し、inst_romに送る
	output [12:0] nextpc;
	output fail_predict;
	
	assign nextpc = (fail_predictE) ? nextpcE : nextpcD;
	assign fail_predict = fail_predictD | fail_predictE;

	// PCは0x8000 ~ 0x10000(15bit)で、さらに下２bitは無視できる
	// PC 13bitのうち、下11bitをインデックス、上2bitをタグとする
	// ダイレクトマップ型
	// 有効1bit, タグ2bit, 値13bit

	wire [1:0] tag;
	wire [10:0] r_addr;
	wire [15:0] r_data;
	
	// 予測結果の読み出し
	assign tag = pcF[12:11];
	assign r_addr = pcF[10:0];
	assign hit_predict = (r_data[15] & r_data[14:13] == tag) ? 1'b1 : 1'b0;
	assign prepc = r_data[12:0];
	
	// e_calcpc で計算されたデータを書き込む
	input [10:0] w_addr;
	input [15:0] w_data;
	input wen;

	cache cache(CLK, r_addr, r_data, w_addr, w_data, wen);

endmodule

module cache(CLK, r_addr, r_data, w_addr, w_data, wen);
	input CLK;
	input [10:0] r_addr, w_addr;
	output reg [15:0] r_data;
	input [15:0] w_data;
	input wen;

	always @(posedge CLK) begin
		if(wen) begin
			mem[w_addr] <= w_data;
		end
	end

	always @(negedge CLK) begin
		r_data <= mem[r_addr];
	end
	
	reg [15:0] mem [0:2047];

	initial begin
		$readmemb("/home/denjo/RV32I/Verilog/cache.hex", mem);
	end
endmodule

