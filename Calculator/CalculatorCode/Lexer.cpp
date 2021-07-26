#include "Lexer.h"

std::string Lexer::getExpression()
{
	return m_expression;
}

double Lexer::getNumber() const
{
	return m_number;
}

std::string Lexer::getId() const
{
	return m_id;
}

/*
* Give the current Token
*/
ETokenType Lexer::getCurrentToken()
{
	return m_current_token;
}

/*
* 
*/
ETokenType Lexer::getNextToken()
{
	if (m_expression.empty() || m_expression == ";")
	{
		return m_current_token = ETokenType::END;
	}

	char ch = m_expression.front();
	m_expression.erase(0, 1);

	// handle operator and token's creation
	switch (ch)
	{
	case '(':
		return m_current_token = ETokenType::LEFT_PARE;
	case ')':
		return m_current_token = ETokenType::RIGHT_PARE;
	case '+':
		return m_current_token = ETokenType::PLUS;
	case '-':
		return m_current_token = ETokenType::MINUS;
	case '*':
		return m_current_token = ETokenType::MUL;
	case '/':
		return m_current_token = ETokenType::DIV;
	}

	// handle NUMBER token's creation
	if (std::isdigit(ch))
	{
		std::string s_number = "";
		s_number += ch;

		while (!m_expression.empty() && (std::isdigit(m_expression.front()) || m_expression.front() == '.'))
		{
			s_number += m_expression.front();
			m_expression.erase(0, 1);
		}

		m_number = std::stof(s_number);
		return m_current_token = ETokenType::NUMBER;
	}
	else
	{
		throw std::string("Lexer Error : a word of this sentence" + m_expression + "is not from this language");
	}
}

/*
* set an expression for treatement and erase all the space ' ' in it
*/
void Lexer::setExpression(std::string const& s_expression)
{
	std::string exp_temp = s_expression;
	exp_temp.erase(std::remove(exp_temp.begin(), exp_temp.end(), ' '), exp_temp.end());
	m_expression = exp_temp;
}