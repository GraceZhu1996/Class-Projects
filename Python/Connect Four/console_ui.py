#Toluwanimi Salako 30417945 and Lindsay Pforsich 78897475
import connectfour

game_state = connectfour.new_game_state()

def show_board():
    '''Shows/Updates the game board'''
    global game_state
    board = game_state.board
    Rows = connectfour.BOARD_ROWS
    print("\n\n")
    for i in range(len (board)):
        print(i+1, " ", end = '')
    print("\n")
    for c in range(Rows):
        for b in board:
            if b[c] == ' ':
                print('.', end = '  ')
            else:
                print(b[c], end = '  ')
        print("\n")
        
def can_you_pop(x: 'move')->bool:
    '''Checks if the current player is making a valid move'''
    global game_state
    board = game_state.board
    if board[x][-1] == game_state.turn:
        return True
    elif board[x][-1] == ' ':
        print("There is no piece in that slot.")
    else:
        print("You can't pop your opponent's piece.")
               
def is_it_full(x: 'move')->bool:
    '''Checks if one column in the game board is full'''
    global game_state
    board = game_state.board
    if board[x][0] == ' ':
        return True
    else:
        print('That column is full bro.')

def check_for_winner():
    '''Returns a winner or None if no winner'''
    global game_state
    return connectfour.winning_player(game_state)

def player_move(net: bool):
    '''Handles dropping pieces and popping pieces'''
    cols = connectfour.BOARD_COLUMNS
    
    is_num = True
    while is_num:
        #Handles inputs that might raise errors.
        y = input('Enter a Column number: ')
        x = 0
        try:
            x = int(y)
        except:
            print('Please! Enter a number!:')
        finally:
            if x <= cols and x != 0:
                x = x-1
                is_num = False
                #Differentiates between drops or pops
                if y[0] == '0':
                    if can_you_pop(x):
                        #POPS
                        pop(x)
                        if net: #If it is a network game
                            return ['POP ', x]
                else:
                    if is_it_full(x):
                        #DROPS
                        drop(x)
                        if net:
                            return ['DROP ', x]
            else:
               print('Enter a number between 1 and', cols)

def drop(x: int):
    global game_state
    game_state = connectfour.drop_piece(game_state, x)
    show_board()
    
def pop(x: int):
    global game_state
    game_state = connectfour.pop_piece(game_state, x)
    show_board()
