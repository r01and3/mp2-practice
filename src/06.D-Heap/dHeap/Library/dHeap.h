#pragma once

template<class T>
class dHeap {
private:
	int maxSize;
	int size;
	int d;
	T* elems;

	int minChild(int);
public:
	dHeap(int, int);
	dHeap(int, int, int, T*);
	dHeap(const dHeap&);
	~dHeap();

	T getRoot();
	void addElem(const T&);

	void transpose(int, int);
	void shiftUp(int);
	void shiftDown(int);
	void popMinElems();
	void heapify();
	bool IsEmpty() const;
};

template<class T>
int dHeap<T>::minChild(int _key) {

	if (_key * d + 1 >= size)
		return -1;

	int e1 = _key * d + 1;
	int e2 = (size - 1 < _key * d + d) ? (size - 1) : (_key * d + d);
	int minChild = e1;

	for (int i = e1; i <= e2; i++)
		if (elems[i] < elems[minChild])
			minChild = i;

	return minChild;
}

template<class T>
dHeap<T>::dHeap(int _maxSize, int _d) {

	if (_maxSize <= 0 || _d <= 0) throw "Incorrect data for create Heap";

	size = 0;
	maxSize = _maxSize;
	d = _d;
	elems = new T[maxSize];

}

template<class T>
dHeap<T>::dHeap(int _maxSize, int _size, int _d, T* _elems) {

	if (_maxSize < 0 || _size < 0 || _d <= 0 || _elems == nullptr || _size > _maxSize)
		throw "Incorrect data for create Heap";

	maxSize = _maxSize;
	size = _size;
	d = _d;
	elems = new T[maxSize];
	for (int i = 0; i < size; i++)
		elems[i] = _elems[i];
	heapify();

}

template<class T>
dHeap<T>::dHeap(const dHeap& _copy) {

	maxSize = _copy.maxSize;
	size = _copy.size;
	d = _copy.d;
	elems = new T[maxSize];
	for (int i = 0; i < size; i++)
		elems[i] = _copy.elems[i];

}

template<class T>
dHeap<T>::~dHeap() {

	delete[] elems;

}

template<class T>
T dHeap<T>::getRoot() {

	return elems[0];

}

template<class T>
void dHeap<T>::addElem(const T& _elem) {

	if (size == maxSize) return;

	elems[size] = _elem;
	size++;

	heapify();

}

template<class T>
void dHeap<T>::transpose(int _key_a, int _key_b) {

	if (_key_a >= size || _key_b >= size) throw "Heap out of bounds";

	T tmp = elems[_key_a];
	elems[_key_a] = elems[_key_b];
	elems[_key_b] = tmp;

}

template<class T>
void dHeap<T>::shiftUp(int _key) {

	if (_key >= size) return;

	while (_key > 0) {
		int parentKey = (_key - 1) / d;
		if (elems[parentKey] > elems[_key]) {
			transpose(parentKey, _key);
			_key = parentKey;
		}
		else
			_key = 0;
	}

}

template<class T>
void dHeap<T>::shiftDown(int _key) {

	if (_key >= size) return;

	int minChildKey = minChild(_key);

	while (minChildKey != -1 && elems[_key] > elems[minChildKey]) {
		transpose(minChildKey, _key);
		_key = minChildKey;
		minChildKey = minChild(_key);
	}

}

template<class T>
void dHeap<T>::popMinElems() {

	transpose(0, size - 1);
	size--;
	shiftDown(0);

}

template<class T>
void dHeap<T>::heapify() {

	for (int i = size - 1; i >= 0; i--)
		shiftDown(i);

}


template<class T>
bool dHeap<T>::IsEmpty() const {
	return size == 0;
}
