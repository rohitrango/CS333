import re
filename = 'dump.txt'
with open(filename) as f:
	lines = f.readlines()
	open_filenames = filter(lambda x: x.split('(')[0] == 'open', lines)
	names = map(lambda x: re.findall("\".*\"", x)[0][1:-1], open_filenames)
	for i in names:
		print(i)
