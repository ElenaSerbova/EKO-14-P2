#include "Item.h"

Item::Item()
{
	dead = false;
}

Item::~Item()
{

}

void Item::SetTexture(string route)
{
	frontTexture.loadFromFile(route);
	sprite.setTexture(frontTexture);
	vector = sprite.getPosition();
}