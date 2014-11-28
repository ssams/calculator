/*
 * Parser.cpp
 *
 *  Created on: Nov 5, 2014
 *      Author: hp
 */

#include "Parser.h"
#include "Expression.h"
#include <iostream>
#include <algorithm>
#include <memory>
#include <set>

namespace calculator{

Parser::Parser() {
}


Parser::~Parser(){
}

Expression<double>::Ptr Parser::parse(std::string input){
	input = preProcessInputString(input);
	std::cout << input << std::endl;
	return parse_core(input);
}

Expression<double>::Ptr Parser::parse_core(std::string input){
	std::array<std::string, 3> operators {"+", "*", "/"};
	for(auto op : operators) {
		std::string::size_type pos = input.find(op);
		if(pos != std::string::npos) {
			std::string left(input, 0, pos);
			std::string right(input, pos+1, std::string::npos);
			Expression<double>::Ptr expr = std::make_shared<Expression<double>>(op, parse_core(left), parse_core(right));
			return expr;
		}
	}

	Expression<double>::Ptr expr = std::make_shared<Expression<double>>(input);
	return expr;
}

std::string Parser::preProcessInputString(std::string input){

	const std::string replacement("+-1*");
	std::string::size_type pos = 0;
	while((pos = input.find("-", pos)) != std::string::npos) {
		input.replace(pos, 1, replacement);
		pos += replacement.size();
	}

	input.erase(std::remove(input.begin(), input.end(), ' '), input.end());

	return input;
}
} // namespace calc



