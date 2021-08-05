#pragma once
#include <iostream>
#include <queue>
#include <string>

#include "Parser.h"

class ExpressionPreProcessor
{
	/* Attribute */
private:
	std::queue<std::string> m_expressions;

	Lexer* m_lexer;
	Parser* m_parser;

	/* Methode */
public:
	/* Constructor */
	ExpressionPreProcessor(std::istream& stream);
	/* Destructor */
	~ExpressionPreProcessor();

	void toString();
	void eval();

private:
	void exprResultPrint(double expr_result);
};

