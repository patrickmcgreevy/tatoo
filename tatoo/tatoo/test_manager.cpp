#pragma once
#include "test_manager.h"

TestManager::TestManager(const string inputName, const string dirName, const string speedMode)
{
	traverser = Traverser(dirName);
	pInput = getTestInputs(inputName);
	speed = speedMode;
}

void TestManager::testAllProjects()
{

}

void testProject(const string & rPathName);
void testInput(string & rInput, fs::directory_iterator & rDirIt);
void TestManager::testInput(string & rInput) // Uses the current directory to look for the exe
{
	SECURITY_ATTRIBUTES saAttr;

	// Set the bInheritHandle flag so pipe handles are inherited.
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;

	hChild_Named_Std_OUT = CreateNamedPipeA("\\\\.\\pipe\\childout", PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, 1, BUFSIZE, BUFSIZE, 100, &saAttr);
	

	// Create a pipe for the child process's STDOUT.
	if (!CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &saAttr, 0))
	{
		ErrorExit(TEXT("StdoutRd CreatePipe"));
	}
	// Ensure the read handle to the pipe for STDOUT is not inherited.
	if (!SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0))
	{
		ErrorExit(TEXT("Stdout SetHandleInformation"));
	}
	// Create a pipe for the child process's STDIN
	if (!CreatePipe(&g_hChildStd_IN_Rd, &g_hChildStd_IN_Wr, &saAttr, 0))
	{
		ErrorExit(TEXT("Stdin CreatePipe"));
	}

	//CreateChildProcess
	CreateChildProcess();

	WriteToPipe(rInput);
	cout << "Input: " << rInput << endl;

	cout << "==============" << endl << "Output: " << endl;
	ReadFromPipe();
}

void testAllInputs(const string & rPathName);

void TestManager::compileProject(const string & codeDir, const string & comLine)
{
	//STARTUPINFO si;
	//PROCESS_INFORMATION pi;

	//ZeroMemory(&si, sizeof(si));
	//si.cb = sizeof(si);
	//ZeroMemory(&pi, sizeof(pi));

	//auto lpAppName = str_to_lpcwstr(compilerPathName);
	//auto lpComLine = str_to_lpwstr("g++ -std=c++17 -static-libgcc -static-libstdc++ -o proj .\\*.cpp"); //-L.\\bin\\ -LC:\\MinGW\\bin\\
	//auto lpComLine = str_to_lpwstr("C:test");
	//auto lpCurDir = str_to_lpctstr("C:Projects\\PA7");
	//cout << lpAppName << endl;
	//cout << lpComLine << endl;
	//bool scd = SetCurrentDirectory(lpCurDir);
	//DWORD nBufferLen = 1000;
	//LPTSTR buffer = new wchar_t[nBufferLen];
	//GetCurrentDirectory(nBufferLen, buffer);
	//std::wcout << (buffer) << endl;

	auto lpCurDir = str_to_lpctstr(codeDir);
	auto lpComLine = str_to_lpwstr(comLine);

	bool cd = changeCurDir(lpCurDir);
	if (cd)
	{
		cout << "Compiling project..." << endl;
		my_createProcess(lpComLine);
	}
	else
	{
		cout << "Changing directory failed." << endl;
	}

	//if (!scd)
	//{
	//	// CreateProcess() failed
	//	// Get the error from the system
	//	LPVOID lpMsgBuf;
	//	DWORD dw = GetLastError();
	//	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
	//		NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	//	// Display the error
	//	auto strError = (LPTSTR)lpMsgBuf;
	//	std::wcout << (TEXT("::executeCommandLine() failed at CreateProcess()\nCommand=%s\nMessage=%s\n\n"), lpCurDir, strError)<< endl;

	//	// Free resources created by the system
	//	LocalFree(lpMsgBuf);

	//}
	//GetCurrentDirectory(nBufferLen, buffer);
	//std::wcout << buffer << endl;
	//bool suc = CreateProcess(
	//	NULL,
	//	lpComLine,		// Command line
	//	NULL,           // Process handle not inheritable
	//	NULL,           // Thread handle not inheritable
	//	TRUE,          // Set handle inheritance to FALSE
	//	CREATE_NEW_CONSOLE,              // No creation flags
	//	NULL,           // Use parent's environment block
	//	NULL,           // Use parent's starting directory 
	//	&si,            // Pointer to STARTUPINFO structure
	//	&pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
	//);
	//CloseHandle(pi.hProcess);
	//CloseHandle(pi.hThread);

	//if (!suc)
	//{
	//	// CreateProcess() failed
	//	// Get the error from the system
	//	LPVOID lpMsgBuf;
	//	DWORD dw = GetLastError();
	//	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
	//		NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	//	// Display the error
	//	auto strError = (LPTSTR)lpMsgBuf;
	//	std::wcout << (TEXT("::executeCommandLine() failed at CreateProcess()\nCommand=%s\nMessage=%s\n\n"), lpCurDir, strError) << endl;

	//	// Free resources created by the system
	//	LocalFree(lpMsgBuf);

	//}
}

std::wstring TestManager::s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

LPCWSTR TestManager::str_to_lpcwstr(const string & rStr)
{
	std::wstring* temp_name = new std::wstring(s2ws(rStr));
	LPCWSTR process_name = temp_name->c_str();

	return process_name;
}

LPWSTR TestManager::str_to_lpwstr(const string & codePath)
{
	std::wstring *temp = new std::wstring(s2ws(codePath));
	LPWSTR commandLine = LPWSTR(temp->c_str());
	
	return commandLine;
}

string TestManager::codePath_to_clang_args(const string & rPath)
{
	return string(rPath + "\\*.cpp -o prog");
}

LPCTSTR TestManager::str_to_lpctstr(const string & rStr)
{
	std::wstring *temp = new std::wstring(s2ws(rStr));
	LPCTSTR r = LPCTSTR(temp->c_str());

	return r;
}

void TestManager::my_createProcess(LPWSTR & rCommand)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	bool suc = CreateProcess(
		NULL,
		rCommand,		// Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		TRUE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
	);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	if (!suc)
	{
		cout << "Process failed." << endl;
		printLastError_w(rCommand);
	}
	else {
		cout << "Process finished!" << endl;
	}
}

bool TestManager::changeCurDir(LPCTSTR & rDirName)
{
	bool scd = SetCurrentDirectory(rDirName);
	if (!scd)
	{
		printLastError_t(rDirName);
	}
	printCurDir();

	return scd;
}

void TestManager::printLastError_t(LPCTSTR & rCom)
{
	// Get the error from the system
	LPVOID lpMsgBuf;
	DWORD dw = GetLastError();
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	// Display the error
	auto strError = (LPTSTR)lpMsgBuf;
	std::wcout << (TEXT("::executeCommandLine() failed at CreateProcess()\nCommand=%s\nMessage=%s\n\n"), rCom, strError) << endl;

	// Free resources created by the system
	//LocalFree(lpMsgBuf);
	delete[] lpMsgBuf;
}

void TestManager::printLastError_w(LPWSTR &rCom)
{
	// Get the error from the system
	LPVOID lpMsgBuf;
	DWORD dw = GetLastError();
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	// Display the error
	auto strError = (LPTSTR)lpMsgBuf;
	std::wcout << (TEXT("::executeCommandLine() failed at CreateProcess()\nCommand=%s\nMessage=%s\n\n"), rCom, strError) << endl;

	// Free resources created by the system
	//LocalFree(lpMsgBuf);
	delete[] lpMsgBuf;
}

void TestManager::printCurDir()
{
	DWORD nBufferLen = 1000;
	LPTSTR buffer = new wchar_t[nBufferLen];
	GetCurrentDirectory(nBufferLen, buffer);
	std::wcout << "Current directory: " << (buffer) << endl;
	delete[] buffer;
}

void TestManager::testCompiler()
{
	//compileProject("C:\\Users\\Patrick McGreevy\\Documents\\College\\Projects\\Repos\\tatoo\\tatoo\\tatoo\\ClangC2\\bin\\amd64\\clang", 
	//	"C:\\Users\\Patrick McGreevy\\Documents\\College\\Projects\\Repos\\tatoo\\tatoo\\tatoo\\Projects\\PA7");
	//compileProject("dick butt", "\"C:\\Users\\Patrick McGreevy\\Documents\\College\\Projects\\Compile_Test\\Debug\\Compile_Test.exe\"");
	//compileProject("DEPRECIATED", "\"C:\\Users\\Patrick McGreevy\\Documents\\College\\Projects\\Repos\\tatoo\\tatoo\\tatoo\\ClangC2\\bin\\amd64\\clang.exe\" \"C:\\Users\\Patrick McGreevy\\Documents\\College\\Projects\\Repos\\tatoo\\tatoo\\tatoo\\Projects\\PA7\\*.cpp\" -o proj");
	//compileProject("DEP", "cd \"C:\\Users\\Patrick McGreevy\\Documents\\College\\Projects\\Repos\\tatoo\\tatoo\\tatoo\\Projects\\PA7\" g++ -o project *.cpp\"");
	compileProject("C:Projects\\PA7", "g++ -std=c++17 -static-libgcc -static-libstdc++ -o proj .\\*.cpp");
}

void TestManager::CreateChildProcess()
{
	//auto quote = str_to_lpwstr(defaultExeName);
	TCHAR *szCmdline = str_to_lpwstr(defaultExeName);
	PROCESS_INFORMATION piProcInfo;
	STARTUPINFO siStartInfo;
	bool bSuccess = false;

	// Set up members of PI struct
	ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

	// Set up members of SI struct.

	ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
	siStartInfo.cb = sizeof(STARTUPINFO);
	/*siStartInfo.hStdError = g_hChildStd_OUT_Wr; // Uses anonymous pipes
	siStartInfo.hStdOutput = g_hChildStd_OUT_Wr;
	siStartInfo.hStdInput = g_hChildStd_IN_Rd;*/
	siStartInfo.hStdError = hChild_Named_Std_OUT; // Uses named pipe
	siStartInfo.hStdOutput = hChild_Named_Std_OUT;
	siStartInfo.hStdInput = g_hChildStd_IN_Rd;
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES; //  | PIPE_WAIT

	bSuccess = CreateProcess(NULL,
		szCmdline, // command line
		NULL,		// process security attributes
		NULL,		// primary thread security attributes
		TRUE,		// handles are inherited
		CREATE_NEW_CONSOLE,			// creation flags
		NULL,		// use parent's enviroinment
		NULL,		// use parent' current directory
		&siStartInfo,
		&piProcInfo);

	if (!bSuccess)
	{
		ErrorExit(TEXT("CreateProcess"));
	}
	else
	{
		CloseHandle(piProcInfo.hProcess);
		CloseHandle(piProcInfo.hThread);
	}
}

void TestManager::WriteToPipe(const string & rInput)
{
	DWORD dwRead = rInput.size() + 1, dwWritten = 0;
	CHAR chBuf[BUFSIZE];
	strcpy(chBuf, rInput.c_str());
	BOOL bSuccess = FALSE;

	bSuccess = WriteFile(g_hChildStd_IN_Wr, chBuf, dwRead, &dwWritten, NULL);

	if (!CloseHandle(g_hChildStd_IN_Wr))
	{
		ErrorExit(TEXT("StdInWr CloseHandle"));
	}
}

void TestManager::ReadFromPipe()
{
	DWORD dwRead = 0, dwWritten;
	CHAR chBuf[BUFSIZE];
	BOOL bSuccess = FALSE;
	HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	OVERLAPPED ol;
	ZeroMemory(&ol, sizeof(OVERLAPPED));

	HANDLE hChild_out_rd = CreateFileA("\\\\.\\pipe\\childout", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	//ol.hEvent = hChild_Named_Std_OUT;
	//ol.Internal = NULL;
	//ol.InternalHigh = NULL;
	//ol.Offset = 0;
	//ol.OffsetHigh = 0;
	//ol.Pointer = 0;
	//ol.hEvent = hChild_Named_Std_OUT;
	/*COMMTIMEOUTS stdoutCT; // Should be set via my createnamedpipe call.
	stdoutCT.ReadIntervalTimeout = 1;
	stdoutCT.ReadTotalTimeoutConstant = 1;
	stdoutCT.ReadTotalTimeoutMultiplier = 2;
	stdoutCT.WriteTotalTimeoutConstant = 100;
	stdoutCT.WriteTotalTimeoutMultiplier = 2;
	bool sct = SetCommTimeouts(g_hChildStd_OUT_Rd, &stdoutCT);

	cout << "Set timeouts ";
	if (sct)
		cout << "worked." << endl;
	else
	{
		cout << "failed." << endl;
	}*/
		

	//bool firstRead = false;
	system("pause");
	for (;;)
	{
		//bSuccess = ReadFile(g_hChildStd_OUT_Rd, chBuf, BUFSIZE, &dwRead, NULL);
		//do {
			bSuccess = ReadFile(hChild_out_rd, chBuf, BUFSIZE, &dwRead, &ol);

		//} while ((dwRead == 0) && (GetLastError() == 997));
		/*if (!bSuccess)
		{
			ErrorExit(TEXT("ReadFile"));
		}*/
		if (/*firstRead &&*/ (!bSuccess || dwRead == 0))
		{
			//ErrorExit(TEXT("ReadFIle"));
			CloseHandle(hChild_out_rd);
			break;
		}
		/*else {

			switch (GetLastError())
			{
			case ERROR_BROKEN_PIPE:
				cout << "Error broken pipe" << endl;
				break;
			case ERROR_MORE_DATA:
				cout << "Error more data" << endl;
				break;
			default:
				break;
			}
		}*/

		bSuccess = WriteFile(hParentStdOut, chBuf,
			dwRead, &dwWritten, NULL);
		if (!bSuccess) { break; }
		//else if (dwWritten > 0) { firstRead = true; }
		
	}
	cout << GetLastError() << endl;
}

void TestManager::ErrorExit(PTSTR lpszFunction)
{
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(1);
}

void TestManager::test_testinput()
{
	testInput(string("1 1 1 7"));
}