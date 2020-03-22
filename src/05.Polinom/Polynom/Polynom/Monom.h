#pragma once
#include "TNode.h"
#include <string>
 
template<>
class TNode<double, unsigned int> {
public:
	unsigned int key;
	double pData;
	TNode* pNext;

	TNode(const TNode&);
	TNode(unsigned int, double, TNode* _monom = 0);
	TNode(const string&);
	~TNode();

	TNode operator*(double);

	TNode operator+(const TNode&);
	TNode operator-(const TNode&);
	TNode operator*(const TNode&);

	TNode operator-() const;

	TNode& operator=(const TNode&);

	bool operator>(const TNode&) const;
	bool operator<(const TNode&) const;
	bool operator==(const TNode&) const;
	bool operator!=(const TNode&) const;
};

typedef TNode<double, unsigned int> Monom;