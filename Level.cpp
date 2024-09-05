#include "Level.h"



Level::Level(const std::string& filename)
{
	loadFromFile(filename);
}

Level::Level()
{

}

Level::~Level()
{
}

bool Level::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return false;
    }

    // título
    std::getline(file, title, ';');  // Lee hasta ;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignora el resto 

    //dimensiones
    std::string dimensions;
    std::getline(file, dimensions, ';');
    std::istringstream iss(dimensions);
    char comma;
    iss >> columns >> comma >> rows;  //x,y 

    //mapa
    grid.clear();
    std::string line;
    while (std::getline(file, line)) {
        grid.push_back(line);  // Agrega mapa
    }

    file.close();
    return true;
}

void Level::saveLevelToFile(const std::string& filename) const
{

    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return;
    }

    // Guarda el txt
    file << title << ";" << std::endl;
    file << columns << "," << rows << ";" << std::endl;

    for (const auto& line : grid) {
        file << line << std::endl;  // Escribe mapa
    }

    file.close();
    std::cout << "Nivel guardado exitosamente en " << filename << std::endl;

}
void Level::display()
{
    std::cout << title << std::endl;
    std::cout << "Size. " << "colum= " << columns << " rows= " << rows << std::endl;
    for (const auto& line : grid) {
        std::cout << line << std::endl;
    }
}

std::string Level::getTitle() const
{
    return title;
}

int Level::getColumns() const
{
    return columns;
}

int Level::getRows() const
{
    return rows;
}

std::vector<std::string> Level::getGrid() const
{
    return grid;
}

void Level::setTitle(const std::string& newTitle)
{
    title = newTitle;
}

void Level::setColumns(int newColumns)
{
    columns = newColumns;
}

void Level::setRows(int newRows)
{
    rows = newRows;
}

void Level::setGrid(const std::vector<std::string>& newGrid)
{
    grid = newGrid;
}
