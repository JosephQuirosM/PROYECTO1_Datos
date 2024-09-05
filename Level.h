#pragma once

#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

class Level
{
private:
    std::string title;
    int columns, rows;
    std::vector<std::string> grid;

public:   
    Level(const std::string& filename);

    Level();

    ~Level();

    void display();

    void saveLevelToFile(const std::string& filename) const;

    std::string getTitle() const;

    int getColumns() const;

    int getRows() const;

    std::vector<std::string> getGrid() const;

    void setTitle(const std::string& newTitle);

    void setColumns(int newColumns);

    void setRows(int newRows);

    void setGrid(const std::vector<std::string>& newGrid);

   

private:
    bool loadFromFile(const std::string& filename);

    
};

#endif;

