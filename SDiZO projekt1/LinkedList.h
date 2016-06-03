#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Node.h"
#include "FileNotFoundException.h"
#include "DataTypeMismatchException.h"
#include "IndexOutOfBoundsException.h"

class LinkedList
{
	
private:
	

	Node* head; // Wskaünik na g≥owÍ listy
	Node* tail; // Wskaünik na ogon listy
	Node* search(int index);
	int size;
	
public:
	LinkedList();
	~LinkedList();

	void readFile(std::string file_name);
	void saveToFile(std::string file_name);
	void push_front(int _value);
	void push_back(int _value);
	void pop_front();
	void pop_back();
	void put(int _index, int _value);
	int get(int index);
	int searchValue(int _value);
	void removeIndex(int index);
	int getSize();
	void replace(int index, int _value);
	friend std::ostream & operator <<(std::ostream & output, LinkedList & lista);
};

