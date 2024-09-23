
#ifndef MENU_H
#define MENU_H

#include "Game.h"

class Menu {

public:
    Menu() = default;
    ~Menu();

    void runMenu();

private:
    void setConsoleSize(int width, int height);
    void setConsoleColors(int textColor, int bgColor);
    void animate();
    void printCenteredWithVerticalLines(const std::string& text, int totalWidth);
    void displayMenu();
    void howToPlay();
    Game loadGames();

};
#endif
