#include "Polynom.h"

Polynom::Polynom() {
	monoms = new TList<double, unsigned int>();
}

Polynom::Polynom(const Polynom &_polynom) {
	monoms = new TList<double, unsigned int>(*(_polynom.monoms));
}

Polynom::Polynom(const string _str) {
	string _sws = "";
	for (int i = 0; i < _str.length(); i++) {
		if ((_str[i] != '*') && (_str[i] != '^')) _sws += _str[i];
	}
	for (int i = 0; i < _sws.length(); i++) {
		string _monom = "";
		_monom += _sws[i++];
		while ((_sws[i] != '+') && (_sws[i] != '-')) {
			_monom += _sws[i++];
		}
		Monom monom = Monom(_monom);
		monoms->Back(monom.key, &(monom.coef));
	}
}

Polynom::~Polynom() {
	delete[] monoms;
}

Polynom Polynom::operator+(double _coef) {
	Polynom res = Polynom(*this);
	if (res.monoms->pFirst->key == 0) {
		res.monoms->pFirst->coef += _coef;
		return res;
	}
	res.monoms->Push(0, &_coef);
	return res;
}

Polynom Polynom::operator-(double _coef) {
	Polynom res = Polynom(*this);
	if (res.monoms->pFirst->key == 0) {
		res.monoms->pFirst->coef -= _coef;
		return res;
	}
	double __coef = -_coef;
	res.monoms->Push(0, &__coef);
	return res;
}

Polynom Polynom::operator*(double _coef) {
	Polynom res = Polynom(*this);
	res.monoms->Reset();
	while (res.monoms->IsEnded()) {
		res.monoms->pCurr->coef *= _coef;
		res.monoms->Next();
	}
}

Polynom Polynom::operator+(const Polynom &_polynom) {
	Polynom res = Polynom();
	while ((!monoms->IsEnded()) && (!_polynom.monoms->IsEnded())) {
		if (monoms->pCurr->key < _polynom.monoms->pCurr->key) {
			res.monoms->Back(monoms->pCurr->key, &monoms->pCurr->coef);
			monoms->Next();
		}
		if (monoms->pCurr->key > _polynom.monoms->pCurr->key) {
			res.monoms->Back(_polynom.monoms->pCurr->key, &_polynom.monoms->pCurr->coef);
			_polynom.monoms->Next();
		}
		if (monoms->pCurr->key == _polynom.monoms->pCurr->key) {
			Monom sum = Monom();
			sum = *monoms->pCurr + (*_polynom.monoms->pCurr);
			res.monoms->Back(sum.key, &sum.coef);
			monoms->Next();
			_polynom.monoms->Next();
		}
	}
	if (!monoms->IsEnded()) 
		while (!_polynom.monoms->IsEnded()) {
			res.monoms->Back(_polynom.monoms->pCurr->key, &_polynom.monoms->pCurr->coef);
			_polynom.monoms->Next();
		}
	if (!_polynom.monoms->IsEnded())
		while (!monoms->IsEnded()) {
			res.monoms->Back(monoms->pCurr->key, &monoms->pCurr->coef);
			monoms->Next();
		}
	return res;
}