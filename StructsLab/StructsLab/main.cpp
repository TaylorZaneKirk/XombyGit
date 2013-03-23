/*Taylor Kirk
December 07, 2012
Dr. Halverson
Lab #10*/

#include <iostream>
#include <fstream>
#include <cstdlib>    
#include <string>
using namespace std;
int main ()
{
	ifstream infile;

	struct Student
	{
		string lastName;
		string firstName;
		int classification;
		float gpa;
	};
	Student list[100];
	
	int num;
	int NumFreshman = 0;
	int NumSophomore = 0;
	int NumJuniors = 0;
	int NumSeniors = 0;
	int Total = 0;

	double Average = 0.0;

	infile.open("Names.txt");
	if(!infile)
	{
		cerr << "Error: File could not be opened." << endl;
		system("pause");
		exit(1);
	}
	infile >> num;
	for(int i = 0; i < num; i++)
	{
		infile >> list[i].lastName >> list[i].firstName >>
			list[i].classification >> list[i].gpa;

		if(list[i].gpa > 3.0)
			cout << list[i].lastName << " " << list[i].firstName
				<< " " << list[i].gpa << endl;

		if(list[i].classification == 0)
			NumFreshman++;
		else if(list[i].classification == 1)
			NumSophomore++;
		else if(list[i].classification == 2)
			NumJuniors++;
		else if(list[i].classification == 3)
			NumSeniors++;

		Total++;
		Average += list[i].gpa;
	}
	Average /= num;

	cout << "Average GPA of all students: " << Average << endl;
	cout << "Freshman: " << NumFreshman;
	cout << " Sophomores: " << NumSophomore;
	cout << " Juniors: " << NumJuniors;
	cout << " Seniors: " << NumSeniors;
	cout << " Total: " << Total << endl;

	system("pause");
	return 0;
}