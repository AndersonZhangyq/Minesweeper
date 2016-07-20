#pragma once
#include "Cell.h"

enum Result{win, gameover, _continue};

class Board
{
public:
	Board(int size, int number_of_bomb);
	void Generate(int number_of_bomb);
	void SetAllCell();

	Result Play(int x, int y);
	void Next(int x, int y, bool & isEnd);

	void Print() const;
	void PrintFinal() const;

private:
	Result Check();
	string Coordinate() const;
	int mines;
	int size;
	int visited;
	Cell ** bomb;
};