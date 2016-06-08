#pragma once
#include <string>
#include <vector>
class QUtil
{
public:
	QUtil();
	~QUtil();
public:
	std::vector<std::string> splitString(std::string delimiter, std::string sourceString);
};

