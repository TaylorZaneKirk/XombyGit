/*
 * This program allows user(s) to play a Hidden Word
 * 	game.
 * 
 * Name: Taylor Kirk
 * Date: 9/3/2015
 * Instructor: Prof. Stringfellow
 */
import java.util.*;

//Class containing the main class as well as the getHint class.
public class HiddenWord {
	//Class Name: main
	//Parameters: N/A
	//Purpose: Main class of the program. The user will be greeted,
	//			and prompted to enter a word to be the game's
	//			Hidden Word. Then, the user will be given the
	//			length of the hidden word, and prompted to
	//			attempt to guess what the Hidden Word is.
	//			The user will have 10 tries to correctly
	//			guess the hidden word. If the user does
	//			not succeed within 10 tries, the game is over.
	
	public static void main(String[] args)
	{
		System.out.println("Thank you for playing Rude Hidden "
				+ "Word Game. The game you just can't win.\n"
				+ "Disclaimer: Players can definitely 'win'"
				+ "the aforementioned game.");
		System.out.print("Please enter a word to hide: ");
		
		//Read in user input; Convert to CAPS.
		Scanner in = new Scanner(System.in);
		String hiddenWord = in.nextLine();
		hiddenWord = hiddenWord.toUpperCase();
		
		//Give user the number of characters
		//	in the Hidden Word.
		int wordLength = hiddenWord.length();
		System.out.println("Length of hidden word: " + wordLength);
		
		//While-loop that serves to conduct most
		//	of the bulk of the game.
		String userGuess = "";
		String hint = "";
		int guessCount = 0;
		
		//Check if user has exceeded the allowed number of guesses
		//	or if the user has guessed the hidden word.
		while(!userGuess.contentEquals(hiddenWord)&&guessCount < 10)
		{
			//Prompt for guess; Convert to CAPS
			System.out.print("Please enter a guess: ");
			userGuess = in.nextLine();
			userGuess = userGuess.toUpperCase();
			
			//Compare number of characters in userGuess
			//	against the number of characters in
			//	hiddenWord, return if values are not equal
			//	Otherwise, call getHint
			if(userGuess.length() == hiddenWord.length())
			{
				hint = hintClass.getHint(userGuess, hiddenWord);
				System.out.println("Hint: " + hint);
			}
			else
				System.out.println("Length Mismatch.");
			
			guessCount++;
		}
		
		//Snide comments correlating with the number
		//	of guesses the user finished the game with.
		if(guessCount == 1)
			System.out.println("SUCCESS!!!\nFirst try? "
					+ "You definitely cheated.");
		else if(guessCount < 5)
		{
			System.out.println("Good job! You got the answer\n"
					+ "with only a little bit of help. You're welcome.");
		}
		else if(guessCount < 9)
		{
			System.out.println("Well, you finally got it. Took you\n"
					+ "long enough. I wouldn't brag about this\n"
					+ "if I were you...");
		}
		else if(guessCount == 10)
		{
			System.out.println("Out of tries! Sorry!");
			System.out.println("Wow, 10 guesses? Are you even trying "
					+ "or did a cat just crawl on the keyboard?");
			System.out.println("Answer: " + hiddenWord);
		}
		
		//Display total number of guesses.
		System.out.println("Number of guesses: " + guessCount);
		
		//Close Scanner.
		in.close();
	}
}
