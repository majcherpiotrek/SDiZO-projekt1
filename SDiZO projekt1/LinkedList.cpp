#include "LinkedList.h"

/*Konstruktor listy. Przypisuje adresy NULL wskaünikowm na g≥owÍ i ogon listy oraz rozmiar = 0.*/
LinkedList::LinkedList()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}
/*Destruktor listy. Usuwa po kolei wszystkie elementy zaczynajπc od g≥owy.*/
LinkedList::~LinkedList()
{
	while (head != tail) {
		head = head->rightPointer;
		delete head->leftPointer;
	}
	
	delete tail;
}
/*Prywatna funkcja listy, szuka elementu o zadanym indeksie i zwraca wskaünik na niego,
jeúli taki indeks jest na liúcie, w przeciwnym razie wskaünik NULL.*/
Node* LinkedList::search(int index)
{
	//Jeúli index wykracza poza listÍ to zwraca wskaünik NULL.
	if (index < 0 || index >= size)
		return nullptr;

	Node* node;
	/*Jeúli szukany indeks w pierwszej po≥owie listy
	to zaczynamy szukanie od wskaünika na g≥owÍ listy.*/
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
	/* Sprawdzam, czy w nazwie pliku brakuje rozszerzenia ".txt", jeúli tak to je dodajÍ.*/
	if (file_name[file_name.length() - 1] != *"t" ||
		file_name[file_name.length() - 2] != *"x" ||
		file_name[file_name.length() - 3] != *"t" ||
		file_name[file_name.length() - 4] != *".")
		file_name.append(".txt");

	/* TworzÍ strumieÒ do odczytu danych z pliku.
	Otwieram go w trybie "std::ios::in", czyli do odczytu.*/
	std::fstream input;
	input.open(file_name, std::ios::in);

	/* Sprawdzam, czy powiod≥o siÍ otwarcie pliku.*/
	if (!input.good())
		throw FileNotFoundException();

	/* TworzÍ zmiennπ do przechowania wejúciowego ≥aÒcucha znakÛw
	i pobieram do niej jeden wiersz z pliku.*/
	std::string input_line;
	getline(input, input_line);

	/* Sprawdzenie poprawnoúci formatu danych.
	(Format: [1,2,3,...,43,23,11])-> Waøne aby by≥ nawiaz kwadratowy
	i liczby porozdzielane przecinkami bez spacji.

	WyszukujÍ pierwsze wystπpienie "["*/
	std::string::size_type begin = input_line.find("[", 0);
	/* Jeúli nie znaleziono "[" to wyrzucam wyjπtek.*/
	if (begin == std::string::npos)
		throw DataTypeMismatchException();
	/* WyszukujÍ pierwsze wystπpienie "]" po "[".*/
	std::string::size_type end = input_line.find("]", begin);
	/* Jeúli nie znaleziono "]" po "[" to wyrzucam wyjπtek.*/
	if (end == std::string::npos)
		throw DataTypeMismatchException();

	/* PÍtla wczytujπca dane z pliku do struktury.
	begin - pozycja "["
	end - pozycja "]"*/
	for (int i = begin + 1; i != end;) {

		/* £aÒcuch znakÛw s≥uøπcy za bufor do wczytywania liczb.*/
		std::string number = "";

		int j = 0;
		/* PÍtla wczytujπca poszczegÛlne liczby. Obraca siÍ, aø nie natrafi na przecinek lub koniec wejúcia ("]").*/
		while (i + j != end && input_line[i + j] != *",") {
			number += input_line[i + j];
			j++;
		}
		if (input_line[i + j] == *"]")
			i = i + j;
		else
			i = i + j + 1;

		/* TworzÍ obiekt istringstream s≥uøπcy do przetworzenia ≥aÒcucha znakÛw na liczbÍ.*/
		std::istringstream iss(number);
		iss >> j;
		/* DodajÍ liczbÍ do struktury*/
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
/*Funkcja wstawiajπca nowy element o wartoúci _value na poczπtek listy.*/
void LinkedList::push_front(int _value)
{
	if (size == 0) {
	 // TworzÍ nowπ "g≥owÍ" listy o wartoúci _value, oba wskaüniki ustawione na NULL
		head = new Node(nullptr, _value, nullptr); 
	
	 // TworzÍ nowy "ogon" listy, czyli wskaünik na pierwsze wolne miejsce na koÒcu listy.
	 // Lewy wskaünik pokazuje pÛki co na "g≥owÍ", poniewaø jest tylko jeden element w liúcie,
	 // pÛüniej bÍdzie pokazywa≥ zawsze na ostatni element listy. Prawy wsk na NULL.
		tail = new Node(head,0 , nullptr); 

	 // Teraz przypisujÍ do prawego wsk "g≥owy" (czyli teraz ostatniego elementu tablicy) adres "ogona".
		head->rightPointer = tail;
		
		size++;
	}
	else{
	 // TworzÍ nowy element listy o wartoúci _value, lewym wsk na NULL 
	 // oraz prawym wsk pokazujπcym na aktualny adres "g≥owy". 
		head->leftPointer = new Node(nullptr, _value, head);

	 // PrzypisujÍ pod wsk "g≥owy" listy adres dodanego elementu, ktÛry jest teraz pierwszy na liúcie.
		head = head->leftPointer;
		
		size++;
	}
	
}
/*Funkcja wstawiajπca nowy element o wartoúci _value na koniec listy.*/
void LinkedList::push_back(int _value) {
    // Sprawdzam, czy lista nie jest pusta.
	if (size == 0)
	 // Jeúli jest pusta to uøywam funkcji push_front
		push_front(_value);
	else {
	 // Do "ogona" listy przypisujÍ wartoúÊ nowego elementu.
		tail->value = _value;
	 // Do prawego wskaünika przypisujÍ adres nowego elementu, ktÛry bÍdzie teraz ogonem.
		tail->rightPointer = new Node(tail, 0, nullptr);
	 // Do wskaünika na ogon listy przypisujÍ adres elementu utworzonego liniÍ wyøej.
		tail = tail->rightPointer;
		
		size++;
	}
}
/*Funkcja usuwajπca element z poczπtku listy. Jeúli lista jest pusta
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
/*Funkcja usuwajπca element z koÒca listy. Jeúli lista
zawiera jeden element lub jest pusta to wywo≥uje pop_front().*/
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
/*Funkcja wstawiajπca element o wartoúci _value na miejsce index na liúcie.
Element, ktÛry sta≥ wczeúniej na tej pozycji, po wstawieniu nowego bÍdzie 
na pozycji o jeden dalszej. Funkcja wyrzuca wyjπtek "OutOfBoundException"
przy otrzymaniu indexu wykraczajπcego poza listÍ.*/
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
/*Funkcja zwracajπca wartoúÊ elementu listy o zadanym indeksie.
Wyrzuca wyjπtek "OutOfBoundException" przy otrzymaniu indexu 
wykraczajπcego poza listÍ. */
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
/*Funkcja zwracajπca aktualny rozmiar listy.*/
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
