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

struct Color : private PositionList
{
	int ColorNum;
	int PathLength;
	PositionList *FrontNode;
	PositionList *BackNode;
	Color *next;
};

class Puzzle
{
private:
	int Size;
	int NumColors;
	int **PuzzleGrid;
	Color *ColorList;
	PositionList *EmptySpaces;

	void FillCells(void);
	void PlaceColors(void);
	void DisplayGrid(void);
	void GerminateNodes(void);
	void FindEmpties(void);
	void GrowNodes(void);
	void FixPuzzle(void);
	int FixColors(int);
	bool IsPossible(int, int);

	Color* Move(char, char, Color*&);

public:
	Puzzle(void);

	void Form(int, int);

	~Puzzle(void);
};

