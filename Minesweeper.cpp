// Minesweeper.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Board.h"

using namespace std;

int main()
{
	int size, number_of_mine;
	cout << "Enter the size of the board: ";
	cin >> size;
	cout << "Enter the number of mine: ";
	cin >> number_of_mine;
	Board SaoLei(size, number_of_mine);
	SaoLei.Print();
	int x, y;
	while (1)
	{
		system("cls");
		SaoLei.Print();
		do {
			cout << "x = ";
			cin >> x;
			cout << "y = ";
			cin >> y;
			if (x > 0 && x <= size && y > 0 && y <= size)
				break;
			cout << "The input is invalid!" << endl;
		} while (1);
		Result state = SaoLei.Play(y, x);
		if (state == gameover)
		{
			cout << "Game Over!" << endl;
			SaoLei.PrintFinal();
			break;
		}
		else if (state == win)
		{
			cout << "Congratulation! You win!" << endl;
			break;
		}
	}
	system("pause");
	return 0;
}