/*Taylor Kirk
Dr. Halverson
Computer Science
09/21/12
Description: Basic Arithmetic; program will calculate output from two given numbers using addition, subtraction, multiplication, division, and modulus.*/

#include<iostream>
#include<fstream>
using namespace std;

int main()
{ 
//initialize variables
int num1;
int num2;

//Prep output file
ofstream outfile;
outfile.open("output.txt");

//Request input
cout << "Please type in an integer then hit the enter key.\n";
cin >> num1;
cout << "Please type in a second number.\n";
cin >> num2;

//Formulas
outfile << "Results:\n";
outfile << num1 << "+" << num2 << "=" << num1 + num2 << endl;
outfile << num1 << "-" << num2 << "=" << num1 - num2 << endl;
outfile << num1 << "*" << num2 << "=" << num1 * num2 << endl;
outfile << num1 << "/" << num2 << "=" << num1 / num2 << endl;
outfile << num1 << "%" << num2 << "=" << num1 % num2 << endl;

system("pause");

outfile.close();
return 0;
}