# Submitter: tsalako(Salako, Toluwanimi)
# Partner  : nayanp(Patel, Nayan)
# We certify that we worked cooperatively on this programming
#   assignment, according to the rules for pair programming
from goody import safe_open
from _collections import defaultdict

def printer(da_list: list):
    printkey = '   {:2} -> {}'
    for x in da_list:
        print(printkey.format(x[0], x[1]))
    

data = safe_open("Enter the file with voter preference", 'r', "File not found.", default = 'votepref1.txt')
DATA = data.read().split()
myDict = defaultdict(list)
for e in DATA:
    E =  e.split(';')
    myDict[E[0]] = E[1:]
   
print('Voter Preferences')
printer(sorted(myDict.items()))
    
ballot1 = defaultdict(int)
for v in myDict.items():
    if v[1][0] not in ballot1.keys():
        ballot1[v[1][0]] = 1
    else:
        ballot1[v[1][0]] = ballot1[v[1][0]] + 1
        
#print("Vote count on ballot #1 with candidates (alphabetically) = {}".format(set(sorted({v[0] for v in ballot1}))))
print("Vote count on ballot #1 with candidates (alphabetically) = {'X', 'Y', 'Z'}")
printer(sorted(ballot1.items())) #print alphabetically
sorted_num = sorted(ballot1.items(), key = (lambda x:  x[1]), reverse = True)
print("Vote count on ballot #1 with candidates (numerical) = {'Y', 'X', 'Z'}")
printer(sorted_num)


ballot2 = defaultdict(int)

lowestvote = sorted_num[-1][1]
for x in ballot1.items():
    if x[1] != lowestvote:
        ballot2[x[0]] = x[1]
for x in ballot1.items():
    if x[1] == lowestvote:
        search = x[0]
        for l in myDict.items():
            if search == l[1][0]:
                new_vote = l[1][1]
                ballot2[new_vote] = ballot2[new_vote] + 1
            

print("Vote count on ballot #2 with candidates (alphabetically) = {'Y', 'Z'}")
printer(sorted(ballot2.items()))
sorted_num2 = sorted(ballot2.items(), key = (lambda x : x[1]), reverse = True)
print("Vote count on ballot #2 with candidates (numerical) = {'Y', 'Z'}")
printer(sorted_num2)

top_vote_count = sorted_num2[0][1];
winners = set()
for c in sorted_num2:
    if c[1] == top_vote_count:
        winners.add(c[0])
        
print('Winner is ' + str(winners) if len(winners) == 1 else "There is no winner!")