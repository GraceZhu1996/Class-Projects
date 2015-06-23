import re

# Use day_dict and is_leap_year in your tomorrow function

day_dict ={ 1 : 31,
            2 : 28,
            3 : 31,
            4 : 30,
            5 : 31,
            6 : 30,
            7 : 31,
            8 : 31,
            9 : 30,
           10 : 31, 
           11 : 30,
           12 : 31} 

def is_leap_year(year:int)->bool:
    return (year%4 == 0 and year%100 != 0) or year%400==0

def days_in(month:int,year:int)->int:
    return (29 if month==2 and is_leap_year(year) else day_dict[month])


def tomorrow(date:str)->str:
    pass



if __name__ == '__main__':
    import driver, prompt,traceback
    while True:
        date = prompt.for_string('Enter a date to test (quit to start driver)')
        if date == 'quit':
            break;
        try:
            print('tomorrow=',tomorrow(date))
        except:
            print('tomorrow raised exception')
            traceback.print_exc()
        
    driver.driver()
