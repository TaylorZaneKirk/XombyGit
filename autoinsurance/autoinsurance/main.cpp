/*Taylor Kirk
Dr. Halverson
October 22, 2012
Descirption: Program to calculate auto insurance based on a person's age, 
number of tickets, value of the car, and if the driver's education.*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main ()
{
	//Declaring Variables to be used for Auto Insurance Program
	int DriversAge;
	int NumberOfTickets;
	int Count;
	int PremiumTF;
	char EducationYN;
	
	double ValueOfCar;
	double PremiumAmount;
	double InsuranceRate;
	double EducationDeduction;

	//Preparing for Auto Insurance output file, and to read from
	//data file
	ofstream outfile;
	ifstream infile;
	outfile.open("output.txt");
	infile.open("Data.txt");
	outfile << fixed << setprecision(2);

	outfile << "Student Name: Taylor Kirk" << endl << endl;

	Count = 1;
	while (Count <= 15)
	{
		//Reading data from the file (such as The Driver's age, 
		//Number of tickets, value of the car, and if the
		//driver is educated

		infile >> DriversAge >> NumberOfTickets
			>> ValueOfCar >> EducationYN;
		InsuranceRate = .0525;

		//Calculating Insurance percantage based on age
		if(DriversAge < 30 && DriversAge >= 21)
		{
			InsuranceRate = InsuranceRate + .1;
			PremiumAmount = ValueOfCar * InsuranceRate;
			
		}
		else if(DriversAge < 21)
		{
			InsuranceRate = InsuranceRate + .139;
			PremiumAmount = ValueOfCar * InsuranceRate;
		}
		else if(DriversAge >= 30)
		{
			PremiumAmount = ValueOfCar * InsuranceRate;
		}

		//Calculating Additional Insurance Percentage based on
		//Amount of tickets
		if(NumberOfTickets > 3)
		{
			PremiumTF = false;
		}
		else if(NumberOfTickets == 3)
		{
			PremiumTF = true;
			PremiumAmount = PremiumAmount + (PremiumAmount * .479);
		}
		else if(NumberOfTickets == 2)
		{
			PremiumTF = true;
			PremiumAmount = PremiumAmount + (PremiumAmount * .196);
		}
		else if(NumberOfTickets == 1)
		{
			PremiumTF = true;
			PremiumAmount = PremiumAmount + (PremiumAmount * .05);
		}
		else if(NumberOfTickets < 1)
		{
			PremiumTF = true;
		}
		
		//Calculating any reducations in Insurance Rate based
		//on if the driver has attended a Driver's Ed. course
		//in the past two years
		if(EducationYN == 'y')
		{
			PremiumAmount = PremiumAmount - (PremiumAmount * .05);
		}
	
		//Printing out completed Insurance Ticket
		if(PremiumTF)
		{
			outfile << "Driver #" << Count << endl;
			outfile << "Driver's age?            " 
				<< DriversAge << endl;
			outfile << "Number of tickets?        " 
				<< NumberOfTickets << endl;
			outfile << "Value of car?   $" << setw(10) 
				<< ValueOfCar << endl;
			outfile << "Premium?        $" << setw(10) 
				<< PremiumAmount << endl << endl;	
		}
		else
		{
			outfile << "Driver #" << Count << endl;
			outfile << "Driver's age?            " 
				<< DriversAge << endl;
			outfile << "Number of tickets?        " 
				<< NumberOfTickets << endl;
			outfile << "Value of car?   $"<< setw(10) 
				<< ValueOfCar << endl;
			outfile << "Premium?            Refused" 
				<< endl << endl;
		}

		Count++;
	}

	infile.close();
	outfile.close();

	system("pause");
	return 0;
}
