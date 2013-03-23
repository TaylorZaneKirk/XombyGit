/*Taylor Kirk
Dr. Halverson
October 8, 2012
Description: work with formatting*/

#include <iomanip>
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	//Preparing out file
	ofstream outfile;
	outfile.open("output.txt");
	outfile << "Taylor Kirk \n" << endl;

	//declare Variables
	double TotalColl = 26572.89087;
	double CountyTax = 501.76;
	double TotalTax = 1504.12890;
	double Sales = 25068.7993;
	double StateTax = 1002.75212;
	int A = 5;
	int B = 15;
	int C = 25;

	//Table 1
	outfile << setw(10) << "A" << setw(10) << "B" << setw(10) << "C" << endl;
	outfile << "**********************************" << endl;
	outfile << "X1" << setw(8) << A << setw(10) << B << setw(10) << C << endl;
	outfile << "X10" << setw(7) << A * 10 << setw(10) << B * 10 << setw(10) << C * 10 << endl;
	outfile << "X100" << setw(6) << A * 100 << setw(10) << B * 100 << setw(10) << C * 100 << endl;
	outfile << endl;

	//Table 2
	outfile << fixed << setprecision(2);
	outfile << "MONTH:  March 2008" << endl;
	outfile << "--------------------------------" << endl;
	outfile << "Total Collected" << setw(6) << "$" << setw(10) << TotalColl << endl;
	outfile << "Sales" << setw(16) << "$" << setw(10) << Sales << endl;
	outfile << "County Tax" << setw(11) << "$" << setw(10) << CountyTax << endl;
	outfile << "State Tax" << setw(12) << "$" << setw(10) << StateTax << endl;
	outfile << "Total Tax" << setw(12) << "$" << setw(10) << TotalTax << endl;
	return 0;
}