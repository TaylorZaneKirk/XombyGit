/*Taylor Kirk
Dr. Halverson
October 28, 2012
Descirption: Experimenting with For Loops */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main()
{
	int r, c, s;
	int t = 0;

	ofstream outfile;
	outfile.open("output.txt");

	for (r = 1; r <= 10; r++)
	{
		for (c = 1; c <= 10; c++)
		{
			outfile << setw(3) << r + c;
			s = r + c;
			t += s;
		}
		outfile << endl;
		
	}
	outfile << t << endl;
	system("pause");
	return 0;
}