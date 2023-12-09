module mem(CLK, NRST,  nextPC, PC, inst, result, write_data, reg_data3, mem_store, mem_load, hc_OUT_data);
	input CLK, NRST;
	input [31:0] nextPC;
	output reg [31:0] PC;
	output [31:0] inst;
	input [31:0] result;
	input [31:0] write_data;
	output [31:0] reg_data3;
	input [1:0] mem_store; // 00:SB, 01:SH, 10:SW
	input [2:0] mem_load;  // 000:LB, 001:LH, 010:LW, 011:LBU, 100:LHU 111:NotLOAD
	input [31:0] hc_OUT_data;
	

	// instruction memory
	parameter startPC = 32768;
	always @(negedge CLK) begin
		if(!NRST) PC <= startPC;
		else PC <= nextPC;
	end

	// data memory
	assign reg_data3 = (mem_load == 3'b000) ? {{24{r_data[7]}}, r_data[7:0]} :
					   (mem_load == 3'b001) ? {{16{r_data[15]}}, r_data[15:0]} :  
					   (mem_load == 3'b010) ? (result == `HARDWARE_COUNTER_ADDR) ? hc_OUT_data : r_data : 
					   (mem_load == 3'b011) ? {24'd0, r_data[7:0]} : 
					   (mem_load == 3'b100) ? {16'd0, r_data[15:0]} : 
					   result;

	wire [31:0] r_data;
	inst_rom inst_rom(CLK, PC, inst);
	data_ram data_ram(CLK, mem_store, result, r_data, result, write_data); 

endmodule

module inst_rom(clk, r_addr, r_data);
	input clk;
	input [31:0] r_addr;
	output reg [31:0] r_data;
	reg [7:0] mem [0:131071];
	initial begin
		$readmemh("/home/denjo/RV32I/00/initdata.hex", mem);
	end
	always @(posedge clk) begin
		r_data <= {mem[r_addr], mem[r_addr+1], mem[r_addr+2], mem[r_addr+3]};
	end
endmodule

module data_ram(clk, mem_store, r_addr, r_data, w_addr, w_data);
	input clk;
	input [1:0] mem_store;
	input [31:0] r_addr, w_addr;
	input [31:0] w_data;
	output reg [31:0] r_data;
	reg [7:0] mem [0:131071];
	reg debug;
	initial begin
		$readmemh("/home/denjo/RV32I/Verilog/initdata.hex", mem);
	end
	always @(negedge clk) begin
		r_data <= {mem[r_addr+3], mem[r_addr+2], mem[r_addr+1], mem[r_addr]};
	end
	always @(posedge clk) begin
		if(mem_store == 2'b00) begin
			mem[w_addr] <= w_data[7:0];
		end else if(mem_store == 2'b01) begin
			mem[w_addr] <= w_data[7:0];
			mem[w_addr+1] <= w_data[15:8];
		end else if(mem_store == 2'b10) begin
			debug <= 1;
			mem[w_addr] <= w_data[7:0];
			mem[w_addr+1] <= w_data[15:8];
			mem[w_addr+2] <= w_data[23:16];
			mem[w_addr+3] <= w_data[31:24];
		end else debug <= 0;
	end
endmodule
		
