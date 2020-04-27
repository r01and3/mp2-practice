#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree(int _key) {
	root = new TreeNode;
	root->key = _key;
	root->left = nullptr;
	root->right = nullptr;
	root->parent = nullptr;
}

BinarySearchTree::~BinarySearchTree(){}

TreeNode* BinarySearchTree::search(int _key) {
	if (root == nullptr) throw std::exception("Tree is empty");
	TreeNode* tmp = root;
	while (tmp != nullptr && tmp->key != _key) {
		if (_key < tmp->key) tmp = tmp->left;
		else tmp = tmp->right;
	}
	return tmp;
}

TreeNode* BinarySearchTree::searchMax(int _key) {
	if (root == nullptr) throw std::exception("Tree is empty");
	TreeNode* tmp = search(_key);
	while (tmp->right != nullptr)
		tmp = tmp->right;
	return tmp;
}

TreeNode* BinarySearchTree::searchMin(int _key) {
	if (root == nullptr) throw std::exception("Tree is empty");
	TreeNode* tmp = search(_key);
	while (tmp->left != nullptr)
		tmp = tmp->left;
	return tmp;
}

TreeNode* BinarySearchTree::searchNext(TreeNode* &_node) {
	if (_node == nullptr) throw std::exception("No such node exists");
	TreeNode* res = nullptr;
	if (_node->right != nullptr) {
		res = searchMin(_node->key);
		return res;
	}
	res = _node->parent;
	TreeNode* tmp = _node;
	while (res != nullptr && tmp == res->right) {
		tmp = res;
		res = res->parent;
	}
	return res;
}

TreeNode* BinarySearchTree::searchPrev(TreeNode* &_node) {
	if (_node == nullptr) throw std::exception("No such node exists");
	TreeNode* res = nullptr;
	if (_node->left != nullptr) {
		res = searchMax(_node->key);
		return res;
	}
	res = _node->parent;
	TreeNode* tmp = _node;
	while (res != nullptr && tmp == res->left) {
		tmp = res;
		res = res->parent;
	}
	return res;
}

void BinarySearchTree::insert(int _key) {
	if (root == nullptr) {
		root = new TreeNode;
		root->key = _key;
		root->left = nullptr;
		root->right = nullptr;
		root->parent = nullptr;
		return;
	}
	TreeNode* tmp1 = root, *tmp2 = root;
	while (tmp1 != nullptr) {
		tmp2 = tmp1;
		if (tmp1->key > _key) 
			tmp1 = tmp1->left;
		else 
			tmp1 = tmp1->right;
	}
	if (tmp2->key > _key) {
		tmp2->left = new TreeNode;
		tmp2->left->key = _key;
		tmp2->left->parent = tmp2;
		tmp2->left->left = nullptr;
		tmp2->left->right = nullptr;
	}
	else {
		tmp2->right = new TreeNode;
		tmp2->right->key = _key;
		tmp2->right->parent = tmp2;
		tmp2->right->left = nullptr;
		tmp2->right->right = nullptr;
	}
}

void BinarySearchTree::remove(int _key) {
	if (root == nullptr) throw std::exception("Tree is empty");
	TreeNode* tmp = search(_key);
	TreeNode* tmp1 = nullptr;
	TreeNode* tmp2 = nullptr;
	if (tmp->left != nullptr && tmp->right != nullptr)
		tmp2 = searchNext(tmp);
	else
		tmp2 = tmp;
	if (tmp2->left != nullptr)
		tmp1 = tmp2->left;
	else
		tmp1 = tmp2->right;
	if (tmp1 != nullptr) tmp1->parent = tmp2->parent;
	if (tmp2->parent != nullptr) {
		if (tmp2 == tmp2->parent->left) tmp2->parent->left = tmp1;
		else tmp2->parent->right = tmp1;
	}
	if (tmp2 != tmp) {
		tmp->key = tmp2->key;
	}
}