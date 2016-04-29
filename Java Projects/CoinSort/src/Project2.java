/**
 * 
 * @author Taylor Kirk
 * Professor Stringfellow
 * CoinSorter - Project2
 *
 */


import java.io.*;
import java.text.DecimalFormat;

//This class contains methods to communicate with the user
//	as well as the main method, which also handles exceptions
//	This program is made to simulate a coin sorter machine.
//	a file will be automatically generated, but the user
//	can specify their own file, as well, providing
//	it follows the acceptable format
public class Project2 {

	//Function to print a parameterized String to the console
	public static void toConsole(String stringToPrint)
	{
		System.out.println(stringToPrint);
	}
	//Overloaded function that prints a predefined
	//	set of strings to the console.
	//0: General greeting
	//1: Print instructions to designate file
	//3: Print invalid array error
	//4: Print final output
	public static void toConsole(int choice)
	{
		if(choice == 0)
		{
			System.out.println("Coin Sorter 9000:Greeting");
			System.out.println("This program will provide you with an "
					+ "easy and quick way to sort the coins you\n "
					+ "have into convenient rolls and tell you "
					+ "exactly how much money you have, and\n "
					+ "how many of each coin you have.\n");
		}
		else if(choice == 1)
		{
			System.out.println("Please specify if you would like to\n"
					+ "load the default file containing\nthe "
					+ "various coin denominations to sort)");
			System.out.println("Please input '" + 
					CoinSorter.CHOSE_DEFAULT + "' to "
					+ "load '" + CoinSorter.FILE_NAME + "' by default");
			System.out.println("Please input '" + CoinSorter.CHOSE_LOAD + "' to "
					+ "choose a file to load");
		}
		else if(choice == 3)
		{
			System.out.println("An error has occured. "
					+ "I can not find your coins.");
		}
		else if(choice == 4)
		{
			DecimalFormat formatter = new DecimalFormat("#0.00");
			System.out.println("After marker #" + CoinSorter.getMarkers());
			System.out.println(CoinSorter.getPennyRolls() +
					" rolls of pennies + " + CoinSorter.getPenny() +
					" pennies = $" + 
					formatter.format(CoinSorter.getPennyTotal()));
			System.out.println(CoinSorter.getNickelRolls() +
					" rolls of nickels + " + CoinSorter.getNickel() +
					" nickels = $" + 
					formatter.format(CoinSorter.getNickelTotal()));
			System.out.println(CoinSorter.getDimeRolls() +
					" rolls of dimes + " + CoinSorter.getDimes() +
					" nickels = $" + 
					formatter.format(CoinSorter.getDimeTotal()));
			System.out.println(CoinSorter.getQuarterRolls() +
					" rolls of quarters + " + CoinSorter.getQuarter() +
					" quarters = $" + 
					formatter.format(CoinSorter.getQuarterTotal()));
			System.out.println("Total = $" + 
					formatter.format(CoinSorter.getTotal()) + "\n");
		}
	}
	
	//Simple greeting to the user, afterward,
	// calls on CoinSorter class to generate
	// a coin file
	public static void greeting() throws IOException
	{
		//print greeting user default message 0(zero)
		toConsole(0);
		CoinSorter.generateCoins();
	}
	
	//main Function to greet user and to begin the sorting process
	public static void main(String[] args)
	{
		//Initiate greeting in order
		//	to obtain coin data
		try
		{
			greeting();
			CoinSorter.beginSort();
		}
		catch(IOException x)
		{
			System.err.format("IOException: ", x);
		}
	}
}
