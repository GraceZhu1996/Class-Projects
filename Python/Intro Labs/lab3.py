# Annette Lee 14941440 and Toluwanimi Salako 30417945. ICS 31 Lab sec 2
print('-------------Part(c)-----------------')
print('-------------Part(c1)-----------------\n')

def abv(mth: 'Month') -> 'Abreviation':
    return (mth[0] + mth[1] + mth[2])
assert abv('January') == 'Jan'
assert abv('February') == 'Feb'

print('-------------Part(c2)-----------------\n')

def find_area_square (n):
    return (n**2)
assert find_area_square(2) == 4
assert find_area_square(4) == 16

print('-------------Part(c3)-----------------\n')

def find_area_circle(r):
    pi = 3.14
    return pi*(r**2)
assert find_area_circle(1) == 3.14
assert find_area_circle(5) == 78.5

print('-------------Part(c4)-----------------\n')

def print_even_numbers(n: 'list of numbers') -> 'even numbers':
    for i in n:
        if i%2 == 0:
            print(i)
print_even_numbers([2, 47, 31, 99, 20, 19, 23, 105, 710, 1004])

print('\n-------------Part(c5)-----------------\n')

def calculate_shipping (w: 'Weight of a package'):
    if w < 2:
        return 2
    elif w==2 or w < 10:
        return 5
    elif w > 10:
        amt = 5 + 1.5*(w-10)
        return amt
assert calculate_shipping(1.5) == 2
assert calculate_shipping(7) == 5
assert calculate_shipping(15) == 12.5

print('\n-------------Part(c6)-----------------\n')

import tkinter
my_window = tkinter.Tk()
my_canvas = tkinter.Canvas(my_window, width = 500, height = 500)
my_canvas.pack()

def create_square (x, y, length):
    my_canvas.create_rectangle(x, y, x + length, y + length)
create_square(100, 100, 200)

print('\n-------------Part(c7)-----------------\n')

def create_circle (x,y,d1,d2):
    my_canvas.create_oval(x,y,d1,d2)
create_circle(100, 100, 300, 300)

tkinter.mainloop()
print('-------------Part(d)-----------------')
print('-------------Part(d1)-----------------\n')
from collections import namedtuple
Restaurant = namedtuple('Restaurant', 'name cuisine phone dish price')
RL = [
    Restaurant("Thai Dishes", "Thai", "334-4433", "Mee Krob", 12.50),
    Restaurant("Nobu", "Japanese", "335-4433", "Natto Temaki", 5.50),
    Restaurant("Nonna", "Italian", "355-4433", "Stracotto", 25.50),
    Restaurant("Jitlada", "Thai", "324-4433", "Paht Woon Sen", 15.50),
    Restaurant("Nola", "New Orleans", "336-4433", "Jambalaya", 5.50),
    Restaurant("Noma", "Modern Danish", "337-4433", "Birch Sap", 35.50),
    Restaurant("Addis Ababa", "Ethiopian", "337-4453", "Yesiga Tibs", 10.50) ]

def restaurant_price (RC):
    return RC.price
assert restaurant_price(RL[0]) == 12.5
assert restaurant_price(RL[-1]) == 10.5

print('\n-------------Part(d2)-----------------\n')
#RL.sort(key=restaurant_price)
print(RL)

print('\n-------------Part(d3)-----------------\n')
def costliest (RP):
    RP.sort(key=restaurant_price)
    return RP[-1].name
assert costliest(RL) == 'Noma'
print(RL)

print('\n-------------Part(d4)-----------------\n')
def costliest2(RP):
    a = sorted(RP)
    return a[-1].name
print(costliest2(RL))

print('\n-------------Part(e)-----------------\n')
print('-------------Part(e1)-----------------\n')
Book = namedtuple ('Book', 'author title genre year price instock')
BLI [
    Book[ "Tolu", "The King Named Tolu", "fiction",2013,100,1000),
    Book[ "Tolu", "Tolu the Evil King", "Biography", 2014,125,2000),
    Book[ "Bob", "The little Train", "Children", 2009,25,100) ]

