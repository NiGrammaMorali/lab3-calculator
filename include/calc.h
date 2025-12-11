#pragma once
#include "stack.h"
#include <map>
#include <vector>

class ArithmExpression {
private:
	string infix;
	string postfix;
	vector<char> lexems;
	map<char, double> operands;
	int GetPriority(char item);
	void Parse();
	void ToPostfix();
public:
	ArithmExpression();
	ArithmExpression(string inf);
	string GetInfix();
	string GetPostfix();
	double Calculate(const map<char, double>& values);
	vector<char> GetOperands() const;
};