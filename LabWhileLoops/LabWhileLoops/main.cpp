/*Taylor Kirk
Dr. Halverson
October 28, 2012
Description: Demonstrate use of While Loops*/

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main ()
{
	int Count = 1;
	double CurrentSalary = 20000.00;
	cout << fixed << setprecision(2);
	
	ofstream outfile;
	outfile.open("output.txt");

	outfile << "  Year     Salary" << endl;
	outfile << "----------------------" << endl;
	while(CurrentSalary <= 50000.00)
	{
		CurrentSalary = CurrentSalary + (CurrentSalary * .1);
		outfile << setw(3) << Count << "    " << "$  " << CurrentSalary << endl;
		Count++;
	}

	system("pause");
	return 0;
}
