#pragma once
#include "TList.h"
#include "Monom.h"

class Polynom {
private:
	TList<double, unsigned int>* monoms;
public:
	Polynom();
	Polynom(const Polynom&);
	Polynom(const string);
	~Polynom();

	Polynom operator+(double);
	Polynom operator-(double);
	Polynom operator*(double);

	Polynom operator+(const Polynom&);
	/*Polynom operator-(const Polynom&);
	Polynom operator*(const Polynom&);

	Polynom& operator=(const Polynom&);

	bool operator==(const Polynom&) const;*/
};