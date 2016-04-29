//***********************************************************************
//							Character Counting
//							Name: Taylor Kirk
//						Data Structures Date: 02/15/2015
//***********************************************************************
//		This program recieves a set data amounting to a text/novel
//		(35.txt located within source folder). The program's purpose
//		is to count each alphabetical character within the data set
//		(Punctuations/Numbers/Symbols are not counted). Uppercase
//		and lowercase are counted as the same character. Once all
//		characters are accounted for the program arranges the characters
//		in order from greatest to least. This set is printed out for
//		the user to see.
//			
//***********************************************************************

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

/*sort_struct()
Parameters: None
Complexity: N/A
This structure aids in sorting pairs 
	(pair<char [Some Letter], int [Letter's Count]>)
	in order from greatest to least by returning True 
	or False if the second value of the first pair 
	is greater than the second value of the right pair.*/
struct sort_struct {
	bool operator()(const pair<char, int> &left, 
		const pair<char, int> &right) {
		return left.second > right.second;
	}
};

/*main()
Parameters: 35.txt
Complexity: N/A
This function serves as the bulk of the program
	where the sort_struct() is called, calculations
	performed and output printed.*/
int main(int argc, char *argv[])
{
	/*Char_List: Variable containing the 
		unsorted list of alphabetical characters
		within the data set, as well as the number
		of their occurences*/
	map<char, int> Char_List;	

	/*Current_Char: Placeholder variable for
		the current character being read in 
		from the data set file.*/
	char Current_Char;

	/*One_Char: Pair of characters and integers.
		there should exist one pair for each
		individual character found within the
		data set file (A-Z) and a count of
		the number of time they are encountered*/
	pair<char, int> One_Char;

	/*Char_Table: Vector of pairs (of the pair One_Char
		from above). This contains one pair for each
		individual character that is found within the
		data set file as well as the number of times that
		indivudal character is encountered.*/
	vector < pair<char, int> > Char_Table;

	/*The below while loop reads in each character
		from the data set one at a time. Loops
		until the end of data*/
	while (cin >> Current_Char)
	{
		/*The below if statement determines whether
			the most recent character that was read
			in from the data set is an alphabetical
			character.*/
		if (isalpha(Current_Char))
		{ 
			/*if Current_Char is alphabetical, convert
				the character into its uppercase state.*/
			Current_Char = toupper(Current_Char);

			/*The below if statement checks Char_List to
				determine whether or not Current_Char has
				already been placed within Char_List. If
				it is not found, then it is placed within
				a pair, with a count of 1 (signifying it
				was the first of that character found, and
				that pair is placed within Char_List; if
				the character is found, then the count of
				that character's pair is incremented by one*/
			if (!Char_List.count(Current_Char))
				{Char_List.insert(pair<char, int>(Current_Char, 1));}
			else{Char_List[Current_Char]++;}
		}
	}

	/*The below for-loop serves to traverse through the map
		Char_List of unsorted characters and copies each pair
		within the map into the vector Char_Table.*/
	for (map<char, int>::const_iterator i = Char_List.begin(), 
		end = Char_List.end(); i != end; ++i)
	{
		One_Char.first = i->first;
		One_Char.second = i->second;
		Char_Table.insert(Char_Table.begin(), One_Char);
	}

	/*The below function sorts the vector Char_Table from
		greatest to least using the sort_struct() to determine
		the order.*/
	sort(Char_Table.begin(), Char_Table.end(), sort_struct());
	
	/*for-loop traverses the Char_Table vector and
		prints the contents.*/
	for (unsigned int i = 0; i < Char_Table.size(); i++)
	{
		cout << Char_Table[i].first << " " 
			<< Char_Table[i].second << endl;
	}

	return 0;
}