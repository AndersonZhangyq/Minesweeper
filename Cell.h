#pragma once
#include <iostream>

using namespace std;

struct Cell
{
	Cell();
	void setCell(bool blank, bool bomb);
	void setNumber(int number);
	void setVisited();

	bool isBlank;
	bool isBomb;
	bool to_show;
	bool isVisited;
	int number;
};

/*ostream & operator << (ostream & out, const Cell & in) {
	if (in.isBomb)
		out << "X";
	else
		out << in.number;
	return out;
}*/