# tsalako(Salako, Toluwanimi)
# I certify that I worked alone on this quiz

import prompt,re
import math



def expand_re(pat_dict:{str:str}):
    KEYS = pat_dict.keys()
    for k in KEYS:
        for x,y in pat_dict.items():
            if k in y:
                pat_dict[x] = re.sub(r"#{}#".format(k), "({})".format(str(pat_dict[k])) , pat_dict[x])
    #pat_dict['integer'] = re.sub(r"#digit#", "({})".format(str(bc['digit'])) , pat_dict['integer'])

            
class Point:
    
    def __init__(self,x,y):
        self.x = x; self.y = y
        assert type(x) == int, "Point. __init__: x must be int instead of {}".format(type(x))
        assert type(y) == int, "Point.__init__: y must be int instead of {}".format(type(x))
        

    def __repr__(self):
        return ("Point({},{})".format(self.x, self.y))


    def __str__(self):
        return ("(x={},y={})".format(self.x, self.y))
    

    def __bool__(self):
        if (self.x, self.y) == (0,0):
            return False
        else:
            return True
        

    def __add__(self,right):
        if not type(right) == Point:
            raise TypeError("Point.__add__: " + str(right) + " should be of type Point")
        return Point(self.x + right.x, self.y + right.y)

    def __mul__(self,right):
        if not type(right) == int:
            raise TypeError("Point.__mul__: " +str(right) + " should be of type Int")
        return Point(self.x*right, right*self.y)
        

    def __rmul__(self,left):
        if not type(left) == int:
            raise TypeError("Point.__rmul__: " +str(left) + " should be of type Int")
        return Point(self.x*left, left*self.y)
        

    def __lt__(self,right):
        if not (type(right) == int or type(right) == float or type(right) == Point):
            raise TypeError("Point.__lt__: " +str(right) + " should be of type Int, float, or Point")
        if type(right) == int or type(right) == float:
            return (math.sqrt(self.x + self.y) < right)
        elif type(right) == Point:
            return (math.sqrt(self.x + self.y) < math.sqrt(right.x + right.y))
        
        

    def __getitem__(self,index):
        if type(index) == int:
            if index == 0:
                return self.x
            elif index == 1:
                return self.y
            else:
                raise IndexError("Point.__getitem__: " +str(index) + " is out of range.")
        elif type(index) == str:
            if index == 'x':
                return self.x
            elif index == 'y':
                return self.y
            else:
                raise IndexError("Point.__getitem__: " +str(index) + " is out of range.")
        else:
            raise IndexError("Point.__getitem__: " + str(index) + " should be str or int.")
        
        
    def __call__(self,x,y):
        assert type(x) == int,"Point.__call__: " + str(x) + "should be of type Int."
        assert type(y) == int, "Point.__call__: " +str(y) + "should be of type Int."
        self.x = x
        self.y = y
        
        



from collections import defaultdict
class History:
    def __init__(self):
        self.__dict__['history'] = defaultdict(list)
    
    def __getattr__(self,name):
        count = name.count("_prev")
        n = name.strip('_prev')
        if count == 0:
            return self.__dict__[n]
        else:
            if n not in self.__dict__['history'].keys():
                raise NameError("History.__getattr__: name " +n + " not found.")
            return self.__dict__['history'][n][-count - 1] if len(self.__dict__['history'][n]) > (count) else None
        
    def __setattr__(self, name, value):
        if not name.find("_prev") == -1:
            raise NameError("History.__setattr__:" + name+ " cannot contain '_prev'")
        n = name.strip("_prev")
        self.__dict__['history'][n].extend([value])
        self.__dict__[n] = value
    def __getitem__(self, index):
        if index == 0:
            current_values = self.__dict__.copy()
            current_values.pop('history')
            return current_values
        elif index < 0:
            result = dict()
            n = index -1
            for k in self.__dict__['history'].keys():
                result[k] = self.__dict__['history'][k][n] if len(self.__dict__['history'][k]) > (-1*index) else None
            return result
#         elif index == -1:
#             result = dict()
#             for k in self.__dict__['history'].keys():
#                 result[k] = self.__dict__['history'][k][-2]
#             return result
#         elif index == -2:
#             result = dict()
#             for k in self.__dict__['history'].keys():
#                 result[k] = self.__dict__['history'][k][-3] if len(self.__dict__['history'][k]) > (-1*-2) else None
#             print(result)
#             return result
        else:
            raise IndexError("Index not found.")

if __name__ == '__main__':
    
    if prompt.for_bool('Test expand?',True):
        pd = dict(digit=r'\d', integer=r'[=-]?#digit##digit#*')
        expand_re(pd)
        print('result =',pd)
        # produces and prints the dictionary {'digit': '\\d', 'integer': '[=-]?(\\d)(\\d)*'}
        
        pd = dict(integer       =r'[+-]?\d+',
                  integer_range =r'#integer#(..#integer#)?',
                  integer_list  =r'#integer_range#(?,#integer_range#)*',
                  integer_set   =r'{#integer_list#?}')
        expand_re(pd)
        print('result =',pd)
        # produces and prints the dictionary 
        # {'integer'      : '[+-]?\\d+',
        #  'integer_range': '([+-]?\\d+)(..([+-]?\\d+))?',
        #  'integer_list' : '(([+-]?\\d+)(..([+-]?\\d+))?)(?,(([+-]?\\d+)(..([+-]?\\d+))?))*',   
        #  'integer_set'  : '{((([+-]?\\d+)(..([+-]?\\d+))?)(?,(([+-]?\\d+)(..([+-]?\\d+))?))*)?}'
        # }
        
        pd = dict(a='correct',b='#a#',c='#b#',d='#c#',e='#d#',f='#e#',g='#f#')
        expand_re(pd)
        print('result =',pd)
        # produces/prints the dictionary 
        # {'d': '(((correct)))',
        #  'c': '((correct))',
        #  'b': '(correct)',
        #  'a': 'correct',
        #  'g': '((((((correct))))))',
        #  'f': '(((((correct)))))',
        #  'e': '((((correct))))'
        # }
    
    import driver
    driver.driver()
