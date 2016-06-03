#include "Tablica.h"

/*Konstruktor argumentowy tablicy.
	tab - wskaznik na poczatek tablicy
	len - rozmiar tablicy*/
Tablica::Tablica(int * tab, int len)
{
	head = tab;
	size = len;
}
/*Konstruktor bezargumentowy tablicy. Przypisuje poczatkowi tablicy nullptr*/
Tablica::Tablica()
{
	size = 0;
	head = nullptr;
}
/*Destruktor tablicy. Zwalnia pamiêæ spod wskaznika na poczatek tablicy*/
Tablica::~Tablica()
{
	delete[] head;
}
/*Funkcja wczytujaca dane do tablicy z pliku.*/
void Tablica::readFile(std::string  file_name)
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
	bool koniec = false;
	std::string input_line;
	bool opened = false;
	while (!koniec && !input.eof()) {
		getline(input, input_line);
		std::string::size_type begin;
		/*Wyszukujê otwarcia danych: "["*/
		if (!opened)
		{
			begin = input_line.find("[", 0);
			if (begin == std::string::npos)
				throw DataTypeMismatchException();
			opened = true;
		}
		else {
			begin = 0;
		}

		/*Sprawdzam, czy w tej linii jest zamkniêcie*/
		std::string::size_type end = input_line.find("]", begin);
		if (!(end == std::string::npos))
			koniec = true;
		else
			end = input_line.length() - 1;
		if (input_line[begin] == *"[")
			begin++;
		for (int i = begin; i != end;) {

			std::string number = "";
			int j = 0;
			/* Pêtla wczytuj¹ca poszczególne liczby. Obraca siê, a¿ nie natrafi na przecinek lub koniec wejœcia ("]").*/
			while (i + j != end && input_line[i + j] != *"," && input_line[i + j] != ' ') {
				number += input_line[i + j];
				j++;
				
			}

			

			if (input_line[i + j] == *",")
				i = i + j + 1;
			else {
				if (i + j == end)
					i = i + j;
			}
			if(number!=""){
				int num;
				std::istringstream iss(number);
				iss >> num;
				/* Dodajê liczbê do struktury*/
				this->push_back(num);
			}
			
		}



	}

}
/*Funkcja zapisujaca tablice do pliku.*/
void Tablica::saveToFile(std::string  file_name)
{
	if (file_name[file_name.length() - 1] != *"t" ||
		file_name[file_name.length() - 2] != *"x" ||
		file_name[file_name.length() - 3] != *"t" ||
		file_name[file_name.length() - 4] != *".")
		file_name.append(".txt");
	std::fstream output;
	output.open(file_name, std::ios::out | std::ios::app);
	output << *this;
	output.close();
}
/*Funckcja podmieniajaca ewartosc elementu pod zadanym indeksem.*/
void Tablica::replace(int index, int value)
{
	if (size == 0) {
		head = new int[1]; size++;
	}
	if (index < 0 || index >= size)
		throw IndexOutOfBoundsException();
	
	*(head + index) = value;
}
/*Funkcja wstawiaj¹ca nowy element o wartoœci _value na pocz¹tek listy.*/
void Tablica::push_front(int value)
{
	if (size == 0) {
		head = new int[1]; 
		*head = value;
		size++; 
	}
	else{
		int* wsk = new int[size + 1];
		memcpy(wsk + 1, head, size*sizeof(int));
		*wsk = value;
		head = wsk;
		size++;
	}
		
}
/*Funkcja usuwajaca element z konca tablicy.*/
void Tablica::pop_back()
{
	removeIndex(this->size - 1);
}
/*Funkcja usuwajaca element z poczatku tablicy.*/
void Tablica::pop_front()
{
	removeIndex(0);
}
/*Funkcja wstawiaj¹ca element o wartoœci _value na miejsce index w tablicy.
Element, który sta³ wczeœniej na tej pozycji, po wstawieniu nowego bêdzie
na pozycji o jeden dalszej. Funkcja wyrzuca wyj¹tek "OutOfBoundException"
przy otrzymaniu indexu wykraczaj¹cego poza tablice.*/
void Tablica::put(int index, int value)
{
	if (size == 0)
		return;
	if (index < 0 || index > size)
		throw IndexOutOfBoundsException();

	int* wsk = new int[size + 1]; //tablic buforowa, do w³o¿enia nowego elementu
	memcpy(wsk, head, index*sizeof(int));//przekopiowujê ze starej tablicy elementy z pocz¹tku, zostawiaj¹c na koñcu miejsce na nowy element
	*(wsk + index) = value;
	memcpy(wsk + index + 1, head + index, (size - index)*sizeof(int));
	head = wsk;
	size++;
}
/*Funkcja szukajaca zadanej wartosci w tablicy. Zwraca indeks elementu lub -1,
jesli wartosc nie zostanie znaleziona.*/
int Tablica::searchValue(int value)
{
	for (int i = 0; i < size; i++) {
		if (*(head + i) == value)
			return i;
	}
	return -1;
}
/*Funkcja wstawiaj¹ca nowy element o wartoœci _value na koniec tablicy.*/
void Tablica::push_back(int value)
{
	if (size == 0) { 
		head = new int[1]; 
		*head = value;
		size++; 
	}
	else{
		int* wsk = new int[size + 1];
		memcpy(wsk, head, size*sizeof(int));
		*(wsk + size) = value;
		head = wsk;
		size++;
	}
		
	
}
/*Funckcja usuwajaca element o zadanym indeksie.*/
void Tablica::removeIndex(int index)
{
	if (size == 0)
		return;
	if (index < 0 || index >= size)
		throw IndexOutOfBoundsException();
	
	int* wsk = new int[size - 1];
	memcpy(wsk, head, index*sizeof(int));
	size--;
	memcpy(wsk + index, head+index+1, (size - index)*sizeof(int));
	head = wsk;
	
	
}
/*Funkcja usuwajaca pierwszy znaleziony element o wartosci value. Zwraca true jesli usuwanie sie powiedzie,
false w przeciwnym wypadku.*/
bool Tablica::removeValue(int value)
{
	int index = searchValue(value);
	if (index == -1) {
		std::cout << "\nremoveValue(" << value << ") not possible,\nbecause the value is not in the table.\n";
		return false;
	}
		
	
	try{removeIndex(index);}
	catch (IndexOutOfBoundsException ex) {
		std::cout << ex;
		return false;}
	
	return true;
}
/*Funkcja zwracaj¹ca wartoœæ elementu tablicy o zadanym indeksie.
Wyrzuca wyj¹tek "OutOfBoundException" przy otrzymaniu indexu
wykraczaj¹cego poza tablice. */
int Tablica::get(int index)
{
	if (index < 0 || index >= size)
		throw IndexOutOfBoundsException();
	return *(head + index);
}
/*Przeladowany operator "<<" umozliwiajacy wypisanie tablicy na podany strumien wyjsciowy.*/
std::ostream & operator<<(std::ostream& output, Tablica& tab)
{
	output << "Tablica: [";
	for (int i = 0; i < tab.getSize(); i++) {
		output << tab.get(i);
		if (i == tab.getSize() - 1)
			output << "]\n";
		else
			output << ",";
	}
	return output;
}
