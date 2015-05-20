#include "Object.h"

Object::Object()
{
	movSpeed = 1;
	health = 100;
	dead = false;
}

short Object::GetMovSpeed()
{
	return movSpeed;
}

void Object::SetRotation(float rotation)
{
	sprite.setRotation(rotation);
}