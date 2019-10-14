#include "Vector.h"
#include "Matrix.h"

void main() {
	/*Vectors test*/
	/*Vector Constructors Test*/
	double *mv = new double[4];
	double *mvn = new double[3];
	for (int i = 0; i < 4; i++) mv[i] = i + 3;
	for (int i = 0; i < 3; i++) mvn[i] = i + 3;
	TVector<double> v1(mv, 4, 0);
	TVector<double> v2(v1);
	TVector<double> v3(4, 0);
	TVector<double> vn(3, 0);
	/*Function and Operation Test*/
	v3 = v1 + 5;
	cout << v3 << endl;
	v3 = v1 - 5;
	cout << v3 << endl;
	v3 = v1 * 5;
	cout << v3 << endl;
	try {
		v3 = v1 + vn;
		cout << v3 << endl;
	}
	catch (char* str) {
		cout << str << endl;
	}
	try {
		v3 = v1 - v2;
		cout << v3 << endl;
	}
	catch (char* str) {
		cout << str << endl;
	}
	try {
		cout << v1 * v2 << endl;
	}
	catch (char* str) {
		cout << str << endl;
	}
	int b = v1 == v2;
	cout << b << endl;
	b = v3 != v2;
	cout << b << endl;
	cout << v3[2] << endl;
	/*Matrix test*/
	/*Matrix constructors test*/
	TMatrix<double> m1(4);
	TVector<TVector<double> > v(4, 0);
	for (int i = 0; i < 4; i++) {
		TVector<double> tmp(4 - i, i);
		cin >> tmp;
		v[i] = tmp;
	}
	cout << v << endl;
	TMatrix<double> m2(v);
	TMatrix<double> m3(m2);
	/*Function and Operation Test*/
	m1 = m2 + 5;
	cout << m1 << endl;
	m1 = m2 - 5;
	cout << m1 << endl;
	m1 = m2 * 5;
	cout << m1 << endl;
	try {
		m1 = m2 + m3;
		cout << m1 << endl;
	}
	catch (char* str) {
		cout << str << endl;
	}
	try {
		m1 = m2 - m3;
		cout << m1 << endl;
	}
	catch (char* str) {
		cout << str << endl;
	}
	try {
		v3 = m2 * v2;
		cout << v3 << endl;
	}
	catch (char* str) {
		cout << str << endl;
	}
	b = m2 == m3;
	cout << b << endl;
	b = m1 != m2;
	cout << b << endl;
}