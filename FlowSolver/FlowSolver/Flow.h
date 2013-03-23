#include <queue>
#include <string>
using namespace std;
#pragma once





class Node;
class Flow
{
	char **FlowPuzzle;
	char *Contents;
	char *ColorsSolved;
	double *Dimension;
	int **ClosedSquares;
	int **OpenSquares;
	int **DirectionMap;
	int **GravityMap;
	int **CurrentPath;
	int **ClosedNodes;
	int **OpenNodes;
	Node* ColorPos;
	Node* ColorEnd;
	Node* Move;
	

private:
	void DisplayPuzzle(void);
	char SelectColor(int);
	void SolvePuzzle(int);
	void ApplyGravity(int, int);
	bool GeneratePath(char);
public:
	Flow(void);
	void Form(int);
	void Load(int, char&);
	~Flow(void);
};

class Node
{
	
	int MapX;
	int MapY;
	int Distance;
	double PathCost;
private:
	
public:
	
	Node(void);
	Node(int, int, int, int);
	int GetMapX(void);
	int GetMapY(void);
	int GetDistance(void);
	void UpdateDistance(void);
	int GetPathCost(void);
	void UpdateCost(int);
	double AverageCost(void);
	~Node(void);
};

