/*Taylor Kirk
Dr. Halverson
Computer Science
09/22/12

Description: Program will calculate the total price for a repair bill from user inputted values*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main()
{ 
	ofstream outfile;

	//Variable Declarations
	int count;
	double PartsCost;
	double LaborCost;
	double SalesTax;
	double TotalCost;
	double PartsAndLabor;

	//Preparing the output file
	outfile.open("output.txt");
	outfile << "Taylor Kirk \n";
	outfile << endl;

	//Setting decimal place to 2 positions
	cout << fixed << setprecision(2);
	outfile << fixed << setprecision(2);

	//Preparing the Loop
	count = 1;

	//Start Loop
	while (count <= 10)
	{
		//User-stated inputs
		cout << "Please enter cost of parts... ";
		cin >> PartsCost;

		cout << "Please enter cost of labor... ";
		cin >> LaborCost;

		//Calculations and formulas
		PartsAndLabor = PartsCost + LaborCost;
		SalesTax = PartsAndLabor * .0825;
		TotalCost = PartsAndLabor + SalesTax;

		//Printing output to the file
		outfile << "Computer Geeks Auto Repair Shop \n";
		outfile << "4008 On The Highway \n";
		outfile << "Wichita Falls, Texas \n";
		outfile << "Service Invoice \n";
		outfile << endl;
		outfile << "Parts:          $" << PartsCost << endl;
		outfile << "Labor:          $" << LaborCost << endl;
		outfile << "Sales Tax:      $" << SalesTax << endl;
		outfile << "----------------------- \n";
		outfile << "TOTAL:          $" << TotalCost << endl;
		outfile << endl;

		count = count + 1;
	}

	outfile.close();

	return 0;
}
