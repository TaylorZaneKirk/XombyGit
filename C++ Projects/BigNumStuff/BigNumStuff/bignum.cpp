#include <iostream>
#include <string>
#include "bignum.h"

using namespace std;

//Default constructor This forms the basic structure
//	of the big numbers
bignum::bignum()
{
	root = new Node;
	root->next = NULL;
	root->val = 0;
	sign = 1;
}

//Parameterized constructor. Requires that an integer
//	be passed to the constructor
bignum::bignum(int number)
{

	//Generic Node Constructor stuff
	root = new Node;
	root = NULL;
	if (number < 0){ sign = -1; number *= -1; }
	else{ sign = 1; }

	//Loop to continuously truncate parameter
	//	and store into linked Nodes
	while (number > 0)
	{
		Node *NextNode;

		NextNode = new Node;
		int digit = number % 1000;

		NextNode->val = digit;
		NextNode->next = root;
		root = NextNode;

		number /= 1000;
	}
}

//Parameterized constructor that uses another
//	bignum as a parameter. Deep-Copy
bignum::bignum(const bignum & Number)
{
	root = new Node;
	Node* Temp = Number.root;
	Node* Head = new Node;
	Node* Tail = new Node;

	Head = NULL;

	sign = Number.sign;
	while (Temp)
	{
		Node* NewNode = new Node;
		NewNode->val = Temp->val;
		if (!Head)
		{
			Head = NewNode;
			Tail = Head;
			Tail->next = NULL;
			Head->next = Tail;
		}
		else
		{
			Tail->next = NewNode;
			Tail = Tail->next;
			Tail->next = NULL;
		}

		Temp = Temp->next;
	}
	root = Head;
}

//Parameterized constructor
//	passes in a string, then
//	truncates into smaller
//	sized individual strings
//	followed by conversion 
//	of each into an integer
bignum::bignum(char* String)
{
	root = new Node;
	root = NULL;
	string temp;
	int Data;
	int count = 0;
	int Size = strlen(String);

	for (int i = (Size - 1); i >= 0; i--)
	{
		count++;
		temp = String[i] + temp;
		if (count == 3||i==0)
		{
			Node* NewNode = new Node;
			Data = stoi(temp);
			temp = "";
			count = 0;

			NewNode->val = Data;
			NewNode->next = root;
			root = NewNode;
		}

	}
	if (root->val < 0){ sign = -1; }
	else{ sign = 1; }

}

//Friend function that overloads the addition
//	operator
bignum operator+(const bignum First, const bignum Second)
{
	bignum *NewResult = new bignum;
	bignum Left = First;
	bignum Right = Second;
	Node* ReverseLeft = new Node;
	Node* ReverseRight = new Node;
	Node* NewNode = new Node;
	Node* ReverseNew = new Node;
	int Sum;
	int Carry = 0;

	NewNode = NULL;
	ReverseLeft = NULL;
	ReverseRight = NULL;
	ReverseNew = NULL;

	//Flipping "First"(Left) to be smallest
	//	largest significant digit.
	while (Left.root != NULL)
	{
		Node* temp = new Node;
		temp->next = ReverseLeft;
		temp->val = Left.root->val;
		ReverseLeft = temp;
		Left.root = Left.root->next;
	}

	//Flip "Second"(Right) to be smallest
	//	largest sig. digit
	while (Right.root != NULL)
	{
		Node* temp = new Node;
		temp->next = ReverseRight;
		temp->val = Right.root->val;
		ReverseRight = temp;
		Right.root = Right.root->next;
	}

	//While both nodes are not empty then add
	//	current values, followed by a test
	//	to see if the Sum is over 999, if
	//	so, divide by 1000, store the result in
	//	Carry, then modulo the Sum by 1000, and
	//	replace the old Sum with the Modulo Sum
	while (ReverseLeft != NULL && ReverseRight != NULL)
	{
		Node* temp = new Node;
		Sum = ReverseLeft->val + ReverseRight->val;
		Sum += Carry;

		if (Sum > 999)
		{
			Carry = Sum / 1000;
			Sum = Sum % 1000;
		}

		temp->val = Sum;
		temp->next = NewNode;
		NewNode = temp;
		ReverseLeft = ReverseLeft->next;
		ReverseRight = ReverseRight->next;
	}

	//If one node is empty, and other is not,
	//	continue attatching nodes to the end
	if (ReverseLeft == NULL && ReverseRight != NULL)
	{
		while (ReverseRight != NULL)
		{
			Node* temp = new Node;
			temp->val = ReverseRight->val;
			temp->next = NewNode;
			NewNode = temp;
			ReverseRight = ReverseRight->next;
		}
	}

	if (ReverseLeft != NULL && ReverseRight == NULL)
	{
		while (ReverseLeft != NULL)
		{
			Node* temp = new Node;
			temp->val = ReverseLeft->val;
			temp->next = NewNode;
			NewNode = temp;
			ReverseLeft = ReverseLeft->next;
		}
	}

	if (NewNode->val < 0){ NewResult->sign = -1; }
	else{ NewResult->sign = 1; }

	NewResult->root = NewNode;
	return *NewResult;
}

//Overloaded friend multiplication operator
//DOES NOT WORK
bignum operator*(const bignum First, const bignum Second)
{
	bignum *NewResult = new bignum;
	bignum Left = First;
	bignum Right = Second;
	Node* ReverseLeft = new Node;
	Node* ReverseRight = new Node;
	Node* NewNode = new Node;
	Node* ReverseNew = new Node;
	int Sum;
	int Carry = 0;

	NewNode = NULL;
	ReverseLeft = NULL;
	ReverseRight = NULL;
	ReverseNew = NULL;

	//Flipping "First"(Left) to be smallest
	//	largest significant digit.
	while (Left.root != NULL)
	{
		Node* temp = new Node;
		temp->next = ReverseLeft;
		temp->val = Left.root->val;
		ReverseLeft = temp;
		Left.root = Left.root->next;
	}

	//Flip "Second"(Right) to be smallest
	//	largest sig. digit
	while (Right.root != NULL)
	{
		Node* temp = new Node;
		temp->next = ReverseRight;
		temp->val = Right.root->val;
		ReverseRight = temp;
		Right.root = Right.root->next;
	}

}

//Deep copy assignment operator
bignum & bignum::operator=(const bignum &Number)
{
	if (this != &Number)
	{
		this->~bignum();
		
		bignum *Next = new bignum;

		root = new Node;
		Node* Temp = Number.root;
		Node* Head = new Node;
		Node* Tail = new Node;

		Head = NULL;

		sign = Number.sign;
		while (Temp)
		{
			Node* NewNode = new Node;
			NewNode->val = Temp->val;
			if (!Head)
			{
				Head = NewNode;
				Tail = Head;
				Tail->next = NULL;
				Head->next = Tail;
			}
			else
			{
				Tail->next = NewNode;
				Tail = Tail->next;
				Tail->next = NULL;
			}

			Temp = Temp->next;
		}
		root = Head;
		Next->root = root;
		*this->root = *Next->root;
	}
	return *this;
}

void bignum::Print(void)
{
	bignum p;
	bool first = true;
	p = *this;
	while (p.root != NULL)
	{
		if (p.root->val == 0){ cout << "000"; }
		if (p.root->val < 100 && p.root->val != 0
			&& first == false){ cout << "0"; }
		if (p.root->val != 0){ cout << p.root->val; }
		if (first == true){ first = false; }
		p.root = p.root->next;
	}
}

bignum::~bignum()
{
	Node* Current = root;
	while (Current != NULL)
	{
		Node* Next = Current->next;
		delete Current;
		Current = Next;
	}

}
