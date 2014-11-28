#ifndef FUNCTION_H_
#define FUNCTION_H_

#include "Expression.h"
#include <set>
#include <string>
#include <vector>

namespace calculator {

class Function {
public:
	Function(Expression::PtrConst expression, std::set<std::string> params);
	virtual ~Function();

	double evaluate(std::vector<Expression::Ptr> paramValues);

private:
	Expression::PtrConst expression;
	std::set<std::string> params;
};

Function::Function(Expression::PtrConst expression, std::set<std::string> params) :
	expression(expression), params(params) {
}

Function::~Function() {

}

double Function::evaluate(std::vector<Expression::Ptr> paramValues) {
	if(paramValues.size() != params.size()) {
		throw std::runtime_error("invalid number of parameters");
	}
	std::map<std::string, Expression::Ptr> paramMap;

	auto paramIter = params.begin();
	for(auto paramValue : paramValues) {
		paramMap[*paramIter] = paramValue;
		paramIter++; // safe as both lists have same length
	}

	return expression->evaluate(paramMap);
}

} /* namespace calculator */

#endif /* FUNCTION_H_ */
