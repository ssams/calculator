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
#include <algorithm>

namespace calculator {

Calculator::Calculator() :
		parser(),
		functionDefRegex("([[:alpha:]]+)\\(((?:[[:alpha:]]+)(?:,(?:[[:alpha:]]+))*)\\)[[:space:]]*=(.*)"),
		functionCallRegex("([[:alpha:]]+)\\(((?:[^,]+)(?:,(?:[^,]+))*)\\)") {

}

Calculator::~Calculator() {}


void Calculator::start(){

	std::cout << "Calculator started" << std::endl;
	std::string input = "";

	while(input != "q"){
		std::cout << ":";
		std::getline(std::cin, input);

		if(input != "q") {
			boost::smatch matches;
			if(input == "help"){
				std::cout << "calculator help" << std::endl;
				showFunctions();
			}
			else if(boost::regex_match(input, matches, functionDefRegex)) {
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
}


void Calculator::handleFunctionDefinition(const boost::smatch &matches) {
	std::string functionName = matches[1];
	auto tokens = splitString(matches[2], ',');
	std::set<std::string> params(tokens.begin(), tokens.end());
	Expression<double>::Ptr expr = parser->parse(matches[3]);
	Function<double> fun(expr, params);

	functions.erase(functionName); // ensure old functions are removed before the new one is created
	functions.emplace(functionName, fun);
	std::cout << "stored function " << functionName << std::endl;
}

void Calculator::handleFunctionCall(const boost::smatch &matches) {
	std::string functionName = matches[1];
	std::cout << "calling stored function '" << functionName << "'" << std::endl;
	try {
		Function<double> fun = functions.at(functionName);
		std::vector<std::string> tokens = splitString(matches[2], ',');
		std::vector<Expression<double>::Ptr> values(tokens.size());
		std::transform(tokens.begin(), tokens.end(), values.begin(), [this](const std::string &s) {
			return parser->parse(s);
		});
		std::cout << fun.evaluate(values) << std::endl;
	} catch(std::out_of_range &e) {
		std::cout << "unknown function" << std::endl;
	}
}


void Calculator::showFunctions(){

	std::cout << "defined functions:" << std::endl;
	std::for_each(functions.begin(), functions.end(), [](std::map<std::string, Function<double>>::value_type v){
		std::cout << v.first;
		std::cout << v.second << std::endl;
	});
}

std::vector<std::string> Calculator::splitString(const std::string &s, char delimiter) {
	std::string::size_type start = 0;
	std::string::size_type end = s.find(delimiter);
	std::vector<std::string> v;

	while(end != std::string::npos) {
		v.push_back(s.substr(start, end - start));
		start = end + 1;
		end = s.find(delimiter, start);
	}

	v.push_back(s.substr(start, s.length() - start));
	return v;

}

} /* namespace calculator */
