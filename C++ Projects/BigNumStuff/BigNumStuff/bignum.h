#pragma once
#include <iostream>
struct Node
{
	int val;
	struct Node * next;
};

class bignum
{
	Node * root;
	int sign; //either -1 or +1

public:
	bignum(); //Default constructor that sets the number to 0
	bignum(int); //Constructor that sets the number to the int parameter
	bignum(char *); //String constructor
	bignum(const bignum&); //Copy constructor
	
	//overloaded friend operators
	friend bignum operator+(const bignum, const bignum);
	friend bignum operator*(const bignum, const bignum);
	bignum& operator=(const bignum&);

	void Print(void);

	~bignum();
};

