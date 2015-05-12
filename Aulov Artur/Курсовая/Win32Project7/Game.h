#pragma once
#include <iostream>

class Game
{
	bool selectfield[11][10];
	int* field[11][10];
	int tmp_i, tmp_j;
	bool buttomselect = true;
	bool reset = false;
public:
	int gettmpi(){ return tmp_i; }
	int gettmpj(){ return tmp_j; }
	void FallColone(int j)
	{
		for (int i = 10; i > 0; i--)
		{
			if (*field[i][j] == 0)
			{
				int i2=i;
				while (*field[i2][j]==0&&i2>0)
				{
					i2--;
				}
				if (*field[i2][j] != 0)
				{
					*field[i][j] = *field[i2][j];
					*field[i2][j] = 0; 
				}
			}
		}
	}

	Game()
	{
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				
				field[i][j] = new int(0);
				if (i == 0)
				{
					*field[i][j] = 6;
				}
				else
				{
					*field[i][j] = (rand() % 5) + 1;

					if (j >= 2)
					{
						if (*field[i][j - 1] == *field[i][j] && *field[i][j - 2] == *field[i][j])
						{
							if (*field[i][j] == 5) *field[i][j] = 1;
							else *field[i][j] = *field[i][j] + 1;
						}
					}
					if (i >= 3)
					{
						if (*field[i - 1][j] == *field[i][j] && *field[i - 2][j] == *field[i][j])
						{
							if (*field[i][j] == 5) *field[i][j] = 1;
							else *field[i][j] = *field[i][j] + 1;
						}
					}
				}
			}
		}
	}

	int Get(int i, int j)
	{
		return *field[i][j];
	}
	
	void ClearSelect()
	{
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				selectfield[i][j] = 0;
			}
		}
	}

	bool isSWAP(int i, int j)
	{
		if (field[i][j] == field[tmp_i][tmp_j + 1] ||
			field[i][j] == field[tmp_i][tmp_j - 1] ||
			field[i][j] == field[tmp_i + 1][tmp_j] ||
			field[i][j] == field[tmp_i - 1][tmp_j]) return true;
		else return false;
	}

	void PointTo(int i, int j)
	{
		if (i > 0 && *field[i][j] != 6 && *field[i][j] != 0)
		{
			ClearSelect();
			int type = Get(i, j);
			if (buttomselect == true)
			{
				tmp_i = i;
				tmp_j = j;
				buttomselect = false;
			}
			if (buttomselect != true)
			{
				if (isSWAP(i, j))
				{
					*field[i][j] = Get(tmp_i, tmp_j);
					*field[tmp_i][tmp_j] = type;
					buttomselect = true;
				}
				else
				{
					tmp_i = i;
					tmp_j = j;
					buttomselect = false;
				}
			}
			while (select3match())
			{
				for (int i = 0; i < 11; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						if (selectfield[i][j] == 1)
						{
							*field[i][j] = 0;
						}
					}
				}
				for (int j = 0; j < 10; j++)
					FallColone(j);
			}
		}
	}

	bool select3match()
	{
		reset = false;
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (*field[i][j] != 6 && *field[i][j] != 0)
				{
					if (j <= 7)
					{
						if (*field[i][j] == *field[i][j + 1] && *field[i][j] == *field[i][j + 2])
						{
							selectfield[i][j] = selectfield[i][j+1] = selectfield[i][j+2] = 1;
							reset = true;
						}
					}
					if (i <= 8)
					{
						if (*field[i][j] == *field[i + 1][j] && *field[i][j] == *field[i + 2][j])
						{
							selectfield[i][j] = selectfield[i + 1][j] = selectfield[i + 2][j] = 1;
							reset = true;
						}
					}
				}
			}
		}

		return reset;
		/*for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (*field[i][j] != 6 && *field[i][j] != 0)
				{
					if (i <= 8)
					{
						if (*field[i][j] == *field[i+1][j] && *field[i][j] == *field[i+2][j])
						{
							selectfield[i][j] = selectfield[i+1][j] = selectfield[i+2][j] = 1;
							return true;
						}
					}
				}
			}
		}*/

		/*int col=0;
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
		if (x < 9)
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
		return col;*/
	}

	~Game()
	{}
};

