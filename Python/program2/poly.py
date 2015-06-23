# Submitter: tsalako(Salako, Toluwanimi)
# Partner  : nayanp(Patel, Nayan)
# We certify that we worked cooperatively on this programming
#   assignment, according to the rules for pair programming
from _collections import defaultdict

def sort_poly(poly) -> list: #sorts the polynomials how it should be
    return sorted(poly, key = lambda d: d[1], reverse = True)
def switch_tups(t)-> tuple:
        result = tuple()
        for x,y in t:
            result += ((y,x),)
        return result
class Poly:
    def __init__(self, *args):
        if len(args) > 0 and (0,0) not in args and not (0,1) in args:
            check = args[0][1]
            self.sorted_poly = sort_poly(args)  
        else:
            self.sorted_poly = []
        for k in range(0, len(args)):  #Assertion set 1
            if len(self.sorted_poly) > 0: assert (args[k] == self.sorted_poly[k]), 'Power must appear in decreasing order in the arguments.' 
        for k in range(1, len(args)):
            if (args[k][1] == check):
                raise AssertionError( 'Power must appear in decreasing order in the arguments.')
                check = args[k][1]
        for c in args:  #Assertion set 2
            assert (type(c[0]) == int or type(c[0]) == float), 'Each coefficient must be an int or a float value'
            assert (type(c[1]) == int), 'Each power must be an int whose value is >= 0'
            if type(c[1]) == int:
                assert(c[1] >= 0), 'Each power must be an int whose value is >= 0'
        
        self.terms = defaultdict(int) #Dict with coefficients and powers
        for coordinates in args:
            if coordinates[0] != 0:
                self.terms[coordinates[1]] = coordinates[0]
        
    
    def __repr__(self) -> str:
        return "Poly{}".format(str(tuple(self.sorted_poly))) if len(self.sorted_poly) > 0 else "Poly()"
    
    def __str__(self) -> str:
        result = ''
        co = []
        power = []
        if len(self.sorted_poly) == 0:
            return '0'
        for x, y in self.sorted_poly:
            co.append(x)
            power.append(y)
        for i in range(0, len(co)):
#             if not co[i] == co[-1]:
            if co[i] <0:
                result += "-" if co[i] == -1 else str(co[i])
            elif co[i]>0:
                result +=  "+" if co[i] == 1 else "+" + str(co[i]) 

            if power[i] == 1:
                result += "x"
            elif power[i] == 0:
                if co[i] == 1 or co[i] == -1: result += '1'
            else:
                result += "x^" + str(power[i]) 

        result = result[1:] if result[0] == '+'else result
            
        new_result = result[1:].replace('+', ' + ')
        new_result = new_result.replace('-', ' - ')
        return result[0] + new_result
                
    def __bool__(self) -> bool:
        if not len(self.sorted_poly) == 0:
            return True
        else:
            return False
    def __len__(self)-> int:
        'Returns the  highest power in the polynomial'
        return self.sorted_poly[0][1] if len(self.sorted_poly) != 0 else 0
    def __call__(self, x):
        return sum(c*(x**p) for c,p in self.sorted_poly)
    def __iter__(self) -> tuple:
       return (x for x in self.sorted_poly)
    def __getitem__(self, power):
        if not type(power) == int:
            raise TypeError(str(power) + " should be a int.")
        if power == 0:
            return self.terms[0] if 0 in self.terms.keys() else 0
        if not power > 0:
            raise TypeError(str(power) + " should be > 0.")
        for x in self: 
            if x[1] == power:
                return x[0]
    def __setitem__(self,power,coefficient):
        if not type(power) == int:
            raise TypeError(str(power) + " should be a int.")
        if not power > 0:
            raise TypeError(str(power) + " should be > 0.")
        if not coefficient == 0:
            self.terms[power] = coefficient
        else:
            self.terms.pop(power)
        self.sorted_poly = sort_poly(switch_tups(tuple(self.terms.items())))
    def __delitem__(self,power):
        if not type(power) == int:
            raise TypeError(str(power) + " should be a int.")
        if not power >= 0:
            raise TypeError(str(power) + " should be >= 0.")
        if power in self.terms.keys():
            self.terms.pop(power)
        self.sorted_poly = sort_poly(switch_tups(tuple(self.terms.items())))
    def _add_term(self, coefficient, power):
        if not (type(coefficient) == int or type(coefficient) == float):
            raise TypeError(str(coefficient) + " should be an int or float.")
        if not type(power) == int:
            raise TypeError(str(power) + " should be a int.")
        if not power >= 0:
            raise TypeError(str(power) + " should be >= 0.")
        if (power not in self.terms.keys() and not coefficient == 0):
            self.terms[power] = coefficient
        elif power in self.terms.keys():
            self.terms[power] += coefficient
            if self.terms[power] == 0:
                self.terms.pop(power)
        self.sorted_poly = sort_poly(switch_tups(tuple(self.terms.items())))
    def __add__(self, right):
        result = tuple()
        if type(right) == Poly:
            for x,y in zip(self,right):
                if x[1] == y[1]:
                    result += ((x[0] + y[0], x[1]),)
            #return Poly(result)
        elif type(right) == int:
            if 0 in self.terms.keys(): 
                return (self.terms.copy()[0] + right)
        self.sorted_poly = sort_poly(switch_tups(tuple(self.terms.items())))
    def __sub__(self, right):    
        if type(right) == Poly:
            return ((x[0] - y[0]) for x,y in zip(self,right) if x[1] == y[1])
        elif type(right) == int:
            if 0 in self.terms.keys(): 
                return (self.terms.copy()[0] - right)
        self.sorted_poly = sort_poly(switch_tups(tuple(self.terms.items())))
    def __pos__(self):
        return self
    def __neg__(self):
        result = tuple()
        for x,y in self.sorted_poly:
            result += ((-1 * x,y),)
        print("P: " + str(Poly(result)))
        return Poly(result)
    def __mul__(self, right):
        pass
    def differentiate(self):
        result = tuple()
        for x,y in self.sorted_poly:
            if not y-1 == 0: result += ((y * x,y-1),)
        print(result)
        return Poly(result)
if __name__ == '__main__':
    # Some simple tests; you can comment them out and/or add your own before
    # the driver is called.
    print('Start simple tests')
    p = Poly((3,2),(-2,1), (4,0))
    print('  For Polynomial: 3x^2 - 2x + 4')
    print('  str(p):',p)
    print('  repr(p):',repr(p))
    print('  len(p):',len(p))
    print('  p(2):',p(2))
    print('  list collecting iterator results:',[t for t in p])
    print('  p+p:',p+p)
    print('  p+2:',p+2)
    print('  p*p:',p*p)
    print('  p*2:',p*2)
    print('End simple tests\n')
    import driver
    #driver.default_show_exception=True
    #driver.default_show_exception_message=True
    #driver.default_show_traceback=True
    driver.driver()     
