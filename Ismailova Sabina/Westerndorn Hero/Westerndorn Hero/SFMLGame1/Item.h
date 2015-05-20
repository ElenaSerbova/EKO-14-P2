#pragma once
#include "Object.h"

class Item : public Object
{
protected:

public:
	Item();
	~Item();
	void SetTexture(string);
};