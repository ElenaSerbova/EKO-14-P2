#include "Mage.h"

Mage::Mage()
{
	position = 1;
	gold = 0;
	experience = 0;
	mana = 100;
	manaregen = 5; // 50;
	abilityPowerPerLevel = 5;
	damage = 10;
	healthregen = 0;

	experiecePerKill = 10;
	movSpeed = 5;
	level = 1;
	dead = false;
}

#pragma region Movement

void Mage::MoveUp()
{
	if (vector.y - movSpeed <= 0)
	{
		return;
	}
	vector.y -= movSpeed;
	sprite.setPosition(vector);

	// ≈сли нет коллизии со стеной или землей
	if (Collision::PixelPerfectTest(sprite, wall.sprite) || Collision::PixelPerfectTest(sprite, ground.sprite))
	{
		vector.y += movSpeed;
		sprite.setPosition(vector);
	}
	position = 0;
	sprite.setTexture(backTexture);
}

void Mage::MoveDown()
{
	if (vector.y + movSpeed >= 700)
	{
		return;
	}

	vector.y += movSpeed;
	sprite.setPosition(vector);

	// ≈сли нет коллизии со стеной или землей
	if (Collision::PixelPerfectTest(sprite, wall.sprite) || Collision::PixelPerfectTest(sprite, ground.sprite))
	{
		vector.y -= movSpeed;
		sprite.setPosition(vector);
	}
	position = 1;
	sprite.setTexture(frontTexture);
}


void Mage::MoveLeft()
{
	if (vector.x - movSpeed <= 0)
	{
		return;
	}

	vector.x -= movSpeed;
	sprite.setPosition(vector);

	// ≈сли нет коллизии со стеной или землей
	if (Collision::PixelPerfectTest(sprite, wall.sprite) || Collision::PixelPerfectTest(sprite, ground.sprite))
	{
		vector.x += movSpeed;
		sprite.setPosition(vector);
	}
	position = 2;
	sprite.setTexture(leftTexture);

}

void Mage::MoveRight()
{
	if (vector.x + movSpeed >= 950)
	{
		return;
	}

	vector.x += movSpeed;
	sprite.setPosition(vector);

	// ≈сли нет коллизии со стеной или землей
	if (Collision::PixelPerfectTest(sprite, wall.sprite) || Collision::PixelPerfectTest(sprite, ground.sprite))
	{
		vector.x -= movSpeed;
		sprite.setPosition(vector);
	}
	position = 3;
	sprite.setTexture(rightTexture);
}

#pragma endregion Movement

short Mage::GetPosition()
{
	return position;
}

// «адаем текстуры дл€ мага тектурки дл€ мага
void Mage::SetTextures(string up, string down, string left, string right)
{
	frontTexture.loadFromFile(down);
	rightTexture.loadFromFile(right);
	leftTexture.loadFromFile(left);
	backTexture.loadFromFile(up);
}

uint Mage::GetLevel()
{
	return level;
}

uint Mage::GetExperience()
{
	return experience;
}

bool Mage::SetExpirience()
{
	experience += experiecePerKill;
	if (experience == 100)
	{
		LevelUp();
		return true;
	}
	return false;
}

void Mage::LevelUp()
{
	experience = 0;
	level++;
	damage += abilityPowerPerLevel;
}

short Mage::GetGold()
{
	return gold;
}

void Mage::SetGold()
{
	gold += GOLD;
}

void Mage::BuyItem(short money)
{
	gold -= money;
}