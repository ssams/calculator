#ifndef FUNCTION_H_
#define FUNCTION_H_

#include "Expression.h"
#include <set>
#include <string>
#include <vector>

namespace calculator {

class Function {
public:
	Function(Expression *expression, std::set<std::string> params);
	virtual ~Function();

	double evaluate(std::vector<Expression *> paramValues);

private:
	Expression *expression;
	std::set<std::string> params;
};

} /* namespace calculator */

#endif /* FUNCTION_H_ */
