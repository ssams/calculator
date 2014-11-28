#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace calculator {

template <typename T>
class Expression {
public:
	typedef std::shared_ptr<Expression<T>> Ptr;
	typedef std::shared_ptr<const Expression<T>> PtrConst;

	Expression(std::string op);
	Expression(std::string op, const PtrConst left, const PtrConst right);

	T evaluate(std::map<std::string, Ptr> params = std::map<std::string, Ptr>()) const;

protected:
	const PtrConst getLeftNode() const;
	const PtrConst getRightNode() const;
	bool isLeaf() const;

private:
	const std::string mOperator;
	const PtrConst mLeftNode;
	const PtrConst mRightNode;
};

// ------------------------------
// implementation

template <typename T> Expression<T>::Expression(std::string op) : Expression(op, nullptr, nullptr) {

}

template <typename T> Expression<T>::Expression(std::string op, const PtrConst  left, const PtrConst right) :
	mOperator(op), mLeftNode(left), mRightNode(right) {
}

template <typename T> const typename Expression<T>::PtrConst Expression<T>::getLeftNode() const {
	return mLeftNode;
}

template <typename T> const typename Expression<T>::PtrConst Expression<T>::getRightNode() const {
	return mRightNode;
}

template <typename T> bool Expression<T>::isLeaf() const {
	return (mLeftNode == nullptr) && (mRightNode == nullptr);
}

template <typename T> T Expression<T>::evaluate(std::map<std::string, Ptr> params) const {
	if(isLeaf()) {
		typename std::map<std::string, Expression<T>::Ptr>::iterator param = params.find(mOperator);
		if(param != params.end()) {
			//std::cout << "param: " << param->first << std::endl;
			return param->second->evaluate();
		} else {
			T value;
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

#endif /* EXPRESSION_H_ */
