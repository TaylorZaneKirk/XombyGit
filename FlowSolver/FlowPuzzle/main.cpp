#include <iostream>
#include <fstream>
#include <queue>
#include "Node.h"

using namespace std;

void main(int argc, char *argv[])
{
	queue<char> Contents; 
	ifstream InFile;
	Flow Puzzle;
	int Count = 0;
	int Size = 0;
	char Temp;

	if(argc < 2)
	{
		cout << "Error:  Invalid number of parameters.\n"
			<< "Message: 2 Parameters required.\n"
			<< "Usage: " << "[FileName.exe] [Name of file containing Flow Puzzle]" << endl;
		system("pause");
		exit(0);
		//InvalidArguements(2, "[FileName.exe] [Name of file containing Flow Puzzle]");
	}
	else
	{
		cout << "Message: Input File: " << argv[1] << endl;
		InFile.open(argv[1]);

		if(!InFile)
		{
			cout << "Error: Cannot find/open file: " << argv[1] << endl;
			system("pause");
			exit(0);
		}
		else
		{
			cout << "Message: File successfully opened..." << endl;
		}

		InFile >> Temp;
		Contents.push(Temp);
		while(!InFile.eof())
		{
			InFile >> Temp;
			Contents.push(Temp);
			Size++;
		}

		for(Count = 0; Count < Size; Count++)
		{
			Puzzle.AddContent(Contents.front());
			Contents.pop();
		}
		Puzzle.Form(Size);

		Count = 0;
		/*while(!Contents.empty())
		{
			if(Count < Size)
			{
				Puzzle.Load(Count, Contents.front());
				Contents.pop();
				Count++;
			}
			
		}*/
	}
	system("pause > 0");
}