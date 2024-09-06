#include "OrthogonalList.h"

OrthogonalList::OrthogonalList( int size)
{
	SIZE = size;
	createList();
}

OrthogonalList::~OrthogonalList()
{
}

void OrthogonalList::createList()
{
	Node* prev = nullptr;

	 //crea columna 0 horizontal
	for (int i = 0; i < SIZE; i++)
	{
		Node* newNode = new Node(0);

		if (i == 0){
			head = newNode;
		}
		else {
			prev->setNodeRight(newNode);
			newNode->setNodeLeft(prev);
		}

		prev = newNode;
	}

	//crea fila

	for (int i = 0; i < SIZE; i++)
	{
		prev = head;
		
		for (int j = 0; j < i; j++)
		{
			prev = prev->getNodeRight();
		}

		for (int k = 1; k < SIZE; k++) {
			Node* newNode = new Node(0);
			
			prev->setNodeDown(newNode);
			newNode->setNodeUp(prev);
			prev = newNode;
		}
	}

	//unir las filas
	Node* next;
	for (int i = 0; i < SIZE - 1; i++)
	{
		prev = head;

		for (int j = 0; j < i; j++)
		{
			prev = prev->getNodeRight();
		}
		next = prev->getNodeRight();
		next = next->getNodeDown();
		prev = prev->getNodeDown();

		for (int k = 1; k < SIZE; k++) {
			next->setNodeLeft(prev);
			prev->setNodeRight(next);
			prev = prev->getNodeDown();
			next = next->getNodeDown();
		}
	}

}

void OrthogonalList::print()
{
	
	for (int i = 0; i < SIZE; i++)
	{
		Node* aux = head;

		for (int j = 0; j < i; j++) {
			aux = aux->getNodeDown();

		 }
		for (int k = 0; k < SIZE; k++)
		{
			std::cout << aux->getValue() << ", ";
			aux = aux->getNodeRight();
		}
		std::cout << std::endl;

	}
	std::cout << std::endl;
	std::cout << std::endl;
}
