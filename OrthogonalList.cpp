#include "OrthogonalList.h"

OrthogonalList::OrthogonalList( int size)
{
	SIZE = size;
	createList();
}

OrthogonalList::OrthogonalList(){
	this->SIZE = 0;
	
}

OrthogonalList::~OrthogonalList()
{
}

void OrthogonalList::setSize(int pSize){
	this->SIZE = pSize;
}

int OrthogonalList::getSize() const{
	return this->SIZE;
}

void OrthogonalList::createList()
{
	Node* prev = nullptr;
	Node* rowStart = nullptr;
	Node* currentNode = nullptr;

	// Crear la primera fila (horizontal)
	for (int i = 0; i < SIZE; i++)
	{
		Node* newNode = new Node(0);

		if (i == 0) {
			head = newNode;
			rowStart = newNode;
		}
		else {
			prev->setNodeRight(newNode);
			newNode->setNodeLeft(prev);
		}

		prev = newNode;
	}

	// Crear las filas siguientes
	for (int i = 1; i < SIZE; i++)
	{
		prev = rowStart;
		Node* newRowStart = new Node(0);
		prev->setNodeDown(newRowStart);
		newRowStart->setNodeUp(prev);
		currentNode = newRowStart;

		for (int j = 1; j < SIZE; j++)
		{
			Node* newNode = new Node(0);
			currentNode->setNodeRight(newNode);
			newNode->setNodeLeft(currentNode);
			currentNode = newNode;
		}

		// Conectar la nueva fila a la fila anterior
		Node* temp = newRowStart;
		Node* prevRowNode = rowStart;
		for (int k = 0; k < SIZE; k++)
		{
			temp->setNodeUp(prevRowNode);
			prevRowNode->setNodeDown(temp);

			temp = temp->getNodeRight();
			prevRowNode = prevRowNode->getNodeRight();
		}

		// Actualizar la referencia de la fila actual
		rowStart = rowStart->getNodeDown();
	}

}

void OrthogonalList::insertData(const std::vector<std::string>& pGrid,int pRow, int pColumn ){
	if (pRow > SIZE || pColumn > SIZE || pGrid.size() != SIZE || pGrid[0].length() != SIZE) {
		std::cout << "El tamaño de la grilla no coincide con el tamaño de la lista." << std::endl;
		return;
	}

	Node* currentRow = head;
	Node* currentNode = nullptr;

	for (int i = 0; i < SIZE; ++i) {
		currentNode = currentRow;
		for (int j = 0; j < SIZE; ++j) {
			currentNode->setSymbol(pGrid[i][j]); // Asignar el símbolo del nivel (e.g., '@', '$', etc.)
			currentNode = currentNode->getNodeRight(); // Mover a la derecha en la fila actual
		}
		currentRow = currentRow->getNodeDown(); // Mover a la fila siguiente
	}
}

Node* OrthogonalList::getHead(){
	return this->head;
}

void OrthogonalList::print()
{
	Node* auxRow = head;  // Inicializamos con la primera fila

	for (int i = 0; i < SIZE; i++)
	{
		Node* aux = auxRow;  // Asignamos auxRow para la fila actual

		for (int k = 0; k < SIZE; k++)
		{
			std::cout << aux->getSymbol() << " ";
			aux = aux->getNodeRight();  // Avanzamos hacia la derecha en la fila
		}
		std::cout << std::endl;

		auxRow = auxRow->getNodeDown();  // Bajamos a la siguiente fila
	}
	std::cout << std::endl;
}
