#Toluwanimi Salako 30417945 and Lindsay Pforsich 78897475
import console_ui
console = console_ui


def instructions():
    '''Prints Game Instructions'''
    key = '{} {} {}'
    print(key.format('|||', '-'*36, '|||'))
    print(key.format('   ', 'INSTRUCTIONS', '   '))
    print('Your game board is displayed below.')
    
    print('Enter a number to drop a piece.')
    print(key.format('---', '-'*36, '---'))
    print('Enter 0 before a number to pop a piece.')
    print('Examples:\n6 drops a piece in column 6')
    print('06 pops the last piece in column 6')
    print(key.format('|||', '-'*36, '|||'))
    print("\nIt is R's turn.")

    
def start():
    console.show_board()
    
    running = True
    while running:
        winner = console.check_for_winner()
        if winner == ' ':
            print('\nIt is', console.game_state.turn +"'s turn.")
            console.player_move(False)
        else:
            print('Congratulations!!!!', winner, 'You are the winner!!')
            running = False
if __name__=='__main__':
    instructions()
    start()
