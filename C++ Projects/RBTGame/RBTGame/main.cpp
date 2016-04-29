//Name: Taylor Kirk
//Date: April 3, 2016
//Class: Advance Structures and Algorithms
//Red-Black Trees

#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include "BSTree.h"
using namespace std;

void GreetMessage(void);
/*precond:  none
postcond: Greets user to program.
checks:   none */

void ExitMessage(void);
/*precond:  none
postcond: Informs user that program will soon be terminated.
checks:   none */

void BeginGame(void);
//precond: none
//postcond: GameLoop controller. Uses input recieved from
//	the user(s) to configure the parameters of the game
//	(such as Tree depth, number of turns per player)
//checks: none

void GameLoop(BSTree & GameTree, int TreeDepth, int NextTurn,
	pair<vector<int>, vector<int>> & PlayerMoves);
//precond: GameTree is referencing a RBTree
//postcond: Will call the TakeTurn function TreeDepth number of times
//	alternating input from both players. If the input is valid, it will
//	be inserted into GameTree and into the respective player's list of moves
//	(represented as a pair of vectors PlayerMoves, where 
//		PlayerMoves.first = Player 1 and PlayerMoves.second = Player 2)
//checks: none

void TakeTurn(BSTree & GameTree, int CurrentPlayer,
	pair<vector<int>, vector<int>> & PlayerMoves);
//precond: GameTree is referencing a RBTree
//postcond: Recieves input from a player If the input is valid, it will
//	be inserted into GameTree and into the respective player's list of moves
//	(represented as a pair of vectors PlayerMoves, where 
//		PlayerMoves.first = Player 1 and PlayerMoves.second = Player 2)
//checks: If the input from the user already exists in GameTree.
//	if true: Alert the user that the input is invalid and request
//		new input from the same user
//	if false: value is inserted into GameTree, no alert

void PrintMoves(pair<vector<int>, vector<int>> & PlayerMoves);
//precond: none
//postcond: The vector of integers representing the inputs from
//	Player 1 (PlayerMoves.first) will be printed to the screen.
//	the vector of integers representing the inputs from Player 2
//	(PlayerMoves.second) will be printed to the screen.
//checks: none

void CheckLeaves(BSTree & GameTree, pair<vector<int>, vector<int>> & PlayerMoves);
//precond: none
//postcond: If GameTree is not empty, the recursive function DoCheck will be called
//	and a pair of vectors (similiar to PlayerMoves) will be propagated to contain
//	the leaf-nodes of GameTree. The values of the leaf-nodes will be put into
//	the vector of the Player that inserted that node. Once DoCheck has finished
//	the PrintMoves will be called again using the pair of vectors containing
//	the leaf nodes.
//checks: if GameTree is empty.
//	if true: Alert the user(s) that the tree is empty and that there is nothing
//		to do.
//	if false: DoCheck is called.

void DoCheck(BSTree & GameTree, pair<vector<int>, vector<int>> & PlayerMoves,
	pair<vector<int>, vector<int>> & LeafNodes);
//precond: GameTree is referencing a non-empty RBTree
//postcond:	DoCheck recursively traverses the GameTree in postfix order
//	if the current node has no children, it is determined to be a leaf
//	node. Its value is retrieved and is checked against the pair of
//	vectors PlayerMoves. If the value has a match in PlayerMoves.first,
//	it is determined that Player1 owns that leaf-node, and the value
//	will be inserted into LeafNodes.first. Otherwise, it is determined
//	that Player2 owns that leaf-node, and the value will be inserted
//	into LeafNodes.second.
//checks: none

void main()
{
	GreetMessage();
	BeginGame();
	ExitMessage();
	return;
}

void GreetMessage()
{
	cout << "The Balanced Tree Leaf Node Game" << endl << endl;
}

void ExitMessage()
{
	cout << "Thank you for using the Expression Tree Program" <<
		endl << "Terminating Program..." << endl;
	system("pause");
}

void BeginGame()
{
	BSTree GameTree;	//RBTree
	pair<vector<int>, vector<int>> PlayerMoves;	//Who played what?
	int TreeDepth = 0;
	int NextTurn;	//Who is next?
	int i; //used to properly configure TreeDepth

	//i = raw TreeDepth
	cout << "Please enter the depth of the tree desired: ";
	cin >> i;
	
	//Using i, calculate true TreeDepth
	for ( i; i > 0; i-- )
		TreeDepth += pow( 2, i - 1 );
	TreeDepth++; //+1 because has to be even number for 2 players

	NextTurn = 0; //Player1 goes first

	//Each player gets ( TreeDepth/2 ) number of turns
	cout << endl << "Each player will enter "<< (TreeDepth / 2) << " values." << endl;

	GameLoop(GameTree, TreeDepth, NextTurn, PlayerMoves);
	//Game is Finished

	//Delete the root
	GameTree.ShiftToRoot();
	GameTree.RetrieveItem(i);
	GameTree.deleteItem(i);

	//Print the list of each players inputs
	PrintMoves(PlayerMoves);

	//Determine winner
	CheckLeaves(GameTree, PlayerMoves);
}

void GameLoop(BSTree & GameTree, int TreeDepth, int NextTurn,
	pair<vector<int>, vector<int>> & PlayerMoves)
{
	//Controls whose turn it currently is
	for (int j = 0; j < TreeDepth; j++)
	{
		if (NextTurn == 0)	//Player 1 turn
		{
			TakeTurn(GameTree, 1, PlayerMoves);
			NextTurn = 1; //Player 2 next
		}
		else //Player 2 turn
		{
			TakeTurn(GameTree, 2, PlayerMoves);
			NextTurn = 0; //Player 1 next
		}
	}
}

void TakeTurn(BSTree & GameTree, int CurrentPlayer,
	pair<vector<int>, vector<int>> & PlayerMoves)
{
	int input;
	
	//get input
	cout << "Player " << CurrentPlayer << "? ";
	cin >> input;
	cout << endl;

	//If the input already existed in GameTree, get another input
	while (GameTree.findItem(input))
	{
		cout << "Please enter a value not already submitted." << endl;
		cout << "Player " << CurrentPlayer << "? ";
		cin >> input;
		cout << endl;
	}

	GameTree.Insert(input);	//Add the input to the RBTree

	//If it is player1's turn, record the input in PlayerMoves.first
	if (CurrentPlayer == 1)
	{
		auto iterator = PlayerMoves.first.end();
		PlayerMoves.first.insert(iterator, input); //Insert at end
		
	}
	//If it is player2's turn, record the input in PlayerMoves.second
	else
	{
		auto iterator = PlayerMoves.second.end();
		PlayerMoves.second.insert(iterator, input); //Insert at end
	}
}

void PrintMoves(pair<vector<int>, vector<int>> & PlayerMoves)
{
	cout << "Player 1 Moves: ";
	for (int i = 0; i < PlayerMoves.first.size(); i++)
		cout << PlayerMoves.first.at(i) << " ";
	cout << endl;

	cout << "Player 2 Moves: ";
	for (int i = 0; i < PlayerMoves.second.size(); i++)
		cout << PlayerMoves.second.at(i) << " ";
	cout << endl << endl;
}

void CheckLeaves(BSTree & GameTree, pair<vector<int>, vector<int>> & PlayerMoves)
{
	pair<vector<int>, vector<int>> LeafNodes;

	GameTree.ShiftToRoot();

	if (GameTree.IsEmpty())
		cout << "Tree is empty" << endl;
	else
		DoCheck(GameTree, PlayerMoves, LeafNodes);

	PrintMoves(LeafNodes);

	if (LeafNodes.first.size() > LeafNodes.second.size())	//Player 1 has more Leaf-Nodes
		cout << "Player 1 Wins!!" << endl;
	else if (LeafNodes.first.size() < LeafNodes.second.size())	//Player 2 has more Leaf-Nodes
		cout << "Player 2 Wins!!" << endl;
	else	//Both players have same amount of Leaf-Nodes
		cout << "Tie Game..." << endl;
}

void DoCheck(BSTree & GameTree, pair<vector<int>, vector<int>> & PlayerMoves,
	pair<vector<int>, vector<int>> & LeafNodes)
{
	
	int data;

	//Traverse-Left
	if (GameTree.HasLeftChild())
	{
		GameTree.ShiftLeft();
		DoCheck(GameTree, PlayerMoves, LeafNodes);
		GameTree.ShiftUp();
	}
	
	//Traverse-Right
	if (GameTree.HasRightChild())
	{
		GameTree.ShiftRight();
		DoCheck(GameTree, PlayerMoves, LeafNodes);
		GameTree.ShiftUp();
	}

	//If current node is a leaf
	if (GameTree.HasNoChildren())
	{
		GameTree.RetrieveItem(data);
		bool found = false;

		//Check to see if Player1 inserted this node
		for (int i = 0; i < PlayerMoves.first.size(); i++)
		{
			if (data == PlayerMoves.first.at(i))
				found = true;
		}

		//If found is true, Player1 inserted this node,
		//	so record the value in LeafNodes.first
		if (found == true)
		{
			auto leaf_iterator = LeafNodes.first.end();
			LeafNodes.first.insert(leaf_iterator, data);
		}
		//otherwise, Player2 inserted this node,
		//	so record the value in LeafNodes.second
		else
		{
			auto leaf_iterator = LeafNodes.second.end();
			LeafNodes.second.insert(leaf_iterator, data);
		}
	}
}