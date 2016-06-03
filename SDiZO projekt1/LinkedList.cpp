#include "LinkedList.h"

/*Konstruktor listy. Przypisuje adresy NULL wska�nikowm na g�ow� i ogon listy oraz rozmiar = 0.*/
LinkedList::LinkedList()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}
/*Destruktor listy. Usuwa po kolei wszystkie elementy zaczynaj�c od g�owy.*/
LinkedList::~LinkedList()
{
	while (head != tail) {
		head = head->rightPointer;
		delete head->leftPointer;
	}
	
	delete tail;
}
/*Prywatna funkcja listy, szuka elementu o zadanym indeksie i zwraca wska�nik na niego,
je�li taki indeks jest na li�cie, w przeciwnym razie wska�nik NULL.*/
Node* LinkedList::search(int index)
{
	//Je�li index wykracza poza list� to zwraca wska�nik NULL.
	if (index < 0 || index >= size)
		return nullptr;

	Node* node;
	/*Je�li szukany indeks w pierwszej po�owie listy
	to zaczynamy szukanie od wska�nika na g�ow� listy.*/
	if (index <= size / 2) {

		node = head;
		for (int i = 0; i != index; i++)
			node = node->rightPointer;

	}
	/*W przeciwnym wypadku zaczynamy szukanie od ostatniego elementu listy.*/
	else {
		node = tail->leftPointer;
		for (int i = size - 1; i != index; i--)
			node = node->leftPointer;
	}

	return node;
}
/*Funkcja wczytujaca dane do listy z pliku.*/
void LinkedList::readFile(std::string  file_name)
{
	/* Sprawdzam, czy w nazwie pliku brakuje rozszerzenia ".txt", je�li tak to je dodaj�.*/
	if (file_name[file_name.length() - 1] != *"t" ||
		file_name[file_name.length() - 2] != *"x" ||
		file_name[file_name.length() - 3] != *"t" ||
		file_name[file_name.length() - 4] != *".")
		file_name.append(".txt");

	/* Tworz� strumie� do odczytu danych z pliku.
	Otwieram go w trybie "std::ios::in", czyli do odczytu.*/
	std::fstream input;
	input.open(file_name, std::ios::in);

	/* Sprawdzam, czy powiod�o si� otwarcie pliku.*/
	if (!input.good())
		throw FileNotFoundException();

	/* Tworz� zmienn� do przechowania wej�ciowego �a�cucha znak�w
	i pobieram do niej jeden wiersz z pliku.*/
	std::string input_line;
	getline(input, input_line);

	/* Sprawdzenie poprawno�ci formatu danych.
	(Format: [1,2,3,...,43,23,11])-> Wa�ne aby by� nawiaz kwadratowy
	i liczby porozdzielane przecinkami bez spacji.

	Wyszukuj� pierwsze wyst�pienie "["*/
	std::string::size_type begin = input_line.find("[", 0);
	/* Je�li nie znaleziono "[" to wyrzucam wyj�tek.*/
	if (begin == std::string::npos)
		throw DataTypeMismatchException();
	/* Wyszukuj� pierwsze wyst�pienie "]" po "[".*/
	std::string::size_type end = input_line.find("]", begin);
	/* Je�li nie znaleziono "]" po "[" to wyrzucam wyj�tek.*/
	if (end == std::string::npos)
		throw DataTypeMismatchException();

	/* P�tla wczytuj�ca dane z pliku do struktury.
	begin - pozycja "["
	end - pozycja "]"*/
	for (int i = begin + 1; i != end;) {

		/* �a�cuch znak�w s�u��cy za bufor do wczytywania liczb.*/
		std::string number = "";

		int j = 0;
		/* P�tla wczytuj�ca poszczeg�lne liczby. Obraca si�, a� nie natrafi na przecinek lub koniec wej�cia ("]").*/
		while (i + j != end && input_line[i + j] != *",") {
			number += input_line[i + j];
			j++;
		}
		if (input_line[i + j] == *"]")
			i = i + j;
		else
			i = i + j + 1;

		/* Tworz� obiekt istringstream s�u��cy do przetworzenia �a�cucha znak�w na liczb�.*/
		std::istringstream iss(number);
		iss >> j;
		/* Dodaj� liczb� do struktury*/
		this->push_back(j);

		number.clear();
		number = "";
	}
}
/*Funkcja zapisujaca liste do pliku.*/
void LinkedList::saveToFile(std::string  file_name)
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
/*Funkcja wstawiaj�ca nowy element o warto�ci _value na pocz�tek listy.*/
void LinkedList::push_front(int _value)
{
	if (size == 0) {
	 // Tworz� now� "g�ow�" listy o warto�ci _value, oba wska�niki ustawione na NULL
		head = new Node(nullptr, _value, nullptr); 
	
	 // Tworz� nowy "ogon" listy, czyli wska�nik na pierwsze wolne miejsce na ko�cu listy.
	 // Lewy wska�nik pokazuje p�ki co na "g�ow�", poniewa� jest tylko jeden element w li�cie,
	 // p�niej b�dzie pokazywa� zawsze na ostatni element listy. Prawy wsk na NULL.
		tail = new Node(head,0 , nullptr); 

	 // Teraz przypisuj� do prawego wsk "g�owy" (czyli teraz ostatniego elementu tablicy) adres "ogona".
		head->rightPointer = tail;
		
		size++;
	}
	else{
	 // Tworz� nowy element listy o warto�ci _value, lewym wsk na NULL 
	 // oraz prawym wsk pokazuj�cym na aktualny adres "g�owy". 
		head->leftPointer = new Node(nullptr, _value, head);

	 // Przypisuj� pod wsk "g�owy" listy adres dodanego elementu, kt�ry jest teraz pierwszy na li�cie.
		head = head->leftPointer;
		
		size++;
	}
	
}
/*Funkcja wstawiaj�ca nowy element o warto�ci _value na koniec listy.*/
void LinkedList::push_back(int _value) {
    // Sprawdzam, czy lista nie jest pusta.
	if (size == 0)
	 // Je�li jest pusta to u�ywam funkcji push_front
		push_front(_value);
	else {
	 // Do "ogona" listy przypisuj� warto�� nowego elementu.
		tail->value = _value;
	 // Do prawego wska�nika przypisuj� adres nowego elementu, kt�ry b�dzie teraz ogonem.
		tail->rightPointer = new Node(tail, 0, nullptr);
	 // Do wska�nika na ogon listy przypisuj� adres elementu utworzonego lini� wy�ej.
		tail = tail->rightPointer;
		
		size++;
	}
}
/*Funkcja usuwaj�ca element z pocz�tku listy. Je�li lista jest pusta
to funkcja nie robi nic.*/
void LinkedList::pop_front()
{
	if (size == 0)
		return;
	if (size == 1) {
		delete head;
		delete tail;
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	else {
		head = head->rightPointer;
		delete head->leftPointer;
		head->leftPointer = nullptr;
		size--;
	}
}
/*Funkcja usuwaj�ca element z ko�ca listy. Je�li lista
zawiera jeden element lub jest pusta to wywo�uje pop_front().*/
void LinkedList::pop_back()
{
	if (size == 1 || size == 0)
		pop_front();
	else {
		tail = tail->leftPointer;
		delete tail->rightPointer;
		size--;
	}
}
/*Funkcja wstawiaj�ca element o warto�ci _value na miejsce index na li�cie.
Element, kt�ry sta� wcze�niej na tej pozycji, po wstawieniu nowego b�dzie 
na pozycji o jeden dalszej. Funkcja wyrzuca wyj�tek "OutOfBoundException"
przy otrzymaniu indexu wykraczaj�cego poza list�.*/
void LinkedList::put(int index, int _value)
{
	Node* node = search(index);
	if (node == nullptr)
		throw "IndexOutOfBoundsException";

	Node* newNode = new Node(node->leftPointer, _value, node);
	(newNode->leftPointer)->rightPointer = newNode;
	node->leftPointer = newNode;

	size++;
}
/*Funkcja zwracaj�ca warto�� elementu listy o zadanym indeksie.
Wyrzuca wyj�tek "OutOfBoundException" przy otrzymaniu indexu 
wykraczaj�cego poza list�. */
int LinkedList::get(int index){
	Node* node = search(index);
	if (node == nullptr)
		throw IndexOutOfBoundsException();
	else
		return node->value;
}
/*Funkcja szukajaca zadanej wartosci w liscie. Zwraca indeks elementu lub -1, 
jesli wartosc nie zostanie znaleziona.*/
int LinkedList::searchValue(int _value){

	Node* node_back = tail->leftPointer;
	Node* node_front = head;
	for (int i = 0; i <= size / 2;i++) {

		if (node_front->value == _value)
			return i;
		if (node_back->value == _value) 
			return size-1-i;

			node_front = node_front->rightPointer;
			node_back = node_back->leftPointer;
		}
		return -1;
	
}
/*Funckcja usuwajaca element o zadanym indeksie.*/
void LinkedList::removeIndex(int index)
{
	Node* toRemove = search(index);
	delete toRemove;
	size--;
}
/*Funkcja zwracaj�ca aktualny rozmiar listy.*/
int LinkedList::getSize()
{
	return size;
}
/*Funckcja podmieniajaca ewartosc elementu pod zadanym indeksem.*/
void LinkedList::replace(int index, int _value)
{
	Node* toReplace = search(index);
	toReplace->value = _value;
}
/*Przeladowany operator "<<" umozliwiajacy wypisanie listy na podany strumien wyjsciowy.*/
std::ostream & operator<<(std::ostream & output, LinkedList & lista)
{
	output << "Lista dwukierunkowa: [";
	for (int i = 0;i < lista.getSize();i++) {
		output << lista.get(i);
		if (i == lista.getSize() - 1)
			output << "]\n";
		else
			output << ",";
	}
	
	return output;
}
