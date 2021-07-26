#include "ExpressionPreProcessor.h"


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

}

ExpressionPreProcessor::~ExpressionPreProcessor()
{

}

void ExpressionPreProcessor::toString() {
	std::queue<std::string> expressions = m_expressions;
	while (!expressions.empty())
	{
		std::cout << expressions.front() << std::endl;
		expressions.pop();
	}
}