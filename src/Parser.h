/*
 * Parser.h
 *
 *  Created on: Nov 5, 2014
 *      Author: hp
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "Expression.h"
#include "Function.h"
#include <array>
#include <map>

namespace calculator {

class Parser {

public:
	Parser();
	~Parser();


	Expression::Ptr parse(std::string input);

private:
	Expression::Ptr parse_core(std::string input);
	std::string preProcessInputString(std::string input);

	std::map<std::string, Function> functions;
};

} /* namespace calculator */

#endif /* PARSER_H_ */
