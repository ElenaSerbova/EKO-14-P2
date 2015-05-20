#pragma once
#include <iostream>
#include "Monstrs.h"

class Game
{

	
	Monstr Lvls[10];
	bool selectfield[10][20];
	int* field[10][20];
	int items[2][10];
public:
	int lvl;
	int rage;
	bool fullgameover;
	int continues;
	bool win;
	bool gameover;
	Hero hero;
	Monstr monstr;
	void RestartField()
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				field[i][j] = new int(0);
				*field[i][j] = (rand() % 5) + 1;

			}
		}
	}
	void SetMonsters()
	{
		Lvls[0] = Monstr(10,2,1,0,L"Rat");
		Lvls[1] = Monstr(20, 5, 3, 2, L"Spider");
		Lvls[2] = Monstr(50, 20, 1, 8, L"Golem");
		Lvls[3] = Monstr(10, 5, 6, 1, L"Skull");
		Lvls[4] = Monstr(30, 1, 4, 3, L"Evil-Evil guy", 1);

		Lvls[1].pic[0] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP13));
		Lvls[1].pic[1] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP14));
		Lvls[1].pic[2] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP15));

		
		Lvls[0].pic[0] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP18));
		Lvls[0].pic[1] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP19));
		Lvls[0].pic[2] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP20));

		Lvls[2].pic[2] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP23));
		Lvls[2].pic[0] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP22));

		Lvls[3].pic[0] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP24));
		Lvls[3].pic[2] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP25));

		Lvls[4].pic[0] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP26));
		Lvls[4].pic[2] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP27));



	}
	void Restart()
	{
		rage = 0;
		hero = Hero(10, 0, 0, 2, L"Arthur");
		hero.pic[0] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP12));
		hero.pic[1] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP16));
		hero.pic[2] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP17));
		monstr = Lvls[lvl];
		win = 0;
		gameover = 0;
		hero.SetEnemy(&monstr);
		monstr.SetEnemy(&hero);
		RestartField();
	}
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
	Game() :hero(10, 0, 0, 2, L"Arthur")
	{
		rage = 0;
		continues = 3;
		hero.pic[0] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP12));
		hero.pic[1] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP16));
		hero.pic[2] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP17));
		SetMonsters();
		lvl = 0;
		monstr = Lvls[lvl];
		win = 0;
		gameover = 0;
		hero.SetEnemy(&monstr);
		monstr.SetEnemy(&hero);
		RestartField();
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
			monstr.Heal = 0;
			hero.Heal = 0;
			monstr.attacket = 0;
			hero.attacket = 0;
			clerselect();
			int type = Get(x, y);
			if (type == 0)
				return;
			int col=NextSqr(x, y, type);
			if (col < 2)
				return;
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
			if (col > 3)
			{
				rage += col - 3;
			}
			hero.DoStep(type, col);
			monstr.DoStep(0, 0);
			for (int i = 0; i < 20;i++)
				FallColone(i);
			for (int i = 0; i < 10; i++)
				SlideStrings();
			if (!hero.life)
			{
				gameover = 1;
				continues--;
				if (continues < 0)
				{
					fullgameover = 1;
				}
			}
			if (hero.life && !monstr.life)
			{
				win=1;
				lvl++;
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

