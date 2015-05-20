#pragma once
#include "Object.h"

class Tree :public Object
{
public:
	Texture opaciveTexture;
	Tree();
	~Tree();
	void SetTexture(string);
	void SetOpaciveTexture(string);
};
