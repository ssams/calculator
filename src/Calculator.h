/*
 * Calculator.h
 *
 *  Created on: Nov 20, 2014
 *      Author: hp
 */

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include "Parser.h"

#include <regex>

namespace calculator {

class Calculator {

public:
	Calculator();
	virtual ~Calculator();

	void start();

	void handleFunctionDefinition(const std::smatch &matches);
	void handleFunctionCall(const std::smatch &matches);

private:
	Parser* parser;

	const std::regex functionDefRegex;
	const std::regex functionCallRegex;

	std::map<std::string, Function> functions;
};



} /* namespace calculator */

#endif /* CALCULATOR_H_ */

