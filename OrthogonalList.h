#ifndef ORTHOGONAL_LIST
#define ORTHOGONAL_LIST
#include "Node.h"
#include <iostream>

class OrthogonalList
{
private:
	Node* head;
	int SIZE;

public:
	OrthogonalList(int size);

	~OrthogonalList();

	void createList();
	void print();

};
#endif;
