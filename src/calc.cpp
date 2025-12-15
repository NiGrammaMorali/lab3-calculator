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
			if (c == '.') {
				lexem += c;
				continue;
			}
			if (flag_n) {
				lexems.push_back(lexem);
				lexem.clear();
				flag_n = false;
			}
			if ((c >= '(' && c <= '+') || c == '-' || c == '/' || c == '^') {
				if (flag_l) {
					if ((lexem[0] < 48 || lexem[0] > 57) && lexem.size() > 1) {
						cout << "Wrong function name or variable name" << '\n';
						correct = false;
						return;
					}
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
				if (lexem == "tan") {
					lexems.push_back(lexem);
					lexem.clear();
					flag_l = false;
					continue;
				}
				if (lexem == "cot") {
					lexems.push_back(lexem);
					lexem.clear();
					flag_l = false;
					continue;
				}
				if (lexem == "asin") {
					lexems.push_back(lexem);
					lexem.clear();
					flag_l = false;
					continue;
				}
				if (lexem == "acos") {
					lexems.push_back(lexem);
					lexem.clear();
					flag_l = false;
					continue;
				}
				if (lexem == "atan") {
					lexems.push_back(lexem);
					lexem.clear();
					flag_l = false;
					continue;
				}
				if (lexem == "sqrt") {
					lexems.push_back(lexem);
					lexem.clear();
					flag_l = false;
					continue;
				}
				if (lexem.size() >= 4) {
					cout << "Wrong function name or variable name" << '\n';
					correct = false;
					return;
				}
			}
		}
	}
	if (lexem.size() != 0) {
		if ((lexem[0] < 48 || lexem[0] > 57) && lexem.size() > 1) {
			cout << "Wrong function name or variable name" << '\n';
			correct = false;
			return;
		}
		lexems.push_back(lexem);
	}
	correct = true;
}
int ArithmExpression::GetPriority(char item) {
	switch (item) {
	case('"'):
	case('#'):
	case('$'):
	case('%'):
	case('&'):
	case('<'):
	case(','):
	case(':'):
	case(';'):
		return 4;
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
	default:
		return 10;
	}
}
void ArithmExpression::ToPostfix() {
	Parse();
	while (!correct) {
		cout << "Rewrite the expression" << '\n';
		cin >> infix;
		Parse();
	}
	DynamicStack<char> Stack;
	char StackItem;
	string tmp;
	char last_lex = ' ';
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
		else if (lexem == "tan") {
			lexem = '%';
		}
		else if (lexem == "cot") {
			lexem = '&';
		}
		else if (lexem == "asin") {
			lexem = '<';
		}
		else if (lexem == "acos") {
			lexem = ',';
		}
		else if (lexem == "atan") {
			lexem = ':';
		}
		else if (lexem == "sqrt") {
			lexem = ';';
		}
		if (lexem.size() != 1) {
			postfix.push_back(lexem);
			last_lex = 'q';
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
			if (StackItem >= '"' && StackItem <= '&' || StackItem == ',' || StackItem >= ':' && StackItem <= '<') {
				tmp = StackItem;
				postfix.push_back(tmp);
				Stack.Pop();
			}
			break;
		case('-'):
			if (last_lex == ' ' || last_lex == '(') {
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
		case('%'):
		case('&'):
		case('<'):
		case(','):
		case(':'):
		case(';'):
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
		case('0'):
		case('1'):
		case('2'):
		case('3'):
		case('4'):
		case('5'):
		case('6'):
		case('7'):
		case('8'):
		case('9'):
			tmp = item;
			postfix.push_back(tmp);
			break;
		default:
			operands.insert({ item, 0.0 });
			postfix.push_back(lexem);
		}
		last_lex = item;
		
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
string ArithmExpression::GetPostfix() {
	string tmp;
	for (string s : postfix) {
		tmp += s;
	}
	return tmp;
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
				LeftOperand = log(LeftOperand);
				Stack.Push(LeftOperand);
				break;
			case('%'):
				LeftOperand = Stack.Top();
				Stack.Pop();
				LeftOperand = tan(LeftOperand);
				Stack.Push(LeftOperand);
				break;
			case('&'):
				LeftOperand = Stack.Top();
				Stack.Pop();
				LeftOperand = cos(LeftOperand)/sin(LeftOperand);
				Stack.Push(LeftOperand);
				break;
			case('<'):
				LeftOperand = Stack.Top();
				Stack.Pop();
				LeftOperand = asin(LeftOperand);
				Stack.Push(LeftOperand);
				break;
			case(','):
				LeftOperand = Stack.Top();
				Stack.Pop();
				LeftOperand = acos(LeftOperand);
				Stack.Push(LeftOperand);
				break;
			case(':'):
				LeftOperand = Stack.Top();
				Stack.Pop();
				LeftOperand = atan(LeftOperand);
				Stack.Push(LeftOperand);
				break;
			case(';'):
				LeftOperand = Stack.Top();
				Stack.Pop();
				LeftOperand = sqrt(LeftOperand);
				Stack.Push(LeftOperand);
				break;
			case('^'):
				RightOperand = Stack.Top();
				Stack.Pop();
				LeftOperand = Stack.Top();
				Stack.Pop();
				Stack.Push(pow(LeftOperand, RightOperand));
				break;
			case('0'):
			case('1'):
			case('2'):
			case('3'):
			case('4'):
			case('5'):
			case('6'):
			case('7'):
			case('8'):
			case('9'):
				Stack.Push(item - 48);
				break;
			default:
				Stack.Push(operands[item]);
				break;
			}
		}
	}
	return Stack.Top();
}
