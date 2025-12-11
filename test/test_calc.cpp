#include <gtest.h>
#include "calc.h"

TEST(Calc, CanMakeEmptyExpr) {
	ASSERT_NO_THROW(ArithmExpression Expr);
}
TEST(Calc, CanMakeExprFromString) {
	string line = "a+b";
	ArithmExpression Expr(line);
	EXPECT_EQ(Expr.GetInfix(), line);
}
TEST(Calc, CanTurnInfixToPostfixEasy) {
	string line = "a+b";
	ArithmExpression Expr(line);
	EXPECT_EQ(Expr.GetPostfix(), "ab+");
}
TEST(Calc, CanTurnInfixToPostfixHard) {
	string line = "a-e+b*(c-d/e)";
	ArithmExpression Expr(line);
	EXPECT_EQ(Expr.GetPostfix(), "ae-bcde/-*+");
}
TEST(Calc, CanCalculate) {
	string line = "a+b*(c-d/e)";
	ArithmExpression Expr(line);
	map<char, double> values;
	vector<char> operands = Expr.GetOperands();
	double val = 1;
	for (const auto& op : operands) {
		values[op] = val;
		val++;
	}
	double result = Expr.Calculate(values);
	EXPECT_EQ(result, 5.4);
}