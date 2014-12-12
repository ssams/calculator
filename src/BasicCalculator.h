#ifndef BASIC_CALCULATOR_H_
#define BASIC_CALCULATOR_H_

namespace calculator {

class BasicCalculator {

public:
	virtual ~BasicCalculator() =default;

	virtual void start() =0;
	virtual void showFunctions() =0;

};



} /* namespace calculator */

#endif /* BASIC_CALCULATOR_H_ */

