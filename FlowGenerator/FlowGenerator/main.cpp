//---------------------------------------------------------------------
//
// Name: Taylor Kirk
//
// Course: CS 1063, Section 202, Spring 2013
//
// Purpose: This program will prompt the user to enter a size of a
//				square (With the number representing both length and
//				width). The user is also prompted to enter a number
//				for how many colors they would like to be included
//				in the puzzle. The program will then generate a
//				2D-Array of either 0's, or a number corresponding
//				to a color code in random locations. Every color will
//				have two locations within the array. The program will
//				then construct a grid to the specifications of the
//				user-defined size using ASCII characters, representing
//				0's with character #176 and representing color markers
//				with a colored character #254.
//
// Input: The user will be asked to specify the size of the puzzle they
//			wish to form, and to specify how many colors they would like
//			to be included in the puzzle.
//
// Output: The program will output the array in it's original format
//			(0's and color codes), followed by the "visual" representation
//			of the puzzle.
//
// Usage: Enter two integers for size and number of colors.
//---------------------------------------------------------------------

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "Puzzle.h"
using namespace std;

void main()
{
	int Size;			//integer to store puzzle size
	int NumColors;		//integer to store number of colors to use
	Puzzle Flow;		//This is the variable for the "Puzzle" to be formed

	srand(time(NULL));


	//This portion is prompting values for the previous integer
	//	variables to be passed onto the "Form()" function to create,
	//	and display the puzzle.
	cout << "Please enter size of puzzle: ";
	cin >> Size;
	cout << "Please enter number of colors to use: ";
	cin >> NumColors;
	cout << "Forming Puzzle..." << endl;
	Flow.Form(Size, NumColors);
	system("pause > 0");
}