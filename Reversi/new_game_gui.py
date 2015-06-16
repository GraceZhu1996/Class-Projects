#Toluwanimi Salako 30417945
import tkinter
import MsgBox

ROW = 0
COLUMN = 0
FIRST = ''
TL = ''

STICKY_ALL = tkinter.N + tkinter.S + tkinter.W + tkinter.E
BG = "#6B6BB2"
def check_options(row, column, first, tl, win)->(bool, 'Data'):
    X = 0
    Y = 0
    P1 = ''
    TL = ''
    C = False
    D = False
    I = False
    messages = []
    try:
        x = int(row)
        y = int(column)
        if x > 16 or y > 16:
            raise Exception("Both of your values must be less than or equal to 16.")
        elif x < 4 or y < 4:
            raise Exception("Both of your values must be greater than or equal to 4.")
        elif x%2 != 0 or y%2 != 0:
            raise Exception("Both of your values must be even integers.")
    except Exception as M:
        messages.append(M)
    else:
        X = x
        Y = y
        C = True

    one = first.lower()
    tl = tl.lower()
    if not (one == 'black' or one == 'white') or not (tl == 'black' or tl == 'white'):
        messages.append("Please enter black or white.")
    else:
        D = True
        P1 = one
        TL = tl

    try:
        p = win.lower()
        if not (p == 'most' or p == 'least'):
            raise Exception("Please enter 'most' or 'least'.")
    except Exception as M:
        messages.append(M)
    else:
        I = True
        
    
    if C and D and I:
        return (True, (X, Y, P1, TL))
    else:
        return (False, messages)


class StartUpWindow:
    def __init__(self):
        self._root_window = tkinter.Tk()
        self._root_window.title("RIVERSI - New Game")
        self._root_window.resizable(width = False, height = False) #I believe dialog windows shouldn't be resizable
        
        self._base = tkinter.Frame(master = self._root_window, background = BG)
        self._base.grid(
            row = 0, rowspan = 6, columnspan = 2,sticky = STICKY_ALL)
        
        self._title = tkinter.Label(master = self._base, text = "RIVERSI", background = BG).grid(row = 0, columnspan = 2, sticky = STICKY_ALL)
        self._ctext = tkinter.Label(master = self._base, text = "Enter numbers from 4 to 16.", background = BG).grid(row = 1, columnspan =2)
        self._rtext = tkinter.Label(master = self._base, text = "ROWS:", background = BG).grid(row = 2, sticky = tkinter.N + tkinter.S + tkinter.W)
        self._ctext = tkinter.Label(master = self._base, text = "COLUMNS:", background = BG, pady =5).grid(row = 3, sticky = tkinter.N + tkinter.S + tkinter.W)
        
        self._rows = tkinter.Entry(master = self._base)
        self._rows.grid(row = 2, column = 1, padx = 10, pady = 10, sticky = STICKY_ALL)
        self._columns= tkinter.Entry(master = self._base)
        self._columns.grid(row = 3, column = 1, padx = 10, pady = 10, sticky = STICKY_ALL)
        
        self._btext = tkinter.Label(master = self._base, text = "Enter 'black' or 'white'", background = BG).grid(row = 4, columnspan =2)
        
        self._ftext = tkinter.Label(master = self._base, text = "FIRST PLAYER:", background = BG).grid(row = 5, sticky = tkinter.N + tkinter.S + tkinter.W)

        
        self._fcolor = tkinter.Entry(master = self._base)
        self._fcolor.grid(row = 5, column = 1, sticky = tkinter.W, padx = 10)

        
        self._tltext = tkinter.Label(master = self._base, text = "TOP-LEFT COLOR:", background = BG, pady = 5).grid(row = 6, sticky = tkinter.N + tkinter.S + tkinter.W)
        self._tlcolor = tkinter.Entry(master = self._base)
        self._tlcolor.grid(row = 6, column = 1, sticky = tkinter.W, padx = 10)
        
        self._dtext = tkinter.Label(master = self._base, text = "Player with the most/least pieces wins the game? ", background = BG).grid(row = 7, columnspan =2)
        self._etext = tkinter.Label(master = self._base, text = "Enter 'most' or 'least':", background = BG).grid(row = 8, column = 0)
        
        self._win = tkinter.Entry(master = self._base)
        self._win.grid(row = 8, column = 1)
        
        self._start = tkinter.Button(master = self._base, text = 'START', command = self.startgame).grid(row = 9, columnspan =2, sticky = tkinter.S, pady = 20)                          
    
    def start(self):
        self._root_window.mainloop()
        
        
    def startgame(self):
        global ROW, COLUMN, FIRST, TL
        result = check_options(self._rows.get(), self._columns.get(), self._fcolor.get(), self._tlcolor.get(), self._win.get())
        
        if result[0]:
            self._root_window.quit()
            ROW = result[1][0]
            COLUMN = result[1][1]
            FIRST = result[1][2]
            TL = result[1][3]
        else:
            msg = ''
            for e in result[1]:
                msg = str(e) + "\n"
            MSG = MsgBox.MsgBox("Error", msg).showDialog()
                