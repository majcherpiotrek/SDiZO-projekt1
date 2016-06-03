#include "LinkedList.h"
#include "Tablica.h"
#include "Kopiec.h"
#include "RandomInputGenerator.h"
#include "Menu.h"
#include <iostream>

void switchTab(Menu& menu) {

	Tablica tab = *(new Tablica());
	bool bad_command = false;
	bool end = false;
	char c;
	std::cout << menu;

	while (!end) {

		
		if (bad_command)
		{
			std::cout << "\nBledny numer opcji! Twoj wybor-> ";
			bad_command = false;
		}
		else
			std::cout << "\nTwoj wybor -> ";

		std::cin.ignore(INT_MAX, '\n');
		//std::cin.clear();
		//std::cin.sync();
		std::cin >> c;

		switch (c) {
		case 'b': { // Powrót do menu glownego
			end = true;
			break;
		}
		case 'r': {//odswiez ekran
			system("cls");
			std::cout << menu;
			break;
		}
		case 'w': { // odczyt danych z pliku
			
			std::cout << "\nPodaj nazwe pliku z danymi ( w sciezce dostepu zamien \ na \\ ): ";
			std::string nazwa;
			std::cin >> nazwa;
			try {
				tab.readFile(nazwa);
			}
			catch (FileNotFoundException ex) {
				std::cout << "\nBLAD - Nie znaleziono takiego pliku!\n";
				break;
			}
			std::cout << "\nPlik odczytany poprawnie\n";
			break;
		}
		case 'z': { //saveToFile(string file_name)
			std::cout << "\nPodaj nazwe pliku do zapisu( w sciezce dostepu zamien \ na \\ ): ";
			std::string nazwa;
			std::cin >> nazwa;
			tab.saveToFile(nazwa);
			std::cout << "\nChyba udalo sie zapisac, ale kto wie...\n";
			break;
		}
		case '0': { //push_front(int value)
			std::cout << "\nPodaj liczbe jaka chcesz dodac: ";
			int v;
			std::cin >> v;
			tab.push_front(v);
			std::cout << "\nDodano " << v << " na poczatek tablic!\n";
			break;
		}
		case '1': { //push_back(int value)
			std::cout << "\nPodaj liczbe jaka chcesz dodac: ";
			int v;
			std::cin >> v;
			tab.push_back(v);
			std::cout << "\nDodano " << v << " na koniec tablicy!\n";
			break;
		}
		case '2': {//put(int index,int value)
			std::cout << "\nPodaj liczbe jaka chcesz dodac: ";
			int v;
			std::cin >> v;
			std::cout << "\Podaj indeks, pod ktory liczba ma byc dodana: ";
			int i;
			std::cin >> i;
			try { 
				tab.put(i, v); 
			}
			catch (IndexOutOfBoundsException ex) {
				std::cout << "\nBLAD - Indeks poza zakresem!\n";
				break;
			}
			std::cout << "\nDodano " << v << " pod indeks "<<i<<" tablicy!\n";
			break;
		}
		case '3': { //pop_front();
			tab.pop_front();
			std::cout << "\nUsunieto element z poczatku tablicy.";
			break;
		}
		case '4': { //pop_back();
			tab.pop_back();
			std::cout << "\nUsunieto element z konca tablicy.";
			break;
		}
		case '5': { //removeIndex(int index)
			std::cout << "\Podaj indeks elementu do usuniecia: ";
			int i;
			std::cin >> i;
			try {
				tab.removeIndex(i);
			}
			catch (IndexOutOfBoundsException ex) {
				std::cout << "\nBLAD - Indeks poza zakresem!\n";
				break;
			}
			std::cout << "\nUsunieto element spod indeksu"<< i << " tablicy!\n";
			break;
		}
		case '6': {//searchValue(int value)
			std::cout << "\nPodaj wartosc do wyszukania: ";
			int v;
			std::cin >> v;
			int i = tab.searchValue(v);
			if (i == -1)
				std::cout << "\nNie znaleziono takiej wartosci!\n";
			else
				std::cout << "Wartosc " << v << " znajduje sie pod indeksem " << i << " .\n";
			break;
		}
		case '7': {//get(int index)
			std::cout << "\nPodeaj indeks elementu, ktory chcesz zobaczyc: ";
			int i;
			std::cin >> i;
			int v;
			try {
				v = tab.get(i);
			}
			catch (IndexOutOfBoundsException ex) {
				std::cout << "\nBLAD - Indeks poza zakresem!\n";
				break;
			}
			std::cout << "\nWartosc pod indeksem " << i << " to " << v << " .\n";
			break;
		}
		
		case 'd': { //wypisz tablice na ekran
			std::cout << std::endl;
			std::cout << tab;
			break;
		}

		default: {
			bad_command = true;
		}
		}
	}
}
void switchList(Menu& menu) {

	LinkedList list = *(new LinkedList());
	bool bad_command = false;
	bool end = false;
	char c;
	std::cout << menu;

	while (!end) {


		if (bad_command)
		{
			std::cout << "\nBledny numer opcji! Twoj wybor-> ";
			bad_command = false;
		}
		else
			std::cout << "\nTwoj wybor -> ";

		std::cin.ignore(INT_MAX, '\n');
		//std::cin.clear();
		//std::cin.sync();
		std::cin >> c;

		switch (c) {
		case 'b': { // Powrót do menu glownego
			end = true;
			break;
		}
		case 'r': {//odswiez ekran
			system("cls");
			std::cout << menu;
			break;
		}
		case 'w': { // odczyt danych z pliku

			std::cout << "\nPodaj nazwe pliku z danymi ( w sciezce dostepu zamien \ na \\ ): ";
			std::string nazwa;
			std::cin >> nazwa;
			try {
				list.readFile(nazwa);
			}
			catch (FileNotFoundException ex) {
				std::cout << "\nBLAD - Nie znaleziono takiego pliku!\n";
				break;
			}
			std::cout << "\nPlik odczytany poprawnie\n";
			break;
		}
		case 'z': { //saveToFile(string file_name)
			std::cout << "\nPodaj nazwe pliku do zapisu( w sciezce dostepu zamien \ na \\ ): ";
			std::string nazwa;
			std::cin >> nazwa;
			list.saveToFile(nazwa);
			std::cout << "\nChyba udalo sie zapisac, ale kto wie...\n";
			break;
		}
		case '0': { //push_front(int value)
			std::cout << "\nPodaj liczbe jaka chcesz dodac: ";
			int v;
			std::cin >> v;
			list.push_front(v);
			std::cout << "\nDodano " << v << " na poczatek listy!\n";
			break;
		}
		case '1': { //push_back(int value)
			std::cout << "\nPodaj liczbe jaka chcesz dodac: ";
			int v;
			std::cin >> v;
			list.push_back(v);
			std::cout << "\nDodano " << v << " na koniec listy!\n";
			break;
		}
		case '2': {//put(int index,int value)
			std::cout << "\nPodaj liczbe jaka chcesz dodac: ";
			int v;
			std::cin >> v;
			std::cout << "\Podaj indeks, pod ktory liczba ma byc dodana: ";
			int i;
			std::cin >> i;
			try {
				list.put(i, v);
			}
			catch (IndexOutOfBoundsException ex) {
				std::cout << "\nBLAD - Indeks poza zakresem!\n";
				break;
			}
			std::cout << "\nDodano " << v << " pod indeks " << i << " listy!\n";
			break;
		}
		case '3': { //pop_front();
			list.pop_front();
			std::cout << "\nUsunieto element z poczatku listy.";
			break;
		}
		case '4': { //pop_back();
			list.pop_back();
			std::cout << "\nUsunieto element z konca listy.";
			break;
		}
		case '5': { //removeIndex(int index)
			std::cout << "\Podaj indeks elementu do usuniecia: ";
			int i;
			std::cin >> i;
			try {
				list.removeIndex(i);
			}
			catch (IndexOutOfBoundsException ex) {
				std::cout << "\nBLAD - Indeks poza zakresem!\n";
				break;
			}
			std::cout << "\nUsunieto element spod indeksu" << i << " listy!\n";
			break;
		}
		case '6': {//searchValue(int value)
			std::cout << "\nPodaj wartosc do wyszukania: ";
			int v;
			std::cin >> v;
			int i = list.searchValue(v);
			if (i == -1)
				std::cout << "\nNie znaleziono takiej wartosci!\n";
			else
				std::cout << "Wartosc " << v << " znajduje sie pod indeksem " << i << " .\n";
			break;
		}
		case '7': {//get(int index)
			std::cout << "\nPodeaj indeks elementu, ktory chcesz zobaczyc: ";
			int i;
			std::cin >> i;
			int v;
			try {
				v = list.get(i);
			}
			catch (IndexOutOfBoundsException ex) {
				std::cout << "\nBLAD - Indeks poza zakresem!\n";
				break;
			}
			std::cout << "\nWartosc pod indeksem " << i << " to " << v << " .\n";
			break;
		}

		case 'd': { //wypisz liste na ekran
			std::cout << std::endl;
			std::cout << list;
			break;
		}

		default: {
			bad_command = true;
		}
		}
	}
}
void switchKop(Menu& menu) {
	Kopiec kopczyk = *(new Kopiec());
	bool bad_command = false;
	bool end = false;
	char c;
	std::cout << menu;

	while (!end) {


		if (bad_command)
		{
			std::cout << "\nBledny numer opcji! Twoj wybor-> ";
			bad_command = false;
		}
		else
			std::cout << "\nTwoj wybor -> ";

		std::cin.ignore(INT_MAX, '\n');
		//std::cin.clear();
		//std::cin.sync();
		std::cin >> c;

		switch (c) {
		case 'b': { // Powrót do menu glownego
			end = true;
			break;
		}
		case 'r': {//odswiez ekran
			system("cls");
			std::cout << menu;
			break;
		}
		case 'w': { // odczyt danych z pliku

			std::cout << "\nPodaj nazwe pliku z danymi ( w sciezce dostepu zamien \ na \\ ): ";
			std::string nazwa;
			std::cin >> nazwa;
			try {
				kopczyk.readFile(nazwa);
			}
			catch (FileNotFoundException ex) {
				std::cout << "\nBLAD - Nie znaleziono takiego pliku!\n";
				break;
			}
			std::cout << "\nPlik odczytany poprawnie\n";
			break;
		}
		case 'z': { //saveToFile(string file_name)
			std::cout << "\nPodaj nazwe pliku do zapisu( w sciezce dostepu zamien \ na \\ ): ";
			std::string nazwa;
			std::cin >> nazwa;
			kopczyk.saveToFile(nazwa);
			std::cout << "\nChyba udalo sie zapisac, ale kto wie...\n";
			break;
		}
		case '0': { //push(int value)
			std::cout << "\nPodaj liczbe jaka chcesz dodac: ";
			int v;
			std::cin >> v;
			kopczyk.push(v);
			std::cout << "\nDodano " << v << " do kopca!\n";
			break;
		}
	
		case '1': { //pop();
			kopczyk.pop();
			std::cout << "\nUsunieto element z korzenia kopca i naprawiono kopiec.";
			break;
		}
		case '2': {//searchValue(int value)
			std::cout << "\nPodaj wartosc do wyszukania: ";
			int v;
			std::cin >> v;
			int i = kopczyk.searchValue(v);
			if (i == -1)
				std::cout << "\nNie znaleziono takiej wartosci!\n";
			else
				std::cout << "Wartosc " << v << " znajduje sie pod indeksem " << i << " kopca.\n";
			break;
		}
		case 'd': { //wypisz kopiec na ekran
			std::cout << std::endl;
			std::cout<< "\n\nReprezentacja tablicowa i graficzna kopca:\n";
			kopczyk.draw(std::cout);
			break;
		}
		case 't': {
			std::cout << std::endl;
			std::cout << "\n\nReprezentacja tablicowa kopca:\n";
			std::cout << kopczyk;
			break;
		}

		default: {
			bad_command = true;
		}
		}
	}
}

void main() {
	
	
	Menu mainMenu = *(new Menu());
	{mainMenu.add("MENU GLOWNE");
	mainMenu.add("(r) Odswiez widok menu.");
	mainMenu.add("***Wybierz strukture danych:***");
	mainMenu.add("(1) Tablica");
	mainMenu.add("(2) Lista dwukierunkowa");
	mainMenu.add("(3) Kopiec binarny");
	mainMenu.add("(g) Wygeneruj plik z losowymi danymi dla struktur.");
	mainMenu.add("(k) Zakoncz program...");}
	
	Menu menuTab = *(new Menu());
	{menuTab.add("TABLICA");
	menuTab.add("Wybierz opcje:");
	menuTab.add("(b) Powrot do glownego menu.");
	menuTab.add("(r) Odswiez widok menu.");
	menuTab.add("----------------------------------------------");
	menuTab.add("(w) Wczytaj dane z pliku. *");
	menuTab.add("(z) Zapisz tablice do pliku.");
	menuTab.add("----------------------------------------------");
	menuTab.add("(0) Dodaj element na poczatek.");
	menuTab.add("(1) Dodaj element na koniec.");
	menuTab.add("(2) Dodaj element pod zadany indeks.");
	menuTab.add("(3) Usun element z poczatku.");
	menuTab.add("(4) Usun element z konca.");
	menuTab.add("(5) Usun element z zadanego miejsca.");
	menuTab.add("(6) Wyszukaj zadan¹ wartoœæ (zwraca indeks).");
	menuTab.add("(7) Pokaz element o zadanym indeksie.");
	menuTab.add("----------------------------------------------");
	menuTab.add("(d) Wypisz tablice na ekran.");
	menuTab.add("* Format danych do odczytania z pliku: [a,b,c,..,x]\nLiczby zapisane w nawiasie klamrowym, oddzielone przecinkami,\nbez spacji. Tekst przed i za nawiasem nie ma znaczenia.");
	}
	Menu menuList = *(new Menu());
	{menuList.add("LISTA DWUKIERUNKOWA");
	menuList.add("Wybierz opcje:");
	menuList.add("(b) Powrot do glownego menu.");
	menuList.add("(r) Odswiez widok menu.");
	menuList.add("----------------------------------------------");
	menuList.add("(w) Wczytaj dane z pliku. *");
	menuList.add("(z) Zapisz liste do pliku.");
	menuList.add("----------------------------------------------");
	menuList.add("(0) Dodaj element na poczatek.");
	menuList.add("(1) Dodaj element na koniec.");
	menuList.add("(2) Dodaj element pod zadany indeks.");
	menuList.add("(3) Usun element z poczatku.");
	menuList.add("(4) Usun element z konca.");
	menuList.add("(5) Usun element z zadanego miejsca.");
	menuList.add("(6) Wyszukaj zadan¹ wartoœæ (zwraca indeks).");
	menuList.add("(7) Pokaz element pod zadanym indeksie.");
	menuList.add("----------------------------------------------");
	menuList.add("(d) Wypisz liste na ekran.");
	menuList.add("* Format danych do odczytania z pliku: [a,b,c,..,x]\nLiczby zapisane w nawiasie klamrowym, oddzielone przecinkami,\nbez spacji. Tekst przed i za nawiasem nie ma znaczenia.");
	}
	Menu menuKop = *(new Menu());
	{menuKop.add("KOPIEC BINARNY");
	menuKop.add("Wybierz opcje:");
	menuKop.add("(b) Powrot do glownego menu.");
	menuKop.add("(r) Odswiez widok menu.");
	menuKop.add("----------------------------------------------");
	menuKop.add("(w) Wczytaj dane do kopca z pliku. *");
	menuKop.add("(z) Zapisz kopiec do pliku.");
	menuKop.add("----------------------------------------------");
	menuKop.add("(0) Dodaj element do kopca.");
	menuKop.add("(1) Usun element z kopca.");
	menuKop.add("(2) Wyszukaj zadan¹ wartoœæ (zwraca indeks).");
	menuKop.add("(d) Wypisz i narysuj kopiec na ekranie.");
	menuKop.add("(t) Wypisz reprezentacje tablicowa kopca na ekranie.");
	menuKop.add("* Format danych do odczytania z pliku: [a,b,c,..,x]\nLiczby zapisane w nawiasie klamrowym, oddzielone przecinkami,\nbez spacji. Tekst przed i za nawiasem nie ma znaczenia.");
	}
	bool end = false;
	bool bad_command = false;
	std::cout << mainMenu;
	while (!end) {
		
		
		if (bad_command)
		{
			std::cout << "Bledny numer opcji! Twoj wybor-> ";
			bad_command = false;
		}
		else
			std::cout<<"\nTwoj wybor -> ";

		std::cin.clear();
		std::cin.sync();
		
		char decision;
		std::cin >> decision;
		

		switch (decision) {
		case 'r': {
			//odswiez ekran
			system("cls");
			std::cout << mainMenu;
			break;
		}
		case '1': {
			system("cls");
			switchTab(menuTab);
			system("cls");
			std::cout << mainMenu;
			break;
		}
		case '2': {
			system("cls");
			switchList(menuList);
			system("cls");
			std::cout << mainMenu;
			break;
		}
		case '3': {
			system("cls");
			switchKop(menuKop);
			system("cls");
			std::cout << mainMenu;
			break;
		}
		case 'g': {
			RandomInputGenerator gen = *(new RandomInputGenerator());
			std::cout << "\nPodaj ile liczb wygenerowac: ";
			int ile;
			std::cin >> ile;
			std::cout << "\nPodaj zakres losowanych liczb (maksymalna wartosc): ";
			int zakres;
			std::cin >> zakres;
			zakres++;
			gen.generate(ile, zakres);
			std::cout << "\nWygenerowano liczby!\nPodaj nazwe pliku do zapisu( w sciezce dostepu zamien \ na \\ ): ";
			std::string nazwa;
			std::cin >> nazwa;
			gen.saveToFile(nazwa);
			std::cout << "\nChyba udalo sie zapisac, ale kto wie...\n";
			break;
		}
		case 'k': {
			end = true;
			break;
		}
		default: 
			bad_command = true;

		}
	}
	
	return;
}

