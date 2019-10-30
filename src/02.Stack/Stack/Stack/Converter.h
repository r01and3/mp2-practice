#pragma once
#include "Stack.h"
#include <string>

using namespace std;

class Converter {
public:
	TStack<char> PostFixForm;
	double* operand_values;
	string se;
	int operandsk;
public:
	void input_source_expression();
	void input_operand_values();
	void create_postfix_form();
	void out_postfix_form();
	bool priority(char, char) const;
	double calculator(double, double, char);
	double expression_count();
};