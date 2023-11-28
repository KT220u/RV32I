module test;

	reg CLK;
	reg [7:0] sw;
	wire [7:0] led;
	wire uart_tx;
	
	always begin
		#10 CLK <= ~CLK;	
	end

	// trace format
	always begin
		#20  if(top.reg_writeM == 1 & top.mem_loadM == 3'b000 & top.rdM !== 0) begin
			$display("0x%4h: 0x%8h # x%02d = 0x%8h", top.pcM[15:0], top.instM, top.rdM, top.distM);

		end else if(top.mem_storeM == 2'b01) begin
			$display("0x%4h: 0x%8h # (no destination); mem[0x%h] <- 0x%h", top.pcM[15:0], top.instM, top.resultM, top.store_dataM[7:0]);
		end else if(top.mem_storeM == 2'b10) begin
			$display("0x%4h: 0x%8h # (no destination); mem[0x%h] <- 0x%h", top.pcM[15:0], top.instM, top.resultM, top.store_dataM[15:0]);
		end else if(top.mem_storeM == 2'b11) begin
			$display("0x%4h: 0x%8h # (no destination); mem[0x%h] <- 0x%h", top.pcM[15:0], top.instM, top.resultM, top.store_dataM);
		end else if(top.mem_loadM == 3'b001 | top.mem_loadM == 3'b100) begin
			$display("0x%4h: 0x%8h # x%02d = 0x%h;            0x%h <- mem[0x%h]", top.pcM[15:0], top.instM, top.rdM, top.distM, top.distM[7:0], top.resultM);
		end else if(top.mem_loadM == 3'b010 | top.mem_loadM == 3'b101) begin
			$display("0x%4h: 0x%8h # x%02d = 0x%h;          0x%h <- mem[0x%h]", top.pcM[15:0], top.instM, top.rdM, top.distM, top.distM[15:0], top.resultM);
		end else if(top.mem_loadM == 3'b011) begin
			$display("0x%4h: 0x%8h # x%02d = 0x%h;      0x%h <- mem[0x%h]", top.pcM[15:0], top.instM, top.rdM, top.distM, top.distM, top.resultM);
		end else
			$display("0x%4h: 0x%8h # (no destination)", top.pcM[15:0], top.instM);
	end

	
	parameter address = 32'h0000f95c >> 2;

/*
	always begin
		//#10 $display("%h, %h, %h, %h,  %h, %h, %h, %h, %h, %h, %h, %h, %h, %h, %h, %h", CLK, top.pcF, top.pcD, top.pcE, top.pcM, top.instF, top.instD, top.instE, top.instM, top.mem_loadM, top.reg_writeM, top.rs1D, top.rdM, top.source1D, top.source2D, top.stall);
		//#20 $display("%h, %h, %h, %h, %h, %h, %h, %h, %h, %h", top.data_ram.data_ram_block.mem[address], top.data_ram.r_data, top.resultE, top.resultM, top.data_ram.r_data, top.data_ram.w_data, top.data_ram.w_data0, top.uart_we, top.uart_IN_data, top.uart_OUT_data);
		//#20 $display("%h,  %h, %h, %h", top.inst_rom.pc, top.fail_predictD, top.fail_predictE, top.hit_predict);
		#20 $display("%b, %h, %h,  %h, %h, %h, %h, %h, %h, %h", CLK, top.pcF, top.pcD, top.pcE, top.pcM, top.stall, top.fail_predictD, top.fail_predictE, top.d_forwarding.cannot_predict, top.e_calcpc.cannot_predict);
		$display("%h, %h, %h, %h, %h", top.rs1D, top.rs2D, top.rdM, top.mem_loadM, top.jump_codeD);
		$display("%h, %h, %h, %h, %h", top.d_forwarding.rs1D, top.d_forwarding.rs2D, top.d_forwarding.rdM, top.d_forwarding.mem_loadM, top.d_forwarding.jump_code);
		//#20 $display("%h, %h, %h", top.predict.wen, top.predict.w_addr << 2, {1'b1 , top.predict.w_data[12:0], 2'b00});
	end
*/

/*	レジスタの確認

	initial begin
		$monitor("%h,%h,%h,%h,%h,%h,%h,%h,%h,%h", top.regfile.reg_file[1], top.regfile.reg_file[2],top.regfile.reg_file[3],top.regfile.reg_file[4], top.regfile.reg_file[5], top.regfile.reg_file[6], top.regfile.reg_file[7], top.regfile.reg_file[8], top.regfile.reg_file[9], top.regfile.reg_file[10]);   
		$monitor("%h, %h,%h,%h,%h,%h,%h,%h,%h,%h,%h", top.regfile.reg_file[10], top.regfile.reg_file[11], top.regfile.reg_file[12],top.regfile.reg_file[13],top.regfile.reg_file[14], top.regfile.reg_file[15], top.regfile.reg_file[16], top.regfile.reg_file[17], top.regfile.reg_file[18], top.regfile.reg_file[19], top.regfile.reg_file[20]);   
	end
*/
	initial begin
		CLK= 1;
		sw[0] <= 0;
		#30 sw[0] <= 1;
		#2000000 $finish;
	end

	top top(CLK, sw[0], led, uart_tx);
endmodule
