module test;

	reg CLK;
	reg NRST;
	
	wire uart_tx;
	
	always begin
		#10 CLK <= ~CLK;	
	end

	// trace format
	always begin
		#20  if(top.reg_writeM1 == 1 & top.mem_loadM1 == 3'b000 & top.rdM1 !== 0) begin
			$display("0x%4h: 0x%8h # x%02d = 0x%8h", {1'b1, top.pcM1, 2'b00},  top.instM1, top.rdM1, top.distM1);

		end else if(top.mem_storeM1 == 2'b01) begin
			$display("0x%4h: 0x%8h # (no destination); mem[0x%h] <- 0x%h", {1'b1, top.pcM1, 2'b00}, top.instM1, top.resultM1, top.reg_data2M1[7:0]);
		end else if(top.mem_storeM1 == 2'b10) begin
			$display("0x%4h: 0x%8h # (no destination); mem[0x%h] <- 0x%h", {1'b1, top.pcM1, 2'b00}, top.instM1, top.resultM1, top.reg_data2M1[15:0]);
		end else if(top.mem_storeM1 == 2'b11) begin
			$display("0x%4h: 0x%8h # (no destination); mem[0x%h] <- 0x%h", {1'b1, top.pcM1, 2'b00}, top.instM1, top.resultM1, top.reg_data2M1);
		end else if(top.mem_loadM1 == 3'b001 | top.mem_loadM1 == 3'b100) begin
			$display("0x%4h: 0x%8h # x%02d = 0x%h;            0x%h <- mem[0x%h]", {1'b1, top.pcM1, 2'b00}, top.instM1, top.rdM1, top.distM1, top.distM1[7:0], top.resultM1);
		end else if(top.mem_loadM1 == 3'b010 | top.mem_loadM1 == 3'b101) begin
			$display("0x%4h: 0x%8h # x%02d = 0x%h;          0x%h <- mem[0x%h]", {1'b1, top.pcM1, 2'b00}, top.instM1, top.rdM1, top.distM1, top.distM1[15:0], top.resultM1);
		end else if(top.mem_loadM1 == 3'b011) begin
			$display("0x%4h: 0x%8h # x%02d = 0x%h;      0x%h <- mem[0x%h]", {1'b1, top.pcM1, 2'b00}, top.instM1, top.rdM1, top.distM1, top.distM1, top.resultM1);
		end else
			$display("0x%4h: 0x%8h # (no destination)", {1'b1, top.pcM1, 2'b00}, top.instM1);
		
		if(top.reg_writeM2 == 1 & top.mem_loadM2 == 3'b000 & top.rdM2 !== 0) begin
			$display("0x%4h: 0x%8h # x%02d = 0x%8h", {1'b1, top.pcM2, 2'b00},  top.instM2, top.rdM2, top.distM2);

		end else if(top.mem_storeM2 == 2'b01) begin
			$display("0x%4h: 0x%8h # (no destination); mem[0x%h] <- 0x%h", {1'b1, top.pcM2, 2'b00}, top.instM2, top.resultM2, top.reg_data2M2[7:0]);
		end else if(top.mem_storeM2 == 2'b10) begin
			$display("0x%4h: 0x%8h # (no destination); mem[0x%h] <- 0x%h", {1'b1, top.pcM2, 2'b00}, top.instM2, top.resultM2, top.reg_data2M2[15:0]);
		end else if(top.mem_storeM2 == 2'b11) begin
			$display("0x%4h: 0x%8h # (no destination); mem[0x%h] <- 0x%h", {1'b1, top.pcM2, 2'b00}, top.instM2, top.resultM2, top.reg_data2M2);
		end else if(top.mem_loadM2 == 3'b001 | top.mem_loadM2 == 3'b100) begin
			$display("0x%4h: 0x%8h # x%02d = 0x%h;            0x%h <- mem[0x%h]", {1'b1, top.pcM2, 2'b00}, top.instM2, top.rdM2, top.distM2, top.distM2[7:0], top.resultM1);
		end else if(top.mem_loadM2 == 3'b010 | top.mem_loadM2 == 3'b101) begin
			$display("0x%4h: 0x%8h # x%02d = 0x%h;          0x%h <- mem[0x%h]", {1'b1, top.pcM2, 2'b00}, top.instM2, top.rdM2, top.distM2, top.distM2[15:0], top.resultM2);
		end else if(top.mem_loadM2 == 3'b011) begin
			$display("0x%4h: 0x%8h # x%02d = 0x%h;      0x%h <- mem[0x%h]", {1'b1, top.pcM2, 2'b00}, top.instM2, top.rdM2, top.distM2, top.distM2, top.resultM2);
		end else
			$display("0x%4h: 0x%8h # (no destination)", {1'b1, top.pcM2, 2'b00}, top.instM2);


		$display("%h, %h, %h, %h, %h, %h", top.pc1_out, top.pcD1, top.pcE1, top.pcM1, top.fail_predictD, top.fail_predictE);
		$display("%h, %h, %h, %h", top.pc2_out, top.pcD2, top.pcE2, top.pcM2);
//		$display("%h, %h, %h, %h, %h, %h, %h", top.d_calcpc.pc_predicted, top.d_calcpc.true_pc, top.e_calcpc.pc_predicted, top.e_calcpc.true_pc, top.e_calcpc.jump_pc, top.e_calcpc.reg_data1, top.e_calcpc.imm);
		$display("-----------------------------------------------------------");
	end

	
	parameter address = 32'h0000f95c >> 2;

/* レジスタの確認

	initial begin
		$monitor("%h,%h,%h,%h,%h,%h,%h,%h,%h,%h", top.regfile.reg_file[1], top.regfile.reg_file[2],top.regfile.reg_file[3],top.regfile.reg_file[4], top.regfile.reg_file[5], top.regfile.reg_file[6], top.regfile.reg_file[7], top.regfile.reg_file[8], top.regfile.reg_file[9], top.regfile.reg_file[10]);   
		$monitor("%h, %h,%h,%h,%h,%h,%h,%h,%h,%h,%h", top.regfile.reg_file[10], top.regfile.reg_file[11], top.regfile.reg_file[12],top.regfile.reg_file[13],top.regfile.reg_file[14], top.regfile.reg_file[15], top.regfile.reg_file[16], top.regfile.reg_file[17], top.regfile.reg_file[18], top.regfile.reg_file[19], top.regfile.reg_file[20]);   
	end
*/
	initial begin
		CLK <= 1;
		NRST <= 0;
		#70 NRST <= 1;
		#300 $finish;
	end

	top top(CLK, NRST);
endmodule
