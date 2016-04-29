//UNIT NAME : PROG5A.cpp
//PURPOSE   : Construct an ADT representation of a DiGraph, and construct its complement
//WRITTEN FOR : CMPS 3013
//WRITTEN BY : Taylor Kirk
//DATE : 4/24/2016

//#include <ctype>
#include <iostream>
#include <fstream>
#include "DiGraph.h"
#include "EnhDiG.h"
#include "Stack.h"
using namespace std;

void OpenFiles (ifstream & infile, ofstream & outfile);

int main ( )
// PreCondition : none
// PosrCondition : The prerequisites for the courses in a program of study  
//                 are read from an input file, and the prerequisites for  
//                 each course selected by the user are found and sent to  
//                 the output file.  The process is repeated  until the user  
//                 decides to stop looking for prerequisites  
// ErrorCondition : none  
{
	DiGraph MyGraph;
	DiGraph CompGraph;
	ifstream infile;
	ofstream outfile;
  // open input & output files
	
	OpenFiles(infile, outfile);
	
	// read data file into G
	ReadDiGraph(MyGraph, infile, outfile);
	

  //5A find complement
	Complement(MyGraph, CompGraph);

  //print graph and print complement graph
	PrintDiGraph(MyGraph, outfile);
	PrintDiGraph(CompGraph, outfile);

  
  // 5B find, and print to outfile, prerequisites for selected courses
  
  
  // while user selects courses to process
	  //get valid course
	  //find linear order
	  //print linear order
	  
	  //do you want to go again?
	 
	 
  //5A and 5B close files
	infile.close();
	outfile.close();


	system("PAUSE");
	return 0;
}

void OpenFiles (ifstream & infile, ofstream & outfile)
{
	char infilename[25];
	char outfilename[25];

	cout << "Enter name of data file> ";
	cin >> infilename;
	infile.open (infilename);

	cout << "Enter name of output file > ";
	cin >> outfilename;
	outfile.open (outfilename);
}
