// ２つの命令の依存関係をチェックする
// チェックすべきこと
// 1. inst1 が分岐命令
// 2. inst1 が reg_write かつ inst1 rd = inst2 rs1/rs2
// 3. inst1, inst2 ともにストア命令
module check(CLK, NRST, pc1_in, pc2_in, inst1_in, inst2_in, pc1_out, pc2_out, inst1_out, inst2_out, is_depend, inst_numberD, stall);
	input CLK, NRST;
	input [12:0] pc1_in, pc2_in;
	input [31:0] inst1_in, inst2_in;
	output [12:0] pc1_out, pc2_out;
	output [31:0] inst1_out, inst2_out;
	output is_depend;
	output reg inst_numberD;
	input stall;

	wire [31:0] inst1, inst2;
	wire [12:0] pc1, pc2;
	reg [31:0] inst2_buffer;
	reg [12:0] pc2_buffer;
	reg was_depend;
	wire inst_numberC;

	// was_depend : １つ前のサイクルで依存があった
	// １つ前の inst2 をこのサイクルでの inst1 にする
	assign inst1 = (was_depend) ? inst2_buffer : inst1_in;
	assign inst2 = (was_depend) ? inst1_in : inst2_in;
	assign pc1 = (was_depend) ? pc2_buffer : pc1_in;
	assign pc2 = (was_depend) ? pc1_in : pc2_in;

	assign inst1_out = inst1;
	assign inst2_out = (!is_depend) ? inst2 : 32'd0;
	assign pc1_out = pc1;
	assign pc2_out = (!is_depend) ? pc2 : 13'd0;


	wire [4:0] opcode1, opcode2;	// opcode は上位５ビットで十分
	wire branch;
	wire reg_write;
	wire use_rs1, use_rs2;
	wire store1, store2;
	wire [4:0] rs1, rs2, rd;
	

	assign opcode1 = inst1[6:2];
	assign opcode2 = inst2[6:2];

	assign branch = opcode1[4];
	assign reg_write = opcode1[0] | opcode1[2] | ~opcode1[3];
	assign use_rs1 = ~opcode2[0] | (~opcode2[3] & ~opcode2[4]);
	assign use_rs2 = ~opcode2[0] & opcode2[3];
	assign store1 = ~opcode1[4] & opcode1[3] & ~opcode1[2];
	assign store2 = ~opcode2[4] & opcode2[3] & ~opcode2[2];

	assign rs1 = inst2[19:15];
	assign rs2 = inst2[24:20];
	assign rd = inst1[11:7];
	assign is_depend = ((reg_write & rd != 5'd0 & ((use_rs1 & (rs1 == rd)) | (use_rs2 & (rs2 == rd)))) |
						(branch) | 
						(store1 & store2)) ? 1'b1 : 1'b0;
	assign inst_numberC = !branch;

	always @(posedge CLK) begin
		if(!NRST) was_depend <= 1'b0;
		else if(stall) was_depend <= was_depend;
		else was_depend <= is_depend;

		inst2_buffer <= inst2;
		pc2_buffer <= pc2;

		inst_numberD <= inst_numberC;
	end

endmodule
