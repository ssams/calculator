#include <iostream>
#include <cstdlib>
#include <array>
#include <forward_list>

#include "Expression.h"
#include "Function.h"
#include "Parser.h"

using namespace calculator;

int main(int argc, char *argv[]) {

	/*Expression expr3("3");
	Expression expr5("5");
	Expression exprM8("-8");

	Expression exprAdd("+", &expr3, &expr5);
	Expression exprMult("*", &exprM8, &exprAdd);

	std::cout << exprMult.evaluate() << std::endl;*/

	std::string input(argv[1]);
	//std::cout << input << std::endl;

	Parser* parser = new Parser();
	Expression::Ptr expr = parser->parse(input);

	//std::cout << expr->evaluate() << std::endl;

	Function fun(parser->parse("x*x + x"), {"x"});
	Expression::Ptr paramX = parser->parse("7");
	std::cout << fun.evaluate({paramX}) << std::endl;

	delete parser;
	return EXIT_SUCCESS;
}

