#pragma once
#include <fstream>
#include <string>
#include <sstream>
class FileRW
{
public:
	//UNUSED
	//Reads the first line of a file and tries to convert it to an int
	static int Read(const std::string& fileName);
	//UNUSED
	//Saves number n to a specified file
	static void Write(const std::string& fileName, int n);
	//Returns the high score made on a board with the given number of columns, rows and colors
	static int ReadHighScore(const std::string& fileName, int columns, int rows, int colors);
	//Saves the score made on a board with the given number of columns, rows and colors
	static void WriteHighScore(const std::string& fileName, int score, int columns, int rows, int colors);

private:
	static std::string ReadFileContents(const std::string& fileName);
};
