#pragma once
#include <iostream>

using namespace std;

template<class TData, class TKey>
class TNode {
public:
	TData pData;
	TKey key;
	TNode* pNext;
public:
	TNode(const TNode&);
	TNode(TKey, TData, TNode* _node = 0);
	bool operator!=(const TNode&) const;
	friend ostream& operator << (ostream& out, TNode<TData, TKey>& _node) {
		out << _node.key << " " << *_node.pData << endl;
		return out;
	}
};

template<class TData, class TKey>
TNode<TData, TKey>::TNode(const TNode<TData, TKey>& copy) {
	pData = copy.pData;
	key = copy.key;
	pNext = copy.pNext;
}

template<class TData, class TKey>
TNode<TData, TKey>::TNode(TKey _key, TData _data, TNode* _pNext) {
	pData = _data;
	key = _key;
	pNext = _pNext;
}

template<class TData, class TKey>
bool TNode<TData, TKey>::operator!=(const TNode& _node) const{
	if (pData == _node.pData && key == _node.key) return false;
	return true;
}