//---------------------------------------------------------------------
//
// Name: Taylor Kirk
//
// Course: CS 1063, Section 202, Spring 2013
//
// Purpose: This program will populate a dynamic 2D array with
//			random numbers and then test the array to see if
//			it meets the requirments of being a Magic Square,
//			if the square is not magic, then the program will
//			delete the previous values within the square and
//			repopulate, then test the square again.
//
// Input: The deminsions of the array to be formed is provided as
//			an arguement passed in from the command line
//
// Output: The program will initially output the number of squares
//			that have been tested, then let the user know if a 
//			Magic Square has been found, then print out an array that 
//			has tested true for being a magic square, followed by printing
//			out the sums of the Rows, Columns, and Diagonals, as
//			well as the value of the Magic Square constant.
//
// Usage: What the command line should look like:
//        MagicSquares.exe [Integer X (where X will define X Rows by X Columns)]
//---------------------------------------------------------------------

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "Magic.h"
using namespace std;

int main(int argc, char *argv[])
{
	long int SquaresTested = 0;	//This will be used to store the number of Squares that have been tested
	int SquareSize = 0;			//This will be used to define the deminsions of the square.
	int Dimensions = 0;
	Magic Square;				//This simply sets up a variable of the type 'Magic,' which will be used throughout this program

	//For loop for some error checking.
	//Makes sure more than just 1 parameter is being passed.
	if(argc < 2)
	{
		cout << "Error: Invalid number of parameters. \n"
			<< "Usage: MagicSquares.exe [An integer X (where 'X' will define 'X' Rows by 'X' Columns)] \n" << endl;
		cout << "Please enter an integer for 'X:' ";
		cin >> Dimensions;
		Square.DefineSquare(Dimensions);
		cout << "Message: Number of squares tested: " << ++SquaresTested;
		while(Square.MagicCheck() == 1)
		{
			cout << "\rMessage: Number of squares tested: " << ++SquaresTested << flush;
			Square.LoadSquare();
		}
	}
	else
	{
		srand(time(NULL));					//Seeds the rand function with a random set of numbers derived from the system time
		cout << "Message: Searching for a Magic Square..." << endl;
		SquareSize = atoi(argv[1]);			//Forming the deminsions of the Array
		Square.DefineSquare(SquareSize);	//Initializes the 2D array, and sets the dimensions of the square
		cout << "Message: Number of squares tested: " << ++SquaresTested;
		
		//While loop that will test the current square to see if the square is magic.
		//If the square that was tested is not magic, the loop increments the 'SquaresTested'
		//variable by 1, then calls the 'LoadSquare' function to create a new Square to be tested.
		//This loop will continue until a MagicSquare has been formed and tests as true.
		while(Square.MagicCheck() == 1)
		{
			cout << "\rMessage: Number of squares tested: " << ++SquaresTested << flush;
			Square.LoadSquare();
		}
	}

	system("pause > 0");
	return 0;
}