#Toluwanimi Salako 30417945

from tkinter import *
import game_logic
import new_game_gui
import MsgBox
from collections import namedtuple

tile = namedtuple('tile', 'x y xx yy id')

MOST_WINS = False

STICKY_ALL = N + S + W + E
DARK = "#56568E"
LIGHT = "#C4C4E0"

ROW = 0
COL = 0

game_state = []
game__gui = None


class Game_Window:
    def __init__(self):
        global game_state
        table = game_state.table
        
        self.main = Tk()
        self.main.title("RIVERSI")
        self.main.resizable(width = True, height = True)
        
        global ROW, COL
        ROW =  len(table)
        COL = len(table[0])
        
        self.base = Frame(master = self.main)
        self.base.grid(row = 1, pady = 5, padx = 5, sticky = STICKY_ALL)
        

        
        self.master = Canvas(master = self.main, background = "#FFFFFF", width = 300, height = 300)
        self.master.grid(row = 0,sticky = STICKY_ALL)
        
        self.h = 300/ROW
        self.w = 300/COL
        
        self.main.rowconfigure(0, weight = 1)
        self.main.columnconfigure(0, weight = 1)

       
        self.tiles = []
        self._draw_board(self.h, self.w)
        
        self.update_score()
        
        self.main.update()
        self.main.minsize(self.main.winfo_width().__int__(), self.main.winfo_height().__int__())
        self.main.bind('<Configure>', self.refresh)
        self.main.bind('<Button-1>', self.onClick)
 
    def start(self):
        self.main.mainloop()
        return
    
    def onClick(self, event: Event):
        ID = self.master.find_closest(self.master.canvasx((event.x)), self.master.canvasy(event.y))
        for row in range(len(self.tiles)):
            for col in range(len(self.tiles[row])):
                if self.tiles[row][col].id == ID[0]:
                    run_game(row-1, col-1)
                    return
    def refresh(self, event):
        self.master.delete(ALL)
        
        self.w = self.master.winfo_width()/COL
        self.h = self.master.winfo_height()/ROW
        
        self._draw_board(self.h, self.w)
    
    def update_score(self):
        global game_state
        game = game_state
        score = "BLACK: {}\t WHITE: {}\n TURN: {}"
        Label(master = self.base, text = score.format(str(game._pieces_num[0]), str(game._pieces_num[1]), game.turn)).grid(row = 0, columnspan = 2, sticky = STICKY_ALL)

    def print_game(self):
        global game_state
        game = game_state
        table = game.table

        for r in range(len(table)):
            for c in range(len(table[r])):
                x = self.tiles[r+1][c+1].x
                y = self.tiles[r+1][c+1].y
                xx = self.tiles[r+1][c+1].xx
                yy = self.tiles[r+1][c+1].yy
                
                if table[r][c] == 'black':
                    self.master.create_oval(x, y, xx, yy, fill = "#000000", outline = "")
                elif table[r][c] == 'white':
                     self.master.create_oval(x, y, xx, yy, fill = "#FFFFFF", outline = "")
        
        
    def _draw_board(self, h, w):
        count = 0
        color = None
        self.tiles = []
        for r in range(ROW+1):
            temp = []
            for c in range(COL+1):
                if count%2 == 0:
                    color = DARK
                else:
                    color = LIGHT
                x = self.master.create_rectangle((c-1)*w, (r-1)*h, w*c, h*r, fill = color)
                count += 1
                X = tile((c-1)*w, (r-1)*h, w*c, h*r, x)
                temp.append(X)
            self.tiles.append(temp)
        self.print_game()

    
def newgame():
    global MOST_WINS

    newgame = new_game_gui
    start = newgame.StartUpWindow()
    start.start()
    X = newgame.ROW
    Y = newgame.COLUMN
    P1 = newgame.FIRST
    TL = newgame.TL
    start._root_window.quit()
    start._root_window.destroy()
    '''Sets up a new game'''
    game = game_logic.game_state(X, Y)
    if TL == 'black':
        other = 'white'
    else:
        other = 'black'
    game.new_game(P1, TL, other)
    
    return game
    

def winner(p_count):
    '''Handles Winning Situations'''
    global MOST_WINS
    p1 = p_count[0]
    p2 = p_count[1]
    if p2 == p1:
        win = "It's a draw!"
    elif MOST_WINS:
        if p1 > p2:
            win = "Congratulations B, you are the winner."
        elif p2 > p1:
            win = "Congratulations A, you are the winner."
    else:
        if p2 > p1:
            win = "Congratulations A, you are the winner."
        elif p1 > p2:
            win = "Congratulations B, you are the winner."
    MSG = MsgBox.MsgBox("Winner Found!", win).showDialog()
        

        
    
def run_game(r, c):
    #Check if the user move is a valid move
    global game_state
    global game_gui
    Error = game_state.make_move(c, r)
    game_gui.print_game()
    game_gui.update_score()
    if not Error == None:
        if Error == 'Game Over':
            winner(game_state._pieces_num)
            return
          
if __name__ == '__main__':
    global game_state
    global game_gui
    game_state = newgame()
    game_gui = Game_Window()
    game_gui.start()