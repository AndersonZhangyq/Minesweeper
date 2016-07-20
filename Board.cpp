#include "stdafx.h"
#include "Board.h"
#include <iostream>
#include <time.h>
#include <string>
#include <sstream>

using namespace std;

Board::Board(int in_size, int number_of_bomb):size(in_size),visited(0),mines(number_of_bomb) {
	bomb = new Cell*[size + 2];
	for (int i = 0; i < size + 2; i++)
		bomb[i] = new Cell[size + 2];
	for (int k = 0; k < size + 2; k++)
		for (int j = 0; j < size + 2; j++)
			bomb[k][j] = Cell();
	Generate(number_of_bomb);
	SetAllCell();
}

void Board::Generate(int number_of_bomb)
{
	srand((unsigned)time(NULL));
	int i = 0;
	while (i < number_of_bomb)
	{
		int x = rand() % size + 1, y = rand() % size + 1;
		if (bomb[x][y].isBomb)
			continue;
		else
			bomb[x][y].setCell(false, true);
		i++;
	}
}

void Board::SetAllCell()
{
	int count;
	for (int x = 1; x < size + 1; x++)
	{
		for (int y = 1; y < size + 1; y++)
		{
			count = 0;
			if (bomb[x][y].isBomb)
				continue;
			if (bomb[x][y + 1].isBomb) //right
				count++;
			if (bomb[x][y - 1].isBomb) // left
				count++;
			if (bomb[x - 1][y + 1].isBomb) // right_up
				count++;
			if (bomb[x - 1][y].isBomb) // up
				count++;
			if (bomb[x - 1][y - 1].isBomb) // left_up
				count++;
			if (bomb[x + 1][y + 1].isBomb) // right_down
				count++;
			if (bomb[x + 1][y].isBomb) // down
				count++;
			if (bomb[x + 1][y - 1].isBomb) // left_down
				count++;
			bomb[x][y].setNumber(count);
		}
	}
}

Result Board::Play(int x, int y)
{
	bool isEnd = false;
	if (bomb[x][y].isBomb)
		return gameover;
	else
		Next(x, y, isEnd);
	return Check();
}

void Board::Next(int x, int y, bool & isEnd)
{
	if (x < 1 || y < 1 || x > size || y > size || bomb[x][y].isBomb)
	{
		isEnd = true;
		return;
	}
	if (bomb[x][y].isVisited)
	{
		return;
	}
	visited++;
	bomb[x][y].setVisited();
	if (bomb[x][y].number == 0)
	{		
		Next(x, y + 1, isEnd); // right
		Next(x, y - 1, isEnd); // left
		Next(x + 1, y, isEnd); // down
		Next(x + 1, y + 1, isEnd); // right_down
		Next(x + 1, y - 1, isEnd); // left_down
		Next(x - 1, y, isEnd); // up
		Next(x - 1, y + 1, isEnd); // right_ up
		Next(x - 1, y - 1, isEnd); // left_up
		if (isEnd)
		{
			bomb[x][y].to_show = true;
			isEnd = false;
		}
	}
	else
	{
		if (!bomb[x][y].isBomb)
			bomb[x][y].to_show = true;
	}
	return;
}

void Board::Print() const
{
	string coordinate = Coordinate();
	cout << "   " << coordinate << endl;
	for (int i = 1; i < size + 1; i++) {
		cout << " " << i << " ";
		for (int j = 1; j < size + 1; j++) {
			cout << " ";
			if (bomb[i][j].to_show)
			{
				if (!bomb[i][j].isBomb)
				{
					if (bomb[i][j].number == 0)
						cout << '#';
					else
						cout << bomb[i][j].number;
				}
				/*else
					cout << "X";*/
			}
			else if (bomb[i][j].number == 0 && bomb[i][j].isVisited)
				cout << '#';
			else
				cout << "%";
			cout << " ";
		}
		cout << endl;
	}
}

void Board::PrintFinal() const
{
	string coordinate = Coordinate();
	cout << visited << " visited! \n";
	cout << "   " << coordinate << endl;
	for (int i = 1; i < size + 1; i++) {
		cout << " " << i << " ";
		for (int j = 1; j < size + 1; j++) {
			cout << " ";
			if (bomb[i][j].isBomb)
				cout << "X";
			else
			{
				if (bomb[i][j].to_show)
				{
					if (bomb[i][j].number == 0)
						cout << '#';
					else
						cout << bomb[i][j].number;
				}
				else if (bomb[i][j].number == 0 && bomb[i][j].isVisited)
					cout << '#';
				else
					cout << "%";
			}

			cout << " ";
		}
		cout << endl;
	}
}

Result Board::Check()
{
	return (size * size - visited) == mines ? win : _continue;
}

string Board::Coordinate() const
{
	string tmp = "", coordinate;
	stringstream change;
	for (int i = 1; i <= size; i++)
	{
		/* int to string */
		change.clear();
		change << i;
		change >> tmp;
		coordinate += " " + tmp + " ";
	}
	return coordinate;
}
