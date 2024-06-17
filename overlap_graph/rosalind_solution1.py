from Bio import SeqIO
import collections

infile = "input.in"
overlap_length = 3

seq_start = collections.defaultdict(list)
seq_end = collections.defaultdict(list)

with open(infile) as file:
    for record in SeqIO.parse(file, 'fasta'):
        seq = str(record.seq)
        seq_start[seq[:overlap_length]].append(record.id)
        seq_end[seq[-overlap_length:]].append(record.id)

for key, start_id in seq_start.items():
    if key in seq_end:
        end_id = seq_end[key]
        [print(j, i) for i in start_id for j in end_id if i != j]