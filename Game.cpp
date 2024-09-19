#include "Game.h"
#include <iostream>
#include <conio.h> 

Game::Game() {
    levels = { "level1.txt", "level2.txt", "level3.txt", "level4.txt", "level5.txt" };
    currentLevelIndex = 0;

    this->player = nullptr;
    this->playerName = "indef";
    this->wasBase = false;
}
void Game::createBoard(std::string pLevel) {
    Level level;
    if (!level.loadLevelFromFile(pLevel)) {
        std::cout << "Error leyendo el nivel desde " << pLevel << std::endl;
        return;
    }

    currentLevel = level; // Almacena el nivel cargado

    int size = level.getRows();  // Obtener filas del nivel cargado
    this->board.setSize(size);    // Establecer tamaño en la lista
    this->board.createList();
    this->board.insertData(level.getGrid(), level.getRows(), level.getCols()); // Usa cols también

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

void Game::swapCharacters(Node* pPrevNode, Node* pNewPosPlayer) {
    if (pNewPosPlayer->getSymbol() == '.') {
        pPrevNode->setSymbol('!');
        pNewPosPlayer->setSymbol('!');
    }
    else {
        char aux = pPrevNode->getSymbol();
        pPrevNode->setSymbol(pNewPosPlayer->getSymbol());
        pNewPosPlayer->setSymbol(aux);
    }
}

void Game::printBoard() {
    std::cout << currentLevel.getLevelName()<<'\n' << std::endl;
    Node* row = this->board.getHead();
    while (row != nullptr) {
        Node* currentNode = row;
        while (currentNode != nullptr) {
            std::cout << currentNode->getSymbol();
            currentNode = currentNode->getNodeRight();
        }
        std::cout << std::endl;
        row = row->getNodeDown();
    }
}

void Game::moveBox(char direction, Node* boxNode) {
    Node* nextPosBox = nullptr;

    switch (direction) {
    case 'W':
    case 'w':
        nextPosBox = boxNode->getNodeUp();
        break;
    case 'D':
    case 'd':
        nextPosBox = boxNode->getNodeRight();
        break;
    case 'S':
    case 's':
        nextPosBox = boxNode->getNodeDown();
        break;
    case 'A':
    case 'a':
        nextPosBox = boxNode->getNodeLeft();
        break;
    default:
        return;
    }

    if (nextPosBox != nullptr && isValidPos(nextPosBox)) {
        char nextSymbol = nextPosBox->getSymbol();

        if (nextSymbol == '.') {
            nextPosBox->setSymbol('!');
        }
        else if (nextSymbol == ' ') {
            nextPosBox->setSymbol('$');
        }

        // Restaurar posición anterior de la caja
        if (boxNode->getSymbol() == '$') {
            boxNode->setSymbol(' ');
        }
        else if (boxNode->getSymbol() == '.') {
            boxNode->setSymbol('.');
        }
    }
    else {
        std::cout << "Movimiento inválido: La caja no puede moverse a la posición destino." << std::endl;
        handleInvalidMove();
    }
}

bool Game::isBox(Node* pNewNode) {
    return pNewNode->getSymbol() == '$';
}

bool Game::isValidPos(Node* node) {
    return node != nullptr && node->getSymbol() != '#';
}

void Game::movePlayerToDirection(char direction) {
    Node* currentNode = this->player;
    Node* nextNode = nullptr;

    switch (direction) {
    case 'W':
        nextNode = this->player->getNodeUp();
        break;
    case 'D':
        nextNode = this->player->getNodeRight();
        break;
    case 'S':
        nextNode = this->player->getNodeDown();
        break;
    case 'A':
        nextNode = this->player->getNodeLeft();
        break;
    default:
        return;
    }

    if (nextNode != nullptr) {
        if (isBox(nextNode)) {
            moveBox(direction, nextNode);
        }

        if (isValidPos(nextNode)) {
            if (wasBase) {
                currentNode->setSymbol('.');
            }
            else {
                currentNode->setSymbol(' ');
            }

            if (nextNode->getSymbol() == '.' || nextNode->getSymbol() == '!') {
                this->wasBase = true;
            }
            else {
                this->wasBase = false;
            }

            nextNode->setSymbol('@'); // Colocar jugador en la nueva posición
            this->player = nextNode;  // Actualizar la posición del jugador
        }
        else {
            std::cout << "Movimiento inválido: No se puede mover a esta posición." << std::endl;
            handleInvalidMove();
        }
    }
}

void Game::movePlayer() {
    int keyPressed = _getch();

    if (keyPressed == 0 || keyPressed == 224) {  // Tecla especial (flechas)
        keyPressed = _getch();  // Capturar el segundo valor de la tecla
        switch (keyPressed) {
        case 72:  // Flecha ARRIBA
            movePlayerToDirection('W');
            recordMove('W');
            break;
        case 80:  // Flecha ABAJO
            movePlayerToDirection('S');
            recordMove('S');
            break;
        case 75:  // Flecha IZQUIERDA
            movePlayerToDirection('A');
            recordMove('A');
            break;
        case 77:  // Flecha DERECHA
            movePlayerToDirection('D');
            recordMove('D');
            break;
        default:
            return;
        }
    }
    else {  // Teclas estándar WASD
        switch (keyPressed) {
        case 'W': case 'w':
            movePlayerToDirection('W');
            recordMove('W');
            break;
        case 'D': case 'd':
            movePlayerToDirection('D');
            recordMove('D');
            break;
        case 'S': case 's':
            movePlayerToDirection('S');
            recordMove('S');
            break;
        case 'A': case 'a':
            movePlayerToDirection('A');
            recordMove('A');
            break;
        default:
            return;
        }
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

void Game::handleInvalidMove() {
    char choice;
    std::cout << "Deseas continuar el juego?\n c: continuar\n r: reiniciar\n n: salir\n ";
    std::cin >> choice;
    if (choice == 'c' || choice == 'C') {
        return;
    }
    else if (choice == 'r' || choice == 'R') {
        resetGame(); // Reiniciar el nivel actual
    }
    else {
        std::cout << "Saliendo del juego." << std::endl;
        exit(0);
    }
}

void Game::resetGame() {
    createBoard(levels[currentLevelIndex]); // Recargar el nivel actual
    setPlayer(); // Volver a configurar el jugador
}

void Game::recordMove(char direction) {
    switch (direction) {
    case 'W':
        replayMoves.push_back("Movimiento: Arriba");
        break;
    case 'A':
        replayMoves.push_back("Movimiento: Izquierda");
        break;
    case 'S':
        replayMoves.push_back("Movimiento: Abajo");
        break;
    case 'D':
        replayMoves.push_back("Movimiento: Derecha");
        break;
    default:
        break;
    }
}

void Game::showReplay() {
    std::cout << "Repetición de movimientos:" << std::endl;
    for (const auto& move : replayMoves) {
        std::cout << move << std::endl;
    }
}

void Game::playGame() {
    while (true) {
        system("cls");
        printBoard();

        if (allBoxesAtDestinations()) {
            std::cout << "¡Has ganado!" << std::endl;
            handleInvalidMove();

            // Avanza al siguiente nivel si existe
            if (currentLevelIndex + 1 < levels.size()) {
                currentLevelIndex++;
                createBoard(levels[currentLevelIndex]);  // Carga el siguiente nivel
            }
            else {
                std::cout << "¡Has completado todos los niveles!" << std::endl;
                break;
            }
        }

        movePlayer();
    }
}

void Game::run() {
    std::cout << "Bienvenido al juego Sokoban." << std::endl;

    createBoard(levels[currentLevelIndex]); // Inicializar el juego creando el primer nivel

    playGame();
}


//#include "Game.h"
//
//Game::Game() {
//<<<<<<< HEAD
//    levels = { "level1.txt", "level2.txt", "level3.txt", "level4.txt", "level5.txt" };
//    currentLevelIndex = 0;
//=======
//    this->currentLevel = "indef";
//    this->player = nullptr;
//    this->playerName = "indef";
//    this->wasBase = false;
//}
//>>>>>>> 7d4bb488a70e90fd92840eabed5cbf6f3280d734
//
//    this->player = nullptr;
//    this->wasBase = false;
//}
//void Game::createBoard(std::string pLevel) {
//    Level level;
//    if (!level.loadLevelFromFile(pLevel)) {
//        std::cout << "Error leyendo el nivel desde " << pLevel << std::endl;
//        return;
//    }
//
//    currentLevel = level; // Almacena el nivel cargado
//
//    int size = level.getRows();  // Obtener filas del nivel cargado
//    this->board.setSize(size);    // Establecer tamaño en la lista
//    this->board.createList();
//    this->board.insertData(level.getGrid(), level.getRows(), level.getCols()); // Usa cols también
//
//    setPlayer(); // Llama a setPlayer después de configurar la lista
//}
//
//void Game::setPlayer() {
//    Node* row = this->board.getHead();
//    while (row != nullptr) {
//        Node* currentNode = row;
//        while (currentNode != nullptr) {
//            if (currentNode->getSymbol() == '@') {
//                this->player = currentNode;
//                return;
//            }
//            currentNode = currentNode->getNodeRight();
//        }
//        row = row->getNodeDown();
//    }
//    std::cout << "Error: Jugador no encontrado en el tablero." << std::endl;
//}
//
//void Game::swapCharacters(Node* pPrevNode, Node* pNewPosPlayer) {
//    if (pNewPosPlayer->getSymbol() == '.') {
//        pPrevNode->setSymbol('!');
//        pNewPosPlayer->setSymbol('!');
//    }
//    else {
//        char aux = pPrevNode->getSymbol();
//        pPrevNode->setSymbol(pNewPosPlayer->getSymbol());
//        pNewPosPlayer->setSymbol(aux);
//    }
//}
//
//<<<<<<< HEAD
//=======
//void Game::newPosPlayer(){
//
//}
//
//void Game::swapCharacters(Node* pPrevNode, Node* pNewPosPlayer){
//    if (pNewPosPlayer->getSymbol() == '.') {
//        
//    }
//    
//    char aux = pPrevNode->getSymbol();
//    pPrevNode->setSymbol(pNewPosPlayer->getSymbol());
//    pNewPosPlayer->setSymbol(aux);
//}
//
//>>>>>>> 7d4bb488a70e90fd92840eabed5cbf6f3280d734
//void Game::printBoard() {
//    std::cout << currentLevel.getLevelName() << '\n' << std::endl;
//
//    Node* row = this->board.getHead();
//    while (row != nullptr) {
//        Node* currentNode = row;
//        while (currentNode != nullptr) {
//            std::cout << currentNode->getSymbol();
//            currentNode = currentNode->getNodeRight();
//        }
//        std::cout << std::endl;
//        row = row->getNodeDown();
//    }
//}
//
//<<<<<<< HEAD
//void Game::moveBox(char direction, Node* boxNode) {
//    Node* nextPosBox = nullptr;
//
//    switch (direction) {
//    case 'W':
//    case 'w':
//        nextPosBox = boxNode->getNodeUp();
//        break;
//    case 'D':
//    case 'd':
//        nextPosBox = boxNode->getNodeRight();
//        break;
//    case 'S':
//    case 's':
//        nextPosBox = boxNode->getNodeDown();
//        break;
//    case 'A':
//    case 'a':
//        nextPosBox = boxNode->getNodeLeft();
//        break;
//    default:
//        return;
//    }
//
//    if (nextPosBox != nullptr && isValidPos(nextPosBox)) {
//        char nextSymbol = nextPosBox->getSymbol();
//
//        if (nextSymbol == '.') {
//            nextPosBox->setSymbol('!');
//        }
//        else if (nextSymbol == ' ') {
//            nextPosBox->setSymbol('$');
//        }
//
//        // Restaurar posición anterior de la caja
//        if (boxNode->getSymbol() == '$') {
//            boxNode->setSymbol(' ');
//        }
//        else if (boxNode->getSymbol() == '.') {
//            boxNode->setSymbol('.');
//        }
//    }
//    else {
//        std::cout << "Movimiento inválido: La caja no puede moverse a la posición destino." << std::endl;
//        handleInvalidMove();
//    }
//}
//
//
//bool Game::isBox(Node* pNewNode) {
//    return pNewNode->getSymbol() == '$';
//}
//
//bool Game::isValidPos(Node* node) {
//    return node != nullptr && node->getSymbol() != '#';
//}
//
//void Game::movePlayerToDirection(char direction) {
//    Node* currentNode = this->player;
//    Node* nextNode = nullptr;
//
//    switch (direction) {
//    case 'W':
//        nextNode = this->player->getNodeUp();
//        break;
//    case 'D':
//        nextNode = this->player->getNodeRight();
//        break;
//    case 'S':
//        nextNode = this->player->getNodeDown();
//        break;
//    case 'A':
//        nextNode = this->player->getNodeLeft();
//        break;
//    default:
//        return;
//    }
//
//    if (nextNode != nullptr) {
//        if (isBox(nextNode)) {
//            moveBox(direction, nextNode);
//        }
//
//        if (isValidPos(nextNode)) {
//            if (wasBase) {
//                currentNode->setSymbol('.');
//            }
//            else {
//                currentNode->setSymbol(' ');
//            }
//
//            if (nextNode->getSymbol() == '.' || nextNode->getSymbol() == '!') {
//                this->wasBase = true;
//            }
//            else {
//                this->wasBase = false;
//            }
//
//            nextNode->setSymbol('@'); // Colocar jugador en la nueva posición
//            this->player = nextNode;  // Actualizar la posición del jugador
//        }
//        else {
//            std::cout << "Movimiento inválido: No se puede mover a esta posición." << std::endl;
//            handleInvalidMove();
//        }
//    }
//}
//
//void Game::movePlayer() {
//    int keyPressed = _getch();
//
//    if (keyPressed == 0 || keyPressed == 224) {  // Tecla especial (flechas)
//        keyPressed = _getch();  // Capturar el segundo valor de la tecla
//        switch (keyPressed) {
//        case 72:  // Flecha ARRIBA
//            movePlayerToDirection('W');
//            recordMove('W');
//            break;
//        case 80:  // Flecha ABAJO
//            movePlayerToDirection('S');
//            recordMove('S');
//            break;
//        case 75:  // Flecha IZQUIERDA
//            movePlayerToDirection('A');
//            recordMove('A');
//            break;
//        case 77:  // Flecha DERECHA
//            movePlayerToDirection('D');
//            recordMove('D');
//            break;
//        default:
//            return;
//        }
//    }
//    else {  // Teclas estándar WASD
//        switch (keyPressed) {
//        case 'W': case 'w':
//            movePlayerToDirection('W');
//            recordMove('W');
//            break;
//        case 'D': case 'd':
//            movePlayerToDirection('D');
//            recordMove('D');
//            break;
//        case 'S': case 's':
//            movePlayerToDirection('S');
//            recordMove('S');
//            break;
//        case 'A': case 'a':
//            movePlayerToDirection('A');
//            recordMove('A');
//            break;
//        default:
//            return;
//        }
//    }
//}
//
//bool Game::allBoxesAtDestinations() {
//    Node* row = this->board.getHead();
//    while (row != nullptr) {
//        Node* currentNode = row;
//        while (currentNode != nullptr) {
//            if (currentNode->getSymbol() == '$') {
//                return false;  // Al menos una caja no está en un destino
//            }
//            currentNode = currentNode->getNodeRight();
//        }
//        row = row->getNodeDown();
//    }
//    return true;  // Todas las cajas están en destinos
//}
//
//void Game::handleInvalidMove() {
//    char choice;
//    std::cout << "Deseas continuar el juego?\n c: continuar\n r: reiniciar\n n: salir\n ";
//    std::cin >> choice;
//    if (choice == 'c' || choice == 'C') {
//        return;
//    }
//    else if (choice == 'r' || choice == 'R') {
//        resetGame(); // Reiniciar el nivel actual
//    }
//    else {
//        std::cout << "Saliendo del juego." << std::endl;
//        exit(0);
//    }
//}
//
//void Game::resetGame() {
//    createBoard(levels[currentLevelIndex]); // Recargar el nivel actual
//    setPlayer(); // Volver a configurar el jugador
//}
//
//void Game::recordMove(char direction) {
//    switch (direction) {
//    case 'W':
//        replayMoves.push_back("Movimiento: Arriba");
//        break;
//    case 'A':
//        replayMoves.push_back("Movimiento: Izquierda");
//        break;
//    case 'S':
//        replayMoves.push_back("Movimiento: Abajo");
//        break;
//    case 'D':
//        replayMoves.push_back("Movimiento: Derecha");
//        break;
//    default:
//=======
//void Game::moveBox(char pPos, Node* pNode){
//    Node* nextPosBox = nullptr;
//    switch (pPos) {
//    case 'W':
//    case 'w':
//        nextPosBox = pNode->getNodeUp();
//        break;
//    case 'D':
//    case 'd':
//        nextPosBox = pNode->getNodeRight();
//        break;
//    case 'S':
//    case 's':
//        nextPosBox = pNode->getNodeDown();
//        break;
//    case 'A':
//    case 'a':
//        nextPosBox = pNode->getNodeLeft();
//        break;
//    default:
//        return;
//    }
//    if (isValidPos(nextPosBox)) {
//        swapCharacters(nextPosBox, pNode);
//    }
//}
//
//bool Game::isBox(Node* pNewNode){
//    if (pNewNode->getSymbol() == '$') {
//        return true;
//    }
//    return false;
//}
//
//bool Game::isValidPos(Node* pNode2) {
//    if (pNode2->getSymbol() == '#') {
//        return false;
//    }
//    return true;
//}
//
//void Game::movePlayer(){
//    char keyPressed = _getch();
//    Node* actualNode = this->player; 
//    Node* nextNode = nullptr;
//
//    switch (keyPressed) {
//    case 'W':
//    case 'w':
//        nextNode = this->player->getNodeUp();
//        break;
//    case 'D':
//    case 'd':
//        nextNode = this->player->getNodeRight();
//        break;
//    case 'S':
//    case 's':
//        nextNode = this->player->getNodeDown();
//        break;
//    case 'A':
//    case 'a':
//        nextNode = this->player->getNodeLeft();
//>>>>>>> 7d4bb488a70e90fd92840eabed5cbf6f3280d734
//        break;
//    default:
//        return;
//    }
//    if (isBox(nextNode)) {
//        moveBox(keyPressed, nextNode);
//    }
//    // Validar si el movimiento es posible
//    if (nextNode != nullptr && isValidPos(nextNode)) {
//        // Restaurar la posición anterior
//        if (wasBase) {
//            actualNode->setSymbol('.');  // Restauramos la base anterior si estaba en una
//        }
//        else {
//            actualNode->setSymbol(' ');  // Si no estaba en una base, dejamos un espacio
//        }
//        // Verificar si la nueva posición es una base ('.')
//        if (nextNode->getSymbol() == '.') {
//            this->wasBase = true;  // La nueva posición es una base
//        }
//        else {
//            this->wasBase = false; // No es una base
//        }
//
//        // Mover al jugador a la nueva posición
//        nextNode->setSymbol('@');  // Colocamos al jugador
//        this->player = nextNode;   // Actualizamos la posición del jugador
//    }
//}
//
//void Game::showReplay() {
//    std::cout << "Repetición de movimientos:" << std::endl;
//    for (const auto& move : replayMoves) {
//        std::cout << move << std::endl;
//    }
//}
//
//void Game::playGame() {
//    while (true) {
//        system("cls");
//        printBoard();
//
//        if (allBoxesAtDestinations()) {
//            std::cout << "¡Has ganado!" << std::endl;
//            handleInvalidMove();
//
//            // Avanza al siguiente nivel si existe
//            if (currentLevelIndex + 1 < levels.size()) {
//                currentLevelIndex++;
//                createBoard(levels[currentLevelIndex]);  // Carga el siguiente nivel
//            }
//            else {
//                std::cout << "¡Has completado todos los niveles!" << std::endl;
//                break;
//            }
//        }
//
//        movePlayer();
//    }
//}

