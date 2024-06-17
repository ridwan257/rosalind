from Bio.Seq import Seq
import re

DNA = ""
is_dna = False
is_intron = False
count = 0
intron_list = []


def spliced_dna(intron, target):
	match = re.search(rf'(\w*){intron}(\w*)', target)
	new_dna = ''
	if match:
		new_dna = ''.join(match.groups())
	return new_dna

with open('./rosalind_splc.txt', 'r') as f:
	line = f.readline().strip()
	intron = ''
	while line:
		if line[0] == '>':
			is_dna = True
			count += 1
			if intron:
				intron_list.append(intron)
				intron = ''
			line = f.readline().strip()

		if count > 1:
			is_dna = False
			is_intron = True

		if is_dna:
			DNA += line

		if is_intron:
			intron += line

		line = f.readline().strip()

if intron:
	intron_list.append(intron)


# print(DNA)
# print(intron_list)

new_dna = DNA[:]
for intron in intron_list:
	new_dna = spliced_dna(intron, new_dna)


print('> DNA')
print(new_dna)
print('> Protein')

new_dna = Seq(new_dna)
protein_seq = new_dna.translate()
print(protein_seq)

print()
print(dir(new_dna))






