def ATCG_get():
    file = open("train_python/NC_045512.fasta", 'r')
    # content=file.read()
    content_list = file.readlines()
    file.close()
    # print(content_list)
    # print(content)
    ATGC_quality = {}
    a = 0
    t = 0
    c = 0
    g = 0
    for i in range(1, len(content_list)):
        a = a + content_list[i].count('A')
        t = t + content_list[i].count('T')
        c = c + content_list[i].count('C')
        g = g + content_list[i].count('G')
    ATGC_quality[content_list[0]] = {'A': a, 'T': t, 'C': c, 'G': g}
    print(ATGC_quality)


def getATCG():
    file = open("train_python/Escherichia_coli_55989.cds.fasta", 'r')
    Ecoil_seq_list = file.readlines()
    each_Ecoil = {}
    each_Ecoil_ATGC = {}
    temp_key = ''
    temp_seq = ''

    def count_ATCG(str1):
        a = str1.count('A')
        t = str1.count('T')
        c = str1.count('C')
        g = str1.count('G')
        ATCG_dict = {'A': a, 'T': t, 'C': c, 'G': g}
        return ATCG_dict

    for i in range(len(Ecoil_seq_list)):
        if '>' in Ecoil_seq_list[i]:
            if temp_key is '':
                temp_key = Ecoil_seq_list[i]
                continue
            else:
                each_Ecoil[Ecoil_seq_list[i]] = temp_seq
                temp_key = Ecoil_seq_list[i]
                temp_seq = ''
                continue
        temp_seq = temp_seq + Ecoil_seq_list[i]
    each_Ecoil[temp_key] = temp_seq
    for key, word in each_Ecoil.items():
        each_Ecoil_ATGC[key] = count_ATCG(word)
    for key, word in each_Ecoil_ATGC.items():
        print(key)
        print(word)

file = open("train_python/Escherichia_coli_55989.cds.fasta", 'r')
seqList = file.read().split('>')[1:]
file.close()
print(seqList)

