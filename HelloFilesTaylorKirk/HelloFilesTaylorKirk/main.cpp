//Taylor Kirk
//Dr. Halverson
//Lab #2
//09/14/2012

#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	int birth_Date;
	ifstream infile;
	ofstream outfile;

	infile.open("input.txt");
	outfile.open("output.txt");
	infile >> birth_Date;

	outfile << "Taylor Kirk \n";
	outfile << birth_Date;
	infile.close();
	outfile.close();
	return 0;
}
