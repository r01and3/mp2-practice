#pragma once
#include "dHeap.h"

template<class T>
class pSort {
public:
	static void Sort(T*, int);
};

template<class T>
void pSort<T>::Sort(T* _array, int _arraySize) {

	if (_array == nullptr || _arraySize <= 0) throw "Incorrect data";

	dHeap<T> heap(_arraySize, _arraySize, 2, _array);

	for (int i = 0; i < _arraySize; i++) {
		_array[i] = heap.getRoot();
		heap.popMinElems();
	}

}