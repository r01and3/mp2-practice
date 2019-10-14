#pragma once
#include <string.h>
#include <math.h>
#include <iostream>
#include <iomanip>

using namespace std;

template<class ValueType>
class TMatrix;

template<class ValueType>
class TVector {
protected:
	int size;
	ValueType* x;
	int index;
public:
	TVector(int size = 4 , int index = 0);
	TVector(ValueType*, int, int);
	TVector(const TVector&);
	~TVector();
	ValueType length() const;
	TVector& operator=(const TVector&);
	TVector operator+(ValueType);
	TVector operator-(ValueType);
	TVector operator*(ValueType);
	TVector operator+(const TVector&);
	TVector operator-(const TVector&);
	ValueType operator*(const TVector&);
	bool operator==(const TVector&) const;
	bool operator!=(const TVector&) const;
	ValueType& operator[](int);
	int getSize() const;
	void setSize(int);
	friend istream& operator >> (istream &_in, TVector &_vector) {
		for (int i = 0; i < _vector.size; i++) _in >> _vector.x[i];
		return _in;
	}
	friend ostream& operator<<(ostream &_out, const TVector<ValueType> &_vector) {
		for (int i = 0; i < _vector.index; i++)
			_out << std::setw(5) << std::setprecision(2) << std::right << ValueType(0) << ' ';
		for (int i = 0; i < _vector.size; i++)
			_out << std::setw(5) << std::setprecision(2) << std::right << _vector.x[i] << ' ';
		return _out;
	}
	friend TMatrix<ValueType>;
};

template<class ValueType>
TVector<ValueType>::TVector(int _size, int _index) {
	size = _size;
	x = new ValueType[size];
	index = _index;
}

template<class ValueType>
TVector<ValueType>::TVector(ValueType* _x, int _size, int _index) {
	size = _size;
	x = new ValueType[size];
	index = _index;
	for (int i = 0; i < size; i++) x[i] = _x[i];
}

template<class ValueType>
TVector<ValueType>::TVector(const TVector &_copy) {
	size = _copy.size;
	x = new ValueType[size];
	index = _copy.index;
	for (int i = 0; i < size; i++) x[i] = _copy.x[i];
}

template<class ValueType>
TVector<ValueType>::~TVector() {
	size = 0;
	index = 0;
	delete[]x;
}

template<class ValueType>
TVector<ValueType>& TVector<ValueType>::operator=(const TVector<ValueType> &_vector) {
	if (_vector == *this) return *this;
	if (size != _vector.size) {
		delete[] x;
		size = _vector.size;
		x = new ValueType[size];
	}
	index = _vector.index;
	for (int i = 0; i < size; i++)
		x[i] = _vector.x[i];
	return *this;
}

template<class ValueType>
ValueType TVector<ValueType>::length() const {
	ValueType length = 0;
	for (int i = 0; i < size; i++)length += x[i] * x[i];
	return sqrt(length);
}

template<class ValueType>
TVector<ValueType> TVector<ValueType>::operator+(ValueType _plus) {
	TVector<ValueType> r(size, index);
	for (int i = 0; i < size; i++) r.x[i] = x[i] + _plus;
	return r;
}

template<class ValueType>
TVector<ValueType> TVector<ValueType>::operator-(ValueType _minus) {
	TVector<ValueType> r(size, index);
	for (int i = 0; i < size; i++) r.x[i] = x[i] - _minus;
	return r;
}

template<class ValueType>
TVector<ValueType> TVector<ValueType>::operator*(ValueType _multiplus) {
	TVector<ValueType> r(size, index);
	for (int i = 0; i < size; i++) r.x[i] = x[i] * _multiplus;
	return r;
}

template<class ValueType>
TVector<ValueType> TVector<ValueType>::operator+(const TVector<ValueType> &_vector) {
	if ((size != _vector.size)||(index != _vector.index)) throw "Error:Different size vectors";
	TVector<ValueType> r(size, index);
	for (int i = 0; i < size; i++) r.x[i] = x[i] + _vector.x[i];
	return r;
}

template<class ValueType>
TVector<ValueType> TVector<ValueType>::operator-(const TVector<ValueType> &_vector) {
	if ((size != _vector.size) || (index != _vector.index)) throw "Error:Different size vectors";
	TVector<ValueType> r(size, index);
	for (int i = 0; i < size; i++) r.x[i] = x[i] - _vector.x[i];
	return r;
}

template<class ValueType>
ValueType TVector<ValueType>::operator*(const TVector<ValueType> &_vector) {
	if ((size != _vector.size) || (index != _vector.index)) throw "Error:Different size vectors";
	ValueType r = 0;
	for (int i = 0; i < _vector.size; i++) {
		r += x[i] * _vector.x[i];
	}
	return r;
}

template<class ValueType>
bool TVector<ValueType>::operator==(const TVector<ValueType> &_vector) const{
	if ((size != _vector.size) || (index != _vector.index)) return false;///
	for (int i = 0; i < size; i++) if (x[i] != _vector.x[i]) return false;
	return true;
}

template<class ValueType>
bool TVector<ValueType>::operator!=(const TVector<ValueType> &_vector) const {
	return !(*this == _vector);
}

template<class ValueType>
ValueType& TVector<ValueType>::operator[](int _position) {
	if (_position > size) throw "Going beyond the limits of the vector";
	return x[_position - index];
}

template<class ValueType>
int TVector<ValueType>::getSize() const{
	return size;
}

template<class ValueType>
void TVector<ValueType>::setSize(int s) {
	size = s;
}

