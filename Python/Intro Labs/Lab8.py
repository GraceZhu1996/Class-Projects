# Adam Milbes 46682951 Toluwanimi Salako 30417945

from collections import namedtuple
print ('PART C')
Dish = namedtuple('Dish', 'name price calories')

def read_menu_with_count(x:str)->[Dish]:
    file_text = open(x, 'r').read()
    L = file_text.splitlines()
    dishes = []
    for j in range(len(L)):
        if j > 0:
            R =(L[j].split('\t'))
            dishes.append(Dish(R[0], float(R[1][1:]), int(R[2])))
    return dishes

assert (read_menu_with_count('menu1.txt') == [Dish(name='Chicken Biryani', price=14.99, calories=450),
                                              Dish(name='Lamb Vindaloo', price=12.00, calories=560),
                                              Dish(name='Samosa', price=3.50, calories=300)])
    
assert(read_menu_with_count('menu2.txt')[0] == Dish(name='Steak Sandwich', price=2.5, calories=300))


print ('PART C2')
def read_menu(x:str)->[Dish]:
    file_text = open(x, 'r').read()
    L = file_text.splitlines()
    dishes = []
    for j in range(len(L)):
        if j > 0:
            R =(L[j].split('\t'))
            dishes.append(Dish(R[0], float(R[1][1:]), int(R[2])))
    return dishes
assert(read_menu('menu3.txt')[0] == Dish(name='Wet Burrito', price=6.0, calories=700))

print ('PART C3')
def write_menu(L : [Dish], f: str):
    newfile = open(f+'.txt', 'x')
    s = str(len(L)) + '\n'
    newfile.write(s)
    for i in L:
        newfile.write('{}\t${:4.2f}\t{:3}\n'.format(i.name, i.price, i.calories))
    newfile.flush()

D = [Dish(name='Chicken Biryani', price=14.99, calories=450),
                                              Dish(name='Lamb Vindaloo', price=12.00, calories=560),
                                              Dish(name='Samosa', price=3.50, calories=300)]
#NOTE:REMOVE THE NUMBER SIGN FOR ASSERTION STATEMENT
#write_menu(D, 'anyfile')

print ('PART D')
Course = namedtuple('Course', 'dept num title instr units')
ics31 = Course('ICS', '31', 'Intro to Programming', 'Kay', 4.0)
ics32 = Course('ICS', '32', 'Programming with Libraries', 'Thornton', 4.0)
wr39a = Course('Writing', '39A', 'Intro Composition', 'Alexander', 4.0)
wr39b = Course('Writing', '39B', 'Intermediate Composition', 'Gross', 4.0)
bio97 = Course('Biology', '97', 'Genetics', 'Smith', 4.0)
mgt1  = Course('Management', '1', 'Intro to Management', 'Jones', 2.0)
  
Student = namedtuple('Student', 'ID name level major studylist')
sW = Student('11223344', 'Anteater, Peter', 'FR', 'PSB', [ics31, wr39a, bio97, mgt1])
sX = Student('21223344', 'Anteater, Andrea', 'SO', 'CS', [ics31, wr39b, bio97, mgt1])
sY = Student('31223344', 'Programmer, Paul', 'FR', 'COG SCI', [ics32, wr39a, bio97])
sZ = Student('41223344', 'Programmer, Patsy', 'SR', 'PSB', [ics32, mgt1])

StudentBody = [sW, sX, sY, sZ]


def Students_at_level(S:[Student],c:str)->list:
    result =[]
    for i in S:
        if i.level==c:
            result.append(i)
    return result

print(Students_at_level(StudentBody,'FR')[0].name)

print ('PART D2')
def Students_in_majors(S:[Student],m:str)->list:
    result= []
    for i in S:
        if i.major==m:
            result.append(i)
    return result

print(Students_in_majors(StudentBody,'CS')[0].name)


print ('PART D3')
def Students_in_class(S:[Student],d:str, c:str) -> [Student]:
    result = []
    
    for i in S:
        SL = []
        for j in i.studylist:
            SL.append(j.dept + j.num)
        if d+c in SL:
            result.append(i)
    return result

print(Students_in_class(StudentBody, 'ICS', '32'))
                                                     
print ('PART D4')
def Student_names(S:[Student])->list:
    names=[]
    for i in S:
        names.append(i.name)
    return names

print(Student_names(StudentBody))


print ('PART D5')
Sim=[]
for i in StudentBody:
    if i.major=='CS':
        print (i)
        Sim.append(i)
    elif i.major=='CSE':
        print(i)
        Sim.append(i)
    elif i.major=='BIM':
        print(i)
        Sim.append(i)
    elif i.major=='INFX':
        print(i)
        Sim.append(i)
    elif i.major=='CGS':
        print(i)
        Sim.append(i)
    elif i.major=='SE':
        print(i)
        Sim.append(i)
    elif i.major=='ICS':
        print(i)
        Sim.append(i)

for i in StudentBody:
    if i.major=='CS':
        print (i.name)
    elif i.major=='CSE':
        print(i.name)
    elif i.major=='BIM':
        print(i.name)
    elif i.major=='INFX':
        print(i.name)
    elif i.major=='CGS':
        print(i.name)
    elif i.major=='SE':
        print(i.name)
    elif i.major=='ICS':
        print(i.name)

print(len(Sim))

n = 0

for i in Sim:
    if i.level == 'SR':
        n+=1
        print (i.name)

print(n)

print(n/len(Sim))

k=0
for i in Sim:
    if i.level == 'FR':
        k+=1
print(k)

total_units = 0
total_fr_ics = 0
for i in StudentBody:
    if i.level=='FR' and i in Students_in_class(StudentBody, 'ICS', '31'):
        total_fr_ics += 1
        for o in i.studylist:
            total_units += o.units
print(total_units/total_fr_ics)

print('Part E')




