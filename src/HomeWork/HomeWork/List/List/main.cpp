#include "List.h"

void main() {
	TList<int, int> Lt1;
	int a[1] = { 2 };
	Lt1.Push(1, a);

	cout << "Copy constructor test" << endl;
	TList<int, int> Lt2(Lt1);
	TList<int, int> Lt3(Lt1);
	cout << Lt2;
	cout << Lt3;

	cout << "Basic function test" << endl;
	cout << "Push test" << endl;
	Lt2.Push(3, a);
	Lt3.Push(4, a);
	cout << "Lt2:" << endl;
	cout << Lt2;
	cout << "Lt3:" << endl;
	cout << Lt3;

	cout << "Back test" << endl;
	Lt2.Back(5, a);
	Lt3.Back(6, a);
	cout << "Lt2:" << endl;
	cout << Lt2;
	cout << "Lt3:" << endl;
	cout << Lt3;

	cout << "Insert after test" << endl;
	Lt2.InsertAfter(7, a, 1);
	Lt3.InsertAfter(8, a, 3);
	cout << "Lt2:" << endl;
	cout << Lt2;
	cout << "Lt3:" << endl;
	cout << Lt3;

	cout << "Insert before test" << endl;
	Lt2.InsertBefore(9, a, 8);
	Lt3.InsertBefore(10, a, 6);
	cout << "Lt2:" << endl;
	cout << Lt2;
	cout << "Lt3:" << endl;
	cout << Lt3;

	cout << "Search test" << endl;
	if (Lt2.Search(9) != 0)
		cout << *Lt2.Search(9);
	if (Lt3.Search(10) != 0)
		cout << *Lt3.Search(10);
	
	cout << "Remove test" << endl;
	Lt2.Remove(1);
	Lt3.Remove(3);
	cout << "Lt2:" << endl;
	cout << Lt2;
	cout << "Lt3:" << endl;
	cout << Lt3;

	cout << "Exception situations" << endl;
	TList<int, int> Lt4;
	cout << "Attempt to withdraw Lt4: " << Lt4;
	try {
		Lt4.Remove(2);
	}
	catch (char* c) {
		cout << c << endl;
	}
	try {
		Lt4.Search(2);
	}
	catch (char* c) {
		cout << c << endl;
	}
}