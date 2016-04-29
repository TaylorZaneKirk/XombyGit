// Name: Taylor Kirk
// File: ComplexNumber.h: interface for the CirList class.
// Date: Feb. 20, 2016
// ADT: A CirList is a circular linked list that contains and manipulate
//	linked nodes containing strings
//////////////////////////////////////////////////////////////////////
#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

//Node containing a string and a pointer to another node
struct node
{
	string name;
	node *next;
	node(string name) : name(name), next(NULL){}
};

class CirList
{
private:
	struct node* Head;	//First node in the list
	struct node* Cursor;	//A cursor node that points to an
							//	existing item in the list
	ofstream output;

	void removeItem(string Name);
	//requires: That CirList has been constructed and that
	//	some node in CirList contains a string s such that
	//	s == Name
	//ensures: That the node (k) in CirList that contains a
	//	string s == Name will be removed and that the other
	//	node (j) pointing to k will now point to l, the node
	//	that k pointed to. This will ensure that the structure
	//	of CirList remains intact.
	//checks: If the string Name is contained within some
	//	node in CirList. If Name is not in CirList no
	//	modification occurs.

	void removeItemHere();
	//requires: That CirList has been constructed, that
	//	the node Cursor points to some node
	//ensures: That the node (k) in CirList that is
	//	pointed to by Cursor will now point to l, the node
	//	that k pointed to. This will ensure that the structure
	//	of CirList remains intact.
	//checks: none

	void clearList();
	//requires: That CirList has been constructed and
	//	that Head has been initialized
	//ensures: That all the nodes in CirList will
	//	be sequentially removed starting from the the last
	//	node in the list.
	//checks: none

	void advanceCursor();
	//requires: That CirList has been constructed and
	//	that Cursor has been initialized and points
	//	to some node in CirList
	//ensures: That Cursor will now point to the node
	//	that the current node(pointed to by Cursor) is
	//	pointing to.
	//checks: That Cursor points to some node. If not
	//	perform no operation

public:
	CirList();
	//requires: none
	//ensures: That a circlular list will be constructed
	//	and the the node pointer Head will point to NULL.
	//	The output file ("output.txt") will also be opened.
	//checks: none

	~CirList();
	//requires: none
	//ensures: That the circular list object's resources are deallocated
	//checks: none

	void insertItemEnd(string Name);
	//requires: that CirList has been constructed
	//ensures: that a new node will be constructed
	//	containing the string Name. That node in
	//	CirList that was pointing to the Head node
	//	(last node in list) will now point to the
	//	new node. The new node will now point to Head
	//checks: none

	void insertItemFirst(string Name);
	//requires: that CirList has been constructed
	//ensures: that a new node will be constructed
	//	containing the string Name. That node in
	//	CirList that was pointing to the Head node
	//	(last node in list) will now point to the
	//	new node. The new node will now point to Head.
	//	The node pointer Head will now point to the new node.
	//checks: none

	void insertItemHere(string Name);
	//requires: That CirList has been constructed and
	//	the node pointer Cursor points to some node
	//	in CirList.
	//ensures: A new node will be contructed containing
	//	the string Name. The node that Cursor is pointing
	//	at will now point to the new node. The new node will
	//	point to the node that was previously pointed to
	//	by Cursor. Cursor is redefined to point to the
	//	new node.
	//checks: none

	void changeCurrentItem(string difName);
	//requires: That CirList has been constructed and that
	//	the node pointer Cursor is pointing to some node
	//	in CirList
	//ensures: The node being pointed to by Cursor will have
	//	its contents changed to string difName
	//checks: If Cursor is pointing to some node. If not,
	//	no operation is performed

	void Permute(int iterations);
	//requires: That CirList has been constructed and that
	//	it contains some number of nodes
	//ensures: i = iterations, every ith node in CirList
	//	will be removed until only one node remains.
	//	output the contents of each node removed to the
	//	output file. Output the contents of the final
	//	node remaining and indicate that it is the winner.
	//	Once the CirList has been entirely processed and
	//	the winner has been determined. Clear the list.
	//checks: That the CirList is not empty. If the CirList
	//	is empty, no operation is performed.

	void printList();
	//requires: CirList has been constructed
	//ensures: Writes the contents of each node in
	//	CirList to the output file as well as the
	//	number of nodes contained in CirList
	//checks: none

	void resetCursor(){	Cursor = Head;	}
	//requires: That CirList has been constructed
	//ensures: That the node pointer Cursor will now
	//	point to the same node that node pointer Head
	//	is pointing to.
	//checks: none

	bool isEmpty();
	//requires: none
	//ensures: Returns false if Head is pointing
	//	to some node. Returns true if Head is not
	//	pointing to anything
	//checks: none

	int length();
	//requires: none
	//ensures: returns i, where i = |CirList|
	//checks: none

	int findItem(string Name);
	//requires: CirList has been constructed
	//ensures: Returns the integer position of the
	//	node in CirList that contains a string s
	//	such that s == Name
	//checks: If Name is not contained in any node
	//	in CirList will return the integer -1

	string getCurrentItem();
	//requires: CirList has been constructed and
	//	that the node pointer Cursor is pointing
	//	to some node in CirList
	//ensures: Returns the contents of the node in
	//	CirList being pointed to by Cursor
	//checks: if Cursor is not pointing to a node,
	//	no operation is performed
};

