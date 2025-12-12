#pragma once
#include "stack.h"
#include <map>
#include <vector>
#include <cmath>
#include <string>

class ArithmExpression {
private:
	string infix;
	vector<string> postfix;
	vector<string> lexems;
	map<char, double> operands;
	int GetPriority(char item);
	void Parse();
	void ToPostfix();
public:
	ArithmExpression();
	ArithmExpression(string inf);
	string GetInfix();
	void GetPostfix();
	double Calculate(const map<char, double>& values);
	vector<char> GetOperands() const;
};
