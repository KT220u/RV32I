module regfile(CLK, rs11, rs21, rs12, rs22, source11, source21, source12, source22, rd1, rd2, dist1, dist2, reg_write1, reg_write2);
	input CLK;
	input [4:0] rs11, rs21, rs12, rs22;
	output [31:0] source11, source21, source12, source22;
	input [4:0] rd1, rd2;
	input [31:0] dist1, dist2;
	input reg_write1, reg_write2;
	
	wire we1, we2;
	wire [31:0] read11, read21, read12, read22;
	
	assign we1 = reg_write1 & (rd1 != 5'd0);
	assign we2 = reg_write2 & (rd2 != 5'd0) & (rd1 != rd2);
	assign source11 = (rs11 == 5'd0) ? 32'd0 : read11;
	assign source21 = (rs21 == 5'd0) ? 32'd0 : read21;
	assign source12 = (rs12 == 5'd0) ? 32'd0 : read12;
	assign source22 = (rs22 == 5'd0) ? 32'd0 : read22;

	reg_ram reg_ram(CLK, rs11, rs21, rs12, rs22, read11, read21, read12, read22, rd1, rd2, dist1, dist2, we1, we2);

endmodule

// XPR based multiport memory
module reg_ram(CLK, r_addr1, r_addr2, r_addr3, r_addr4, r_data1, r_data2, r_data3, r_data4, w_addr1, w_addr2, w_data1, w_data2, we1, we2 );
	input CLK;
	input [4:0] r_addr1, r_addr2, r_addr3, r_addr4;
	output [31:0] r_data1, r_data2, r_data3, r_data4;
	input [4:0] w_addr1, w_addr2;
	input [31:0] w_data1, w_data2;
	input we1, we2;
	
	reg [31:0] mem1 [0:31];
	reg [31:0] mem2 [0:31];

	always @(posedge CLK) begin
		if(we1) begin
			mem1[w_addr1] <= w_data1 ^ mem2[w_addr1];
		end
		if(we2) begin
			mem2[w_addr2] <= w_data2 ^ mem1[w_addr2];
		end
	end

	initial begin
		$readmemh("init_reg.hex", mem1);
		$readmemh("init_reg.hex", mem2);
	end

	assign r_data1 = mem1[r_addr1] ^ mem2[r_addr1];
	assign r_data2 = mem1[r_addr2] ^ mem2[r_addr2];
	assign r_data3 = mem1[r_addr3] ^ mem2[r_addr3];
	assign r_data4 = mem1[r_addr4] ^ mem2[r_addr4];
endmodule
