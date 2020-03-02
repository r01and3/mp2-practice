#include "Monom.h"
#include "TList.h"
#include "Polynom.h"

void main() {
	try {
		string str_1 = "2*x*y^2*z^3+3*x^3*y^2*z-4*x^4*y^4*z^4";
		string str_2 = "3*x^2*y*z^3-3*x^3*y^2*z-4*x^4*y^4*z^4";
		Polynom polynom_1(str_1);
		Polynom polynom_2(str_2);
		cout << polynom_1 << endl;
		cout << polynom_2 << endl;
		Polynom polynom_o;
		polynom_o = polynom_1 + polynom_2;
		cout << polynom_o << endl;
		polynom_o = polynom_1 - polynom_2;
		cout << polynom_o << endl;
		polynom_o = polynom_1 * polynom_2;
		cout << polynom_o << endl;
	}
	catch (const exception & e) {
		cout << e.what() << endl;
	}
}