#include "MenuElement.h"



MenuElement::MenuElement(MenuElement* prev,const char * _name,MenuElement* nxt)
{
	previous = prev;
	next = nxt;
	name = _name;


}

MenuElement::~MenuElement()
{
	if (previous != nullptr)
		previous->next = this->next;
	if (next != nullptr)
		next->previous = this->previous;
	
}
