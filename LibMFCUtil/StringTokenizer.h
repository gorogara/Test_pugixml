#pragma once

#ifndef stringTokenize_h
	#define stringTokenize_h

#include <vector>
#include <string>


class StringTokenizer
{
public:
	StringTokenizer(const std::string& inputstring, const std::string& seperator);
	~StringTokenizer();

private:
	std::string _input;
	std::string _delimiter;
	std::vector<std::string> token;
	std::vector<std::string>::iterator index;

public:
	size_t countTokens(); //token 갯수
	bool hasMoreTokens(); //token 존재 확인
	std::string nextToken();  //다음 token
	void split();   //string을 seperator로 나눠서 vector에 저장
};

#endif