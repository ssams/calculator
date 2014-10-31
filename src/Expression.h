#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include <string>

namespace calculator {

class Expression {
public:
	Expression(std::string op);
	Expression(std::string op, const Expression* const left, const Expression* const right);

	double evaluate() const;

protected:
	const Expression* const getLeftNode() const;
	const Expression* const getRightNode() const;
	bool isLeaf() const;

private:
	const std::string mOperator;
	const Expression* const mLeftNode;
	const Expression* const mRightNode;
};

} /* namespace calculator */

#endif /* EXPRESSION_H_ */