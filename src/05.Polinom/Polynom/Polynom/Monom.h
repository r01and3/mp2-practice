#pragma once
#include "TNode.h"

#define Monom TNode<double, unsigned int>

template<>
class Monom{
private:
	unsigned int key;
	double coef;
	Monom* pNext;
public:
	TNode();
	TNode(double, unsigned int);
	TNode(const Monom&);
	TNode(const string);
	~TNode();

	Monom operator*(double);

	Monom operator+(const Monom&);
	Monom operator-(const Monom&);
	Monom operator*(const Monom&);

	Monom& operator=(const Monom&);

	bool operator==(const Monom&) const;

	friend class Polynom;
};

Monom::TNode() : key(0), coef(0), pNext(nullptr){}

Monom::TNode(double _coef, unsigned int _key){
	if (_key < 0 || _key > 999) throw "Invalid key";
	key = _key;
	coef = _coef;
	pNext = nullptr;
}

Monom::TNode(const Monom &_monom) {
	key = _monom.key;
	coef = _monom.coef;
	if (_monom.pNext != nullptr) {
		pNext = new Monom;
		*pNext = *(_monom.pNext);
	}
	else pNext = nullptr;
}

Monom::TNode(const string _str) {
	if (_str == "") throw "An empty string cannot be converted to monomial";
	double _coef = 0;
	unsigned int _key = 0;
	int j = 0;
	string _sws = "";
	string COEFFICIENT = "";
	string DEGREE = "";
	string DEGREE_X = "";
	string DEGREE_Y = "";
	string DEGREE_Z = "";
	for (int i = 0; i < _str.length(); i++)
		if ((_str[i] != '*') && (_str[i] != '^')) _sws += _str[i];
	while ((_sws[j] != 'x') && (_sws[j] != 'y') && (_sws[j] != 'z')) {
		COEFFICIENT += _str[j++];
	}
	for (int i = 0; i < _sws.length(); i++) {
		if (_sws[i] == 'x') {
			DEGREE_X += _sws[++i];
		}
		if (_sws[i] == 'y') {
			DEGREE_Y += _sws[++i];
		}
		if (_sws[i] == 'z') {
			DEGREE_Z += _sws[++i];
		}
	}
	if (DEGREE_X != "") DEGREE += '0';
	else DEGREE += DEGREE_X;
	if (DEGREE_Y != "") DEGREE += '0';
	else DEGREE += DEGREE_Y;
	if (DEGREE_Y != "") DEGREE += '0';
	else DEGREE += DEGREE_Y;
	_key = stod(DEGREE);
	if (_key > 999) throw "Invalid key";
	_coef = stod(COEFFICIENT);
	key = _key;
	coef = _coef;
	pNext = nullptr;
}

Monom::~TNode() {
	delete[] this;
}

Monom Monom::operator*(double _coef) {
	Monom res = Monom(*this);
	res.coef *= _coef;
	return res;
}

Monom Monom::operator+(const Monom &_monom) {
	if (this->key != _monom.key) return Monom(0, 0);
	Monom res = Monom(*this);
	res.coef += _monom.coef;
	return res;
}

Monom Monom::operator-(const Monom &_monom) {
	if (this->key != _monom.key) return Monom(0, 0);
	Monom res = Monom(*this);
	res.coef -= _monom.coef;
	return res;
}

Monom Monom::operator*(const Monom &_monom) {
	if ((this->key + _monom.key) > 999) throw "Excess degree";
	Monom res = Monom(*this);
	res.coef *= _monom.coef;
	res.key += _monom.key;
	return res;
}

Monom& Monom::operator=(const Monom &_monom) {
	if (*this == _monom) return *this;
	key = _monom.key;
	coef = _monom.coef;
	pNext = _monom.pNext;
}

bool Monom::operator==(const Monom &_monom) const{
	return((key == _monom.key) && (coef == _monom.coef));
}