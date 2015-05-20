#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <string> 
#include <conio.h>
#include "Collision.h"
#include "Tree.h"
#include <SFML\Audio.hpp>
#include "Mage.h"
#include "Enemy.h"
#include "Wall.h"
#include "Ground.h"
#include "Spell.h"


class Test
{
public:
	Test();
	~Test();
	void Start();
	void SetPlayerSettings(Mage&);
};

