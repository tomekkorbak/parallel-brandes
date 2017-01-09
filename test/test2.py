from subprocess import call

files = [
    # ('input1.txt', '1.txt', 'output1.txt'),
    # ('input2.txt', '2.txt', 'output2.txt'),
    # ('input3.txt', '3.txt', 'output3.txt'),
    # ('input4.txt', '4.txt', 'output4.txt'),
    ('input5.txt', '5.txt', 'output5.txt'),
    # ('input6.txt', '6.txt', 'output6.txt'),
]

for program_input, output, target in files:
	# call(['../a.out', program_input, output])
	print(output)

	with open(output) as output_file:
		with open(target) as target_file:
			for line_output, line_target in zip(output_file.readlines(), target_file.readlines()):
				id1, id2 = line_output.split()[0], line_target.split()[0]
				assert int(id1) == int(id2)
				v1, v2 = float(line_output.split()[1]), float(line_target.split()[1])
				print('v1 ', v1, 'v2 ', v2)
				assert abs(v1 - v2) < 0.001