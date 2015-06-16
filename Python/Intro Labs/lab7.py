# Nolan Brown 82592624 and Tolu Salako 30417945. ICS 31 Lab sec 2. Lab asst 7.

#
#c1
#
print("===C===")

from random import randrange

ln = open("surnames.txt", 'r').read()
key = str.maketrans("1234567890.,'", "             ")
ln = ln.translate(key)
last_names = ln.split()

fn = open("femalenames.txt", 'r').read()
fn = fn.translate(key)
female_names = fn.split()

mn = open("femalenames.txt", 'r').read()
mn = mn.translate(key)
male_names = mn.split()

def random_names(i: int) -> [str]:
    ''' takes an integer and returns a list of that many strings'''
    result = []
    for j in range(i):
        lastname = single_random_name(last_names)
        firstname = ""
        if randrange(0, 2) > 0:
            firstname = single_random_name(male_names)
        else:
            firstname = single_random_name(female_names)
        result.append(lastname + " " + firstname)
    return result

def single_random_name(s: [str]) -> str:
    '''Takes in a list of names and returns a name from the list'''
    return s[randrange(0, len(s))]

print(random_names(5))


#
#d1
#
print("===D===")

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


dictionary = open("wordlist.txt", 'r').read()
dictionary = dictionary.replace("'s", " ").replace("A'", " ")

dic = dictionary.split()

def Caesar_break (s: str) -> str:
    '''Takes a cyphered string and returns a normal one'''
    ans = ""
    L = s.split()
    for j in L:
        for i in range(1, 26):
            result = Caesar_decrypt (j, i)
            if result.replace(" ", "") in dic:
                ans += result
    return ans
assert(Caesar_break("xajwpnb jyyunb kjwjwj") == " oranges apples banana")
print(Caesar_break("xajwpnb jyyunb kjwjwj"))


#
#e1
#
print("===E===")
def copy_file(s: str):
    
    infile_name = input("Please enter the name of the file to copy: ")
    infile = open(infile_name, 'r')
    outfile_name = input("Please enter the name of the new copy:  ")
    outfile = open(outfile_name, 'w')

    if s == 'line numbers':
        i = 1
        for line in infile:
            outfile.write("{:6}: {}".format(i, line))
            i+= 1
    elif s == 'Gutenberg trim':
        read = infile.read()
        read = read[read.index("*** START"): read.index("*** END")]
        outfile.write(read)
    elif s == 'statistics':
        line_count = 0
        empty_lines = 0
        char = 0
        for line in infile:
            outfile.write(line)
            outfile.write
            if len(line.split()) > 0:
                line_count += 1
                char += len(line)
            else:
                empty_lines += 1
        outfile.write("\n\n\n{:6} lines in the file\n".format(line_count))
        outfile.write("{:6} empty lines\n".format(empty_lines))
        n = line_count+empty_lines
        outfile.write("{:6.3} average characters per line\n".format(n/char))
        outfile.write("{:6.3} average characters per non-empty line".format(line_count/char))
    else:
         for line in infile:
            outfile.write(line)
    infile.close()
    outfile.close()
copy_file('statistics')

    
