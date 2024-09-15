#ifndef GAME_H
#define GAME_H
#include "OrthogonalList.h"
#include "Level.h"
#include <string>
class Game{
private:
	OrthogonalList board;
	std::string currentLevel;
	Node* player;
	std::string playerName;
public:
	Game();
	void createBoard(std::string level);
	void setPlayer();
	void printBoard();
};
#endif