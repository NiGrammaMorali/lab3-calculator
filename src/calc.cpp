#include "calc.h"

ArithmExpression::ArithmExpression() = default;
ArithmExpression::ArithmExpression(string inf) : infix(inf) {
	ToPostfix();
}
void ArithmExpression::Parse() {
	string lexem;
	bool flag_l = false;
	bool flag_n = false;
	for (char c : infix) {
		if (c == '\n') {
			break;
		}
		if (c >= '0' && c <= '9') {
			if (flag_l) {
				lexems.push_back(lexem);
				lexem.clear();
				flag_l = false;
			}
			lexem.push_back(c);
			flag_n = true;
		}
		else {
			if (flag_n) {
				lexems.push_back(lexem);
				lexem.clear();
				flag_n = false;
			}
			if ((c >= '(' && c <= '+') || c == '-' || c == '/' || c == '^') {
				if (flag_l) {
					lexems.push_back(lexem);
					lexem.clear();
					flag_l = false;
				}
				lexem = c;
				lexems.push_back(lexem);
				lexem.clear();
			}
			else {
				flag_l = true;
				lexem.push_back(c);
				if (lexem == "sin") {
					lexems.push_back(lexem);
					lexem.clear();
					flag_l = false;
					continue;
				}
				if (lexem == "cos") {
					lexems.push_back(lexem);
					lexem.clear();
					flag_l = false;
					continue;
				}
				if (lexem == "ln") {
					lexems.push_back(lexem);
					lexem.clear();
					flag_l = false;
					continue;
				}
			}
		}
	}
	if (lexem.size() != 0) {
		lexems.push_back(lexem);
	}
}
int ArithmExpression::GetPriority(char item) {
	switch (item) {
	case('"'):
	case('#'):
	case('$'):
	case('^'):
		return 3;
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
	string tmp;
	for (string lexem : lexems) {
		char item;
		if (lexem == "sin") {
			lexem = '"';
		}
		else if (lexem == "cos") {
			lexem = '#';
		}
		else if (lexem == "ln") {
			lexem = '$';
		}
		if (lexem.size() != 1) {
			postfix.push_back(lexem);
			continue;
		}
		else {
			item = lexem[0];
		}
		switch (item) {
		case('('):
			Stack.Push(item);
			break;
		case(')'):
			StackItem = Stack.Top();
			Stack.Pop();
			while (StackItem != '(') {
				tmp = StackItem;
				postfix.push_back(tmp);
				StackItem = Stack.Top();
				Stack.Pop();
			}
			StackItem = Stack.Top();
			if (StackItem >= '"' && StackItem <= '$') {
				tmp = StackItem;
				postfix.push_back(tmp);
				Stack.Pop();
			}
			break;
		case('-'):
			if (Stack.IsEmpty()) {
				Stack.Push('0');
			}
			else if (Stack.Top() == '(') {
				Stack.Push('0');
			}
			while (!Stack.IsEmpty()) {
				StackItem = Stack.Top();
				Stack.Pop();
				if (GetPriority(item) <= GetPriority(StackItem)) {
					tmp = StackItem;
					postfix.push_back(tmp);
				}
				else {
					Stack.Push(StackItem);
					break;
				}
			}
			Stack.Push(item);
			break;
		case('+'):
		case('*'):
		case('/'):
		case('"'):
		case('#'):
		case('$'):
		case('^'):
			while (!Stack.IsEmpty()) {
				StackItem = Stack.Top();
				Stack.Pop();
				if (GetPriority(item) <= GetPriority(StackItem)) {
					tmp = StackItem;
					postfix.push_back(tmp);
				}
				else {
					Stack.Push(StackItem);
					break;
				}
			}
			Stack.Push(item);
			break;
		default:
			operands.insert({ item, 0.0 });
			postfix.push_back(lexem);
		}
		
	}
	while (!Stack.IsEmpty()) {
		StackItem = Stack.Top();
		Stack.Pop();
		tmp = StackItem;
		postfix.push_back(tmp);
	}
}
string ArithmExpression::GetInfix() {
	return infix;
}
void ArithmExpression::GetPostfix() {
	for (string s : postfix) {
		cout << s;
	}
	cout << '\n';
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
	for (string lexem : postfix) {
		char item;
		if (lexem.size() > 1) {
			double tmp = stod(lexem);
			Stack.Push(tmp);
			cout << Stack.Top() << '\n';
		}
		else {
			item = lexem[0];
			switch (item) {
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
			case('"'):
				LeftOperand = Stack.Top();
				Stack.Pop();
				LeftOperand = sin(LeftOperand);
				Stack.Push(LeftOperand);
				break;
			case('#'):
				LeftOperand = Stack.Top();
				Stack.Pop();
				LeftOperand = cos(LeftOperand);
				Stack.Push(LeftOperand);
				break;
			case('$'):
				LeftOperand = Stack.Top();
				Stack.Pop();
				LeftOperand = log2(LeftOperand);
				Stack.Push(LeftOperand);
				break;
			case('^'):
				RightOperand = Stack.Top();
				Stack.Pop();
				LeftOperand = Stack.Top();
				Stack.Pop();
				Stack.Push(pow(LeftOperand, RightOperand));
				break;
			default:
				Stack.Push(operands[item]);
				break;
			}
		}
	}
	return Stack.Top();
}
