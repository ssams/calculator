#ifndef FUNCTION_H_
#define FUNCTION_H_

#include "Expression.h"
#include <set>
#include <string>
#include <vector>
#include <stdexcept>
#include <map>

namespace calculator {

template <typename T>
class Function {
public:
	typedef Expression<T> ExpressionType;

	Function(typename ExpressionType::PtrConst expression, std::set<std::string> params);
	virtual ~Function();

	T evaluate(std::vector<typename ExpressionType::Ptr> paramValues);

private:
	typename ExpressionType::PtrConst expression;
	std::set<std::string> params;
};


template <typename T> Function<T>::Function(typename ExpressionType::PtrConst expression, std::set<std::string> params) :
	expression(expression), params(params) {
}

template <typename T> Function<T>::~Function() {

}

template<typename T> T Function<T>::evaluate(std::vector<typename ExpressionType::Ptr> paramValues) {
	if(paramValues.size() != params.size()) {
		throw std::runtime_error("invalid number of parameters");
	}
	std::map<std::string, typename ExpressionType::Ptr> paramMap;

	auto paramIter = params.begin();
	for(auto paramValue : paramValues) {
		paramMap[*paramIter] = paramValue;
		paramIter++; // safe as both lists have same length
	}

	return expression->evaluate(paramMap);
}

} /* namespace calculator */

#endif /* FUNCTION_H_ */
