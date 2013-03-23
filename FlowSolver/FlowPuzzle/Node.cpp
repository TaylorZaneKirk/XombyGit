#include "Node.h"
#include <math.h>
#include <iostream>
#include <iomanip>
#include <queue>

using namespace std;

const int Directions = 4;
static int DirX[Directions] = {1, 0, -1, 0};
static int DirY[Directions] = {0, 1, 0, -1};
queue<char> Contents;
queue<char> ColorList;
queue<char> temp;
queue<Node*> Nodes;


bool operator<(const Node & a, const Node & b)
{
  return a.GetPriority() > b.GetPriority();
}

Node::Node(void)
{
}

Node::Node(int x, int y, int d, int p)
{
	xPos = x;
	yPos = y;
	Distance = d;
	Priority = p;
}

void Node::UpdatePriority(const int & xGoal, const int & yGoal)
{
	Priority = Distance+Estimate(xGoal, yGoal)*10;
}

void Node::AddGravity(const int & Gravity)
{
	Distance += Gravity;
}

const int & Node::Estimate(const int & xGoal, const int & yGoal) const
{
	static int xd, yd, d;
	double root;
	xd = xGoal - xPos;
	yd = yGoal - xPos;
	root = xd*xd+yd*yd;
	d = static_cast<int>(sqrt(root));
	return d;
}

Node::~Node(void)
{
}

Flow::Flow(void)
{
}

void Flow::AddContent(char Content)
{
	Contents.push(Content);
}

void Flow::Form(int Size)
{
	char Color;
	Dimension = new double (sqrt(double(Size)));

	if((*Dimension * *Dimension) != Size)
	{
		cout << "Error: Invalid puzzle dimensions." << endl;
		system("pause > 0");
		exit(0);
	}
	
	Puzzle = new char *[int(*Dimension)];
	OpenList = new int *[int(*Dimension)];
	ClosedList = new int *[int(*Dimension)];
	DirMap = new int *[int(*Dimension)];
	GravityMap = new int *[int(*Dimension)];
	for(int c = 0; c < int(*Dimension); c++)
	{
		Puzzle[c] = new char [int(*Dimension)];
		ClosedList[c] = new int [int(*Dimension)];
		OpenList[c] = new int [int(*Dimension)];
		DirMap[c] = new int [int(*Dimension)];
		GravityMap[c] = new int [int(*Dimension)];
	}
	temp = Contents;
	while(!(Contents.empty()))
	{
		
		for(int x = 0; x < *Dimension; x++)
		{
			for(int y = 0; y < *Dimension; y++)
			{
				Puzzle[x][y] = Contents.front();
				GravityMap[x][y] = 1;
				bool Found = FindDupes(Puzzle[x][y]);
				if(!Found)
				{
					ColorList.push(Puzzle[x][y]);
				}
				if(Contents.front() == 'x')
				{
					ClosedList[x][y] = 0;
				}
				else
				{
					ClosedList[x][y] = 1;
				}
				Contents.pop();
			}
		}
	}

	for(int i = 0; i < *Dimension; i++)
	{
		for(int j = 0; j < *Dimension; j++)
		{
			if(Puzzle[i][j] != 'x')
			{
				ApplyGravity(i, j);
			}
		}
	}

	DisplayPuzzle();
	cout << endl;

	for(int i = 0; i < *Dimension; i++)
	{
		for(int j = 0; j < *Dimension; j++)
		{
			cout << setw(3) << GravityMap[i][j];
		}
		cout << endl;
	}

	SolvePuzzle();
	
	
}

bool Flow::FindDupes(char Color)
{
	queue<char> test;
	test = ColorList;
	test.push('x');
	bool Found = false;
	while(!test.empty())
	{
		char ThisColor = test.front();
		if(ThisColor == Color)
		{
			Found = true;
			return Found;
		}
		test.pop();
	}
	return Found;
}

void Flow::ApplyGravity(int x, int y)
{
	//cout << x << "," << y << endl;
	
	if((x - 1) < 0 && (y - 1) < 0)
	{
		GravityMap[x+1][y] = ((GravityMap[x+1][y])+5);
		GravityMap[x][y+1] = ((GravityMap[x][y+1])+5);
		GravityMap[x+1][y+1] = ((GravityMap[x+1][y+1])+5);
	}
	else if((x - 1) < 0 && (y + 1) == int(*Dimension))
	{
		GravityMap[x][y-1] = ((GravityMap[x][y-1])+5);
		GravityMap[x+1][y] = ((GravityMap[x+1][y])+5);
		GravityMap[x+1][y-1] = ((GravityMap[x+1][y-1])+5);
	}
	else if(((y - 1) < 0) && ((x + 1) == int(*Dimension)))
	{
	
		GravityMap[x-1][y] = ((GravityMap[x-1][y])+5);
		GravityMap[x][y+1] = ((GravityMap[x][y+1])+5);
		GravityMap[x-1][y+1] = ((GravityMap[x-1][y+1])+5);
	}
	else if((y + 1) == int(*Dimension) && (x + 1) == int(*Dimension))
	{
		GravityMap[x-1][y] = ((GravityMap[x-1][y])+5);
		GravityMap[x][y-1] = ((GravityMap[x][y-1])+5);
		GravityMap[x+1][y-1] = ((GravityMap[x+1][y-1])+5);
	}
	else if((x - 1) < 0)
	{
		GravityMap[x][y-1] = ((GravityMap[x][y-1])+5);
		GravityMap[x+1][y-1] = ((GravityMap[x+1][y-1])+5);
		GravityMap[x+1][y] = ((GravityMap[x+1][y])+5);
		GravityMap[x+1][y+1] = ((GravityMap[x+1][y+1])+5);
		GravityMap[x][y+1] = ((GravityMap[x][y+1])+5);
	}
	else if((y - 1) < 0)
	{
		GravityMap[x-1][y] = ((GravityMap[x-1][y])+5);
		GravityMap[x-1][y+1] = ((GravityMap[x-1][y+1])+5);
		GravityMap[x][y+1] = ((GravityMap[x][y+1])+5);
		GravityMap[x+1][y+1] = ((GravityMap[x+1][y+1])+5);
		GravityMap[x+1][y] = ((GravityMap[x+1][y])+5);
	}
	else if((y + 1) == int(*Dimension))
	{
		GravityMap[x-1][y] = ((GravityMap[x-1][y])+5);
		GravityMap[x-1][y-1] = ((GravityMap[x-1][y-1])+5);
		GravityMap[x][y-1] = ((GravityMap[x][y-1])+5);
		GravityMap[x+1][y-1] = ((GravityMap[x+1][y-1])+5);
		GravityMap[x+1][y] = ((GravityMap[x+1][y])+5);
	}
	else if((x + 1) == int(*Dimension))
	{
		GravityMap[x][y-1] = ((GravityMap[x][y-1])+5);
		GravityMap[x-1][y-1] = ((GravityMap[x-1][y-1])+5);
		GravityMap[x-1][y] = ((GravityMap[x-1][y])+5);
		GravityMap[x-1][y+1] = ((GravityMap[x-1][y+1])+5);
		GravityMap[x][y+1] = ((GravityMap[x][y+1])+5);
	}
	else
	{
		GravityMap[x+1][y] = ((GravityMap[x+1][y])+5);
		GravityMap[x-1][y] = ((GravityMap[x-1][y])+5);
		GravityMap[x][y-1] = ((GravityMap[x][y-1])+5);
		GravityMap[x][y+1] = ((GravityMap[x][y+1])+5);
		GravityMap[x+1][y+1] = ((GravityMap[x+1][y+1])+5);
		GravityMap[x-1][y+1] = ((GravityMap[x-1][y+1])+5);
		GravityMap[x-1][y-1] = ((GravityMap[x-1][y-1])+5);
		GravityMap[x+1][y-1] = ((GravityMap[x+1][y-1])+5);
	}

}


void Flow::SolvePuzzle(void)
{
	char Color;
	bool StartFound = false;
	bool GoalFound = false;
	int xPos, yPos;
	Node* StartNode;
	Node* GoalNode;

	while(!ColorList.empty())
	{
		Color = ColorList.front();
		for(int y = 0; y < *Dimension; y++)
		{
			for(int x = 0; x < *Dimension; x++)
			{
				if(Puzzle[y][x] == Color)
				{
					
					if(StartFound == false)
					{
						StartNode = new Node(x, y, NULL, NULL);
						StartFound = true;
					}
					else if(GoalFound == false)
					{
						GoalNode = new Node(x, y, NULL, NULL);
						GoalFound = true;
						ClosedList[x][y] = 0;
					}
				}
			}
		}
		cout << "Color: " << Color << endl;
		cout << "Location: (" << StartNode->GetxPos() 
			<< "," << StartNode->GetyPos() << ")" << endl;
		cout << "Goal: (" << GoalNode->GetxPos()
			<< "," << GoalNode->GetyPos() << ")" << endl;
		system("pause");
		bool PathFound = PathFind(StartNode, GoalNode, Color);
		if(PathFound == true)
		{
			cout << "TRUE" << endl;
			ColorList.pop();
			StartFound = false;
			GoalFound = false;
			delete StartNode;
			delete GoalNode;
			DisplayPuzzle();
			

		}
		else
		{
			cout << "Error on color: " << Color << endl;
			DisplayPuzzle();
			system("pause");
		}
	}
	DisplayPuzzle();
}

void Flow::DisplayPuzzle(void)
{
	for(int i = 0; i < *Dimension; i++)
	{
		for(int j = 0; j < *Dimension; j++)
		{
			cout << setw(3) << Puzzle[i][j];
		}
		cout << endl;
	}
}

void Flow::UpdateClosed(void)
{
	for(int i = 0; i < *Dimension; i++)
	{
		for(int j = 0; j < *Dimension; j++)
		{
			if(Puzzle[i][j] != 'x')
			{
				ClosedList[i][j] = 1;
				
			}
			cout << setw(3) << ClosedList[i][j];
		}
		cout << endl;
	}
}

bool Flow::PathFind(Node* Start, Node* Goal, char Color)
{
	priority_queue<Node> pq[2];
	int pqi;
	int x, y, xGoal, yGoal, xNew, yNew;
	int Gravity;
	Node* ThisNode;
	Node* ThatNode;
	pqi = 0;
	for(y = 0; y < *Dimension; y++)
	{
		for(x = 0; x < *Dimension; x++)
		{
			ClosedList[x][y] = 0;
			OpenList[x][y] = 0;
			DirMap[x][y] = 0;
		}
	}
	UpdateClosed();
	Start->UpdatePriority(Goal->GetxPos(), Goal->GetyPos());
	pq[pqi].push(*Start);
	x = Start->GetxPos();
	y = Start->GetyPos();
	xGoal = Goal->GetxPos();
	yGoal = Goal->GetyPos();
	OpenList[x][y]=Start->GetPriority();
	ClosedList[xGoal][yGoal] = 0;

	while(!pq[pqi].empty())
	{
		
		ThisNode = new Node(pq[pqi].top().GetxPos(), pq[pqi].top().GetyPos(),
			pq[pqi].top().GetDistance(), pq[pqi].top().GetPriority());
		x = ThisNode->GetxPos();
		y = ThisNode->GetyPos();
		pq[pqi].pop();
		OpenList[x][y] = 0;
		ClosedList[x][y] = 1;
		cout << x << " " << y << endl;
		if(x == xGoal && y == yGoal)
		{
			
			while(!(x == Start->GetxPos() && y == Start->GetyPos()))
			{
				int Step = DirMap[x][y];
				Puzzle[y][x] = Color;
				//ClosedList[y][x] = 1;
				x += DirX[Step];
				y += DirY[Step];
			}
			delete ThisNode;
			while(!pq[pqi].empty())
				pq[pqi].pop();
			return true;
		}

		for(int i = 0; i < Directions; i++)
		{
			xNew = x + DirX[i];
			yNew = y + DirY[i];
			//out << xNew << "," << yNew << " " << ClosedList[x][y] << endl;

			if(!(xNew < 0 || xNew > *Dimension - 1|| yNew < 0 || yNew > *Dimension - 1
				|| ClosedList[xNew][yNew] == 1))
			{
				ThatNode = new Node(xNew, yNew, 
					ThisNode->GetDistance(), ThisNode->GetPriority());
				Gravity = GravityMap[xNew][yNew];
				ThatNode->AddGravity(Gravity);
				ThatNode->UpdatePriority(xGoal, yGoal);

				if(OpenList[xNew][yNew] == 0)
				{
					OpenList[xNew][yNew] = ThatNode->GetPriority();
					pq[pqi].push(*ThatNode);
					DirMap[xNew][yNew] = (i + Directions / 2)%Directions; 
				}
				else if(OpenList[xNew][yNew]>ThatNode->GetPriority())
				{
					OpenList[xNew][yNew] = ThatNode->GetPriority();
					DirMap[xNew][yNew] = (i + Directions / 2)%Directions;

					while(!(pq[pqi].top().GetxPos() == xNew &&
						pq[pqi].top().GetyPos() == yNew))
					{
						pq[1-pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pq[pqi].pop();
					if(pq[pqi].size() > pq[1-pqi].size())
						pqi = 1 - pqi;
					while(!pq[pqi].empty())
					{
						pq[1-pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push(*ThatNode);
				}

				else delete ThatNode;
				
			}
			
		}
		delete ThisNode;
	}
	return false;
}

Flow::~Flow(void)
{
}
