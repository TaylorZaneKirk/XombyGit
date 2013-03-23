/* Taylor Kirk
Dr. Halverson
December 06, 2012
Description: Write a program to determine
	the winner of a singing competition by
	accepting the scores of five judges,
	dropping the highest and the lowest
	scores and averaging the remainder.*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

//Function Prototype; Function name is Calculate_Score;
//Function type is Double; Function parameters are
//5 Floats
double Calculate_Score(float ScoreA, float ScoreB, 
	float ScoreC, float ScoreD, float ScoreE);

//Function Prototype; Function name is Find_Lowest;
//Function type is Double; Function parameters are
//5 Floats
double Find_Lowest(float ScoreA, float ScoreB, 
	float ScoreC, float ScoreD, float ScoreE);

//Function Prototype; Function name is Find_Highest;
//Function type is Double; Function parameters are
//5 Floats
double Find_Highest(float ScoreA, float ScoreB, 
	float ScoreC, float ScoreD, float ScoreE);

//Function Prototype; Function name is Print_Results;
//Function type is Void; Function parameters are
// 1 string, 1 double, and 5 floats.
void Print_Results(string ContestantName,
	double FinalScore, float ScoreA,
	float ScoreB, float ScoreC,
	float ScoreD, float ScoreE);

int main ()
{
	//Declaring the variables to be used in the
	//TexasIdol program
	string ContestantName;

	float ScoreA;
	float ScoreB;
	float ScoreC;
	float ScoreD;
	float ScoreE;

	double FinalScore;

	//Initializing input/output files
	ifstream infile;
	infile.open("Data.txt");
	ofstream outfile;
	outfile.open("output.txt");

	//Setting up output file header for
	//TexasIdol program; including name,
	//and a for loop in order to easily
	//populate a complete header
	outfile << "Programmer: Taylor Kirk"
		<< endl << endl;
	outfile << "  Name       Avg. Score"
		<< "                Judges' scores"
		<< "      " << endl;
	for(int i = 1; i <= 12; i++)
		outfile << "-----";
	outfile << endl;
	outfile << setw(40) << "#1   "
		<< "#2   #3   #4   #5" << endl;
	outfile.close();

	//Checking for errors in opening the
	//data file, if none, proceed onto
	//reading the data and storing into
	//proper variables
	if (!infile)
		cout << "Error opening file." << endl;
	else
	{
		infile >> ContestantName >> ScoreA 
			>> ScoreB>> ScoreC >> ScoreD
			>> ScoreE;
		FinalScore = Calculate_Score(ScoreA, ScoreB, 
			ScoreC, ScoreD, ScoreE);
		Print_Results(ContestantName, FinalScore,
			ScoreA, ScoreB, ScoreC, ScoreD, ScoreE);
		while (!infile.eof())
		{
			infile >> ContestantName >> ScoreA 
				>> ScoreB >> ScoreC >> ScoreD
				>> ScoreE;
			FinalScore = Calculate_Score(ScoreA, ScoreB, 
			ScoreC, ScoreD, ScoreE);
			Print_Results(ContestantName, FinalScore,
			ScoreA, ScoreB, ScoreC, ScoreD, ScoreE);
		}
	}
	
	//Closing opened data file and
	//preparing for the program
	//to terminate.
	infile.close();
	system("Pause");
	return 0;
}

//Function: Calculate_Score
//Input: Accepts 5 float parameters
//Process: Calls the Find_Lowest
//	And the Find_Highest functions
//	Also calculates and returns the
//	average of the 3 middle scores.
//Output: 1 double
double Calculate_Score(float ScoreA, float ScoreB, 
	float ScoreC, float ScoreD, float ScoreE)
{
	//Defining variables to be used in the function
	double Highest;
	double Lowest;
	double Average;

	//Calling functions in order to determine
	//the Lowest, and Highest of the scores
	Lowest = Find_Lowest(ScoreA, ScoreB, ScoreC,
		ScoreD, ScoreE);
	Highest = Find_Highest(ScoreA, ScoreB, ScoreC,
		ScoreD, ScoreE);

	//Calculating the average of the 3
	//middle scores by adding all the
	//scores and then subtracting the
	//highest and lowest of the scores
	//then dividing the total by 3.
	Average = ((ScoreA + ScoreB + ScoreC +
		ScoreD + ScoreE) - Highest - Lowest) / 3;

	return(Average);
}

//Function: Find_Lowest
//Input: Accepts 5 float parameters
//Process: Determines the lowest of
//	all the scores and returning
//	it to the Calculate_Score
//	function.
//Output: 1 double
double Find_Lowest(float ScoreA, float ScoreB, 
	float ScoreC, float ScoreD, float ScoreE)
{
	//Defining variables for function
	double CurrentLowest;
	
	//Determining which score is the
	//Lowest
	CurrentLowest = ScoreA;
	if(ScoreB < CurrentLowest)
		CurrentLowest = ScoreB;
	if(ScoreC < CurrentLowest)
		CurrentLowest = ScoreC;
	if(ScoreD < CurrentLowest)
		CurrentLowest = ScoreD;
	if(ScoreE < CurrentLowest)
		CurrentLowest = ScoreE;

	return(CurrentLowest);
}

//Function: Find_Highest
//Input: Accepts 5 float parameters
//Process: Determines the highest of
//	all the scores and returning
//	it to the Calculate_Score
//	function.
//Output: 1 double
double Find_Highest(float ScoreA, float ScoreB, 
	float ScoreC, float ScoreD, float ScoreE)
{
	//Defining variables for function
	double CurrentHighest;
	
	//Determining the highest score
	CurrentHighest = ScoreA;
	if(ScoreB > CurrentHighest)
		CurrentHighest = ScoreB;
	if(ScoreC > CurrentHighest)
		CurrentHighest = ScoreC;
	if(ScoreD > CurrentHighest)
		CurrentHighest = ScoreD;
	if(ScoreE > CurrentHighest)
		CurrentHighest = ScoreE;

	return(CurrentHighest);
}

//Function: Print_Results
//Input: Accepts 7 parameters
//	(1 string, 1 double, 5 floats)
//Process: prints the parameters to
//	the outfile.
//Output: None
void Print_Results(string ContestantName,
	double FinalScore, float ScoreA,
	float ScoreB, float ScoreC,
	float ScoreD, float ScoreE)
{
	ofstream outfile;
	outfile.open("output.txt", ios::app);

	outfile << setw(8) << ContestantName << setw(12)
		<< fixed << setprecision(3) << FinalScore 
		<< fixed << setprecision(1) 
		<< setw(18) << ScoreA << setw(5) 
		<< ScoreB << setw(5) << ScoreC 
		<< setw(5) << ScoreD << setw(5) << ScoreE;
	outfile << endl << endl;
	outfile.close();
}