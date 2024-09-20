
#ifndef NODE_H
#define NODE_H

class Node
{
private:
	Node* right;
	Node* left;
	Node* up;
	Node* down;
	char character;

	int row;   
	int column; 

public:
	Node(char caracter);
	Node(char caracter, int r, int c);
	Node* getNodeRight();
	Node* getNodeLeft();
	Node* getNodeUp();
	Node* getNodeDown();
	char getSymbol() const;

	void setNodeRight(Node* right);
	void setNodeLeft(Node* left);
	void setNodeUp(Node* up);
	void setNodeDown(Node* down);
	void setSymbol(char pSymbol);

	int getRow() const;
	void setRow(int r);
	int getColumn() const;
	void setColumn(int c);

};

#endif;
