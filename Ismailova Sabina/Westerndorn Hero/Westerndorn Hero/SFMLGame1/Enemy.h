#pragma once
#include <string>
#include "Object.h"
#include "Collision.h"
#include "Ground.h"
#include <stdlib.h> 

#include "Ground.h"
#include "Wall.h"


class Enemy :public Object
{
protected:

	// + frontTexture от Object'a
	Texture rightTexture;
	Texture leftTexture;
	Texture backTexture;

	Wall wall;
	Ground ground;

public:

	short attackDamage;
	Enemy();

	void SetTextures(string, string, string, string);
	void SetTextures(Texture, Texture, Texture, Texture);

	bool Move(float, float);
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	// Дополнительное движение для Ghosts
	bool MoveGhost(float, float);
	void MoveUpGhost();
	void MoveDownGhost();
	void MoveLeftGhost();
	void MoveRightGhost();

	void SetDamage(short);
};