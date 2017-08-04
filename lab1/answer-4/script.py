filename = raw_input('Enter dump name  ')
with open(filename) as f:
	lines = set(map(lambda x: x.split('(')[0], f.readlines()[:-1]))
print(lines)
print(len(lines))