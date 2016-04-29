//Name: Taylor Kirk
//Date: April 3, 2016
//Class: Advance Structures and Algorithms
//Red-Black Trees

#include <iostream>
using namespace std;

struct Node{
	int data;
	char color;
	Node *left;
	Node *right;
	Node *parent;
};

class BSTree{

public:
	BSTree();

	void Insert(int x);

	int Height();

	void PrintTree();

	bool findItem(int x);

	void deleteItem(int x);

	void ShiftToRoot();
	//precond:  this tree is created and not empty
	//postcond: this tree's cursor is pointing to the root of T, this tree unchanged otw.
	//checks:   none

	void ShiftLeft();
	//precond:  this tree has been created and this tree's cursor not at leaf
	//postcond: this tree's cursor is advanced so that it references the 
	//          left child of the item that this tree's #cursor,
	//          this tree is unChanged otherwise.
	//checks:   this tree's cursor not at leaf

	void ShiftRight();
	//precond:  this tree has been created and this tree's cursor not at leaf
	//postcond: this tree's cursor is advanced so that it references the 
	//          right child of the item that this tree's #cursor,
	//          this tree is unChanged otherwise.
	//checks:   this tree's cursor not at end

	void ShiftUp();
	//precond:  this tree is created and this tree's cursor not at root
	//postcond: this tree's cursor is moved back so that it references the
	//          parent of the item that this tree's #cursor, 
	//          this tree is unChanged otw.
	//checks:   this tree's cursor not referencing root

	bool HasParent();
	//precond:  Tree is created
	//postcond: HasParent = TRUE iff the tree is not empty and the cursor is
	//          pointing at a node that has a parent.  this tree = #tree
	//checks:   none

	bool HasNoChildren();
	//precond:  Tree is created
	//postcond: HasNoChildren = TRUE iff the tree is not empty and the cursor is
	//          pointing at an node that has no children. tree =#tree.
	//checks:   none

	bool HasLeftChild();
	//precond:  Tree is created
	//postcond: HasLeftChild = TRUE iff the tree is not empty and the cursor is
	//          pointing at an node that has a left child. tree=#tree.
	//checks:   none

	bool HasRightChild();
	//precond:  Tree is created
	//postcond: HasRightChild = TRUE iff the tree is not empty and the cursor is
	//          pointing at an node that has a right child. tree=#tree.
	//checks:   none

	void RetrieveItem(int & Item);
	//precond:  this tree is created and this tree's cursor is referencing a node
	//postcond: the value of the item that this tree's cursor references is
	//          returned as the value of Item, this tree = #tree.
	//checks:   this tree's cursor is referencing a node

	bool IsEmpty();
	//precond:  none
	//postcond:  returns true iff tree is empty and false otherwise
	//checks:	none

	

private:
	Node *root;
	Node *cursor;

	void __Insert(Node *& parent, Node *&subroot, int data);
	int __Height(Node *subroot);
	void __Print(Node *subroot);
	void __deleteItem();
	void __RemoveRoot(Node *& parent, Node *&subroot);
	void Transplant(Node *& parent, Node *&subroot);

	void FixTree(Node *& subroot);
	//precond: this tree is created and Node subroot is referencing some
	//	node within this tree
	//postcond:	this tree will be rearranged based on RBTree properties.
	//	if this tree already meets all the RBTree properties this tree = #tree
	//checks:	none

	void FixDelete(Node *& subroot);
	//precond: this tree is created and Node subroot is referencing some
	//	node within this tree
	//postcond:	this tree will be rearranged based on RBTree properties.
	//	if this tree already meets all the RBTree properties this tree = #tree
	//checks:	none

	void LeftRotate(Node *&subroot);
	//precond: this tree is created and Node subroot is referencing some
	//	node within this tree
	//postcond:	this sub-tree (subroot as root of sub-tree) will be rearranged
	//	based on RBTree properties. Subroot's right-child becomes the parent
	//	of sub-root (Now called the former-right-child). Subroot's right-child
	//	will now reference the former-right-child's left-child. Subroot becomes
	//	the left-child of the former-right-child.
	//checks:	none

	void RightRotate(Node *&subroot);
	//precond: this tree is created and Node subroot is referencing some
	//	node within this tree
	//postcond:	this sub-tree (subroot as root of sub-tree) will be rearranged
	//	based on RBTree properties. Subroot's left-child becomes the parent
	//	of sub-root (Now called the former-left-child). Subroot's left-child
	//	will now reference the former-left-child's right-child. Subroot becomes
	//	the right-child of the former-left-child.
	//checks:	none

};