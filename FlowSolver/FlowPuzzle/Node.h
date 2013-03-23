#include <queue>
#pragma once



class Flow;
class Node
{
public:
	int xPos;
	int yPos;
	int Distance;
	int Priority;
	int Cost;
	char Color;
	bool Blocked;

	Node(void);
	Node(int, int, int, int);
	int GetxPos()	const {return xPos;}
	int GetyPos()	const {return yPos;}
	int GetDistance()	const {return Distance;}
	int GetPriority()	const {return Priority;}
	void AddGravity(const int &);
	void UpdatePriority(const int &, const int &);
	const int & Estimate(const int & xGoal, const int & yGoal) const;
	~Node(void);
};

class Flow
{
public:
	
	double *Dimension;
	char **Puzzle;
	int **OpenList;
	int **ClosedList;
	int **DirMap;
	int **GravityMap;

	Flow(void);
	void Form(int);
	void AddContent(char);
	bool FindDupes(char);
	void ApplyGravity(int, int);
	void UpdateClosed(void);
	void SolvePuzzle(void);
	bool PathFind(Node*, Node*, char);
	void DisplayPuzzle(void);
	~Flow(void);
};

