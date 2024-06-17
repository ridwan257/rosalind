from Bio import SeqIO

sequences = SeqIO.parse('./rosalind_sseq.txt', 'fasta')

DNA = next(sequences).seq
motif = next(sequences).seq

positions = []

for ch in motif:
	lead = positions[-1] if positions else 0
	lead += DNA[lead:].index(ch)
	positions.append(lead+1)

print(' '.join(map(str, positions)))
