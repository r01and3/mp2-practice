#include "Monom.h"
#include "TList.h"
#include "Polynom.h"

void main() {
	Monom monom1(890, 12);
	Monom monom2(106, 30);
	Monom monom3 = monom1 + monom2;
	string str = "2*x^4*y^5*z^6+5*x^3*y^7-2*y^4*x^5";
	Polynom monom4(str);
	Polynom poly1;
	Polynom poly2;
	poly1 = poly1 + monom1;
	poly1 = poly1 - monom2;
	poly2 = poly2 + monom3;
	poly1 = poly1 + poly2;
	poly1 = poly1 * poly2;
	cout << (monom1 > monom2);
}