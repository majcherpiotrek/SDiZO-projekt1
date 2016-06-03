#include "Node.h"


/*Konstruktor bezargumentowy klasy Node,
reprezentuj¹cej pojedynczy element listy. Tworzy element
o dwóch wskaŸnikach NULL i wartoœci 0.*/
Node::Node()
{
	new Node(nullptr, 0, nullptr);
}
/*Konstruktor z argumentami klasy Node. Tworzy nowy
element o zadanych wskaŸnikach oraz wartoœci.*/
Node::Node(Node * _leftPointer, int _value, Node * _rightPointer)
{
	leftPointer = _leftPointer;
	rightPointer = _rightPointer;
	value = _value;
}
/*Destruktor klasy Node. Sprz¹ta przed usuniêciem elementu
przestawiaj¹c wskaŸniki s¹siednich elementów listy tak, aby pokazywa³y teraz na siebie.*/
Node::~Node()
{
	if (leftPointer != nullptr)
		leftPointer->rightPointer = this->rightPointer;
	if (rightPointer != nullptr)
		rightPointer->leftPointer = this->leftPointer;
}
