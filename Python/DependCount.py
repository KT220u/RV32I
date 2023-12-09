with open("depend_result", "r") as f:
	branch = 0
	data_hazard = 0
	store_store = 0
	store_load = 0
	for line in f:
		if line == "inst1 is branch\n":
			branch += 1
		elif line == "data hazard\n":
			data_hazard += 1
		elif line == "store and store\n":
			store_store += 1
		elif line == "store and load\n":
			store_load += 1
	print("branch :", branch)
	print("data hazard :", data_hazard)
	print("store and store :", store_store);
	print("store and load :", store_load)

	
