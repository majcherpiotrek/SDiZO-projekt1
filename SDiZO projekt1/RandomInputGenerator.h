#pragma once
#include <string>
#include <fstream>
#include <time.h>

class RandomInputGenerator
{
	int* tab;
	int size;
	
public:
	RandomInputGenerator();
	~RandomInputGenerator();

	void generate(int length, int range);
	std::string saveToFile(std::string file_name);
	int* getData();
};

