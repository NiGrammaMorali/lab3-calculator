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
	string line = "5-4+2*(6-7/4)";
	ArithmExpression Expr(line);
	EXPECT_EQ(Expr.GetPostfix(), "54-2674/-*+");
}
TEST(Calc, CanCalculate1) {
	string line = "1+3";
	ArithmExpression Expr(line);
	map<char, double> values;
	double result = Expr.Calculate(values);
	EXPECT_EQ(result, 4);
}
TEST(Calc, CanCalculate2) {
	string line = "22-4*22/5";
	ArithmExpression Expr(line);
	map<char, double> values;
	double result = Expr.Calculate(values);
	EXPECT_FLOAT_EQ(result, 4.4);
}
TEST(Calc, CanCalculate3) {
	string line = "17.6+44.2-0.22*(5.8+3.7)";
	ArithmExpression Expr(line);
	map<char, double> values;
	double result = Expr.Calculate(values);
	EXPECT_FLOAT_EQ(result, 59.71);
}
TEST(Calc, CanCalculate4) {
	string line = "-8*(-8+10)";
	ArithmExpression Expr(line);
	map<char, double> values;
	double result = Expr.Calculate(values);
	EXPECT_FLOAT_EQ(result, -16);
}
TEST(Calc, CanCalculate5) {
	string line = "sin(14+38/2)";
	ArithmExpression Expr(line);
	map<char, double> values;
	double result = Expr.Calculate(values);
	EXPECT_FLOAT_EQ(result, sin(33));
}
TEST(Calc, CanCalculate6) {
	string line = "ln(32)*cot(3^sin(10))";
	ArithmExpression Expr(line);
	map<char, double> values;
	double result = Expr.Calculate(values);
	EXPECT_FLOAT_EQ(result, 5.6515817);
}
TEST(Calc, CanCalculate7) {
	string line = "sqrt(tan(3+2/7+(sin(5^5))))+23.04^2";
	ArithmExpression Expr(line);
	map<char, double> values;
	double result = Expr.Calculate(values);
	EXPECT_FLOAT_EQ(result, 531.985);
}
TEST(Calc, CanCalculate8) {
	string line = "atan(335.23*4/19+ln(12/tan(111)))+3^4";
	ArithmExpression Expr(line);
	map<char, double> values;
	double result = Expr.Calculate(values);
	EXPECT_FLOAT_EQ(result, 82.557);
}