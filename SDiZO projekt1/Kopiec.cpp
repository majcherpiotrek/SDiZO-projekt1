#include "Kopiec.h"

/*Prywatna funkcja szukajaca elementu o zadanej wartosci od zadanego indeksu w dol.*/
int Kopiec::search(int index, int value)
{
	if (index >= this->size || index < 0)
		return -1;
	if (root->get(index) == value)
		return index;
	int childL = 2 * index + 1;
	int childR = childL + 1;
	int x = -1;
	x = search(childL, value);
	if (x == -1)
		x = search(childR, value);
	return x;
}
/*Funkcja rysujaca graficzna reprezentacje kopca w sposob rekurencyjny.(Prywatna)*/
void Kopiec::drawREK(std::ostream & output, int index)
{
	int child = 2 * index + 2;
	/*Jesli istnieje prawy syn, to wywolujemy rekurencyjnie funkcje dla niego.*/
	if (child < size)
		drawREK(output, child);
	
	/*poziom, na którym znajduje siê element (poziom korzenia to 0)*/
	int element_level = (int)log2(index);
	
	/*sprawdzam, czy nie jest to element maksymalnie lewy z danego poziomu 
	(wtedy z logarytmu wyjdzie poziom o jeden ni¿szy)*/
	if (index == (int)exp2(element_level + 1) - 1)
		element_level++;
	
	
	/*Pêtla rysuj¹ca dany wiersz. Na ka¿dy poziom rysuje 3 spacje.*/
	for (int i = 0; i < element_level*3;i++)
	{
		/*Jeœli jesteœmy na ostatnim miejscu przed elementem do narysowania*/
		if (i == element_level*3 - 1)
		{   
			/*Jeœli ten element to prawy syn*/
			if (index % 2 == 0)
				output << "/";
			else
				/*Jesli ten element to lewy syn*/
				output << "\\";
		}else
			/*Na wczesniejszych pozycjach*/
			output << " ";
		
			
	}
	/*wypisujemy wartosc elementu.*/
	output << root->get(index)<<std::endl;
	
	
	child = 2 * index + 1;
	/*Jesli istenieje lewy syn, to wywolujemy rekurencyjnie funkcje dla niego.*/
	if (child < size)
		drawREK(output, child);
	
}
/*Konstruktor kopca. Tworzy now¹ pust¹ tablicê i przypisuje pod korzen.*/
Kopiec::Kopiec()
{
	root = new Tablica();
	size = 0;
}
/*Destruktor kopca. Zwalnia miejce po tablicy zapisanej w korzeniu.*/
Kopiec::~Kopiec()
{
	delete root;
}
/*Funkcja odczytuj¹ca dane do kopca z pliku.*/
void Kopiec::readFile(std::string  file_name)
{
	/* Sprawdzam, czy w nazwie pliku brakuje rozszerzenia ".txt", jeœli tak to je dodajê.*/
	if (file_name[file_name.length() - 1] != *"t" ||
		file_name[file_name.length() - 2] != *"x" ||
		file_name[file_name.length() - 3] != *"t" ||
		file_name[file_name.length() - 4] != *".")
		file_name.append(".txt");

	/* Tworzê strumieñ do odczytu danych z pliku.
	Otwieram go w trybie "std::ios::in", czyli do odczytu.*/
	std::fstream input;
	input.open(file_name, std::ios::in);

	/* Sprawdzam, czy powiod³o siê otwarcie pliku.*/
	if (!input.good())
		throw FileNotFoundException();

	/* Tworzê zmienn¹ do przechowania wejœciowego ³añcucha znaków
	i pobieram do niej jeden wiersz z pliku.*/
	std::string input_line;
	getline(input, input_line);

	/* Sprawdzenie poprawnoœci formatu danych.
	(Format: [1,2,3,...,43,23,11])-> Wa¿ne aby by³ nawiaz kwadratowy
	i liczby porozdzielane przecinkami bez spacji.

	Wyszukujê pierwsze wyst¹pienie "["*/
	std::string::size_type begin = input_line.find("[", 0);
	/* Jeœli nie znaleziono "[" to wyrzucam wyj¹tek.*/
	if (begin == std::string::npos)
		throw DataTypeMismatchException();
	/* Wyszukujê pierwsze wyst¹pienie "]" po "[".*/
	std::string::size_type end = input_line.find("]", begin);
	/* Jeœli nie znaleziono "]" po "[" to wyrzucam wyj¹tek.*/
	if (end == std::string::npos)
		throw DataTypeMismatchException();

	/* Pêtla wczytuj¹ca dane z pliku do struktury.
	begin - pozycja "["
	end - pozycja "]"*/
	for (int i = begin + 1; i != end;) {

		/* £añcuch znaków s³u¿¹cy za bufor do wczytywania liczb.*/
		std::string number = "";

		int j = 0;
		/* Pêtla wczytuj¹ca poszczególne liczby. Obraca siê, a¿ nie natrafi na przecinek lub koniec wejœcia ("]").*/
		while (i + j != end && input_line[i + j] != *",") {
			number += input_line[i + j];
			j++;
		}
		if (input_line[i + j] == *"]")
			i = i + j;
		else
			i = i + j + 1;

		/* Tworzê obiekt istringstream s³u¿¹cy do przetworzenia ³añcucha znaków na liczbê.*/
		std::istringstream iss(number);
		iss >> j;
		/* Dodajê liczbê do struktury*/
		this->push(j);

		number.clear();
		number = "";
	}
}
/*Funkcja zapisuj¹ca kopiec do pliku w postaci tablicowej oraz graficznej.*/
void Kopiec::saveToFile(std::string  file_name)
{
	if (file_name[file_name.length() - 1] != *"t" ||
		file_name[file_name.length() - 2] != *"x" ||
		file_name[file_name.length() - 3] != *"t" ||
		file_name[file_name.length() - 4] != *".")
		file_name.append(".txt");
	std::fstream output;
	output.open(file_name, std::ios::out | std::ios::app);
	this->draw(output);
	output.close();
}
/*Funkcja dodaj¹ca element do kopca*/
void Kopiec::push(int value)
{
	
	if (size == 0) {
		root->push_front(value);
		size++;
		return;
	}
	size++;
	root->push_back(value);
	//naprawa kopca
	heap_fix_up(root,size);
	

}
/*Funkcja usuwajaca element z korzenia.*/
void Kopiec::pop() {
	//jeœli kopiec pusty to koniec
	if (size == 0)
		return;
	//wstawienie ostatniego liœcia na miejsce korzenia
	
	root->replace(0, root->get(size - 1));
	//usuniêcie ostatniego liœcia
	root->removeIndex(size - 1);
	size--;
	heap_fix_down(root,0,size);
	
}
/*Funkcja naprawiajaca kopiec w gore*/
void Kopiec::heap_fix_up(Tablica* tab, int len)
{
	int i = len - 1;
	//znalezienie rodzica
	int rodzic = (i - 1) / 2;
	while (tab->get(rodzic) < tab->get(i)) {
		int bufor = tab->get(rodzic);
		//zamiana miejscami rodzica z nowym elementem
		tab->replace(rodzic, tab->get(i));
		tab->replace(i, bufor);
		//przypisanie nowego indeksu nowego elementu
		i = rodzic;
		//znalezienie rodzica dla nowego indeksu
		rodzic = (i - 1) / 2;
	}
}
/*Funkcja naprawiajaca kopiec w dol*/
void Kopiec::heap_fix_down(Tablica* tab, int i, int len)
{
	
	int j = 2 * i + 1; //indeks syna (teraz lewego)
	while (j < len) {

		//szukam wiêkszego syna
		if (j + 1 < len && tab->get(j) < tab->get(j + 1))
			j = j + 1;

		if (tab->get(i) >= tab->get(j))
			break;

		int buf = tab->get(i);
		tab->replace(i, tab->get(j));
		tab->replace(j, buf);
		i = j;
		j = 2 * i + 1;
	}
}
/*Funkcja szukajaca zadanej wartosci w kopcu. Zwraca indeks tablicowy elementu lub -1,
jesli wartosc nie zostanie znaleziona.*/
int Kopiec::searchValue(int value)
{
	return search(0,value);
}
/*Funkcja zwracajaca element z zadanego indeksu tablicowego kopca (Prywatna)*/
int Kopiec::get(int index)
{
	return root->get(index);
}
/*Funkcja rysujaca tablicowa i graficzna reprezentacja kopca na zadany strumien wyjsciowy*/
void Kopiec::draw(std::ostream & output)
{
	output << *this << std::endl;
	drawREK(output, 0);
}
/*Przeladowany operator "<<" sluzacy do wypisywania reprezentacji tablicowej kopca na ekran*/
std::ostream & operator<<(std::ostream & output, Kopiec & kopiec)
{
	output << "Kopiec: " << *(kopiec.root);
	return output;
}
