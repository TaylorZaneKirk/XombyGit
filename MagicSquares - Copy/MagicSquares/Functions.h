#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//-----------------------------------------------------------------
// Adds up all the values of a user designated row.
// @Param: int **MagicSquare - 2D array
// @Param: int SquareSize - Number of Rows/Columns
// @Returns: The sum of the row
//-----------------------------------------------------------------

int WhichRow = 0;		//User will define this with which row they would like to add together.
int WhichColumn = 0;	//User will define this with which column they would like to add together.
int WhichDiagonal = 0;	//User will define this with which diagonal they would like to add together.
int RowSum = 0;			//This will be used to store the sum of a single row of the array.
int ColumnSum = 0;		//This will be used to store the sum of a single column of the array.
int DiagonalSum = 0;	//This will be used to store the sum of a single diagonal of the array.
int r, c = 0;			//Counter variables.
int MagicSquareSum = 0;	//This will be used to store the value from the MagicSquares formula to test if the array is a magic square.

int SumRow(int **MagicSquare, int SquareSize)
{
	cout << "Message: Adding up the values of all the rows." << endl;

	for(WhichRow = 1; WhichRow <= SquareSize; WhichRow++)
	{
		for(c = 0; c < SquareSize; c++)
		{
			RowSum = RowSum + MagicSquare[WhichRow - 1][c];
		}
	}
	return(RowSum / SquareSize);
}

int SumColumn(int **MagicSquare, int SquareSize)
{
	for(WhichColumn = 1; WhichColumn <= SquareSize; WhichColumn++)
	{
		for(r = 0; r < SquareSize; r++)
		{
			ColumnSum = ColumnSum + MagicSquare[r][WhichColumn - 1];
		}
	}
	return(ColumnSum / SquareSize);
}

int SumDiagonal(int **MagicSquare, int SquareSize)
{
	for(WhichDiagonal = 1; WhichDiagonal <= 2; WhichDiagonal++)
	{
		if(WhichDiagonal == 1)
		{
			for(r = 0; r < SquareSize; r++)
			{
				DiagonalSum = DiagonalSum + MagicSquare[r][r];
			}
		}
		else
		{
			for(r = 0; r < SquareSize; r++)
			{
				DiagonalSum = DiagonalSum + MagicSquare[r][SquareSize-r-1];
			}
		}
	}
	return (DiagonalSum / 2);
}

bool CheckForMagic(int RowSum, int ColumnSum, int DiagonalSum, int SquareSize)
{
	MagicSquareSum = (SquareSize * ((SquareSize * SquareSize) + 1)) / 2;
	cout << "Message: Magic Square sum should total to: " << MagicSquareSum << endl;

	if(MagicSquareSum == RowSum && MagicSquareSum == ColumnSum && MagicSquareSum == DiagonalSum)
	{
		return(0);
	}
	else
	{
		return(1);
	}
}
