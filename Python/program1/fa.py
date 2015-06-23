# Submitter: tsalako(Salako, Toluwanimi)
# Partner  : nayanp(Patel, Nayan)
# We certify that we worked cooperatively on this programming
#   assignment, according to the rules for pair programming
from goody import safe_open
from _collections import defaultdict

def read_fa(data)-> dict:
    DATA = data.read().split()
    myDict = defaultdict(defaultdict)
    for e in DATA:
        D = e.split(';')
        tempDict = defaultdict(str)
        for j in range(1, len(D), 2):
            tempDict[D[j]] = D[j+1]
        myDict[D[0]] = tempDict
    return myDict

if __name__ == '__main__':
    theDict = read_fa(safe_open("Enter file with finite automaton", 'r', "File not found.", default = 'faparity.txt'))
    print("Finite Automaton Description")
    sDict = sorted(theDict.items())
    for state in sDict:
        print("\t" + state[0] + " transitions: " + str(sorted(state[1].items())))
        
    batch = safe_open("Enter file with start-state and input", 'r', "File not found.", default = 'fainputparity.txt').read().split()
    operations = []
    
    for b in batch:
        B = b.split(';')
        operations.append(B)
    for o in operations:
        print('\nStarting new simulation')
        print('Start state = ' + o[0])
        last_state = o[0]
        for r in range(1, len(o)):
            if o[r] != 'x':
                print("\tInput = {}; new state = {}".format(o[r], str(theDict[last_state][o[r]])))
                last_state = theDict[last_state][o[r]]
            else:
                last_state = 'None'
                print("\tInput = {}; new state = {}".format(o[r], "illegal input: terminated"))
        print('Stop state = ' + last_state)   