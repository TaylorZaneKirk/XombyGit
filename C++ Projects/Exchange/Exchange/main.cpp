/*Taylor Kirk
Dr. Halverson
9/30/2012
Exchange Program
Description: Convert currency from US dollars to six other forms of currency*/

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

//Declare Constants
const double EURO = 0.7748;
const double YUAN = 6.3059;
const double REAL = 2.0334;
const double PESO = 12.8602;
const double RUPEE = 53.3703;
const double POUND = 0.6176;

int main ()
{
	ofstream outfile;

	//Declare Variables
	int count;
	double AmountUS;
	double AmountEuro;
	double AmountYuan;
	double AmountReal;
	double AmountPeso;
	double AmountRupee;
	double AmountPound;
	char UserName[40];

	//Preparing the output file
	outfile.open("output.txt");
	outfile << "Taylor Kirk \n" << endl;

	//Setting decimal places
	cout << fixed << setprecision (4);
	outfile << fixed << setprecision (4);

	//Preparing for loop
	count = 1;

	//Looping...
	while (count <= 12)
	{
		//Inquire last name
		cout << "Please input your last name... " << endl;
		cin >> UserName;

		//Inquire Amount of US dollars
		cout << "Please state the amount of U.S. dollars to convert... " << endl;
		cin >> AmountUS;

		//Conversions
		AmountEuro = AmountUS * EURO;
		AmountYuan = AmountUS * YUAN;
		AmountReal = AmountUS * REAL;
		AmountPeso = AmountUS * PESO;
		AmountRupee = AmountUS * RUPEE;
		AmountPound = AmountUS * POUND;

		//Display output
		outfile << "Name:" << setw(7) << UserName << endl;
		outfile << "US Dollars: " << AmountUS << endl;
		outfile << "Exchanges: " << setw(8) << AmountEuro << " Euro" << endl;
		outfile << setw(19) << AmountYuan << " Chinese Yuan" << endl;
		outfile << setw(19) << AmountReal << " Brazilian Real" << endl;
		outfile << setw(19) << AmountPeso << " Mexican Peso" << endl;
		outfile << setw(19) << AmountRupee << " Indian Rupee" << endl;
		outfile << setw(19) << AmountPound << " British Pound" << endl;
		outfile << endl;

		cout << "Conversion " << count << " complete." << endl;
		//Add to the count
		count = count + 1;
		
	}
	system("pause");
	return 0;
}