#include "OrthogonalList.h"

OrthogonalList::OrthogonalList( int size)
{
    head = nullptr;
	SIZE = size;
	createList();
}

OrthogonalList::OrthogonalList(){
    head = nullptr;
	this->SIZE = 0;
	
}

OrthogonalList::~OrthogonalList()
{
    clearList();
}

void OrthogonalList::setSize(int pSize){
	this->SIZE = pSize;
}

int OrthogonalList::getSize() const{
	return this->SIZE;
}

void OrthogonalList::createList() {
    Node* prev = nullptr;
    Node* rowStart = nullptr;

    for (int i = 0; i < SIZE; i++) {
        Node* newNode = new Node(0, i, 0); // x = i, y = 0 para la primera fila
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

    for (int i = 1; i < SIZE; i++) {
        prev = rowStart;
        Node* newRowStart = new Node(0, 0, i); // x = 0, y = i para la nueva fila
        prev->setNodeDown(newRowStart);
        newRowStart->setNodeUp(prev);
        Node* currentNode = newRowStart;

        for (int j = 1; j < SIZE; j++) {
            Node* newNode = new Node(0, j, i); // x = j, y = i
            currentNode->setNodeRight(newNode);
            newNode->setNodeLeft(currentNode);
            currentNode = newNode;
        }

        Node* temp = newRowStart;
        Node* prevRowNode = rowStart;
        for (int k = 0; k < SIZE; k++) {
            temp->setNodeUp(prevRowNode);
            prevRowNode->setNodeDown(temp);
            temp = temp->getNodeRight();
            prevRowNode = prevRowNode->getNodeRight();
        }

        rowStart = rowStart->getNodeDown();
    }
}

void OrthogonalList::clearList()
{
    Node* aux = nullptr;
    Node* del = nullptr;

    while (head != nullptr) {
        aux = head->getNodeRight();

        while (aux != nullptr) {
            del = aux;
            aux = aux->getNodeRight();
            delete del;
        }

        del = head;
        head = head->getNodeDown();
        delete del;
    }
}


void OrthogonalList::insertData(const std::vector<std::string>& pGrid,int pRow, int pColumn ){
	if (pRow > SIZE || pColumn > SIZE || pGrid.size() != SIZE || pGrid[0].length() != SIZE) {
		std::cout << "El tamaño de la grilla no coincide con el tamaño de la lista." << std::endl;
		return;
	}

	Node* currentRow = head;
	Node* currentNode = nullptr;
    char character;

	for (int i = 0; i < SIZE; ++i) {
		currentNode = currentRow;
		for (int j = 0; j < SIZE; ++j) {
            character = pGrid[i][j];

            if (character == '.') {
                currentNode->setBase(true);
            }
			currentNode->setSymbol(character); // Asignar el símbolo del nivel (e.g., '@', '$', etc.)
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
