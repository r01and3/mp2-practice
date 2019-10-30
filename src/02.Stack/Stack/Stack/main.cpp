#include "Converter.h"
#include "Stack.h"
#include <iostream>

void main() {
	Converter c;
	c.input_source_expression();
	c.create_postfix_form();
	c.out_postfix_form();
	c.input_operand_values();
	cout << c.expression_count();
}