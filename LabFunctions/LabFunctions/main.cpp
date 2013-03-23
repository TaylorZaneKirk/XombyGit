/*Taylor Kirk
Dr. Halverson
October 28, 2012
Description: Working with Functions*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

// Function Prototype; Function name is FindMax;
// Function type is int; Function parameters are 3 integers
int FindMax (int, int, int);

//Function Prototype; Function name is PrintVal;
//Function type is void; Function parameter is 1 integer
void PrintVal (int);

int main ()
{
	int Biggest, N1, N2, N3, X;

	//Requests that the user input a series of three numbers
	//in order to determine which of the three is the biggest
	//and to print that value to the screen

	cout << "Please input 3 different integers" << endl;
	cin >> N1 >> N2 >> N3;
	//Calls for the FindMax Function
	FindMax(N1, N2, N3);

	
	system("pause");
	return 0;
}

//Function: FindMax
//Input: Accepts three integers parameters
//Process: Compare Three numbers to determine
//			largest number and to call for
//			PrintVal function
//Output: One integer
int FindMax (int N1, int N2, int N3)
{
	int Big;
	if (N1 >= N2 && N2 >= N3)
	{
		Big = N1;
	}
	else if (N2 >= N1 && N2 >= N3)
	{
		Big = N2;
	}
	else 
	{
		Big = N3;
	}
	PrintVal(Big);
	return 0;
}

//Function: PrintVal
//Input: Accepts one integer parameter
//Process: Print input parameter to the screen
//Output: none
void PrintVal (int X)
{
	ofstream outfile;
	outfile.open("output.txt");
	outfile << "The answer is: " << X << endl;
	outfile.close();
}
