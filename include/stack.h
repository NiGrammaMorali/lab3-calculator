#pragma once
#include <iostream>

using namespace std;

template<typename T>
class DynamicStack {
private:
	int top;
	size_t size;
	T* pMem;
public:
	DynamicStack(size_t sz = 1) : top(-1), size(sz) {
		pMem = new T[size];
	}
	~DynamicStack() {
		delete[] pMem;
	}
	void Push(T val) {
		if (IsFull()) {
			T* tmp = new T[size*2];
			for (size_t i = 0; i < size; i++) {
				tmp[i] = pMem[i];
			}
			delete[] pMem;
			size *= 2;
			pMem = tmp;
		}
		pMem[++top] = val;
	}
	void Pop() {
		if (IsEmpty()) {
			throw out_of_range("The stack is empty");
		}
		pMem[top] = NULL;
		top--;
	}
	T Top() {
		if (IsEmpty()) {
			throw("The stack is empty");
		}
		return pMem[top];
	}
	T Peek(T val) {
		if (val > top || val < 0) {
			throw out_of_range("The index is out of range");
		}
		return pMem[val];
	}
	size_t Size() {
		return size;
	}
	bool IsEmpty() {
		return (top == -1);
	}
	bool IsFull() {
		return (top == size - 1);
	}
	friend ostream& operator<<(ostream& ostr, const DynamicStack& S) {
		for (size_t i = 0; i <= S.top; i++) {
			ostr << S.Peek(i);
		}
		return ostr;
	}
};