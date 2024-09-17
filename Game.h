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
	bool wasBase;
public:
	Game();
	void createBoard(std::string level);
	void printBoard();
	void movePlayer();
	void run();
private:
	void moveBox(char pPos, Node* pNode);
	bool isBox(Node* pNewNode);
	bool isValidPos(Node* pNewPos);
	void setPlayer();
	void newPosPlayer();
	void swapCharacters(Node* pPrevNode, Node* pNewPosPlayer);
};
#endif