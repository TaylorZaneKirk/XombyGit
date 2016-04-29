#include "MagicSquare.h"
#include <fstream>
using namespace std;

int r, c = 0;			//Counter variables

MagicSquare::MagicSquare(void)
{
}

void MagicSquare::Form(int **&MagicSquare, int SquareSize)
{
	//Forming the deminsions of the Array
	MagicSquare = new int *[SquareSize];
	for(r = 0; r < SquareSize; r++)
	{
		MagicSquare[r] = new int[SquareSize];
	}
}

MagicSquare::~MagicSquare(void)
{
}
