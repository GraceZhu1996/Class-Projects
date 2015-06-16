#Toluwanimi Salako 30417945

from collections import namedtuple
can_move = namedtuple('can_move', 'piece available_locations method')

class EndLoop(Exception):
    pass

def _new_table(c_rows) -> 'Game Table' :
    '''Creates a new table object'''
    result = []
    for c in range(c_rows[0]):
        temp = []
        for r in range(c_rows[1]):
            temp.append('-')
        result.append(temp)
    
    return result

class game_state:
    COLUMNS_ROWS = 0,0 #No of columns, #No of Rows.
    turn = '' #TURNS CAN BE (B)lack or (W)hite.
    _pieces_num = 0,0 #No of black pieces, No of white pieces
    table = None
    _no_legals = 0


    def new_game(self, player1, top_left, other)->'game_state':
        table = _new_table(self.COLUMNS_ROWS)

        #Locate and Set mid points
        c_mid = int(self.COLUMNS_ROWS[0]/2)
        r_mid = int(self.COLUMNS_ROWS[1]/2)
        
        table[c_mid][r_mid] = top_left
        table[c_mid][r_mid-1] = other
        table[c_mid-1][r_mid] = other
        table[c_mid-1][r_mid-1] = top_left

        self.table = table
        self.turn = player1
        self._update_count()

    def make_move(self, col, row):
        message = ''
        legals = self._legal_moves()
        
        if 'No_Moves' in legals:
            return'Game Over'
        if len(legals) == 0: #No legal moves
            self._no_legals += 1
            if self._no_legals == 2:
                #If no both users have no moves
                return 'Game Over'
            else:
                self._switch_turns()
        else:
            self._no_legals = 0
            for move in legals:
                if move.available_locations == (row, col):
                    if move.method == 'left':
                        self._move_left(move.piece, (row, col))
                        self._switch_turns()
                        return message
                    elif move.method == 'right':
                        self._move_right(move.piece, (row, col))
                        self._switch_turns()
                        return message
                    elif move.method == 'up':
                        self._move_up(move.piece, (row, col))
                        self._switch_turns()
                        return message
                    elif move.method == 'down':
                        self._move_down(move.piece, (row, col))
                        self._switch_turns()
                        return message
                    elif move.method == 'leftup':
                        self._move_leftup(move.piece, (row, col))
                        self._switch_turns()
                        return message
                    elif move.method == 'rightup':
                        self._move_rightup(move.piece, (row, col))
                        self._switch_turns()
                        return message
                    elif move.method == 'leftdown':
                        self._move_leftdown(move.piece, (row, col))
                        self._switch_turns()
                        return message
                    elif move.method == 'rightdown':
                        self._move_rightdown(move.piece, (row, col))
                        self._switch_turns()
                        return message
    
    def _move_up(self, piece, destination):
        row, col = piece
        try:
            for r in range(len(self.table[:row]) - 1, -1, -1):
                if self.table[r][col] == '-':  # If an empty space is found
                    if (r, col) == (destination[0], destination[1]):
                        #If the empty space is the destination
                        self.table[r][col] = self.turn
                        raise EndLoop(None)
                    else:
                        raise EndLoop(None)
                else:
                    self.table[r][col] = self.turn
        except:
            pass
    
    def _move_down(self, piece, destination):
        row, col = piece
        try:
            for r in range(len(self.table[row:]) - 1, len(self.table)):
                if self.table[r][col] == '-':  # If an empty space is found
                    if (r,col) == (destination[0], destination[1]):
                        #If the empty space is the destination
                        self.table[r][col] = self.turn
                        raise EndLoop(None)
                    else:
                        raise EndLoop(None)
                else:
                    self.table[r][col] = self.turn
        except:
            pass
    
    def _move_left(self, piece, destination):
        #[row][column]
        row, col = piece
        try:
            for l in range(len(self.table[row][:col]) - 1, -1, -1):
                if self.table[row][l] == '-':  # If an empty space is found
                    if (row, l) == (destination[0], destination[1]):
                        #If the empty space is the destination
                        self.table[row][l] = self.turn
                        raise EndLoop(None)
                    else:
                        raise EndLoop(None)
                else:
                    self.table[row][l] = self.turn
        except:
            pass
        
    def _move_right(self, piece, destination):
        row, col = piece
        try:
            for c in range(len(self.table[row][col:]) -1, len(self.table[row])):
                if self.table[row][c] == '-':  # If an empty space is found
                    if (row, c) == (destination[0], destination[1]):
                        #If the empty space is the destination
                        self.table[row][c] = self.turn
                        raise EndLoop(None)
                    else:
                        raise EndLoop(None)
                else:
                    self.table[row][c] = self.turn
        except:
            pass
    def _move_leftup(self, piece, destination):
        row, col = piece
        co = col - 1
        try:
            for r in range(len(self.table[:row]) - 1, -1, -1):
                if self.table[r][co] == '-':  # If an empty space is found
                    if (r, co) == (destination[0], destination[1]):
                        #If the empty space is the destination
                        self.table[r][co] = self.turn
                        raise EndLoop(None)
                    else:
                        raise EndLoop(None)
                else:
                    self.table[r][co] = self.turn
                    co -= 1     
        except:
            co -= 1
            pass
    def _move_rightup(self, piece, destination):
        row, col = piece
        co = col + 1
        try:
            for r in range(len(self.table[:row]) - 1, -1, -1):
                if self.table[r][co] == '-':  # If an empty space is found
                    if (r, co) == (destination[0], destination[1]):
                        #If the empty space is the destination
                        self.table[r][co] = self.turn
                        raise EndLoop(None)
                    else:
                        raise EndLoop(None)
                else:
                    self.table[r][co] = self.turn  
                    co += 1     
        except:
            co += 1
            pass
        
    def _move_leftdown(self, piece, destination):
        row, col = piece
        co = col
        try:
            for r in range(len(self.table[row:]) -1, len(self.table)):
                if self.table[r][co] == '-':  # If an empty space is found
                    if (r, co) == (destination[0], destination[1]):
                        # If the empty space is the destination
                        self.table[r][co] = self.turn
                        raise EndLoop(None)
                    else:
                        raise EndLoop(None)
                else:
                    self.table[r][co] = self.turn
                    co -= 1     
        except:
            co -= 1
            pass
    def _move_rightdown(self, piece, destination):
        row, col = piece
        co = col
        try:   
            for r in range(len(self.table[row:]) -1, len(self.table)): 
                if self.table[r][co] == '-':  # If an empty space is found
                    if (r, co) == (destination[0], destination[1]):
                        #If the empty space is the destination
                        self.table[r][co] = self.turn
                        raise EndLoop(None)
                    else:
                        raise EndLoop(None)
                else:
                    self.table[r][co] = self.turn     
                    co += 1  
        except:
            co += 1
            pass

        
        
    def _legal_moves(self) -> [can_move]:
        '''Generates a list of legal moves for the turn and returns it'''
        game = self.table
        turn = self.turn
        pieces_location = []
        result = []  # List of legal moves
        # Scan the board for user's pieces
        for r in range(len(game)):
            for c in range(len(game[0])):
                if game[r][c] == turn:
                    pieces_location.append((r, c))   
                    
        if '-' in game == False:
            return ['No_Moves']
        
        # Starting from a piece,...
        for a in pieces_location:
            row, col = a[0], a[1]
            # Scan horizontally for legal moves
            try:  # Scan Left
                if game[row][col - 1] == turn or game[row][col - 1] == '-':
                    # if the user's piece is found first or if an empty piece is found first
                    raise EndLoop(None)
                else:
                    try:
                        for l in range(len(game[row][:col]) - 1, -1, -1):
                            if game[row][l] == '-':  # If an empty space is found
                                result.append(can_move(a, (row,l), "left"))
                                raise EndLoop(None) 
                    except:
                        pass
            except:
                pass
            
            try:  # Scan Right
                if game[row][col + 1] == turn or game[row][col + 1] == '-':
                    # if the user's piece is found first or if an empty piece is found first
                    raise EndLoop(None)
                else:
                    try:
                        for r in range(len(game[row][col:]) - 1, len(game[row])):
                            if game[row][r] == '-':  # If an empty space is found
                                result.append(can_move(a, (row, r), "right"))
                                raise EndLoop(None)
                    except:
                        pass
            except:
                pass
            
            try:  # Scan Upwards
                if game[row - 1][col] == turn or game[row - 1][col] == '-':
                    # if the user's piece is found first or if an empty piece is found first
                    raise EndLoop(None)
                else:
                    try:
                        for r in range(len(game[:row]) - 1, -1, -1):
                            if game[r][col] == '-':  # If an empty space is found
                                result.append(can_move(a, (r,col), "up"))
                                raise EndLoop(None)
                    except:
                        pass
            except:
                pass
            
            try:  # Scan Downwards
                if game[row + 1][col] == turn or game[row + 1][col] == '-':
                    # if the user's piece is found first or if an empty piece is found first
                    raise EndLoop(None)
                else:
                    try:
                        for r in range(len(game[row:]) - 1, len(game)):
                            if game[r][col] == '-':  # If an empty space is found
                                result.append(can_move(a, (r,col), "down"))
                                raise EndLoop(None)
                    except:
                        pass
            except:
                pass
            
            try:  # Scan Diagonal (left up)
                if game[row - 1][col - 1] == turn or game[row - 1][col - 1] == '-':
                    # if the user's piece is found first or if an empty piece is found first
                    raise EndLoop(None)
                else:
                    co = col - 1
                    try:
                        for r in range(len(game[:row]) - 1, -1, -1):
                            if game[r][co] == '-':  # If an empty space is found
                                result.append(can_move(a, (r,co), "leftup"))
                                raise EndLoop(None)
                            else:
                                co -= 1
                    except:
                        co -= 1
                        pass
            except:
                pass
            
            try:  # Scan Diagonal (right up)
                if game[row - 1][col + 1] == turn or game[row - 1][col + 1] == '-':
                    # if the user's piece is found first or if an empty piece is found first
                    raise EndLoop(None)
                else:
                    co = col + 1
                    try:
                        for r in range(len(game[:row]) - 1, -1, -1):
                            if game[r][co] == '-':  # If an empty space is found
                                result.append(can_move(a, (r,co), "rightup"))
                                raise EndLoop(None)
                            else:
                                co += 1
                    except:
                        co += 1
                        pass
            except:
                pass
            
            try:  # Scan Diagonal (Left Down)
                if game[row + 1][col - 1] == turn or game[row + 1][col - 1] == '-':
                    # if the user's piece is found first or if an empty piece is found first
                    raise EndLoop(None)
                else:
                    co = col - 1
                    try:
                        for r in range(len(game[row:]) -1, len(game)):
                            if game[r][co] == '-':  # If an empty space is found
                                result.append(can_move(a, (r,co), "leftdown"))
                                raise EndLoop(None)
                            else:
                                co -= 1
                    except:
                        co -= 1
                        pass    
            except:
                   pass
               
            try:  # Scan Diagonal (Right Down)
                if game[row + 1][col + 1] == turn or game[row + 1][col + 1] == '-':
                    # if the user's piece is found first or if an empty piece is found first
                    raise EndLoop(None)
                else:
                    co = col + 1
                    try:
                        for r in range(len(game[row:]) -1, len(game)):
                            if game[r][co] == '-':  # If an empty space is found
                                result.append(can_move(a, (r,co), "rightdown"))
                                raise EndLoop(None)
                            else:
                                co += 1
                    except:
                        co += 1
                        pass    
            except:
                   pass
        return result
            
    def _update_count(self):
        l = [0,0]
        for r in self.table:
            for c in r:
                if c == 'black':
                    l[0] += 1
                elif c == 'white':
                    l[1] += 1
        self._pieces_num = tuple(l)
    def _switch_turns(self):
        self._update_count()
        if self.turn == 'black':
            self.turn = 'white'
        else:
            self.turn = 'black'

    def __init__(self, rows, columns):
        self.COLUMNS_ROWS = columns, rows
