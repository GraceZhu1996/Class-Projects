#Toluwanimi Salako 30417945 and Lindsay Pforsich 78897475
import protocol
import console_ui
console = console_ui

LOGIN_MESSAGE = "I32CFSP_HELLO "

def Instructions(name: str):
    '''Prints Instructions'''
    key = '{} {} {}'
    print(key.format('|||', '-'*36, '|||'))
    print(key.format('   '*4, 'INSTRUCTIONS', '   '))
    print('Your game board is displayed below.')
    
    print('Enter a number to drop a piece.')
    print(key.format('---', '-'*36, '---'))
    print('Enter 0 before a number to pop a piece.')
    print('Examples:\n6 drops a piece in column 6')
    print('06 pops the last piece in column 6')
    print(key.format('|||', '-'*36,
                     '|||'))
    print("\nIt is your turn", name)

    
def login():
    host = ''
    port = ''
    name = ''
    passed = False

    while not passed:
        host = input("Enter a host (eg. an IP address or a hostname): ")
        port = input("Enter a port number: ")
        passed = protocol.try_connection(host, port)
        if not passed:
            print("Connection Failed, Try again.")
    
    passed = False
    while not passed:
        name = input("Enter a username (No spaces!): ")
        if ' ' in name:
            print('No spaces please :(.')
        else:
            user = name
            passed = True
    print("\nConnection Successful.\n")
    protocol.create_connection(host, int(port), name, LOGIN_MESSAGE)
    print(protocol.readline())
    

def new_game():
    protocol.writeline("AI_GAME")
    _game = (protocol.readline() == 'READY\n')
    while _game:
        console.show_board()
        #START PLAYING
        x = console.player_move(True) #Make move
        print(x)
        if not x == None:
            y = x[1] + 1
            protocol.writeline(x[0] + str(y)) #Makes the Drop or POP move on the server side
        
            if not protocol.readline() == 'INVALID\n':
                
                server_move = protocol.readline()
                print(server_move)
                protocol.readline()
                if server_move[0:3] == 'DRO':
                    console.drop(int(server_move[5]) - 1)
                elif server_move[0:3] == 'POP':
                    console.pop(int(server_move[4]) - 1)
            else:
                print("This should never be printed!")

        winner = console.check_for_winner()
        if not winner == ' ':
            console.show_board()
            print("Winner is", winner, '!')
            _game = False
        

def start():
    login()
    new_game()


if __name__ == '__main__':
    start()
