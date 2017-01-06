from subprocess import call

files = [
    ('input1.txt', '1.txt', 'output1.txt'),
    ('input2.txt', '2.txt', 'output2.txt'),
    ('input3.txt', '3.txt', 'output3.txt'),
    ('input4.txt', '4.txt', 'output4.txt'),
    ('input5.txt', '5.txt', 'output5.txt'),
]

for program_input, output, target in files:
	call(['../a.out', program_input, output])
	print(output)

	with open(output) as output_file:
		with open(target) as target_file:
			for line_output, line_target in zip(output_file.readlines(), target_file.readlines()):
				print('a', line_output.split()[0], line_target.split()[0])
				assert int(line_output.split()[0]) == int(line_target.split()[0])

				print('b', line_output.split()[1], line_target.split()[1])
				assert abs(float(line_output.split()[1]) - float(line_target.split()[1])) < 0.001