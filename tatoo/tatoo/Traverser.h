#pragma once
#include <filesystem>
#include <string>

using std::string;
namespace fs = std::experimental::filesystem;
//using std::experimental::filesystem::directory_iterator;
//using std::experimental::filesystem::path;
//using std::experimental::filesystem::directory_entry;
//using std::experimental::filesystem::is_directory;

class Traverser
{
public:
	Traverser();
	Traverser(string dirName);

	bool getNextPathName(string *&pName);

private:
	fs::directory_iterator dIter;

	const fs::path getNextPath();
};