def checkDepend(index, line1, line2):
	inst1 = str(format(int(line1, 16), "032b"));
	inst2 = str(format(int(line2, 16), "032b"));

# 依存の種類
# 1. line1 = branch
# 2. line1 = reg_write & rd = rs1, rs2
# 3. line1 = store & line2 = store
# 4. line1 = store & line2 = load
	
	opcode1 = inst1[25:32]
	opcode2 = inst2[25:32]
	
# 1.
	if opcode1[0] == '1':
		print(index);
		print("inst1 is branch")
		return
#2.
	rd = "xxxxx"
	rs1 = "xxxxx"
	rs2 = "xxxxx"
	if opcode1 == "0110011" or opcode1 == "0010011" or opcode1 == "0000011" or opcode1 == "1100111" or opcode1 == "0110111" or opcode1 == "0010111" or opcode1 == "1101111":
		rd = inst1[20:25]
	if opcode2 == "0110011" or opcode2 == "0010011" or opcode2 == "0000011" or opcode2 == "1100111" or opcode2 == "0100011" or opcode2 == "1100111":
		rs1 = inst2[12:17]
	if opcode2 == "0110011" or opcode2 == "0100011" or opcode2 == "1100111":
		rs2 = inst2[7:12]
	if rd!= "00000" and rd != "xxxxx" and (rd == rs1 or rd == rs2):

		print(index);
		print("data hazard")
		return
#3.
	if opcode1 == "0100011" and opcode2 == "0100011":
		print(index);
		print("store and store")
		return
#4.
	if opcode1 == "0100011" and opcode2 == "0000011":
		print(index);
		print("store and load")
		return
	
# 各命令について、直後の命令とどのような依存関係があるかを出力する
with open("trace", "r") as f:
	line1 = "00000000";
	index = 0;
	for line in f:
		index += 1
		line2 = line[0:8]
		checkDepend(index, line1, line2);
		line1 = line2;

