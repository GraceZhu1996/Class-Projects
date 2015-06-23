from functools import reduce # for code_metric
from _collections import defaultdict

''' (5 pts) Define a recursive function named compare; it is passed two str arguments; it returns one of three 
str values: '<’, '=’, or '>’ which indicates the relationship between the first and second parameter. Hint: my 
solution compared strings to the empty string and compared one character in one string to one character in 
the other. Yours shouldn’t do much else (like you cannot use relational operators on the entire strings).'''

def separate(p,l)-> tuple:
    result = ([], [])
    for i in l:
        if p(i): result[0].append(i)
        else: result[1].append(i)
    return result

def is_sorted(s)->bool:
    return True if s == sorted(s) else False

  
def sort(l):
    def my_predicate(n):
        return True if n > l[0] else False
    if len(l) == 0:
        return []
    else:
        k = separate(my_predicate, l[1:])
        return sort(k[1]) + [l[0]] +  sort(k[0])

    
def compare(a,b):
    def compare_one(s,k):
        if s == k:
            return '='
        elif s > k:
            return '>'
        else:
            return '<'
    result = defaultdict(int)
    if len(a) == 0 and len(b) == 0:
        result['='] += 1
        return sorted(result.items(), key = lambda x:  x[1], reverse = True)[0][0]
    else:
        if len(a) == 0:
            result[compare_one("", b[0])] += 1
            result[compare("", b[1:])] += 1
        elif len(b) == 0:
            result[compare_one(a[0], "")] += 1
            result[compare(a[1:], "")] += 1
        else:
            result[compare_one(a[0], b[0])] += 1
            result[compare(a[1:], b[1:])] += 1
        return sorted(result.items(), key = lambda x:  x[1], reverse = True)[0][0]
def code_metric(file):
    pass





if __name__=="__main__":
    import predicate,random,driver
    from goody import irange
    
    driver.driver() # type quit in driver to return and execute code below
    
    print('Testing separate')
    print(separate(predicate.is_positive,[]))
    print(separate(predicate.is_positive,[1, -3, -2, 4, 0, -1, 8]))
    print(separate(predicate.is_prime,[i for i in irange(2,20)]))
    print(separate(lambda x : len(x) <= 3,'to be or not to be that is the question'.split(' ')))
     
    print('\nTesting is_sorted')
    print(is_sorted([]))
    print(is_sorted([1,2,3,4,5,6,7]))
    print(is_sorted([1,2,3,7,4,5,6]))
    print(is_sorted([1,2,3,4,5,6,5]))
    print(is_sorted([7,6,5,4,3,2,1]))
    
    print('\nTesting sort')
    print(sort([1,2,3,4,5,6,7]))
    print(sort([7,6,5,4,3,2,1]))
    print(sort([4,5,3,1,2,7,6]))
    print(sort([1,7,2,6,3,5,4]))
    l = [i+1 for i in range(30)]
    random.shuffle(l)
    print(l)
    print(sort(l))
    
    print('\nTesting sort')
    
    print('\nTesting compare')
    print(compare('','abc'))
    print(compare('abc',''))
    print(compare('',''))
    print(compare('abc','abc'))
    print(compare('bc','abc'))
    print(compare('abc','bc'))
    print(compare('aaaxc','aaabc'))
    print(compare('aaabc','aaaxc'))
    
    print('\nTesting code_metric')
    print(code_metric('cmtest.py'))
    print(code_metric('collatz.py'))
    print(code_metric('q5solution.py'))  # A function analyzing the file it is in
