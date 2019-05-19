#pragma once
#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::vector;
using std::fstream;

vector<string>* getTestInputs(const string & rName);
void loadInputs(vector<string> * pInputStrings, fstream *pInputFile);