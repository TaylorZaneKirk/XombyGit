/*Taylor Kirk
Dr. Halverson
September 10, 2012
Description: Sales commission program that will read from a file, print the customer 
				code number, the sales amount, commission rate, discount value, the net
				amount, and the total commission.*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

int main()
{
	//Declaring Variables for Sales Commission program
	int CustomerCode;
	int Count;
	int Quantity;
	int CommissionRateDisplay;
	double SalesAmount;
	double DiscountRate;
	double NetAmount;
	double Commission;
	double PricePerItem;
	double CommissionRate;
	double Discount;

	//Preparing for Sales Commission output file, and to read from data file
	ofstream outfile;
	ifstream infile;
	outfile.open("output.txt");
	infile.open("Data.txt");
	outfile << fixed << setprecision(2);
	cout << fixed << setprecision(2);

	outfile << "Taylor Kirk" << endl << endl;

	Count = 1;
	while (Count <= 10)
	{
		//Reading Customer Code, Quantity, and Price Per Item
		infile >> CustomerCode >> Quantity >> PricePerItem;

		//Calculating Sales Amount
		SalesAmount = Quantity * PricePerItem;

		//Calculating Discount
		if(SalesAmount >= 1500)
		{
			DiscountRate = .01;
		}
		else
		{
			DiscountRate = 0;
		}

		//Calculating discount amount
		Discount = SalesAmount * DiscountRate;

		//Calculating Net Price
		if(DiscountRate = .01)
		{
			NetAmount = SalesAmount - Discount;
		}
		else
		{
			NetAmount = SalesAmount;
		}

		//Calculating Commision Rate
		if(NetAmount >= 1000)
		{
			CommissionRate = .03;
			CommissionRateDisplay = 3;
		}
		else
		{
			CommissionRate = .02;
			CommissionRateDisplay = 2;
		}

		//Calculating Commision
		Commission = SalesAmount * CommissionRate;

		outfile << "Customer: " << CustomerCode << endl;
		outfile << setw(12) << "$ " << SalesAmount << "  $ " << Discount 
			<< setw(5) << "$ " << NetAmount << endl;
		outfile << setw(18) << CommissionRateDisplay << "%" << setw(13) << "$"
			<< setw(8) << Commission << endl;

		cout << "Customer: " << CustomerCode << endl;
		cout << setw(12) << "$ " << SalesAmount << "  $ " << Discount 
			<< setw(5) << "$ " << NetAmount << endl;
		cout << setw(18) << CommissionRateDisplay << "%" << setw(13) << "$"
			<< setw(8) << Commission << endl;



		Count = Count + 1;
		system("pause");
	}

	infile.close();
	outfile.close();

	system("pause");
	return 0;
}
