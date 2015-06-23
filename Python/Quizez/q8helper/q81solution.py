import random
from goody         import irange
from priorityqueue import PriorityQueue
from performance   import Performance


def setup(N):
    global pq
    pq = PriorityQueue([random.randrange(0, N) for i in range(0, N)])
        
def code(N):
    global pq
    for i in range(N):
        pq.remove()
 
for i in irange(0, 8):
    N = 10000*2**i
    P = Performance(lambda: code(10000), lambda: setup(N), 8, title = "\nPriority Queue of size " + str(N))
    P.evaluate()
    P.analyze()