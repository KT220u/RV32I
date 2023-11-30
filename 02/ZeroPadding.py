import sys
args = sys.argv

with open(args[1], "a") as f:
	for i in range(8192):
		f.write("00000000\n")

