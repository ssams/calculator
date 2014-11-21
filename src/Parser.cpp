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
#include <regex>
#include <set>

namespace calculator{

Parser::Parser(){
	std::regex functionDefRegex("([[:alpha:]]+)\\(([[:alpha:]]+)(?:,([[:alpha:]]+))*\\)[[:space:]]*=(.*)");
	std::regex functionCallRegex("([[:alpha:]]+)\\(([^,]+)(?:,([^,]+))*\\)");
}


Parser::~Parser(){
}

InputType Parser::getInputType(std::string input){

	std::smatch matches;
	InputType ret;

	if(std::regex_match(input, matches, functionDefRegex)) {
		ret = InputType::FuncDef;
		std::cout << "funcdef";
	}else if(regex_match(input, matches, functionCallRegex)){
		ret = InputType::FuncCall;
		std::cout << "funcCall";
	}else
		ret = InputType::Expression;

	return ret;
}

Expression::Ptr Parser::parse(std::string input){
	input = preProcessInputString(input);
	std::cout << input << std::endl;
	return parse_core(input);
}

Function Parser::parseFunction(std::string input){

	std::smatch matches;
	std::string functionName = matches[1];
	std::set<std::string> params(matches.begin() + 2, matches.end() - 1);
	Expression::Ptr expr = parse(*(matches.end() - 1));
	Function fun(expr, params);

	//functions.emplace(functionName, fun);
	//std::cout << "stored function " << functionName << std::endl;
	return fun;
}

std::string Parser::parseFunctionCall(std::string input, std::vector<Expression::Ptr> values){
	std::smatch matches;
	std::cout << "function call" << std::endl;
	std::string functionName = matches[1];
	try {
		Function fun = functions.at(functionName);
		for(auto i = matches.begin() + 2; i != matches.end(); i++) {
			values.push_back(parse(*i));
		}

		// TODO move somewhere else
		//std::cout << fun.evaluate(values) << std::endl;
		return functionName;
	} catch(std::out_of_range &e) {
		std::cout << "unknown function" << std::endl;
		return nullptr;
	}
}

Expression::Ptr Parser::parse_core(std::string input){
	std::array<std::string, 3> operators {"+", "*", "/"};
	for(auto op : operators) {
		std::string::size_type pos = input.find(op);
		if(pos != std::string::npos) {
			std::string left(input, 0, pos);
			std::string right(input, pos+1, std::string::npos);
			Expression::Ptr expr = std::make_shared<Expression>(op, parse_core(left), parse_core(right));
			return expr;
		}
	}

	Expression::Ptr expr = std::make_shared<Expression>(input);
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



