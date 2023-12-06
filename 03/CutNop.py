with open("res", "w") as w:
	with open("result", "r") as f:
		for line in f:
			if line == "0x8000: 0x00000000 # (no destination)\n":
				continue;
			else:
				w.write(line);


