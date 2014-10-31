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

double Expression::evaluate() const {
	if(isLeaf()) {
		double value;
		std::istringstream in(mOperator);
		in >> value;
		return value;
	} else {
		if(mOperator == "*") {
			return getLeftNode()->evaluate() * getRightNode()->evaluate();
		} else if(mOperator == "/") {
			return getLeftNode()->evaluate() / getRightNode()->evaluate();
		} else if(mOperator == "+") {
			return getLeftNode()->evaluate() + getRightNode()->evaluate();
		} else if(mOperator == "-") {
			return getLeftNode()->evaluate() - getRightNode()->evaluate();
		}
	}

	throw std::runtime_error("could not evaluate operator");
}

} /* namespace calculator */
