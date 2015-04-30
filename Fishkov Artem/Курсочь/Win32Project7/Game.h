#pragma once
#include <iostream>
class Game
{
	bool selectfield[10][20];
	int* field[10][20];
public:
	void fall()
	{
		for (int i = 10; i > 0; i--)
		{
			for (int j = 20; j >0; j--)
			{
				if (field[i - 1][j] == 0)
				{
					for (int i2 = i - 2; i2 > 0; i2--)
					{

					}
				}
			}
		}

	}
	Game()
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				field[i][j] = new int(0);
				*field[i][j] = (rand() % 4) + 1;
			}
		}
	}
	int Get(int x, int y)
	{
		return *field[y][x];
	}
	
	void clerselect()
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				selectfield[i][j] = 0;
			}
		}
	}
	void PointTo(int x, int y)
	{
			clerselect();
			int type = Get(x, y);
			NextSqr(x, y, type);
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 20; j++)
				{
					if (selectfield[i][j] == 1)
					{
						*field[i][j] = 0;
					}
				}
			}
	}
	int NextSqr(int x, int y, int type)
	{
		int col=0;
		if (Get(x, y) == type)
		{
			selectfield[y][x] = 1;
			col++;
			if (x > 0)
			{
				if (selectfield[y][x-1]!=1)
				col+=NextSqr(x - 1, y, type);
			}
			if (y > 0)
			{
				if (selectfield[y-1][x] != 1)
				col += NextSqr(x, y-1, type);
			}
			if (x < 19)
			{
				if (selectfield[y][x + 1] != 1)
				col += NextSqr(x + 1, y, type);
			}
			if (y < 9)
			{
				if (selectfield[y+1][x] != 1)
				col += NextSqr(x, y+1, type);
			}
		}
		return col;


	}
	~Game()
	{}
};

