#include "test_manager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>

using std::cout;
using std::cin;
using std::endl;

struct settings
{
	string inputFileName;
	string projectsDirName;
	string speed;
	bool forceCompile;
};

void runLoop();

void changeSettings(string &rTestsFile, string &rProjectsDir, string &rSpeed); // Lets the user change the settings for the current instance
void changeSettings(settings &rSetting);
void writeToSettings(string &rTestsFile, string &rProjectsFolder);  // Saves the current settings to settings.txt
int getChoice(); // Gets the choice from the user
void showOptions(); // Shows the user all the options they have
void selectChoice(int choice, string &rTestsFile, string &rProjectsDir, string &rSpeed); // Runs the option that the user has chosen
void selectChoice(int choice, settings &rSettings);
void loadSettings(string &rTestsFile, string &rProjectsDir); // Load settings from settings.txt into the current instance
void testProjects(string &rTestsFile, string &rProjectsDir, string &rSpeed); // Tests the project with the specified inputs and the directory
void exit(string &rTestsFile, string &rProjectsDir, string &rSpeed); // Quit and give the option of saving settings
void exit(settings &rSettings);