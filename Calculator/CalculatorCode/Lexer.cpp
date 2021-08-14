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
* Get the next Token of the Expression
*/
ETokenType Lexer::getNextToken()
{
	if (m_expression.empty() || m_expression == ";")
	{
		return m_current_token = ETokenType::END;
	}

	char character = m_expression.front();
	m_expression.erase(0, 1);

	// handle operator and token's creation
	switch (character)
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
	case '=':
		return m_current_token = ETokenType::ASSIGN;
	}

	// handle NUMBER token's creation
	if (std::isdigit(character))
	{
		std::string number = "";
		number += character;

		while (!m_expression.empty() && (std::isdigit(m_expression.front()) || m_expression.front() == '.'))
		{
			number += m_expression.front();
			m_expression.erase(0, 1);
		}

		m_number = std::stof(number);
		return m_current_token = ETokenType::NUMBER;
	}

	// handle Nary and ID token's creation
	if (std::isalpha(character))
	{
		std::string id = "";
		id += character;

		while (!m_expression.empty() && std::isalpha(m_expression.front()))
		{
			id += m_expression.front();
			m_expression.erase(0, 1);
		}

		m_id = id;
		// Create NARY token
		if (isNaryFun(id))
		{
			return m_current_token = ETokenType::NARY;
		}
		// Create ID token
		else
		{
			return m_current_token = ETokenType::ID;
		}
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

bool Lexer::isNaryFun(std::string str)
{
	return (str == "cos" || str == "sin" || str == "tan" || str == "log" || str == "exp" || str == "squrt" || str == "pow" || str == "hypot" || str == "lerp" || str == "polynome");
}