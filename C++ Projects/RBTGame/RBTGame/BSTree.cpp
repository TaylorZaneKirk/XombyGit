//Name: Taylor Kirk
//Date: April 3, 2016
//Class: Advance Structures and Algorithms
//Red-Black Trees

#include <iostream>
#include "BSTree.h"
using namespace std;

BSTree::BSTree(){
	root = NULL;
	cursor = NULL;
}

void BSTree::Insert(int x){
	Node * p = NULL;
	if (root == NULL){
		root = new Node();
		root->data = x;
		root->color = 'B';	//first node is black
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
		cursor = root;
	}
	else{
		__Insert(p, root, x);
	}
}

int BSTree::Height(){
	return __Height(root);
}

void BSTree::PrintTree(){
	__Print(root);
}

bool BSTree::findItem(int x) {
	bool found = false;
	Node * p;

	//set p to root
	p = root;

	while (!found && (p != NULL)) {
		if (p->data == x)
			found = true;
		else if (x < p->data)
			p = p->left;
		else  if (x > p->data)
			p = p->right;
	}

	//if found, make cursor point to it; might want to do something with it?
	if (found)
		cursor = p;

	return found;
}

void BSTree::deleteItem(int x){

	bool found = findItem(x);

	if (!found)
		cout << "ERROR: Cannot remove item, item is not in tree.\n";
	//item found and cursor is at the node that contains the item
	else {
		__deleteItem();
		cursor = root;
	}
}

void BSTree::__deleteItem() {
	Node * p;
	Node * q;

	//case 1:  interior node
	if ((cursor->left != NULL) && (cursor->right != NULL)){
		p = cursor;

		//move q to right most node in left subtree
		q = cursor;
		q = q->left;
		while (q->right != NULL)
			q = q->right;

		//copy value in q to the node p
		p->data = q->data;
		cursor = q;
		
		//delete q which could be a leaf or node that has left subtree
		__deleteItem();

		if (p != root)
			cursor = p->parent;
		else
			cursor = root;
	}
	//case 2: has only left subtree
	else if (cursor->left != NULL) {
		p = cursor;

		if (cursor != root) {
			cursor = p->parent;
			cursor->right = p->left;
			cursor->right->color = p->color;
			p->left->parent = cursor;
			
		}
		else
		{
			cursor = p->left;
			root = cursor;
			root->parent = NULL;
		}
		FixDelete(cursor);	//Maintain RBTree properties
		delete p;
	}
	//case 3: has only right subtree
	else if (cursor->right != NULL) {
		p = cursor;
		if (cursor != root) {
			cursor = p->parent;
			cursor->left = p->right;
			p->right->parent = cursor;
		}
		else
		{
			cursor = p->right;
			root = cursor;
			root->parent = NULL;
		}
		FixDelete(cursor);	//Maintain RBTree properties
		delete p;
	}
	//case 4: cursor is at leaf, because both left and right are NULL
	else {
		p = cursor;
		if (cursor == root) {
			root = NULL;
			cursor = NULL;
		}
		else {
			cursor = p->parent;
			if (p->parent->left == p)
				p->parent->left = NULL;
			else
				p->parent->right = NULL;
		}
		
		delete p;
	}
}

void BSTree::FixDelete(Node *& subroot)
{
	cursor = subroot;	//Set cursor to the current node

	//For as long as we are not at root, and for as long as
	//	the color of the current node is Black
	while (cursor != root && cursor->color == 'B')
	{
		//Cursor is a left-child
		if (cursor == cursor->parent->left)
		{
			Node * w = cursor->parent->right; //uncle
			Node * v = cursor; //remember original location

			//Uncle is red
			if (w->color == 'R')
			{
				//recolor uncle and parent
				w->color = 'B';
				cursor->parent->color = 'R';
				LeftRotate(cursor->parent);
				w = cursor->right; //reset uncle
			}
			//Uncle's left-child is Black and it's right-child is Black
			if ((w->left == NULL || w->left->color == 'B') && w->right->color == 'B')
			{
				w->color = 'R'; //uncle becomes Red
				cursor = cursor->parent; //Current node is now the parent
			}
			else
			{
				//If uncle's right-child is Black
				if (w->right->color == 'B')
				{
					//color left-child Black, and uncle becomes Read
					if (w->left !=NULL)
						w->left->color = 'B';
					w->color = 'R';
					RightRotate(w);
					cursor = v; //Rotates change cursor position. Return cursor
								//	back to it's prior location
					w = cursor->parent->right;	//reset uncle
				}

				//Uncle's color becomes the color of the current node's parent
				w->color = cursor->parent->color;
				cursor->parent->color = 'B';	//Parent is black
				w->right->color = 'B';	//Uncle's right-child is Black
				LeftRotate(cursor->parent);
				cursor = root; //Current node is root
			}
		}
		else	//Cursor is a right-child
		{
			Node * w = cursor->parent->left; //uncle
			Node * v = cursor; //remember original location

			//Uncle is red
			if (w->color == 'R')
			{
				w->color = 'B';
				cursor->parent->color = 'R';
				RightRotate(cursor->parent);
				w = cursor->parent->left; //reset uncle
			}
			//Uncle's right-child is Black and it's left-child is Black
			if ((w->right == NULL || w->right->color == 'B') && w->left->color == 'B')
			{
				w->color = 'R';
				cursor = cursor->parent;
			}
			else
			{
				//uncle's left-child is black
				if (w->left->color == 'B')
				{
					//right-child becomes black
					if (w->right != NULL)
						w->right->color = 'B';
					w->color = 'R';	//Uncle is Red
					LeftRotate(w);
					cursor = v; //Go back to prior location before rotate
					w = cursor->parent->left; //reset uncle
				}

				//Uncle's color becomes the color of the current node's parent
				w->color = cursor->parent->color;
				cursor->parent->color = 'B';	//Parent is black
				w->left->color = 'B';	//Uncle's left-child is black
				RightRotate(cursor->parent);
				cursor = root; //Current node is now root
			}
		}
	}
	root->color = 'B'; //root has to be black
}

void BSTree::__Insert(Node *& parent, Node *&subroot, int data){
	if (subroot == NULL){
		subroot = new Node();
		subroot->data = data;
		subroot->color = 'R';	//All secondary nodes are Red
		subroot->left = NULL;
		subroot->right = NULL;
		subroot->parent = parent;
		cursor = subroot;
		FixTree(cursor);	//Maintain RBTree properties
	}
	else{
		if (data < subroot->data){
			__Insert(subroot, subroot->left, data);
		}
		else{
			__Insert(subroot, subroot->right, data);
		}
	}
}

void BSTree::FixTree(Node *& subroot)
{
	Node * temp;
	cursor = subroot; //Set cursor to current node

	//Continue for as long as we aren't at the root of the RBTree
	//	and as long as the parent of the current node is Red
	while (cursor != root && cursor->parent->color == 'R')
	{
		if (cursor->parent == cursor->parent->parent->left) //Parent was left-child
		{
			temp = cursor->parent->parent->right; //Uncle

			//Case 3
			if (cursor->parent->parent->right != NULL && temp->color == 'R')
			{
				cursor->parent->color = 'B'; //Recolor Parent
				temp->color = 'B';	//Recolor Uncle
				cursor->parent->parent->color = 'R'; //Recolor Grand-Parent
				cursor = cursor->parent->parent; //Set cursor to be Grand-Parent
			}
			else 	
			{
				//case 4
				//cursor is a right-child
				if (cursor == cursor->parent->right)
				{
					cursor = cursor->parent;
					LeftRotate(cursor);
				}
				//case 5
				cursor->parent->color = 'B'; //Recolor parent
				cursor->parent->parent->color = 'R'; //Recolor Grand-Parent
				cursor = cursor->parent->parent; //Set Cursor to Grand-Parent
				RightRotate(cursor);
			}

		}
		else //Parent was a right-child
		{
			temp = cursor->parent->parent->left;	//uncle

			//case 3
			if (cursor->parent->parent->left != NULL && temp->color == 'R')
			{
				//swap colors of Parent, Uncle, and GrandParent
				cursor->parent->color = 'B';
				temp->color = 'B';
				cursor->parent->parent->color = 'R';
				cursor = cursor->parent->parent;	//Set cursor to now be GP
			}
			else 
			{
				//case 4
				//current-node is a left-child
				if (cursor == cursor->parent->left)
				{
					cursor = cursor->parent;
					RightRotate(cursor);
				}
				//case 5
				//Recolor Parent and GrandParent
				cursor->parent->color = 'B';
				cursor->parent->parent->color = 'R';
				cursor = cursor->parent->parent; //Set cursor to now be GP
				LeftRotate(cursor);
			}
		}
	}
	//case 2
	root->color = 'B';
}

void BSTree::LeftRotate(Node *& subroot)
{
	Node * RightChild = cursor->right;

	//Connect cursor's right-pointer to the left-child of RightChild
	cursor->right = RightChild->left;

	//Connect RightChild's left-child's parent-pointer to cursor
	if (RightChild->left != NULL)
		RightChild->left->parent = cursor;

	//RightChild's parent-pointer now connects to the parent of Cursor
	RightChild->parent = cursor->parent;

	//Cursor was the root
	if (cursor->parent == NULL)
	{
		root = RightChild;
	}
	
	else if (cursor == cursor->parent->left) //Cursor was a left-child
		cursor->parent->left = RightChild;
	
	else	//cursor was a right-child
		cursor->parent->right = RightChild;

	//Cursor becomes the left-child of RightChild
	RightChild->left = cursor;

	//Cursor's parent is now RightChild
	cursor->parent = RightChild;
}

void BSTree::RightRotate(Node *& subroot)
{
	Node * LeftChild = cursor->left;

	//Connect cursor's right-pointer to the left-child of LeftChild
	cursor->left = LeftChild->right;

	//Connect LeftChild's right-child's parent-pointer to cursor
	if (LeftChild->right != NULL)
		LeftChild->right->parent = cursor;

	//RightChild's parent-pointer now connects to the parent of Cursor
	LeftChild->parent = cursor->parent;

	//Cursor was the root
	if (cursor->parent == NULL)
	{
		root = LeftChild;
	}
	
	else if (cursor == cursor->parent->right) //Cursor was a right-child
		cursor->parent->right = LeftChild;
	else	//cursor was a left-child
		cursor->parent->left = LeftChild;

	//Cursor becomes the right-child of LeftChild
	LeftChild->right = cursor;
	
	//The parent of cursor becomes LeftChild
	cursor->parent = LeftChild;
}

void BSTree::__Print(Node *subroot){
	if (subroot == NULL){
		return;
	}
	else{
		//cout << subroot->data << " ";	//Preorder
		__Print(subroot->left);
		cout << subroot->data << " "; //Inorder
		__Print(subroot->right);
		//cout << subroot->data << " "; //Postorder
	}
}

int BSTree::__Height(Node *subroot){
	if (subroot == NULL){
		return 0;
	}
	else{
		int ldepth = __Height(subroot->left);
		int rdepth = __Height(subroot->right);

		if (ldepth > rdepth){
			return 1 + ldepth;
		}
		else{
			return 1 + rdepth;
		}
	}
}

void BSTree::ShiftToRoot()
{
	if ((cursor == NULL) || (root == NULL))
		cout << "ERROR:  T's cursor cannot advance to root" << endl;
	else
	{
		//move the actual cursor
		cursor = root;
	}
}


void BSTree::ShiftLeft()
{
	if ((cursor == NULL) || (cursor->left == NULL))
		cout << "ERROR:  T's cursor cannot advance left" << endl;
	else
	{
		//move the actual cursor
		cursor = cursor->left;
	}
}


void BSTree::ShiftRight()
{
	if ((cursor == NULL) || (cursor->right == NULL))
		cout << "ERROR:  T's cursor cannot advance right" << endl;
	else
	{
		//move the actual cursor
		cursor = cursor->right;
	}
}


void BSTree::ShiftUp()
{
	if ((cursor == NULL) || (cursor->parent == NULL))
		cout << "ERROR:  T's cursor cannot advance up" << endl;
	else
	{
		//move the actual cursor
		cursor = cursor->parent;
	}

}

bool BSTree::HasParent()
{
	if (cursor != root && cursor != NULL)
	{
		return cursor->parent != NULL;
	}
	return false;
}


bool BSTree::HasNoChildren()
{
	return ((cursor != NULL) && (cursor->left == NULL && cursor->right == NULL));
}


bool BSTree::HasLeftChild()
{
	return ((cursor != NULL) && (cursor->left != NULL));
}


bool BSTree::HasRightChild()
{
	return ((cursor != NULL) && (cursor->right != NULL));
}


void BSTree::RetrieveItem(int & Item)
{
	if (cursor)
		Item = cursor->data;
}

bool BSTree::IsEmpty()
{
	return root == NULL;
}