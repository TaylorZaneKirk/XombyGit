/*Taylor Kirk
Dr. Halverson
November 6, 2012
Description: Program to compute the balance of a bank account
	Over the span of several months.*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

//Function Prototype; Function name is DoDeposit;
//Function type is double; Function Parameters is 1 double
double DoDeposit(double);

//Function Prototype; Function name is DoWithdrawal;
//Function type is double; Function Parameters is 1 double
double DoWithdrawal(double);

//Function Prototype; Function name is DoInterest;
//Function type is double; Function Parameters is 2 doubles
double DoInterest(double, double);

int main ()
{
	//Delcaring the variables to be 
	//used in the Bank Account program
	string Username;
	char UserInput;

	int InterestDisplay;
	int Count;
	int ContinueTF = 1;
	int KeepGoing = 1;

	double InterestRate;
	double InitialBalance;
	double Deposit;
	double NewBalance;
	double Withdrawal;
	double Interest;

	//Prepping Out/In files to be
	//used for the Bank Account
	//program.
	ofstream outfile;
	ifstream infile;
	outfile.open("output.txt");
	infile.open("Data.txt");

	//Other neccessary preps
	outfile << fixed << setprecision(2);
	cout << fixed << setprecision(2);

	outfile << "Taylor Kirk" << endl << endl;
	Count = 1;

	//Beginning Program
	cout << "Welcome to Bank Co. Account program" << endl;

	while (ContinueTF == 1)
	{
		if(KeepGoing == 0)
			KeepGoing = 1;

		cout << "Please input your last name." << endl;
		cin >> Username;
		outfile << Username << endl;

		cout << "Welcome " << Username << ". Please enter your "
			"account balance." << endl;
		cin >> InitialBalance;

		while (InitialBalance < 0)
		{
			cout << "Invalid Input. Please re-enter your balance."
				<< endl;
			cin >> InitialBalance;
		}

		cout << endl << "Please enter interest rate." << endl;
		cin >> InterestRate;
		while (InterestRate < 0)
		{
			cout << "Invalid Input. Please re-enter your interest."
				<< endl;
			cin >> InterestRate;
		}

		outfile << "      Interest Rate" << setw(24) << InterestRate
			<< "%" << endl;
		outfile << "      Initial Balance       $" << setw(15) <<
			InitialBalance << endl;

		while (KeepGoing == 1)
		{
			cout << "Please enter 'D' or 'd' for Deposits, "
				"'W' or 'w' for Withdrawals, 'I' or 'i' for Interest "
				"or enter 'X' or 'x' to exit." << endl;
			cin >> UserInput;

			switch(UserInput)
			{
				case 'D': 
					{
						NewBalance = DoDeposit(InitialBalance);
						Deposit = NewBalance - InitialBalance;
						InitialBalance = NewBalance;
						outfile << "      Deposit               $" <<
							setw(15) << Deposit << endl;
						outfile << "      New Balance           $" <<
							setw(15) << InitialBalance << endl;
						break;
					}
				case 'd':
					{
						NewBalance = DoDeposit(InitialBalance);
						Deposit = NewBalance - InitialBalance;
						InitialBalance = NewBalance;
						outfile << "      Deposit               $" <<
							setw(15) << Deposit << endl;
						outfile << "      New Balance           $" <<
							setw(15) << InitialBalance << endl;
						break;
					}
				case 'W':
					{
						NewBalance = DoWithdrawal(InitialBalance);
						Withdrawal = InitialBalance - NewBalance;
						InitialBalance = NewBalance;
						outfile << "      Withdrawal            $" <<
							setw(15) << Withdrawal << endl;
						outfile << "      New Balance           $" <<
							setw(15) << InitialBalance << endl;
						break;
					}
				case 'w':
					{
						NewBalance = DoWithdrawal(InitialBalance);
						Withdrawal = InitialBalance - NewBalance;
						InitialBalance = NewBalance;
						outfile << "      Withdrawal            $" <<
							setw(15) << Withdrawal << endl;
						outfile << "      New Balance           $" <<
							setw(15) << InitialBalance << endl;
						break;
					}
				case 'I':
					{
						NewBalance = DoInterest(InitialBalance, InterestRate);
						Interest = NewBalance - InitialBalance;
						InitialBalance = NewBalance;
						outfile << "      Interest              $" <<
							setw(15) << Interest << endl;
						outfile << "      New Balance           $" <<
							setw(15) << InitialBalance << endl;
						break;
					}
				case 'i':
					{
						NewBalance = DoInterest(InitialBalance, InterestRate);
						Interest = NewBalance - InitialBalance;
						InitialBalance = NewBalance;
						outfile << "      Interest              $" <<
							setw(15) << Interest << endl;
						outfile << "      New Balance           $" <<
							setw(15) << InitialBalance << endl;
						break;
					}
				case 'X': KeepGoing = 0;
					break;
				case 'x': KeepGoing = 0;
					break;
				default:
					{
						cout << "Sorry, I could not recognize your command."
						" Please try again." << endl;
					}
			}
			
		}
		outfile << endl;
	}


	system("pause");
	return 0;
}

/*Function: DoDeposit
Input: Accepts 1 double parameter
Process: Asks user to input how much
	he or she would like to deposit
	into their account. Then adds
	that amount to their balance.
Output: Two doubles*/
double DoDeposit(double InitialBalance)
{
	double DepositAmount;

	ofstream outfile; 

	cout << "Please enter the amount you would "
		"like to deposit." << endl;
	cout << "Balance: " << InitialBalance << endl;
	cin >> DepositAmount;

	while(DepositAmount < 0)
	{
		cout << "Invalid input. Please re-enter amount"
			" you wish to deposit." << endl;
		cin >> DepositAmount;
		
	}
	cout << "Deposit: " << DepositAmount << endl;
	InitialBalance += DepositAmount;
	cout << "Balance: " << InitialBalance << endl;
	return(InitialBalance);
}

/*Function: DoWithdrawal
Input: Accepts 1 double parameter
Process: Asks user to input how much
	he or she would like to withdrawal
	from their account. Then subtracts
	that amount to their balance.
Output: Two doubles*/
double DoWithdrawal(double InitialBalance)
{
	double WithdrawalAmount;

	cout << "Please enter the amount you would "
		"like to withdrawal." << endl;
	cout << "Balance: " << InitialBalance << endl;
	cin >> WithdrawalAmount;

	while(WithdrawalAmount < 0||WithdrawalAmount > InitialBalance)
	{
		cout << "Invalid input. Please re-enter amount"
			" you wish to withdrawal" << endl;
		cin >> WithdrawalAmount;
	}


	cout << "Withdrawal: " << WithdrawalAmount << endl;
	InitialBalance -= WithdrawalAmount;
	cout << "Balance: " << InitialBalance << endl;
	return(InitialBalance);
}

/*Function: DoInterest
Input: Accepts 2 double parameters
Process: Calculates the monthly interest
Output: 1 double*/
double DoInterest(double InitialBalance, double InterestRate)
{
	double InterestDecimal;
	double InterestAmount;

	cout << "Balance: " << InitialBalance << endl;
	cout << "Interest Rate: " << InterestRate << endl;
	InterestDecimal = InterestRate / 100;
	InterestDecimal = InterestDecimal / 12;
	InterestAmount = InitialBalance * InterestDecimal;
	InitialBalance += InterestAmount;
	cout << "Interest: " << InterestAmount << endl;
	cout << "Balance: " << InitialBalance << endl;
	return(InitialBalance);
}

