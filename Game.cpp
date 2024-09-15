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
    std::cout << "Tamaño del nivel: " << size << std::endl;
    // Configurar la lista ortogonal con el tamaño del nivel
    this->board.setSize(size);
    this->board.insertData(level.getGrid(), size, size);

    std::cout << "Nivel cargado exitosamente." << std::endl;
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

void Game::printBoard() {
    Node* row = this->board.getHead();

    // Imprimir el tablero
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