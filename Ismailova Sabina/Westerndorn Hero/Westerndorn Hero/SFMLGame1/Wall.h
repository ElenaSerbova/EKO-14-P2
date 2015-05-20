#pragma once
#include "Object.h"

class Wall :public Object
{
public:
	Wall()
	{
		dead = false;
		frontTexture.loadFromFile("tileset/wall.png");
		sprite.setTexture(frontTexture);
	}
};