#pragma once
#include "Stack.h"
#include <string>

using namespace std;

static class Converter {
private:
	static bool Priority(char, char);
	static double Calculator(double, double, char);
public:
	static string CreatePostFixForm(const string&);
	static double Calculate(const string&, double*, char*, int);
	static void GetValueOperands(const string&, double*&, char*&, int&);
};