#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "Puzzle.h"

using namespace std;

void main()
{
	int Size;			//integer to store puzzle size
	int NumColors;		//integer to store number of colors to use
	Puzzle Flow;		//This is the variable for the "Puzzle" to be formed

	srand(time(NULL));


	//This portion is prompting values for the previous integer
	//	variables to be passed onto the "Form()" function to create,
	//	and display the puzzle.
	cout << "Please enter size of puzzle: ";
	cin >> Size;
	cout << "Please enter number of colors to use: ";
	cin >> NumColors;
	cout << "Forming Puzzle..." << endl;
	Flow.Form(Size, NumColors);

	while(Flow.PuzzleComplete == false)
	{
		Flow.Form(Size, NumColors);
	}
	system("pause > 0");
}