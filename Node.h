
#ifndef NODE_H
#define NODE_H

class Node
{
private:
	Node* right;
	Node* left;
	Node* up;
	Node* down;
	int value;
	char character;

public:
	Node(int value);
	Node(char caracter);
	
	Node* getNodeRight();
	Node* getNodeLeft();
	Node* getNodeUp();
	Node* getNodeDown();
	int getValue();

	void setNodeRight(Node* right);
	void setNodeLeft(Node* left);
	void setNodeUp(Node* up);
	void setNodeDown(Node* down);
	void setValue(int value);


};

#endif;
