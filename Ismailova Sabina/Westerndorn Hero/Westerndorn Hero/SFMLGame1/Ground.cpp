#include "Ground.h"

Ground::Ground()
{
	dead = false;

	frontTexture.loadFromFile("tileset/Ground.png");
	sprite.setTexture(frontTexture);
}