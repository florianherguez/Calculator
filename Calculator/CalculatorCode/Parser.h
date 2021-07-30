#pragma once
#include <map>

#include "Lexer.h"
class Parser
{
private:
	/* Attribute */
	Lexer* m_lexer = nullptr;
	std::map<std::string, double> m_memory;
public:
	/* Constructor */
	Parser(Lexer* lexer);

	double parsePrimaryExpression();
	double parseMulDiv();
	double parseAddSub();
	double calculate();
};

