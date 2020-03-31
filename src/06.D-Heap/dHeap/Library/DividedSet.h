#pragma once

class dividedSet {
private:
	int size;
	int* sets;
public:
	dividedSet(int);
	dividedSet(int, int*);
	dividedSet(const dividedSet&);
	~dividedSet();

	void combine(int, int);
	int find(int);
};