#include "Converter.h"
#include <iostream>

string Converter::CreatePostFixForm(const string &_str) {
	int l = 0;
	int r = 0;
	for (int i = 0; i < _str.length(); i++) {
		if (_str[i] == '(') l++;
		if (_str[i] == ')') r++;
	}
	if (l != r) throw "Invalid expression";
	if ((_str[0] == '+') || (_str[0] == '-') || (_str[0] == '*') || (_str[0] == '/')) throw "Invalid expression";
	if (_str[_str.length() - 1] == '+' || _str[_str.length() - 1] == '-' || _str[_str.length() - 1] == '*' || _str[_str.length() - 1] == '/') throw "Invalid expression";
	for (int i = 0; i < _str.length(); i++)
		if (_str[i] == '0' || _str[i] == '1' || _str[i] == '2' || _str[i] == '3' || _str[i] == '4' || _str[i] == '5' || _str[i] == '6' || _str[i] == '7' || _str[i] == '8' || _str[i] == '9')
			throw "Invalid expression";
	for (int i = 1; i < _str.length(); i++)
		if ((_str[i] != '+') && (_str[i] != '-') && (_str[i] != '*') && (_str[i] != '/') && (_str[i] != '(') && (_str[i] != ')') && (_str[i - 1] != '+') && (_str[i - 1] != '-') && (_str[i - 1] != '*') && (_str[i - 1] != '/') && (_str[i - 1] != '(') && (_str[i - 1] != ')'))
			throw "Invalid expression";
	for (int i = 1; i < _str.length(); i++)
		if (((_str[i] == '+') || (_str[i] == '-') || (_str[i] == '*') || (_str[i] == '/')) && ((_str[i - 1] == '+') || (_str[i - 1] == '-') || (_str[i - 1] == '*') || (_str[i - 1] == '/')))
			throw "Invalid expression";
	TStack<double> operands(_str.length());
	TStack<double> operators(_str.length());
	string PostFixForm = "";
	for (int i = 0; i < _str.length(); i++) {
		bool b = (_str[i] == '+') || (_str[i] == '-') || (_str[i] == '*') || (_str[i] == '/') || (_str[i] == '(') || (_str[i] == ')');
		if (!b) {
			operands.Push(_str[i]);
			continue;
		}
		if (b) {
			if (_str[i] == ')') {
				while (operators.TopElems() != '(')
					operands.Push(operators.Pop());
				operators.Pop();
				continue;
			}
			if (Priority(_str[i], operators.TopElems())) {
				while ((Priority(_str[i], operators.TopElems())) && !(operators.IsEmpty()) && (operators.TopElems() != '('))
					operands.Push(operators.Pop());
				operators.Push(_str[i]);
				continue;
			}
			operators.Push(_str[i]);
		}
	}
	while (!operators.IsEmpty())
		operands.Push(operators.Pop());
	while (!operands.IsEmpty())
		operators.Push(operands.Pop());
	while (!operators.IsEmpty())
		PostFixForm += operators.Pop();
	return PostFixForm;
}

double Converter::Calculate(const string &_str, double* VO, int k) {
	TStack<double> e(k);
	int l = _str.length();
	int j = 0;
	for (int i = 0; i < l; i++) {
		if (_str[i] == '+' || _str[i] == '-' || _str[i] == '*' || _str[i] == '/') {
			double a = e.Pop();
			double b = e.Pop();
			e.Push(Calculator(b, a, _str[i]));
		}
		else {
			e.Push(VO[j]);
			j++;
		}
	}
	return e.Pop();
}


bool Converter::Priority(char a, char b) {
	if ((a == '*' || a == '/') && (b == '*' || b == '/')) return true;
	if ((a == '+' || a == '-') && (b == '+' || b == '-')) return true;
	if ((a == '+' || a == '-') && (b == '*' || b == '/')) return true;
	return false;
}

double Converter::Calculator(double a, double b, char o) {
	switch (o)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	}
}

double* Converter::GetValueOperands(const string &_str, int *ki) {
	(*ki)--;
	for (int i = 0; i < _str.length(); i++)
		if (_str[i] != '*' && _str[i] != '/' && _str[i] != '+' && _str[i] != '-')
			(*ki)++;
	double *VO = new double[(*ki)];
	char* B = new char[(*ki)];
	int c = 0;
	int f = 0;
	int g = 0;
	for (int i = 0; i < _str.length(); i++) {
		if (_str[i] != '*' && _str[i] != '/' && _str[i] != '+' && _str[i] != '-') {
			for (int j = 0; j < f; j++) {
				if (B[j] == _str[i]) {
					B[f] = _str[i];
					f++;
					VO[c] = VO[j];
					c++;
					g = 1;
					break;
				}
			}
			if (g == 0) {
				B[f] = _str[i];
				f++;
				cin >> VO[c];
				c++;
			}
		}
	}
	return VO;
}