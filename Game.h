
#ifndef GAME_H
#define GAME_H
#include "OrthogonalList.h"
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
	std::vector<char> replayMoves;
	std::vector<std::string> levels;
	int currentLevelIndex = 0;
	bool isPlaying;

public:
	Game();
	Game(int currentLevel, std::string movement);
	
	void run();
	void reloadGame();

private:
	void setPlayer();
	void createBoard(std::string level);
	void printBoard();
	void movePlayer();

	void playGame();
	bool allBoxesAtDestinations();
	void pauseMenu();
	void resetGame();
	void showReplay();
	void setColor(int textColor, int bgColor);

	void mapMovements(char move);
	
};
#endif