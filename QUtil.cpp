#include "QUtil.hpp"



QUtil::QUtil()
{
}

QUtil::~QUtil()
{
}

std::vector<std::string> QUtil::splitString(std::string delimiter, std::string sourceString)
{
	std::vector<std::string> fileIds;

	size_t pos = 0;
	std::string token;
	while ((pos = sourceString.find(delimiter)) != std::string::npos) {
		token = sourceString.substr(0, pos);
		fileIds.push_back(token);
		sourceString.erase(0, pos + delimiter.length());
	}
	// ---------------------
	return fileIds;
}
