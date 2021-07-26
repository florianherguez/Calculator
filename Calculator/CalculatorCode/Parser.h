#pragma once
#include "Lexer.h"
class Parser
{
private:
	/* Attribute */
	Lexer* m_lexer = nullptr;
public:
	/* Constructor */
	Parser(Lexer* lexer);

	double parsePrimaryExpression();
	double parseMulDiv();
	double parseAddSub();
	double calculate();
};

