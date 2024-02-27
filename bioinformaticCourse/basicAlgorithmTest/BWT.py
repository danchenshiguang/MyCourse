from Bio import SeqIO
import time
'''这个函数用于生成不同碱基的位置信息'''
def loc_search(str_seq):
    para =[]
    if str_seq[0] == 'A':
        para.append(1)
    elif str_seq[0] == 'T':
        para.append(2)
    elif str_seq[0] == 'G':
        para.append(3)
    elif str_seq[0] == 'C':
        para.append(4)
    else:
        para.append(0)
    if str_seq[-1] == 'A':
        para.append(1)
    elif str_seq[-1] == 'T':
        para.append(2)
    elif str_seq[-1] == 'G':
        para.append(3)
    elif str_seq[-1] == 'C':
        para.append(4)
    else:
        para.append(0)
    return para


file = SeqIO.read("ac_FV_geno_part.fna","fasta")
genome_seq = file.seq
#编码过程
marked_genome_seq = genome_seq+'$'
M_matrix = []
F_line = []
L_line = []

temp =marked_genome_seq[-1]+marked_genome_seq[0:-1]
#添加标记符号
for i in range(len(marked_genome_seq)):
    M_matrix.append(temp)
    if temp[-1] == '$':
        break
    temp = temp[-1]+temp[0:-1]
#得到M_matrix
M_matrix.sort()
loc_matrix =[['$',0,0],['A',0,0],['G',0,0],['C',0,0],['G',0,0]]
#得到F_line和L_line
for i in M_matrix:
        which_index = loc_search(i)

        F_line.append((i[0],loc_matrix[which_index[0]][1]))
        L_line.append((i[-1],loc_matrix[which_index[1]][2]))
        # L_line.append(i[-1])
        loc_matrix[which_index[0]][1]=loc_matrix[which_index[0]][1]+1
        loc_matrix[which_index[1]][2]=loc_matrix[which_index[1]][2]+1
print(L_line)
'''将L_line解码成原来的序列'''
#解码过程
decode_seq=''
decode_seq=decode_seq+L_line[0][0]
search_letter =L_line[0]
while True:
    next_letter_index = F_line.index(search_letter)
    search_letter = L_line[next_letter_index]
    if search_letter ==('$',0):
        decode_seq=decode_seq[::-1]
        break
    decode_seq = decode_seq+L_line[next_letter_index][0]
print(decode_seq)
'''3.查询一段序列的位置'''
#输入查询DNA片段，输出该片段的开始和结束位置
match_seq = 'CTTTTTTGT'
def look_for_seq(a_seq):
    count_matrix = [0]*len(M_matrix)
    result =[]
    for index, value in enumerate(a_seq):
        for i,j in enumerate(M_matrix):
            if value == j[index]:
                count_matrix[i]=count_matrix[i]+1
    for index,value in enumerate(count_matrix):
        if value == len(a_seq):
            result.append(index)
    location = []
    for i in result:
        for index, value in enumerate(M_matrix[i]):
            if value == '$':
                start = len(M_matrix[i]) - index
                end = start + len(a_seq)-1
                location.append((start,end))
    return result ,location
start_time =time.perf_counter()
m = look_for_seq(match_seq)
end_time = time.perf_counter()
print(m[1][0])
highlighted_seq = decode_seq.replace(match_seq, "\033[31m"+match_seq+"\033[0m")
print(highlighted_seq)
print(f"运行速度为{end_time-start_time}")













