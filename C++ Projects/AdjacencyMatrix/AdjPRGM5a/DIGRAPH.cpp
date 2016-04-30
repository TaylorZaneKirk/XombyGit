
/*---------------------------------------------------------------------------
UNIT NAME : DiGraph.cpp
PURPOSE   : Directed Graph / Adjacency List Implementation
WRITTEN FOR : Data Structures
WRITTEN BY : Taylor Kirk
DATE : 4/24/2016
---------------------------------------------------------------------------*/
#include "digraph.H"
#include <iostream>
using namespace std;


DiGraph::DiGraph (int n)
// PreCondition : Graph has not been created and 0 <= n < MaxVertices
// PostCondition : Graph Graph is created and has n vertices and no edges
// Error Condition : Error if n < 0 or n >+ MaxVertices
{
	if ((n <= MAXVERTICES) && (n >= 0))
	{
		size = n;
		
		for (int i = 0; i < size; i++)
		{
			int * matrix = new int[size];

			for (int j = 0; j < size; j++)
			{
				matrix[j] = 0;
			}

			adjList.push_back(matrix);
		}
	}
	else
	{
		cout << "ERROR: SPECIFIED SIZE: [" << n << "] IS INVALID" << endl;
		return;
	}
} //DiGraph

DiGraph::DiGraph(DiGraph & other)
// Requires : other has been created and initialized
// Ensures : other is copied to this graph
// Checks : none
{
	size = other.size;
	

	for (int i = 0; i < size; i++)
	{
		int * matrix = new int[size];

		for (int j = 0; j < size; j++)
		{
			matrix[j] = other.adjList[i][j];
		}

		adjList.push_back(matrix);
	}
}


DiGraph::~DiGraph ()
// PreCondition : Graph is created
// PostCondition : Graph is not created
// ErrorCondition : none
{
	for (int i = 0; i < size; i++)
	{
		delete adjList[i];
	}

	adjList.clear();
} //~DiGraph


void DiGraph::SwapDiGraphs ( DiGraph & other)
// PreCondition : this graph and other are created and initialized
// PostCondition : this = #other and other = #this
// ErrorCondition : none
{
	vector<int*> temp;
	int tempsize;

	temp = other.adjList;
	tempsize = other.GetNumberOfVertices();

	other.adjList = adjList;
	other.size = size;

	adjList = temp;
	size = tempsize;
	
} // swap DiGraphs


void DiGraph::AddEdge (int X, int Y)
// PreCondition : Graph is created, X and Y are distinct vertices in Graph, and
//                edge (X,Y) not in Graph
// PostCondition : Graph is the same except an edge (X,Y) now exists
// ErrorCondition : Error if X or Y is not
//                  a vertex in Graph or if X and Y are not distinct or if
//                  edge (X,Y) is already in Graph
{
	if ( (X < size) && (Y < size) && (X >= 0) && (Y >= 0) && (X != Y) && !IsEdge(X,Y) )
	{
		adjList[X][Y] = 1;
	}
	else
	{
		cout << "ERROR: VERTICES [" << X << "] AND / OR [" << Y << "] " <<
			"ARE NOT DISTINCT OR CAN NOT BE LOCATED WITHIN DIGRAPH" << endl;
		return;
	}
}  // Add Edge

void DiGraph::RemoveEdge(int X, int Y)
// PreCondition : Graph is created, X and Y are distinct vertices in Graph, and
//                edge (X,Y) not in Graph
// PostCondition : Graph is the same except an edge (X,Y) now exists
// ErrorCondition : Error if X or Y is not
//                  a vertex in Graph or if X and Y are not distinct or if
//                  edge (X,Y) is already in Graph
{
	if ((X < size) && (Y < size) && (X != Y) && (X >= 0) && (Y >= 0) && IsEdge(X, Y))
	{
		adjList[X][Y] = 0;
	}
	else
	{
		cout << "ERROR: VERTICES [" << X << "] AND / OR [" << Y << "] " <<
			"ARE NOT DISTINCT OR CAN NOT BE LOCATED WITHIN DIGRAPH" << endl;
		return;
	}
}  // Remove Edge


bool DiGraph::IsEdge (int X, int Y ) const
// PreCondition : Graph is created, X and Y are vertices in Graph
// PostCondition : Graph is unchanged, IsEdge is true if (f edge (X,Y) is in Graph
// ErrorCondition : X or Y is not a vertex in Graph
{
	if ((X < size) && (Y < size) && (X >= 0) && (Y >= 0))
	{
		return adjList[X][Y];
	}
	else
	{
		cout << "ERROR: VERTICES [" << X << "] AND / OR [" << Y << "] " <<
			"ARE NOT LOCATED WITHIN DIGRAPH" << endl;
		return 0;
	}

} //IsEdge

int DiGraph::GetNumberOfVertices ( ) const
// PreCondition : Graph is created
// PostCondition : Graph is unchanged, GetNumberofVertices is the number of
//                 vertices in Graph
// ErrorCondition : none
{
	return size;
}    // GetNumberOfVertices


