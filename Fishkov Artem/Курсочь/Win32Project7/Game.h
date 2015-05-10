#pragma once
#include <iostream>
class creature
{
public:
	bool life;
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
		life = 1;
	}
	creature(int hp,int attack,int defence,TCHAR*name)
	{
		this->hp = hp;
		this->attack = attack;
		this->defence = defence;
		_tcscpy_s(this->name, name);	
		life = 1;
	}
	virtual void TakeDMG(int dmg)
	{
		hp = hp - (dmg-defence);
		if (hp <= 0)
		{
			life = 0;
		}
	}
	virtual void DoStep(int type, int col) = 0;
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
	void DoStep(int type, int col)
	{
		if (timeng == curentTime)
		{
			enemy->TakeDMG(attack);
			curentTime = 0;

		}
		else
		{
			curentTime++;
		}
	}
};
class Hero :public creature
{
public:
	int concentration;
	int shildtime;
	int shildcurtime;
	Hero(int hp, int attack, int defence,int shildtime,TCHAR*name) : creature(hp, attack, defence, name)
	{
		concentration = 0;
		this->shildtime = shildtime;
	}
	Hero()
	{
	}
	void TakeDMG(int dmg)
	{
		hp = hp - (dmg - defence);
		if (hp <= 0)
		{
			life = 0;
		}

		if (defence != 0)
		{
			if (shildcurtime == shildtime)
			{
				defence = 0;
			}
			shildcurtime++;
		}
	}
	void DoStep(int type,int col)
	{
		
		switch (type)
		{
		case 1:
			enemy->TakeDMG(col + concentration);
			concentration = 0;
			break;
		case 2:
			defence = col + concentration;
			shildcurtime = 0;
			concentration = 0;
			break;
		case 3:
			hp += col + concentration;
			concentration = 0;
			break;
		case 4:
			concentration = col;
			break;
		case 5:
			enemy->TakeDMG(col + concentration);
			concentration = 0;
			break;
		}
		
	}
};


class Game
{
	bool selectfield[10][20];
	int* field[10][20];
public:
	bool win;
	bool gameover;
	Hero hero;
	Monstr monstr;
	void Restart()
	{
		hero = Hero(10, 0, 0, 2, L"Nigga");
		monstr = Monstr(15, 5, 2, 1,L"Spady");
		win = 0;
		gameover = 0;
		hero.SetEnemy(&monstr);
		monstr.SetEnemy(&hero);
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				field[i][j] = new int(0);
				*field[i][j] = (rand() % 5) + 1;

			}
		}
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
	Game() :hero(10, 0, 0,2,L"Nigga"), monstr(15,5,2,1,L"Spady")
	{
		win = 0;
		gameover = 0;
		hero.SetEnemy(&monstr);
		monstr.SetEnemy(&hero);
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				field[i][j] = new int(0);
				*field[i][j] = (rand() % 5) + 1;
				
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
			hero.DoStep(type, col);
			monstr.DoStep(0, 0);
			for (int i = 0; i < 20;i++)
				FallColone(i);
			for (int i = 0; i < 10; i++)
				SlideStrings();
			if (!hero.life)
			{
				gameover = 1;
			}
			if (hero.life && !monstr.life)
			{
				win=1;
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

