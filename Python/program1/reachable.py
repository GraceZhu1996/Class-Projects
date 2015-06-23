# Submitter: tsalako(Salako, Toluwanimi)
# Partner  : nayanp(Patel, Nayan)
# We certify that we worked cooperatively on this programming
#   assignment, according to the rules for pair programming

from goody import safe_open
from _collections import defaultdict
def read_graph(file)-> dict:
    DATA = file.read().split()
    myDict = defaultdict(set)
    for e in DATA:
        E =  e.split(';')
        myDict[E[0]].add(E[1])
    return myDict
def print_graph(myDict: dict):
    sortedDict = sorted(myDict.items())
    printkey = '   {:3} -> {}'
    print('Graph: source -> {destination} edges')
    for x in sortedDict:
        print(printkey.format(x[0], x[1]))
    
def reacheability(D: dict, x_in: str):    
    myDict = D
    
    if len(x_in) > 0:
        char = x_in[0]
        if char in myDict.keys():
            done = {char}  #Finished nodes
            prechecked = myDict[char].copy()   #Nodes to be scanned
            checking = True  
            
            while checking:
                for n in prechecked:
                    if n in myDict.keys():
                        s = myDict[n].copy()
                        for d in done:
                            if d in s:
                                s.remove(d)
                        prechecked = prechecked.union(s)
                    done.add(n)
                    prechecked.remove(n) 
                    break;
                if len(prechecked) == 0:
                    checking = False
            print("From " +char + " the reachable nodes are " + str(done))
        elif x_in.lower() == 'quit':
            cond = False
            print("Quitting...")
            return 0
            
        else:
            print("Error! Not a starting node. Please Re-", end='')




if __name__ == '__main__':
    theDict = read_graph(safe_open("Enter the name of the file representing a graph", 'r', "File not found.", default = 'graph1.txt'))
    print_graph(theDict)
    cond = True
    while cond:
        x_in = input("Enter a starting node: ")
        if reacheability(theDict, x_in) == 0:
            cond = False