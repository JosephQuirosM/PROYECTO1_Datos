#ifndef GAME_H
#define GAME_H
#include "OrthogonalList.h"
#include "Level.h"
#include <string>
#include <conio.h>
class Game {
private:
	OrthogonalList board;
	Level currentLevel;
	Node* player;
<<<<<<< HEAD
	bool wasBase;

	std::vector<std::string> replayMoves;
	std::vector<std::string> levels;
	int currentLevelIndex = 0;

=======
	std::string playerName;
	bool wasBase;
>>>>>>> 7d4bb488a70e90fd92840eabed5cbf6f3280d734
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
<<<<<<< HEAD

	void swapCharacters(Node* pPrevNode, Node* pNewPosPlayer);
	void playGame();
	bool allBoxesAtDestinations();

	void movePlayerToDirection(char direction);
	void handleInvalidMove();
	void resetGame();

	std::vector<std::string> getReplay() const;  // Devuelve pasos de la repeticion
	void recordMove(char direction);
	void showReplay();
=======
	void newPosPlayer();
	void swapCharacters(Node* pPrevNode, Node* pNewPosPlayer);
>>>>>>> 7d4bb488a70e90fd92840eabed5cbf6f3280d734
};
#endif