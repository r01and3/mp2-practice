#pragma once
#include "Stack.h"
#include <string.h>

class Converter {
protected:
	TStack<string> operators;
	TStack<string> operands;
	double* operand_values;
	char* source_expression;
public:
	void input_source_expression();
	void input_operand_values();
	double expression_evaluation();
	void postfix_form();
	void output_postfix_form();
};
