#include "Node.h"


Node::Node(int value)
{
    this->value = value;
    right = nullptr;
    left = nullptr;
    up = nullptr;
    down = nullptr;

}

Node::Node(char caracter)
{
    this->character = caracter;
    right = nullptr;
    left = nullptr;
    up = nullptr;
    down = nullptr;

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

int Node::getValue()
{
    return value;
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

void Node::setValue(int value)
{
    this->value = value;
}
