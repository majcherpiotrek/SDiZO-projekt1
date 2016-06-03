#pragma once
#include<iostream>
/*Klasa wyj¹tku.
Wyj¹tek ten jest wyrzucany, jeœli szukany indeks jest poza rozmiarem struktury.*/
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

