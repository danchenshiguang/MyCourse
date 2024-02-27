inputstr = input("请输入序列:")
revstr = ''
for i in range(len(inputstr)-1,-1,-1):
    revstr = revstr+inputstr[i]
print('反向序列为：{}'.format(revstr))
compstr = ""
for i in range(0,len(revstr),1):
    if revstr[i] in ['A', 'a']:
        compstr = compstr + 'T'
    elif revstr[i] in ['T', 't']:
        compstr = compstr + 'A'
    elif revstr[i] in ['C', 'c']:
        compstr = compstr + 'G'
    elif revstr[i] in ['G', 'g']:
        compstr = compstr + 'C'
    else:
        print("输入格式错误")
    print("反向互补序列为：{}".format(compstr))
