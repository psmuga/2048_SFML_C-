#include "File.h"



string File::fileName="files/score.csv";
void File::WriteToFile(unsigned int rhs)
{
	ofstream plik(fileName, ios::out | ios::trunc);
	if (plik.good())
	{	
			plik << rhs << ",";
			plik.close();

	}
	else
	{
		//throw "Unable to write to file";
		throw exception("Unable write to file");
	}
}

unsigned int File::ReadFromFile()
{
	ifstream plik(fileName.c_str());

	if (plik.good())
	{
		unsigned int help;
		plik >> help;
		plik.close();
		return help;
	}
	else
		throw exception("Unable read from file");
}

