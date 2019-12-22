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

Polynom Polynom::operator+(const Polynom&) {
	Polynom res 
}