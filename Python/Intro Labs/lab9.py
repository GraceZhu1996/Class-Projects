#  Juan Contreras 81108859 and Toluwanimi Salako 30417945.  ICS 31 Lab sec 2.  Lab asst 9.
from random import *
from collections import namedtuple
print()
print('c1')
print()
alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
NUMBER_OF_STUDENTS = 200
NUMBER_OF_QUESTIONS = 20
NUMBER_OF_CHOICES = 4  # 3 choices is A/B/C, 4 choices is A/B/C/D, 5 is A/B/C/D/E

def generate_answers()->str:
    '''Returns a string of letters represnting the correct ansers to the test'''
    
    result = ''
    for i in range(NUMBER_OF_QUESTIONS):
        result += choice(alphabet[:4])
    return result
ANSWERS = generate_answers()

print()
print('c2')
print()

Student = namedtuple('Student', 'name answers scores total')

def id_generator()->str:
    '''Generates an 8 digit ID#'''
    result = ''
    for i in range(8):
        result += str(randrange(0,9))
    return result

def random_students():
    '''Creates a list of student namedtuples'''
    result = []
    for i in range(NUMBER_OF_STUDENTS):
        student_answers = generate_answers()
        student_scores = []
        total = 0
        for j in range(len(ANSWERS)):
            if student_answers[j] == ANSWERS[j]:
                student_scores.append(1)
                total+=1
            else:
                student_scores.append(0)
        result.append(Student(id_generator(), student_answers,student_scores,
                              total))
    return result

def total_score(S: Student)->str:
    '''Takes in a student and returns the total score'''
    return S.total

STUDENTS = random_students()

print()
def top_ten(S: [Student]):
    '''Takes in list of students and prints the top ten'''
    S.sort(key=total_score, reverse = True)
    for i in range(len(S)):
        if i < 11:
            print(S[i].name)
            
top_ten(STUDENTS)

def average_scores(S: [Student])->int:
    '''Takes list of students and returns their average'''
    total = 0
    for i in range(len(S)):
        total += S[i].total
    return total/len(S)

print("Average score of students is", average_scores(STUDENTS))
print()
print('c4')
print()
def generate_weighted_student_answer(a:str)->str:
    '''Generates weighted answer'''
    choices = alphabet[0:4]
    choices += str(a*randrange(0, 8))
    return choice(choices)

print(generate_weighted_student_answer('B'))
    
def generate_w_answers()->str:
    '''Generates weighted answers'''
    result = ''
    for i in range(NUMBER_OF_QUESTIONS):
        result += generate_weighted_student_answer(ANSWERS[i])
    return result

def random_students2()->[Student]:
    '''Creates a list of student namedtuples'''
    result = []
    for i in range(NUMBER_OF_STUDENTS):
        
        student_answers = ''
        student_scores = []
        total = 0
        student_answers = generate_w_answers()
        for j in range(len(ANSWERS)):
            if student_answers[j] == ANSWERS[j]:
                student_scores.append(1)
                total+=1
            else:
                student_scores.append(0)
        result.append(Student(id_generator(), student_answers,student_scores,
                              total))
    return result

STUDENTS = random_students2()
STUDENTS.sort(key=total_score, reverse = True)

print()
top_ten(STUDENTS)
        
print("Average score of students is", average_scores(STUDENTS))

print()
print('c5')
print()
def question_weights(S: [Student])-> [int]:
    '''takes a list of Student records and returns a list of numbers, one number for each question on the test, where each number is the number of students who answered that question incorrectly.
    '''
    result = []
    for j in range(NUMBER_OF_QUESTIONS):
        result.append(0)
    for j in range(NUMBER_OF_QUESTIONS):
        for s in S:
            if s.scores[j] == 0:
                result[j] += 1
    return result
Q_WEIGHT = question_weights(random_students2())

def Student_weighted_score(S: [Student], w: [int])-> [Student]:
    '''Takes in list of students and list of weighted answers, and returns
    the list based with changed total scores.'''
    result = []
    for s in S:
        new_scores = []
        new_total = 0
        for i in range(len(s.scores)):
            new_scores.append(s.scores[i]*w[i])
            new_total += s.scores[i]*w[i]
        result.append(Student(s.name, s.answers, new_scores, new_total))
    return result

STUDENTS = Student_weighted_score(STUDENTS, Q_WEIGHT)

print()
top_ten(STUDENTS)
        
print("Average score of students is", average_scores(STUDENTS))

print()
print('d1a')
print()
def calculate_GPA(G: [])->float:
    '''Takes in a list of letter grades and returns their G.P.A'''
    total = 0
    for g in G:
        if g == 'A':
            total += 4
        elif g == 'B':
            total += 3
        elif g == 'C':
            total += 2
        elif g == 'D':
            total += 1
        elif g == 'F':
            total += 0
    return total/len(G)
print()
print('d1b')
print()

def calculate_GPA2(G: [])->float:
    GPA = {'A+': 4.3, 'A': 4.0, 'A-':3.7, 'B+': 3.3, 'B': 3.0,
           'B-': 2.7, 'C+':2.3, 'C':2.0, 'C-':1.7, 'D+': 1.3, 'D':1.0,
           'D-':.7, 'F+':.3,'F':0}
    total = 0
    for g in G:
        total += GPA[g]
    return total/len(G)

assert calculate_GPA(['A', 'C', 'A', 'B', 'A', 'F', 'D']) == 2.5714285714285716
assert calculate_GPA2(['A', 'C', 'A', 'B', 'A', 'F', 'D']) == 2.5714285714285716

print()
print('d2')
print()

def flatten_2D_list(L: [])-> []:
    '''Takes in table of lists and returns a flattened list'''
    result = []
    for l in L:
        result.extend(l)
    return result

assert (flatten_2D_list([[1, 3, 2], [3, 5, 1], [7, 5, 1], [3, 2], [9, 4]]) == 
	[1, 3, 2, 3, 5, 1, 7, 5, 1, 3, 2, 9, 4])

print()
print('d3')
print()

def skip_every_third_item(L: []):
    '''takes in a list and prints each item on the list except every third
    item'''
    j = 1
    for l in L:
        if j < 3:
            print(l)
            j+=1
        else:
            j=1
        
L = ['If', 'you', '432234', 'did', 'the', '9834234', 'exercise', 'correctly',\
      '534523423','this', 'should', '1044323', 'be', 'readable']
skip_every_third_item(L)
print()
print('d3b')
print()
def skip_every_nth_item(L: [], n: int):
    '''Takes in list and int and prints each term except the nth term'''
    j = 1
    for l in L:
        if j < n:
            print(l)
            j+=1
        else:
            j=1
            
skip_every_nth_item(L, 3)

print()
print('d4')
print()

work_week = ['Bob', 'Jane', 'Kyle', 'Larry', 'Brenda', 'Samantha', 'Bob', 
             'Kyle', 'Larry', 'Jane', 'Samantha', 'Jane', 'Jane', 'Kyle', 
             'Larry', 'Brenda', 'Samantha']

def tally_days_worked(E: [])->'dictionary':
    '''Takes list of workers for amount worked in a week and returns how many days each worker worked'''
    result = {}
    for n in E:
        if n in result:
                d = {n: result[n] + 1}
        else:
                d = {n: 1}
                
        result.update(d)

    return result
print (tally_days_worked(work_week))
