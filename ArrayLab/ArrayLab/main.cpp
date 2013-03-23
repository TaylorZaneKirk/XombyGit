/*Taylor Kirk
November 19, 2012
Dr. Halverson
Lab #9
Description: To demonstrate understanding
	and use of Arrays*/

#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

const int size = 100;
int Values[size];
int Largest = 0;
int Sum = 0;
int Average = 0;
int Position = 0;

int main()
{
	//Setting the seed
	srand(5);

	//Initializing the array for random
	//numbers
	for (int i = 0; i < size; i++)
	{
		Values[i] = rand();
	}

	//Finding the largest number, finding
	//its position, and calculating
	//the sum and average of all numbers
	for (int i = 0; i < size; i++)
	{
	   cout << Values[i] << " ";
	   Sum = Sum + Values[i];
	   Average = Sum / 100;
	   if (Values[i] > Largest)
	   {
		   Largest = Values[i];
		   Position = i + 1;
	   }

	}

	//Printing all outputs
	cout << endl << "Largest number: " << Largest << endl;
	cout << "Largest Number Position: " << Position << endl;
	cout << "Average: " << Average << endl;
	cout << "\nEND OF OUTPUT" << endl;

	

	system("pause");
	return 0;
}