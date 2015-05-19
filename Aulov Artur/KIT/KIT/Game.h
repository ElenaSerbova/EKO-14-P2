#pragma once
#include "Library.h"

class Game
{
	bool selectfield[11][10];
	int* field[11][10];
	bool second_select = false;
	bool first_select = false;
	bool reset = false;

	int score = 0, coins = 0;
	int firsti, firstj, secondi, secondj;
public:
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

	bool getreset(){ return reset; }
	bool getfs(){ return first_select; }
	bool getss(){ return second_select; }
	bool getselect(int i, int j) { return selectfield[i][j]; }
	int Get(int i, int j){ return *field[i][j]; }

	void setbs(int i, int j){ firsti = i; firstj = j; first_select = true; second_select = false; }
	void setselect(int i, int j, bool select){ selectfield[i][j] = select; }
	void Set(int i, int j, int type){ *field[i][j] = type; }

	int score_()
	{
		return score;
	}
	int coins_()
	{
		return coins;
	}

	void unselect(){ second_select = 0; first_select = 0; }

	void destroy(int i, int j)
	{
		if (*field[i][j] != 6 && *field[i][j] != 0)
			selectfield[i][j] = 1;
	}
	void destroyj(int i)
	{
		for (int j = 0; j < 10; j++)
		{
			if (*field[i][j] != 6 && *field[i][j] != 0)
				selectfield[i][j] = 1;
		}
	}
	void destroyi(int j)
	{
		for (int i = 0; i < 11; i++)
		{
			if (*field[i][j] != 6 && *field[i][j] != 0)
				selectfield[i][j] = 1;
		}
	}

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

	void fallcolone(int j)
	{
		for (int i = 10; i > 0; i--)
		{
			if (*field[i][j] == 0)
			{
				int i2 = i;
				while (*field[i2][j] == 0 && i2 > 0)
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

	void clearselect()
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
	void swap()
	{
		int type = Get(firsti, firstj);
		*field[firsti][firstj] = *field[secondi][secondj];
		*field[secondi][secondj] = type;
	}

	void click(int i, int j)
	{
		if (Get(i, j) == 0 || Get(i, j) == 6)
		{
			unselect();
			return;
		}
		if (!first_select)
		{
			firsti = i;
			firstj = j;
			first_select = true;
		}
		else
		{
			secondi = i;
			secondj = j;
			first_select = false;
			second_select = true;
		}
	}

	void delete3match()
	{
		int co = 0;
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (*field[i][j] != 6 && *field[i][j] != 0)
				{
					if (selectfield[i][j] == 1)
					{
						co++;
						*field[i][j] = 0;
						score += 20;
					}
				}
			}
		}
		if (co == 3) coins += 2;
		else if (co == 4) coins += 4;
		else coins += 6;
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
	}
};

