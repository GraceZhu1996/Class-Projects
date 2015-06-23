# Submitter: tsalako(Salako, Toluwanimi)
# Partner  : nayanp(Patel, Nayan)
# We certify that we worked cooperatively on this programming
#   assignment, according to the rules for pair programming
from goody import safe_open, read_file_values
from _collections import defaultdict
from random import choice

def read_corpus(order_stat: int, file) -> dict:
    DATA = list(read_file_values(file))
    myDict = defaultdict(tuple)
    order_stat = int(order_stat)
    key_list = []

    for j in range(0, len(DATA)):
        key = tuple()
        try:
            for i in range(0, order_stat):
                key = key + (DATA[j],) if i == 0 else key + (DATA[j+1],)
            key_list.append(key)
        except Exception as e:
            pass
    for i in range(0, len(key_list)):
        try:
            if i+2 < len(key_list):
                new_value = key_list[i+2][0]
            elif i+2 > len(key_list):
                raise Exception
            else:
                new_value = key_list[-1][0]
            if key_list[i] in myDict.keys():#Check if the key exists
                nv = set(myDict[key_list[i]])
                nv.add(new_value)
                myDict[key_list[i]] = list(nv)
            else:
                myDict[key_list[i]] = list(new_value)
        except:
            pass
            
    return myDict

def print_corpus(D: dict):
    print('Corpus')
    key = '  {} can be followed by any of {}'
    for d in D.keys():
        print(key.format(d, D[d]))
    sorted_dict = sorted(D.values(), key = lambda x: len(x))
    max = len(sorted_dict[-1]); min = len(sorted_dict[0])
    print('min/max = {}/{}'.format(min,max))
    
def produce_text(D: dict, L: list, i: int) -> list:
    total_size = int(i) + len(L)
    L1 = list(); L2 = list()
    for i in L:
        L1.append(i)
        L2.append(i)
    if tuple(L) in D.keys():
        L1.extend(D[(tuple(L))])
        c = choice(D[(tuple(L))])
        L.extend(c)
    else:
        return
    while len(L1) != total_size:
        c = choice(D[(L[-2], L[-1])])
        L1.extend(c)
    return L1

if __name__ == '__main__':
    static = 0
    static_loop = True
    while static_loop:
        x = input("Enter order of static: ")
        try:
            if int(x) < 1:
                raise Exception
            else:
                static = x
                static_loop = False
        except:
            print("Please Re-", end = '')
            
    data = safe_open("Enter file to process", 'r', "File not found.", default = 'wginput1.txt')
    myDict = read_corpus(static, data)
    print_corpus(myDict)
    
    print("Enter {} words to start with ".format(static))
    
    Words = []
    while len(Words) <  int(static):
        for i in range(0, int(static)):
            x = input("Enter word {}:".format(i+1))
            try:
                y = str(x)
                Words.append(y)
            except:
                print("Please Re-", end = '')
    int_loop = True 
    num_words = 0
    while int_loop:
        x = input("Enter # of words to generate: ")
        try:
            if int(x) < 1:
                raise Exception
            else:
                num_words = x
                int_loop = False
        except:
            print("Please Re-", end = '')
    print("Random text = " + str(produce_text(myDict, Words, num_words)))