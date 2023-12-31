// ２つの命令の依存関係をチェックする
// チェックすべきこと
// 1. inst1 が分岐命令
// 2. inst1 が reg_write かつ inst1 rd = inst2 rs1/rs2
// 3. inst1, inst2 ともにストア命令
// 4. inst1 : STORE, inst2 : LOAD
// 5. Fステージで命令１が分岐キャッシュヒット（この場合、命令２を遅らせるのではなく破棄する）
module check(CLK, NRST, pc1_in, pc2_in, inst1_in, inst2_in, state1_in, state2_in, pc1_out, pc2_out, inst1_out, inst2_out, state1_out, state2_out, is_depend, branch_numberD, stall, fail_predictD, fail_predictE, hit_predict1);
	input CLK, NRST;
	input [12:0] pc1_in, pc2_in;
	input [31:0] inst1_in, inst2_in;
	input [1:0] state1_in, state2_in;
	output [12:0] pc1_out, pc2_out;
	output [31:0] inst1_out, inst2_out;
	output [1:0] state1_out, state2_out;
	output is_depend;
	output reg [1:0] branch_numberD; // 01 : inst1 が分岐命令、10 : inst2 が分岐命令、00 : ともに分岐命令でない
									 // posedge CLK で、Dステージの d_calcpc に伝える。
	input stall;
	input fail_predictD, fail_predictE;
	input hit_predict1;

	wire [31:0] inst1, inst2;
	wire [12:0] pc1, pc2;
	wire [1:0] state1, state2;
	reg [31:0] inst2_buffer;
	reg [12:0] pc2_buffer;
	reg [1:0] state2_buffer;
	reg was_depend;
	wire [1:0] branch_numberC;

	// was_depend : １つ前のサイクルで依存があった
	// １つ前の inst2 をこのサイクルでの inst1 にする
	assign inst1 = (was_depend) ? inst2_buffer : inst1_in;
	assign inst2 = (was_depend) ? inst1_in : inst2_in;
	assign pc1 = (was_depend) ? pc2_buffer : pc1_in;
	assign pc2 = (was_depend) ? pc1_in : pc2_in;
	assign state1 = (was_depend) ? state2_buffer : state1_in;
	assign state2 = (was_depend) ? state1_in : state2_in;

	assign inst1_out = inst1;
	assign inst2_out = (!is_depend) ? inst2 : 32'd0;
	assign pc1_out = pc1;
	assign pc2_out = (!is_depend) ? pc2 : 13'd0;
	assign state1_out = state1;
	assign state2_out = (!is_depend) ? state2 : 2'd0;


	wire [4:0] opcode1, opcode2;	// opcode は上位５ビットで十分
	wire branch;
	wire reg_write;
	wire use_rs1, use_rs2;
	wire store1, store2, load2;
	wire [4:0] rs1, rs2, rd;
	

	assign opcode1 = inst1[6:2];
	assign opcode2 = inst2[6:2];

	assign branch = opcode1[4];
	assign reg_write = opcode1[0] | opcode1[2] | ~opcode1[3];
	assign use_rs1 = ~opcode2[0] | (~opcode2[1] & ~opcode2[1]);
	assign use_rs2 = ~opcode2[0] & opcode2[3];
	assign store1 = ~opcode1[4] & opcode1[3] & ~opcode1[2];
	assign store2 = ~opcode2[4] & opcode2[3] & ~opcode2[2];
	assign load2 = ~opcode2[3] & ~opcode2[0];

	assign rs1 = inst2[19:15];
	assign rs2 = inst2[24:20];
	assign rd = inst1[11:7];
	assign is_depend = ((reg_write & rd != 5'd0 & ((use_rs1 & (rs1 == rd)) | (use_rs2 & (rs2 == rd)))) |
						(branch) | 
						(store1 & store2) | 
						(store1 & load2)) 
						? (inst2 != 32'd0) ? 1'b1 : 1'b0 : 1'b0;
	assign branch_numberC = opcode1[4] ? 2'b01 : opcode2[4] ? 2'b10 : 2'b00;


	// 更新のやり方
	// 1, Eステージで予測ミス　：　ゼロリセット
	// 2. ストール ：　値そのまま
	// 3. Dステージで予測ミス　かつ　ストールでない　：　ゼロリセット
	//		Dステージでストールが発生している場合、予測ミス判定の結果は正しくないため。
	always @(posedge CLK) begin
		if(!NRST | fail_predictE | (fail_predictD & ~stall)) begin
			was_depend <= 1'b0;
			branch_numberD <= 2'b00;
			inst2_buffer <= 32'd0;
			pc2_buffer <= 13'd0;
			state2_buffer <= 2'd0;
		end else if(stall) begin
			was_depend <= was_depend;
			branch_numberD <= branch_numberD;
			inst2_buffer <= inst2_buffer;
			pc2_buffer <= pc2_buffer;
			state2_buffer <= state2_buffer;
		end else begin
			was_depend <= is_depend;
			branch_numberD <= branch_numberC;
			inst2_buffer <= inst2;
			pc2_buffer <= pc2;
			state2_buffer <= state2;
		end

//		inst2_buffer <= inst2;
//		pc2_buffer <= pc2;
	end

endmodule
