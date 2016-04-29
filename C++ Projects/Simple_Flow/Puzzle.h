#pragma once
#include <Windows.h>
#include <iostream>
#include <iomanip>

struct PositionList
{
	int xPos;
	int yPos;
	PositionList *next;
};

struct FlowList : private PositionList
{
	int ColorCode;
	int NumExpansions;
	int ThisExpansionMethod; //0 for horizontal, 1 for vertical
	PositionList *Vertex;
	PositionList *FrontNode;
	PositionList *BackNode;
	FlowList *next;
};

class Puzzle
{
private:
	FlowList *TopFlow;
	PositionList *EmptyList;
	int **Grid;
	int Size;
	int NumColors;
	int GridMax;
	int GridMin;
	int GridMid;
	int ExpansionMethod;
	int ColorCount;

	void FillEmpties(void);
	void FindEmpties(void);
	void FillCells(void);
	void PlaceColors(int);
	bool ExpandVertex(void);
	bool OnGrid(int, int);
	void HorizontalExpansion(void);
	void VerticalExpansion(void);
	int HowManyNeighbors(int, int, int);
	bool IsPossible(int, int);
	void Draw(void);
	void FinalCheck(void);
public:
	bool PuzzleComplete;

	Puzzle(void);
	void Form(int, int);
	~Puzzle(void);
};

