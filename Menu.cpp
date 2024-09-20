#include "Menu.h"
#include <windows.h>
#include <thread>
#include <chrono>

Menu::~Menu() {}

void Menu::displayMenu() {
    setConsoleColors(4, 0);
    system("cls");

    const int totalWidth = 50;

    std::cout << std::string(totalWidth, '*') << std::endl; // Línea superior
    std::cout << "*" << std::string(totalWidth - 2, ' ') << "*" << std::endl; // Espacio vacío

    printCenteredWithVerticalLines("Bienvenido a Sokoban", totalWidth);
    printCenteredWithVerticalLines("1. Jugar", totalWidth);
    printCenteredWithVerticalLines("2 Cargar juego", totalWidth);
    printCenteredWithVerticalLines("3. Cómo usar", totalWidth);
    printCenteredWithVerticalLines("4. Salir", totalWidth);

    std::cout << "*" << std::string(totalWidth - 2, ' ') << "*" << std::endl;
    printCenteredWithVerticalLines("Seleccione una opción:", totalWidth);
    std::cout << std::string(totalWidth, '*') << std::endl; // Línea inferior
}

void Menu::howToPlay() {
    system("cls");
    setConsoleColors(14, 0);
    std::cout << "\n*************** Cómo Usar ***************\n";
    std::cout << "@  = Jugador en el tablero\n";
    std::cout << "#  = Pared\n";
    std::cout << ".  = Espacio para colocar una caja\n";
    std::cout << "$  = Caja\n";
    std::cout << "!  = Caja ubicada en el espacio correcto\n";
    std::cout << "******************************************\n\n";
    std::cout << "Presione cualquier tecla para volver al menú principal.\n";
    std::cin.ignore();
    std::cin.get();
}
void Menu::loadGame()
{
    system("cls");
    std::cout << "Presione cualquier tecla para volver al menú principal.\n";
    std::cin.ignore();
    std::cin.get();
}
void Menu::printCenteredWithVerticalLines(const std::string& text, int totalWidth) {
    setConsoleColors(4, 0);
    int textWidth = totalWidth - 4; // Espacio para las líneas verticales
    int padding = (textWidth - text.length()) / 2;
    if (padding < 0) padding = 0;

    std::cout << "*"; 
    std::cout << std::string(padding, ' ') << text;
    std::cout << std::string(textWidth - padding - text.length(), ' ') << "*"; // Línea vertical derecha
    std::cout << std::endl;
}

void Menu::runMenu() {
    setConsoleSize(50, 20); // Cambiar tamaño de consola

    int choice;
    Game game;
    do {
        displayMenu();
        std::cin >> choice;
        switch (choice) {
        case 1:
            setConsoleColors(3, 0);
            animate();
            game.run(); 
            break;
        case 2:
            loadGame();
            break;
        case 3:
            howToPlay();
            break;
        case 4:
            std::cout << "Hasta luego\n";
            exit(-1);
            break;
        default:
            std::cout << "Opción no válida. Intente nuevamente.\n";
        }
    } while (choice != 4);
}

void Menu::setConsoleSize(int width, int height) {
    COORD coord = { (SHORT)width, (SHORT)height };
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    HWND console = GetConsoleWindow();
    MoveWindow(console, 100, 100, width * 8, height * 20, TRUE);
}

void Menu::setConsoleColors(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

void Menu::animate() {
    std::cout << "Cargando";
        for (int i = 0; i < 3; i++) {
        std::cout << ".";
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Espera 0.5 segundos
    }
    std::cout << std::endl;
}
