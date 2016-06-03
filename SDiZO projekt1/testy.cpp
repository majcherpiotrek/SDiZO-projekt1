/*--------------------------------Plik do testowania---------------------------------------------*/

#include <iostream>
#include <fstream>
#include "Tablica.h"
#include "LinkedList.h"
#include "Kopiec.h"
#include "RandomInputGenerator.h"
#include <Windows.h>
#include <time.h>



LARGE_INTEGER startTimer()
{
	LARGE_INTEGER start;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return start;
}
LARGE_INTEGER endTimer()
{
	LARGE_INTEGER stop;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&stop);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return stop;
}

void test() {

	int rozmiaryTab[4] = {1000,2000,5000,10000};
	
	for (int i = 0, range = 25000; i < 2;i++, range = 3 * range) {
		
		double srednie[4];
		 for (int kolejny_rozm = 0; kolejny_rozm < 4; kolejny_rozm++) {
			
			int rozmiar = rozmiaryTab[kolejny_rozm];
			RandomInputGenerator gen = *(new RandomInputGenerator());
			gen.generate(rozmiar, range);
			int* data = gen.getData();

			LinkedList tab = *(new LinkedList());



			for (int i = 0; i < rozmiar; i++)
			{
				tab.push_back(*(data + i));
				/*if (i == rozmiar - 100)
					tab.push(50000);
				else
					tab.push(100000);*/
			}


			/*testy push_front*/

			double avg[10];

			srand(time(NULL));
			for (int i = 0; i < 10; i++) {

				double wyniki[100];

				LARGE_INTEGER countStart, countEnd;
				for (int i = 0; i < 100; i++) {

					int x = rand() % range;
					//tab.pop();
					//tab.push(x);
					//int index = rozmiar / 2;
					//tab.replace(index, x);
					//int index = rozmiar;
					//index = index - 100;
					//int value = tab.get(index);
					/*POMIAR*/
					countStart = startTimer();
					tab.push_front(x); //!!!!!!!!!!!!!!!!!!!!!!!!TESTOWANA FUNKCJA!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					countEnd = endTimer();
					/*--------*/
					//tab.pop();
					tab.pop_front();
					//tab.put(index,x);
					//tab.removeIndex(index);
					/*obliczenie pojedynczego wyniku*/
					double result = countEnd.QuadPart - countStart.QuadPart;



					/*zapisanie wyniku do tablicy*/
					wyniki[i] = result;
					//delete &tab;
				}


				double suma = 0;
				for (int i = 0; i < 100;i++)
					suma += wyniki[i];
				suma = suma / 100;

				avg[i] = suma;

			}

			double suma = 0;
			for (int i = 0; i < 10;i++)
				suma += avg[i];
			suma = suma / 10;
			srednie[kolejny_rozm] = suma;
			
		}
		 /*-----------Utworzenie nazwy pliku-------------*/
		 std::fstream plik;
		 std::stringstream konwerter;
		 std::string buf;

		 std::string nazwa = "D:\\Piotrek\\Documents\\Uczelnia\\IV semestr\\SDiZO\\TESTY projekt 1\\srednieczasy_";



		 konwerter << range;
		 buf = konwerter.str();

		 nazwa.append("range");
		 nazwa.append(buf);
		 nazwa.append(".txt");

		 plik.open(nazwa, std::ios::out);
		 for (int i = 0; i < 4; i++)
			 plik << srednie[i] << ";";
		 plik.close();

	}

	
	
	//tab.saveToFile("D:\\Piotrek\\Documents\\Uczelnia\\IV semestr\\SDiZO\\TESTY projekt 1\\test_data.txt");
	return;
}
