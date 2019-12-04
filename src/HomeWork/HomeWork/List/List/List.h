#pragma once
#include <iostream>
#include "Node.h"

using namespace std;

template<class TData, class TKey>
class TList {
private:
	TNode<TData, TKey>* pFirst;
	TNode<TData, TKey>* pPrev;
	TNode<TData, TKey>* pCurr;
	TNode<TData, TKey>* pNext;
public:
	TList();
	TList(TNode<TData, TKey>*);
	TList(const TList&);
	~TList();
	bool IsEnded() const;
	void Next();
	void Reset();
	TNode<TData, TKey>* Search(TKey);
	void Back(TKey, TData*);
	void Push(TKey, TData*);
	void InsertAfter(TKey, TData*, TKey);
	void InsertBefore(TKey, TData*, TKey);
	void Remove(TKey);
	friend ostream& operator << (ostream &out, TList<TData, TKey> &_list) {
		TNode<TData, TKey>* fpCurr = _list.pCurr;
		TNode<TData, TKey>* fpPrev = _list.pPrev;
		TNode<TData, TKey>* fpNext = _list.pNext;
		_list.Reset();
		while (!_list.IsEnded()) {
			out << _list.pCurr->key << "  " << *_list.pCurr->pData << endl;
			_list.Next();
		}
		_list.pCurr = fpCurr;
		_list.pPrev = fpPrev;
		_list.pNext = fpNext;
		return out;
	}
};

template<class TData, class TKey>
TList<TData, TKey>::TList() {
	pFirst = 0;
	pPrev = 0;
	pCurr = 0;
	pNext = 0;
}

template<class TData, class TKey>
TList<TData, TKey>::TList(TNode<TData, TKey>* list) {
	pFirst = new TNode<TData, TKey>(list);
	pCurr = pFirst;
	pPrev = 0;
	pNext = pFirts->pNext;
}

template<class TData, class TKey>
TList<TData, TKey>::TList(const TList<TData, TKey> &list) {
	pFirst = new TNode<TData, TKey>(list.pFirst);
	list.Reset();
	TNode<TData, TKey>* node = pFirst;
	list.Next();
	while (_list.IsEnded()) {
		node->pNext = new TNode<TData, TKey>(list.pCurr);
		node = node->pNext;
		list.Next();
	}
	Reset();
}

template<class TData, class TKey>
TList<TData, TKey>::~TList() {
	TNode<TData, TKey>* del = pFirst;
	TNode<TData, TKey>* tmp;
	while (del != 0) {
		tmp = del->pNext;
		delete del;
		del = tmp;
	}
}

template<class TData, class TKey>
void TList<TData, TKey>::Reset() {
	pPrev = 0;
	pCurr = pFirst;
	if (pFirst != 0)
		pNext = pFirst->pNext;
	else	
		pNext = 0;
}

template<class TData, class TKey>
void TList<TData, TKey>::Next() {
	if (IsEnded()) throw "List is ended";
	pPrev = pCurr;
	pCurr = pNext;
	if (pNext != 0)
		pNext = pNext->pNext;
}

template<class TData, class TKey>
bool TList<TData, TKey>::IsEnded() const{
	return (pCurr == 0);
}

template<class TData, class TKey>
TNode<TData, TKey>* TList<TData, TKey>::Search(TKey key) {
	if (pFirts == 0) throw "List is empty";
	TNode<TData, TKey>* fpCurr = pCurr;
	TNode<TData, TKey>* fpPrev = pPrev;
	TNode<TData, TKey>* fpNext = pNext;
	while ((!IsEnded()) && (pCurr->key != key))
		Next();
	if (pCurr == 0) {
		cout << "Item not listed" << endl;
		return;
	}
	TNode<TData, TKey>* cpCurr = pPrev;
	pPrev = fpPrev;
	pCurr = fpCurr;
	pNext = fpNext;
	return cpCurr;
}

template<class TData, class TKey>
void TList<TData, TKey>::Push(TKey _key, TData* _data) {
	if (pFirst == 0) {
		pFirst = new TNode<TData, TKey>(_key, _data);
		pCurr = pFirst;
		return;
	}
	TNode<TData, TKey>* fpCurr = pCurr;
	TNode<TData, TKey>* fpPrev = pPrev;
	TNode<TData, TKey>* fpNext = pNext;
	Reset();
	pFirst = new TNode<TData, TKey>(_key, _data);
	pFirst->pNext = pCurr;
	pCurr = fpCurr;
	pPrev = fpPrev;
	pNext = fpNext;
}

template<class TData, class TKey>
void TList<TData, TKey>::Back(TKey _key, TData* _data) {
	if (pFirst == 0) {
		pFirst = new TNode<TData, TKey>(_key, _data);
		pCurr = pFirst;
		return;
	}
	TNode<TData, TKey>* fpCurr = pCurr;
	TNode<TData, TKey>* fpPrev = pPrev;
	TNode<TData, TKey>* fpNext = pNext;
	while (!IsEnded())
		Next();
	pPrev->pNext = new TNode<TData, TKey>(_key, _data);
	pPrev = fpPrev;
	pCurr = fpCurr;
	pNext = fpNext;
}

template<class TData, class TKey>
void TList<TData, TKey>::InsertAfter(TKey ikey, TData* data, TKey akey) {
	if (pFirst == 0) {
		pFirst = new TNode<TData, TKey>(ikey, data);
		pCurr = pFirst;
		return;
	}
	TNode<TData, TKey>* fpCurr = pCurr;
	TNode<TData, TKey>* fpPrev = pPrev;
	TNode<TData, TKey>* fpNext = pNext;
	Reset();
	while ((!IsEnded()) && (pCurr->key != akey))
		Next();
	if (pCurr == 0) {
		cout << "Item not listed" << endl;
		return;
	}
	TNode<TData, TKey>* ins = new TNode<TData, TKey>(ikey, data);
	TNode<TData, TKey>* tmp = pCurr->pNext;
	pCurr->pNext = ins;
	ins->pNext = tmp;
	pPrev = fpPrev;
	pCurr = fpCurr;
	pNext = fpNext;
}

template<class TData, class TKey>
void TList<TData, TKey>::InsertBefore(TKey ikey, TData* data, TKey bkey) {
	if (pCurr == 0) {
		pFirst = new TNode<TData, TKey>(ikey, data);
		pCurr = pFirst;
		return;
	}
	TNode<TData, TKey>* fpCurr = pCurr;
	TNode<TData, TKey>* fpPrev = pPrev;
	TNode<TData, TKey>* fpNext = pNext;
	Reset();
	while ((!IsEnded()) && (pNext->key = bkey))
		Next();
	if (pCurr == 0) {
		cout << "Item not listed" << endl;
		return;
	}
	TNode<TData, TKey>* ins = new TNode<TData, TKey>(ikey, data);
	TNode<TData, TKey>* tmp = pCurr->pNext;
	pCurr->pNext = ins;
	ins->pNext = tmp;
	pPrev = fpPrev;
	pCurr = fpCurr;
	pNext = fpNext;
}

template<class TData, class TKey>
void TList<TData, TKey>::Remove(TKey dkey) {
	if (pFirst == 0) throw "List is empty";
	TNode<TData, TKey>* fpCurr = pCurr;
	TNode<TData, TKey>* fpPrev = pPrev;
	TNode<TData, TKey>* fpNext = pNext;
	Reset();
	while ((!IsEnded()) && (pCurr->key != dkey))
		Next();
	if (pCurr == 0) {
		cout << "Item not listed" << endl;
		return;
	}
	if (pCurr == pFirst) {
		pFirst = pNext;
		return;
	}
	pPrev->pNext = pNext;
	delete pCurr;
	pCurr = fpCurr;
	pPrev = fpPrev;
	pNext = fpNext;
}

/*template<class TData, class TKey>
ostream& operator << (ostream &out, TList<TData, TKey> &_list) {
	_list.Reset();
	while (!IsEnded()) {
		out << _list.pCurr->key << "  " << _list.pCurr->pData << endl;
		_list.Next();
	}
}*/