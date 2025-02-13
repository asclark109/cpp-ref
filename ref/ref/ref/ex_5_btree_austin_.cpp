#include "ex_5_btree_austin.h"
#include <iostream>


void findAndPrintResult(int x, Btree const& tree) {
	Node* nodePtr = tree.search(x);
	if (nodePtr != nullptr) {
		std::cout << "found: " << *nodePtr << std::endl;
	}
	else {
		std::cout << "did not find " << x << std::endl;
	}
}

int main() {
	Btree tree{};
	tree.insert(2);
	tree.insert(6);
	tree.insert(2);
	tree.insert(3);
	tree.insert(10);
	tree.insert(1);
	findAndPrintResult(3, tree);

	Btree tree2(tree); // test copy constructor
	Btree tree3;
	tree3=tree; // test copy-assignment constructor
	return 0;
}