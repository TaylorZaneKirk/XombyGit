//Written by Taylor Kirk
//Feb. 20, 2016
//This program performs Josephus's permutation on circular linked list

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "CirList.h"

using namespace std;

void Josephus(vector<string> contents)
//requires: A vector of strings containing all the configurations
//	for preforming the Josephus Permutation
//ensures: That the vector of strings 'contents' will be iterated
//	through and based on the expected format of the data a Circular
//	Linked list, CirList, will be constructed for each of the specified number
//	of operations defined in contents. Once each CirList is completed,
//	the josephus permuation will be performed on CirList. The results will be
//	stored in an output file
//checks: That all the data in contents are of expected format.
//	(Number of Datasets(Number of Contestants, number of iterations, [Constestants]))
//	If any unexpected character or input is encountered, will abort and alert the user.
{
	ofstream output;

	int NumDataSets = 0;
	int NumSetsProcessed = 0;
	int CurrentLine = 0;
	int NumContestants = 0;
	int NumConProcessed;
	int NumIterations = 0;

	CirList cll; //Create new Circular Linked List

	NumDataSets = stoi(contents[CurrentLine++]);
	
	//Make sure contents is not empty
	if (contents.size() > 0)
	{

		if (NumSetsProcessed > NumDataSets)
			cout << "ERROR: NO SETS TO PROCESS." << endl;

		//While there are sets to process
		while (NumSetsProcessed < NumDataSets)
		{
			NumContestants = stoi(contents[CurrentLine++]);
			NumIterations = stoi(contents[CurrentLine++]);
			
			//Check that there is at least 1 constestant
			if (NumContestants > 0)
			{
				//Fill CirList
				for (int i = 0; i < NumContestants; i++)
				{
					cll.insertItemEnd(contents[CurrentLine++]);
				}
				//Check that Iterations is at least 1, and that the
				//	number of contestants is greater or equal to the
				//	number of iterations, if so run the permuation.
				if (NumIterations > 0 && NumContestants >= NumIterations)
				{
					cout << "[DATA SET " << NumSetsProcessed + 1 << "]:" <<
						"LIST PREPARED. PERFORMING PERMUTATION..." << endl;
					cll.Permute(NumIterations);
					cout << "[DATA SET " << NumSetsProcessed + 1 << "]:" <<
						"PERMUTATION COMPLETE. RESULTS IN OUTPUT FILE" << endl << endl;
				}
				else
				{
					//Unexpected format, alert user
					cout << "ERROR[DATA SET " << NumSetsProcessed + 1 <<
						"]: THE NUMBER OF CONTESTANTS MUST BE LESS THAN OR " <<
						"EQUAL TO THE NUMBER OF ITERATIONS. SKIPPING THIS SET..."
						<< endl << endl;
				}
			}
			else
				cout << "ERROR[DATA SET " << NumSetsProcessed + 1 << "]: THE NUMBER OF " <<
				"CONTESTANTS MUST BE GREATER THAN OR EQUAL TO ZERO" << endl << endl;
			//Set complete
			NumSetsProcessed++;
		}
	}
	else
		cout << "ERROR: NO DATA DETECTED." << endl;
}

//requires: a string containing all the contents of the
//	input file. All values must be seperated by whitespace
//ensures: Returns a vector of strings representing the
//	configuration of the Permuations
//checks: none
vector<string> PrepareContents(string contents)
{
	vector<string> data;
	stringstream stream(contents);
	string buffer;

	while (stream >> buffer)
		data.push_back(buffer);

	return (data);
}

//requires: none
//ensures: The user will be greeted and informed of program purpose
//	and will prompt the user for input file location.
//checks: none
string GreetAndGetFile()
{
	string contents = "";
	string fileName = "";
	string line;

	ifstream myFile;

	//Welcome prompt
	cout << "Thank you for using MusicalChairs." << endl
		<< "Please enter the file name containing the dataset you would like to use." << endl
		<< "FILE NAME: ";

	cin >> fileName;

	if (!fileName.empty())	//Check if there was input
	{
		myFile.open(fileName);

		if (myFile.is_open())	//Make sure the file exists and can be opened
		{
			while (getline(myFile, line))
			{
				contents.append(line + " ");	//represent new line as a space
			}
		}
	}

	myFile.close();	//close the input file

	return contents;
}

void main()
{
	vector<string> contents;	//Vector of strings that will contains
								//	contents of input file

	//Greet the user and have the string containing the contents of
	//	the input file returned. Format that string have a vector of
	//	string returned containing each value of the string seperated
	//	by white space as individual members in the vector
	contents = PrepareContents(GreetAndGetFile());
	Josephus(contents);	//Perform Josephus's Permutation on the vector of strings
	
	system("PAUSE");
	return;
}