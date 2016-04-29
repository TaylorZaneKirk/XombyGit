#include <iomanip>
#include <iostream>
#include "Puzzle.h"
using namespace std;

const int PossibleDirections = 4;
int DirectionsX[PossibleDirections] = {0, 1, -1, 0};
int DirectionsY[PossibleDirections] = {1, 0, 0, -1};

Puzzle::Puzzle(void)
{
	ColorList = NULL;
	EmptySpaces = NULL;
}

void Puzzle::Form(int _size, int num_colors)
{
	Size = _size;
	NumColors = num_colors;

	PuzzleGrid = new int *[Size];
	FillCells();
	PlaceColors();
	GerminateNodes();
}

void Puzzle::FillCells(void)
{
	for(int i = 0; i < Size; i++)
	{
		PuzzleGrid[i] = new int [Size];
		for(int j = 0; j < Size; j++)
		{
			PuzzleGrid[i][j] = 0;
		}
	}
}

void Puzzle::PlaceColors(void)
{
	int xPos;
	int yPos;

	for(int i = 1; i <= NumColors; i++)
	{
		Color *NewColor = new Color;
		PositionList *NewFront = new PositionList;
		PositionList *NewBack = new PositionList;

		xPos = rand()%(Size);
		yPos = rand()%(Size);
		
		while(PuzzleGrid[xPos][yPos] != 0)
		{
			xPos = rand()%(Size);
			yPos = rand()%(Size);
		}

		NewColor->PathLength = 1;

		NewFront->xPos = xPos;
		NewFront->yPos = yPos;
		NewFront->next = NewBack;

		NewBack->xPos = xPos;
		NewBack->yPos = yPos;
		NewBack->next = NULL;

		NewColor->FrontNode = NewFront;
		NewColor->BackNode = NewBack;
		NewColor->ColorNum = i;
		NewColor->next = NULL;

		if(ColorList == NULL)
		{
			ColorList = NewColor;
		}
		else
		{
			NewColor->next = ColorList;
			ColorList = NewColor;
		}
		
		PuzzleGrid[xPos][yPos] = NewColor->ColorNum;
	}
}

int Puzzle::FixColors(int color_code)
{
	switch(color_code)
	{
	case 1: color_code = 9; break;
	case 2: color_code = 10; break;
	case 3: color_code = 12; break;
	case 4: color_code = 13; break;
	case 5: color_code = 14; break;
	}

	return color_code;
}

void Puzzle::FindEmpties(void)
{
	EmptySpaces = NULL;
	for(int i = 0; i < Size; i++)
	{
		for(int j = 0; j < Size; j++)
		{
			if(PuzzleGrid[i][j] == 0)
			{
				PositionList *NewEmpty = new PositionList;
				NewEmpty->xPos = i;
				NewEmpty->yPos = j;
				NewEmpty->next = NULL;

				if(EmptySpaces == NULL)
				{
					EmptySpaces = NewEmpty;
				}
				else
				{
					NewEmpty->next = EmptySpaces;
					EmptySpaces = NewEmpty;
				}
			}
		}
	}

	DisplayGrid();
	system("pause");

	if(EmptySpaces == NULL)
	{
		cout << "DONE!" << endl;
		system("pause");
	}
	else
	{
		cout << "Working..." << endl;
		system("pause");
		GrowNodes();
	}
}

void Puzzle::GerminateNodes(void)
{
	Color *ThisColor;
	Color *NewList = new Color;
	NewList = NULL;

	while(ColorList != NULL)
	{
		ThisColor = new Color(*ColorList);
		ThisColor->next = NULL;

		ThisColor = Move('l','f',ThisColor);
		ThisColor = Move('r','b',ThisColor);

		if(NewList == NULL)
		{
			NewList = ThisColor;
		}
		else
		{
			ThisColor->next = NewList;
			NewList = ThisColor;
		}

		ColorList = ColorList->next;
	}
	ColorList = NewList;
	FindEmpties();
}

Color* Puzzle::Move(char which_direction, 
	char which_node, Color* &this_color)
{
	Color *tempColor = new Color;
	tempColor = this_color;
	int xPos;
	int yPos;
	int xChange = 0;
	int yChange = 0;

	if(which_node == 'f')
	{
		xPos = tempColor->FrontNode->xPos;
		yPos = tempColor->FrontNode->yPos;
	}
	else
	{
		xPos = tempColor->BackNode->xPos;
		yPos = tempColor->BackNode->yPos;
	}
	
	switch(which_direction)
	{
	case 'u': xChange = -1; break;
	case 'd': xChange = 1; break;
	case 'l': yChange = -1; break;
	case 'r': yChange = 1; break;
	}

	xPos = xPos + xChange;
	yPos = yPos + yChange;

	if(IsPossible(xPos, yPos))
	{
		PuzzleGrid[xPos][yPos] = tempColor->ColorNum;

		PositionList *NewPoint = new PositionList;
		NewPoint->xPos = xPos;
		NewPoint->yPos = yPos;
		tempColor->PathLength++;

		if(which_node == 'f')
		{
			NewPoint->next = tempColor->FrontNode;
			tempColor->FrontNode = NewPoint;
		}
		else
		{
			NewPoint->next = NULL;
			tempColor->BackNode = NewPoint;
		}
	}
	return tempColor;
}

void Puzzle::GrowNodes(void)
{
	Color *tempColor;
	Color *NewList;
	Color *ChoiceList;
	PositionList *AddPoint;
	while(EmptySpaces != NULL)
	{
		
		int PathCost = 99;

		int xPos = EmptySpaces->xPos;
		int yPos = EmptySpaces->yPos;

		for(int i = 0; i < PossibleDirections; i++)
		{
			NewList = new Color;
			NewList = NULL;
			
			int ThisX = xPos + DirectionsX[i];
			int ThisY = yPos + DirectionsY[i];


			while(ColorList != NULL)
			{
				tempColor = new Color(*ColorList);
				tempColor->next = NULL;

				int FrontX = tempColor->FrontNode->xPos;
				int FrontY = tempColor->FrontNode->yPos;
				int BackX = tempColor->BackNode->xPos;
				int BackY = tempColor->BackNode->yPos;

				if(FrontX == ThisX && FrontY == ThisY)
				{
					if(tempColor->PathLength < PathCost)
					{
						int NumNeighbors = 0;
						PuzzleGrid[xPos][yPos] = tempColor->ColorNum;
						for(int j = 0; j < PossibleDirections; j++)
						{
							int SomeX = xPos + DirectionsX[j];
							int SomeY = yPos + DirectionsY[j];
							if(IsPossible(SomeX, SomeY))
							{
								int ThisCell = PuzzleGrid[SomeX][SomeY];
								if(ThisCell == tempColor->ColorNum)
								{
									NumNeighbors++;
								}
							}
						}
						if(NumNeighbors < 2)
						{
							PathCost = tempColor->PathLength;
							AddPoint = new PositionList(*EmptySpaces);
							AddPoint->next = tempColor->FrontNode;
							tempColor->FrontNode = AddPoint;
							tempColor->PathLength++;
						}
					}
				}

				if(BackX == ThisX && BackY == ThisY)
				{
					if(tempColor->PathLength < PathCost)
					{
						int NumNeighbors = 0;
						PuzzleGrid[xPos][yPos] = tempColor->ColorNum;
						for(int j = 0; j < PossibleDirections; j++)
						{
							int SomeX = xPos + DirectionsX[j];
							int SomeY = yPos + DirectionsY[j];
							if(IsPossible(SomeX, SomeY))
							{
								int ThisCell = PuzzleGrid[SomeX][SomeY];
								if(ThisCell == tempColor->ColorNum)
								{
									NumNeighbors++;
								}
							}
						}
						if(NumNeighbors < 2)
						{
							PathCost = tempColor->PathLength;
							AddPoint = new PositionList(*EmptySpaces);
							AddPoint->next = NULL;
							tempColor->BackNode = AddPoint;
							tempColor->PathLength++;
						}
					}
				}
				tempColor->next = NewList;
				NewList = tempColor;
				ColorList = ColorList->next;
			}
			ColorList = new Color(*NewList);
		}
		EmptySpaces = EmptySpaces->next;
	}
	FindEmpties();
}


bool Puzzle::IsPossible(int x, int y)
{
//Function to test if a given (x,y) coordinate is located off of the grid

	if(x > Size - 1 || x < 0 || y > Size - 1 || y < 0
		|| PuzzleGrid[x][y] != 0)
	{
		return false;
	}

	int CommonNeighbor = 0;

	for(int i = 0; i < PossibleDirections; i++)
	{
		int NeighborX = x + DirectionsX[i];
		int NeighborY = y + DirectionsY[i];

		if(!(NeighborX > Size - 1 || NeighborX < 0 || NeighborY > Size - 1
			|| NeighborY < 0))
		{
			if(PuzzleGrid[NeighborX][NeighborY] ==
				PuzzleGrid[x][y])
			{
				CommonNeighbor++;
			}
		}
	}
	
	if(CommonNeighbor = 1)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

void Puzzle::DisplayGrid(void)
{
	//For loop to display the "loaded" array
	for(int i = 0; i < Size; i++)
	{
		for(int j = 0; j < Size; j++)
		{
			cout << setw(3) << PuzzleGrid[i][j];
		}
		cout << endl;
	}
}

Puzzle::~Puzzle(void)
{
}
