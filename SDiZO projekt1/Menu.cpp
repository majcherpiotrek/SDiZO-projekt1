#include "Menu.h"



MenuElement * Menu::search(int index)
{
	//Jeœli index wykracza poza listê to zwraca wskaŸnik NULL.
	if (index < 0 || index >= menu_size)
		return nullptr;

	MenuElement* element;
	/*Jeœli szukany indeks w pierwszej po³owie listy
	to zaczynamy szukanie od wskaŸnika na g³owê listy.*/
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
		// Tworzê now¹ "g³owê" listy o wartoœci _value, oba wskaŸniki ustawione na NULL
		head = new MenuElement(nullptr, optionHeader, nullptr);

		// Tworzê nowy "ogon" listy, czyli wskaŸnik na pierwsze wolne miejsce na koñcu listy.
		// Lewy wskaŸnik pokazuje póki co na "g³owê", poniewa¿ jest tylko jeden element w liœcie,
		// póŸniej bêdzie pokazywa³ zawsze na ostatni element listy. Prawy wsk na NULL.
		tail = new MenuElement(head,"", nullptr);

		// Teraz przypisujê do prawego wsk "g³owy" (czyli teraz ostatniego elementu tablicy) adres "ogona".
		head->next = tail;

		menu_size++;
	}
	else {
		// Do "ogona" listy przypisujê wartoœæ nowego elementu.
		tail->name = optionHeader;
		// Do prawego wskaŸnika przypisujê adres nowego elementu, który bêdzie teraz ogonem.
		tail->next = new MenuElement(tail, "", nullptr);
		// Do wskaŸnika na ogon listy przypisujê adres elementu utworzonego liniê wy¿ej.
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
