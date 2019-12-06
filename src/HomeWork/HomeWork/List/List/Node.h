#pragma once
#include <iostream>

using namespace std;

template<class TData, class TKey>
class TNode {
public:
	TData* pData;
	TKey key;
	TNode* pNext;
public:
	TNode(const TNode&);
	TNode(TKey, TData*);
	friend ostream& operator << (ostream &out, TNode<TData, TKey> &_node) {
		out << _node.key << " " << *_node.pData << endl;
		return out;
	}
};

template<class TData, class TKey>
TNode<TData, TKey>::TNode(const TNode<TData, TKey> &copy) {
	pData = copy.pData;
	key = copy.key;
	pNext = copy.pNext;
}

template<class TData, class TKey>
TNode<TData, TKey>::TNode(TKey _key, TData* _data) {
	pData = _data;
	key = _key;
	pNext = 0;
}