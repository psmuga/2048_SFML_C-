#pragma once
#include <fstream>
#include <string>

using namespace std;
class File
{
public:
	static string fileName;
	static void WriteToFile(unsigned int rhs);
	static unsigned int ReadFromFile();
};

