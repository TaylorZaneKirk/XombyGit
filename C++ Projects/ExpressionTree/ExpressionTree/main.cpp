//Name: Taylor Kirk
// 3/4/2016
// Prof. Stringfellow
// Expression Trees


#include <iostream>
#include <fstream>
#include "BTree.h"
using namespace std;

void DoBuilding(BTree  & T, ifstream & infile, char dir);
/*precond: T is created and infile is open for reading and file is in "correct" format
postcond:  Reads the file and builds up the data in the subtree referenced by the cursor in preOrder
dir is the left or right child position the next item goes into
checks:  none  */

void BuildTree(BTree  & T, ifstream & infile);
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

void Reduce(BTree & T);
/*precond:  T is created
postcond: Traverses the binary tree T in preorder. 
T will now be the reduced form of #T. T's cursor is referencing the root.
checks:   none */

void AllConsts(BTree & T);
/*precond:  T is created
postcond: Traverses the binary tree T in preorder.
Visit a node means print out its data to monitor.  T = #T, except T's
cursor is referencing the root. Returns true if all nodes contain no variables
checks:   none */

void Evaluate(BTree & T);
/*precond:  T is created
postcond: Traverses the binary tree T in preorder.
Visit a node means return the data of the node.  T = #T, except T's
cursor is referencing the root. Returns the integer representation
of the solution of the tree (Solves the expression)
checks:   none */

bool DoAllConsts(BTree & T);
/*precond:  T is created
postcond: Traverses the binary tree T in preorder.
Visit a node means return the data of the node.  T = #T,
Returns true if all nodes contain no variables
checks:   none */

int DoEvaluate(BTree & T);
/*precond:  T is created
postcond: Traverses the binary tree T in preorder.
Visit a node means return the data of the node.  T = #T,
Returns the integer representation of the solution of 
the tree (Solves the expression)
checks:   none */

void DoReduce(BTree & T);
/*precond:  T is created
postcond: Traverses the binary tree T in preorder.
T will now be the reduced form of #T. T's cursor is referencing the root.
checks:   none */

void GreetMessage(void);
/*precond:  none
postcond: Greets user to program.
checks:   none */

void ExitMessage(void);
/*precond:  none
postcond: Informs user that program will soon be terminated.
checks:   none */

int main()
{
	BTree T;
	ifstream infile;
	char infilename[40];

	// CALL FUNCTION TO SHOW INTRO HERE
	GreetMessage();

	//open input file
	cout << " Please enter name of input file:  ";
	cin >> infilename;
	cout << endl;
	infile.open(infilename);

	//Build the tree and print it out in InOrder
	BuildTree(T, infile);

	//close input file
	infile.close();

	//CALL FUNCTION TO SHOW EXIT MESSAGE HERE
	ExitMessage();

	system("pause");

	return 0;
}

void GreetMessage()
{
	cout << "Expression Tree Program - Build, Evaluate, and Reduce Trees" << endl;
}

void ExitMessage()
{
	cout << "Thank you for using the Expression Tree Program" << 
		endl << "Terminating Program..." << endl;
}

void DoBuilding(BTree & T, ifstream & infile, char dir)
{
	char item;

	//read item
	item = infile.get();

	//if not eof (by bad data file) and not end of line (\n)
	if (!infile.eof() && item != '\n')
	{
		while (item == ' ')
			item = infile.get();

		//build root of new subtree
		if (T.IsEmpty())
			T.CreateFirstNode(item);
		else if (dir == 'L')
		{
			T.AddLeft(item);
			T.ShiftLeft();
		}
		else
		{
			T.AddRight(item);
			T.ShiftRight();
		}

		if ((item == '+') || (item == '-') || (item == '/') || (item == '*'))
		{
			//build left subtree of subtree
			DoBuilding(T, infile, 'L');
		}
		else
		{
			if (T.HasParent())
				T.ShiftUp();
			while (T.HasParent() && T.HasRightChild())
				T.ShiftUp();
			//build right subtree of subtree
			DoBuilding(T, infile, 'R');
		}


		//get back to root of subtree 
		if (T.HasParent())
			T.ShiftUp();
	}
	
}


void BuildTree(BTree  & T, ifstream & infile)
{
	char* NumTrees = new char[2];

	//get num of lines
	infile.getline(NumTrees, 3);

	for (int i = 0; i < atoi(NumTrees); i++)
	{
		T.ClearTree();
		DoBuilding(T, infile, 'L');
		T.ShiftToRoot();
		Preorder(T);
		Inorder(T);
		Postorder(T);
		AllConsts(T);
		Reduce(T);
	}
}

//called by InOrder
void DoInOrder(BTree  & T)
{
	ItemType Item;

	//2 base cases: empty tree or subtree is a leaf
	if (!T.IsEmpty())
	{
		//not a leaf, has a left child, traverse left subtree of subtree in InOrder
		if (T.HasLeftChild())
		{
			cout << "( ";
			T.ShiftLeft();
			DoInOrder(T);
			T.ShiftUp();
		}

		//display root of subtree
		T.RetrieveItem(Item);
		cout << char(Item) << "  ";

		//not a leaf, has a right child, traverse right subtree of subtree in InOrder
		if (T.HasRightChild())
		{
			T.ShiftRight();
			DoInOrder(T);
			T.ShiftUp();
			cout << ") ";
		}
	}
}

void Inorder(BTree  & T)
{
	T.ShiftToRoot();

	if (T.IsEmpty())
		cout << "Tree is empty" << endl;
	else
	{
		cout << "Infix form (parenthesized) is: ";
		DoInOrder(T);
	}

	cout << endl;
}

//DEFINE ADDITIONAL NON-MEMBER FUNCTIONS HERE

void Reduce(BTree & T)
{
	T.ShiftToRoot();

	if (T.IsEmpty())
	{
		cout << "Tree is empty" << endl;
	}
	else
	{
		DoReduce(T);
		cout << "Reduced infix expression is: ";
		DoInOrder(T);
	}
	cout << endl << endl;
}

void Preorder(BTree  & T)
{
	T.ShiftToRoot();

	if (T.IsEmpty())
		cout << "Tree is empty" << endl;
	else
	{
		cout << "Input prefix expression is: ";
		DoPreOrder(T);
	}

	cout << endl;
}

void Postorder(BTree  & T)
{
	T.ShiftToRoot();

	if (T.IsEmpty())
		cout << "Tree is empty" << endl;
	else
	{
		cout << "Postfix form is: ";
		DoPostOrder(T);
	}

	cout << endl;
}

void AllConsts(BTree & T)
{
	T.ShiftToRoot();

	if (T.IsEmpty())
	{
		cout << "Tree is empty" << endl;
	}
	else
	{
		if (DoAllConsts(T))
			Evaluate(T);
	}
}

void Evaluate(BTree & T)
{
	int Solution;
	T.ShiftToRoot();

	if (T.IsEmpty())
	{
		cout << "Tree is empty" << endl;
	}
	else
	{
		Solution = DoEvaluate(T);
		cout << "Evaluation is: " << Solution;
	}
	cout << endl;
}

//called by PreOrder
void DoPreOrder(BTree  & T)
{
	ItemType Item;

	//2 base cases: empty tree or subtree is a leaf
	if (!T.IsEmpty())
	{
		//display root of subtree
		T.RetrieveItem(Item);
		cout << char(Item) << "  ";

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
		cout << char(Item) << "  ";
	}
}

bool DoAllConsts(BTree & T)
{
	ItemType Item;

	//2 base cases: empty tree or subtree is a leaf
	if (!T.IsEmpty())
	{
		//display root of subtree
		T.RetrieveItem(Item);
		if (!((char)Item == '+' || (char)Item == '-' || (char)Item == '*' || (char)Item == '/' ||
			(Item >= int('0') && Item <= int('9'))))
		{
			return false;
		}

		//not a leaf, has a left child, traverse left subtree of subtree in PreOrder
		if (T.HasLeftChild())
		{
			T.ShiftLeft();
			if (DoAllConsts(T))
				T.ShiftUp();
			else
				return false;
				
		}

		//not a leaf, has a right child, traverse right subtree of subtree in PreOrder
		if (T.HasRightChild())
		{
			T.ShiftRight();
			if (DoAllConsts(T))
				T.ShiftUp();
			else
				return false;
		}

		return true;
	}

	return false;
}

int DoEvaluate(BTree & T)
{
	int temp;

	//Not Empty and Has Children
	if (!T.IsEmpty() && !T.HasNoChildren())
	{
		int LeftItem;
		int RightItem;
		int Solution;
		char thisOperator;

		if (T.HasLeftChild())
		{
			T.ShiftLeft();
			LeftItem = DoEvaluate(T);
			T.ShiftUp();
		}

		if (T.HasRightChild())
		{
			T.ShiftRight();
			RightItem = DoEvaluate(T);
			T.ShiftUp();
		}

		//Get Operator
		T.RetrieveItem(temp);
		thisOperator = char(temp);

		if (thisOperator == '+')
		{
			Solution = LeftItem + RightItem;
		}
		else if (thisOperator == '-')
		{
			Solution = LeftItem - RightItem;
		}
		else if (thisOperator == '*')
		{
			Solution = LeftItem * RightItem;
		}
		else if (thisOperator == '/')
		{
			Solution = LeftItem / RightItem;
		}

		return Solution;
	}
	else
	{
		if (!T.IsEmpty())
		{
			T.RetrieveItem(temp);
			return temp - 48;
		}
	}
	return 0;
}

void DoReduce(BTree & T)
{
	int temp;

	//Not Empty and Has Children
	if (!T.IsEmpty() && !T.HasNoChildren())
	{
		ItemType LeftItem;
		ItemType RightItem;
		char Solution;
		char thisOperator;

		if (T.HasLeftChild())
		{
			T.ShiftLeft();
			DoReduce(T);
			T.RetrieveItem(LeftItem);
			T.ShiftUp();
		}

		if (T.HasRightChild())
		{
			T.ShiftRight();
			DoReduce(T);
			T.RetrieveItem(RightItem);
			T.ShiftUp();
		}

		//Get Operator
		T.RetrieveItem(temp);
		thisOperator = char(temp);

		//Addition
		if (thisOperator == '+')
		{
			if (char(LeftItem) == '0')
			{
				T.ShiftRight();
				BTree N(T);
				T.ShiftUp();
				T.SwapSubTrees(N);
			}
			else if (char(RightItem) == '0')
			{
				T.ShiftLeft();
				BTree N(T);
				T.ShiftUp();
				T.SwapSubTrees(N);
			}
			//If both have no variables
			else if ((LeftItem >= 48 && LeftItem <= 57) &&
				(RightItem >= 48 && RightItem <= 57))
			{
				Solution = char((LeftItem + RightItem) - 48);
				T.ChangeItem(Solution);
				T.RemoveLeft();
				T.RemoveRight();
			}

		}
		//Substraction
		else if (thisOperator == '-')
		{
			if (char(LeftItem) == '0')
			{
				T.ShiftRight();
				BTree N(T);
				T.ShiftUp();
				T.SwapSubTrees(N);
			}
			else if (char(RightItem) == '0')
			{
				T.ShiftLeft();
				BTree N(T);
				T.ShiftUp();
				T.SwapSubTrees(N);
			}
			//If both have no variables
			else if ((LeftItem >= 48 && LeftItem <= 57) &&
				(RightItem >= 48 && RightItem <= 57))
			{
				Solution = char(LeftItem - RightItem + 48);
				T.ChangeItem(Solution);
				T.RemoveLeft();
				T.RemoveRight();
			}
		}
		//Multiplication
		else if (thisOperator == '*')
		{
			if (char(LeftItem) == '0')
			{
				T.ShiftLeft();
				BTree N(T);
				T.ShiftUp();
				T.SwapSubTrees(N);
			}
			else if (char(RightItem) == '0')
			{
				T.ShiftRight();
				BTree N(T);
				T.ShiftUp();
				T.SwapSubTrees(N);
			}
			else if (char(LeftItem) == '1')
			{
				T.ShiftRight();
				BTree N(T);
				T.ShiftUp();
				T.SwapSubTrees(N);
			}
			else if (char(RightItem) == '1')
			{
				T.ShiftLeft();
				BTree N(T);
				T.ShiftUp();
				T.SwapSubTrees(N);
			}
			//If both have no variables
			else if ((LeftItem >= 48 && LeftItem <= 57) &&
				(RightItem >= 48 && RightItem <= 57))
			{
				Solution = char((LeftItem - 48) * (RightItem - 48) + 48);
				T.ChangeItem(Solution);
				T.RemoveLeft();
				T.RemoveRight();
			}
		}
		//Division
		else if (thisOperator == '/')
		{
			if (char(RightItem) == '1')
			{
				T.ShiftLeft();
				BTree N(T);
				T.ShiftUp();
				T.SwapSubTrees(N);
			}
			//If both have no variables
			else if ((LeftItem >= 48 && LeftItem <= 57) &&
				(RightItem >= 48 && RightItem <= 57))
			{
				Solution = char((LeftItem - 48) / (RightItem - 48) + 48);
				T.ChangeItem(Solution);
				T.RemoveLeft();
				T.RemoveRight();
			}
		}

		return;
	}
}

