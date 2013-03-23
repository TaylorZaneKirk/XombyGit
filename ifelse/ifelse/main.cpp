/* Taylor Kirk
Dr. Halverson
October 8, 2012
Description: Demonstrate if/else statements */

#include <iomanip>
#include <fstream>
#include <iostream>
using namespace std;

int main ()
{
	//Declare Variables
	double TotalPurchase;
	double Discount;
	double NewPrice;
	int count;

	//Prepare Output File
	ofstream outfile;
	outfile.open("output.txt");
	outfile << "Taylor Kirk \n";
	outfile << fixed << setprecision(2);

	//Initialize Loop
	count = 1;
	while (count <= 6)
	{
		cout << "Please enter total purchase amount" << endl;
		cin >> TotalPurchase;

		//Determine Discount
		if (TotalPurchase >= 1000)
		{
			Discount = .5;
		}
		else if (TotalPurchase >= 500)
		{
			Discount = .4;
		}
		else if (TotalPurchase >= 250)
		{
			Discount = .3;
		}
		else if (TotalPurchase >= 100)
		{
			Discount = .2;
		}
		else
		{
			Discount = .1;
		}

		//Apply Discount
			NewPrice = TotalPurchase - (TotalPurchase * Discount);

			outfile << "Total Purchase" << setw(7) << "$" << setw(8) << TotalPurchase << endl;
			outfile << "Discount" << setw(13) << "$" << setw(8) << TotalPurchase * Discount << endl;
			outfile << "-----------------------------" << endl;
			outfile << "New Price" << setw(12) << "$" << setw(8) << NewPrice << endl;
			outfile << endl;

			count +=1;
		}


	system("pause");
	return 0;
}