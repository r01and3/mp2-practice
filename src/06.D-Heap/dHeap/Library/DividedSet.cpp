#include "dividedSet.h"

dividedSet::dividedSet(int _size) {

	if (_size <= 0) throw "Invalid data";

	size = _size;
	sets = new int[size];

	for (int i = 0; i < size; i++)
		sets[i] = i;

}

dividedSet::dividedSet(int _size, int* _sets) {

	if (_size <= 0 || _sets == nullptr) throw "Invalid data";

	size = _size;
	sets = new int[size];

	for (int i = 0; i < size; i++)
		sets[i] = _sets[i];

}

dividedSet::dividedSet(const dividedSet& _mSets) {

	size = _mSets.size;
	sets = new int[size];

	for (int i = 0; i < size; i++)
		sets[i] = _mSets.sets[i];

}

dividedSet::~dividedSet() {
	delete[] sets;
}

void dividedSet::combine(int a, int b) {

	if (a >= size || b >= size) throw "Invalid data";

	for (int i = 0; i < size; i++)
		if (sets[i] == b)
			sets[i] = a;

}

int dividedSet::find(int a) {

	if (a >= size) throw "Invalid data";

	return sets[a];

}