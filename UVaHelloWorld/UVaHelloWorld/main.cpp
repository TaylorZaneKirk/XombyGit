//***********************************************************************
//					UVa Warm Up 11636 - Hello World
//						Name: Taylor Kirk
//					Data Structures Date: 01/21/2015
//***********************************************************************
//		This program recieves a set data including integers (ex. Data.txt)
//			and based on the quantity and type of integers the program
//			will calulate the minimum amount of copying required to
//			duplicate a single line a certain number of times.
//			Once the program is fed a negative integer,
//			the program will terminate.
//***********************************************************************

//***********************************************************************
//							main()
//						Parameters: Data.txt - This file would contain
//							the set of integers to instruct the program
//						Complexity: Unknown
//		This function serves as the whole of the program. No other
//			functions will be called. This function will calculate
//			the total number of "copy" procedures that are required
//			to duplicate a single line to a certain total number.
//***********************************************************************

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	int Copies;
	int TotalNumber;
	int LinesExisting;
	int i = 0;

	while (cin >> TotalNumber)
	{
		Copies = 0;
		LinesExisting = 1;
		i++;

		if (TotalNumber < 0)
			break;
		else if (TotalNumber == 1)
		{
			Copies = 0;
		}
		else
		{
			while (true)
			{
				LinesExisting = LinesExisting * 2;
				if (LinesExisting >= TotalNumber)
				{
					Copies++;
					break;
				}
				else
					Copies++;
			}
		}

		cout << "Case " << i << ": " << Copies << endl;
	}
	cin.ignore();
	return 0;
}
