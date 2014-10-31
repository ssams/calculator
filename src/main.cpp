#include <iostream>
#include <cstdlib>
#include <array>
#include <forward_list>

#include "Expression.h"

using namespace calculator;

Expression* parse(std::string input, std::forward_list<const Expression*> expressions);

int main(int argc, char *argv[]) {
	Expression expr3("3");
	Expression expr5("5");
	Expression exprM8("-8");

	Expression exprAdd("+", &expr3, &expr5);
	Expression exprMult("*", &exprM8, &exprAdd);

	std::cout << exprMult.evaluate() << std::endl;

	// TODO refactor into separate function (utility function in parser class?)
	std::string input(argv[1]);
	const std::string replacement("+-1*");
	std::string::size_type pos = 0;
	while((pos = input.find("-", pos)) != std::string::npos) {
		input.replace(pos, 1, replacement);
		pos += replacement.size();
	}
	std::cout << input << std::endl;



	// TODO move following code + parse function into parser class
	std::forward_list<const Expression*> expressions;

	Expression* expr = parse(input, expressions);
	std::cout << expr->evaluate() << std::endl;

	for(const Expression* expr : expressions) {
		delete expr;
	}

	return EXIT_SUCCESS;
}

Expression* parse(std::string input, std::forward_list<const Expression*> expressions) {
	std::array<std::string, 3> operators {"+", "*", "/"};
	for(auto op : operators) {
		std::string::size_type pos = input.find(op);
		if(pos != std::string::npos) {
			std::string left(input, 0, pos);
			std::string right(input, pos+1, std::string::npos);
			Expression* expr = new Expression(op, parse(left, expressions), parse(right, expressions));
			expressions.push_front(expr);
			return expr;
		}
	}

	Expression* expr = new Expression(input);
	expressions.push_front(expr);
	return expr;
}
