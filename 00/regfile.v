module regfile(CLK, rs1, rs2, reg_data1, reg_data2, rd, reg_data3, reg_write);
	input CLK;
	input [4:0] rs1, rs2, rd;
	output [31:0] reg_data1, reg_data2;
	input [31:0] reg_data3;
	input reg_write;

	assign reg_data1 = reg_file[rs1];
	assign reg_data2 = reg_file[rs2];

	reg [31:0] reg_file [0:31];


	always @(posedge CLK) begin
		reg_file[0] <= 0;	// zero register
		if (reg_write & rd !== 0) reg_file[rd] <= reg_data3;
	end


endmodule

