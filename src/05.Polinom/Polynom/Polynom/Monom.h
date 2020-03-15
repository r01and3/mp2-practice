#pragma once
#include "TNode.h"
#include <string>
 
template<>
class TNode<double, unsigned int> {
public:
	unsigned int key;
	double pData;
	TNode* pNext;

	TNode(const TNode&);
	TNode(unsigned int, double, TNode* _monom = 0);
	TNode(const string&);
	~TNode();

	TNode operator*(double);

	TNode operator+(const TNode&);
	TNode operator-(const TNode&);
	TNode operator*(const TNode&);

	TNode operator-() const;

	TNode& operator=(const TNode&);

	bool operator>(const TNode&) const;
	bool operator<(const TNode&) const;
	bool operator==(const TNode&) const;
	bool operator!=(const TNode&) const;
};

typedef TNode<double, unsigned int> Monom;

TNode<double, unsigned int>::TNode(const TNode<double, unsigned int>& _monom) {
	key = _monom.key;
	pData = _monom.pData;
	if (_monom.pNext == NULL)
		pNext = NULL;
	pNext = _monom.pNext;
}

TNode<double, unsigned int>::TNode(unsigned int _key, double _pData, TNode<double, unsigned int>* _monom) {
	if (_key < 0 || _key > 999 /*|| _pData == 0.0*/) throw exception("Incorrect monom");
	key = _key;
	pData = _pData;
	if (_monom == NULL)
		pNext = NULL;
	pNext = _monom;
}

TNode<double, unsigned int>::TNode(const string& _str) {
	string sws;
	string _coef;
	string _degree;
	string _degreeX = "0";
	string _degreeY = "0";
	string _degreeZ = "0";
	for (int i = 0; i < _str.length(); i++)
		if (_str[i] != '*' && _str[i] != '^') sws += _str[i];
	int i = 0;
	if (sws[0] == 'x' || sws[0] == 'y' || sws[0] == 'z') _coef = '1';
	while (sws[i] != 'x' && sws[i] != 'z' && sws[i] != 'y' && i < sws.length()) {
		_coef += sws[i];
		i++;
	}
	while (i < sws.length()) {
		if (sws[i] == 'x') {
			i++;
			if (sws[i] == 'y' || sws[i] == 'z' || i == sws.length()) _degreeX = '1';
			else _degreeX = sws[i];
		}
		if (sws[i] == 'y') {
			i++;
			if (sws[i] == 'x' || sws[i] == 'z' || i == sws.length()) _degreeY = '1';
			else _degreeY = sws[i];
		}
		if (sws[i] == 'z') {
			i++;
			if (sws[i] == 'x' || sws[i] == 'y' || i == sws.length()) _degreeZ = '1';
			else _degreeZ = sws[i];
		}
		i++;
	}
	_degree = _degree + _degreeX + _degreeY + _degreeZ;
	key = stoi(_degree);
	pData = stod(_coef);
	pNext = NULL;
}

TNode<double, unsigned int>::~TNode() {}

TNode<double, unsigned int> TNode<double, unsigned int>::operator*(double _factor) {
	TNode result(*this);
	result.pData *= _factor;
	return result;
}

TNode<double, unsigned int> TNode<double, unsigned int>::operator+(const TNode<double, unsigned int>& _monom) {
	if (key != _monom.key) return *this;
	TNode<double, unsigned int> result(*this);
	result.pData += _monom.pData;
	return result;
}

TNode<double, unsigned int> TNode<double, unsigned int>::operator-(const TNode<double, unsigned int>& _monom) {
	if (key != _monom.key) return *this;
	TNode<double, unsigned int> result(*this);
	result.pData -= _monom.pData;
	return result;
}

TNode<double, unsigned int> TNode<double, unsigned int>::operator*(const TNode<double, unsigned int>& _monom) {
	if (key + _monom.key < 0 || key + _monom.key > 999) throw "Incorrect degree";
	TNode<double, unsigned int> result(*this);
	result.pData *= _monom.pData;
	result.key += _monom.key;
	return result;
}

TNode<double, unsigned int> TNode<double, unsigned int>::operator-() const{
	TNode<double, unsigned int> result(*this);
	result.pData *= -1;
	return result;
}

TNode<double, unsigned int>& TNode<double, unsigned int>::operator=(const TNode& _monom) {
	if (*this == _monom) return *this;
	key = _monom.key;
	pData = _monom.pData;
	pNext = _monom.pNext;
	return *this;
}

bool TNode<double, unsigned int>::operator<(const TNode& _monom) const {
	if (key < _monom.key) return true;
	return false;
}

bool TNode<double, unsigned int>::operator>(const TNode& _monom) const {
	if (key > _monom.key) return true;
	return false;
}

bool TNode<double, unsigned int>::operator==(const TNode& _monom) const {
	if (key == _monom.key) return true;
	return false;
}

bool TNode<double, unsigned int>::operator!=(const TNode& _monom) const {
	if (key != _monom.key || pData != _monom.pData) return true;
	return false;
}