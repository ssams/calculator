#include <iostream>
#include <cstdlib>
#include <array>
#include <forward_list>

#include "Expression.h"
#include "Parser.h"

using namespace calculator;

Expression* parse(std::string input, std::forward_list<const Expression*> expressions);

int main(int argc, char *argv[]) {

	/*Expression expr3("3");
	Expression expr5("5");
	Expression exprM8("-8");

	Expression exprAdd("+", &expr3, &expr5);
	Expression exprMult("*", &exprM8, &exprAdd);

	std::cout << exprMult.evaluate() << std::endl;*/

	std::string input(argv[1]);
	std::cout << input << std::endl;

	Parser* parser = new Parser();
	Expression* expr = parser->parse(input);

	std::cout << expr->evaluate() << std::endl;

	delete parser;
	return EXIT_SUCCESS;
}

