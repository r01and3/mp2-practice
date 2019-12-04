#include "List.h"

void main() {
	TList<int, int> Lt1;
	int a[1] = { 2 };
	Lt1.Push(1, a);
	cout << Lt1;
	Lt1.Push(3, a);
	cout << Lt1;
	Lt1.Remove(3);
	cout << Lt1;
}