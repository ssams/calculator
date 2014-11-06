/*
 * Parser.cpp
 *
 *  Created on: Nov 5, 2014
 *      Author: hp
 */

#include "Parser.h"
#include "Expression.h"
#include <iostream>

namespace calculator{

Parser::Parser(){}

Parser::~Parser(){
	std::cout << "desctructor called";
	for(const Expression* expr : expressions) {
				delete expr;
	}
}

Expression* Parser::parse(std::string input){
	input = preProcessInputString(input);
	std::cout << input << std::endl;
	return parse(input, this->expressions);
}

Expression* Parser::parse(std::string input, std::forward_list<const Expression*> expressions){
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

std::string Parser::preProcessInputString(std::string input){

	const std::string replacement("+-1*");
	std::string::size_type pos = 0;
	while((pos = input.find("-", pos)) != std::string::npos) {
		input.replace(pos, 1, replacement);
		pos += replacement.size();
	}
	return input;
}
} // namespace calc



