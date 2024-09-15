#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
class Level {
private:
    std::string levelName;  // Nombre del nivel
    int rows;
    int cols;
    std::vector<std::string> grid;  // Aquí se almacena el tablero como una matriz de caracteres

public:
    Level() : rows(0), cols(0) {}

    // Cargar el tablero desde un archivo
    bool loadLevelFromFile(const std::string& filename);

    // Devuelve el nombre del nivel
    std::string getLevelName() const;

    // Devuelve el tablero
    std::vector<std::string> getGrid() const;

    // Devuelve el número de filas
    int getRows() const;

    // Devuelve el número de columnas
    int getCols() const;

    // Imprimir el nivel en consola (opcional para verificar)
    void printLevel() const;
};

#endif
