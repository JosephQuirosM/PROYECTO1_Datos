#ifndef GAME_H
#define GAME_H
#include "OrthogonalList.h"
#include "Level.h"
#include <string>
#include <conio.h>
class Game{
private:
	OrthogonalList board;
	std::string currentLevel;
	Node* player;
	std::string playerName;
public:
	Game();
	void createBoard(std::string level);
	void printBoard();
	void movePlayer();
private:
	void setPlayer();
	void newPosPlayer();
	void swapCaracters(Node* pNode1, Node* pNode2);
};
#endif