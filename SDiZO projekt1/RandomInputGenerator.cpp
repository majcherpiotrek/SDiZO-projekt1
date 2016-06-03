#include "RandomInputGenerator.h"
/*Klasa do generowania liczb losowych*/


RandomInputGenerator::RandomInputGenerator()
{
	tab = nullptr;
	size = 0;
}

RandomInputGenerator::~RandomInputGenerator()
{
	delete[] tab;
}
/*Funkcja generuje zadana ilosc liczb losowych z zadanego zakresu.
	length - ilosc liczb do wygenerowania
	range - zakres generowanych liczb*/
void RandomInputGenerator::generate(int length, int range)
{
	tab = new int[length];
	size = length;
	int x;
	srand(time(NULL));
	for (int i = 0; i < size;i++){
		x = rand() % range;
		tab[i] = x;
	}
}
/*Funkcja zapisujaca wygenerowane liczby do pliku w formacie zgodnym
z formatem akceptownym przez struktury.*/
std::string RandomInputGenerator::saveToFile(std::string file_name)
{
	if (file_name[file_name.length() - 1] != *"t" ||
		file_name[file_name.length() - 2] != *"x" ||
		file_name[file_name.length() - 3] != *"t" ||
		file_name[file_name.length() - 4] != *".")
		file_name.append(".txt");
	std::fstream output;
	output.open(file_name, std::ios::out | std::ios::app);
	output << "[";
	for (int i = 0;i < size;i++) {
		output << tab[i];
		if (i == size - 1)
			output << "]";
		else
			output << ",";
	}
	output.close();
	return file_name;
}
/*Funkcja zwracajaca wskaznik na poczatek tablicy z wygenerowanym liczbami.*/
int * RandomInputGenerator::getData()
{
	return this->tab;
}

