#include "SFML/Graphics.hpp";
#include "SFML/System.hpp"
#include <iostream>;

int main()
{
	sf::RenderWindow w;
	w.create(sf::VideoMode(500, 600), "Poker");

	while (w.isOpen()) {
		std::cout << "sirve\n";
		system("pause");
	}
	return 80;
}