/*
 * Calculator.h
 *
 *  Created on: Nov 20, 2014
 *      Author: hp
 */

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include "Parser.h"

namespace calculator {

class Calculator {

public:
	Calculator();
	virtual ~Calculator();

	void start();

private:
	Parser* parser;


};



} /* namespace calculator */

#endif /* CALCULATOR_H_ */
