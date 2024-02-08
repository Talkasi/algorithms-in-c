from random import randint

CONFIG_DIR = "Tests/tests.conf"
FILES_DIR = "Tests/Data/"
TEST_FORMAT = ".txt"

tests_info = [1, 2, 5, 10, 100, 1000, 5000, 10000]
min_bound = -10000
max_bound =  10000

max_test_n = max(tests_info)
max_test_slen = len(str(max_test_n))
for i in tests_info:
	test_name = FILES_DIR + '0' * (max_test_slen - len(str(i))) + str(i) + TEST_FORMAT

	data = []
	with open(test_name, "w") as f:
		for j in range(i):
			n = randint(min_bound, max_bound + 1)
			data.append(n)
			f.write(str(n) + "\n")

	data = sorted(data)
	test_res_name = FILES_DIR + '0' * (max_test_slen - len(str(i))) + str(i) + "_S" + TEST_FORMAT
	with open(test_res_name, "w") as f:
		for n in data:
			f.write(str(n) + "\n")
