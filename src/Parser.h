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
#include <regex>

namespace calculator {

enum class InputType{
	FuncDef,
	FuncCall,
	Expression
};

class Parser {

public:
	Parser();
	~Parser();

	InputType getInputType(std::string input);

	Expression::Ptr parse(std::string input);
	Function parseFunction(std::string input);
	std::string parseFunctionCall(std::string input, std::vector<Expression::Ptr> values);

private:
	std::regex functionDefRegex;
	std::regex functionCallRegex;


	Expression::Ptr parse_core(std::string input);
	std::string preProcessInputString(std::string input);

	std::map<std::string, Function> functions;
};

} /* namespace calculator */

#endif /* PARSER_H_ */
