from Bio import SeqIO


def get_index(char, string):
	for i, ch in enumerate(string):
		if char == ch:
			return i
	return -1



sequences = SeqIO.parse('./input.txt', 'fasta')

DNA = next(sequences).seq
motif = next(sequences).seq

out = []
i = 0
lead = 0

temp = [0]*len(motif)
while i < len(motif):
	ch = motif[i]

	if lead != 0:
		lead = temp[i-1] + 1
	j = get_index(ch, DNA[lead:])
	lead += j
	temp[i] = lead

	i += 1

print(temp)

