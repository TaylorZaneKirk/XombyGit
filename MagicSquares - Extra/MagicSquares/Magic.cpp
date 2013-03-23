#include "Magic.h"
using namespace std;


Magic::Magic(void)
{
}

//-----------------------------------------------------------------
// Parameterized construcor: Defines the variable 'SquareSize' to be
//		the same value as the variable that was passed into the
//		function. The function then declares the variable, (NumOfSpaces)
//		that will be used to define the size of the Array that will store
//		the numbers to be placed into the square, by multipling the number
//		of rows by the number of columns. The Function then defines the
//		dimensions of the 2D array that will be the Square to be tested.
//		The function then finally calls the LoadSquare function.
// @Param: int LocalSquareSize
// @Returns: void
//-----------------------------------------------------------------
void Magic::DefineSquare(int LocalSquareSize)
{
	SquareSize = new int;
	*SquareSize = LocalSquareSize;
	int NumOfSpaces = (*SquareSize * *SquareSize);
	NumbersToUse = new int [NumOfSpaces];
	MagicSquare = new int *[*SquareSize];
	for(r = 0; r < *SquareSize; r++)
	{
		MagicSquare[r] = new int[*SquareSize];
	}
	
	LoadSquare();
}

//-----------------------------------------------------------------
// Parameterized construcor: Initializes a counter variable, then
//		initializes another NumOfSpaces variable, defining it in the
//		same way as the previous function, followed by initializing
//		one more counter variable. The function then enters a for loop
//		to clear the NumbersToUse array of any previous values.
//		the function then enters another for loop to populate the
//		NumbersToUse array with integers returned by the GetNonDupNumber
//		function. The function then finally enters its last for loop
//		to fill the MagicSquare array with the numbers in the NumbersToUse array.
// @Param: void
// @Returns: void
//-----------------------------------------------------------------
void Magic::LoadSquare()
{
	
	int i = 0;
	int NumOfSpaces = (*SquareSize * *SquareSize);
	int Count = 0;

	for(i = 0; i < NumOfSpaces; i++)
	{
		NumbersToUse[i] = 0;
	}
	for(i = 0; i < NumOfSpaces; i++)
	{
		NumbersToUse[i] = GetNonDupNumber(NumOfSpaces);	
	}
	for(r = 0; r < *SquareSize; r++)
	{
		for(c = 0; c < *SquareSize; c++)
		{
			MagicSquare[r][c] = NumbersToUse[Count++];
		}
	}
	
}

//-----------------------------------------------------------------
// Parameterized construcor: initializes two counters variables, a
//		variable to store a random number between 1 and the value of
//		the NumOfSpaces variable. The function then enters a for loop
//		that checks if the value of CurrentValue is found anywhere
//		within the NumbersToUse array. If the value of CurrentValue is
//		found within the NumbersToUse array, the function calls itself
//		in order to continually loop until the NumbersToUse array is
//		filled with all the numbers between 1 and the value of the
//		NumOfSpaces variable in random order.
// @Param: int NumOfSpaces
// @Returns: int CurrentValue
//-----------------------------------------------------------------
int Magic::GetNonDupNumber(int NumOfSpaces)
{
	int i, j = 0;
	int CurrentValue = 0;
	CurrentValue = (rand()%NumOfSpaces) + 1;
	for(i = 0; i < NumOfSpaces; i++)
	{
		if(NumbersToUse[i] == CurrentValue)
		{
			return (GetNonDupNumber(NumOfSpaces));
		}	
	}
	return(CurrentValue);
}

//-----------------------------------------------------------------
// Parameterized construcor: Intializes a variable which will contain
//		constant of a MagicSquare with the dimensions that have been
//		previous defined. The function then initializes the Row, Column,
//		DiagonalConstant variables, then declares them by calling their
//		respective Sum functions. Then the function delcares the
//		MagicSquareSum variable by using the equation to determine the
//		Magic Square constant. The function then uses an if statement
//		to check the Row, Column, and Diagonal sum with the MagicSquareSum
//		to make sure all the values are equal.
// @Param: void
// @Returns: 0 if true, 1 if false
//-----------------------------------------------------------------
bool Magic::MagicCheck()
{
	int MagicSquareSum = 0;
	int RowConstant = SumRows();
	int ColumnConstant = SumColumns();
	int DiagonalConstant = SumDiagonals();

	MagicSquareSum = (*SquareSize * ((*SquareSize * *SquareSize) + 1)) / 2;
	if(MagicSquareSum == RowConstant && MagicSquareSum == ColumnConstant && MagicSquareSum == DiagonalConstant)
	{
		cout << "\nMessage: Magic Square Found!!" << endl;
		PrintSquare(RowConstant, ColumnConstant, DiagonalConstant, MagicSquareSum);
		FreeMemory();
		return(0);
	}
	else
	{
		return(1);
	}
}

//-----------------------------------------------------------------
// Parameterized construcor: Prints out a Square, along with the sums
//		of the Rows, Columns, Diagonals, and the MagicSquare constant.
// @Param: int RowConstant
// @Param: int ColumnConstant
// @Param: int DiagonalConstant
// @Param: int MagicSquareSum
// @Returns: void
//-----------------------------------------------------------------
void Magic::PrintSquare(int RowConstant, int ColumnConstant, int DiagonalConstant, int MagicSquareSum)
{
	for(r = 0; r < *SquareSize; r++)
	{
		for(c = 0; c < *SquareSize; c++)
		{
			cout << setw(3) << MagicSquare[r][c];
		}
		cout << endl;
	}
	cout << "Message: Sum of Rows: " << RowConstant << endl;
	cout << "Message: Sum of Columns: " << ColumnConstant << endl;
	cout << "Message: Sum of Diagonals: " << DiagonalConstant << endl;
	cout << "Message: Sums must equal: " << MagicSquareSum << endl;
}

//-----------------------------------------------------------------
// Parameterized construcor: Function initializes a counter variable
//		to keep track of which row is being added up, a variable to
//		store the sum of the current row, and a variable to store the
//		sum of the previous row. The function then enters a for nested
//		for loop that adds all the integers in a row then checks it against
//		the sum of the previous row. If all the rows equal the same amount
//		that value is returned to the function that called the SumRows
//		function, if all the rows do not equal the same amount, this function
//		returns a zero to the function that called the SumRows function.
// @Param: void
// @Returns: PreviousRow
//-----------------------------------------------------------------
int Magic::SumRows()
{
	int WhichRow = 0;
	int RowSum = 0;
	int PreviousRow = 0;

	for(WhichRow = 1; WhichRow <= *SquareSize; WhichRow++)
	{
		for(c = 0; c < *SquareSize; c++)
			RowSum = RowSum + MagicSquare[WhichRow - 1][c];
		if(PreviousRow == 0)
			{
				PreviousRow = RowSum;
			}
			else
			{
				if(PreviousRow == RowSum)
				{
					PreviousRow = RowSum;
				}
				else
				{
					return(0);
				}
			}
		RowSum = 0;
	}
	return(PreviousRow);
}

//-----------------------------------------------------------------
// Parameterized construcor: Function initializes a counter variable
//		to keep track of which Column is being added up, a variable to
//		store the sum of the current Column, and a variable to store the
//		sum of the previous Column. The function then enters a for nested
//		for loop that adds all the integers in a Column then checks it against
//		the sum of the previous Column. If all the Columns equal the same amount
//		that value is returned to the function that called the SumColumns
//		function, if all the Columns do not equal the same amount, this function
//		returns a zero to the function that called the SumColumns function.
// @Param: void
// @Returns: PreviousColumn
//-----------------------------------------------------------------
int Magic::SumColumns()
{
	int WhichColumn = 0;
	int ColumnSum = 0;
	int PreviousColumn = 0;
	for(WhichColumn = 1; WhichColumn <= *SquareSize; WhichColumn++)
	{
		for(r = 0; r < *SquareSize; r++)
			ColumnSum = ColumnSum + MagicSquare[r][WhichColumn - 1];
		if(PreviousColumn == 0)
			{
				PreviousColumn = ColumnSum;
			}
			else
			{
				if(PreviousColumn == ColumnSum)
				{
					PreviousColumn = ColumnSum;
				}
				else
				{
					return(0);
				}
			}
		ColumnSum = 0;
	}
	return(PreviousColumn);
}

//-----------------------------------------------------------------
// Parameterized construcor: Function initializes a counter variable
//		to keep track of which Diagonal is being added up, a variable to
//		store the sum of the current Diagonal, and a variable to store the
//		sum of the previous Diagonal. The function then enters a for nested
//		for loop that adds all the integers in a Diagonal then checks it against
//		the sum of the previous Diagonal. If all the Diagonals equal the same amount
//		that value is returned to the function that called the SumDiagonals
//		function, if all the Diagonals do not equal the same amount, this function
//		returns a zero to the function that called the SumDiagonals function.
// @Param: void
// @Returns: PreviousDiagonal
//-----------------------------------------------------------------
int Magic::SumDiagonals()
{
	int WhichDiagonal = 0;
	int DiagonalSum = 0;
	int PreviousDiagonal = 0;
	for(WhichDiagonal = 1; WhichDiagonal <= 2; WhichDiagonal++)
	{
		if(WhichDiagonal == 1)
		{
			for(r = 0; r < *SquareSize; r++)
				DiagonalSum = DiagonalSum + MagicSquare[r][r];
		}
		else
		{
			for(r = 0; r < *SquareSize; r++)
				DiagonalSum = DiagonalSum + MagicSquare[r][*SquareSize-r-1];
		}
		if(PreviousDiagonal == 0)
			{
				PreviousDiagonal = DiagonalSum;
			}
			else
			{
				if(PreviousDiagonal == DiagonalSum)
				{
					PreviousDiagonal = DiagonalSum;
				}
				else
				{
					return(0);
				}
			}
		DiagonalSum = 0;
	}
	return (PreviousDiagonal);
}

void Magic::FreeMemory(void)
{
	for(int i = 0; i < *SquareSize; i++)
	{
		delete[] MagicSquare[i];
	}
	delete[] MagicSquare;
	delete[] NumbersToUse;
	delete SquareSize;
}

Magic::~Magic(void)
{
}
