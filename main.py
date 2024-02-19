board = [[' ' for _ in range(3)] for _ in range(3)]

def display_board():
    for row in board:
        print('|'.join(row))
        print('-' * 5)

def check_winner(player):
    for row in board:
        if all(cell == player for cell in row):
            return True

    for col in range(3):
        if all(board[row][col] == player for row in range(3)):
            return True

    if all(board[i][i] == player for i in range(3)):
        return True
    if all(board[i][2-i] == player for i in range(3)):
        return True

    return False

def make_move(player, row, col):
    if board[row][col] == ' ':
        board[row][col] = player
        return True
    else:
        return False

def play_game():
    current_player = 'X'
    while True:
        display_board()
        # option = input('Ingrese 1 para insertar nueva ficha o 2 para mover una pieza: ')
        # if option == '1':
            # play_insert(current_player)
        # elif option == '2':
        #     play_move(current_player)
        # else:
        #     print('Opcion invalida. Intente nuevamente.')
            # continue
        row = int(input('Ingrese el numero de la fila (0-2): '))
        col = int(input('Ingrese el numero de la columna (0-2): '))
        if make_move(current_player, row, col):
            if check_winner(current_player):
                display_board()
                print(f'Jugador {current_player} gano!')
                break
            elif all(board[row][col] != ' ' for row in range(3) for col in range(3)):
                display_board()
                print('Empate!')
                break
            else:
                current_player = 'O' if current_player == 'X' else 'X'
        else:
            print('Accion invalida. Intente nuevamente.')

# def move_piece(player, row, col, new_row, new_col):
#     if board[row][col] == player and board[new_row][new_col] == ' ':
#         board[row][col] = ' '
#         board[new_row][new_col] = player
#         return True
#     else:
#         return False

play_game()

