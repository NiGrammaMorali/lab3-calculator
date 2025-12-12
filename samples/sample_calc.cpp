#include <iostream>
#include "calc.h"

void main() {
	string Expr;
	cin >> Expr;
	ArithmExpression ArExpr(Expr);
	map<char, double> values;
	vector<char> operands = ArExpr.GetOperands();
	double val;
	ArExpr.GetPostfix();
	for (const auto& op : operands) {
		if (op >= 48 && op <= 57) {
			values[op] = op - 48;
		}
		else {
			cout << op << " = ";
			cin >> val;
			values[op] = val;
		}
	}
	cout << ArExpr.Calculate(values);
}
