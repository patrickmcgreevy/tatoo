#pragma once
#include "input.h"
#include "Traverser.h"
#include <iostream>
#include "test_manager.h"

using std::cout;
using std::endl;

int main() {
	vector<string> * pInput = getTestInputs("test.txt");

	for (auto i : *pInput) {
		cout << i << endl;
	}

	Traverser testTraverser = Traverser("test_folder");
	string *pName = nullptr;
	while (testTraverser.getNextPathName(pName))
	{
		cout << *pName << endl;
	}
	
	TestManager testmanagertest = TestManager("test.txt", "test_folder", "-s");
	testmanagertest.testCompiler();
	testmanagertest.test_testinput();
}