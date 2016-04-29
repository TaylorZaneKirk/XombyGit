//This class represents the puzzle array and handles the puzzle's
//	definition, creation, and display.

#pragma once
#include <Windows.h>

struct CoordList
{
	int NeighborX;
	int NeighborY;
	CoordList *next;
};

struct ColorPoint : private CoordList
{
	int ColorCode;
	int xPos;
	int yPos;
	int GoalX;
	int GoalY;
	
	
	CoordList *Neighbors;
	CoordList *Path;
	ColorPoint *next;
};

class Puzzle
{
private:
	ColorPoint *head;
	int Size;
	int NumColors;
	int **Flow;	//initializes a dynamic 2D array to be filled with
				//	either 0's or a number code in each cell.
	int **ClosedSpaces;

	bool IsPossible(int, int);
	CoordList* MovingIn(int, int);
	CoordList* GeneratePath(CoordList*, int, int);
	void SetGoal(ColorPoint*);
	void FindSpot(void);
	void DisplayNumGrid(void);
	void Draw(void);
	void FillCells(void);
	void LoadColors(void);
	void FillPath(ColorPoint*&);
	void Clear99s(void);
	void CheckEmpty(void);
	double DetermineDistance(int, int, int, int);
		
public:
	Puzzle(void);
	void Form(int, int);
	~Puzzle(void);
};

