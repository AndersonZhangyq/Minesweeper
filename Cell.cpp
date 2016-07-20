#include "stdafx.h"
#include "Cell.h"

Cell::Cell()
{
	isBlank = true;
	isBomb = to_show = isVisited = false;
	number = 0;
}

void Cell::setCell(bool blank, bool bomb)
{
	isBlank = blank;
	isBomb = bomb;
}

void Cell::setNumber(int number)
{
	this->number = number;
}

void Cell::setVisited()
{
	isVisited = true;
}
