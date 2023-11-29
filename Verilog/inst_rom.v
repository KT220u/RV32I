`include "define.vh"

module inst_rom(CLK, NRST, prepc, nextpc, pc, inst, stall, hit_predict, fail_predict);
	input CLK, NRST;
	
	// 分岐予測器による予測PC
	input [12:0] prepc;

	// 予測失敗時の次PC　Dステージでミス発覚 or Eステージでミス発覚
	// 分岐先キャッシュ読み出しは１クロック後から可能になる
	input [12:0] nextpc;

	// 読み出している命令に対応するPC
	output reg [12:0] pc;
	output [31:0] inst;

	// predict : 分岐キャッシュヒット
	// stall : ストール信号
	input stall;	
	input hit_predict;
	input fail_predict;
	
	wire fail_predict;

	parameter startpc = 0;

	// posedgeでPC更新
	// ストール時　PCを更新しない
	// 分岐予測ミス時　
	// 分岐キャッシュヒット時　
	// 分岐キャッシュミス時　PC+4
	
	wire [12:0] PC;
	assign PC = (stall) ? pc : (fail_predict) ? nextpc : (hit_predict) ? prepc : pc + 13'd1;

	always @(posedge CLK) begin
		if(!NRST) pc <= startpc;
		else pc <= PC;
	end

	inst_rom_block inst_rom_block(CLK, pc[12:0], inst);		//pcの下２ビットは除く
endmodule

module inst_rom_block(clk, r_addr, r_data);
	input clk;
	input [12:0] r_addr;
	output reg [31:0] r_data;
	reg [31:0] mem [0:8191];
	initial begin
		$readmemh("/home/denjo/RV32I/Verilog/code.hex", mem);
	end

	// negedgeで命令読み出し
	always @(negedge clk) begin
		r_data <= mem[r_addr];
	end
endmodule
