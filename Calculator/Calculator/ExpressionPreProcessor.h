#pragma once
#include <iostream>
#include <queue>
#include <string>

class ExpressionPreProcessor
{
private:
	std::queue<std::string> m_expressions;
public:
	ExpressionPreProcessor(std::istream& stream);
	~ExpressionPreProcessor();
	void toString();
};

