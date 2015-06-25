//***********************************************************************
//					UVa 118 - Mutant Flatworld Explorers
//						Name: Taylor Kirk
//					Data Structures Date: 02/1/2015
//***********************************************************************
//		This program recieves a set data including integers (ex. Data.txt)
//			and characters which will serve as instructions for how the
//			program will conduct its operations. The purpose of this program
//			is to determine a matrix of valid possible coordinates (First two
//			integers contained within Data.txt) followed by placing a "robot"
//			at some point within the afore mentioned matrix (with (0,0) and
//			([First input integer],[Second input integer]) being considered
//			to be the minimum and maximum points valid within afore mentioned
//			matrix. The robot's position is determined by the second set
//			of numbers contained within the input file. This is followed by
//			determining the robot's direction which is accomplished by
//			reading in the next character in the input. The program will
//			then read in the entire next line which will serve as the
//			instruction set. This set of characters determines the actions
//			performed by the robot such as changing direction or moving
//			forward. If the robot happens to move off of the acceptable
//			limits of the matrix, then that position that the robot moved
//			into is added into two vectors (one such for x, and one for y
//			coordinates) Afterwards, if another robot attempts to enter
//			the invalid position, the instruction will be ignored. The
//			program will then repeat these operations until it reaches
//			the end of the data file. After each robot the program will
//			print out the ending position of the robot. If the robot
//			terminated in an invalid postion the output will be appended
//			with the phrase "LOST".
//			
//***********************************************************************

//***********************************************************************
//							main()
//						Parameters: Data.txt - This file would contain
//							the set of instructions for the program to operate
//						Complexity: Unknown
//		This function serves as the whole of the program. No other
//			functions will be called. This function will calculate
//			the ending position of a variable number of robots
//			
//***********************************************************************

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
	int GridWidth;	//Max grid width(x)
	int GridHeight;	//Max grid height(y)
	int Robot_x;	//Current x-coord. of Current Robot
	int Robot_y;	//Current y-coord. of Current Robot
	char Instruction;	//Variable used for assigning various instructions (Coordinates, etc...)
	char Direction;	//Current direction of current Robot(N,W,E,S)
	string line;	//Serves as a general read-into string variable
	vector<char> Set;	//Is the set of robot-instructions for movement
	vector<int> Invalid_x;	//Is the container of invalid x-coordinate positions
								//(Related to Invalid_y in a linear fashion)
	vector<int> Invalid_y;	//is the container of invalid y_coordinate positions
								//(Related to Invalid_x in a linear fashion)
	int Last_x;	//Stores the last valid x-coordinate that the current active robot inhabited
	int Last_y;	//Stores the last valid y_coordinate that the current active robot inhabited
	bool RobotDied;	//Boolean variable that is True if the robot is currently located in an
						//invalid position. False otherwise

	getline(cin, line);	//Reads in the first line of data, containing the integers
							//which are used for setting int GridWidth and int
							//GridHeight, respectively
	istringstream BoardMaximums(line);
	BoardMaximums >> GridWidth >> GridHeight;	//Setting viable maximums

	//Main while loop. This loops once for every robot
	while (getline(cin, line))
	{
		istringstream ThisLine(line);
		ThisLine >> Robot_x >> Robot_y >> Direction;	//Determining robot's beginning location
															//and direction
		RobotDied = false;	//Reset robot's current status
		getline(cin, line);	//This reads in the set of characters that serve as
								//instructions to move the robot
		istringstream Commands(line);

		//While loop that serves to prepare the set of instructions
		//	for the current robot
		while (Commands >> Instruction){ Set.push_back(Instruction); }
		
		//For loop to process current Robot's instructions.
		for (unsigned int i = 0; i < Set.size(); i++)
		{
			Instruction = Set[i];	//Current instruction to be interpreted.
			Last_x = Robot_x;	//Storing last valid x-coordinate location
			Last_y = Robot_y;	//Storing last valid y-coordinate location

			//If the robot hasn't moved off of the designated grid
			//	then allow for instructions to be put into motion
			if (!RobotDied)
			{
				//If the instruction is an 'R' it is interpreted as
				//	turn the robot to the right. If the Robot is currently
				//	facing North ('N') then turning right will cause
				//	the robot to now be facing East ('E') this
				//	same pattern is repeated for other directions
				//	as well. (West: ['W'], South: ['S'])
				if (Instruction == 'R')
				{
					if (Direction == 'N'){ Direction = 'E'; }
					else if (Direction == 'E'){ Direction = 'S'; }
					else if (Direction == 'S'){ Direction = 'W'; }
					else if (Direction == 'W'){ Direction = 'N'; }
				}

				//If the instruction is an 'L' it is interpreted as
				//	turn the robot to the left. If the Robot is currently
				//	facing North ('N') then turning right will cause
				//	the robot to now be facing West ('W') this
				//	same pattern is repeated for other directions
				//	as well. (East: ['E'], South: ['S'])
				else if (Instruction == 'L')
				{
					if (Direction == 'N'){ Direction = 'W'; }
					else if (Direction == 'E'){ Direction = 'N'; }
					else if (Direction == 'S'){ Direction = 'E'; }
					else if (Direction == 'W'){ Direction = 'S'; }
				}

				//if the instruction is 'F' then, based on the direction
				//	the current robot is facing (North, East, South, or West)
				//	the robot will advance one position. If the robot's
				//	direction is North or South, then the y-coordinate
				//	will be either incremented (case of North) or decremented
				//	(case of South). If direction is East, or West, the
				//	x-coordinate will be incremented (case of East) or
				//	decremented (case of West)
				else if (Instruction == 'F')
				{
					if (Direction == 'N'){ Robot_y++; }
					else if (Direction == 'W'){ Robot_x--; }
					else if (Direction == 'E'){ Robot_x++; }
					else if (Direction == 'S'){ Robot_y--; }

					//After movement is performed, a for loop is started
					//	that checks to see if the Robot went off the grid
					//	in a location that a previous robot 'died.' If so,
					//	return the robot to it's last valid location
					for (unsigned int i = 0; i < Invalid_x.size(); i++)
					{
						if (Robot_x == Invalid_x[i] && Robot_y == Invalid_y[i]){ Robot_x = Last_x; Robot_y = Last_y; }
					}
				}

				//If the robot 'died' from a new location, then store the new invalid
				//	coordinates into two seperate vectors (one for x-coordinate
				//	one for y-coordinate). Then, return the robot to its last
				//	valid location, then declare that the Robot 'died'
				if ((Robot_x < 0) || (Robot_y < 0) ||
					(Robot_x > GridWidth) || (Robot_y > GridHeight))
				{
					Invalid_x.push_back(Robot_x);
					Invalid_y.push_back(Robot_y);
					Robot_x = Last_x;
					Robot_y = Last_y;
					RobotDied = true;
				}
			}
		}

		
		Set.clear();	//Prep for next robot by clearing the previous instruction set

		//Print the current Robot's coordinates as well as its current direction
		cout << Robot_x << " " << Robot_y << " " << Direction;

		//If the robot had died print "LOST" after the
		//	previous output
		if (RobotDied)
			cout << " LOST";
		cout << endl;
	}

	cin.ignore();
	return 0;
}