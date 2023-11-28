module fd_reg(CLK, NRST, pcF, instF, pcD, instD, stall, fail_predictD, fail_predictE, nextpc);
	input CLK, NRST;
	input [12:0] pcF;
	input [31:0] instF;
	output reg [12:0] pcD;
	output reg [31:0] instD;
	input stall;
	input fail_predictD, fail_predictE;
	input [12:0] nextpc;

	wire fail = fail_predictD | fail_predictE;

	always @(posedge CLK) begin
		if(!NRST) begin
			pcD <= 13'b1111111111111;	// startPC-1とすることで、PC初期化時に分岐予測ミスと判定されてしまうのを防ぐ
			instD <= 32'd0;
		end else if(stall) begin
			pcD <= pcD;
			instD <= instD;
		end else if(fail) begin
			pcD <= nextpc - 13'd1;	// 分岐予測ミス時は、新しいPC-4を代入して、予測ミス判定を防ぐ。
			instD <= 32'd0;
		end else begin
			pcD <= pcF;
			instD <= instF;
		end
	end
endmodule
