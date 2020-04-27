#pragma once
#include <exception>

struct TreeNode {
	int key;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;
};

class BinarySearchTree {
protected:
	TreeNode* root;
public:
	BinarySearchTree(int _key);
	//BinarySearchTree(const BinarySearchTree& _tree);
	~BinarySearchTree();
	
	TreeNode* search(int _key);
	TreeNode* searchMax(int _key);
	TreeNode* searchMin(int _key);
	TreeNode* searchNext(TreeNode* &_node);
	TreeNode* searchPrev(TreeNode* &_node);
	void insert(int _key);
	void remove(int _key);
};