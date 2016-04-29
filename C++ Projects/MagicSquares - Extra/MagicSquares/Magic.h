#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
using namespace std;

//The following class represents a 2D array which forms a Square
class Magic
{
int **MagicSquare;		//Initializes a 2D array which will be defined dynamically
int *NumbersToUse;		//Initializes a dynamic array
int *SquareSize;		//Initializes a dynamic array which will store the integer that
						//will define the dimensions of the 2D array 'MagicSquare'
int r, c;				//Counter variables

private:
	int GetNonDupNumber(int);
	int SumRows(void);
	int SumColumns(void);
	int SumDiagonals(void);
	void PrintSquare(int, int, int, int);
	void FreeMemory(void);
	
public:
	Magic(void);
	void DefineSquare(int);
	void LoadSquare(void);
	bool MagicCheck(void);
	~Magic(void);
};

