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
				while((!priority(operators.TopElems(), se[i])) && !(operators.IsEmpty()) && (operators.TopElems() != '('))
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
	return false;
}

void Converter::input_source_expression() {
	cin >> se;
}

void Converter::out_postfix_form() {
	TStack<char> copy = PostFixForm;
	TStack<char> rcopy = PostFixForm;
	while (!rcopy.IsEmpty()) rcopy.Pop();
	while (!copy.IsEmpty()) rcopy.Push(copy.Pop());
	while (!rcopy.IsEmpty()) cout << rcopy.Pop();

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
	TStack<char> a(PostFixForm.size);
	int i = 0;
	while(!PostFixForm.IsEmpty()) a.Push(PostFixForm.Pop());
	while (!a.IsEmpty()) {
		if ((a.TopElems() == '+') || (a.TopElems() == '-') || (a.TopElems() == '*') || (a.TopElems() == '/')) {
			double b = s.Pop();
			double c = s.Pop();
			s.Push(calculator(c, b, a.Pop()));
			continue;
		}
		else {
			s.Push(operand_values[i]);
			i++;
		}
		a.Pop();
	}
	return s.Pop();
}

void Converter::input_operand_values() {
	operand_values = new double[operandsk];
	for (int i = 0; i < operandsk; i++)
		cin >> operand_values[i];
}