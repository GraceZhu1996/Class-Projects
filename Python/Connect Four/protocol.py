#Toluwanimi Salako 30417945 and Lindsay Pforsich 78897475
import socket
from collections import namedtuple

GameConnection = namedtuple('GameConnection', ['socket', 'username', 'input', 'output'])
connection = None
def create_connection(host: str, port: int, username: str, log_msg: str)-> GameConnection:
    new_socket = socket.socket()
    new_socket.connect((host, port))

    game_input = new_socket.makefile('r')
    game_output = new_socket.makefile('w')
    
    global connection
    connection = GameConnection(new_socket, username, game_input, game_output)
    _login(log_msg)

def try_connection(host, port)->bool:
    game_socket = socket.socket()
    '''Returns true or false if connection was successful'''
    try:
        game_socket.connect((host, int(port)))
        return True
    except:
        return False
    finally:
        game_socket.close()


def _login(logmessage: str):
    global connection
    writeline(logmessage + connection.username)

def writeline(line: str):
    global connection
    connection.output.write(line + '\r\n')
    connection.output.flush()
    
def readline()->str:
    global connection
    return connection.input.readline()
