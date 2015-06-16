# Toluwanimi Salako 30417945 and Nabeel Alam #58231639. ICS 31 Lab sec 2. Lab asst Rohan Achar

print('''(C)''')
print('''(c.1)''')

def contains(i: str,s:str)->bool:
    '''The function checks if the second string occurs in the first string. If the second
    string does occur, the function returns True; if not, it returns False.'''
    return s in i

assert contains('banana', 'ana')
assert not contains('racecar', 'ck')

print('''(c.2)''')
def sentence_stats(s:str):
    "prints out the stats of a string"
    string_only = str.maketrans('*.,!?;:"', '        ')
    s = s.translate(string_only)
    each_word = s.split()
    j = 0
    print('Characters: ',len(s))
    print('Words: ', len(each_word))
    for i in each_word:
        j+= len(i)
    print('Average word length: ', j/len(each_word))
sentence_stats("I love UCI")
sentence_stats('***The ?! quick brown fox:  jumps over the lazy dog.')

print('''(c.3)''')

def initials(F: str) -> str:
    '''Takes in two strings and returns the capitalized initials'''
    F = F.upper()
    L = F.split()
    result = ""
    for i in range(len(L)):
        result += L[i][0]
    return result
assert initials('Bill Cosby') == 'BC'
assert initials('Guido van Rossum') == 'GVR'
assert initials('alan turing') == 'AT'

print('''(D)''')
print('''(d.1)''')

from random import randrange
for i in range(51):
    print(randrange(0,11))
for i in range(51):
    print(randrange(0,6))

print('''(d.2)''')
def roll2dice()->int:
    "takes no parameters and returns a number that reflects the random roll of two dice"
    return randrange(0,7)+randrange(0,7)
for i in range(51):
    print(roll2dice())

print('d3')
def distribution_of_rolls(i: int):
    '''Takes the number of times to roll two dice—and prints the distribution of
    the values'''
    ourvalues = []
    star = '*'
    for j in range(i):
        ourvalues.append(roll2dice())
    print("Distribution of dice rolls")
    for n in range(13):
        if n > 1:
            print("{:2}:    {:2} ({:4.1f}%) {}".format(n, ourvalues.count(n),\
                            ourvalues.count(n)/i * 100, star*ourvalues.count(n)))
    print('--------------------------------')
    print('\t', i, 'rolls')
distribution_of_rolls(200)

print('''(E)''')
print('''(e.1)''')

alphabet = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"

def Caesar_encrypt(s:str ,k: int) -> 'ciphertext':
    '''a string containing the message and an int for the key, indicating
    how far down the alphabet to find each substitute letter.
    Then returns the ciphertext'''
    result = ''
    for i in s.split():
        result = "{} {}".format(result, new_sentence(i, k))
    return result
    

def Caesar_decrypt(s:str, k: int) -> 'plaintext':
    '''a string containing the message and an int for the key, indicating
    how far down the alphabet to find each substitute letter.
    Then returns the plaintext'''
    result = ''
    for i in s.split():
        result = "{} {}".format(result, new_sentence(i, -k))
    return result

def new_sentence(r:str, p: int)->'translated word':
    '''takes a word and translates it based on the number.'''
    r = r.lower()
    result = ''
    for j in range(len(r)):
        key = str.maketrans(r[j], alphabet[alphabet.index(r[j]) + p])
        result = result + r[j].translate(key)
    return result
    

print(Caesar_encrypt('The cat jumped high', 2))
print(Caesar_decrypt('vjg ecv lworgf jkij', 2))

print('''(F)''')
print('''(f.1)''')
def print_line_numbers(s:[str]):
    '''Takes list of strings and prints each string preceded by a line number'''
    for i in range(len(s)):
        print("{:2}:  {}".format(i+1, s[i]))

print(print_line_numbers([ "Four score and seven years ago, our fathers brought forth on",
  "this continent a new nation, conceived in liberty and dedicated",
  "to the proposition that all men are created equal.  Now we are",
  "   engaged in a great 		civil war, testing whether that nation, or any",
  "nation so conceived and so dedicated, can long endure.        " ]))
def stats (s:[str]):
    '''Takes list of strings and prints statistics'''
    total_lines = 0
    empty_lines = 0
    total_chars = 0
    avg_char_per_line = 0
    avg_char_per_non_empty_lines = 0
    for a in s:
        if a = "":
            empty_lines += 1
        else:
            total_lines += 1
            total_chars += len(a)
        total_lines += empty_lines
