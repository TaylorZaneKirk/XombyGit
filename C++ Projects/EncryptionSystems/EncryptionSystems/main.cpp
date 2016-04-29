#include <iostream>
#include <queue>

using namespace std;

void main(void){
	char String[] = "I CANNOT SOLVE THIS IN LESS THAN A CHILIAD";
	queue<int> Modified;
	int ModChar;
	for each(char i in String){
		switch (i){
		case 'A':
			ModChar = 0;
			break;
		case 'C':
			ModChar = 2;
			break;
		case 'D':
			ModChar = 3;
			break;
		case 'E':
			ModChar = 4;
			break;
		case 'H':
			ModChar = 7;
			break;
		case 'I':
			ModChar = 8;
			break;
		case 'L':
			ModChar = 11;
			break;
		case 'N':
			ModChar = 13;
			break;
		case 'O':
			ModChar = 14;
			break;
		case 'S':
			ModChar = 18;
			break;
		case 'T':
			ModChar = 19;
			break;
		case 'V':
			ModChar = 21;
			break;
		case ' ':
			ModChar = 26;
			break;
		default:
			cout << "Unexpected Letter" << endl;
		}
		ModChar = (ModChar + 7) % 27;
		Modified.push(ModChar);
	}

	while (Modified.empty() == false){
		cout << Modified.front() << endl;
		Modified.pop();
	}
}