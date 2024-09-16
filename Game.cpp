#include "Game.h"

Game::Game() {
    this->currentLevel = "indef";
    this->player = nullptr;
    this->playerName = "indef";
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

void Game::swapCharacters(Node* pNode1, Node* pNode2){
    char aux = pNode1->getSymbol();
    pNode1->setSymbol(pNode2->getSymbol());
    pNode2->setSymbol(aux);
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

bool Game::isValidPos(Node* pNode2) {
    if (pNode2->getSymbol() == '#') {
        return false;
    }
    return true;
}

void Game::movePlayer(){
    char keyPressed = _getch();
    Node* prevNode = nullptr;
    switch (keyPressed) {
    case 'W':
    case 'w': // Mover hacia arriba
        if (isValidPos(this->player->getNodeUp())) {
            prevNode = this->player;
            this->player = player->getNodeUp();
            swapCharacters(prevNode, this->player);
        }
        break;
    case 'D':
    case 'd': // Mover hacia la derecha
        if (isValidPos(this->player->getNodeRight())) {
            prevNode = this->player;
            this->player = player->getNodeRight();
            swapCharacters(prevNode, this->player);
        }
        break;
    case 'S':
    case 's': // Mover hacia abajo
        if (isValidPos(this->player->getNodeDown())) {
            prevNode = this->player;
            this->player = player->getNodeDown();
            swapCharacters(prevNode, this->player);
        }
        break;
    case 'A':
    case 'a': // Mover hacia la izquierda
        if (isValidPos(this->player->getNodeLeft())) {
            prevNode = this->player;
            this->player = player->getNodeLeft();
            swapCharacters(prevNode, this->player);
        }
        break;
    }
}

void Game::run(){
    while (true) {
        system("cls"); // Limpia la consola (Windows). En Linux sería "clear".
        printBoard();
        movePlayer();
    }
}
