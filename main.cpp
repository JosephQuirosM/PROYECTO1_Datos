#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Level.h"
#include "OrthogonalList.h"
#include <iostream>
#include "Game.h"
int main(){
	Game obj;
	obj.createBoard("level1.txt");
	obj.run();
}