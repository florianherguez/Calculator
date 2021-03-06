#pragma once
#include <string>
#include <iostream>

#include "ETokenType.h"

class Lexer
{
/* Attribute */
private:
	std::string m_expression = "";

	double m_number = 0.0;
	std::string m_id = "";
	ETokenType m_current_token = ETokenType::END;

/* Methode */
public:
	std::string getExpression();
	double getNumber() const;
	std::string getId() const;

	ETokenType getNextToken();
	ETokenType getCurrentToken();

	void setExpression(std::string const& expression);
private:
	bool isNaryFun(std::string str);
};

