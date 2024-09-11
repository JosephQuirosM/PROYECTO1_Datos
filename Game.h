#ifndef GAME_H
#define GAME_H
#include "OrthogonalList.h"
#include "Level.h"
#include <string>
class Game{
private:
	OrthogonalList board;
	std::string currentLevel;
public:
	Game();
	void createBoard(std::string level);

};
#endif