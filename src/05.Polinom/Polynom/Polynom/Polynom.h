#pragma once
#include "TList.h";
#include "Monom.h"
#include <string>

class Polynom {
public:
	TList<double, unsigned int>* monoms;

	Polynom();
	Polynom(const Polynom&);
	Polynom(string);
	~Polynom();

	Polynom operator+(const Monom&);
	Polynom operator-(const Monom&);
	Polynom operator*(const Monom&);

	Polynom operator+=(const Monom&);
	Polynom operator-=(const Monom&);
	Polynom operator*=(const Monom&);

	Polynom operator+(const Polynom&);
	Polynom operator-(const Polynom&);
	Polynom operator*(const Polynom&);

	Polynom operator+=(const Polynom&);
	Polynom operator-=(const Polynom&);
	Polynom operator*=(const Polynom&);

	Polynom operator-() const;

	Polynom& operator=(const Polynom&);

	bool operator==(const Polynom&) const;

	friend ostream& operator<<(ostream&, Polynom&);
};

Polynom::Polynom() {
	monoms = new TList<double, unsigned int>;
}

Polynom::Polynom(const Polynom& _polynom) {
	monoms = new TList<double, unsigned int>(*_polynom.monoms);
}

Polynom::Polynom(string str) {
	monoms = new TList<double, unsigned int>;
	string sws;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] != '^' && str[i] != '*') sws += str[i];
	}
	if (sws[0] == '+') throw exception("Incorrect str");
	if (sws[sws.length() - 1] == '+' || sws[sws.length() - 1] == '-') throw exception("Incorrect str");
	for (int i = 0; i < sws.length(); i++) if (sws[i] == ' ') throw exception("Incorrect str");
	for (int i = 1; i < sws.length(); i++) if ((sws[i] == 'x' && sws[i - 1] == 'x') || (sws[i] == 'y' && sws[i - 1] == 'y') || (sws[i] == 'z' && sws[i - 1] == 'z')) throw exception("Incorrect str");
	for (int i = 1; i < sws.length(); i++) if ((sws[i] == '+' && sws[i - 1] == '+') || (sws[i] == '+' && sws[i - 1] == '-') || (sws[i] == '-' && sws[i - 1] == '+') || (sws[i] == '-' && sws[i - 1] == '-')) throw exception("Incorrect str");
	int i = 0;
	while (i < sws.length()) {
		string coef;
		string degree;
		string degree_x = "0";
		string degree_y = "0";
		string degree_z = "0";
		while (sws[i] != 'x' && sws[i] != 'y' && sws[i] != 'z' && i < sws.length()) {
			coef += sws[i];
			i++;
		}
		while (sws[i] != '+' && sws[i] != '-' && i < sws.length()) {
			if (sws[i] == 'x') {
				i++;
				
				if (sws[i] == 'y' || sws[i] == 'z' || sws[i] == '+' || sws[i] == '-') {
					degree_x = "1";
					i--;
				}
				else degree_x = sws[i];
			}
			if (sws[i] == 'y') {
				i++;
				if (sws[i] == 'x' || sws[i] == 'z' || sws[i] == '+' || sws[i] == '-') {
					degree_y = "1";
					i--;
				}
				else degree_y = sws[i];
			}
			if (sws[i] == 'z') {
				i++;
				if (sws[i] == 'x' || sws[i] == 'y' || sws[i] == '+' || sws[i] == '-') {
					degree_z = "1";
					i--;
				}
				else degree_z = sws[i];
			}
			i++;
		}
		double _coef = stod(coef);
		degree = degree + degree_x + degree_y + degree_z;
		unsigned int _degree = stoi(degree);
		unsigned int _bkey = 0;
		monoms->Reset();
		while (!monoms->IsEnded()) {
			if (monoms->pCurr->key > _degree) {
				_bkey = monoms->pCurr->key;
				break;
			}
			monoms->Next();
		}
		if (_bkey != 0) monoms->InsertBefore(_degree, _coef, _bkey);
		else monoms->Back(_degree, _coef);
	}
	monoms->Reset();
}

Polynom::~Polynom() {
	delete monoms;
}

Polynom Polynom::operator+(const Monom& _monom) {
	Polynom result(*this);
	unsigned int _bkey = 0;
	result.monoms->Reset();
	while (!result.monoms->IsEnded()) {
		if (result.monoms->pCurr->key == _monom.key) {
			result.monoms->pCurr->pData += _monom.pData;
			if (result.monoms->pCurr->pData == 0) result.monoms->Remove(_monom.key);
			return result;
		}
		if (result.monoms->pCurr->key > _monom.key) {
			_bkey = result.monoms->pCurr->key;
			result.monoms->InsertBefore(_monom.key, _monom.pData, _bkey);
			return result;
		}
		result.monoms->Next();
	}
	result.monoms->Back(_monom.key, _monom.pData);
	result.monoms->Reset();
	return result;
}

Polynom Polynom::operator-(const Monom& _monom) {
	return *this + (-_monom);
}

Polynom Polynom::operator*(const Monom& _monom) {
	monoms->Reset();
	while (!monoms->IsEnded()) {
		monoms->Next();
	}
	if (monoms->pPrev->key + _monom.key < 0 || monoms->pPrev->key + _monom.key > 999) throw exception("Incorrect degree");
	Polynom result(*this);
	result.monoms->Reset();
	while (!result.monoms->IsEnded()) {
		result.monoms->pCurr->key += _monom.key;
		result.monoms->pCurr->pData *= _monom.pData;
		result.monoms->Next();
	}
	result.monoms->Reset();
	return result;
}

Polynom Polynom::operator+=(const Monom& _monom) {
	Polynom copy = *this;
	*this = copy + _monom;
	return *this;
}

Polynom Polynom::operator-=(const Monom& _monom) {
	return *this += (-_monom);
}

Polynom Polynom::operator*=(const Monom& _monom) {
	Polynom copy = *this;
	*this = copy * _monom;
	return *this;
}

Polynom Polynom::operator+(const Polynom& _polynom) {
	Polynom result;
	monoms->Reset();
	_polynom.monoms->Reset();
	while (!monoms->IsEnded() && !_polynom.monoms->IsEnded()) {
		if (monoms->pCurr->key < _polynom.monoms->pCurr->key) {
			result.monoms->Back(monoms->pCurr->key, monoms->pCurr->pData);
			result.monoms->Reset();
			monoms->Next();
		}
		else if (monoms->pCurr->key > _polynom.monoms->pCurr->key) {
			result.monoms->Back(_polynom.monoms->pCurr->key, _polynom.monoms->pCurr->pData);
			result.monoms->Reset();
			_polynom.monoms->Next();
		}
		else if (monoms->pCurr->key == _polynom.monoms->pCurr->key) {
			if (monoms->pCurr->pData + _polynom.monoms->pCurr->pData != 0.0) {
				result.monoms->Back(monoms->pCurr->key, (monoms->pCurr->pData + _polynom.monoms->pCurr->pData));
				result.monoms->Reset();
			}
			monoms->Next();
			_polynom.monoms->Next();
		}
	}
	while (!monoms->IsEnded()) {
		result.monoms->Back(monoms->pCurr->key, monoms->pCurr->pData);
		monoms->Next();
	}
	while (!_polynom.monoms->IsEnded()) {
		result.monoms->Back(_polynom.monoms->pCurr->key, _polynom.monoms->pCurr->pData);
		_polynom.monoms->Next();
	}
	result.monoms->Reset();
	return result;
}

Polynom Polynom::operator-(const Polynom& _polynom) {
	return *this + (-_polynom);
} 

Polynom Polynom::operator*(const Polynom& _polynom) {
	Polynom result;
	_polynom.monoms->Reset();
	while (!_polynom.monoms->IsEnded()) {
		result = result + (*this * (Monom)(*_polynom.monoms->pCurr));
		_polynom.monoms->Next();
	}
	return result;
}

Polynom Polynom::operator+=(const Polynom& _polynom) {
	Polynom copy = *this;
	*this = copy + _polynom;
	return *this;
}

Polynom Polynom::operator-=(const Polynom& _polynom) {
	return *this += (-_polynom);
}

Polynom Polynom::operator*=(const Polynom& _polynom) {
	Polynom copy = *this;
	*this = copy * _polynom;
	return *this;
}

Polynom Polynom::operator-() const{
	Polynom result(*this);
	result.monoms->Reset();
	while (!result.monoms->IsEnded()) {
		result.monoms->pCurr->pData *= -1;
		result.monoms->Next();
	}
	return result;
}

Polynom& Polynom::operator=(const Polynom& _polynom) {
	if (*this == _polynom) return *this;
	delete monoms;
	monoms = new TList<double, unsigned int>(*(_polynom.monoms));
	monoms->Reset();
	return *this;
}

bool Polynom::operator==(const Polynom& _polynom) const{
	monoms->Reset();
	_polynom.monoms->Reset();
	while (!monoms->IsEnded() && !_polynom.monoms->IsEnded()) {
		if (*monoms->pCurr != *_polynom.monoms->pCurr) return false;
		monoms->Next();
		_polynom.monoms->Next();
	}
	if (!monoms->IsEnded() || !_polynom.monoms->IsEnded()) return false;
	return true;
}

ostream& operator<<(ostream& out, Polynom& _polynom) {
	_polynom.monoms->Reset();
	while (!_polynom.monoms->IsEnded()) {
		if(_polynom.monoms->pCurr->pData > 0)
			out << "+" << _polynom.monoms->pCurr->pData;
		else 
			out << _polynom.monoms->pCurr->pData;
		if (_polynom.monoms->pCurr->key / 100 == 1) out << "*x";
		if (_polynom.monoms->pCurr->key / 100 != 0 && _polynom.monoms->pCurr->key / 100 != 1) out << "*x^" << _polynom.monoms->pCurr->key / 100;
		if (_polynom.monoms->pCurr->key % 100 / 10 == 1) out << "*y";
		if (_polynom.monoms->pCurr->key % 100 / 10 != 0 && _polynom.monoms->pCurr->key % 100 / 10 != 1) out << "*y^" << _polynom.monoms->pCurr->key % 100 / 10;
		if (_polynom.monoms->pCurr->key % 10 == 1) out << "*z";
		if (_polynom.monoms->pCurr->key % 10 != 0 && _polynom.monoms->pCurr->key % 10 != 1) out << "*z^" << _polynom.monoms->pCurr->key % 10;
		_polynom.monoms->Next();
	}
	return out;
}