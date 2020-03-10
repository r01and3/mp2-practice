#pragma once
#include "TNode.h"

using namespace std;

template<class TData, class TKey, class TListNode>
class TList {
protected:
	TListNode* pFirst;
	TListNode* pPrev;
	TListNode* pCurr;
	TListNode* pNext;
public:
	TList();
	TList(TListNode*);
	TList(const TList&);
	~TList();

	bool IsEnded() const;
	void Next();
	void Reset();

	TListNode* Search(TKey);
	void Back(TKey, TData);
	void Push(TKey, TData);
	void InsertAfter(TKey, TData, TKey);
	void InsertBefore(TKey, TData, TKey);
	void Remove(TKey);
	TListNode* ReturnCurrent() const;
	friend ostream& operator << (ostream& out, TList<TData, TKey, TListNode>& _list) {
		if (_list.pFirst == 0) cout << "List is empty" << endl;
		TListNode* fpCurr = _list.pCurr;
		TListNode* fpPrev = _list.pPrev;
		TListNode* fpNext = _list.pNext;
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

template<class TData, class TKey, class TListNode>
TList<TData, TKey, TListNode>::TList() {
	pFirst = 0;
	pPrev = 0;
	pCurr = 0;
	pNext = 0;
}

template<class TData, class TKey, class TListNode>
TList<TData, TKey, TListNode>::TList(TListNode* list) {
	if (list == 0) throw "Empty link";
	pFirst = new TListNode(*list);
	TListNode* node = list;
	TListNode* tmp = pFirst;
	while (tmp->pNext != 0) {
		node->pNext = TListNode(*tmp->pNext);
		node = node->pNext;
		tmp = tmp->pNext;
	}
	pPrev = 0;
	pCurr = pFirst;
	pNext = pCurr->pNext;
}

template<class TData, class TKey, class TListNode>
TList<TData, TKey, TListNode>::TList(const TList<TData, TKey, TListNode>& list) {
	if (list.pFirst == 0) {
		pFirst = 0;
		pPrev = 0;
		pCurr = 0;
		pNext = 0;
		return;
	}
	pFirst = new TListNode(*list.pFirst);
	TListNode* node = pFirst;
	TListNode* tmp = list.pFirst;
	while (tmp->pNext != 0) {
		node->pNext = new TListNode(*(tmp->pNext));
		node = node->pNext;
		tmp = tmp->pNext;
	}
	pCurr = pFirst;
	pPrev = 0;
	pNext = pCurr->pNext;
}

template<class TData, class TKey, class TListNode>
TList<TData, TKey, TListNode>::~TList() {
	TListNode* del = pFirst;
	while (del != 0) {
		TListNode* tmp = del->pNext;
		delete del;
		del = tmp;
	}
}

template<class TData, class TKey, class TListNode>
void TList<TData, TKey, TListNode>::Reset() {
	pPrev = 0;
	pCurr = pFirst;
	if (pFirst != 0)
		pNext = pFirst->pNext;
	else
		pNext = 0;
}

template<class TData, class TKey, class TListNode>
void TList<TData, TKey, TListNode>::Next() {
	if (IsEnded()) throw "List is ended";
	pPrev = pCurr;
	pCurr = pNext;
	if (pNext != 0)
		pNext = pNext->pNext;
	else pNext = 0;
}

template<class TData, class TKey, class TListNode>
bool TList<TData, TKey, TListNode>::IsEnded() const {
	return (pCurr == 0);
}

template<class TData, class TKey, class TListNode>
TListNode* TList<TData, TKey, TListNode>::Search(TKey key) {
	if (pFirst == 0) return 0;

	TListNode* fpCurr = pCurr;
	TListNode* fpPrev = pPrev;
	TListNode* fpNext = pNext;

	Reset();
	while ((!IsEnded()) && (pCurr->key != key))
		Next();
	if (pCurr == 0) {
		pPrev = fpPrev;
		pCurr = fpCurr;
		pNext = fpNext;
		return 0;
	}
	TListNode* cpCurr = pCurr;

	pPrev = fpPrev;
	pCurr = fpCurr;
	pNext = fpNext;

	return cpCurr;
}

template<class TData, class TKey, class TListNode>
void TList<TData, TKey, TListNode>::Push(TKey _key, TData _data) {
	if (pFirst == 0) {
		pFirst = new TListNode(_key, _data);
		pCurr = pFirst;
		return;
	}

	pFirst = new TListNode(_key, _data, pCurr);

	if (pCurr == pFirst->pNext) pPrev = pFirst;
}

template<class TData, class TKey, class TListNode>
void TList<TData, TKey, TListNode>::Back(TKey _key, TData _data) {
	if (pFirst == 0) {
		pFirst = new TListNode(_key, _data);
		pCurr = pFirst;
		return;
	}
	TListNode* fpCurr = pCurr;
	TListNode* fpPrev = pPrev;
	TListNode* fpNext = pNext;
	while (!IsEnded())
		Next();
	pPrev->pNext = new TListNode(_key, _data);

	if (fpCurr == pPrev) {
		pNext = pPrev->pNext;
		pPrev = fpPrev;
		pCurr = fpCurr;
	}
	else if (fpCurr == 0) {
		pPrev = pPrev->pNext;
		pCurr = fpCurr;
		pNext = fpNext;
	}
}

template<class TData, class TKey, class TListNode>
void TList<TData, TKey, TListNode>::InsertAfter(TKey ikey, TData data, TKey akey) {
	if (pFirst == 0) {
		pFirst = new TListNode(ikey, data);
		pCurr = pFirst;
		return;
	}
	TListNode* fpCurr = pCurr;
	TListNode* fpPrev = pPrev;
	TListNode* fpNext = pNext;

	Reset();
	while ((!IsEnded()) && (pCurr->key != akey))
		Next();
	if (pCurr == 0)  throw "Item not listed";
	TListNode* ins = new TListNode(ikey, data, pNext);

	pCurr->pNext = ins;

	if (pCurr == fpCurr) {
		pNext = pCurr->pNext;
		pPrev = fpPrev;
	}
	else if (pNext == fpCurr) {
		pPrev = pCurr->pNext;
		pCurr = fpCurr;
		pNext = fpNext;
	}
	else {
		pPrev = fpPrev;
		pCurr = fpCurr;
		pNext = fpNext;
	}
}

template<class TData, class TKey, class TListNode>
void TList<TData, TKey, TListNode>::InsertBefore(TKey ikey, TData data, TKey bkey) {
	if (pFirst == 0) {
		pFirst = new TListNode(ikey, data);
		pCurr = pFirst;
		return;
	}
	if (pFirst->key == bkey) {
		Push(ikey, data);
		return;
	}
	TListNode* fpCurr = pCurr;
	TListNode* fpPrev = pPrev;
	TListNode* fpNext = pNext;

	Reset();
	while ((!IsEnded()) && (pCurr->key != bkey))
		Next();
	if (pCurr == 0) throw "Item not listed";
	TListNode* ins = new TListNode(ikey, data, pCurr);

	pPrev->pNext = ins;

	if (pCurr == fpCurr) {
		pPrev = pPrev->pNext;
		pNext = fpNext;
	}
	else if (pPrev == fpCurr) {
		pNext = pPrev->pNext;
		pPrev = fpPrev;
		pCurr = fpCurr;
	}
	else {
		pPrev = fpPrev;
		pCurr = fpCurr;
		pNext = fpNext;
	}
}

template<class TData, class TKey, class TListNode>
void TList<TData, TKey, TListNode>::Remove(TKey dkey) {
	if (pFirst == 0) throw "List is empty";
	TListNode* fpCurr = pCurr;
	TListNode* fpPrev = pPrev;
	TListNode* fpNext = pNext;

	Reset();
	while ((!IsEnded()) && (pCurr->key != dkey))
		Next();
	if (pCurr == 0) throw "Item not listed";
	if (pCurr == pFirst) {
		if (fpCurr == pFirst) {
			delete pFirst;
			pFirst = pNext;
			pCurr = pFirst;
			pNext = pCurr->pNext;
		}
		else
		{
			delete pFirst;
			pFirst = pNext;
			pCurr = fpCurr;
			pPrev = fpPrev;
			pNext = fpNext;
		}
	}
	else if (pCurr == fpCurr) {
		pPrev->pNext = pNext;
		delete pCurr;
		if (fpNext == 0) pNext = 0;
		pNext = fpNext->pNext;
		pPrev = fpPrev;
		pCurr = fpNext;
	}
	else if (pPrev == fpCurr) {
		pPrev->pNext = pNext;
		delete pCurr;
		pNext = pPrev->pNext;
		pPrev = fpPrev;
		pCurr = fpCurr;
	}
	else if (pNext == fpCurr) {
		pPrev->pNext = pNext;
		delete pCurr;
		pCurr = fpCurr;
		pNext = fpNext;
	}
	else {
		pPrev->pNext = pNext;
		delete pCurr;
		pCurr = fpCurr;
		pPrev = fpPrev;
		pNext = fpNext;
	}
}

template<class TData, class TKey, class TListNode>
TListNode* TList<TData, TKey, TListNode>::ReturnCurrent() const{
	return pCurr;
}