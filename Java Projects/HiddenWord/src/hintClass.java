//Class Name: hintClass
//Class Purpose: Class containing for getHint Method
public class hintClass extends HiddenWord {
	//Method Name: getHint
	//Parameters: String userGuess - This is a string
	//				containing the guess the user submitted.
	//			  String hiddenWord - This is a string
	//				containing the word that the user
	//				is trying to find out
	//Purpose: This class will check the user's guess against
	//	the value of the hidden word that the user is trying to
	//	find out. getHint will return a string which will indicate
	//	if the guess had any correct characters in it.
	public static String getHint(String userGuess, String hiddenWord)
	{
		String hint = "";

		//Iterate through userGuess and compare each
		//	character against all the characters contained
		//	within the string hiddenWord to evaluate if the
		//	userGuess character is not located within the
		//	hiddenWord string('-'), if the userGuess character
		//	is in the string hiddenWord, but not in the same
		//	location('+'), or if the userGuess character
		//	is both in the hiddenWord and is located in
		//	the same cell number in both string.
		for(int i = 0; i < userGuess.length(); i++)
		{
			if(userGuess.charAt(i) == hiddenWord.charAt(i))
				hint = hint + userGuess.charAt(i);
			else
			{
				String gLetter = "" + userGuess.charAt(i);
				if(hiddenWord.contains(gLetter))
					hint = hint + "+";
				else
					hint = hint + "-";
			}
		}
		
		return(hint);
	}
}
