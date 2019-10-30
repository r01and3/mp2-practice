#include "Converter.h"
#include <iostream>

void Converter::create_postfix_form() {
	TStack<char> operators(se.length());
	TStack<char> operands(se.length());
	operandsk = 0;
	for (int i = 0; i < se.length(); i++) {
		bool b = (se[i] == '+') || (se[i] == '-') || (se[i] == '*') || (se[i] == '/') || (se[i] == '(') || (se[i] == ')');
		if (!b) {
			operands.Push(se[i]);
			operandsk++;
		}
		if (b) {
			if (se[i] == ')') {
				while (operators.TopElems() != '(')
					operands.Push(operators.Pop());
				operators.Pop();
				continue;
			}
			if (priority(se[i], operators.TopElems())) {
				while((operators.TopElems() != ')') && !(operators.IsEmpty()))
					operands.Push(operators.Pop());
				operators.Push(se[i]);
				continue;
			}
			operators.Push(se[i]);
		}
	}
	while(!(operators.IsEmpty()))
		operands.Push(operators.Pop());
	PostFixForm = operands;
}

bool Converter::priority(char a, char b) const {
	if ((a == '+' || a == '-') && (b == '*' || b == '/')) return true;
	if ((a == '*' || a == '/') && (b == '*' || b == '/')) return true;
	return false;
}

void Converter::input_source_expression() {
	cin >> se;
}

void Converter::out_postfix_form() {
	TStack<char> copy = PostFixForm;
	string out;
	string aout;
	while (copy.IsEmpty()) out.append(copy.Pop());
	//reverse(out.begin(), out.end());
	cout << out;
}

double Converter::calculator(double a, double b, char o) {
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

double Converter::expression_count() {
	TStack<double> s(se.length());
	for (int i = 0; i < operandsk; i++) s.Push(operand_values[i]);
	while (!PostFixForm.IsEmpty()) {
		if ((PostFixForm.TopElems() == '+') || (PostFixForm.TopElems() == '-') || (PostFixForm.TopElems() == '*') || (PostFixForm.TopElems() == '/')) {
			double a = s.Pop();
			double b = s.Pop();
			s.Push(calculator(a, b, PostFixForm.Pop()));
			continue;
		}
		PostFixForm.Pop();
	}
	return s.Pop();
}

void Converter::input_operand_values() {
	operand_values = new double[operandsk];
	for (int i = 0; i < operandsk; i++)
		cin >> operand_values[i];
}