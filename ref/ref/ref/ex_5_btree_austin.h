#ifndef BTREE_H
#  define BTREE_H
// From http://www.cprogramming.com/tutorial/lesson18.html 

#include <memory>
#include <string>
#include <ostream>

// MAJOR CHANGES
// 
// SUMMARY: Node and Btree are changed to exhibit automatic duration lifecycle management; this makes
//          these classes way easier to think about, logically. Intricacies of delete methods have
//          been removed, and the code within these classes is now heavily domain-focused. Granted,
//          the classes now implement the copy and copy-assignment constructors, but that provides
//          additional correctness.
// 
// (1) The Node now holds 2 unique_ptr's to its children. This enables automatic duration lifetime
//     management for its children, which majorly simplifies deletion. If the parent Node is destroyed,
//     its children are automatically destroyed as well. This makes logical sence, meriting the use
//     of unique_ptr's. This has beneficial consequences for change (2)
// 
// (2) The Btree now holds 1 unique_ptr to the root Node. This enables automatic duration lifetime
//     management for the Btree, and we can then delete its destructor method! Can now delete
//     good chunk of code.
// 
// (3) implement the copy and copy-assignment constructors for Node and BTree. This needs to be 
//     added because Node and BTree are classes that *manage* resources (children, root). 
//     I do not believe we need to redefine the move constructor and move-copy constructor, since 
//     we have automatic life-cycle management of the Node and Btree. Again, We do NOT need to implement 
//     the destructors becuase we achieved automatic duration lifecycle management

// in order to realize changes (1) and (2), having unique_ptr's means we can no longer pass nodes into
// insert, search functions (because unique_ptr's can't be copied). So, instead we change the method 
// signatures to take Node&. This is fine because a Node& means no copying involved. So, we can have 
// unique_ptr's and not suffer overhead or intricacies of passing the Nodes into functions. This does 
// mean we have to check children Nodes are not nullptr before dereferencing them when passing them 
// into function calls. This is not a concern, though, because we were still checking for nullptr's 
// before (just at a different location).

// BTree::search() still returns a Node*. This reflects the fact that the search operation can
// fail (i.e. we need to be able to return the Node in case of success but also return "None"
// in case of failure, and only a pointer gives this functionality. The question is now whether 
// we ought to return a raw pointer or a smart pointer). We return a raw pointer to reflect the fact 
// that the Btree is not "giving up" ownership of its Node. Thus, the raw pointer is still the 
// appropriate return type.

// MENIAL CHANGES
// (1) capitalize struct names (e.g. "node" -> "Node", "btree" -> "Btree"); inconsequential
// (2) replace the use of the NULL macro with the superior nullptr
// (3) declare Btree::search method "const" to inform compiler the tree object won't change state

struct Node
{
	int key_value;
	std::unique_ptr<Node> left;
	std::unique_ptr<Node> right;

	inline friend std::ostream& operator<<(std::ostream& os, const Node& node) { // NEW: (for debugging)
		os << "Node(key=" << node.key_value << ")";
		return os;
	}

	Node() = default;

	Node(const Node& that) { // NEW
		// copy key
		this->key_value = that.key_value; 
		// copy left subtree
		if (that.left != nullptr) {
			this->left = std::make_unique<Node>(*that.left);
		}
		else {
			this->left = nullptr;
		}
		// copy right subtree
		if (that.right != nullptr) { 
			this->left = std::make_unique<Node>(*that.right);
		}
		else {
			this->left = nullptr;
		}
	}

	Node& operator=(Node const& that) { // NEW
		if (this != &that) {
			auto copy = Node(that);
			return copy;
		}
		return *this;
	}


};

class Btree
{
public:
	Btree() = default;

	Btree(const Btree& that) { // NEW
		// copy root
		if (that.root != nullptr) {
			this->root = std::make_unique<Node>(*that.root);
		}
		else {
			this->root = nullptr;
		}
	}

	Btree& operator=(Btree const& that) { // NEW
		if (this != &that) {
			auto copy = Btree(that);
			return copy;
		}
		return *this;
	}

	void insert(int key) {
		if (root != nullptr)
			insert(key, *root);
		else
		{
			root = std::make_unique<Node>(); // NEW
			root->key_value = key;
			root->left = nullptr;
			root->right = nullptr;
		}
	}

	Node* search(int key) const {
		if (root != nullptr) {
			return search(key, *root);
		}
		else {
			return nullptr;
		}
	}

private:

	void insert(int key, Node& leaf) {
		if (key < leaf.key_value)
		{
			if (leaf.left != nullptr)
				insert(key, *leaf.left);
			else
			{
				leaf.left = std::make_unique<Node>(); // NEW
				leaf.left->key_value = key;
				leaf.left->left = nullptr;    //Sets the left child of the child node to nullptr
				leaf.left->right = nullptr;   //Sets the right child of the child node to nullptr
			}
		}
		else if (key >= leaf.key_value)
		{
			if (leaf.right != nullptr)
				insert(key, *leaf.right);
			else
			{
				leaf.right = std::make_unique<Node>(); // NEW
				leaf.right->key_value = key;
				leaf.right->left = nullptr;  //Sets the left child of the child node to nullptr
				leaf.right->right = nullptr; //Sets the right child of the child node to nullptr
			}
		}
	}

	Node* search(int key, Node& leaf) const { // NEW
		if (key == leaf.key_value)
			return &leaf;
		else if (key < leaf.key_value && leaf.left != nullptr)
			return search(key, *leaf.left);
		else if (key > leaf.key_value && leaf.right != nullptr)
			return search(key, *leaf.right);
		return nullptr;
	}

	std::unique_ptr<Node> root; // NEW
};

#endif
