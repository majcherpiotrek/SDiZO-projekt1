#pragma once
#include <iostream>
/*Klasa wyj�tku.
Wyj�tek ten jest wyrzucany w programie przy b��dnym formacie danych wprowadzanych z pliku.*/
class DataTypeMismatchException
{
public:
	DataTypeMismatchException();
	~DataTypeMismatchException();
	friend std::ostream& operator << (std::ostream& output, DataTypeMismatchException ex) {
		output << "\nDataTypeMismatchException\n";
		return output;
	}
};

