#pragma once
#include <iostream>
/*Klasa wyj¹tku.
Wyj¹tek ten jest wyrzucany, jeœli nie zostanie odnaleziony plik, z którego mia³y byæ odczytane dane do struktury.*/
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

