# A generator for iterating through any iterable (mostly used to
#  iterate through the letters in a string).
# It is present and called to ensure that your generator code works on
#   general iterable parameters (not just on a string, list, etc.)
# For example, although we can call len(string) we cannot call
#   len(lets(string)), so the generator functions you write should not
#   call len on their parameters

def lets(string):
    for i in range(len(string)):
        yield string[i]

def transform(iterable,f):
    pass


def running_count(iterable,p):
    pass

        
def n_with_pad(iterable ,n ,pad = None):
    pass

        
def sequence(*args):
    pass


def alternate(*args):
    pass


                
                
if __name__ == '__main__':
    import driver
    driver.driver()
