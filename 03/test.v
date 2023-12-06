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
			$display("0x%4h: 0x%8h # x%02d = 0x%h;            0x%h <- mem[0x%h]", {1'b1, top.pcM2, 2'b00}, top.instM2, top.rdM2, top.distM2, top.distM2[7:0], top.resultM2);
		end else if(top.mem_loadM2 == 3'b010 | top.mem_loadM2 == 3'b101) begin
			$display("0x%4h: 0x%8h # x%02d = 0x%h;          0x%h <- mem[0x%h]", {1'b1, top.pcM2, 2'b00}, top.instM2, top.rdM2, top.distM2, top.distM2[15:0], top.resultM2);
		end else if(top.mem_loadM2 == 3'b011) begin
			$display("0x%4h: 0x%8h # x%02d = 0x%h;      0x%h <- mem[0x%h]", {1'b1, top.pcM2, 2'b00}, top.instM2, top.rdM2, top.distM2, top.distM2, top.resultM2);
		end else
			$display("0x%4h: 0x%8h # (no destination)", {1'b1, top.pcM2, 2'b00}, top.instM2);

		//$display("%h, %h", top.alu2.src1, top.alu2.src2);
		//$display("%h, %h, %h, %h, %h", top.e_forwarding2.reg_data1E, top.e_forwarding2.source1E, top.e_forwarding2.rs1E, top.e_forwarding2.distW2, top.e_forwarding2.resultM1);
//		$display("%h, %h, %h, %h, %h, %h, %h, %h", top.pcF1<<2, top.check.pc1<<2, top.pc1_out<<2, top.pcD1<<2, top.pcE1<<2, top.pcM1<<2, top.fail_predictD, top.fail_predictE);
//		$display("%h, %h, %h, %h, %h, %h, %h, %h", top.pcF2<<2, top.check.pc2<<2, top.pc2_out<<2, top.pcD2<<2, top.pcE2<<2, top.pcM2<<2, top.fail_predictD, top.fail_predictE);
//		$display("%h, %h", top.d_calcpc.jump_pc<<2, top.e_calcpc.jump_pc<<2);
//		$display("%h, %h, %h, %h, %h",top.reg_data1D1, top.reg_data2D1, top.reg_data1D2, top.reg_data2D2, top.d_calcpc.true_pc<<2);
//		$display("%h, %h, %h, %h, %h", top.reg_data1E1, top.reg_data2E1, top.reg_data1E2, top.reg_data2E2, top.e_calcpc.true_pc<<2);
//		$display("%h, %h",top.e_calcpc.pc<<2, top.e_calcpc.jump_pc<<2);
//		$display("%h, %h, %h, %h", top.e_calcpc.reg_data11, top.e_calcpc.reg_data21, top.e_calcpc.reg_data12, top.e_calcpc.reg_data22);
//		$display("%h, %h", top.e_calcpc.reg_data1, top.e_calcpc.reg_data2);
//		$display("%h, %h, %h", top.reg_data1D1, top.reg_data2D1, top.branch_numberD);
//		$display("%h, %h", top.resultM1, top.source1D1);
//		$display("%h, %h, %h, %h", top.d_forwarding1.rs1D, top.d_forwarding1.rdM, top.d_forwarding1.mem_loadM, top.d_forwarding1.rs2D);
//		$display("%h, %h", top.resultE1, top.resultE2);
//		$display("%h, %h, %h", top.check.is_depend, top.check.was_depend, top.hit_predict1);
//		$display("%h, %h", top.e_calcpc.pc_predicted<<2, top.e_calcpc.true_pc<<2);
//		$display("%h, %H, %h", top.predict_w_data<<2, top.predict_w_addr<<2, top.predict_wen);
//		$display("%h, %h, %h, %h", top.hit_predict1, top.hit_predict2, top.pre_pc1, top.pre_pc2);
//		$display("%h, %h, %h", top.d_calcpc.true_pc, top.d_calcpc.pc_predicted, top.d_calcpc.jump_code);
//		$display("%h, %h, %h, %h", top.jump_codeD1, top.jump_codeD2, top.jump_codeDj, top.branch_numberD);
//		$display("%h, %h, %h", top.check.pc1<<2, top.check.pc2<<2, top.check.is_depend);
//		$display("%h, %h, %h, %h, %h, %h", top.check.reg_write, top.check.rs1, top.check.rs2, top.check.rd, top.check.use_rs1, top.check.use_rs2);
		
//		$display("%h, %h, %h", top.fail_predictD, top.fail_predictE, top.stall);
//		$display("%h, %h, %h, %h", top.pc2_out, top.pcD2, top.pcE2, top.pcM2);
//		$display("%h, %h, %h, %h, %h, %h, %h", top.d_calcpc.pc_predicted, top.d_calcpc.true_pc, top.e_calcpc.pc_predicted, top.e_calcpc.true_pc, top.e_calcpc.jump_pc, top.e_calcpc.reg_data1, top.e_calcpc.imm);
//	 	$display("%h", top.data_ram.data_ram_block.mem[4096]);
//		$display("%h, %h, %h, %h, %h, %h", top.data_ram.resultM, top.data_ram.resultM_before, top.data_ram.mem_store_before, top.data_ram.load_after_store1, top.data_ram.resultM1, top.data_ram.resultM2);
//		$display("-----------------------------------------------------------");
	
	end

	
	parameter address = 32'h0000f95c >> 2;

//レジスタの確認
/*
	initial begin
		$monitor("%h,%h,%h,%h,%h,%h,%h,%h,%h,%h", top.regfile.reg_file[1], top.regfile.reg_file[2],top.regfile.reg_file[3],top.regfile.reg_file[4], top.regfile.reg_file[5], top.regfile.reg_file[6], top.regfile.reg_file[7], top.regfile.reg_file[8], top.regfile.reg_file[9], top.regfile.reg_file[10]);   
		$monitor("%h, %h,%h,%h,%h,%h,%h,%h,%h,%h,%h", top.regfile.reg_file[10], top.regfile.reg_file[11], top.regfile.reg_file[12],top.regfile.reg_file[13],top.regfile.reg_file[14], top.regfile.reg_file[15], top.regfile.reg_file[16], top.regfile.reg_file[17], top.regfile.reg_file[18], top.regfile.reg_file[19], top.regfile.reg_file[20]);   
	end
*/
	initial begin
		CLK <= 1;
		NRST <= 0;
		#70 NRST <= 1;
		#2000000 $finish;
	end

	top top(CLK, NRST, uart_tx);
endmodule
