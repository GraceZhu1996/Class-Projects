#Toluwanimi Salako 30417945
import game_logic
import new_game_gui
import main
MOST_WINS = False

    
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
    
def print_game(game):
    pass

def winner(p_count):
    '''Handles Winning Situations'''
    global MOST_WINS
    p1 = p_count[0]
    p2 = p_count[1]
    if p2 == p1:
        print("It's a draw!")
    elif MOST_WINS:
        if p1 > p2:
            print("Congratulations B, you are the winner.")
        elif p2 > p1:
             print("Congratulations A, you are the winner.")
    else:
        if p2 > p1:
            print("Congratulations A, you are the winner.")
        elif p1 > p2:
             print("Congratulations B, you are the winner.")
    
            
def _highlight_moves(game_state, moves):
    '''Highlights possible moves on the board with an x.'''
    for x in moves:
        row,col = x.available_locations.split("/")
        game_state.table[int(row)][int(col)] = "X"
    print_game(game_state)
        
                
        
        

    
#if the current player was to move here, what pieces would be flipped in this direction?
#First it has to be an opposite color, then it has to be one of yours.
def player_move(game_state, cols, rows)->'Game Move':
    global ALPHABET
    invalid = True
    while invalid:
        try:
            x = input(game_state.turn + "---->").upper().strip()
            if x == "":
                raise Exception("Your input can't be empty.")
            elif len(x) == 1:
                raise Exception("Enter a Column and a Row.")
            if not x[0].upper() in ALPHABET[1:cols+1]:
                raise Exception("Please enter a valid column letter.")
            if not int(x[1:]) <= rows:
                raise Exception("Please enter a valid row number.")
            if int(x[1:]) == 0:
                raise Exception("Please enter a valid row number.")
        except Exception as H:
            print(H)
        else:
            invalid = False
            
    return x
        
    
def run_game(game_state):
    game = game_state.table
    gui = main.Game_Window(game)
    gui.start()
    gui.print_game(game_state)
    winner_found = False
    while not winner_found:
        _move = player_move(game_state, len(game[0]), len(game))
        user_col = int(ALPHABET.index(_move[0])) - 1
        user_row = int(_move[1:]) - 1
        #Check if the user move is a valid move
        Error = game_state.make_move(int(user_col), int(user_row))
        gui.print_game(game_state)
        if not Error == None:
            print(Error)
            if Error == 'Game Over':
                winner(game_state._pieces_num)
                return
            
if __name__ == '__main__':
    game_state = newgame()
    run_game(game_state)
