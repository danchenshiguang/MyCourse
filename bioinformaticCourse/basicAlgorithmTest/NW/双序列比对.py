import pandas as pd
from Bio.SubsMat.MatrixInfo import blosum62
from Bio import SeqIO
# file1=r"D:\pythonProject\flaskProject\生物信息学\test1.fasta"
# file2=r"D:\pythonProject\flaskProject\生物信息学\test2.fasta"
# 读取fasta格式文件
# input_seqA = SeqIO.read("NC_045512.fasta","fasta")
# input_seqB = SeqIO.read("NC_045512.fasta","fasta")
# # print(blosum62)
# seqA = list(str(0) + input_seqA.seq)
# seqB = list(str(0) + input_seqB.seq)
# print(input_seqA.seq)
def NW_alignment(file1,file2):
    input_seqA = SeqIO.read(file1,"fasta")
    input_seqB = SeqIO.read(file2,"fasta")
    seqA = list(str(0) + input_seqA.seq)
    seqB = list(str(0) + input_seqB.seq)
    nw = pd.DataFrame(index=seqB, columns=seqA)
    nw.iloc[0, 0] = 0
    nw.iloc[0, 1] = -11
    nw.iloc[1, 0] = -11
    for i in range(1, len(seqA)):
        nw.iloc[0, i] = nw.iloc[0, i - 1] - 11
    for i in range(1, len(seqB)):
        nw.iloc[i, 0] = nw.iloc[i - 1, 0] - 11
    for i in range(0, len(seqB) - 1):
        for j in range(0, len(seqA) - 1):
            n = nw.iloc[i][j + 1] - 11
            m = nw.iloc[i + 1][j] - 11
            if blosum62.get((nw.index[i + 1], nw.columns[j + 1])) is not None:

                s = nw.iloc[i][j] + blosum62.get((nw.index[i + 1], nw.columns[j + 1]))
            else:
                s = nw.iloc[i][j] + blosum62.get((nw.columns[j + 1], nw.index[i + 1]))
            value = max([n, m, s])
            nw.iloc[i + 1][j + 1] = value
    length_A = len(seqA) - 1
    length_B = len(seqB) - 1
    alignment_A = ""
    alignment_B = ""
    alignment_A = alignment_A + nw.columns[length_A]
    alignment_B = alignment_B + nw.index[length_B]
    # 回溯，从最后一位置开始
    while length_A > 0 and length_B > 0:
        if nw.iloc[length_B][length_A] == nw.iloc[length_B - 1][length_A] - 11:
            alignment_A = alignment_A + '-'
            alignment_B = alignment_B + nw.index[length_B - 1]
            length_B = length_B - 1
            continue
        if nw.iloc[length_B][length_A] == nw.iloc[length_B][length_A - 1] - 11:
            alignment_A = alignment_A + nw.columns[length_A - 1]
            alignment_B = alignment_B + '-'
            length_A = length_A - 1
            continue
        alignment_A = alignment_A + nw.columns[length_A]
        alignment_B = alignment_B + nw.index[length_B]
        length_A = length_A - 1
        length_B = length_B - 1
    # print(alignment_B)
    # print(alignment_A)
    alignment_A = alignment_A[::-1]
    alignment_B = alignment_B[::-1]
    return alignment_A,alignment_B,nw.iloc[len(seqB) - 1][len(seqA) - 1]