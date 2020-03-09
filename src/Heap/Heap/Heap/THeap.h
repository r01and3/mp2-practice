#pragma once

template<class T>
class THeap {
private:	
	int d;
	int max_size;
	int size;
	T* keys;

	int minChild(int);
public:
	THeap(int, int);
	THeap(int, int, int, T*);
	~THeap();

	void transpose(int, int);
	void ascent(int);
	void immersion(int);
	void heapify();
	void remove();
};

template<class T>
THeap<T>::THeap(int _d, int _max_size) {
	d = _d;
	max_size = _max_size;
	size = 0;
	keys = new T[max_size];
}

template<class T>
THeap<T>::THeap(int _d, int _max_size, int _size, T* _keys) {
	d = _d;
	max_size = _max_size;
	size = _size;
	for (int i = 0; i < size; i++)
		keys[i] = _keys[i];
	heapify();
}

template<class T>
THeap<T>::~THeap() {
	delete keys;
}

template<class T>
void THeap<T>::transpose(int _a, int _b) {
	T tmp = keys[_a];
	keys[_a] = keys[_b];
	keys[_b] = tmp;
}

template<class T>
void THeap<T>::ascent(int _a) {
	while (_a > 0) {
		int p;
		p = (_a - 1) / d;
		if (keys[p] > keys[_a]) {
			transpose(_a, p);
			_a = p;
		}
		else
			_a = -1;
	}
}

template<class T>
void THeap<T>::immersion(int _a) {
	int min_child = minChild(_a);
	while (min_child != -1 && keys[min_child] < keys[_a]) {
		transpose(_a, min_child);
		_a = min_child;
		min_child = minChild(_a);
	}
}

template<class T>
void THeap<T>::heapify() {
	for (int i = size - 1; i >= 0; i--)
		ascent(i);
}

template<class T>
void THeap<T>::remove() {
	transpose(0, size - 1);
	size--;
	immersion(0);
}

template<class T>
int THeap<T>::minChild(int _a) {
	if (_a * d + 1 >= size)
		return -1;

	int fd = _a * d + 1;
	int ld = (_a * d + d) ? (size - 1) : (_a * d + d);
	int min_child = fd;

	for (int i = fd; i <= ld; i++) {
		if (keys[i] < keys[min_child])
			min_child = i;
	}

	return min_child;
}