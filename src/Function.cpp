#include "Function.h"

#include <stdexcept>
#include <map>

namespace calculator {

Function::Function(Expression *expression, std::set<std::string> params) :
	expression(expression), params(params) {
}

Function::~Function() {

}

double Function::evaluate(std::vector<Expression *> paramValues) {
	if(paramValues.size() != params.size()) {
		throw std::runtime_error("invalid number of parameters");
	}
	std::map<std::string, Expression *> paramMap;

	auto paramIter = params.begin();
	for(auto paramValue : paramValues) {
		paramMap[*paramIter] = paramValue;
		paramIter++; // safe as both lists have same length
	}

	return expression->evaluate(paramMap);
}

} /* namespace calculator */