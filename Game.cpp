#include "Game.h"

Game::Game() {
    this->currentLevel = "indef";
    this->player = nullptr;
    this->playerName = "indef";
    this->wasBase = false;
}

void Game::createBoard(std::string pLevel) {
    Level level;
    // Cargar el nivel desde archivo
    if (!level.loadLevelFromFile(pLevel)) {
        std::cout << "Error leyendo el nivel desde " << pLevel << std::endl;
        return;
    }
    int size = level.getGrid().size();
    // Configurar la lista ortogonal con el tamaño del nivel
    this->board.setSize(size);
    this->board.createList();
    this->board.insertData(level.getGrid(), size, size);

    std::cout << "Nivel cargado exitosamente." << std::endl;
    setPlayer();
}

void Game::setPlayer() {
    Node* row = this->board.getHead();
    bool playerFound = false;

    // Recorrer el tablero para encontrar al jugador
    while (row != nullptr) {
        Node* currentNode = row;
        while (currentNode != nullptr) {
            if (currentNode->getSymbol() == '@') {
                this->player = currentNode;
                std::cout << "Jugador encontrado en el tablero." << std::endl;
                playerFound = true;
                return;
            }
            currentNode = currentNode->getNodeRight();
        }
        row = row->getNodeDown();
    }

    if (!playerFound) {
        std::cout << "Error: Jugador no encontrado en el tablero." << std::endl;
    }
}

void Game::newPosPlayer(){

}

void Game::swapCharacters(Node* pPrevNode, Node* pNewPosPlayer){
    if (pNewPosPlayer->getSymbol() == '.') {
        
    }
    
    char aux = pPrevNode->getSymbol();
    pPrevNode->setSymbol(pNewPosPlayer->getSymbol());
    pNewPosPlayer->setSymbol(aux);
}

void Game::printBoard() {
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

void Game::moveBox(char pPos, Node* pNode){
    Node* nextPosBox = nullptr;
    switch (pPos) {
    case 'W':
    case 'w':
        nextPosBox = pNode->getNodeUp();
        break;
    case 'D':
    case 'd':
        nextPosBox = pNode->getNodeRight();
        break;
    case 'S':
    case 's':
        nextPosBox = pNode->getNodeDown();
        break;
    case 'A':
    case 'a':
        nextPosBox = pNode->getNodeLeft();
        break;
    default:
        return;
    }
    if (isValidPos(nextPosBox)) {
        swapCharacters(nextPosBox, pNode);
    }
}

bool Game::isBox(Node* pNewNode){
    if (pNewNode->getSymbol() == '$') {
        return true;
    }
    return false;
}

bool Game::isValidPos(Node* pNode2) {
    if (pNode2->getSymbol() == '#') {
        return false;
    }
    return true;
}

void Game::movePlayer(){
    char keyPressed = _getch();
    Node* actualNode = this->player; 
    Node* nextNode = nullptr;

    switch (keyPressed) {
    case 'W':
    case 'w':
        nextNode = this->player->getNodeUp();
        break;
    case 'D':
    case 'd':
        nextNode = this->player->getNodeRight();
        break;
    case 'S':
    case 's':
        nextNode = this->player->getNodeDown();
        break;
    case 'A':
    case 'a':
        nextNode = this->player->getNodeLeft();
        break;
    default:
        return;
    }
    if (isBox(nextNode)) {
        moveBox(keyPressed, nextNode);
    }
    // Validar si el movimiento es posible
    if (nextNode != nullptr && isValidPos(nextNode)) {
        // Restaurar la posición anterior
        if (wasBase) {
            actualNode->setSymbol('.');  // Restauramos la base anterior si estaba en una
        }
        else {
            actualNode->setSymbol(' ');  // Si no estaba en una base, dejamos un espacio
        }
        // Verificar si la nueva posición es una base ('.')
        if (nextNode->getSymbol() == '.') {
            this->wasBase = true;  // La nueva posición es una base
        }
        else {
            this->wasBase = false; // No es una base
        }

        // Mover al jugador a la nueva posición
        nextNode->setSymbol('@');  // Colocamos al jugador
        this->player = nextNode;   // Actualizamos la posición del jugador
    }
}

void Game::run(){
    while (true) {
        system("cls");
        printBoard();
        movePlayer();
    }
}
