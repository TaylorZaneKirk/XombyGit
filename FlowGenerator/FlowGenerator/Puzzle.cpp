#include "Puzzle.h"
#include <iomanip>
#include <iostream>
#include <Windows.h>
using namespace std;

const int NumDirections = 4;
int DirectsX[NumDirections] = {-1, 0, 0, 1};
int DirectsY[NumDirections] = {0, -1, 1, 0};


Puzzle::Puzzle(void)
{
	head = NULL;
}

void Puzzle::Form(int PuzzleSize, int PuzzleColors)
{
//Parameterized function: Defines the 2D-Array to the size
//	of user-specification, followed by filling all cells
//	within the array with blank spaces (0's) to be possibly
//	overwritten in the function "Load()", next the function
//	will display the newly loaded array in its original
//	format (integers), finally the function will call the
//	"Draw()" function to print the visual representation.
//
//@Param: int "variable representing size of the puzzle",
//			int "variable representing number of colors
//			to include within the puzzle"
//@Returns:	Void

	Size = PuzzleSize;
	NumColors = PuzzleColors;
	Flow = new int *[Size];	//Initializes the 2D Array to be
							//	used for the 0's and color codes
	ClosedSpaces = new int *[Size];

	FillCells();
	
	//Loads the colors into the array
	LoadColors();

	//Draw the visual puzzle grid
	Draw();
}

void Puzzle::FillCells(void)
{
	//For loop to place 0 within 
	//all allocated cells of the array
	for(int r = 0; r < Size; r++)
	{
		Flow[r] = new int [Size];
		ClosedSpaces[r] = new int [Size];
		for(int c = 0; c < Size; c++)
		{
			Flow[r][c] = 0;
			ClosedSpaces[r][c] = 0;
		}
	}
}

void Puzzle::LoadColors(void)
{
	//Main function of the class, loads the color list, determines their start
	//and goal points, calls the path generation function, ect...
	int ThisX;
	int ThisY;
	for(int i = 0; i < NumColors; i++)
	{
		ColorPoint* NewPoint = new ColorPoint;
		CoordList* Path = new CoordList;
		NewPoint->next = NULL;
		NewPoint->Neighbors = NULL;
		Path->next = NULL;
		if(head == NULL)
		{
			head = NewPoint;
			head->ColorCode = i + 1;
			ThisX = rand()%Size;
			ThisY = rand()%Size;
			head->xPos = ThisX;
			head->yPos = ThisY;
			Flow[ThisX][ThisY] = head->ColorCode;
			head->Neighbors = MovingIn(ThisX, ThisY);
			SetGoal(head);
			Path->NeighborX = ThisX;
			Path->NeighborY = ThisY;
			head->Path = GeneratePath(Path, head->GoalX, head->GoalY);
			//DisplayNumGrid();
			system("pause");
		}
		else
		{
			
			NewPoint->ColorCode = i + 1;
			NewPoint->next = head;
			head = NewPoint;
			FindSpot();
			ThisX = head->xPos;
			ThisY = head->yPos;
			Flow[ThisX][ThisY] = head->ColorCode;
			head->Neighbors = MovingIn(ThisX, ThisY);
			SetGoal(head);
			Path->NeighborX = ThisX;
			Path->NeighborY = ThisY;
			Path->next = NULL;
			head->Path = GeneratePath(Path, head->GoalX, head->GoalY);
			//DisplayNumGrid();

			system("pause");
		}
	}
}

void Puzzle::FindSpot(void)
{
	//Function to locate a point on the grid that is not currently being used.
	int ThisX;
	int ThisY;

	ThisX = rand()%Size;
	ThisY = rand()%Size;

	if(ClosedSpaces[ThisX][ThisY] != 0)
	{
		FindSpot();
	}
	else
	{
		head->xPos = ThisX;
		head->yPos = ThisY;
	}
}

CoordList* Puzzle::MovingIn(int ThisX, int ThisY)
{
	//Locates all spaces adjacent to the initial point, this is used to make
	//sure that a goal is not positioned directly next to its start point
	int NewX;
	int NewY;
	CoordList* PointNeighbors;
	CoordList* NewNeighbor;
	CoordList* NeighborHead;
	NeighborHead = NULL;
	for(int j = 0; j < NumDirections; j++)
	{
		NewX = ThisX + DirectsX[j];
		NewY = ThisY + DirectsY[j];
		PointNeighbors = new CoordList;		
		
		if(IsPossible(NewX, NewY))
		{
			if(NeighborHead == NULL)
			{
				PointNeighbors->NeighborX = NewX;
				PointNeighbors->NeighborY = NewY;
				PointNeighbors->next = NeighborHead;
				NeighborHead = PointNeighbors;
				
				
			}
			else
			{
				PointNeighbors->next = NeighborHead;
				PointNeighbors->NeighborX = NewX;
				PointNeighbors->NeighborY = NewY;
				NeighborHead = PointNeighbors;
				
			}
			if(Flow[NewX][NewY] == 0)
			{
				Flow[NewX][NewY] = 99;
			}
		}
	}
	DisplayNumGrid();
	return NeighborHead;
}

void Puzzle::SetGoal(ColorPoint* ThisColor)
{
	//Find a space on the grid that is not already taken
	int NeighborX;
	int NeighborY;
	bool Occupied;
	int ThisX = ThisColor->xPos;
	int ThisY = ThisColor->yPos;
	int GoalX = rand()%Size;
	int GoalY = rand()%Size;
	CoordList* temp = ThisColor->Neighbors;
	
	while(temp != NULL)
	{
		while(Flow[GoalX][GoalY] != 0)
		{
			GoalX = rand()%Size;
			GoalY = rand()%Size;
		}
		temp = temp->next;
	}
	ThisColor->GoalX = GoalX;
	ThisColor->GoalY = GoalY;
	Flow[GoalX][GoalY] = ThisColor->ColorCode;
	
}

CoordList* Puzzle::GeneratePath(CoordList* Path, int GoalX, int GoalY)
{
	//Recursive function to determine a path between two points
	int CurrX;
	int CurrY;
	double OriginalDistance;
	CurrX = Path->NeighborX;
	CurrY = Path->NeighborY;
	OriginalDistance = DetermineDistance(CurrX, CurrY, GoalX, GoalY);

	//Once a path is found, return as a list, and mark the path in the ClosedSpaces array
	if(CurrX == GoalX && CurrY == GoalY)
	{
		cout << "Path Found" << endl;

		CoordList* temppath;
		temppath = Path;
		while(temppath != NULL)
		{
			
			int someX = temppath->NeighborX;
			int someY = temppath->NeighborY;
			ClosedSpaces[someX][someY] = 1;
			temppath = temppath->next;
		}
		return(Path);
	}
	//If a path has not yet been found, determine all neighbors of the leading
	//point in the path list.
	else
	{
		int NewX;
		int NewY;
		double NewDistance;
		int OldX;
		int OldY;
		double OldDistance;
		CoordList* PointNeighbors = NULL;
		CoordList* BestChoice = NULL;

		for(int i = 0; i < NumDirections; i++)
		{
			
			CoordList* NewNeighbor = new CoordList;
			NewX = CurrX + DirectsX[i];
			NewY = CurrY + DirectsY[i];
			if(IsPossible(NewX, NewY))
			{
				NewNeighbor->NeighborX = NewX;
				NewNeighbor->NeighborY = NewY;
				
				if(PointNeighbors == NULL)
				{
					NewNeighbor->next = NULL;
					PointNeighbors = NewNeighbor;
				}
				else
				{
					NewNeighbor->next = PointNeighbors;
					PointNeighbors = NewNeighbor;
				}
			}
			//delete NewNeighbor;
		}
		
		//Test all neighbors to determine which is closest to the goal point.
		while(PointNeighbors != NULL)
		{
			NewX = PointNeighbors->NeighborX;
			NewY = PointNeighbors->NeighborY;

			while(ClosedSpaces[NewX][NewY] != 0)
			{
				PointNeighbors = PointNeighbors->next;
				NewX = PointNeighbors->NeighborX;
				NewY = PointNeighbors->NeighborY;
			}

			if(PointNeighbors == NULL)
			{
				cout << "No Path Found." << endl;
				system("pause");
			}

			if(BestChoice == NULL)
			{
				CoordList* AChoice = new CoordList;
				AChoice->next = NULL;
				AChoice->NeighborX = NewX;
				AChoice->NeighborY = NewY;
				BestChoice = AChoice;
				PointNeighbors = PointNeighbors->next;
			}
			
			if(PointNeighbors != NULL)
			{
				
				NewDistance = DetermineDistance(NewX, NewY, GoalX, GoalY);

				OldX = BestChoice->NeighborX;
				OldY = BestChoice->NeighborY;
				OldDistance = DetermineDistance(OldX, OldY, GoalX, GoalY);
				
				//If the new neighbor is closer than the old neighbor, replace it
				if(NewDistance < OldDistance && NewDistance < OriginalDistance)
				{
					
					BestChoice->NeighborX = NewX;
					BestChoice->NeighborY = NewY;
				}
				PointNeighbors = PointNeighbors->next;
			}
			
		}
		//put the neighbor closest to the goal into the path and run the function again.
		BestChoice->next = Path;
		Path = BestChoice;
		return(GeneratePath(Path, GoalX, GoalY));
	}
}

double Puzzle::DetermineDistance(int OneX, int OneY, int TwoX, int TwoY)
{
	//Function to determine the distance between two point using simple Point Distance
	//formula. (D = sqrt((x2 - x1)^2 + (y2 - y1)^2))
	int DifX;
	int DifY;
	double PointSum;

	DifX = (TwoX - OneX);
	DifY = (TwoY - OneY);
	DifX = (DifX * DifX);
	DifY = (DifY * DifY);
	PointSum = (DifX + DifY);
	return (sqrt(PointSum));
}

bool Puzzle::IsPossible(int x, int y)
{
//Function to test if a given (x,y) coordinate is located off of the grid

	if(x > Size - 1 || x < 0 
		|| y > Size - 1 || y < 0)
	{
		return false;
	}
	return true;
}

void Puzzle::DisplayNumGrid(void)
{
	//For loop to display the "loaded" array
	for(int r = 0; r < Size; r++)
	{
		for(int c = 0; c < Size; c++)
		{
			cout << setw(3) << Flow[r][c];
		}
		cout << endl;
	}
}

void Puzzle::Draw(void)
{
//Parameterized function: Constructs a visual grid using
//	ASCII characters, and by comparing each (x,y) coordinate
//	with the Puzzle Array. If the coordinate currently being
//	looked at is a 0, or a 99, a blank space is placed on the
//	grid. If the coodinate is a color code, then a solid square
//	of the color representing by the coordinate's code is placed
//	on the grid.
//
//@Param: int "variable representing size of the puzzle"
//			
//@Returns:	Void

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
			if(Flow[i][c] == 0 || Flow[i][c] == 99)
				cout << char(176);
			else
			{
				Color = Flow[i][c];
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

Puzzle::~Puzzle(void)
{
}
