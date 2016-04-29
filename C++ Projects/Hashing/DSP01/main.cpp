/*				Implementation of Hashing
					Name: Taylor Kirk
					Date: 03/24/2015
			Discrete Structures and Analysis
********************************************************
The purpose of this program is to read in a data set file
	(ex. Data.txt; located within source folder) and to
	assign the values within the data set into a hash
	table based on a CRP, followed by printing out
	the result to an output file (output.txt)
********************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

/*			main()
	Parameters: Data.txt
	Purpose: This function serves to assign the keys
		into a hash table based on a hashing algorithm
		and a CRP function*/
int main(int argc, char *argv[])
{
	const int TableSize = 113;	//Constant integer containing the
								//	the size of the hash table.

	int HashTable[TableSize] = { 0 };	//Array of integers of size
										//TableSize, initiated with
										//all spaces containing the
										//integer zero, denoting that
										//the space is empty.

	int ProbeTable[TableSize] = { 0 };	//Array of integers of size
										//TableSize, initated containing
										//only zeroes. This array will
										//denote the number of probes
										//required to place each key
										//with respect to HashTable position

	//Key: Integer variable that will contain the value read in
	//	from the data file.
	//PotentialAddress: Integer variable that will contain the
	//	address within the hash table that the key will attempted
	//	to be inserted into
	//INCR: Integer variable that determines the CRP increment
	//	that will be used in case of a collision
	//Probes: Integer variable containing the number of probes
	//	for each key required to place the key within the
	//	hash table.
	int Key, PotentialAddress, INCR, Probes, Total;
	float Average;
	static int TotalProbes;	//Integer variable containing the number
							//	of probes that were required to place
							//	all the keys within the hash table

	//Print required headings into an output file
	ofstream OutputFile;
	OutputFile.open("output.txt");
	OutputFile << "Taylor Kirk" << endl;
	OutputFile << setw(5) << right << "Address"
		<< setw(20) << right << "Key Value"
		<< setw(20) << right << "Probe Count" << endl;

	INCR = 1;	//Determining the CRP method (ex: If 1, when
				//	a collision occurs, move one space and
				//	and check. If 2, move two spaces and check

	TotalProbes = 0;	//Initiating total probes
	Total = 0;
	//While-loop to read values within data set into
	//	the key integer
	while (cin >> Key)
	{
		Probes = 1;
		++Total;

		//the value of the Key variable modulo the
		//	value of the TableSize variable is used
		//	to determine the address that will be
		//	used to attempt to place the Key into.
		PotentialAddress = Key % TableSize;

		//While-loop that first checks the Hash table
		//	at the address value of Potential address
		//	to see if that address is empty. If so,
		//	this loop breaks to the next instruction
		//	otherwise, the PotentialAddress variable
		//	is recalculated using INCR as the CRP
		while (HashTable[PotentialAddress] != 0)
		{
			PotentialAddress = (PotentialAddress + INCR) % TableSize;
			Probes++;
		}
		HashTable[PotentialAddress] = Key;	//Once a valid address
											//	is found, place the key

		ProbeTable[PotentialAddress] = Probes;	//Update the probe table

		TotalProbes += Probes;	//Add individual key's probes to
								//	total probe count.
	}

	//Loop through the Hash table and print the key located
	//	in each index.
	for (unsigned int i = 0; i < TableSize; i++)
	{
		OutputFile << right << setw(5) << i <<
			setw(20) << right << HashTable[i] <<
			setw(15) << right << ProbeTable[i] << endl;
	}

	Average = double(TotalProbes) / double(Total);

	//Print the total probes used to place all keys, then
	//	close the output file
	OutputFile << "Total Probes: " << TotalProbes << endl
		<< "Total Keys: " << Total << endl
		<< "Average: " << Average << endl;
	OutputFile.close();

	cout << "Program Complete..." << endl;
	return 0;
}