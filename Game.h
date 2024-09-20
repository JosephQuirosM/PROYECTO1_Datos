
#ifndef GAME_H
#define GAME_H
#include "OrthogonalList.h"
#include "Menu.h"
#include "Level.h"
#include <vector>
#include <string>
#include <conio.h>
class Game {
private:
	OrthogonalList board;
	Level currentLevel;
	Node* player;
	std::string playerName;
	bool wasBase;

	std::vector<std::string> replayMoves;

	std::vector<std::string> levels;
	int currentLevelIndex = 0;

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

	void swapCharacters(Node* pPrevNode, Node* pNewPosPlayer);
	void playGame();
	bool allBoxesAtDestinations();

	void movePlayerToDirection(char direction);
	void handleInvalidMove();
	void resetGame();
	void recordMove(char direction);
	void showReplay();
	void setColor(int textColor, int bgColor);
};
#endif