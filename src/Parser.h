/*
 * Parser.h
 *
 *  Created on: Nov 5, 2014
 *      Author: hp
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <array>
#include <forward_list>
#include "Expression.h"

namespace calculator {

class Parser {

public:
	Parser();
	~Parser();


	Expression* parse(std::string input);

private:
	std::forward_list<const Expression*> expressions;
	Expression* parse(std::string input, std::forward_list<const Expression*> expressions);
	std::string preProcessInputString(std::string input);
};

} /* namespace calculator */

#endif /* PARSER_H_ */
