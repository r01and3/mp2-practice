#pragma once
#include "Stack.h"

class Converter {
protected:
	TStack<char> operators;
	TStack<char> operands;
	double* operand_values;
	char* source_expression;
public:
	void input_source_expression();
	void input_operand_values();
	double expression_evaluation();
	void postfix_form();
	void output_postfix_form();
};
