#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>


using namespace std;

const int NUMROWS = 39;
const int NUMCOLS = 39;
const char EXIT = 'E';
const char START = 'S';
const char WALL = '%';
const char FREE = '.';

char Maze[NUMROWS][NUMCOLS];

class LocNode
{
public:
	int X;
	int Y;
	LocNode(int x = 1, int y = 1)
		{ X = x, Y = y; }
	LocNode(const LocNode &coord)
		{ X = coord.X; Y = coord.Y; }
};

LocNode StartPos(1, 1);
LocNode EndPos(37, 37);

void PrintMaze()
{
	for (int row = 0; row < NUMROWS; row++)
	{
		for (int col = 0; col < NUMCOLS; col++)
		{
			cout << Maze[row][col];
		}
		cout << endl;
	}
}

void PrintResults(bool result)
{
	if (result)
		cout << "MAZE HAS BEEN SOLVED!" << endl;
	else
		cout << "NO SOLUTION FOUND." << endl;
}

bool SolveMaze(int X, int Y, char dir)
{
	Maze[Y][X] = dir;
	
	if (X == EndPos.X && Y == EndPos.Y)
	{
		Maze[1][1] = START;
		Maze[37][37] = EXIT;
		PrintMaze();
		return true;
	}
		
	if ((Y < NUMROWS && Maze[Y + 1][X] == FREE || Y < NUMROWS && Maze[Y + 1][X] == EXIT) &&
		SolveMaze(X, Y + 1, 'v'))
	{
		return true;
	}
	if ((X < NUMCOLS && Maze[Y][X + 1] == FREE || X < NUMCOLS && Maze[Y][X + 1] == EXIT) &&
		SolveMaze(X + 1, Y, '>'))
	{
		return true;
	}
	if ((X > 0 && Maze[Y][X - 1] == FREE || X > 0 && Maze[Y][X - 1] == EXIT) &&
		SolveMaze(X - 1, Y, '<'))
	{
		return true;
	}
	if ((Y > 0 && Maze[Y - 1][X] == FREE || Y > 0 && Maze[Y - 1][X] == EXIT) &&
		SolveMaze(X, Y - 1, '^'))
	{
		return true;
	}
	

	Maze[Y][X] = FREE;

	PrintMaze();
	system("PAUSE");
	
	return false;
}

void ConstructMaze(string contents)
{

	for (int row = 0; row < NUMROWS; row++)
	{

		for (int col = 0; col < NUMCOLS; col++)
		{
			Maze[row][col] = contents.at(0);
			contents = contents.erase(0,1);
		}
		
	}
	Maze[StartPos.X][StartPos.Y] = START;
	Maze[EndPos.X][EndPos.Y] = EXIT;

}

string GreetAndGetFile()
{
	string contents = "";
	string fileName = "";
	string line;
	ifstream myFile;

	cout << "Thank you for using MazeSolver." << endl
		<< "Please enter the file name containing the maze you would like solved." << endl
		<< "FILE NAME: ";
	
	cin >> fileName;

	if (!fileName.empty())
	{
		myFile.open(fileName);
		if (myFile.is_open())
		{
			while (getline(myFile, line))
			{
				for (unsigned int i = 0; i < line.size(); i++)
				{
					if (!(line[i] == WALL || line[i] == FREE))
					{
						cout << "ENCOUNTERED AN ERROR. ONLY THE CHARACTERS '%' AND '.' "
							<< "ARE ACCEPTABLE IN INPUT FILE. PLEASE TRY AGAIN." << endl;
						system("PAUSE");
						exit(0);
					}
				}
				contents.append(line);
			}
		}
	}

	myFile.close();

	if (contents.size() != 1521)
	{
		cout << "ENCOUNTERED AN ERROR. MAZE SHOULD BE " << NUMROWS << " X " << NUMCOLS << " IN SIZE." << endl
			<< "PLEASE CHECK YOUR INPUT FILE AND TRY AGAIN." << endl;
		system("PAUSE");
		exit(0);
	}
	return contents;
}

void main()
{
	string contents;
	contents = GreetAndGetFile();
	ConstructMaze(contents);
	
	PrintResults(SolveMaze(StartPos.X, StartPos.Y, FREE));
	
}