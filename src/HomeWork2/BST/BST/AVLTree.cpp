#include "AVLTree.h"

void AVLTree::turnRight(AVLTreeNode* _node) {
	AVLTreeNode* L = (AVLTreeNode*) _node->left;
	_node->left = L->right;
	L->right = _node;
	L->parent = _node->parent;
	_node->parent = L;
	/*L->balance = 0;
	_node->balance = 0;*/
	_node = L;
}

void AVLTree::turnLeft(AVLTreeNode* _node) {
	AVLTreeNode* R = (AVLTreeNode*)_node->right;
	_node->right = R->left;
	R->left = _node;
	R->parent = _node->parent;
	_node->parent = R;
	_node = R;
}

void AVLTree::balancing(AVLTreeNode* _node) {
	if (_node->balance == -2) {
		AVLTreeNode* ltmp = (AVLTreeNode*)_node->left;
		if (ltmp->balance == -1) {
			turnRight(_node);
			_node->balance = 0;
			ltmp->balance = 0;
		}
		else {
			AVLTreeNode* rtmp = (AVLTreeNode*)ltmp->right;
			turnLeft(ltmp);
			turnRight(_node);
			if (rtmp->balance == -1) _node->balance = 1;
			else if (rtmp->balance == 1) _node->balance = -1;
			else _node->balance = 0;
			rtmp->balance = 0;
			ltmp->balance = 0;
		}
	}
	else if (_node->balance == 2) {
		AVLTreeNode* rtmp = (AVLTreeNode*)_node->right;
		if (rtmp->balance == 1) {
			turnLeft(_node);
			_node->balance = 0;
			rtmp->balance = 0;
		}
		else {
			AVLTreeNode* ltmp = (AVLTreeNode*)rtmp->left;
			turnLeft(rtmp);
			turnRight(_node);
			if (ltmp->balance == -1) _node->balance = 1;
			else if (ltmp->balance == 1) _node->balance = -1;
			else _node->balance = 0;
			rtmp->balance = 0;
			ltmp->balance = 0;
		}
	}
}

void AVLTree::insert(int _key, TreeNode* &_node) {
	if (_node == nullptr) {
		_node = new TreeNode;
		_node->key = _key;
		return;
	}
	AVLTreeNode* tmp = (AVLTreeNode*)_node;
	if (tmp->key > _key) {
		tmp->balance--;
		insert(_key, _node->left);
		balancing(tmp);
		return;
	}
	if (tmp->key < _key) {
		tmp->balance++;
		insert(_key, _node->right);
		balancing(tmp);
		return;
	}
}