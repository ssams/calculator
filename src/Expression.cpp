#include "Expression.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

namespace calculator {

Expression::Expression(std::string op) : Expression(op, nullptr, nullptr) {

}

Expression::Expression(std::string op, const Expression*  left, const Expression* const right) :
	mOperator(op), mLeftNode(left), mRightNode(right) {
}

const Expression* const Expression::getLeftNode() const {
	return mLeftNode;
}

const Expression* const Expression::getRightNode() const {
	return mRightNode;
}

bool Expression::isLeaf() const {
	return (mLeftNode == nullptr) && (mRightNode == nullptr);
}

double Expression::evaluate(std::map<std::string, Expression *> params) const {
	if(isLeaf()) {
		std::map<std::string, Expression *>::iterator param = params.find(mOperator);
		if(param != params.end()) {
			//std::cout << "param: " << param->first << std::endl;
			return param->second->evaluate();
		} else {
			double value;
			std::istringstream in(mOperator);
			in >> value;
			//std::cout << "op: " << mOperator << ", value: " << value << std::endl;
			return value;
		}
	} else {
		if(mOperator == "*") {
			return getLeftNode()->evaluate(params) * getRightNode()->evaluate(params);
		} else if(mOperator == "/") {
			return getLeftNode()->evaluate(params) / getRightNode()->evaluate(params);
		} else if(mOperator == "+") {
			return getLeftNode()->evaluate(params) + getRightNode()->evaluate(params);
		} else if(mOperator == "-") {
			return getLeftNode()->evaluate(params) - getRightNode()->evaluate(params);
		}
		throw std::runtime_error("could not evaluate operator");
	}

}

} /* namespace calculator */
