import sys
argv = sys.argv[1:]

if len(argv) >= 1:
	file_in = argv[0]
else:
	file_in = "assembly_code.dat"

if len(argv) >= 2:
	file_out = argv[1]
else:
	file_out = "code.hex"

print("input_file : ",file_in);
print("output_file : ",file_out);

def assemble(read_f, write_f):

	R = ["add", "sub", "and", "or", "xor", "sll", "srl", "sra", "slt", "sltu"]
	I = ["addi", "andi", "ori", "xori", "lb", "lh", "lw", "lbu", "lhu", "jalr", "slli", "srli", "srai", "slti", "sltiu"]
	S = ["sb", "sh", "sw"]
	B = ["beq", "bne", "blt", "bge", "bltu", "bgeu"]
	U = ["lui", "auipc"]
	J = ["jal"]

	line_count = 0

	for line in read_f:
		if len(line) <= 1:
			continue

		line_count += 1;
		machine_code = [None] * 32
		code = line.split()
		if code[0] == "#":
			continue

		opcode = code[0]
		arg1 = code[1]
		arg2 = code[2]
		if len(code) >= 4:
			arg3 = code[3]

		if opcode in R:
			machine_code[25:32] = [0,1,1,0,0,1,1]
			machine_code[20:25] = [int(i) for i in format(int(arg1[1:]), "05b")]
			machine_code[12:17] = [int(i) for i in format(int(arg2[1:]), "05b")]
			machine_code[7:12] = [int(i) for i in format(int(arg3[1:]), "05b")]

			if opcode == "sub" or opcode == "sra":
				machine_code[0:7] = [0,1,0,0,0,0,0]
			else:
				machine_code[0:7] = [0,0,0,0,0,0,0]
			if opcode == "add" or opcode == "sub":
				machine_code[17:20] = [0,0,0]
			elif opcode == "and":
				machine_code[17:20] = [1,1,1]
			elif opcode == "or":
				machine_code[17:20] = [1,1,0]
			elif opcode == "xor":
				machine_code[17:20] = [1,0,0]
			elif opcode == "sll":
				machine_code[17:20] = [0,0,1]
			elif opcode == "srl" or opcode == "sra":
				machine_code[17:20] = [1,0,1]
			elif opcode == "slt":
				machine_code[17:20] = [0,1,0]
			elif opcode == "sltu":
				machine_code[17:20] = [0,1,1]

		elif opcode in I:
			machine_code[20:25] = [int(i) for i in format(int(arg1[1:]), "05b")]
			machine_code[12:17] = [int(i) for i in format(int(arg2[1:]), "05b")]

			if int(arg3) >= 0:
				imm = format(int(arg3), "012b")
			else:
				imm = format(int(arg3) + 2 ** 12, "012b")
			machine_code[0:12] = [int(i) for i in imm]

			machine_code[25:32] = [0,0,1,0,0,1,1]
			if opcode == "addi":
				machine_code[17:20] = [0,0,0]
			elif opcode == "andi":
				machine_code[17:20] = [1,1,1]
			elif opcode == "ori":
				machine_code[17:20] = [1,1,0]
			elif opcode == "xori":
				machine_code[17:20] = [1,0,0]
			elif opcode == "lb":
				machine_code[17:20] = [0,0,0]
				machine_code[25:32] = [0,0,0,0,0,1,1]
			elif opcode == "lh":
				machine_code[17:20] = [0,0,1]
				machine_code[25:32] = [0,0,0,0,0,1,1]
			elif opcode == "lw":
				machine_code[17:20] = [0,1,0]
				machine_code[25:32] = [0,0,0,0,0,1,1]
			elif opcode == "lbu":
				machine_code[17:20] = [1,0,0]
				machine_code[25:32] = [0,0,0,0,0,1,1]
			elif opcode == "lhu":
				machine_code[17:20] = [1,0,1]
				machine_code[25:32] = [0,0,0,0,0,1,1]
			elif opcode == "jalr":
				machine_code[17:20] = [0,0,0]
				machine_code[25:32] = [1,1,0,0,1,1,1]
			elif opcode == "slli":
				machine_code[17:20] = [0,0,1]
			elif opcode == "srli":
				machine_code[17:20] = [1,0,1]
			elif opcode == "srai":
				machine_code[17:20] = [1,0,1]
				machine_code[0:7] = [0,1,0,0,0,0,0]
			elif opcode == "slti":
				machine_code[17:20] = [0,1,0]
			elif opcode == "sltiu":
				machine_code[17:20] = [0,1,1]

		elif opcode in S:
			machine_code[12:17] =  [int(i) for i in format(int(arg1[1:]), "05b")]
			machine_code[7:12] =  [int(i) for i in format(int(arg2[1:]), "05b")]
			machine_code[25:32] = [0,1,0,0,0,1,1]

			if int(arg3) >= 0:
				imm = format(int(arg3), "012b")
			else:
				imm = format(int(arg3) + 2 ** 12, "012b")
			machine_code[0:7] = [int(i) for i in imm[0:7]]
			machine_code[20:25] = [int(i) for i in imm[7:12]]

			if opcode == "sb":
				machine_code[17:20] = [0,0,0]
			elif opcode == "sh":
				machine_code[17:20] = [0,0,1]
			elif opcode == "sw":
				machine_code[17:20] = [0,1,0]

		elif opcode in B:
			machine_code[12:17] =  [int(i) for i in format(int(arg1[1:]), "05b")]
			machine_code[7:12] =  [int(i) for i in format(int(arg2[1:]), "05b")]
			machine_code[25:32] = [1,1,0,0,0,1,1]

			if int(arg3) >= 0:
				imm = format(int(arg3), "013b")
			else:
				imm = format(int(arg3) + 2 ** 13, "013b")

			machine_code[0] = int(imm[0])
			machine_code[1:7] = [int(i) for i in imm[2:8]]
			machine_code[20:24] = [int(i) for i in imm[8:12]]
			machine_code[24] = int(imm[1])

			if opcode == "beq":
				machine_code[17:20] = [0,0,0]
			elif opcode == "bne":
				machine_code[17:20] = [0,0,1]
			elif opcode == "blt":
				machine_code[17:20] = [1,0,0]
			elif opcode == "bge":
				machine_code[17:20] = [1,0,1]
			elif opcode == "bltu":
				machine_code[17:20] = [1,1,0]
			elif opcode == "bgeu":
				machine_code[17:20] = [1,1,1]

		elif opcode in U:
			machine_code[20:25] = [int(i) for i in format(int(arg1[1:]), "05b")]

			if int(arg2) >= 0:
				imm = format(int(arg2), "020b")
			else:
				imm = format(int(arg2) + 2 ** 20, "020b")

			machine_code[0:20] = [int(i) for i in imm]

			if opcode == "lui":
				machine_code[25:32] = [0,1,1,0,1,1,1]
			elif opcode == "auipc":
				machine_code[25:32] = [0,0,1,0,1,1,1]

		elif opcode in J:
			machine_code[20:25] = [int(i) for i in format(int(arg1[1:]), "05b")]

			if int(arg2) >= 0:
				imm = format(int(arg2), "021b")
			else:
				imm = format(int(arg2) + 2 ** 21, "021b")
			machine_code[0] = int(imm[0])
			machine_code[12:20] = [int(i) for i in imm[1:9]]
			machine_code[11] = int(imm[9])
			machine_code[1:11] = [int(i) for i in imm[10:20]]

			machine_code[25:32] = [1,1,0,1,1,1,1]

		else:
			print("format error, line number : ", line_count)
			break

		for i in range(4):	# 32 bit machine_code -> 4 * 8 bit (0x) code	
			num = 0
			for j in range(8):
				num += machine_code[8 * i + j] * 2 ** (7 - j)
			write_f.write(format(num, "02x"))
		write_f.write("\n")
	
	while(line_count <= 8191):
		write_f.write("00000000\n")
		line_count += 1

with open(file_in, "r") as read_f:
	with open(file_out,"w") as  write_f:
		assemble(read_f, write_f)

