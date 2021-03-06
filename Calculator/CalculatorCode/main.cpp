#include "ExpressionPreProcessor.h"

int main(int argc, char* argv[]) {
	ExpressionPreProcessor prog = ExpressionPreProcessor(std::cin);
	prog.eval();

	std::cout << "Push Enter for closing...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return 0;
}