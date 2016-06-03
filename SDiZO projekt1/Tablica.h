#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "IndexOutOfBoundsException.h"
#include "FileNotFoundException.h"
#include "DataTypeMismatchException.h"



class Tablica
{
private:
	int* head;
	int size;
public:
	
	Tablica(int*tab, int len);
	Tablica();
	~Tablica();

	void readFile(std::string file_name);
	void saveToFile(std::string file_name);
	void replace(int index, int value);
	void push_back(int value);
	void push_front(int value);
	void pop_back();
	void pop_front();
	void put(int index, int value);
	int searchValue(int value);
	void removeIndex(int index);
	bool removeValue(int value);

	int get(int index);
	int getSize() { return size; }
	friend std::ostream& operator << (std::ostream& output, Tablica& tab);
};

