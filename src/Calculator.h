/*
 * Calculator.h
 *
 *  Created on: Nov 20, 2014
 *      Author: hp
 */

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include "Parser.h"

#include <string>
#include <vector>
#include <boost/regex.hpp>

namespace calculator {

class Calculator {

public:
	Calculator();
	virtual ~Calculator();

	void start();

	void handleFunctionDefinition(const boost::smatch &matches);
	void handleFunctionCall(const boost::smatch &matches);

private:
	std::vector<std::string> splitString(const std::string &s, char delimiter);

	Parser* parser;

	const boost::regex functionDefRegex;
	const boost::regex functionCallRegex;

	std::map<std::string, Function<double>> functions;
};



} /* namespace calculator */

#endif /* CALCULATOR_H_ */

