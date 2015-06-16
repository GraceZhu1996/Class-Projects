#BANDB

from collections import namedtuple
from datetime import datetime

Bedroom = namedtuple('Bedroom', 'number available')
Reservation = namedtuple('Reservation', 'name room date_in date_out reservation_num')
B_collection = []
live_rooms= []
R_collection = []

reservation = 1

def print_line(x:list):
    printer = ''
    for k in x:
        if not k.lower() == 'pl':
            printer += k
            printer += " "
    print (printer)

def Add_room(i: int):
    '''Adds the number of room, if it is doesn't exist'''
    if i not in live_rooms:
        B_collection.append(Bedroom(i, True))
        live_rooms.append(i)
    else:
        print("Sorry, can't add room " +str(i)+ " again; it's already on the list.")  

def Del_room(i: int):
    '''Deletes a bedroom'''
    error = True
    for n in B_collection:
        if n.number == i:
            error = False
            B_collection.remove(n)
            live_rooms.remove(n.number)
            L= []
            for j in R_collection:
                L.append(int(j.room))
            key = "Deleting room {} forces cancellation of this reservation: \n\
   {} arriving {} and departing  {} (Conf. #{})"
            print (L)
            for k in L:
                if n.number == k:
                    room = R_collection[L.index(k)]
                    print(key.format(room.room, room.name, room.date_in,
                                     room.date_out, room.reservation_num))
                    R_collection.remove(room)
        
            
    if error:
        print("Sorry, can't delete room", i,"; it is not in service now")

def available_room_list():
    '''Prints the list of available bedrooms'''

    print('Number of bedrooms in service:', len(live_rooms))
    print('-------------------------------------')
    if len(live_rooms) > 0:
        for i in live_rooms:
            print(i)

def new_reservation(R: [str]):
    '''Makes a new reservation'''
    global reservation
    if len(R) == 6:
        new_room = Reservation(R[4]+ " " +R[5], R[1], R[2], R[3], reservation)  
    elif len(R) == 7:
        new_room = Reservation(R[4]+ " " +R[5]+" "+R[6], R[1], R[2], R[3], reservation)

    '''Check for invalid dates'''
    key = "{} {} ({} to {});\n\t{}"
    error = "Sorry; can't reserve room "
    condition = check_reservation(new_room.date_in, new_room.date_out)
    if  condition == 'equal':
        print (key.format(error, new_room.room, new_room.date_in, new_room.date_out,
                "can't arrive and leave on the same day."))
        return
    elif not condition == 'True':
        print (key.format(error, new_room.room, new_room.date_in, new_room.date_out,
                "can't leave before you arrive."))          
        return

    '''Check if room has already been reserved'''
    L = []
    for l in R_collection:
        L.append(l.room)
    if new_room.room in L:
        i = L.index(new_room.room)
        r_room = R_collection[i]
        
        if check_reservation(new_room.date_out, r_room.date_in) == 'equal':
              
            reserve_room(new_room)
            return
        elif check_reservation(new_room.date_in, r_room.date_out) == 'True' or\
             check_reservation(new_room.date_in, r_room.date_in) == 'equal' or\
             (check_reservation(new_room.date_in, r_room.date_in) == 'True' and\
              check_reservation(new_room.date_out, r_room.date_out) == 'True'):
            print (key.format(error, new_room.room, new_room.date_in, new_room.date_out,
                "it's already booked (Conf. #" + str(r_room.reservation_num) +')'))          
            return

    reserve_room(new_room)

def reserve_room(r: Reservation):
    global reservation
    '''Adds room'''
    if int(r.room) in live_rooms:
        R_collection.append(r)
        print("Reserving room", r.room, "for", r.name,
        " -- Confirmation #" +str(len(R_collection)))
        print("\t(arriving", r.date_in, ", departing", r.date_out+")")
    else:
        print("Sorry; can't reserve room "+r.room+"; room not in service")
        return

    reservation += 1

def check_reservation(i: str, o: str):
    '''Returns true if the date in is less than date out'''
    date_in = datetime.strptime(i, "%m/%d/%Y")
    date_out = datetime.strptime(o, "%m/%d/%Y")
    if date_in == date_out:
        return 'equal'
    elif date_in < date_out:
        return 'True'
        
def print_reservation():
    key = "{:2} {:3} {:10s}  {:10s}   {:20s}"
    print("Number of reservations: " + str(len(R_collection)))
    print(key.format("No.", "Rm.","Arrive","Depart","Guest"))        
    print("-------------------------------------------------")
    count = 1
    for i in R_collection:
        print(key.format(i.reservation_num, i.room, i.date_in, i.date_out, i.name))
        count += 1

def reservation_delete(R:list, num:int)->list:
    for i in R_collection:
        if i.reservation_num == num:
            R.remove(i)
            return
    print("Sorry, can't cancel reservation; confirmation number",num)
            
        
def system(action: str):
    x = action.split()
    if x[0].lower() == 'ab':
        Add_room(int(action.strip()[2:]))
    elif x[0].lower() == 'bd':
        Del_room(int(action.strip()[2:]))
    elif x[0].lower() == 'bl':
        available_room_list()
    elif x[0].lower() == 'nr':
        new_reservation(x)
    elif x[0].lower() == 'pl':
        print_line(x)
    elif x[0].lower() == '**':
        None
    elif x[0].lower() == "rl":
        print_reservation()
    elif x[0].lower() == 'rd':
        reservation_delete(R_collection,int(x[1]))
        
        

batch = open('batch.txt').read()
file = batch.split("\n")


for k in file:
    system(k)    
