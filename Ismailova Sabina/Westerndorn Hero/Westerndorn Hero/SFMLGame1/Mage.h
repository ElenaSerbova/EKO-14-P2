#pragma once
#include <iostream>
#include "Object.h"
#include "Collision.h"
#include "Ground.h"
#include "Wall.h"
#include "Header.h"

#define uint unsigned int 

class Mage :public Object
{
protected:	
	uint abilityPowerPerLevel;

	uint level;
	uint experience;
	uint experiecePerKill;
	short gold;

	/*
	up = 0;
	down = 1;
	left = 2;
	right = 3;
	*/
	short position;

	//+ от object'a Texture front
	Texture rightTexture;
	Texture leftTexture;
	Texture backTexture;

public:
	Wall wall;
	Ground ground;

	uint mana;
	uint manaregen;
	uint healthregen;
	uint damage;

	Mage();
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	// Возвращает был ли level Up
	bool SetExpirience();
	void LevelUp();

	short GetPosition();
	void SetTextures(string, string, string, string);

	uint GetLevel();
	uint GetExperience();
		
	short GetGold();
	void SetGold();

	void BuyItem(short);
	
};

