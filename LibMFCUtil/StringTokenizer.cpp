#include "stdafx.h"
#include "StringTokenizer.h"

using namespace std;
StringTokenizer::StringTokenizer(const string& inputstring, const string& seperator)
: _input(inputstring), _delimiter(seperator)
{
	split();
}

StringTokenizer::~StringTokenizer()
{

}

size_t StringTokenizer::countTokens()
{
	return token.size();
}

bool StringTokenizer::hasMoreTokens()
{
	return index != token.end();
}

string StringTokenizer::nextToken()
{
	if (index != token.end()) return *(index++);
	else return "";
}

void StringTokenizer::split()
{
	string::size_type lastPos = _input.find_first_not_of(_delimiter, 0); //구분자가 나타나지 않는 위치
	string::size_type Pos = _input.find_first_of(_delimiter, lastPos); //구분자가 나타나는 위치

	while (string::npos != Pos || string::npos != lastPos)
	{
		token.push_back(_input.substr(lastPos, Pos - lastPos));
		lastPos = _input.find_first_not_of(_delimiter, Pos); //구분자가 나타나지 않는 위치
		Pos = _input.find_first_of(_delimiter, lastPos); //구분자가 나타나는 위치
	}

	index = token.begin();
}
