module uart(
	uart_tx,     
	uart_wr_i,
	uart_dat_i,
	sys_clk_i,
	sys_rstn_i 
	);

	input uart_wr_i;
	input [7:0] uart_dat_i;
	input sys_clk_i;
	input sys_rstn_i;

	// output uart_busy;
	output uart_tx;

	reg [3:0] bitcount;
	reg [8:0] shifter;
	reg uart_tx;

	wire uart_busy = |bitcount[3:1];
	wire sending = |bitcount;

	// sys_clk_i is 100MHz.  We want a 115200Hz clock

	reg [28:0] d;
	wire [28:0] dInc = d[28] ? (115200) : (115200 - 80000000);
	wire [28:0] dNxt = d + dInc;
	always @(posedge sys_clk_i or negedge sys_rstn_i) begin
		if (!sys_rstn_i) begin
			d <= 29'b0;
		end else begin
			d <= dNxt;
		end
	end
	wire ser_clk = ~d[28]; // this is the 115200 Hz clock

	always @(posedge sys_clk_i or negedge sys_rstn_i) begin
		if (!sys_rstn_i) begin
			uart_tx <= 1;
			bitcount <= 0;
			shifter <= 0;
		end else begin
			// just got a new byte
			if (uart_wr_i & ~uart_busy) begin
				shifter <= { uart_dat_i[7:0], 1'h0 };
				bitcount <= (1 + 8 + 2);
			end

			if (sending & ser_clk) begin
				{ shifter, uart_tx } <= { 1'h1, shifter };
				bitcount <= bitcount - 1;
			end
		end
	end

endmodule
