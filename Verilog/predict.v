module predict(CLK, pcF, prepc, hit_predict, pcD, nextpcD, fail_predictD, pcE, nextpcE, fail_predictE, nextpc, fail_predict);
	input CLK;
	input [31:0] pcF;
	output [31:0] prepc;
	output hit_predict;
	input [31:0] pcD, nextpcD;
	input fail_predictD;
	input [31:0] pcE, nextpcE;
	input fail_predictE;

	// DとEどちらかのnextpcを採用し、inst_romに送る
	output [31:0] nextpc;
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
	wire [12:0] prepc_13bit;
	
	// 予測結果の読み出し
	assign tag = pcF[14:13];
	assign r_addr = pcF[12:2];
	assign hit_predict = (r_data[15] & r_data[14:13] == tag) ? 1'b1 : 1'b0;
	assign prepc_13bit = r_data[12:0];
	assign prepc = {16'd0, 1'b1, prepc_13bit, 2'd0};
	
	// Dステージ、またはEステージで予測ミスが発覚したら、その分岐先結果をキャッシュに書き込む
	wire [10:0] w_addr;
	wire [15:0] w_data;
	wire wen;
	wire [12:0] new_pc;
	wire [12:0] new_nextpc;
	
	assign new_pc = (fail_predictD) ? pcD[14:2] : pcE[14:2];
	assign new_nextpc = (fail_predictD) ? nextpcD[14:2] : nextpcE[14:2];
	assign w_addr = new_pc[10:0];
	assign w_data = {1'b1, new_pc[12:11], new_nextpc};
	assign wen = fail_predictD | fail_predictE;

	cache cache(CLK, r_addr, r_data, w_addr, w_data, wen);

endmodule

module cache(CLK, r_addr, r_data, w_addr, w_data, wen);
	input CLK;
	input [10:0] r_addr, w_addr;
	output [15:0] r_data;
	input [15:0] w_data;
	input wen;
	
	always @(posedge CLK) begin
		if(wen) begin
			mem[w_addr] <= w_data;
		end
	end
	assign r_data = mem[r_addr];

	reg [15:0] mem [0:2047];
endmodule

