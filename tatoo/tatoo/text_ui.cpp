#include "text_ui.h"


void runLoop()
{
	int curChoice;
	string inputFileName, projectsDirName, speed = "-s";

	loadSettings(inputFileName, projectsDirName);

	do {
		showOptions();
		curChoice = getChoice();

		system("cls");
		selectChoice(curChoice, inputFileName, projectsDirName, speed);
	} while (curChoice != 3);
}

void testProjects(string &rTestsFile, string &rProjectsDir, string &rSpeed)
{
	TestManager manager(rTestsFile, rProjectsDir, rSpeed);

	manager.testAllProjects();
	system("pause");
}

void changeSettings(string &rTestsFile, string &rProjectsDir, string &rSpeed)
{
	string newTestsFile, newProjectsDir, prompt1 = "testfilename", prompt2 = "projectsfoldername"; // Don't change, hardcoded into settings.txt and load
	cout << prompt1 << " = ";
	std::getline(cin, newTestsFile); // Loads from cin into the string
	cout << endl << prompt2 << " = ";
	std::getline(cin, newProjectsDir);

	rTestsFile = newTestsFile;
	rProjectsDir = newProjectsDir;
}

void writeToSettings(string &rTestsFile, string &rProjectsFolder)
{
	std::ofstream output("settings.txt"); // POens the file
	output << "testfilename=" << rTestsFile << endl << "projectsfoldername=" << rProjectsFolder;
	output.close();
}

void exit(string &rTestsFile, string &rProjectsDir, string &rSpeed)
{
	cout << "Save current settings?<y/n>" << endl << "This will overwrite your last saved settings." << endl;
	string input;
	std::getline(cin, input);
	if (input == "y" || input == "Y")
	{
		writeToSettings(rTestsFile, rProjectsDir);
		cout << "Settings saved." << endl;
	}
	cout << "Exit." << endl;
}

int getChoice()
{
	string input;
	int x = -1;
	cout << "Please choose an option <1, 2, or 3>." << endl;
	std::getline(cin, input);
	sscanf_s(input.c_str(), "%d", &x); // Secure version of scanf for getting an int from the user

	return x;
}

void showOptions()
{
	cout << "1. Test projects" << endl << "2. Change settings" << endl << "3. Exit" << endl;
}

void selectChoice(int choice, string &rTestsFile, string &rProjectsDir, string &rSpeed)
{
	switch(choice)
	{
	case 1:
		testProjects(rTestsFile, rProjectsDir, rSpeed);
		break;
	case 2:
		changeSettings(rTestsFile, rProjectsDir, rSpeed);
		break;
	case 3:
		exit(rTestsFile, rProjectsDir, rSpeed);
		break;
	default:
		break;
	}
}

void loadSettings(string &rTestsFile, string &rProjectsDir)
{
	string s;
	std::ifstream infile("settings.txt");
	if (infile)
	{
		if (std::getline(infile, s))
		{
			std::istringstream inputStream(s);
			std::getline(inputStream, s, '=');
			std::getline(inputStream, rTestsFile);
		}
		if (std::getline(infile, s))
		{
			std::istringstream inputStream(s);
			std::getline(inputStream, s, '=');
			std::getline(inputStream, rProjectsDir);
		}
		if (std::getline(infile, s))
		{
			std::istringstream inputStream(s);
			std::getline(inputStream, s, '=');
			std::getline(inputStream, s);
			
		}
	}
	else
	{
		cout << "settings.txt couldn't be opened" << endl;
	}

	infile.close();
}