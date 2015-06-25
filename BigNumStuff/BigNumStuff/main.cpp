//***********************************************************************
//							Big Numbers
//							Name: Taylor Kirk
//						Data Structures Date: 04/22/2015
//***********************************************************************
//		This program demonstrates how to deal with linked list in model-
//	ling large nuumbers and the manipulation thereof.
//			
//***********************************************************************

#include <iostream>
#include "bignum.h"
using namespace std;

void main(void)
{
	bignum x, y, z("123456789"), m(11097), d(m);

	cout << "d=";
	d.Print();
	cout << endl;

	x = z + m;
	
	cout << "x=";
	x.Print();
	cout << endl;

	//y = x * m;

	cout << "y=";
	//y.Print();
	cout << endl;

	//y = 2 * z + m + 4;
	//cout << "y modified is" << y << endl;
	z = 100000000;
	z.Print();
	//for (int i = 0; i<10; i++)z = 1 + z; //runs the overloaded = and +
//	cout << "The value of z is" << z << endl;
}
