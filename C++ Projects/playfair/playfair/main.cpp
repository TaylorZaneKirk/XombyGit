/*##############################################################
  #	
  #							Taylor Kirk
  #				Network Security - Summer I 2015
  #						Professor Passos
  #							6/23/2015
  #
  #	Project Name: Modified Playfair Cipher Encryption
  #	Purpose: To encrypt plaintext into ciphertext
  #		based on the Playfair cipher.
  #
  ##############################################################
*/
#include <iostream>
#include <string>

using namespace std;

//Class Name: Playfaire
//Class Purpose: Contains the init() function which in turn triggers
//			the formGrid(), readyText(), encryptText(), and displayText()
//			functions.
//Parameters:
//		string Key: This is a string variable containing the keyword
//			to be used by the class to form the matrix that will be used
//			to encrypt the Plaintext
//		string Plaintext: This is a string variable containing the Plaintext
//			that the playfair class will encrypt using the Key.
class playfair
{
public:

	//Function Name: init()
	//Function Parameters: string Key: This is a string variable containing the keyword
	//			to be used by the class to form the matrix that will be used
	//			to encrypt the Plaintext
	//		string Plaintext: This is a string variable containing the Plaintext
	//			that the playfair class will encrypt using the Key.
	//Function Purpse: Public handle for the playfair class
	void init(string Key, string Plaintext)
	{
		formGrid(Key);	//Generates the Matrix by which the Plaintext is Encrypted
		readyText(Plaintext);	//Manipules the user-inputted Plaintext into an acceptable format
		encryptText();	//Function to encypt the modified Plaintext
		displayText();	//Function to output the Ciphertext
	}

private:
	string _Plaintext; //This variable will start as Plaintext, and through its scope will
					   //	be modified multiple time until it resembles the intended ciphertext
	char _Matrix[6][6];//Two-Dementional array by which the Plaintext will be encrypted

	//Private function formGrid()
	//Purpose: This is the first function to be called
	//	by the public init() handler. This function, based on the
	//	Key provided by the user will generate a 6 x 6 matrix containing
	//	the Keyword, followed by the numbers 0 through 9, followed finally
	//	by the letters of the alphabet not found in the Keyword, in
	//	alphabetical order.
	void formGrid(string Key)
	{
		//Error catching--If the user, for what ever reason,
		//	does not provide a key to be used, the class
		//	will use KEYWORD as a default.
		string MatrixFodder = "";
		if (Key.length() < 1)
			Key = "KEYWORD";

		//append all possible values to the end of the Key
		Key += "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		
		//Iterate through the string, change all values to
		//	uppercase is applicable, if the character is
		//	not already found within MatrixFodder, place
		//	the character into MatrixFodder
		for (string::iterator ThisCharacter = Key.begin();
			ThisCharacter != Key.end(); ThisCharacter++)
		{
			*ThisCharacter = toupper(*ThisCharacter);
			if (MatrixFodder.find(*ThisCharacter) == -1)
				MatrixFodder += *ThisCharacter;
		}

		//Copy MatrixFodder, node by node, into _Matrix starting at (0,0)
		copy(MatrixFodder.begin(), MatrixFodder.end(), &_Matrix[0][0]);
	}

	//Function Name: readyText
	//Function Parameters: string Plaintext
	//	provided by the user.
	//Function Purpose: Modify the user provided Plaintext
	//	into a form that is compatible with the encryption
	//	algorithm.
	void readyText(string PlainText)
	{
		string NewText = "";
		int j = 0;
		//Convert all applicable character within the plaintext
		//	into uppercase. Any spaces within the plaintext
		//	will be ignored
		for (string::iterator ThisCharacter = PlainText.begin();
			ThisCharacter != PlainText.end(); ThisCharacter++)
		{
			if (*ThisCharacter != ' ')
			{
				*ThisCharacter = toupper(*ThisCharacter);
				_Plaintext += *ThisCharacter;
			}
		}

		//Iterate through the Plaintext, if two letters
		//	that are side by side are the same, then
		//	split them with an 'X' character
		for (int i = 0; i < _Plaintext.length(); i += 2)
		{
			NewText += _Plaintext[i];
			if (i + 1 < _Plaintext.length())
			{
				if (_Plaintext[i] == _Plaintext[i + 1])
					if (j % 2 == 1)
						NewText += 'X';
				NewText += _Plaintext[i + 1];
			}
			j++;
		}

		_Plaintext = NewText;

		//If _Plaintext has a length that is not even, then
		//	append an 'X' character to the end
		if (_Plaintext.length() & 1)
			_Plaintext += 'X';
	}
	
	//Function Name: getCharacterPosition()
	//Function Parameters: char ThisChar - This variable
	//		contains the character value for the function
	//		to look for within the matrix
	//	int &CellA - Variable passed by reference, which, upon
	//		locating ThisChar within the matrix will set
	//		CellA to be the x-coordinate of the matrix
	//	int &CellB - Same as CellA, but sets itself to
	//	the matrix's y-coordinate
	//Function Purpose: Searches the matrix for ThisChar. If
	//	ThisChar is located within the matrix, sets CellA, and
	//	CellB to its location, and the function returns true,
	//	signaling that ThisChar was found. Else, returns false.
	bool getCharacterPosition(char ThisChar, int &CellA, int &CellB)
	{
		//Traverses the matrix to find ThisChar
		for (int y = 0; y < 6; y++)
			for (int x = 0; x < 6; x++)
				if (_Matrix[y][x] == ThisChar)
				{
					CellA = x;
					CellB = y;
					return true;
				}

		return false;
	}

	//Function Name: getChar()
	//Function Parameters: int CellA - This variable
	//		contains the x-coordinate of the character
	//		to be returned.
	//	int CellB - this variable contains the
	//		y-coordinate of the character to
	//		be returned.
	//Function Purpose: To return the character contained
	//	within the matrix at location, after shift at (CellA, CellB)
	//	This will be the encrypted character.
	char getCharacter(int CellA, int CellB)
	{
		return _Matrix[(CellB + 6) % 6][(CellA + 6) % 6];
	}

	//Function Name: encryptText()
	//Function Parameters: NONE
	//Function Purpose: This is the function
	//	that actually performs the encryption algorithm
	void encryptText(void)
	{
		int CellA, CellB, CellC, CellD;
		string NewText;

		//Traverse the modified Plaintext, and based on a set of rules
		//	within the algorithm, call the getCharacter() function in
		//	order to retrieve the encrypted character from the plaintext
		//	character.
		for (string::const_iterator ThisChar = _Plaintext.begin();
			ThisChar != _Plaintext.end(); ThisChar++)
			
			if (getCharacterPosition(*ThisChar++, CellA, CellB))
				if (getCharacterPosition(*ThisChar, CellC, CellD))
				{
					//If columns of a set are both the same, perform slide
					if (CellA == CellC)
					{
						NewText += getCharacter(CellA, CellB + 1);
						NewText += getCharacter(CellC, CellD + 1);
					}

					//if rows of a set are both the same, perform fall
					else if (CellB == CellD)
					{
						NewText += getCharacter(CellA + 1, CellB);
						NewText += getCharacter(CellC + 1, CellD);
					}

					//if rows and columns are different, perform switch
					else
					{
						NewText += getCharacter(CellC, CellB);
						NewText += getCharacter(CellA, CellD);
					}
				}

		//_Plaintext will now contain completed Ciphertext
		_Plaintext = NewText;
	}

	//Function Name: displayText()
	//Function Parameters: NONE
	//Function Purpose: To display the ciphertext output
	//	(or to display the current value of _Plaintext
	void displayText(void)
	{
		string::iterator ThisCharacter = _Plaintext.begin();
		
		cout << "\nOUTPUT:\n" << endl;

		//While-loop that traverses _Plaintext and
		//	displays the contents in sets of two
		while (ThisCharacter != _Plaintext.end())
		{
			cout << *ThisCharacter;
			ThisCharacter++;
			cout << *ThisCharacter << " ";
			ThisCharacter++;
		}
		cout << endl;
	}

};

//Function Name: main()
//Function Parameters: NONE
//Function Purpose: Provides the user an interface
//	in order to specify a Key to be used to uniquely
//	encrypt a string of text. The user is then expected
//	to provide a message that will be used as plaintext
//	which will be encrypted using the Key previously entered
void main(void)
{
	string Key, PlainText;
	playfair pf;

	cout << "Please enter a key: "; 
	getline(cin, Key);

	cout << "Please enter the PlainText: ";
	getline(cin, PlainText);

	pf.init(Key, PlainText);
	system("Pause");
	return;
}