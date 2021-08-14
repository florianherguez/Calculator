#pragma once
#include <map>
#include <list>

#include "Lexer.h"
class Parser
{
/* Attribute */
private:
	Lexer* m_lexer = nullptr;
	std::map<std::string, double> m_memory;
	std::map<std::string, double(*)(std::list<double>)> m_naries{
		{"cos",[](std::list<double> list)
			{
				if (list.size() != 1)
				{
					throw std::string("Synthax Error : cos function take 1 parameter");
				}
				return std::cos(list.front());
			}
		},
		{"sin",[](std::list<double> list)
			{
				if (list.size() != 1)
				{
					throw std::string("Synthax Error : sin function take 1 parameter");
				}
				return std::sin(list.front());
			}
		},
		{"tan",[](std::list<double> list)
			{
				if (list.size() != 1)
				{
					throw std::string("Synthax Error : tan function take 1 parameter");
				}
				return std::tan(list.front());
			}
		},
		{"log",[](std::list<double> list)
			{
				if (list.size() != 1)
				{
					throw std::string("Synthax Error : log function take 1 parameter");
				}
				return std::log(list.front());
			}
		},
		{"exp",[](std::list<double> list)
			{
				if (list.size() != 1)
				{
					throw std::string("Synthax Error : exp function take 1 parameter");
				}
				return std::exp(list.front());
			}
		},
		{"sqrt",[](std::list<double> list)
			{
				if (list.size() != 1)
				{
					throw std::string("Synthax Error : sqrt function take 1 parameter");
				}
				return std::sqrt(list.front());
			}
		},
		{"pow",[](std::list<double> list)
			{
				if (list.size() != 2)
				{
					throw std::string("Synthax Error : pow function take 2 parameters");
				}
				return std::pow(list.front(), list.back());
			}
		},
		{ "hypot",[](std::list<double> list)
			{
				if (list.size() != 2)
				{
					throw std::string("Synthax Error : hypot function take 2 parameters");
				}
				return std::hypot(list.front(), list.back());
			}
		},
		// lerp(x, a, b) = x+b*(a-x) ==> WARNING here the parameters are not in order the function is lerp(x, a, b) = a+b*(x-a)
		// -> pbl avec le package cmath presence de lerpe a la version c++20 mais ne le détecte pas
		{ "lerp",[](std::list<double> list)
			{
				if (list.size() != 3)
				{
					throw std::string("Synthax Error : lerp function take 3 parameters");
				}
				double x = list.front();
				list.pop_front();
				return list.front() + list.back() * (x - list.front());
			}
		},
		//polynome(k, a0, ..., ak, x) = a_0 + a_1*x + ... + a_k*x^k
		{ "polynome",[](std::list<double> list)
			{
				double k = list.front();
				list.pop_front();
				double x = list.back();
				list.pop_back();

				if (k != list.size() - 1)
				{
					throw std::string("Synthax Error : polynome function take a number of parameters equal to k = nb(a) - 1");
				}
				int length = list.size();
				double result = 0;
				for (int i = 0; i < length; i++)
				{
					result += list.back() * std::pow(x, k);
					list.pop_back();
					k--;
				}
				return result;
			}
		}
	};

/* Methode */
public:
	Parser(Lexer* lexer);

	double parsePrimaryExpression();
	double parseMulDiv();
	double parseAddSub();
	double calculate();
};

