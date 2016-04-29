
/*
UNIT NAME : EnhDiGraph.cpp
PURPOSE   : Enhanced DiGraph Operations Specifications
WRITTEN FOR : CS 3013
WRITTEN BY : Taylor Kirk
DATE : 4/24/2016
*/
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "enhdig.h"
using namespace std;

void ReadDiGraph(DiGraph & G, ifstream & InFile, ofstream & OutFile)
// PreCondition : G is created.  The first line of InFile contains the
//                number of vertices in the graph,, the following lines
//                are the edges (vertex pairs) of the Graph
// PostCondition : Graph G is the DiGraph specified by InFile
// ErrorCondition : Error if the size is invalid, or if there are invalid edges
{
	int GSize;
	int X;
	int Y;
	DiGraph * temp;

	// read size of digraph to be created from infile */
	InFile >> GSize;
	// invalid graph size */
	if (GSize > MAXVERTICES)
	{
		cout << "ERROR: INVALID SIZE" << endl;
		return;
	}
	else
	{
		//valid graph size
		temp = new DiGraph(GSize);

		// while there are vertices listed in InFile */
		while (!InFile.eof())
		{
			// get a pair of vertices from InFile */
			InFile >> X >> Y;
			// vertices not in digraph */
			if (X >= GSize || Y >= GSize)
			{
				cout << "ERROR: VERTICES [" << X << "] AND / OR [" << Y << "] " <<
					"ARE NOT LOCATED WITHIN DIGRAPH" << endl;
				
			}
			// vertices not distinct */
			else if (X == Y)
			{
				cout << "ERROR: VERTICES [" << X << "] AND [" << Y << "] " <<
					"ARE NOT DISTINCT" << endl;
			
			}
			else
			// valid edge; add to G */
				temp->AddEdge(X, Y);
		}

		G.SwapDiGraphs(*temp);
	}     
}// read digraph */


void PrintDiGraph ( DiGraph & G, ofstream & OutFile)
// PreCondition  : G is created
// PostCondition : outfile"s first line is the size of the graph, the
//                 succeeding lines contain a list of vertices and the
//                 vertices to which they are adjacent
// ErrorCondition : none
{
	int size = G.GetNumberOfVertices();

	OutFile << "There are " << size << " vertices in the Graph." << endl;
	OutFile << "The edges are as follows:" << endl;
	for (int i = 0; i < size; i++)
	{
		OutFile << "\t From vertex " << i << " to: ";
		for (int j = 0; j < size; j++)
		{
			if (G.IsEdge(i, j))
			{
				OutFile << j << " ";
			}
		}
		OutFile << endl;
		
	}
	OutFile << endl << endl;
}     // print digraph */


void Complement (DiGraph & G, DiGraph & GComp)
// PreCondition : G and GComp are created
// PostCondition : G = #G, GComp is the same size as G and has edges between
//                 exactly those pairs of vertices not directly
//                 connected in G
// ErrorCondition : none
{
	int compsize = G.GetNumberOfVertices();
	DiGraph temp(compsize);

  // clear GComp by creating a temp graph of correct size and no edges and swapping
	GComp.SwapDiGraphs(temp);


  // for (each pair of vertices (i,j) in GComp,if (there is no edge
  // between those vertices in G, add an edge (i,j) in GComp
	for (int i = 0; i < compsize; i++)
	{
		for (int j = 0; j < compsize; j++)
		{
			if (i != j && !(G.IsEdge(i, j)))
				GComp.AddEdge(i, j);
		}

	}
	  //if i == j  not try to complement! (thanks, Randy!) 
	  
}     // complement 

void DoLinearOrder(DiGraph & G, int Course, Stack & PreReq, ControlData & Visited)
// requires : G is created, PreReq is created, Course is a valid course
// ensures : G is unchanged; PreReq contains the sequence of courses that
//           have to be taken before Course, with Course itself at the top
// checks : Course is a valid course
{
  int i;

  // start at vertex <course>, mark vertex <course> as visited
	
	 // for (each vertex in G which has not already been visited
	 
	  //if (there is an edge between <course> and <i>, recursively
	  // call  LinearOrder for (vertex <i> */
		
				// with each return (backtrack) from a call to  LinearOrder,
				// add the vertex (for (which that call was made) to PreReq *
 
  }      //  LinearOrder 

void FindLinearOrder (DiGraph & G, int Course, Stack & Prerequisites)
// requires : G is created, Prerequisites is created, Course is a valid course
// ensures : G = #G; Prerequisites contains the sequence of courses that have
//           to be taken before Course, with Course itself at the top
// checks : Course is a valid course
{
	ControlData Visited;
	int i;

	// Find Linear Order */
	// initialize array Visited */
	
	// clear stack Prerequisites */
	

	// checkif (Course is valid course number */
	
	//else do it
	  
}  // FindLinearOrder

void PrintLinearOrder (ofstream & OutFile, Stack & PreReq)
// requires : OutFile has been opened for (output; PreReq is created,
//            and its top item is the "target course" for (which the rest
//            of the items on the stack are prerequisites
// checks : none
{

  
}


