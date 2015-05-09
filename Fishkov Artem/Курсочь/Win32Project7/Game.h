#pragma once
#include <iostream>
class creature
{
public:
	int hp;
	int attack;
	int defence;
	creature*enemy;
	TCHAR name[30];
	void SetEnemy(creature*enemy)
	{
		this->enemy = enemy;	
	}
	creature()
	{
		hp=0;
		attack=0;
		defence=0;
		_tcscpy_s(this->name, L"NONAME");
	}
	creature(int hp,int attack,int defence,TCHAR*name)
	{
		this->hp = hp;
		this->attack = attack;
		this->defence = defence;
		_tcscpy_s(this->name, name);	
	}
	virtual void DoStep() = 0;
};
class Monstr :public creature
{
public:
	int timeng;
	int curentTime;
	Monstr()
	{
	}
	Monstr(int hp, int attack, int defence,int timeng, TCHAR*name) : creature(hp, attack, defence, name)
	{
		this->timeng = timeng;
		curentTime = 0;
	}
	void DoStep()
	{
	}
};
class Hero :public creature
{
public:
	int concentration;
	int shildtime;
	int shildcurtime;
	Hero(int hp, int attack, int defence, TCHAR*name) : creature(hp, attack, defence, name)
	{

	}
	Hero()
	{
	}
	
	void DoStep()
	{

	}
};


class Game
{
	Hero hero;
	Monstr monstr;
	bool selectfield[10][20];
	int* field[10][20];
public:
	void SlideStrings()
	{
		for (int j = 19; j > 1; j--)
		{
			if (*field[9][j] == 0)
			{
				for (int i = 0; i < 10; i++)
					for (int j2 = j-1; j2 > -1; j2--)
					{
					*field[i][j2 + 1] = *field[i][j2];
						* field[i][j2] = 0;

					}
			}
		}
	}
	void FallColone(int x)
	{
		for (int i = 9; i > 0; i--)
		{
			if (*field[i][x] == 0)
			{
				int i2=i;
				while (*field[i2][x]==0&&i2>0)
				{
					i2--;
				}
				if (*field[i2][x] != 0)
				{
					*field[i][x] = *field[i2][x];
					*field[i2][x] = 0; 
				}
			}
		}
	}
	Game() :hero(10, 0, 0,L"Nigga"), monstr(5,2,1,3,L"Spady")
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
			for (int i = 0; i < 20;i++)
				FallColone(i);
			for (int i = 0; i < 10; i++)
				SlideStrings();
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

