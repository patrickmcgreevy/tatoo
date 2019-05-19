#include "Traverser.h"

Traverser::Traverser()
{

}
Traverser::Traverser(string dirName)
{
	dIter = fs::directory_iterator(fs::path(dirName));
}

bool Traverser::getNextPathName(string *&pName)
{
	string p = getNextPath().string();
	bool suc = false;

	if (p != "")
	{
		pName = new string(p);
		suc = true;
	}
	else
	{
		pName = nullptr;
		suc = false;
	}

	return suc;
	//return getNextPath().string(); // Returns the pathname as a standard string. Format may be machine dependant
}

const fs::path Traverser::getNextPath()
{
	if (dIter != fs::end(dIter))
	{
		auto cPath = dIter->path();
		++dIter;

		return cPath;
	}
	else
	{
		return fs::path("");
	}
	//try {
	//	//if (dIter != nullptr)
	//	if (is_directory(dIter.))
	//	{
	//		auto cPath = dIter->path(); //Store a copy of the current path
	//		dIter++; // Increments the iterator to the next path
	//		return cPath;
	//	}
	//	else {
	//		return path("");
	//	}
	//}
	//catch (const std::exception& ex) {
	//	return path("");
	//}
	//return dIter->path();
}
//class Traverser {
//public:
//	Traverser(std::string directoryName);
//private:
//	directory_iterator dIter;
//};
//
//Traverser(std::string directoryName) {
//
//}