#pragma once
#include <iostream>
/*Klasa wyj�tku.
Wyj�tek ten jest wyrzucany, je�li nie zostanie odnaleziony plik, z kt�rego mia�y by� odczytane dane do struktury.*/
class FileNotFoundException
{
public:
	FileNotFoundException();
	~FileNotFoundException();
	friend std::ostream& operator <<(std::ostream& output, FileNotFoundException ex){
		output << "\nFileNotFoundException\n";
		return output;
	}
	
};

