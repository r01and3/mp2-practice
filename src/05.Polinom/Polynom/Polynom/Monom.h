#pragma once
#include "TNode.h"

class Monom : public TNode<double, unsigned int> {
public:
	Monom(const Monom&);
	Monom(unsigned int, double, Monom* _monom = 0);
	~Monom();

	Monom operator*(double);

	Monom operator+(const Monom&);
	Monom operator-(const Monom&);
	Monom operator*(const Monom&);

	Monom& operator=(const Monom&);

	bool operator>(const Monom&) const;
	bool operator<(const Monom&) const;
	bool operator==(const Monom&) const;
};

Monom::Monom(const Monom& _monom) : TNode<double, unsigned int>(_monom) {}

Monom::Monom(unsigned int _key, double _pData, Monom* _monom) : TNode<double, unsigned int>(_key, _pData, _monom) {
	if (_key < 0 || _key > 999 || _pData == 0.0) throw "Incorrect monom";
}

Monom::~Monom() {
	delete[] pNext;
}

Monom Monom::operator*(double _factor) {
	Monom result(*this);
	result.pData *= _factor;
	return result;
}

Monom Monom::operator+(const Monom& _monom) {
	if (key != _monom.key) return *this;
	Monom result(*this);
	result.pData += _monom.pData;
	return result;
}

Monom Monom::operator-(const Monom& _monom) {
	if (key != _monom.key) return *this;
	Monom result(*this);
	result.pData -= _monom.pData;
	return result;
}

Monom Monom::operator*(const Monom& _monom) {
	if (key + _monom.key < 0 || key + _monom.key > 999) throw "Incorrect degree";
	Monom result(*this);
	result.pData *= _monom.pData;
	result.key += _monom.key;
	return result;
}

Monom& Monom::operator=(const Monom& _monom) {
	if (*this == _monom) return *this;
	delete this;
	key = _monom.key;
	pData = _monom.pData;
	pNext = _monom.pNext;
}

bool Monom::operator<(const Monom& _monom) const {
	if (key < _monom.key) return true;
	if (key == _monom.key && pData < _monom.pData) return true;
	return false;
}

bool Monom::operator>(const Monom& _monom) const {
	if (key > _monom.key) return true;
	if (key == _monom.key && pData > _monom.pData) return true;
	return false;
}

bool Monom::operator==(const Monom& _monom) const {
	if (!(*this < _monom) && !(*this > _monom)) return true;
	return false;
}
