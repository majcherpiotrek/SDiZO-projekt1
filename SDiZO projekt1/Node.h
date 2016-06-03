#pragma once
class Node
{
	friend class LinkedList;
private:
	Node* leftPointer;
	Node* rightPointer;
	int value;

public:
	

	Node();
	Node(Node* _leftPointer, int _value, Node* _rightPointer);
	~Node();

};

