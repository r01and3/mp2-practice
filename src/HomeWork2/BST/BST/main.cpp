#include "BinarySearchTree.h"
#include "AVLTree.h"

void main() {
	AVLTree tree(1);
	tree.insert(2, tree.getRoot());
	tree.insert(4, tree.getRoot());
	tree.insert(6, tree.getRoot());
}