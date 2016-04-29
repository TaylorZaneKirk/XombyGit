/**
 * 
 * @author Taylor Kirk
 * Professor Stringfellow
 * CoinSorter - Project2
 *
 */

import java.io.*;
import java.util.*;

//CoinSorter class contains variables key to the function
//	of the overall program. CoinSorter also includes methods
//	to generate a coin list, read a coin list, calculate totals
public class CoinSorter {

	//Number of coins to be generated and/or
	//	to be evaluated by the program
	static final int NUM_OF_COINS = 800;

	//Default file name used for writer/reading
	//	a file filled with coin denominations
	static final String FILE_NAME = "CoinSort.txt";

	//Numeric representations for coin conversion
	//	from file.
	private final static int QUARTER = 3;
	private final static int DIME = 2;
	private final static int NICKEL = 1;
	private final static int PENNY = 0;
	
	//Numeric representations for the number
	//	of coin that can be contained within
	//	each roll
	private final static int NUM_Q_PER_ROLL = 40;
	private final static int NUM_D_PER_ROLL = 50;
	private final static int NUM_N_PER_ROLL = 40;
	private final static int NUM_P_PER_ROLL = 50;
	
	//Total number of rolls(filled) for
	//	each coin type
	private static int NUM_QUARTER_ROLLS = 0;
	private static int NUM_DIME_ROLLS = 0;
	private static int NUM_NICKEL_ROLLS = 0;
	private static int NUM_PENNY_ROLLS = 0;
	
	//Total number of extra(loose) coins
	//	for each coin type
	private static int NUM_EXTRAS_QUARTER = 0;
	private static int NUM_EXTRAS_DIME = 0;
	private static int NUM_EXTRAS_NICKEL = 0;
	private static int NUM_EXTRAS_PENNY = 0;
	
	//Total dollar value for each coin type
	// and Total dollar value for all coins
	private static double TOTAL_QUARTER = 0.0;
	private static double TOTAL_DIME = 0.0;
	private static double TOTAL_NICKEL = 0.0;
	private static double TOTAL_PENNY = 0.0;
	private static double TOTAL = 0.0;
	
	//Number of markers contained within
	//	the input file
	private static int NUM_MARKERS = 0;
	
	//USER_FILE is initialized in beginSort()
	//	NULL unless user chooses to load
	//	their own file.
	private static String userFile;
	
	//Choice values for user to designate
	//	whether they want to load their own
	//	file ('L') or to load the default
	//	generated file ('D')
	public static final char CHOSE_DEFAULT = 'D';
	public static final char CHOSE_LOAD = 'L';
	
	//Functions for output of penny rolls, extras, and dollar total
	public static String getPennyRolls()
		{return toString(NUM_PENNY_ROLLS);}
	public static String getPenny()
		{return toString(NUM_EXTRAS_PENNY);}
	public static double getPennyTotal()
		{return(TOTAL_PENNY / 100);}
	
	//Functions for output of nickel rolls, extras, and dollar total
	public static String getNickelRolls()
		{return toString(NUM_NICKEL_ROLLS);}
	public static String getNickel()
		{return toString(NUM_EXTRAS_NICKEL);}
	public static double getNickelTotal()
		{return(TOTAL_NICKEL / 100);}
	
	//Functions for output of dime rolls, extras, and dollar total
	public static String getDimeRolls()
		{return toString(NUM_DIME_ROLLS);}
	public static String getDimes()
		{return toString(NUM_EXTRAS_DIME);}
	public static double getDimeTotal()
		{return(TOTAL_DIME / 100);}
	
	//Functions for output of quarter rolls, extras, and dollar total
	public static String getQuarterRolls()
		{return toString(NUM_QUARTER_ROLLS);}
	public static String getQuarter()
		{return toString(NUM_EXTRAS_QUARTER);}
	public static double getQuarterTotal()
		{return(TOTAL_QUARTER / 100);}
	
	//Function for returning total dollar amount
	public static double getTotal()
		{return(TOTAL / 100);}
	
	//Function to return current marker count
	public static String getMarkers()
		{return toString(NUM_MARKERS);}
	
	//Return string representation of a single double
	private static String toString(double d)
	{
		String thisDouble = new Double(d).toString();
		return(thisDouble);
	}
	
	//Return string representation of an
	//	array of integers
	private static String toString(int a[])
	{
		String thisArray = "[ ";
		for(int i = 0; i < a.length; i++)
		{
			thisArray += a[i] + ",";
		}
		thisArray += " ]";
		return thisArray;
	}
	
	//Converts quantity of various coins into proper value
	private static void calcTotals()
	{
		TOTAL_QUARTER = 25 * ((NUM_QUARTER_ROLLS * NUM_Q_PER_ROLL)
				+ NUM_EXTRAS_QUARTER);
		TOTAL_DIME = 10 * ((NUM_DIME_ROLLS * NUM_D_PER_ROLL)
				+ NUM_EXTRAS_DIME);
		TOTAL_NICKEL = 5 * ((NUM_NICKEL_ROLLS * NUM_N_PER_ROLL) 
				+ NUM_EXTRAS_NICKEL);
		TOTAL_PENNY = (NUM_PENNY_ROLLS * NUM_P_PER_ROLL) 
				+ NUM_EXTRAS_PENNY;
		TOTAL = TOTAL_QUARTER + TOTAL_DIME + TOTAL_NICKEL 
				+ TOTAL_PENNY;
	}
	
	//Function Name: EasyRolls
	//Return type: int
	//Parameters: int, int
	//Purpose: Returns the number of rolls of a
	//	type of coin based on which coin, and 
	//	how many coins can fit in a roll
	private static int EasyRolls(int whatCoin, int perRoll)
	{
		int numRolls = whatCoin / perRoll;
		return numRolls;
	}
	
	//Function Name: EasyExtras
	//Return type: int
	//Parameters: int, int,
	//Purpose: Returns the number of extras of a type of coin
	//	based on coin type and how many coins can fit into a roll
	private static int EasyExtras(int whatCoin, int perRoll)
	{
		int numExtras = whatCoin % perRoll;
		return numExtras;
	}
	
	//Function Name: loadArrays
	//Parameters: String
	//Purpose: To read the input file and fill an
	//	arraylist with the unsorted values. The ArrayList
	//	is then sorted and converted into a regular, sorted
	//	array. The sorted array is then evaluated with the
	//	Calculate() method, the calcTotals() method, and
	//	then the results are printed
	private static void loadArrays(String fileName) throws IOException
	{
		int thisCoin = 0;
		Scanner scanner = null;
		ArrayList<Integer> loadArray = null;
		int sortedArray[];
		
		try
		{
			scanner = new Scanner(new File(fileName));
			loadArray = new ArrayList<Integer>();
			while(scanner.hasNextInt())
			{
				if((thisCoin = scanner.nextInt()) != -1)
				{
					loadArray.add(thisCoin);
				}
				else
				{
					NUM_MARKERS++;
					Collections.sort(loadArray);
					sortedArray = loadArray.stream()
							.mapToInt(Integer::intValue).toArray();
					loadArray.clear();
					Calculate(sortedArray);
					calcTotals();
					Project2.toConsole(4);
				}
			}
			
		}
		finally
		{
			if(scanner != null)
				scanner.close();
		}
	}
	
	//Function Name: Calculate
	//Parameters: int[]
	//Purpose: To count the number of various coins
	//	and organize them into rolls and extras
	public static void Calculate(int sortedRoll[])
	{
		if(sortedRoll.length == 0)
		{
			Project2.toConsole(3);
		}
		else
		{
			for(int i : sortedRoll)
			{
				switch(i)
				{
				case 1: NUM_EXTRAS_PENNY++; break;
				case 5: NUM_EXTRAS_NICKEL++; break;
				case 10: NUM_EXTRAS_DIME++; break;
				case 25: NUM_EXTRAS_QUARTER++; break;
				}
			}
			NUM_PENNY_ROLLS += EasyRolls(NUM_EXTRAS_PENNY,
					NUM_P_PER_ROLL);
			NUM_EXTRAS_PENNY = EasyExtras(NUM_EXTRAS_PENNY,
					NUM_P_PER_ROLL);
			
			NUM_NICKEL_ROLLS += EasyRolls(NUM_EXTRAS_NICKEL,
					NUM_N_PER_ROLL);
			NUM_EXTRAS_NICKEL = EasyExtras(NUM_EXTRAS_NICKEL,
					NUM_N_PER_ROLL);
			
			NUM_DIME_ROLLS += EasyRolls(NUM_EXTRAS_DIME,
					NUM_D_PER_ROLL);
			NUM_EXTRAS_DIME = EasyExtras(NUM_EXTRAS_DIME,
					NUM_D_PER_ROLL);
			
			NUM_QUARTER_ROLLS += EasyRolls(NUM_EXTRAS_QUARTER,
					NUM_Q_PER_ROLL);
			NUM_EXTRAS_QUARTER = EasyExtras(NUM_EXTRAS_QUARTER,
					NUM_Q_PER_ROLL);
		}
	}
	
	//Return string representation of a single integer
	public static String toString(int i)
	{
		String thisInteger = new Integer(i).toString();
		return(thisInteger);
	}
	
	//Function Name: beginSort()
	//Purpose: To tell the rest of the class
	//	what file it is operating on
	public static void beginSort() throws IOException
	{
		Scanner input = null;
		String userChoice = null;
		
		//print initial coinSort instructions
		Project2.toConsole(1);
		
		input = new Scanner(System.in);
		userChoice = input.nextLine().toUpperCase();
		
		if(userChoice.charAt(0) == 'D')
			loadArrays(FILE_NAME);
		else if(userChoice.charAt(0) == 'L')
		{
			Project2.toConsole("Please input file name: ");
			userFile = input.nextLine();
			loadArrays(userFile);
		}
		else
		{
			Project2.toConsole("Invalid Choice. Loading"
					+ " default file.");
			loadArrays(FILE_NAME);
		}
		
		input.close();
	}

	//Function Name: generateCoins()
	//Purpose: To create a new file and to fill
	//	that file with values between -1 and 3
	public static void generateCoins() throws IOException
	{
		
		Random newRoll = new Random();
		FileWriter outputStream = null;
		int probNewRoll;
		
		try
		{
			outputStream = (new FileWriter(FILE_NAME));
			
			for(int i = 0; i < NUM_OF_COINS; i++)
			{
				//(1/160) is the reduced value of (8/500)
				//	if probNewRoll == 80, then add '-1'
				//	to the coinList array
				probNewRoll = newRoll.nextInt(160);
				
				if(probNewRoll == newRoll.nextInt(160) && i != 0)
					outputStream.write("-1 ");
				else
				{
					int k = newRoll.nextInt(4);
					switch(k)
					{
						case PENNY: outputStream.write("1 "); break;
						case NICKEL: outputStream.write("5 "); break;
						case DIME: outputStream.write("10 "); break;
						case QUARTER: outputStream.write("25 "); break;
					}
					
				}
				
				if((i + 1)% 20 == 0 && i != 0)
					outputStream.write("\r\n");
			}
		}
		finally
		{
			if(outputStream != null)
			{
				outputStream.write("-1");
				outputStream.close();
				Project2.toConsole("File: '" + FILE_NAME + 
						"' has been generated.\n");
			}
		}
	}
}
