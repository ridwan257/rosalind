from itertools import permutations

class Sequence:
	def __init__(self, id_='', sequence=''):
		self.id = id_
		self.string = sequence
		self.length = len(sequence)

	def add(self, string):
		self.string += string
		self.length += len(string)

	def get(self):
		return self.string

	def char_at(self, i):
		return self.string[i]


sequence_list = []
sample = None

while True:
	try:
		line = input().strip()
		if line:
			if line[0] == '>':
				if sample is not None:
					sequence_list.append(sample)
				sample = Sequence(line[1:])
				continue

			sample.add(line)

	except EOFError:
		if sample is not None:
			sequence_list.append(sample)
		
		break

		

# for s in sequence_list:
# 	print(s.id)
# 	print(s.string)

def check_rigth_overlap(s, t):
	# print(f"{s.id} -{s.get()}-")
	# print(s.length)

	# print(f"{t.id} -{t.get()}-")
	# print(t.length)

	# match = 0
	# count = 0

	scores = []

	for i in range(s.length):
		k = i
		# print(f"outer-loop : i, {k=}")

		for j in range(t.length):
			# count += 1
			# print(f"inner-loop : {k=} {j=}")
			if s.char_at(k) != t.char_at(j):
				break
			k += 1
			if k == s.length:
				scores.append(s.length - i)
				break

	return scores

	



for i, left in enumerate(sequence_list):
	for j, right in enumerate(sequence_list):
		if i == j:
			continue

		score = check_rigth_overlap(left, right)


		if len(score) > 0:
			print(f"{left.id} {right.id} : {score}")

