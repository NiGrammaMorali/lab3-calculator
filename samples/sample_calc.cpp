#include <iostream>
#include "calc.h"

void main() {
	string Expr;
	cin >> Expr;
	ArithmExpression ArExpr(Expr);
	map<char, double> values;
	vector<char> operands = ArExpr.GetOperands();
	double val;
	cout << ArExpr.GetPostfix() << '\n';
	for (const auto& op : operands) {
		cout << op << " = ";
		cin >> val;
		values[op] = val;
	}
	cout << ArExpr.Calculate(values);
}
