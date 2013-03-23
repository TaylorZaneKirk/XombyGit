#pragma once
#include <fstream>
using namespace std;

class MagicSquare
{
private:

public:
	MagicSquare(void);
	void Form(int**&, int);
	void Load(int, int, ifstream);
	~MagicSquare(void);
};

