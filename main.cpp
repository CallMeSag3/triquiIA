#include <iostream>
#include <vector>

// Funcion de imprimir el tablero de Triqui
void printBoard(const std::vector<std::vector<char>> &board)
{
    for (const auto &row : board)
    {
        for (const auto &cell : row)
        {
            std::cout << cell << " | ";
        }
        std::cout << std::endl;
    }
}

// Funcion para verificar si un jugador gano
bool checkWin(const std::vector<std::vector<char>> &board, char mark)
{
    // Revisar filas
    for (const auto &row : board)
    {
        if (row[0] == mark && row[1] == mark && row[2] == mark)
        {
            return true;
        }
    }

    // Revisar columnas
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark)
        {
            return true;
        }
    }

    // Revisar diagonales
    if (board[0][0] == mark && board[1][1] == mark && board[2][2] == mark)
    {
        return true;
    }

    if (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark)
    {
        return true;
    }

    return false;
}

// Funcion para revisar si el tablero esta lleno :)))
bool isBoardFull(const std::vector<std::vector<char>> &board)
{
    for (const auto &row : board)
    {
        for (const auto &cell : row)
        {
            if (cell == ' ')
            {
                return false;
            }
        }
    }
    return true;
}

// Funcion para verificar si el valor ingresado es un numero
void checkInput()
{
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Valor invalido. Por favor ingrese un valor para la fila y columna" << std::endl;
        throw std::invalid_argument("Se recibio un no entero!");
    }
}

// Funcion para verificar el turno del jugador y poner o mover una ficha 🐸
void playerTurn(std::vector<std::vector<char>> &board, char mark)
{
    int row, col;
    std::string action;

    std::cout << "Ingrese 'poner' para poner una ficha o 'mover' para mover alguna existente: ";
    std::cin >> action;

    // Poner una nueva ficha
    if (action == "poner")
    {
        std::cout << "Ingrese la fila y columna para poner la ficha (0-2): ";
        std::cin >> row >> col;

        checkInput();

        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ')
        {
            board[row][col] = mark;
        }
        else
        {
            std::cout << "La posicion no existe o esta ocupada. Intente nuevamente." << std::endl;
            playerTurn(board, mark);
        }
    }
    // Mover una ficha existente
    else if (action == "mover")
    {
        std::cout << "Ingrese la fila y columna de la ficha a mover (0-2): ";
        std::cin >> row >> col;

        checkInput();

        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == mark)
        {
            std::cout << "Ingrese la fila y columna para mover la ficha (0-2): ";
            int newRow, newCol;
            std::cin >> newRow >> newCol;

            checkInput();

            if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3 && board[newRow][newCol] == ' ')
            {
                // Solo posiciones vecinas
                if ((newRow == row + 1 && newCol == col) || (newRow == row - 1 && newCol == col) ||
                    (newRow == row && newCol == col + 1) || (newRow == row && newCol == col - 1))
                {
                    board[row][col] = ' ';
                    board[newRow][newCol] = mark;
                }
                else
                {
                    std::cout << "Se puede mover solamente a una casilla adyacente. Intente nuevamente." << std::endl;
                    playerTurn(board, mark);
                }
            }
            else
            {
                std::cout << "La posicion no existe o esta ocupada. Intente nuevamente." << std::endl;
                playerTurn(board, mark);
            }
        }
        else
        {
            std::cout << "No se encontro la ficha o la posicion no existe. Intente nuevamente." << std::endl;
            playerTurn(board, mark);
        }
    }
    else
    {
        std::cout << "Comando invalido. Intente nuevamente." << std::endl;
        playerTurn(board, mark);
    }
}

// Funcion para jugar el juego de Triqui
void playGame()
{
    std::vector<std::vector<char>> board(3, std::vector<char>(3, ' '));
    char currentPlayer = 'X';

    std::cout << "Bienvenido al juego de Triqui!" << std::endl;
    std::cout << "El formato de escribir la posicion es la siguiente: x y" << std::endl;
    std::cout << "Donde X es la fila y Y la columna de la posicion\n"
              << std::endl;

    while (true)
    {
        printBoard(board);
        std::cout << "\nTurno de jugador " << currentPlayer << "." << std::endl;

        playerTurn(board, currentPlayer);

        if (checkWin(board, currentPlayer))
        {
            printBoard(board);
            std::cout << "Jugador " << currentPlayer << " gana!" << std::endl;
            break;
        }

        if (isBoardFull(board))
        {
            printBoard(board);
            std::cout << "Empate!" << std::endl;
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

int main()
{
    playGame();
    return 0;
}
