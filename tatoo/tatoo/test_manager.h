#pragma once
#include "Traverser.h"
#include "input.h"
#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <strsafe.h>
#include <stdio.h>

using std::cout;
using std::endl;



class TestManager
{
public:
	TestManager(const string inputName, const string dirName, const string speedMode);

	void testAllProjects(); // Test all inputs on all projects in the directory
	void testCompiler();
	void test_testinput();
	void testAllInputs(); // Uses current directory
private:
	Traverser traverser;
	vector<string> *pInput;
	string speed;
	bool forceCompile;
	//string compilerPath = ".\\ClangC2\\bin\\amd64\\clang";
	string defaultExeName = "proj"; // Hard coded because I'm a scrub

	//void testInput(vector<string>::iterator & rIt);
	void testProject(const string & rPathName);
	//void testInput(string & rInput, fs::directory_iterator & rDirIt);
	void testInput(string & rInput); // Uses the current directory
	

	void compileProject(const string & codeDirName, const string & commandLine); // Given the folder name, and the commandline compile message, compile all cpp files into a .exe
	bool projectCompiled(); // Checks that the proj.exe exists in the file
	/*
	This is all for making string conversions and interacting with the windows api
	*/

	LPWSTR str_to_lpwstr(const string & codePath); // converts std::string to lpwstr
	std::wstring s2ws(const std::string& s); // Taken from https://stackoverflow.com/a/27296/11444508
	LPCWSTR str_to_lpcwstr(const string & rStr); // converts std::string to LPCWSTR
	LPCTSTR str_to_lpctstr(const string & rStr);
	string codePath_to_clang_args(const string & rPath); // ToDo: Delete this.
	bool changeCurDir(LPCTSTR & rDirName);
	void my_createProcess(LPWSTR & rCommand);
	void printLastError_t(LPCTSTR & rCommand); // Pass the command you gave to the last WinAPI call
	void printLastError_w(LPWSTR & rCommand); // Same bro
	void printCurDir();

	// For creating child processes with piped std input and std output
	// Mostly taken from https://docs.microsoft.com/en-us/windows/desktop/procthread/creating-a-child-process-with-redirected-input-and-output
	#define BUFSIZE 4096
	HANDLE g_hChildStd_IN_Rd = NULL;
	HANDLE g_hChildStd_IN_Wr = NULL;
	HANDLE g_hChildStd_OUT_Rd = NULL;
	HANDLE g_hChildStd_OUT_Wr = NULL;
	HANDLE hChild_Named_Std_OUT = NULL;

	HANDLE g_hInputFile = NULL;

	void CreateChildProcess();
	void WriteToPipe(const string & rInput);
	void ReadFromPipe();
	void ErrorExit(PTSTR);
};