#include "Node.h"


/*Konstruktor bezargumentowy klasy Node,
reprezentuj�cej pojedynczy element listy. Tworzy element
o dw�ch wska�nikach NULL i warto�ci 0.*/
Node::Node()
{
	new Node(nullptr, 0, nullptr);
}
/*Konstruktor z argumentami klasy Node. Tworzy nowy
element o zadanych wska�nikach oraz warto�ci.*/
Node::Node(Node * _leftPointer, int _value, Node * _rightPointer)
{
	leftPointer = _leftPointer;
	rightPointer = _rightPointer;
	value = _value;
}
/*Destruktor klasy Node. Sprz�ta przed usuni�ciem elementu
przestawiaj�c wska�niki s�siednich element�w listy tak, aby pokazywa�y teraz na siebie.*/
Node::~Node()
{
	if (leftPointer != nullptr)
		leftPointer->rightPointer = this->rightPointer;
	if (rightPointer != nullptr)
		rightPointer->leftPointer = this->leftPointer;
}
