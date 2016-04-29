//Name: Taylor Kirk
// 2/27/2016
// Prof. Stringfellow
// Binary Trees


#include <iostream>
#include <fstream>
#include "BTree.h"
using namespace std;

void DoBuilding (BTree  & T, ifstream & infile, char dir);
/*precond: T is created and infile is open for reading and file is in "correct" format
  postcond:  Reads the file and builds up the data in the subtree referenced by the cursor in preOrder
             dir is the left or right child position the next item goes into
  checks:  none  */

void BuildTree (BTree  & T, ifstream & infile);
/*precond: T is created and infile is open for reading and file is in "correct" format
  postcond:  Reads the file and builds up the data in the Tree in preOrder
  checks:  none  */

void DoInOrder(BTree  & T);
/*precond:  T is created
 postcond: Traverses the binary subtree referenced by T's cursor in inorder.
			  Visit a node means print out its data to monitor.  T = #T.
 checks:   none */

void Inorder(BTree  & T);
/*precond:  T is created
 postcond: Traverses the binary tree T in inorder.
			  Visit a node means print out its data to monitor.  T = #T, except T's
			  cursor is referencing the root
 checks:   none */

// DECLARE AND SPECIFY ADDITIONAL NON-MEMBER FUNCTIONS HERE

void DoPreOrder(BTree  & T);
/*precond:  T is created
postcond: Traverses the binary subtree referenced by T's cursor in Preorder.
Visit a node means print out its data to monitor.  T = #T.
checks:   none */

void Preorder(BTree  & T);
/*precond:  T is created
postcond: Traverses the binary tree T in preorder.
Visit a node means print out its data to monitor.  T = #T, except T's
cursor is referencing the root
checks:   none */

void DoPostOrder(BTree  & T);
/*precond:  T is created
postcond: Traverses the binary subtree referenced by T's cursor in Postorder.
Visit a node means print out its data to monitor.  T = #T.
checks:   none */

void Postorder(BTree  & T);
/*precond:  T is created
postcond: Traverses the binary tree T in postorder.
Visit a node means print out its data to monitor.  T = #T, except T's
cursor is referencing the root
checks:   none */

void SumTree(BTree  & T);
/*precond:  T is created
postcond: Returns the integer sum of the value of all nodes in T
			T = #T
checks:   none */

int DoSum(BTree  & T);
/*precond:  T is created
postcond: Traverses the binary subtree referenced by T's cursor in Inorder.
Visit a node means print out its data to monitor. Returns the sum of
all integers in T. T = #T.
checks:   none */

int main ()
{
  BTree T ;
  ifstream infile ;
  char infilename[40];

  // CALL FUNCTION TO SHOW INTRO HERE

  //open input file
  cout <<" Please enter name of input file:  ";
  cin >> infilename;
  cout << endl;
  infile.open (infilename);

    //Build the tree and print it out in InOrder
  BuildTree (T, infile);
  cout <<"  The inorder traversal of the tree " << endl;
  Inorder (T);

  // print it out in PreOrder
  cout <<"  The Preorder traversal of the tree " << endl;
  Preorder (T);

  // print it out in PostOrder
  cout <<"  The postorder traversal of the tree " << endl;
  Postorder (T);

  // print sum
  cout << " The Sum of the tree " << endl;
  SumTree(T);

  //close input file
  infile.close ();

  //CALL FUNCTION TO SHOW EXIT MESSAGE HERE

  system ("pause");

  return 0;
}

void DoBuilding (BTree & T, ifstream & infile, char dir)
{
	ItemType item;
	
	//read item
	infile >> item;

	//if not eof (by bad data file) and not end of subtree (-1)
    if (!infile.eof() && (item != -1))
	{
		//build root of new subtree
		if (T.IsEmpty())
		   T.CreateFirstNode(item);
		else if (dir == 'L')
		{	
			T.AddLeft (item); 		
			T.ShiftLeft();
		}
		else
		{    
			T.AddRight(item); 		
			T.ShiftRight();
		}
	    
		//build left subtree of subtree
		DoBuilding(T, infile, 'L');
		
		//build right subtree of subtree
		DoBuilding(T, infile, 'R');

		//get back to root of subtree 
		if (T.HasParent())
			T.ShiftUp();	
	}
}


void BuildTree (BTree  & T, ifstream & infile)
{
	T.ClearTree();
    DoBuilding(T, infile, 'L');
	T.ShiftToRoot ();
}

//called by InOrder
void DoInOrder(BTree  & T)
{
  ItemType Item;

  //2 base cases: empty tree or subtree is a leaf
  if (!T.IsEmpty ())
  {
	 //not a leaf, has a left child, traverse left subtree of subtree in InOrder
	 if (T.HasLeftChild())
	 {
		T.ShiftLeft();
		DoInOrder(T);
		T.ShiftUp();
	 }

	 //display root of subtree
	 T.RetrieveItem(Item);
	 cout << Item << "  ";	

	 //not a leaf, has a right child, traverse right subtree of subtree in InOrder
	 if (T.HasRightChild())
	 {
		T.ShiftRight ();
		DoInOrder(T);
		T.ShiftUp ();
	 }
  }
}

void Inorder(BTree  & T)
{
  T.ShiftToRoot ();

  if (T.IsEmpty())
	 cout << "Tree is empty" << endl;
  else
  {
	 cout << "Tree contains: " << endl;
	 DoInOrder (T);
  }

   cout << endl << endl;
}

//DEFINE ADDITIONAL NON-MEMBER FUNCTIONS HERE

//called by PreOrder
void DoPreOrder(BTree  & T)
{
	ItemType Item;

	//2 base cases: empty tree or subtree is a leaf
	if (!T.IsEmpty())
	{
		//display root of subtree
		T.RetrieveItem(Item);
		cout << Item << "  ";

		//not a leaf, has a left child, traverse left subtree of subtree in PreOrder
		if (T.HasLeftChild())
		{
			T.ShiftLeft();
			DoPreOrder(T);
			T.ShiftUp();
		}

		//not a leaf, has a right child, traverse right subtree of subtree in PreOrder
		if (T.HasRightChild())
		{
			T.ShiftRight();
			DoPreOrder(T);
			T.ShiftUp();
		}
	}
}

void Preorder(BTree  & T)
{
	T.ShiftToRoot();

	if (T.IsEmpty())
		cout << "Tree is empty" << endl;
	else
	{
		cout << "Tree contains: " << endl;
		DoPreOrder(T);
	}

	cout << endl << endl;
}

//called by PostOrder
void DoPostOrder(BTree  & T)
{
	ItemType Item;

	//2 base cases: empty tree or subtree is a leaf
	if (!T.IsEmpty())
	{
		//not a leaf, has a left child, traverse left subtree of subtree in PostOrder
		if (T.HasLeftChild())
		{
			T.ShiftLeft();
			DoPostOrder(T);
			T.ShiftUp();
		}

		//not a leaf, has a right child, traverse right subtree of subtree in PostOrder
		if (T.HasRightChild())
		{
			T.ShiftRight();
			DoPostOrder(T);
			T.ShiftUp();
		}

		//display root of subtree
		T.RetrieveItem(Item);
		cout << Item << "  ";
	}
}

void Postorder(BTree  & T)
{
	T.ShiftToRoot();

	if (T.IsEmpty())
		cout << "Tree is empty" << endl;
	else
	{
		cout << "Tree contains: " << endl;
		DoPostOrder(T);
	}

	cout << endl << endl;
}

//called by InOrder
int DoSum(BTree  & T)
{
	ItemType Item;
	int Sum = 0;

	//2 base cases: empty tree or subtree is a leaf
	if (!T.IsEmpty())
	{
		//not a leaf, has a left child, traverse left subtree of subtree in InOrder
		if (T.HasLeftChild())
		{
			T.ShiftLeft();
			Sum += DoSum(T);
			T.ShiftUp();
		}

		//display root of subtree
		T.RetrieveItem(Item);
		Sum += int(Item);

		//not a leaf, has a right child, traverse right subtree of subtree in InOrder
		if (T.HasRightChild())
		{
			T.ShiftRight();
			Sum += DoSum(T);
			T.ShiftUp();
		}
	}
	else
		return 0;

	return Sum;
}

void SumTree(BTree  & T)
{
	int total;

	T.ShiftToRoot();

	if (T.IsEmpty())
		cout << "Tree is empty" << endl;
	else
	{
		total = DoSum(T);
	}

	cout << "Total: " << total << endl << endl;
}