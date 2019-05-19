#include "input.h"

vector<string>* getTestInputs(const string & rName)
{
	vector<string> *pInputStrings = new vector<string>; // Will constain a test input in each index
	fstream *pInputFile = new fstream(rName, fstream::in); // Each line has a test input

	loadInputs(pInputStrings, pInputFile);

	delete pInputFile;
	return pInputStrings;
}

void loadInputs(vector<string> * pInputStrings, fstream *pInputFile)
{
	char *pBuffer = new char[1000];
	while (pInputFile && !pInputFile->eof()) {
		pInputFile->getline(pBuffer, 1000); // Delimiter '/n'
		pInputStrings->push_back(string(pBuffer)); // Allows us to use the move constructor bc string(pBuffer) will return a rvalue
	}
 }