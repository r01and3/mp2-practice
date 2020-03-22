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