# Submitter: tsalako(Salako, Toluwanimi)
# Partner  : nayanp(Patel, Nayan)
# We certify that we worked cooperatively on this programming
#   assignment, according to the rules for pair programming
from goody import safe_open
from _collections import defaultdict
def read_ndfa(file)-> dict:
    DATA = file.read().split()
    myDict = defaultdict(dict)
    for e in DATA:
        D = e.split(';')
        tempDict = dict()
        for j in range(1, len(D), 2):
            if D[j] in tempDict.keys():
                tempDict[D[j]].add(D[j+1])
            else:
                tempDict[D[j]] = {D[j+1]}
        myDict[D[0]] = tempDict
    return myDict

def print_ndfa(D: dict):
    print("Non-Deterministic Finite Automaton")
    sDict = sorted(D.items())
    for state in sDict:
        print("\t" + state[0] + " transitions: " + str(sorted(state[1].items())))
    
def process(D: dict):
    batch = safe_open("Enter file with start-state and input", 'r', "File not found.", default = 'ndfainputendin01.txt').read().split()
    operations = []
    myDict = D
    for b in batch:
        B = b.split(';')
        operations.append(B)
    for o in operations:
        print('\nStarting new simulation')
        print('Start state = ' + o[0])
        last_state = [o[0]]
        for r in range(1, len(o)):
            if len(last_state) == 1:
                print("\tInput = {}; new possible state(s) = {}".format(o[r], str(myDict[last_state[0]][o[r]])))
                last_state = list(myDict[last_state[0]][o[r]])     
            elif len(last_state) > 1:
                possible_states = []
                for ls in last_state:
                    if len(myDict[ls]) != 0:
                        if o[r] in myDict[ls].keys():
                            possible_states.extend(list(myDict[ls][o[r]]))
                last_state = possible_states.copy()
                s = set(last_state)
                print("\tInput = {}; new possible state(s) = {}".format(o[r], str(s)))
        print('Stop state(s) = ' + str(set(last_state)))
    
if __name__ == '__main__':
    myDict = read_ndfa(safe_open("Enter file with non-deterministic finite automaton", 'r', "File not found.", default = 'ndfaendin01.txt'))
    print_ndfa(myDict)
    process(myDict)