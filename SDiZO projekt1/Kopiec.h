#pragma once
#include "Tablica.h"
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include "DataTypeMismatchException.h"
#include "FileNotFoundException.h"

class Kopiec
{
private:
	Tablica* root;
	int size;
	int search(int index, int value);
	void drawREK(std::ostream& output, int index);
	void heap_fix_up(Tablica* tab, int len);
	void heap_fix_down(Tablica*tab, int index, int len);
	
public:
	Kopiec();
	~Kopiec();

	void readFile(std::string file_name);
	void saveToFile(std::string file_name);
	void push(int value);
	void pop();
	int searchValue(int value);
	int get(int index);
	void draw(std::ostream& output);
	friend std::ostream& operator<<(std::ostream& output, Kopiec& kopiec);
};

