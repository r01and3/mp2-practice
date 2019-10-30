#pragma once

template<class ValueType>
class TStack {
public:
	ValueType* elems;
	int size;
	int top;
public:
	TStack(int size = 4);
	TStack(const TStack&);
	~TStack();
	void Push(ValueType);
	ValueType Pop();
	bool IsEmpty() const;
	bool IsFull() const;
	ValueType TopElems() const;
	TStack<ValueType>& operator=(const TStack<ValueType>&);
};

template<class ValueType>
TStack<ValueType>::TStack(int _size) {
	size = _size;
	top = -1;
	elems = new ValueType[size];
}

template<class ValueType>
TStack<ValueType>::TStack(const TStack &_copy) {
	size = _copy.size;
	top = _copy.top;
	elems = new ValueType[size];
	for (int i = 0; i < top + 1; i++) elems[i] = _copy.elems[i];
}

template<class ValueType>
TStack<ValueType>::~TStack() {
	size = 0;
	top = -1;
	delete[] elems;
}

template<class ValueType>
bool TStack<ValueType>::IsEmpty() const{
	if (top == -1) return true;
	return false;
}

template<class ValueType>
bool TStack<ValueType>::IsFull() const{
	if (top == size - 1) return true;
	return false;
}

template<class ValueType>
void TStack<ValueType>::Push(ValueType _elem) {
	if (this->IsFull()) throw "Error:Stack full";
	elems[++top] = _elem;
} 

template<class ValueType>
ValueType TStack<ValueType>::Pop() {
	if (this->IsEmpty()) throw "Error:Stack empty";
	return elems[top--];
}

template<class ValueType>
ValueType TStack<ValueType>::TopElems() const {
	return elems[top];
}

template<class ValueType>
TStack<ValueType>& TStack<ValueType>::operator=(const TStack<ValueType> &_stack) {
	if (this == &_stack) return *this;
	if (size != _stack.size) {
		delete[] elems;
		size = _stack.size;
		elems = new ValueType[size];
	}
	top = _stack.top;
	for (int i = 0; i < size; i++) elems[i] = _stack.elems[i];
	return *this;
}