#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include <string>
#include <map>
#include <memory>

namespace calculator {

class Expression {
public:
	typedef std::shared_ptr<Expression> Ptr;
	typedef std::shared_ptr<const Expression> PtrConst;

	Expression(std::string op);
	Expression(std::string op, const PtrConst left, const PtrConst right);

	double evaluate(std::map<std::string, Ptr> params = std::map<std::string, Ptr>()) const;
protected:
	const PtrConst getLeftNode() const;
	const PtrConst getRightNode() const;
	bool isLeaf() const;

private:
	const std::string mOperator;
	const PtrConst mLeftNode;
	const PtrConst mRightNode;
};

} /* namespace calculator */

#endif /* EXPRESSION_H_ */
