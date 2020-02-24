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

	Polynom operator+(const Polynom&);
	Polynom operator-(const Polynom&);
	Polynom operator*(const Polynom&);

	Polynom& operator=(const Polynom&);
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
				degree_x = sws[i];
			}
			if (sws[i] == 'y') {
				i++;
				degree_y = sws[i];
			}
			if (sws[i] == 'z') {
				i++;
				degree_z = sws[i];
			}
			i++;
		}
		double _coef = stod(coef);
		degree = degree + degree_x + degree_y + degree_z;
		unsigned int _degree = stoi(degree);
		monoms->Back(_degree, _coef);
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
	Polynom result(*this);
	unsigned int _bkey = 0;
	result.monoms->Reset();
	while (!result.monoms->IsEnded()) {
		if (result.monoms->pCurr->key == _monom.key) {
			result.monoms->pCurr->pData -= _monom.pData;
			return result;
		}
		if (result.monoms->pCurr->key > _monom.key) {
			_bkey = result.monoms->pCurr->key;
			result.monoms->InsertBefore(_monom.key, (-_monom.pData), _bkey);
			return result;
		}
		result.monoms->Next();
	}
	result.monoms->Back(_monom.key, (-_monom.pData));
	result.monoms->Reset();
	return result;
}

Polynom Polynom::operator*(const Monom& _monom) {
	monoms->Reset();
	while (!monoms->IsEnded()) {
		if (monoms->pCurr->key + _monom.key < 0 || monoms->pCurr->key + _monom.key > 999) throw "Incorrect degree";
		monoms->Next();
	}
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

Polynom Polynom::operator+(const Polynom& _polynom) {
	Polynom result;
	while (!monoms->IsEnded() && !_polynom.monoms->IsEnded()) {
		if (monoms->pCurr->key < _polynom.monoms->pCurr->key) {
			result.monoms->Back(monoms->pCurr->key, monoms->pCurr->pData);
			monoms->Next();
		}
		else if (monoms->pCurr->key > _polynom.monoms->pCurr->key) {
			result.monoms->Back(_polynom.monoms->pCurr->key, _polynom.monoms->pCurr->pData);
			_polynom.monoms->Next();
		}
		else if (monoms->pCurr->key == _polynom.monoms->pCurr->key) {
			result.monoms->Back(monoms->pCurr->key, (monoms->pCurr->pData + _polynom.monoms->pCurr->pData));
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
	Polynom result;
	while (!monoms->IsEnded() && !_polynom.monoms->IsEnded()) {
		if (monoms->pCurr->key < _polynom.monoms->pCurr->key) {
			result.monoms->Back(monoms->pCurr->key, monoms->pCurr->pData);
			monoms->Next();
		}
		if (monoms->pCurr->key > _polynom.monoms->pCurr->key) {
			result.monoms->Back(_polynom.monoms->pCurr->key, (-_polynom.monoms->pCurr->pData));
			_polynom.monoms->Next();
		}
		if (monoms->pCurr->key == _polynom.monoms->pCurr->key) {
			result.monoms->Back(monoms->pCurr->key, (monoms->pCurr->pData - _polynom.monoms->pCurr->pData));
			monoms->Next();
			_polynom.monoms->Next();
		}
	}
	while (!monoms->IsEnded()) {
		result.monoms->Back(monoms->pCurr->key, monoms->pCurr->pData);
		monoms->Next();
	}
	while (!_polynom.monoms->IsEnded()) {
		result.monoms->Back(_polynom.monoms->pCurr->key, (-_polynom.monoms->pCurr->pData));
		_polynom.monoms->Next();
	}
	result.monoms->Reset();
	return result;
}

Polynom Polynom::operator*(const Polynom& _polynom) {
	Polynom result;
	monoms->Reset();
	_polynom.monoms->Reset();
	while (!monoms->IsEnded()) {
		result.monoms->Back((monoms->pCurr->key + _polynom.monoms->pCurr->key), (monoms->pCurr->pData * _polynom.monoms->pCurr->pData));
		monoms->Next();
	}
	_polynom.monoms->Next();
	while (!_polynom.monoms->IsEnded()) {
		monoms->Reset();
		while (!monoms->IsEnded()) {
			unsigned int _akey = _polynom.monoms->pPrev->key + monoms->pCurr->key;
			result.monoms->InsertAfter((monoms->pCurr->key + _polynom.monoms->pCurr->key), monoms->pCurr->pData * _polynom.monoms->pCurr->pData, _akey);
			monoms->Next();
		}
		_polynom.monoms->Next();
	}
	result.monoms->Reset();
	return result;
}

Polynom& Polynom::operator=(const Polynom& _polynom) {
	delete monoms;
	monoms = new TList<double, unsigned int>(*(_polynom.monoms));
	monoms->Reset();
	return *this;
}
