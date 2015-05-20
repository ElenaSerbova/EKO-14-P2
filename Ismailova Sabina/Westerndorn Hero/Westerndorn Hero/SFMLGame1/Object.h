#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#define uint unsigned int 

using namespace std;
using namespace sf;

class Object
{
	//protected:
public:
	short movSpeed;
	uint health;

	//уничтожен ли объект
	bool dead;

	Texture frontTexture;
	Sprite sprite;
	Vector2f vector;

public:

	Object();
	short GetMovSpeed();
	void SetRotation(float);
};