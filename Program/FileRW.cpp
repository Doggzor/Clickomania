#include "FileRW.h"

int FileRW::Read(const std::string& fileName)
{
	std::ifstream in;
	in.open(fileName);
	if (!in.good()) return 0;
	std::string outString;
	std::getline(in, outString);
	in.close();
	return std::stoi(outString);
}

void FileRW::Write(const std::string& fileName, int n)
{
	std::ofstream out;
	out.open(fileName);
	out << std::to_string(n);
	out.close();
}

int FileRW::ReadHighScore(const std::string& fileName, int columns, int rows, int colors)
{
	int nScore, nRows, nColumns, nColors;
	std::stringstream ss(ReadFileContents(fileName));
	while (ss.good()) {
		ss >> nScore >> nColumns >> nRows >> nColors;
		if (columns == nColumns && rows == nRows && colors == nColors)
			return nScore;
	} 
	return 0;
}

void FileRW::WriteHighScore(const std::string& fileName, int score, int columns, int rows, int colors)
{
	int nScore, nRows, nColumns, nColors;
	bool written = false;
	std::stringstream ss(ReadFileContents(fileName));
	//String that will be used to store the text before saving it to a file
	std::string s = "";
	while (ss.good()) {
		ss >> nScore >> nColumns >> nRows >> nColors;
		//Write the new score if the board parameters match the ones in the file
		if (columns == nColumns && rows == nRows && colors == nColors) {
			s += std::to_string(score);
			written = true;
		}
		//Do not modify the score if the board parameters don't match
		else
			s += std::to_string(nScore);
		s += ' ' + std::to_string(nColumns) + ' ' + std::to_string(nRows) + ' ' + std::to_string(nColors) + '\n';
	}
	//If the board with the given parameters wasn't found in the file, add a new entry
	if (!written)
		s += std::to_string(score) + ' ' + std::to_string(columns) + ' ' + std::to_string(rows) + ' ' + std::to_string(colors) + '\n';
	//Delete the last empty line that was written before saving
	s.pop_back();

	//Save the content of the created string to a file
	std::ofstream out;
	out.open(fileName);
	out << s;
	out.close();
}

std::string FileRW::ReadFileContents(const std::string& fileName)
{
	std::ifstream in;
	in.open(fileName);
	std::stringstream ss;
	std::string s;
	while (in.good()) {
		std::getline(in, s);
		ss << s << '\n';
	}
	s = ss.str();
	//Delete the last empty line that was written before returning the string
	s.pop_back();
	in.close();
	return s;
}
