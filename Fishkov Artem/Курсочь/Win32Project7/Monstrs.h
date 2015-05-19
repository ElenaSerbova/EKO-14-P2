#pragma once
#include <iostream>
#define STD 0
class creature
{
public:
	HBITMAP pic[3];
	int Heal;
	bool attacket;
	int TakenDMG;
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
		Heal = 0;
		TakenDMG = 0;
		hp = 0;
		attack = 0;
		defence = 0;
		_tcscpy_s(this->name, L"NONAME");
		life = 1;
	}
	creature(int hp, int attack, int defence, TCHAR*name)
	{
		Heal = 0;
		attacket = 0;
		TakenDMG = 0;
		if (TakenDMG < 0)
			TakenDMG = 0;
		this->hp = hp;
		this->attack = attack;
		this->defence = defence;
		_tcscpy_s(this->name, name);
		life = 1;
	}
	virtual void TakeDMG(int dmg)
	{
		attacket = 1;
		TakenDMG = (dmg - defence);
		if (TakenDMG < 0)
			TakenDMG = 0;
		hp = hp - TakenDMG;

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
	int patern;
	int timeng;
	int curentTime;
	Monstr()
	{
	}
	Monstr(int hp, int attack, int defence, int timeng, TCHAR*name, int ptr=0) : creature(hp, attack, defence, name)
	{
		patern = ptr;
		this->timeng = timeng;
		curentTime = 0;
	}
	virtual void DoStep(int type, int col)
	{
		switch (patern)
		{
		case STD:

			if (timeng == curentTime)
			{
				enemy->TakeDMG(attack);
				curentTime = 0;

			}
			else
			{
				curentTime++;
			}
			break;

		}
	}
	
};
class Hero :public creature
{
public:
	int concentration;
	int shildtime;
	int shildcurtime;
	Hero(int hp, int attack, int defence, int shildtime, TCHAR*name) : creature(hp, attack, defence, name)
	{
		concentration = 0;
		this->shildtime = shildtime;
	}
	Hero()
	{
	}
	void TakeDMG(int dmg)
	{
		attacket = 1;
		TakenDMG = (dmg - defence);
		if (TakenDMG < 0)
			TakenDMG = 0;
		hp = hp - TakenDMG;
		if (hp <= 0)
		{
			life = 0;
		}

		if (defence != 0)
		{
			if (shildcurtime == shildtime)
			{
				defence = 0;
				shildcurtime = -1;
			}
			shildcurtime++;
		}
	}
	void DoStep(int type, int col)
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
			Heal = (col + concentration);
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
