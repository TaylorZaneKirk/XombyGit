//---------------------------------------------------------------------
//
// Name: Taylor Kirk
//
// Course: CS 1063, Section 202, Spring 2013
//
// Purpose: This program will test to see if an 2D array populated
//			with numbers could be considered to be a magic square.
//			This means that by adding all the numbers in a row in any
//			direction would result in a single constant number.
//
// Input: The list of numbers used to populate the array will be provided
//			in the form of a file.
//
// Output: True if the array is a magic square, False if it is not.
//
// Usage: What the command line should look like:
//        MagicSquares.exe [Input File] [Rows] [Columns]
//---------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Functions.h"
using namespace std;


int main(int argc, char *argv[])
{
	int r, c = 0;			//Counter variables
	int **MagicSquare;		//Initializing a 2D array which will be defined dynamically.
	int SquareSize = 0;		//This will be used to define the deminsions of the square.
	int WhichRow = 0;		//User will define this with which row they would like to add together.
	int WhichDiagonal = 0;	//User will define this with which diagonal they would like to add together.
	int RowSum = 0;			//This will be used to store the sum of a single row of the array.
	int ColumnSum = 0;		//This will be used to store the sum of a single column of the array.
	int DiagonalSum = 0;	//This will be used to store the sum of a single diagonal of the array.
	int MagicSquareSum = 0;	//This will be used to store the value from the MagicSquares formula to test if the array is a magic square.

	//For loop for some error checking.
	//Makes sure more than just 1 parameter is being passed.
	if(argc < 3)
	{
		cout << "Error: Invalid number of parameters. \n"
			<< "Usage: MagicSquares.exe [input file] [#rows] [#columns] \n";
		system("Pause");
		exit(0);
	}
	else
	{
		//Printing the name of the currently used input file to the screen.
		cout << "Input file: " << argv[1]<< endl;

		//Preparing the input file handler and then opening
		//the input file, as well as error checking to
		//ensure that the file was opened correctly.
		ifstream infile;
		infile.open(argv[1]);

		//Error checking portion
		if(!infile)
		{
			cout << "Error: Could not find and/or open specified input file." << endl;
			system("pause");
			exit(0);
		}
		else
		{
			cout << "Message: Specified input file was opened successfully." << endl;
		}

		//Preparing the output file handler and then creating
		//the output file, as well as error checking to
		//make sure that the file was created successfully.
		ofstream outfile;
		outfile.open("MagicSquares_Output.txt");

		//Error checking portion
		if(!outfile)
		{
			cout << "Error: Could not create an output file." << endl;
			system("pause");
			exit(1);
		}
		else
		{
			cout << "Message: Output file was created successfully." << endl;
		}

		//Forming the deminsions of the Array
		SquareSize = atoi(argv[2]);
		MagicSquare = new int *[SquareSize];
		for(r = 0; r < SquareSize; r++)
		{
			MagicSquare[r] = new int[SquareSize];
		}

		//Using a nested for loop to
		//read values in from the input file
		//and storing them within the 2D Array
		cout << "Message: Loading array from input file..." << endl;
		for(r = 0; r < SquareSize; r++)
		{
			for(c = 0; c < SquareSize; c++)
			{
				infile >> MagicSquare[r][c];
				cout << setw(3) << MagicSquare[r][c];
			}
			cout << endl;
		}

		//Using a nested for loop to
		//write values from the array
		//into the output file
		cout << "Message: Writing array values into output file..." << endl;
		for(r = 0; r < SquareSize; r++)
		{
			for(c = 0; c < SquareSize; c++)
			{
				outfile << setw(3) << MagicSquare[r][c];
			}
			outfile << endl;
		}

		RowSum = SumRow(MagicSquare, SquareSize);

		ColumnSum = SumColumn(MagicSquare, SquareSize);

		DiagonalSum = SumDiagonal(MagicSquare, SquareSize);

		if(CheckForMagic(RowSum, ColumnSum, DiagonalSum, SquareSize) == 0)
		{
			cout << "Message: This square is magical!!" << endl;
		}
		else
		{
			cout << "Message: No magic here..." << endl;
		}
	}
	
	system("pause");
	return 0;
}