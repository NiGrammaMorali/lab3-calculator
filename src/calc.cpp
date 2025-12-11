#include "calc.h"

ArithmExpression::ArithmExpression() = default;
ArithmExpression::ArithmExpression(string inf) : infix(inf) {
	ToPostfix();
}
void ArithmExpression::Parse() {
	for (char c : infix) {
		lexems.push_back(c);
	}
}
int ArithmExpression::GetPriority(char item) {
	switch (item) {
	case('+'):
	case('-'):
		return 1;
	case('*'):
	case('/'):
		return 2;
	case('('):
	case(')'):
		return -1;
	}
}
void ArithmExpression::ToPostfix() {
	Parse();
	DynamicStack<char> Stack;
	char StackItem;
	for (char item : lexems) {
		switch (item) {
		case('('):
			Stack.Push(item);
			break;
		case(')'):
			StackItem = Stack.Top();
			Stack.Pop();
			while (StackItem != '(') {
				postfix += StackItem;
				StackItem = Stack.Top();
				Stack.Pop();
			}
			break;
		case('+'):
		case('-'):
		case('*'):
		case('/'):
			while (!Stack.IsEmpty()) {
				StackItem = Stack.Top();
				Stack.Pop();
				if (GetPriority(item) <= GetPriority(StackItem)) {
					postfix += StackItem;
				}
				else {
					Stack.Push(StackItem);
					break;
				}
			}
			Stack.Push(item);
			break;
		default:
			operands.insert({item, 0.0});
			postfix += item;
		}
	}
	while (!Stack.IsEmpty()) {
		StackItem = Stack.Top();
		Stack.Pop();
		postfix += StackItem;
	}
}
string ArithmExpression::GetInfix() {
	return infix;
}
string ArithmExpression::GetPostfix() {
	return postfix;
}
vector<char> ArithmExpression::GetOperands() const {
	vector<char> result;
	for (const auto& item : operands) {
		result.push_back(item.first);
	}
	return result;
}
double ArithmExpression::Calculate(const map<char, double>& values) {
	for (auto& value : values) {
		try {
			operands.at(value.first) = value.second;
		}
		catch (out_of_range &e) {}
	}
	DynamicStack<double> Stack;
	double LeftOperand, RightOperand;
	for (char lexem : postfix) {
		switch (lexem) {
		case('+'):
			RightOperand = Stack.Top();
			Stack.Pop();
			LeftOperand = Stack.Top();
			Stack.Pop();
			Stack.Push(LeftOperand + RightOperand);
			break;
		case('-'):
			RightOperand = Stack.Top();
			Stack.Pop();
			LeftOperand = Stack.Top();
			Stack.Pop();
			Stack.Push(LeftOperand - RightOperand);
			break;
		case('*'):
			RightOperand = Stack.Top();
			Stack.Pop();
			LeftOperand = Stack.Top();
			Stack.Pop();
			Stack.Push(LeftOperand * RightOperand);
			break;
		case('/'):
			RightOperand = Stack.Top();
			Stack.Pop();
			LeftOperand = Stack.Top();
			Stack.Pop();
			Stack.Push(LeftOperand / RightOperand);
			break;
		default:
			Stack.Push(operands[lexem]);
			break;
		}
	}
	return Stack.Top();
}