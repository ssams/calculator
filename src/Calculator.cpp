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

Calculator::Calculator():parser()
{
	parser = new Parser();
}

Calculator::~Calculator() {}


void Calculator::start(){

	std::cout << "Calculator started" << std::endl;
	std::string input = "";

	while(input != "q"){
		std::cout << ":";
		std::getline(std::cin, input);

		InputType t = parser->getInputType(input);
		Expression::Ptr e;

		switch(t){

		case InputType::Expression:
			std::cout << "expression" << std::endl;

			e = parser->parse(input);
			std::cout << e->evaluate();
			break;
		case InputType::FuncCall:
			std::cout << "Function Call";
			break;
		case InputType::FuncDef:
			std::cout << "Function Definition";
			auto func = parser->parseFunction(input);
			break;

		}
		std::cout << std::endl;

	}
}

} /* namespace calculator */
