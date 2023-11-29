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
			$display("0x%4h: 0x%8h # x%02d = 0x%8h", {1'b1, top.pcM, 2'b00},  top.instM, top.rdM, top.distM);

		end else if(top.mem_storeM == 2'b01) begin
			$display("0x%4h: 0x%8h # (no destination); mem[0x%h] <- 0x%h", {1'b1, top.pcM, 2'b00}, top.instM, top.resultM, top.store_dataM[7:0]);
		end else if(top.mem_storeM == 2'b10) begin
			$display("0x%4h: 0x%8h # (no destination); mem[0x%h] <- 0x%h", {1'b1, top.pcM, 2'b00}, top.instM, top.resultM, top.store_dataM[15:0]);
		end else if(top.mem_storeM == 2'b11) begin
			$display("0x%4h: 0x%8h # (no destination); mem[0x%h] <- 0x%h", {1'b1, top.pcM, 2'b00}, top.instM, top.resultM, top.store_dataM);
		end else if(top.mem_loadM == 3'b001 | top.mem_loadM == 3'b100) begin
			$display("0x%4h: 0x%8h # x%02d = 0x%h;            0x%h <- mem[0x%h]", {1'b1, top.pcM, 2'b00}, top.instM, top.rdM, top.distM, top.distM[7:0], top.resultM);
		end else if(top.mem_loadM == 3'b010 | top.mem_loadM == 3'b101) begin
			$display("0x%4h: 0x%8h # x%02d = 0x%h;          0x%h <- mem[0x%h]", {1'b1, top.pcM, 2'b00}, top.instM, top.rdM, top.distM, top.distM[15:0], top.resultM);
		end else if(top.mem_loadM == 3'b011) begin
			$display("0x%4h: 0x%8h # x%02d = 0x%h;      0x%h <- mem[0x%h]", {1'b1, top.pcM, 2'b00}, top.instM, top.rdM, top.distM, top.distM, top.resultM);
		end else
			$display("0x%4h: 0x%8h # (no destination)", {1'b1, top.pcM, 2'b00}, top.instM);
	end

	
	parameter address = 32'h0000f95c >> 2;

/*
	always begin
		#10 $display("%b, %h, %h,  %h, %h, %h, %h, %h, %h, %h, %h, %h", CLK, top.pcF, top.pcD, top.pcE, top.pcM, top.stall, top.fail_predictD, top.fail_predictE, top.cannot_calcpcD, top.cannot_calcpcE, top.predict.r_data, top.hit_predict);
	end
*/

/* レジスタの確認

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
