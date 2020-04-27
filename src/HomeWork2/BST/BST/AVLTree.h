#pragma once
#include "BinarySearchTree.h"

struct AVLTreeNode : public TreeNode{
	int balance;
};

class AVLTree : public BinarySearchTree{
private:
	void turnRight(AVLTreeNode* _node);
	void turnLeft(AVLTreeNode* _node);
	void balancing(AVLTreeNode* _node);
public:
	AVLTree(int _key) : BinarySearchTree(_key) {
		AVLTreeNode* tmp = (AVLTreeNode*)root;
		tmp->balance = 0;
	};
	void insert(int _key, TreeNode* &_node);
	TreeNode* getRoot() {
		return root;
	}
};