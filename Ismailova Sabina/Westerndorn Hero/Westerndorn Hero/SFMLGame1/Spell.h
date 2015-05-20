#pragma once
#include "Object.h"
#include "Enemy.h"

class Spell :public Object
{
protected:
	short timeToLive;
	// сторона в которую будет лететь спел
	short position;	

	unsigned short currentTexture;
	Texture textureArray[4];

public:

	Spell();
	void SetTexturesWithRoute(string, string, string, string);
	void SetTextures(Texture, Texture, Texture, Texture);
	void ChangeTexture();
	void Move(short);
	void SetPosition(short);
	short GetPosition();
	void SetTTL(short);
	short GetTTL();
	short alreadyGone;
};