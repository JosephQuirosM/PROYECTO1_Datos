#include "Level.h"

bool Level::loadLevelFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
        return false;
    }

    std::string line;

    if (std::getline(file, line)) {
        std::stringstream ss(line);
        std::getline(ss, levelName, ';');  // Lee hasta el punto y coma
       
    }

    // Leer la segunda línea para obtener el tamaño del tablero
    if (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string temp;

        std::getline(ss, temp, ',');
        rows = std::stoi(temp);

        std::getline(ss, temp, ';');
        cols = std::stoi(temp);
    }


    // Leer las siguientes líneas para el diseño del tablero
    while (std::getline(file, line)) {
        grid.push_back(line);
    }

    file.close();
    return true;
}

std::string Level::getLevelName() const {
    return levelName;
}

std::vector<std::string> Level::getGrid() const {
    return grid;
}

int Level::getRows() const {
    return rows;
}

int Level::getCols() const {
    return cols;
}

void Level::setLevel(int level)
{
    this->level = level;
}

int Level::getLevel()
{
    return level;
}

void Level::printLevel() const {
    std::cout << "Nombre del nivel: " << levelName << std::endl;
    std::cout << "Tamaño del tablero: " << rows << "x" << cols << std::endl;
    for (const auto& row : grid) {
        std::cout << row << std::endl;
    }
}

void Level::saveGame(std::vector<char>& moves, int currentLevel)
{
    std::ofstream save("saveFile.txt");

    if (!save.is_open()) {
        std::cout << "Error al guardar partida";
        return;
    }

    save << currentLevel <<std::endl;

    std::string movement = "";

    if (!moves.empty()) {
        for (const auto& move : moves) {
            movement += move;
            movement += '-';
        }
        movement.erase(movement.length() - 1, 1);
    }
    
    movement += ';';
    save << movement <<std::endl;

    save.close();
}

std::string Level::loadGame()
{
    std::ifstream game("saveFile.txt");
    std::string line;

    if (!game.is_open()) {
        std::cout << "error al cargar una partida\n";
        return "ERROR";
    }

    std::getline(game, line);
    setLevel(std::stoi(line));


    std::getline(game, line);

    return line;
}
