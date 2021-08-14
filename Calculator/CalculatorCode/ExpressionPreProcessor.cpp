#include "ExpressionPreProcessor.h"

/*
* Constructor
*/
ExpressionPreProcessor::ExpressionPreProcessor(std::istream& stream)
{
	while (true)
	{
		std::string expression;
		std::getline(stream, expression);

		if (expression == "")
			break;

		expression.erase(std::remove(expression.begin(), expression.end(), ' '), expression.end());
		m_expressions.push(expression);
	}

	m_lexer = new Lexer();
	m_parser = new Parser(m_lexer);
}

/*
* Destructor
*/
ExpressionPreProcessor::~ExpressionPreProcessor()
{
	delete(m_parser);
	delete(m_lexer);
}

/*
* Print the expressions contained by the class
*/
void ExpressionPreProcessor::toString() {
	std::queue<std::string> expressions = m_expressions;
	while (!expressions.empty())
	{
		std::cout << expressions.front() << std::endl;
		expressions.pop();
	}
}

/*
* Print the expression's result if their is not a semi-colon ( ; ) at the and of the expression
*/
void ExpressionPreProcessor::exprResultPrint(double expr_result)
{
	if (m_lexer->getExpression().empty())
	{
		std::cout << expr_result << std::endl;
	}
}

/*
* Sequential evaluation treatement for the Expression in the stream (string from a file, shell, etc)
*/
void ExpressionPreProcessor::eval()
{
	try
	{
		while (!m_expressions.empty())
		{
			m_lexer->setExpression(m_expressions.front());
			double expr_result = m_parser->calculate();

			exprResultPrint(expr_result);

			m_expressions.pop();
		}
	}
	catch (std::string const& error)
	{
		std::cerr << error << std::endl;
	}
}