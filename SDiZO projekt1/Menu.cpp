#include "Menu.h"



MenuElement * Menu::search(int index)
{
	//Je�li index wykracza poza list� to zwraca wska�nik NULL.
	if (index < 0 || index >= menu_size)
		return nullptr;

	MenuElement* element;
	/*Je�li szukany indeks w pierwszej po�owie listy
	to zaczynamy szukanie od wska�nika na g�ow� listy.*/
	if (index <= menu_size / 2) {

		element = head;
		for (int i = 0; i != index; i++)
			element = element->next;

	}
	/*W przeciwnym wypadku zaczynamy szukanie od ostatniego elementu listy.*/
	else {
		element = tail->previous;
		for (int i = menu_size - 1; i != index; i--)
			element = element->previous;
	}

	return element;
}

Menu::Menu()
{
	head = nullptr;
	tail = nullptr;
	menu_size = 0;
}


Menu::~Menu()
{ 
	delete head;
	delete tail;
}

void Menu::add(const char* optionHeader)
{
	if (menu_size == 0) {
		// Tworz� now� "g�ow�" listy o warto�ci _value, oba wska�niki ustawione na NULL
		head = new MenuElement(nullptr, optionHeader, nullptr);

		// Tworz� nowy "ogon" listy, czyli wska�nik na pierwsze wolne miejsce na ko�cu listy.
		// Lewy wska�nik pokazuje p�ki co na "g�ow�", poniewa� jest tylko jeden element w li�cie,
		// p�niej b�dzie pokazywa� zawsze na ostatni element listy. Prawy wsk na NULL.
		tail = new MenuElement(head,"", nullptr);

		// Teraz przypisuj� do prawego wsk "g�owy" (czyli teraz ostatniego elementu tablicy) adres "ogona".
		head->next = tail;

		menu_size++;
	}
	else {
		// Do "ogona" listy przypisuj� warto�� nowego elementu.
		tail->name = optionHeader;
		// Do prawego wska�nika przypisuj� adres nowego elementu, kt�ry b�dzie teraz ogonem.
		tail->next = new MenuElement(tail, "", nullptr);
		// Do wska�nika na ogon listy przypisuj� adres elementu utworzonego lini� wy�ej.
		tail = tail->next;

		menu_size++;
	}

}

std::string Menu::get(int index)
{
	MenuElement* element = search(index);
	if (element == nullptr)
		throw IndexOutOfBoundsException();
	else
		return element->name;
}

std::ostream & operator<<(std::ostream & output, Menu & menu)
{
	for (int i = 0;i < menu.menu_size;i++) 
		output << menu.get(i) << std::endl;
	return output;
}
