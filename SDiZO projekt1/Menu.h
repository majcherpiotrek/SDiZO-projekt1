#pragma once
#include <string>
#include <iostream>
#include "MenuElement.h"
#include "IndexOutOfBoundsException.h"
class Menu
{
	MenuElement* head;
	MenuElement* tail;
	int menu_size;
	MenuElement* search(int index);
public:
	Menu();
	~Menu();

	void add(const char* menu_text);
	std::string get(int index);
	friend std::ostream& operator << (std::ostream& output, Menu& menu);
};

