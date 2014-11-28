/*
 * Calculator.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: hp
 */

#include "Calculator.h"
#include "Expression.h"
#include <iostream>
#include <cstdlib>
#include <string>

namespace calculator {

Calculator::Calculator() :
		parser(),
		functionDefRegex("([[:alpha:]]+)\\(([[:alpha:]]+)(?:,([[:alpha:]]+))*\\)[[:space:]]*=(.*)"),
		functionCallRegex("([[:alpha:]]+)\\(([^,]+)(?:,([^,]+))*\\)") {

}

Calculator::~Calculator() {}


void Calculator::start(){

	std::cout << "Calculator started" << std::endl;
	std::string input = "";

	while(input != "q"){
		std::cout << ":";
		std::getline(std::cin, input);

		boost::smatch matches;
		if(boost::regex_match(input, matches, functionDefRegex)) {
			handleFunctionDefinition(matches);
		} else if(boost::regex_match(input, matches, functionCallRegex)) {
			handleFunctionCall(matches);
		} else {
			Expression<double>::Ptr e;
			e = parser->parse(input);
			std::cout << e->evaluate() << std::endl;
		}

	}
}


void Calculator::handleFunctionDefinition(const boost::smatch &matches) {
	std::string functionName = matches[1];
	std::set<std::string> params(matches.begin() + 2, matches.end() - 1);
	Expression<double>::Ptr expr = parser->parse(*(matches.end() - 1));
	Function<double> fun(expr, params);

	functions.emplace(functionName, fun);
	std::cout << "stored function " << functionName << std::endl;
}

void Calculator::handleFunctionCall(const boost::smatch &matches) {
	std::cout << "function call" << std::endl;
	std::string functionName = matches[1];
	try {
		Function<double> fun = functions.at(functionName);
		std::vector<Expression<double>::Ptr> values;
		for(auto i = matches.begin() + 2; i != matches.end(); i++) {
			values.push_back(parser->parse(*i));
		}
		std::cout << fun.evaluate(values) << std::endl;
	} catch(std::out_of_range &e) {
		std::cout << "unknown function" << std::endl;
	}
}

} /* namespace calculator */
