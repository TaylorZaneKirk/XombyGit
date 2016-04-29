#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <queue>
#include "Flow.h"

using namespace std;

int const Directions = 4;
int DirX[Directions] = {1, 0, -1, 0};
int DirY[Directions] = {0, 1, 0, -1};
queue<Node> PathTaken;
queue<char> SolvedColors;





//Begin Flow Class//
Flow::Flow(void)
{
}


void Flow::Form(int Size)
{
	
	int Count = 0;
	Dimension = new double (sqrt(double(Size)));

	if((*Dimension * *Dimension) != Size)
	{
		cout << "Error: Invalid puzzle dimensions." << endl;
		system("pause > 0");
		exit(0);
	}
	Contents = new char [int(*Dimension)];
	FlowPuzzle = new char *[int (*Dimension)];
	ClosedSquares = new int *[int (*Dimension)];
	OpenSquares = new int *[int (*Dimension)];
	GravityMap = new int *[int (*Dimension)];
	CurrentPath = new int *[int (*Dimension)];
	ClosedNodes = new int *[int (*Dimension)];
	OpenNodes = new int *[int (*Dimension)];
	for(Count = 0; Count < *Dimension; Count++)
	{
		FlowPuzzle[Count] = new char [int(*Dimension)];
		ClosedSquares[Count] = new int [int(*Dimension)];
		OpenSquares[Count] = new int [int(*Dimension)];
		GravityMap[Count] = new int [int(*Dimension)];
		CurrentPath[Count] = new int [int (*Dimension)];
		ClosedNodes[Count] = new int [int (*Dimension)];
		OpenNodes[Count] = new int [int (*Dimension)];
	}

}

void Flow::Load(int Count, char &SquareType)
{
	int ContentTotal;
	int NumberOfColors = 0;
	Contents[Count] = SquareType;

	if(Count == ((*Dimension * *Dimension)-1))
	{
		ContentTotal = Count;
		Count = 0;
	
		while(Count < (*Dimension * *Dimension))
		{
			for(int i = 0; i < *Dimension; i++)
			{
				for(int j = 0; j < *Dimension; j++)
				{
					FlowPuzzle[i][j] = Contents[Count++];
					ClosedSquares[i][j] = 0;
					OpenSquares[i][j] = 0;
					CurrentPath[i][j] = 0;
					GravityMap[i][j] = 1;
					ClosedNodes[i][j] = 0;
					OpenNodes[i][j] = 0;
				}
			}
		}

		for(int x = 0; x < int(*Dimension); x++)
		{
			for(int y = 0; y < int(*Dimension); y++)
			{
			
				if(FlowPuzzle[x][y] != 'x')
				{
					ClosedSquares[x][y] = 1;
					ApplyGravity(x, y);
				}
			}
		}

		DisplayPuzzle();
		Count = 0;

		while(Count < ContentTotal)
		{
			if(Contents[Count] != 'x')
			{
				NumberOfColors++;
			}
			Count++;
		}
		NumberOfColors = NumberOfColors / 2;
		ColorsSolved = new char [NumberOfColors];
		for(int i = 0; i < NumberOfColors; i++)
		{
			ColorsSolved[i] = 'z';
		}
		SolvePuzzle(NumberOfColors);
	}
}

void Flow::DisplayPuzzle(void)
{
	for(int i = 0; i < *Dimension; i++)
	{
		for(int j = 0; j < *Dimension; j++)
		{
			cout << setw(3) << FlowPuzzle[i][j];
		}
		cout << endl;
	}
}

char Flow::SelectColor(int NumberOfColors)
{
	int Count = 0;
	char SelectedColor;
	char CurrSquare;

	for(int i = 0; i < (*Dimension * *Dimension); i++)
	{
		CurrSquare = Contents[i];
		if(CurrSquare != 'x')
		{
			SelectedColor = CurrSquare;
			for(int j = 0; j < NumberOfColors; j++)
			{
				if(ColorsSolved[j] == SelectedColor)
				{
					break;
				}
				else
				{
					return(SelectedColor);
				}
			}
		}
	}
	return('F');
}

void Flow::SolvePuzzle(int NumberOfColors)
{
	
	bool StartFound = false;
	bool EndFound = false;
	int xStart, yStart;
	int xEnd, yEnd;
	static int Count = 0;

	char ColorToSolve = SelectColor(NumberOfColors);
	if(ColorToSolve != 'F')
	{
		for(int x = 0; x < *Dimension; x++)
		{
			for(int y = 0; y < *Dimension; y++)
			{
				if(FlowPuzzle[x][y] == ColorToSolve)
				{
					if(StartFound == false)
					{
						xStart = x;
						yStart = y;
						StartFound = true;
					}
					else if(EndFound == false)
					{
						xEnd = x;
						yEnd = y;
						ClosedSquares[xEnd][yEnd] = 0;
						EndFound = true;
					}
				}
			}
		}
		ColorPos = new Node(xStart, yStart, 0, 0);
		ColorEnd = new Node(xEnd, yEnd, 0, 0);
		PathTaken.push(*ColorPos);
		cout << "Color Selected: " << ColorToSolve << endl;
		cout << "(x,y) of " << ColorToSolve << ": (" << xStart << "," << yStart << ")" << endl;
		cout << "Goal of " << ColorToSolve << ": (" << xEnd << "," << yEnd << ")" << endl;
		bool Found = GeneratePath(ColorToSolve);
		if(Found)
		{
			cout << "Path Found!" << endl;
			ColorsSolved[Count] = ColorToSolve;
			Count++;
			PathTaken.pop();
			SolvePuzzle(NumberOfColors);	
		}
		else
		{
			cout << "Error on Color: " << ColorToSolve << endl;
			system("pause");
		}
		delete ColorPos;
		delete ColorEnd;
	}
}

bool Flow::GeneratePath(char ColorToSolve)
{
	int x, y, xEnd, yEnd;
	int xTemp, yTemp;
	int Step, Cost, NewCost, ThisX, ThisY, Distance;
	char AddStep;
	Node* ThisSquare;
	int OldCost;
	

	cout << "Attempting to find path..." << endl;
	queue<Node> CurrentPath;
	queue<Node> PossibleMoves;
	CurrentPath = PathTaken;
	
	x = PathTaken.front().GetMapX();
	y = PathTaken.front().GetMapY();
	xEnd = ColorEnd->GetMapX();
	yEnd = ColorEnd->GetMapY();


	while(!(x == xEnd && y == yEnd))
	{
		Node* NewSquare;
		x = CurrentPath.back().GetMapX();
		y = CurrentPath.back().GetMapY();
		
		if(!(x == xEnd && y == yEnd))
		{
			
				for(int i = 0; i < Directions; i++)
				{
			
					ThisSquare = new Node(CurrentPath.back().GetMapX(), CurrentPath.back().GetMapY(),
					CurrentPath.back().GetDistance(), CurrentPath.back().GetPathCost());
					xTemp = ThisSquare->GetMapX();
					yTemp = ThisSquare->GetMapY();

					Cost = ThisSquare->GetPathCost();
					Distance = ThisSquare->GetDistance();
				
					ThisX = xTemp + DirX[i];
					ThisY = yTemp + DirY[i];
					cout << ThisX << "," << ThisY << endl; 
				
					if(!(ThisX < 0 || ThisX > (int(*Dimension)) - 1
						|| ThisY < 0 || ThisY > (int(*Dimension)) - 1
						|| ClosedSquares[ThisX][ThisY] == 1))
					{
						NewCost = Cost + GravityMap[ThisX][ThisY];
						
						NewSquare = new Node(ThisX, ThisY, Distance, NewCost);
						PossibleMoves.push(*NewSquare);
			
						delete NewSquare;
					}
					
					if(PossibleMoves.size() > 2)
					{
						PossibleMoves.pop();
						int OldCost = PossibleMoves.front().GetPathCost();
						int NewCost = PossibleMoves.back().GetPathCost();
						int FirstDistance = PossibleMoves.front().GetDistance();
						int SecondDistance = PossibleMoves.back().GetDistance();
							
							
						int OldV = OldCost * FirstDistance;
						int NewV = NewCost * SecondDistance;
						if(NewV > OldV)
						{
							cout << "Whee" << endl;
							PossibleMoves.pop();
						}
							
						/*else
						{
							if(NewCost < OldCost)
							{
								cout << "Snaw" << endl;
								PossibleMoves.pop();
							}
						}*/

					}

					delete ThisSquare;
				}
				if(!(PossibleMoves.front().GetMapX() == x && PossibleMoves.back().GetMapY() == y))
				{
					PossibleMoves.front().UpdateDistance();
				}
				ClosedSquares[PossibleMoves.front().GetMapX()][PossibleMoves.front().GetMapY()] = 1;
		
				CurrentPath.push(PossibleMoves.front());
				
			
		
			
			//delete ThisSquare;
		}
		
	}
	
	while(!(CurrentPath.empty()))
		{
			x = CurrentPath.front().GetMapX();
			y = CurrentPath.front().GetMapY();
			FlowPuzzle[x][y] = ColorToSolve;
			CurrentPath.pop();
		}
	
	DisplayPuzzle();
	return (1);	
}

/*string Flow::GeneratePath(void)
{
	int x, y, xEnd, yEnd;
	int xTemp, yTemp;
	int Step, Cost, OldCost, NewCost, ThisX, ThisY;
	char AddStep;
	Node* ThisSquare;
	
	queue<Node> CurrentPath;

	CurrentPath = PathTaken;
	
	x = ColorPos->GetMapX();
	y = ColorPos->GetMapY();
	xEnd = ColorEnd->GetMapX();
	yEnd = ColorEnd->GetMapY();
	
	while(!(x == xEnd && y == yEnd))
	{
		Node *NewSquare;
		ThisSquare = new Node(PathTaken.front().GetMapX(), PathTaken.front().GetMapY(),
			PathTaken.front().GetDistance(), PathTaken.front().GetPathCost());
		xTemp = ThisSquare->GetMapX();
		yTemp = ThisSquare->GetMapY();

		while(!(xTemp == xEnd && yTemp == yEnd))
		{
			
		
			NewSquare = new Node(CurrentPath.front().GetMapX(), CurrentPath.front().GetMapY(),
			CurrentPath.front().GetDistance(), CurrentPath.front().GetPathCost());
			xTemp = NewSquare->GetMapX();
			yTemp = NewSquare->GetMapY();
			

			for(int i = 0; i < Directions; i++)
			{
				Node* NextSquare;
				ThisX = xTemp + DirX[i];
				ThisY = yTemp + DirY[i];

				if(!(ThisX < 0 || ThisX > (int(*Dimension)) - 1
					|| ThisY < 0 || ThisY > (int(*Dimension)) - 1
					|| ClosedSquares[ThisX][ThisY] == 1))
				{
					NextSquare = new Node(ThisX, ThisY, NewSquare->GetDistance(),
						NewSquare->GetPathCost());
					NextSquare->UpdateDistance();
					Cost = GravityMap[ThisX][ThisY];
					NextSquare->UpdateCost(Cost);
					CurrentPath.push(*NextSquare);
					cout << ThisX << "," << ThisY << endl;
					system("pause");
					delete NextSquare;
					
				}
				
				
			}
			
			
			
			
		}
		
		OldCost = PathTaken.front().AverageCost();
		NewCost = CurrentPath.front().AverageCost();
		if(OldCost > NewCost || OldCost == 0)
		{
			while(!(CurrentPath.empty()))
			{
				PathTaken.push(CurrentPath.front());
				CurrentPath.pop();
			}
		}
		delete NewSquare;

	}
	return "Nlaaah";
}*/

void Flow::ApplyGravity(int y, int x)
{
	//cout << x << "," << y << endl;
	
	if((y - 1) < 0 && (x - 1) < 0)
	{
		GravityMap[y+1][x] = ((GravityMap[y+1][x])+5);
		GravityMap[y][x+1] = ((GravityMap[y][x+1])+5);
		GravityMap[y+1][x+1] = ((GravityMap[y+1][x+1])+5);
	}
	else if((y - 1) < 0 && (x + 1) == int(*Dimension))
	{
		GravityMap[y][x-1] = ((GravityMap[y][x-1])+5);
		GravityMap[y+1][x] = ((GravityMap[y+1][x])+5);
		GravityMap[y+1][x-1] = ((GravityMap[y+1][x-1])+5);
	}
	else if(((x - 1) < 0) && ((y + 1) == int(*Dimension)))
	{
	
		GravityMap[y-1][x] = ((GravityMap[y-1][x])+5);
		GravityMap[y][x+1] = ((GravityMap[y][x+1])+5);
		GravityMap[y-1][x+1] = ((GravityMap[y-1][x+1])+5);
	}
	else if((x + 1) == int(*Dimension) && (y + 1) == int(*Dimension))
	{
		GravityMap[y-1][x] = ((GravityMap[y-1][x])+5);
		GravityMap[y][x-1] = ((GravityMap[y][x-1])+5);
		GravityMap[y+1][x-1] = ((GravityMap[y+1][x-1])+5);
	}
	else if((y - 1) < 0)
	{
		GravityMap[y][x-1] = ((GravityMap[y][x-1])+5);
		GravityMap[y+1][x-1] = ((GravityMap[y+1][x-1])+5);
		GravityMap[y+1][x] = ((GravityMap[y+1][x])+5);
		GravityMap[y+1][x+1] = ((GravityMap[y+1][x+1])+5);
		GravityMap[y][x+1] = ((GravityMap[y][x+1])+5);
	}
	else if((x - 1) < 0)
	{
		GravityMap[y-1][x] = ((GravityMap[y-1][x])+5);
		GravityMap[y-1][x+1] = ((GravityMap[y-1][x+1])+5);
		GravityMap[y][x+1] = ((GravityMap[y][x+1])+5);
		GravityMap[y+1][x+1] = ((GravityMap[y+1][x+1])+5);
		GravityMap[y+1][x] = ((GravityMap[y+1][x])+5);
	}
	else if((x + 1) == int(*Dimension))
	{
		GravityMap[y-1][x] = ((GravityMap[y-1][x])+5);
		GravityMap[y-1][x-1] = ((GravityMap[y-1][x-1])+5);
		GravityMap[y][x-1] = ((GravityMap[y][x-1])+5);
		GravityMap[y+1][x-1] = ((GravityMap[y+1][x-1])+5);
		GravityMap[y+1][x] = ((GravityMap[y+1][x])+5);
	}
	else if((y + 1) == int(*Dimension))
	{
		GravityMap[y][x-1] = ((GravityMap[y][x-1])+5);
		GravityMap[y-1][x-1] = ((GravityMap[y-1][x-1])+5);
		GravityMap[y-1][x] = ((GravityMap[y-1][x])+5);
		GravityMap[y-1][x+1] = ((GravityMap[y-1][x+1])+5);
		GravityMap[y][x+1] = ((GravityMap[y][x+1])+5);
	}
	else
	{
		GravityMap[y+1][x] = ((GravityMap[y+1][x])+5);
		GravityMap[y-1][x] = ((GravityMap[y-1][x])+5);
		GravityMap[y][x-1] = ((GravityMap[y][x-1])+5);
		GravityMap[y][x+1] = ((GravityMap[y][x+1])+5);
		GravityMap[y+1][x+1] = ((GravityMap[y+1][x+1])+5);
		GravityMap[y-1][x+1] = ((GravityMap[y-1][x+1])+5);
		GravityMap[y-1][x-1] = ((GravityMap[y-1][x-1])+5);
		GravityMap[y+1][x-1] = ((GravityMap[y+1][x-1])+5);
	}

}

Flow::~Flow(void)
{
}
//End Flow Class

//Begin Node Class
Node::Node(int xPos, int yPos, int CurrDistance, int CurrCost)
{
	MapX = xPos;
	MapY = yPos;
	Distance = CurrDistance;
	PathCost = CurrCost;
}

int Node::GetMapX(void)
{
	return(MapX);
}

int Node::GetMapY(void)
{
	return(MapY);
}

int Node::GetDistance(void)
{
	return(Distance);
}

int Node::GetPathCost(void)
{
	return(PathCost);
}

void Node::UpdateDistance(void)
{
	Distance++;
}

void Node::UpdateCost(int SquareCost)
{
	PathCost = (PathCost + (double)SquareCost);
}

double Node::AverageCost(void)
{
	double Average;
	if(Distance == 0 || PathCost == 0)
	{
		return(0);
	}
	else
	{
		Average = (PathCost / Distance);
		return(Average);
	}
}

Node::~Node(void)
{
}

