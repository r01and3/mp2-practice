#pragma once
#include "Vector.h"

template<class ValueType>
class TMatrix :public TVector<TVector<ValueType> > {
public:
	TMatrix(int _size = 4);
	TMatrix(const TMatrix&);
	TMatrix(const TVector<TVector<ValueType> >&);
	~TMatrix();
	TMatrix operator+(const ValueType);
	TMatrix operator-(const ValueType);
	TMatrix operator*(const ValueType);

	TMatrix operator+(const TMatrix&);
	TMatrix operator-(const TMatrix&);
	
	TVector<ValueType> operator*(const TVector<ValueType>&);
	
	TMatrix& operator=(const TMatrix&);
	
	bool operator==(const TMatrix&) const;
	bool operator!=(const TMatrix&) const;
	
	friend istream& operator >> (istream &in, TMatrix &m){
		for (int i = 0; i < m.size; i++) cin >> m.x[i];
		return in;
	}
	friend ostream& operator << (ostream &out, const TMatrix &m) {
		for (int i = 0; i < m.size - 1; i++)
			out << m.x[i] << std::endl;
		out << m.x[m.size - 1] << endl;
		return out;
	}
};

template<class ValueType>
TMatrix<ValueType>::TMatrix(int _size) : TVector<TVector<ValueType> >(_size){
	for (int i = 0; i < _size; i++)
		x[i] = TVector<ValueType>(_size - i, i);
}

template<class ValueType>
TMatrix<ValueType>::TMatrix(const TMatrix<ValueType> &_copy) :
	TVector<TVector<ValueType> >(_copy) 
{ }

template<class ValueType>
TMatrix<ValueType>::TMatrix(const TVector<TVector<ValueType> > &_vector) :
	TVector<TVector<ValueType> >(_vector)
{ }

template<class ValueType>
TMatrix<ValueType>::~TMatrix()
{ }

template<class ValueType>
TMatrix<ValueType> TMatrix<ValueType>::operator+(const ValueType _p) {
	TMatrix<ValueType> m(size);
	for (int i = 0; i < size; i++)
		m[i] = x[i] + _p;
	return m;
}

template<class ValueType>
TMatrix<ValueType> TMatrix<ValueType>::operator-(const ValueType _p) {
	TMatrix<ValueType> m(size);
	for (int i = 0; i < size; i++)
		m[i] = x[i] - _p;
	return m;
}

template<class ValueType>
TMatrix<ValueType> TMatrix<ValueType>::operator*(const ValueType _p) {
	TMatrix<ValueType> m(size);
	for (int i = 0; i < size; i++)
		m[i] = x[i] * _p;
	return m;
}

template<class ValueType>
TMatrix<ValueType> TMatrix<ValueType>::operator+(const TMatrix &_p) {
	if (size != _p.size)
		throw "Error:Matrices have different sizes";
	TMatrix<ValueType> m(size);
	for (int i = 0; i < size; i++)
		m.x[i] = x[i] + _p.x[i];
	return m;
}

template<class ValueType>
TMatrix<ValueType> TMatrix<ValueType>::operator-(const TMatrix &_p) {
	if (size != _p.size) 
		throw "Error:Matrices have different sizes";
	TMatrix<ValueType> m(size);
	for (int i = 0; i < size; i++)
		m.x[i] = x[i] - _p.x[i];
	return m;
}

template<class ValueType>
TVector<ValueType> TMatrix<ValueType>::operator*(const TVector<ValueType> &_v)
{
	if (size != _v.getSize())
		throw "Error:Matrice and vector have different sizes";
	TVector<ValueType> r(size);
	for (int i = 0; i < size; i++) {
		r[i] = 0;
		for (int j = 0; j < x[i].size; j++) r[i] += x[i].x[j] * _v.x[j];
	}
	return r;
}

template<class ValueType>
TMatrix<ValueType>& TMatrix<ValueType>::operator=(const TMatrix<ValueType> &_m) {
	if (_m == *this) return *this;
	if (size != _m.size) {
		delete[] x;
		size = _m.size;
		x = new TVector<ValueType>[size];
	}
	for (int i = 0; i < size; i++) {
		x[i] = _m.x[i];
	}
	return *this;
}

template<class ValueType>
bool TMatrix<ValueType>::operator==(const TMatrix<ValueType> &_m) const{
	if (size != _m.size) return false;
	for (int i = 0; i < size; i++) if (x[i] != _m.x[i]) return false;
	return true;
}

template<class ValueType>
bool TMatrix<ValueType>::operator!=(const TMatrix<ValueType> &_m) const {
	return !(*this == _m);
}