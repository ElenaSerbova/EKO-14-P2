#pragma once
#include <iostream>

class Game
{
	bool selectfield[11][10];
	int* field[11][10];
	int tmp_i, tmp_j, tmp_i2, tmp_j2;
	bool secondselect = false;
	bool buttonselect = false;
	bool reset = false;
	int firsti, firstj, secondi, secondj;
public:
	bool getreset(){ return reset; }
	bool getbs(){ return buttonselect; }
	bool getss(){ return secondselect; }
	void setbs(int i, int j){ firsti = i; firstj = j; buttonselect = true; secondselect = false; }
	void unselect(){ secondselect = 0; buttonselect = 0; }
	int gettmpi(){ return tmp_i; }
	int gettmpj(){ return tmp_j; }
	void setselect(int i, int j, bool select){ selectfield[i][j] = select; }
	bool getselect(int i, int j) { return selectfield[i][j]; }

	void destroyj(int i) 
	{
		for (int j = 0; j < 10; j++)
		{
			if (*field[i][j] != 6 && *field[i][j] != 0)
			*field[i][j] = 0;
		}
	}

	void destroyi(int j)
	{
		for (int i = 0; i < 11; i++)
		{
			if (*field[i][j] != 6 && *field[i][j] != 0)
			*field[i][j] = 0;
		}
	}

	int Get(int i, int j){ return *field[i][j]; }

	void Set(int i, int j, int type){ *field[i][j] = type; }

	void stone_on()
	{
		for (int j = 0; j < 10; j++)
		{
			if (*field[10][j] == 6) *field[10][j] = 0;
		}
	}

	int count_stone()
	{
		int count = 0;
		for (int j = 0; j < 10; j++)
		{
			if (*field[10][j] == 0) count++;
		}
		return count;
	}

	void generatefield()
	{
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 10; j++)
			{
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

	void FallColone(int j)
	{
		for (int i = 10; i > 0; i--)
		{
			if (*field[i][j] == 0)
			{
				int i2=i;
				while (*field[i2][j] == 0 && i2 > 0)
				{
					i2--;
				}
				if (*field[i2][j] != 0 )
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

	bool isswap()
	{
		if (field[firsti][firstj] == field[secondi][secondj + 1] ||
			field[firsti][firstj] == field[secondi][secondj - 1] ||
			field[firsti][firstj] == field[secondi + 1][secondj] ||
			field[firsti][firstj] == field[secondi - 1][secondj]) return true;
		else return false;
	}

	void Click(int i, int j)
	{
		if (Get(i, j) == 0 || Get(i, j) == 6)
		{
			unselect();
			return;
		}
		if (!buttonselect)
		{
			firsti = i;
			firstj = j;
			buttonselect = true;
		}
		else
		{
			secondi = i;
			secondj = j;
			buttonselect = false;
			secondselect = true;
		}
	}

	void swap()
	{
		int type = Get(firsti, firstj);
		*field[firsti][firstj] = *field[secondi][secondj];
		*field[secondi][secondj] = type;
	}

	void PointTo(int i, int j)
	{
		if (i > 0 && *field[i][j] != 6 && *field[i][j] != 0)
		{
			ClearSelect();
			if (buttonselect == true)
			{
				tmp_i = i;
				tmp_j = j;
				buttonselect = false;
			}
			if (buttonselect != true)
			{
				if (isswap())
				{
					int type = Get(i, j);
					*field[i][j] = Get(tmp_i, tmp_j);
					*field[tmp_i][tmp_j] = type;
					buttonselect = true;
					tmp_i2 = i;
					tmp_j2 = j;
				}
				else
				{
					tmp_i = i;
					tmp_j = j;
					buttonselect = false;
				}
			}
		}
	}

	void delete3match()
	{
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (*field[i][j] != 6 && *field[i][j] != 0)
				{
					if (selectfield[i][j] == 1)
					{
						*field[i][j] = 0;
					}
				}
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
							if (*field[i][j] != 6 && *field[i][j] != 0)
							{
								selectfield[i][j] = selectfield[i][j + 1] = selectfield[i][j + 2] = 1;
								reset = true;
							}
						}
					}
					if (i <= 8)
					{
						if (*field[i][j] == *field[i + 1][j] && *field[i][j] == *field[i + 2][j])
						{
							if (*field[i][j] != 6 && *field[i][j] != 0)
							{
								selectfield[i][j] = selectfield[i + 1][j] = selectfield[i + 2][j] = 1;
								reset = true;
							}
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

