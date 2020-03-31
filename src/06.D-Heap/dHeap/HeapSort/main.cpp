#include "HeapSort.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

void main() {

	srand(time(NULL));
	int arrSize;
	double* arr;

	cout << "Enter array size: ";
	cin >> arrSize;

	arr = new double[arrSize];

	for (int i = 0; i < arrSize; i++)
		arr[i] = rand();

	cout << "Start array " << endl;

	for (int i = 0; i < arrSize; i++)
		cout << arr[i] << endl;

	pSort<double>::Sort(arr, arrSize);

	cout << "Sort array " << endl;

	for (int i = 0; i < arrSize; i++)
		cout << arr[i] << endl;
}
