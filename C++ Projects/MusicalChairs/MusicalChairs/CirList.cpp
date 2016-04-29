#include "CirList.h"

using namespace std;

CirList::CirList():Head(NULL)
{
	//Prep output file for writing
	output.open("output.txt");
}

CirList::~CirList()
{
	if (Head != NULL)
	{
		node *temp = Head;

		//Delete each node in CirList
		while (temp->next != Head)
		{
			node *remove = temp;
			temp = temp->next;
			delete(remove);
		}

		delete temp;
		Head = NULL;
		Cursor = NULL;
	}

	output.close();
}

void CirList::insertItemEnd(string Name)
{
	node *newItem = new node(Name);	//create new node containing Name
	node *temp = Head;

	//If Head is Null, create a new list
	if (Head == NULL)
	{
		newItem->next = newItem; //new node points to itself
		Head = newItem;	//designate Head as new node
		Cursor = Head;	//Point Cursor at Head
		return;
	}

	//Find last node in CirList
	while (temp->next != Head)
	{
		temp = temp->next;
	}

	temp->next = newItem;	//Make last item point to new node
	newItem->next = Head;	//Make new node point to Head
}

void CirList::insertItemFirst(string Name)
{
	node *newItem = new node(Name); //create new node containing Name
	node *temp = Head;

	//If Head is NULL, create a new list
	if (Head == NULL)
	{
		newItem->next = newItem; //new node points to itself
		Head = newItem; //Set Head to point to new node
		Cursor = Head; //set Cursor to new Head
		return;
	}

	//Find last node in CirList
	while (temp->next != Head)
	{
		temp = temp->next;
	}

	temp->next = newItem;	//Set last node to point to new node
	newItem->next = Head;	//New node points to Head
	Head = newItem;		//Designate the new node as Head
}

void CirList::insertItemHere(string Name)
{
	//crete new node
	node *newItem = new node(Name);

	//if Head is NULL, then start a new List
	if (Head == NULL)
	{
		newItem->next = newItem;
		Head = newItem;
		Cursor = Head;
		return;
	}

	node *temp = Head;

	//Get node that will point to new node
	while (temp->next != Cursor)
	{
		temp = temp->next;
	}

	//If Cursor was at the end, place new node at the
	//	front and redefine Head to point to the new node
	if (temp->next == Head)
		Head = newItem;

	//Attach new node to the CirList
	newItem->next = temp->next;	//point to next node
	temp->next = newItem;	//Previous node point to new node
	Cursor = newItem->next;	//Set the Cursor to the next node
}

bool CirList::isEmpty()
{
	if (Head == NULL)	//Head is NULL, thus no list
		return true;

	return false;
}

string CirList::getCurrentItem()
{
	//Return contents of Cursor
	if (Cursor != NULL)
		return Cursor->name;

	return "";
}

void CirList::removeItem(string Name)
{
	node * temp = Head;
	node * prev = NULL;

	//Iterate through CirList until the end of the
	//	list or when the Node containing the string
	//	Name is found
	while (temp->next != Head && temp->name != Name)
	{
		prev = temp;
		temp = temp->next;
	}

	if (temp->name == Name)	//node containing name found
	{
		//If Cursor was pointing here,
		// make it point to the next node
		if (temp == Cursor)	
			Cursor = Cursor->next;

		//If Head was pointing here, make the node immediately
		//	following Head be redefined has `Head make the last node
		//	in the list point to `Head.
		if (temp == Head)
		{
			while (temp->next != Head)
			{
				temp = temp->next;
			}

			temp->next = Head->next;
			delete Head;
			Head = temp->next;
		}
		//Remove the node and attach the previous node to the next node
		else
		{
			prev->next = temp->next; //Reconnect list
			delete temp;
		}
	}
}

int CirList::length()
{
	node *temp = Head;
	int numItems = 1;

	//counts number of nodes in CirList
	while (temp->next != Head)
	{
		numItems++;
		temp = temp->next;
	}

	return numItems;
}

int CirList::findItem(string Name)
{
	node *temp = Head;
	int numItems = 0;

	if (temp->next == Head)
		return 1;

	while (temp->next != Head)
	{
		numItems++;

		if (temp->name == Name)
			return numItems; //return integer position of the node
							//	containing Name in CirList

		temp = temp->next;
	}

	return -1; //return this if item not in CirList
}

void CirList::removeItemHere()
{
	//remove the node being pointed at by Cursor
	string Name = Cursor->name;
	removeItem(Name);
}

void CirList::changeCurrentItem(string difName)
{
	//Change the contents of the node being pointed
	//	at by Cursor to be difName
	if (Cursor != NULL)
		Cursor->name = difName;
}

void CirList::clearList()
{
	node *temp = Head;

	//iterate through CirList and delete all nodes
	while (temp->next != Head)
	{
		node *remove = temp;
		temp = temp->next;
		delete(remove);
	}

	delete(temp);
	Head = NULL;
}

void CirList::advanceCursor()
{
	//Set Cursor to point to the
	//	next item in CirList
	if (Cursor != NULL)
		Cursor = Cursor->next;
}

void CirList::Permute(int iterations)
{
	string Winner;

	if (!isEmpty())	//Ensure there are items
	{
		printList();
		output << "J-P permutation removing every " << iterations << "th:" << endl;

		//remove every ith node where i = interations
		while (length() != 1)
		{
			for (int i = 0; i < iterations - 1; i++)
			{
				advanceCursor();
			}
			output << getCurrentItem() << ", ";
			removeItemHere();
		}

		//Winner will equal the contents of the last node
		Winner = getCurrentItem();
		output << getCurrentItem() << endl;
		clearList();	//Clear the list for next run

		//specify winner
		output << endl << Winner << " WINS!" << endl << endl;
	}
}

void CirList::printList()
{
	node * temp = Head;
	string name;
	int count = 0;
	
	//Write the number of nodes in CirList to output file
	output << "List has " << length() << " names:" << endl;

	//Write ten names per line
	while (temp->next != Head)
	{
		name = temp->name;
		output << name.data() << ", ";
		temp = temp->next;

		if (count == 10)
			output << endl;
	}
	
	name = temp->name;	//get last node
	output << name.data() << endl << endl;
}
