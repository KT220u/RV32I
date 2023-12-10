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
		#20  if(top.reg_write == 1 & top.mem_load == 3'b111 & top.rd !== 0) begin
			//$display("0x%4h: 0x%8h # x%02d = 0x%8h, reg1:%h,reg2:%h,imm:%h", top.PC[15:0], top.inst, top.rd, top.reg_data3, top.reg_data1, top.reg_data2, top.imm);
			$display("0x%4h: 0x%8h # x%02d = 0x%8h", top.alu.PCbuffer[15:0], top.inst, top.rd, top.reg_data3);

		end else if(top.mem_store <= 2'b00) begin
			$display("0x%4h: 0x%8h # (no destination); mem[0x%h] <- 0x%h", top.alu.PCbuffer[15:0], top.inst, top.result, top.reg_data2[7:0]);
		end else if(top.mem_store <= 2'b01) begin
			$display("0x%4h: 0x%8h # (no destination); mem[0x%h] <- 0x%h", top.alu.PCbuffer[15:0], top.inst, top.result, top.reg_data2[15:0]);
		end else if(top.mem_store <= 2'b10) begin
			$display("0x%4h: 0x%8h # (no destination); mem[0x%h] <- 0x%h", top.alu.PCbuffer[15:0], top.inst, top.result, top.reg_data2);
		end else if(top.mem_load == 3'b000 | top.mem_load == 3'b011) begin
			$display("0x%4h: 0x%8h # x%02d = 0x%h;            0x%h <- mem[0x%h]", top.alu.PCbuffer[15:0], top.inst, top.rd, top.reg_data3, top.reg_data3[7:0], top.result);
		end else if(top.mem_load == 3'b001 | top.mem_load == 3'b100) begin
			$display("0x%4h: 0x%8h # x%02d = 0x%h;          0x%h <- mem[0x%h]", top.alu.PCbuffer[15:0], top.inst, top.rd, top.reg_data3, top.reg_data3[15:0], top.result);
		end else if(top.mem_load == 3'b010) begin
			$display("0x%4h: 0x%8h # x%02d = 0x%h;      0x%h <- mem[0x%h]", top.alu.PCbuffer[15:0], top.inst, top.rd, top.reg_data3, top.reg_data3, top.result);
		end else
			$display("0x%4h: 0x%8h # (no destination)", top.alu.PCbuffer[15:0], top.inst);
	//	$display("%h%h%h%h, %b", top.Mem.data_ram.mem[129372], top.Mem.data_ram.mem[129373],top.Mem.data_ram.mem[129374],top.Mem.data_ram.mem[129375], top.Mem.data_ram.store_enable);
//		$display("w_data;%h, w_addr:%h, r_data:%h, reg_data3:%h", top.Mem.data_ram.w_data, top.Mem.data_ram.w_addr, top.Mem.data_ram.r_data, top.Mem.reg_data3);
	end
	

	initial begin
//		$monitor("PC:%h, inst:%b, %b,%b,%b,%b", top.PC, top.Mem.inst_D, top.jal, top.jalr, top.branch, top.flag);
//		$monitor("mem_load:%b mem_store:%b", top.mem_load, top.mem_store);
//		$monitor("%b, w_addr:%d,w_data:%h, mem_store:%b, mem:%b %b %b %b %b %b %b %b", top.Mem.data_ram.debug, top.result, top.Mem.write_data, top.mem_store, top.Mem.data_ram.mem[128916],top.Mem.data_ram.mem[128917],top.Mem.data_ram.mem[128918],top.Mem.data_ram.mem[128919],top.Mem.data_ram.mem[128920],top.Mem.data_ram.mem[128921],top.Mem.data_ram.mem[128922],top.Mem.data_ram.mem[128923]);
//		$monitor("%t,  r_addr:%d, r_data:%h, reg_data3:%h, mem_load:%b, reg15:%h", $time, top.Mem.data_ram.r_addr, top.Mem.data_ram.r_data, top.reg_data3, top.mem_load, top.RegFile.reg_file[15]);
//		$monitor("time:%t, PC:%h, PCbuffer:%h, inst:%h",$time,  top.PC, top.alu.PCbuffer, top.inst);
	end

	initial begin
		CLK= 1;
		sw[0] <= 0;
		#40 sw[0] <= 1;
		#10000000 $finish;
	end

	top top(CLK, sw[0], led, uart_tx);
endmodule
