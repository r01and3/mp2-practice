#include "Converter.h"
#include "Stack.h"
#include <iostream>

using namespace std;

void main() {
	Converter c;
	string s, g;
	int f = 1;
	int* k = &f;
	cout << "Enter expression:" << endl;
	cin >> s;
	try {
		string g = c.CreatePostFixForm(s);
		cout << "Polish notation:" << endl;
		cout << g << endl;
		double *V = new double[1];
		char *B = new char[1];
		c.GetValueOperands(g, V, B, *k);
		cout << "Expression value: " << c.Calculate(g, V, B, *k) << endl;
	}
	catch (char* f) {
		cout << f << endl;
	}
}