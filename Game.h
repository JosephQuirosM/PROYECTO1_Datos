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
	void run();
private:
	bool isValidPos(Node* pNewPos);
	void setPlayer();
	void newPosPlayer();
	void swapCharacters(Node* pNode1, Node* pNode2);
};
#endif