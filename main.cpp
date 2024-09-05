#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Level.h"
#include <iostream>

int main()
{
    Level level1("Levels/lvl1.txt");
    level1.display();

    Level level2("Levels/lvl2.txt");
    level2.display();

    Level level3("Levels/lvl3.txt");
    level3.display();

    Level level4("Levels/lvl4.txt");
    level4.display();

    Level level5("Levels/lvl5.txt");
    level5.display();
   
    //Prueba guardado en lvl
    Level level;
    level.setTitle("prueba");
    level.setColumns(7);
    level.setRows(5);
    level.setGrid({
        "#######",
        "#BBBBB#",
        "#B@$BB#",
        "#B.BBB#",
        "#######"
        });

    level.saveLevelToFile("Levels/nivelPrueba.txt");// Guardar archivo


    /*sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }*/
	return 0;
}