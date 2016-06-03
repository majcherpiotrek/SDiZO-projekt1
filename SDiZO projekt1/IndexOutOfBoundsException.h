#pragma once
#include<iostream>
/*Klasa wyj�tku.
Wyj�tek ten jest wyrzucany, je�li szukany indeks jest poza rozmiarem struktury.*/
class IndexOutOfBoundsException
{
public:
	IndexOutOfBoundsException();
	~IndexOutOfBoundsException();
	friend std::ostream& operator<<(std::ostream& output, IndexOutOfBoundsException ex) {
		output << "\nIndexOutOfBoundsException\n";
		return output;
	}
};

