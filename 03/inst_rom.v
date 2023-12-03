module inst_rom(CLK, NRST, pc1, pc2, inst1, inst2, stall, fail_predictD, true_pcD, fail_predictE, true_pcE, hit_predict, is_depend);
	input CLK, NRST;
	output [12:0] pc1, pc2;
	output [31:0] inst1, inst2;

	assign pc1 = pc;
	assign pc2 = pc + 13'd1;

	input stall;
	input fail_predictD, fail_predictE;
	input [12:0] true_pcD, true_pcE;

	input hit_predict;
	input is_depend;

	// PCの更新パターン
	// 1. NRST
	// 2. stall
	// 3. 分岐予測失敗
	// 4. 命令１が分岐予測ヒット
	// 5. 命令２が分岐予測ヒット
	// 6. ２つの命令が依存
	// 7. その他

	reg [12:0] pc;
	wire [12:0] PC;
	assign PC = (stall) ? pc : 
				(fail_predictE) ? true_pcE :
				(fail_predictD) ? true_pcD :
				//(hit_predict) ? pre_pc :
				(is_depend) ? pc + 13'd1 :
				pc + 13'd2;

	always @(posedge CLK) begin
		if(!NRST) pc <= 13'd0;
		else pc <= PC;
	end

	inst_rom_block inst_rom_block(CLK, pc, pc + 13'd1, inst1, inst2);
endmodule

module inst_rom_block(clk, r_addr1, r_addr2, r_data1, r_data2);
	input clk;
	input [12:0] r_addr1, r_addr2;
	output reg [31:0] r_data1, r_data2;
	reg [31:0] mem [0:8191];
	initial begin
		$readmemh("/home/denjo/RV32I/03/code.hex", mem);
	end

	// negedgeで命令読み出し
	always @(negedge clk) begin
		r_data1 <= mem[r_addr1];
		r_data2 <= mem[r_addr2];
	end
endmodule
