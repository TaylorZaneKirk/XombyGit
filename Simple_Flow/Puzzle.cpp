#include <iomanip>
#include <iostream>
#include "Puzzle.h"
#include <Windows.h>
using namespace std;

const int PossibleDirections = 4;
int DirectionsX[PossibleDirections] = {0, 0, -1, 1};
int DirectionsY[PossibleDirections] = {-1, 1, 0, 0};

Puzzle::Puzzle(void)
{
	TopFlow = NULL;
	EmptyList = NULL;
	PuzzleComplete = false;
}

void Puzzle::Form(int _size, int num_colors)
{
	Size = _size;
	NumColors = num_colors;
	ColorCount = NumColors;

	Grid = new int *[Size];
	GridMin = 0;
	GridMax = Size - 1;
	GridMid = GridMax / 2;

	ExpansionMethod = 1;
	
	FillCells();
	
	for(int i = 0; i < NumColors; i++)
	{
		PlaceColors(i + 1);
	}

	FindEmpties();
}

void Puzzle::FillCells(void)
{
	for(int i = 0; i < Size; i++)
	{
		Grid[i] = new int [Size];
		for(int j = 0; j < Size; j++)
		{
			Grid[i][j] = 0;
		}
	}
	Grid[GridMin + 1][GridMin + 1] = 99;
	Grid[GridMin + 1][GridMax - 1] = 99;
	Grid[GridMax - 1][GridMin + 1] = 99;
	Grid[GridMax - 1][GridMax - 1] = 99;
	Grid[GridMid][GridMid] = 99;
}

void Puzzle::PlaceColors(int which_color)
{
	int WhichColor = which_color;
	int xPos;
	int yPos;
	int AdjacentEmpties = 0;

	xPos = rand()%(Size);
	yPos = rand()%(Size);

	for(int z = 0; z < PossibleDirections; z++)
	{
		int AdjacentX = xPos + DirectionsX[z];
		int AdjacentY = yPos + DirectionsY[z];
		if(OnGrid(AdjacentX, AdjacentY))
		{
			if(Grid[AdjacentX][AdjacentY] == 0
				||Grid[AdjacentX][AdjacentY] == 99)
			{
				AdjacentEmpties++;
			}
		}
	}

	while(Grid[xPos][yPos] != 0 || AdjacentEmpties <= 1)
	{
		AdjacentEmpties = 0;
		xPos = rand()%(Size);
		yPos = rand()%(Size);

		for(int z = 0; z < PossibleDirections; z++)
		{
			int AdjacentX = xPos + DirectionsX[z];
			int AdjacentY = yPos + DirectionsY[z];
			if(OnGrid(AdjacentX, AdjacentY))
			{
				if(Grid[AdjacentX][AdjacentY] == 0
					||Grid[AdjacentX][AdjacentY] == 99)
				{
					AdjacentEmpties++;
				}
			}
		}
	}

	if(ExpansionMethod == 1)
	{
		ExpansionMethod = 0;
	}
	else 
		ExpansionMethod = 1;
	
	FlowList *NewFlow = new FlowList;
	PositionList *NewFront = new PositionList;

	NewFront->xPos = xPos;
	NewFront->yPos = yPos;
	NewFront->next = NULL;

	PositionList *NewBack = new PositionList(*NewFront);
	PositionList *NewVertex = new PositionList(*NewFront);

	NewFlow->FrontNode = NewFront;
	NewFlow->BackNode = NewBack;
	NewFlow->Vertex = NewVertex;
	NewFlow->ColorCode = WhichColor;
	NewFlow->ThisExpansionMethod = ExpansionMethod;
	NewFlow->NumExpansions = 0;
	NewFlow->next = TopFlow;
	TopFlow = NewFlow;
	Grid[xPos][yPos] = NewFlow->ColorCode;
	ExpandVertex();
	WhichColor++;
}

bool Puzzle::ExpandVertex(void)
{
	int xPos = TopFlow->Vertex->xPos;
	int yPos = TopFlow->Vertex->yPos;

	if(TopFlow->ThisExpansionMethod == 0)
		HorizontalExpansion();
	if(TopFlow->ThisExpansionMethod == 1)
		VerticalExpansion();
			
	if(TopFlow->NumExpansions != 3)
	{
		return false;
	}
	return true;
}

void Puzzle::HorizontalExpansion(void)
{
	int xPos = TopFlow->Vertex->xPos;
	int yPos = TopFlow->Vertex->yPos;
	int LeftY = yPos - 1;
	int RightY = yPos + 1;
	int UpX = xPos - 1;
	int DownX = xPos + 1;

	if(OnGrid(xPos, LeftY))
	{
		Grid[xPos][LeftY] = TopFlow->ColorCode;
		TopFlow->FrontNode->xPos = xPos;
		TopFlow->FrontNode->yPos = LeftY;
		TopFlow->NumExpansions++;
	}
	else
	{
		if(xPos > GridMid)
		{
			if(OnGrid(UpX, yPos))
			{
				Grid[UpX][yPos] = TopFlow->ColorCode;
				TopFlow->FrontNode->xPos = UpX;
				TopFlow->FrontNode->yPos = yPos;
				TopFlow->NumExpansions++;
			}
		}
		else
		{
			if(OnGrid(DownX, yPos))
			{
				Grid[DownX][yPos] = TopFlow->ColorCode;
				TopFlow->FrontNode->xPos = DownX;
				TopFlow->FrontNode->yPos = yPos;
				TopFlow->NumExpansions++;
			}
		}
	}

	if(OnGrid(xPos, RightY))
	{
		Grid[xPos][RightY] = TopFlow->ColorCode;
		TopFlow->BackNode->xPos = xPos;
		TopFlow->BackNode->yPos = RightY;
		TopFlow->NumExpansions++;
	}
	else
	{
		if(xPos < GridMid)
		{
			if(OnGrid(UpX, yPos))
			{
				Grid[UpX][yPos] = TopFlow->ColorCode;
				TopFlow->BackNode->xPos = UpX;
				TopFlow->BackNode->yPos = yPos;
				TopFlow->NumExpansions++;
			}
		}
		else
		{
			if(OnGrid(DownX, yPos))
			{
				Grid[DownX][yPos] = TopFlow->ColorCode;
				TopFlow->BackNode->xPos = UpX;
				TopFlow->BackNode->yPos = yPos;
				TopFlow->NumExpansions++;
			}
		}
	}
}

void Puzzle::VerticalExpansion(void)
{
	int xPos = TopFlow->Vertex->xPos;
	int yPos = TopFlow->Vertex->yPos;
	int LeftY = yPos - 1;
	int RightY = yPos + 1;
	int UpX = xPos - 1;
	int DownX = xPos + 1;

	if(OnGrid(UpX, yPos))
	{
		Grid[UpX][yPos] = TopFlow->ColorCode;
		TopFlow->FrontNode->xPos = UpX;
		TopFlow->FrontNode->yPos = yPos;
		TopFlow->NumExpansions++;
	}
	else
	{
		if(xPos > GridMid)
		{
			if(OnGrid(xPos, LeftY))
			{
				Grid[xPos][LeftY] = TopFlow->ColorCode;
				TopFlow->FrontNode->xPos = xPos;
				TopFlow->FrontNode->yPos = LeftY;
				TopFlow->NumExpansions++;
			}
		}
		else
		{
			if(OnGrid(xPos, RightY))
			{
				Grid[xPos][RightY] = TopFlow->ColorCode;
				TopFlow->FrontNode->xPos = xPos;
				TopFlow->FrontNode->yPos = RightY;
				TopFlow->NumExpansions++;
			}
		}
	}

	if(OnGrid(DownX, yPos))
	{
		Grid[DownX][yPos] = TopFlow->ColorCode;
		TopFlow->BackNode->xPos = DownX;
		TopFlow->BackNode->yPos = yPos;
		TopFlow->NumExpansions++;
	}
	else
	{
		if(xPos > GridMid)
		{
			if(OnGrid(xPos, LeftY))
			{
				Grid[xPos][LeftY] = TopFlow->ColorCode;
				TopFlow->BackNode->xPos = xPos;
				TopFlow->BackNode->yPos = LeftY;
				TopFlow->NumExpansions++;
			}
		}
		else
		{
			if(OnGrid(xPos, RightY))
			{
				Grid[xPos][RightY] = TopFlow->ColorCode;
				TopFlow->BackNode->xPos = xPos;
				TopFlow->BackNode->yPos = RightY;
				TopFlow->NumExpansions++;
			}
		}
	}
}

bool Puzzle::OnGrid(int x, int y)
{
//Function to test if a given (x,y) coordinate is located off of the grid

	if(x > Size - 1 || x < 0 || y > Size - 1 || y < 0)
		return false;

	if(Grid[x][y] != 0)
	{
		if(Grid[x][y] != 99)
		{
			return false;
		}
	}

	return true;
}

bool Puzzle::IsPossible(int x, int y)
{
//Function to test if a given (x,y) coordinate is located off of the grid

	if(x > Size - 1 || x < 0 || y > Size - 1 || y < 0)
		return false;
	return true;
}

void Puzzle::FindEmpties(void)
{
	int NumOfEmpties = 0;
	static int PreviousNum = 0;
	EmptyList = NULL;
	for(int i = 0; i < Size; i++)
	{
		for(int j = 0; j < Size; j++)
		{
			if(Grid[i][j] == 0||Grid[i][j] == 99)
			{
				NumOfEmpties++;
			}
		}
	}
	if(NumOfEmpties == 0)
	{
		PuzzleComplete = true;
		FinalCheck();
		if(PuzzleComplete == true)
		{
			Draw();
		}
	}
	else
	{
		if(NumOfEmpties == PreviousNum)
		{
			return;
		}
		PreviousNum = NumOfEmpties;
		FillEmpties();
	}
}

void Puzzle::FillEmpties(void)
{
	FlowList *NewList = new FlowList;
	NewList = NULL;

	while(TopFlow != NULL)
	{
		int xFront = TopFlow->FrontNode->xPos;
		int yFront = TopFlow->FrontNode->yPos;
		int xBack = TopFlow->BackNode->xPos;
		int yBack = TopFlow->BackNode->yPos;
		bool CheckTheBack = true;

		for(int i = 0; i < PossibleDirections; i++)
		{
			int xAdjacent = xFront + DirectionsX[i];
			int yAdjacent = yFront + DirectionsY[i];

			if(OnGrid(xAdjacent, yAdjacent))
			{
				if((Grid[xAdjacent][yAdjacent] == 0 
					|| Grid[xAdjacent][yAdjacent] == 99)
					&& HowManyNeighbors(TopFlow->ColorCode, xAdjacent, yAdjacent) == 1
					&& TopFlow->NumExpansions <= Size + 1)
				{
					Grid[xAdjacent][yAdjacent] = TopFlow->ColorCode;
					TopFlow->FrontNode->xPos = xAdjacent;
					TopFlow->FrontNode->yPos = yAdjacent;
					TopFlow->NumExpansions++;
					CheckTheBack = false;
					break;
				}
			}
		}

		if(CheckTheBack == true)
		{
			for(int i = 0; i < PossibleDirections; i++)
			{
				int xAdjacent = xBack + DirectionsX[i];
				int yAdjacent = yBack + DirectionsY[i];

				if(OnGrid(xAdjacent, yAdjacent))
				{
					if((Grid[xAdjacent][yAdjacent] == 0 
						|| Grid[xAdjacent][yAdjacent] == 99)
						&& HowManyNeighbors(TopFlow->ColorCode, xAdjacent, yAdjacent) == 1
						&& TopFlow->NumExpansions <= Size + 1)
					{
						Grid[xAdjacent][yAdjacent] = TopFlow->ColorCode;
						TopFlow->BackNode->xPos = xAdjacent;
						TopFlow->BackNode->yPos = yAdjacent;
						TopFlow->NumExpansions++;
						break;
					}
				}
			}
			FlowList *ThisFlow = new FlowList(*TopFlow);
			ThisFlow->next = NewList;
			NewList = ThisFlow;
			TopFlow = TopFlow->next;
		}
	}
	TopFlow = NewList;
	FindEmpties();
}

int Puzzle::HowManyNeighbors(int which_color, int which_x, int which_y)
{
	int ThisColor = which_color;
	int xPos = which_x;
	int yPos = which_y;
	int NumNeighbors = 0;

	for(int z = 0; z < PossibleDirections; z++)
	{
		int xAdjacent = xPos + DirectionsX[z];
		int yAdjacent = yPos + DirectionsY[z];
		if(IsPossible(xAdjacent, yAdjacent))
		{
			if(Grid[xAdjacent][yAdjacent] == ThisColor)
				NumNeighbors++;
		}
	}

	return NumNeighbors;
}

void Puzzle::Draw()
{
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
	int i = 0;
	int Color;
	cout << char(218);
	while(i < Size)
	{
		cout << char(196);
		i++;
	}
	cout << char(191) << endl;
	i = 0;
	while(i < Size)
	{
		cout << char(179);
		for(int c = 0; c < Size; c++)
		{
			if(Grid[i][c] == 0 || Grid[i][c] == 99)
				cout << char(176);
			else
			{
				Color = Grid[i][c];
				SetConsoleTextAttribute(screen, Color);
				cout << char(254);
				SetConsoleTextAttribute(screen, 7);
			}
		}
		cout << char(179);
		cout << endl;
		i++;
	}
	i = 0;
	cout << char(192);
	while(i < Size)
	{
		cout << char(196);
		i++;
	}
	cout << char(217) << endl;
}

void Puzzle::FinalCheck(void)
{
	while(TopFlow != NULL)
	{
		if(TopFlow->NumExpansions == 0)
		{
			PuzzleComplete = false;
			return;
		}
		TopFlow = TopFlow->next;
	}

	int NumNeighbors = 0;

	for(int x = 0; x < Size; x++)
	{
		for(int y = 0; y < Size; y++)
		{
			int xPos = x;
			int yPos = y;
			for(int z = 0; z < PossibleDirections; z++)
			{
				int xAdj = xPos + DirectionsX[z];
				int yAdj = yPos + DirectionsY[z];
				if(IsPossible(xAdj, yAdj))
				{
					if(Grid[xAdj][yAdj] == Grid[xPos][yPos])
					{
						NumNeighbors++;
					}
				}
			}
			if(NumNeighbors > 2)
			{
				PuzzleComplete = false;
				return;
			}
			NumNeighbors = 0;
		}
	}
}

Puzzle::~Puzzle(void)
{
}
