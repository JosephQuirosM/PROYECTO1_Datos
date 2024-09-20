#include "Node.h"


Node::Node(char caracter){
    this->character = caracter;
    right = nullptr;
    left = nullptr;
    up = nullptr;
    down = nullptr;

}

Node::Node(char caracter, int r, int c) {
    this->character = caracter;
    right = nullptr;
    left = nullptr;
    up = nullptr;
    down = nullptr;
    row = r;    // Inicializa la fila
    column = c; // Inicializa la columna
}

Node* Node::getNodeRight()
{
    return right;
}

Node* Node::getNodeLeft()
{
    return left;
}

Node* Node::getNodeUp()
{
    return up;
}

Node* Node::getNodeDown()
{
    return down;
}

char Node::getSymbol() const{
    return this->character;
}



void Node::setNodeRight(Node* right)
{
    this->right = right;
}

void Node::setNodeLeft(Node* left)
{
    this->left = left;
}

void Node::setNodeUp(Node* up)
{
    this->up = up;
}

void Node::setNodeDown(Node* down)
{
    this->down = down;
}

void Node::setSymbol(char pSymbol){
    this->character = pSymbol;
}


int Node::getRow() const { 
    return row;
}
void Node::setRow(int r) {
    row = r;
}

int Node::getColumn() const {
    return column;
}
void Node::setColumn(int c) {
    column = c; 
}