//Written by: Taylor Kirk
//February 2, 2016
//This program will attempt to solve a Maze

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

const int SIZE = 39;	//Expected length/width of the maze
const int START_X = 1;	//Starting location
const int START_Y = 1;
const int EXIT_X = SIZE - 2; //Exit location(37)
const int EXIT_Y = SIZE - 2;

const char EXIT = 'E';
const char START = 'S';
const char WALL = '%';
const char FREE = '.';


//The class 'LocNode' stores coordinates
//	to be used on the maze
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

//The class 'MazeObj' contains the 2D array which
//	represents the maze, as well as methods for
//	operating upon the maze
class MazeObj
{
	char Maze[SIZE][SIZE];
	LocNode StartPos;
	LocNode EndPos;

	//requires: MazeObj object has been initialized
	//ensures: Will output the contents of the maze array
	//	to the screen for the user to see. If any character
	//	that is represented by FREE is encountered, output
	//	a blank space instead.
	//chekcs: None
	void PrintMaze()
	{
		for (int row = 0; row < SIZE; row++)
		{
			for (int col = 0; col < SIZE; col++)
			{
				if (Maze[row][col] == FREE)	//Print spaces instead of characters
											//	for FREE spaces
					cout << " ";
				else
					cout << Maze[row][col];
			}

			cout << endl;
		}
	}

	//requires: MazeObj has been initialized, and
	//	that integers X and Y
	//ensures: That the values of X and Y are stored
	//	as coordinates in LocNode SetStartNode as (x = X, y = Y)
	//checks: None
	void SetStartNode(int X, int Y)
	{ StartPos.X = X; StartPos.Y = Y; }

	//requires: MazeObj has been initialized, and
	//	that integers X and Y
	//ensures: That the values of X and Y are stored
	//	as coordinates in LocNode SetEndNode as (x = X, y = Y)
	//checks: None
	void SetEndNode(int X, int Y)
	{ EndPos.X = X; EndPos.Y = Y; }

public:

	int GetStartX(){ return StartPos.X; }	//returns x-coordinate of Start Location
	int GetStartY(){ return StartPos.Y; }	//returns y-coordinate of Start Location
	int GetEndX(){ return EndPos.X; }	//returns x-coordinate of Exit Location
	int GetEndY(){ return EndPos.Y; }	//returns y-coordinate of Exit Location

	//requires: MazeObj has been initialize, Integers X & Y,
	//	a Character C.
	//ensures: Use recursion to attempt to solve 2D array representing a maze.
	//	returns false if the current location is not the Exit, returns true
	//	if the Current location being evaluated is the Exit of the Maze.
	//checks: none
	bool SolveMaze(int X, int Y, char dir)
	{
		static int count = 0;
		count++;
		Maze[Y][X] = dir;	//Mark direction

		//Check if the current location is the exit
		if (X == GetEndX() && Y == GetEndY())
		{
			Maze[GetStartY()][GetStartX()] = START;
			Maze[GetEndY()][GetEndX()] = EXIT;
			PrintMaze();
			cout << count << endl;
			return true;
		}

		//Recursively checks if the locations adjacent to the
		//	current location for an free space, or the exit, 
		//	if true, set that space to the to the Character dir,
		//	and attempt to solve the Maze at that location,
		//	and return true.
		if ((Y < SIZE && Maze[Y + 1][X] == FREE || Y < SIZE && Maze[Y + 1][X] == EXIT) &&
			SolveMaze(X, Y + 1, 'v'))	//down
		{ return true; }

		if ((X < SIZE && Maze[Y][X + 1] == FREE || X < SIZE && Maze[Y][X + 1] == EXIT) &&
			SolveMaze(X + 1, Y, '>'))	//right
		{ return true; }

		if ((X > 0 && Maze[Y][X - 1] == FREE || X > 0 && Maze[Y][X - 1] == EXIT) &&
			SolveMaze(X - 1, Y, '<'))	//left
		{ return true; }

		if ((Y > 0 && Maze[Y - 1][X] == FREE || Y > 0 && Maze[Y - 1][X] == EXIT) &&
			SolveMaze(X, Y - 1, '^'))	//up
		{ return true; }

		//Couldn't find a free space, or the Exit, begin to backtrack,
		//	return false.
		Maze[Y][X] = FREE;
		return false;
	}

	//requires: A string of characters, contents
	//ensures: A 2D array representing the maze will be 
	//	constructed using each of the characters in contents
	//	in sequential order
	//chekcs: None
	void ConstructMaze(string& contents)
	{
		for (int row = 0; row < SIZE; row++)
		{
			for (int col = 0; col < SIZE; col++)
			{
				Maze[row][col] = contents.at(0);	//Set this location to the first character
													//	of String contents
				contents = contents.erase(0, 1);	//Remove first character of String contents
			}
		}

		//Set the Start and Exit locations
		Maze[GetStartY()][GetStartX()] = START;
		Maze[GetEndY()][GetEndX()] = EXIT;
	}

	//Initialize the MazeObj Maze
	MazeObj()
	{
		SetStartNode(START_X, START_Y);
		SetEndNode(EXIT_X, EXIT_Y);
	}
};

//requires: A boolean value result
//ensures: Output to the screen with different
//	depending on if the Maze was solved or not
//checks: None
void PrintResults(bool result)
{
	if (result)
		cout << "MAZE HAS BEEN SOLVED!" << endl;
	else
		cout << "NO SOLUTION FOUND." << endl;
}

//requires: no parameters
//ensures: The user will be greeted, and prompted
//	for the name of the file containing the maze.
//	That file is then read, and stores the contents
//	of input into a string called contents and
//	returns this string
//checks:If the input from the file specified contains
//	any characters other than WALL or FREE, provide
//	an error message, then terminate the program.
//	Otherwise, append the current character to
//	String contents.
//	If the length of String contents is not exactly
//	the same value as the result of SIZE^2, provide
//	an error message, and terminate program
string GreetAndGetFile()
{
	string contents = "";
	string fileName = "";
	string line;
	ifstream myFile;

	//Welcome prompt
	cout << "Thank you for using MazeSolver." << endl
		<< "Please enter the file name containing the maze you would like solved." << endl
		<< "FILE NAME: ";

	cin >> fileName;

	if (!fileName.empty())	//Check if there was input
	{
		myFile.open(fileName);

		if (myFile.is_open())	//Make sure the file exists and can be opened
		{
			while (getline(myFile, line))
			{
				for (unsigned int i = 0; i < line.size(); i++)
				{
					//Check for acceptable input
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

	//Check that maze size is compatible with program
	if (contents.size() != (SIZE*SIZE))
	{
		cout << "ENCOUNTERED AN ERROR. MAZE SHOULD BE " << SIZE
			<< " X " << SIZE << " IN SIZE." << endl
			<< "PLEASE CHECK YOUR INPUT FILE AND TRY AGAIN." << endl;
		system("PAUSE");
		exit(0);
	}

	return contents;
}

void main()
{
	string contents;
	MazeObj maze;	//Object for containing the 2D array that
					//	will represent the maze to be solved
					//	and methods to set a Start and Exit location
					//	as well as to SolveMaze and to PrintMaze

	contents = GreetAndGetFile();	//Get Maze contents
	maze.ConstructMaze(contents);	//Fill the initialized 2D array of MazeObj maze
									//	with the String contents

	//Attempt to recursively solve the maze and print the results
	PrintResults(maze.SolveMaze(maze.GetStartX(), maze.GetStartY(), FREE));
}