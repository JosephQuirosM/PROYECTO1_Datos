#ifndef ORTHOGONAL_LIST
#define ORTHOGONAL_LIST
#include "Node.h"
#include <iostream>
#include <vector>
class OrthogonalList{
private:
	Node* head;
	int SIZE;

public:
	OrthogonalList(int size);
	OrthogonalList();
	~OrthogonalList();

	void setSize(int pSize);
	int getSize() const;
	void createList();
	void insertData(const std::vector<std::string>& grid, int pRow, int pColumn);
	Node* getHead();
	void print();

};
#endif;
