#pragma once
#include "TList.h";
#include "Monom.h"

class Polynom {
private:
	TList<double, unsigned int, Monom>* monoms;

	void Parse(const string&);
public:
	Polynom();
	Polynom(const Polynom&);
	Polynom(const string&);
	~Polynom();

	Polynom operator+(const Monom&);
	Polynom operator-(const Monom&);
	Polynom operator*(const Monom&);

	Polynom& operator+=(const Monom&);
	Polynom& operator-=(const Monom&);
	Polynom& operator*=(const Monom&); 

	Polynom operator+(const Polynom&);
	Polynom operator-(const Polynom&);
	Polynom operator*(const Polynom&);

	Polynom& operator+=(const Polynom&);
	Polynom& operator-=(const Polynom&);
	Polynom& operator*=(const Polynom&);

	Polynom operator-() const;

	Polynom& operator=(const Polynom&);

	bool operator==(const Polynom&) const;

	friend ostream& operator<<(ostream&, const Polynom&);
	friend istream& operator>>(istream&, Polynom&);
};

void Polynom::Parse(const string& _str) {
	if (_str[0] == '+') throw exception("Invalid polynom");
	if (_str[_str.length() - 1] == '+' || _str[_str.length() - 1] == '-') throw exception("Invalid polynom");
	for (int i = 0; i < _str.length(); i++)
		if (_str[i] == ' ') throw exception("Invalid polynom");
	for (int i = 0; i < _str.length() - 1; i++) 
		if (_str[i] == '+' && _str[i + 1] == '+' ||
			_str[i] == '+' && _str[i + 1] == '-' || 
			_str[i] == '-' && _str[i + 1] == '+' || 
			_str[i] == '-' && _str[i + 1] == '-' ||
			_str[i] == '*' && _str[i + 1] == '*' || 
			_str[i] == '*' && _str[i + 1] == '^' || 
			_str[i] == '^' && _str[i + 1] == '*' || 
			_str[i] == '^' && _str[i + 1] == '^' || 
			_str[i] == '+' && _str[i + 1] == '*' || 
			_str[i] == '+' && _str[i + 1] == '^' || 
			_str[i] == '*' && _str[i + 1] == '+' || 
			_str[i] == '^' && _str[i + 1] == '+' || 
			_str[i] == '-' && _str[i + 1] == '*' || 
			_str[i] == '-' && _str[i + 1] == '^' || 
			_str[i] == '*' && _str[i + 1] == '-' || 
			_str[i] == '^' && _str[i + 1] == '-' ) throw exception("Invalid polynom");
	for (int i = 0; i < _str.length() - 1; i++)
		if (_str[i] == '^' &&
			(_str[i + 1] == 'x' || _str[i + 1] == 'y' || _str[i + 1] == 'z')) throw exception("Invalid polynom");
	for (int i = 0; i < _str.length() - 2; i++)
		if (_str[i] == '^' &&
			(_str[i + 2] != 'x' && _str[i + 2] != 'y' && _str[i + 2] != 'z' && _str[i + 2] != '+' && _str[i + 2] != '-' && _str[i + 2] != '*')) throw exception("Invalid polynom");
} 

Polynom::Polynom() {
	monoms = new TList<double, unsigned int, Monom>;
}

Polynom::Polynom(const Polynom& _polynom) {
	monoms = new TList<double, unsigned int, Monom>(*_polynom.monoms);
}

Polynom::Polynom(const string& str) {
	Parse(str);
	monoms = new TList<double, unsigned int, Monom>;
	int i = 0;
	while (i < str.length()) {
		string _monom;
		if (str[i] == '-') {
			_monom = str[i];
			i++;
		}
		if (str[i] == '+') i++;
		while (str[i] != '+' && str[i] != '-' && i < str.length()) {
			_monom += str[i];
			i++;
		}
		Monom monom(_monom);
		*this += monom;
		monoms->Reset();
	}
}

Polynom::~Polynom() {
	delete monoms;
}

Polynom Polynom::operator+(const Monom& _monom) {
	Polynom result(*this);
	result.monoms->Reset();
	unsigned int _bkey = 0;
	while (!result.monoms->IsEnded() && (*result.monoms->pCurr < _monom || *result.monoms->pCurr == _monom)) result.monoms->Next();
	if (result.monoms->IsEnded())
		result.monoms->Back(_monom.key, _monom.pData);
	else if (*result.monoms->pCurr > _monom) {
		_bkey = result.monoms->pCurr->key;
		result.monoms->InsertBefore(_monom.key, _monom.pData, _bkey);
	}
	else if (*result.monoms->pCurr == _monom) {
		*result.monoms->pCurr = *result.monoms->pCurr + _monom;
		if (result.monoms->pCurr->pData == 0) result.monoms->Remove(_monom.key);
	}
	result.monoms->Reset();
	return result;
}

Polynom Polynom::operator-(const Monom& _monom) {
	return *this + (-_monom);
}

Polynom Polynom::operator*(const Monom& _monom) {
	Polynom result(*this);
	result.monoms->Reset();
	while (!result.monoms->IsEnded()) {
		*result.monoms->pCurr = *result.monoms->pCurr * _monom;
		result.monoms->Next();
	}
	result.monoms->Reset();
	return result;
}

Polynom& Polynom::operator+=(const Monom& _monom) {
	Polynom copy(*this);
	*this = copy + _monom;
	return *this;
}

Polynom& Polynom::operator-=(const Monom& _monom) {
	Polynom copy(*this);
	*this = copy - _monom;
	return *this;
}

Polynom& Polynom::operator*=(const Monom& _monom) {
	Polynom copy(*this);
	*this = copy * _monom;
	return *this;
}

Polynom Polynom::operator+(const Polynom& _polynom) {
	Polynom result;
	monoms->Reset();
	_polynom.monoms->Reset();
	while (!monoms->IsEnded() && !_polynom.monoms->IsEnded()) {
		if (*monoms->pCurr < *_polynom.monoms->pCurr) {
			result.monoms->Back(monoms->pCurr->key, monoms->pCurr->pData);
			result.monoms->Reset();
			monoms->Next();
		}
		else if (*monoms->pCurr > *_polynom.monoms->pCurr) {
			result.monoms->Back(_polynom.monoms->pCurr->key, _polynom.monoms->pCurr->pData);
			result.monoms->Reset();
			_polynom.monoms->Next();
		}
		else if (*monoms->pCurr == *_polynom.monoms->pCurr) {
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
		result = result + (*this * *_polynom.monoms->pCurr);
		_polynom.monoms->Next();
	}
	return result;
}

Polynom& Polynom::operator+=(const Polynom& _polynom) {
	Polynom copy(*this);
	*this = copy + _polynom;
	return *this;
}

Polynom& Polynom::operator-=(const Polynom& _polynom) {
	Polynom copy(*this);
	*this = copy - _polynom;
	return *this;
}

Polynom& Polynom::operator*=(const Polynom& _polynom) {
	Polynom copy(*this);
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
	monoms = new TList<double, unsigned int, Monom>(*(_polynom.monoms));
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

ostream& operator<<(ostream& out, const Polynom& _polynom) {
	_polynom.monoms->Reset();
	if (_polynom.monoms->pCurr->pData > 0)
		out << _polynom.monoms->pCurr->pData;
	if (_polynom.monoms->pCurr->key / 100 == 1) out << "*x";
	if (_polynom.monoms->pCurr->key / 100 != 0 && _polynom.monoms->pCurr->key / 100 != 1) out << "*x^" << _polynom.monoms->pCurr->key / 100;
	if (_polynom.monoms->pCurr->key % 100 / 10 == 1) out << "*y";
	if (_polynom.monoms->pCurr->key % 100 / 10 != 0 && _polynom.monoms->pCurr->key % 100 / 10 != 1) out << "*y^" << _polynom.monoms->pCurr->key % 100 / 10;
	if (_polynom.monoms->pCurr->key % 10 == 1) out << "*z";
	if (_polynom.monoms->pCurr->key % 10 != 0 && _polynom.monoms->pCurr->key % 10 != 1) out << "*z^" << _polynom.monoms->pCurr->key % 10;
	_polynom.monoms->Next();
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

istream& operator>>(istream& in, Polynom& _polynom) {
	delete _polynom.monoms;
	_polynom.monoms = new TList<double, unsigned int, Monom>;
	Polynom PolyParse;
	string str;
	getline(in, str);
	PolyParse.Parse(str);
	int i = 0;
	while (i < str.length()) {
		string _monom;
		if (str[i] == '-') {
			_monom = str[i];
			i++;
		}
		if (str[i] == '+') i++;
		while (str[i] != '+' && str[i] != '-' && i < str.length()) {
			_monom += str[i];
			i++;
		}
		Monom monom(_monom);
		_polynom += monom;
		_polynom.monoms->Reset();
	}
	return in;
}