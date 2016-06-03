#pragma once
#include <string>
class MenuElement
{
	friend class Menu;
	MenuElement* previous;
	MenuElement* next;
	std::string name;

public:
	MenuElement(MenuElement* prev,const char* _name, MenuElement* nxt);
	~MenuElement();
};

