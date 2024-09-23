
#include "Game.h"
#include <iostream>
#include <conio.h> 
#include <windows.h>
#include <thread>

Game::Game() {
    levels = { "level1.txt", "level2.txt", "level3.txt", "level4.txt", "level5.txt" };
    currentLevelIndex = 0;

    this->player = nullptr;
    this->playerName = "indef";
    isPlaying = true;
}

Game::Game(int currentLevel, std::string movement) {
    levels = { "level1.txt", "level2.txt", "level3.txt", "level4.txt", "level5.txt" };
    currentLevelIndex = currentLevel;
    for (char c : movement) {
        if (c == ';') {
            break;
        }
        if (c != '-') {
            replayMoves.push_back(c);
        }
    }
    isPlaying = true;
}

void Game::createBoard(std::string pLevel) {
    board.clearList();
    Level level;

    if (!level.loadLevelFromFile(pLevel)) {
        std::cout << "Error leyendo el nivel desde " << pLevel << std::endl;
        return;
    }

    currentLevel = level; // Almacena el nivel cargado


    board.setSize(level.getRows());
    this->board.createList();
    this->board.insertData(currentLevel.getGrid(), currentLevel.getRows(), currentLevel.getCols()); // Usa cols también

    setPlayer(); // Llama a setPlayer después de configurar la lista
}

void Game::setPlayer() {
    Node* row = this->board.getHead();
    while (row != nullptr) {
        Node* currentNode = row;
        while (currentNode != nullptr) {
            if (currentNode->getSymbol() == '@') {
                this->player = currentNode;
                return;
            }
            currentNode = currentNode->getNodeRight();
        }
        row = row->getNodeDown();
    }
    std::cout << "Error: Jugador no encontrado en el tablero." << std::endl;
}

void Game::printBoard() {
    std::cout << currentLevel.getLevelName() << '\n' << std::endl;
    Node* row = this->board.getHead();
    while (row != nullptr) {
        Node* currentNode = row;
        while (currentNode != nullptr) {
            char symbol = currentNode->getSymbol();
//

            // Establecer colores según el símbolo
            switch (symbol) {
            case '!':
                setColor(1, 0); // Naranja
                break;
            case '#':
                setColor(12, 0); // Rojo
                break;
            case '@':
                setColor(13, 0); // Rosa
                break;
            case '$':
                setColor(10, 0); // Verde oscuro
                break;
            case '.':
                setColor(1, 0);  
                break;
            default:
                setColor(7, 0);  // Color por defecto (blanco sobre negro)
                break;
            }

            std::cout << symbol;
            currentNode = currentNode->getNodeRight();
        }
        std::cout << std::endl;
        row = row->getNodeDown();
    }

    setColor(7, 0); // Restablecer a blanco sobre 
}

void Game::movePlayer() {
    int keyPressed = _getch();

    switch (keyPressed)
    {
    case 27:
        pauseMenu();
        break;
    case 72:  // Flecha ARRIBA
        mapMovements('W');
        replayMoves.push_back('W');
        break;
    case 80:  // Flecha ABAJO
        mapMovements('S');
        replayMoves.push_back('S');
        break;
    case 75:  // Flecha IZQUIERDA
        mapMovements('A');
        replayMoves.push_back('A');
        break;
    case 77:  // Flecha DERECHA
        mapMovements('D');
        replayMoves.push_back('D');
        break;
    case 'W': case 'w':
        mapMovements('W');
        replayMoves.push_back('W');
        break;
    case 'A': case 'a':
        mapMovements('A');
        replayMoves.push_back('A');
        break;
    case 'S': case 's':
        mapMovements('S');
        replayMoves.push_back('S');
        break;
    case 'D': case 'd':
        mapMovements('D');
        replayMoves.push_back('D');
        break;
    default:
        //no toco una tecla de los casos
        break;
    }
}

bool Game::allBoxesAtDestinations() {
    Node* row = this->board.getHead();
    while (row != nullptr) {
        Node* currentNode = row;
        while (currentNode != nullptr) {
            if (currentNode->getSymbol() == '$') {
                return false;  // Al menos una caja no está en un destino
            }
            currentNode = currentNode->getNodeRight();
        }
        row = row->getNodeDown();
    }
    return true;  // Todas las cajas están en destinos
}

void Game::pauseMenu() {
    char choice;
    std::cout << "Deseas continuar el juego?\n c: continuar\n r: reiniciar\n m: volver al menu\n n: salir\n ";
    std::cin >> choice;

    if (choice == 'c' || choice == 'C') {
        return;
    }
    else if (choice == 'r' || choice == 'R') {
        replayMoves.clear();
        resetGame(); // Reiniciar el nivel actual
    }
    else if (choice == 'm' || choice == 'M') {
        currentLevel.saveGame(replayMoves, currentLevelIndex);
        isPlaying = false;
    }
    else {
        currentLevel.saveGame(replayMoves, currentLevelIndex);
        std::cout << "Saliendo del juego." << std::endl;
        exit(0);
    }
}

void Game::resetGame() {
    createBoard(levels[currentLevelIndex]); // Recargar el nivel actual
    setPlayer(); // Volver a configurar el jugador
}

void Game::showReplay() {
    std::system("cls");
    printBoard();
    

    for (const auto& move : replayMoves) {
        std::this_thread::sleep_for(std::chrono::milliseconds(350)); // Espera 0.5
        std::system("cls");
        mapMovements(move);
        printBoard();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(700)); // Espera 1 segundos
}

void Game::playGame() {
    while (isPlaying) {
        system("cls");
        printBoard();
        std::cout << "Esc para desplegar el menu de pausa o presione una tecla de direccion para moverse.\nTecla: ";

        if (allBoxesAtDestinations()) {
            std::cout << "\n¡Has ganado!\n" << std::endl;
            char choice;
            std::cout << "Desea ver la repeticion?\n s:Si \n n:No\n";
            std::cin >> choice;

            if (choice == 's' || choice == 'S') {
                resetGame();
                showReplay();
            }

            std::cout << "Deseas continuar al siguiente nivel?\n s: siguiente nivel\n m: volver al menu\n ";
            std::cin >> choice;

            if (choice == 's' || choice == 'S') {
                // Avanza al siguiente nivel si existe
                if (currentLevelIndex + 1 < levels.size()) {
                    currentLevelIndex++;
                    replayMoves.clear();
                    createBoard(levels[currentLevelIndex]);  // Carga el siguiente nivel
                }
                else {
                    replayMoves.clear();
                    currentLevelIndex = 0;
                    currentLevel.saveGame(replayMoves, currentLevelIndex);
                    std::cout << "¡Has completado todos los niveles!" << std::endl;
                    system("pause");
                    break;
                }
            }
            else if (choice == 'm' || choice == 'M') {
                if (currentLevelIndex + 1 < levels.size()) {
                    currentLevelIndex++;
                    replayMoves.clear();
                    currentLevel.saveGame(replayMoves, currentLevelIndex);
                }
                else {
                    replayMoves.clear();
                    currentLevelIndex = 0;
                    currentLevel.saveGame(replayMoves, currentLevelIndex);
                }
                isPlaying = false;
                break;
            }
        }
        else {
            movePlayer();
        }

        
    }
}

void Game::run() {

    createBoard(levels[currentLevelIndex]); // Inicializar el juego creando el primer nivel

    playGame();
}

void Game::setColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

void Game::mapMovements(char move)
{
    Node* square = nullptr;
    

    switch (move) {
    case 'W':
        square = player->getNodeUp();
        break;
    case 'D':
        square = player->getNodeRight();
        break;
    case 'S':
        square = player->getNodeDown();
        break;
    case 'A':
        square = player->getNodeLeft();
        break;
    default:
        return;
    }
    char squareSymbol = square->getSymbol();

    if ( squareSymbol != '#') {     //es el caso mas irrelevante, no se hace nada

        if (squareSymbol == ' ') {
            if (player->isBase()) {
                player->setSymbol('.');
            }
            else {
                player->setSymbol(' ');
            }
            square->setSymbol('@');
            player = square;
            return;
        }

        if (squareSymbol == '.') {
            player->setSymbol(' ');
            square->setSymbol('@');
            player = square;
            return;
        }
        //ya evaluamos los casos mas simples

        Node* nextSquare = nullptr;

        switch (move) {
        case 'W':
            nextSquare = square->getNodeUp();
            break;
        case 'D':
            nextSquare = square->getNodeRight();
            break;
        case 'S':
            nextSquare = square->getNodeDown();
            break;
        case 'A':
            nextSquare = square->getNodeLeft();
            break;
        default:
            return;
        }
        char nextSquareSymbol = nextSquare->getSymbol();

        if (nextSquareSymbol == ' ') {//podemos mover caja
            if (squareSymbol == '$') {
                player->setSymbol(' ');
                square->setSymbol('@');
                nextSquare->setSymbol('$');
                player = square;
                return;
            }
            if (squareSymbol == '!') {
                nextSquare->setSymbol('$');
                square->setSymbol('@');
                player->setSymbol(' ');
                player = square;
                return;
            }
        }

        if (nextSquareSymbol == '.') { //mover una caja a una base
            player->setSymbol(' ');
            square->setSymbol('@');
            nextSquare->setSymbol('!');
            player = square;
            return;
        }
    }
    return;
}

void Game::reloadGame()
{
    createBoard(levels[currentLevelIndex]); // Inicializar el juego con el nivel cargado
    for (const auto& move : replayMoves) {
        mapMovements(move);
    }
    playGame();
}
