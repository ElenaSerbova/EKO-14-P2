#include "Spell.h"

Spell::Spell()
{
	// Или таймер или количество клеток
	timeToLive = 100;
	alreadyGone = 0;
	movSpeed = 5;
	dead = false;
	currentTexture = 0;
	vector = sprite.getPosition();

	textureArray[0].loadFromFile("tileset/fireball1.png");
	textureArray[1].loadFromFile("tileset/fireball2.png");
	textureArray[2].loadFromFile("tileset/fireball3.png");
}

void Spell::SetTextures(Texture t1, Texture t2, Texture t3, Texture t4)
{
	textureArray[0] = t1;
	textureArray[1] = t2;
	textureArray[2] = t3;
}

// последоватлельное изменение текстуры
void Spell::ChangeTexture()
{
	if (currentTexture == 2)
	{
		// Если сейчас установлена третья текстура
		sprite.setTexture(textureArray[0]);
		currentTexture = 0;
	}
	else
	{
		// Если установлена первая или вторая текстура
		sprite.setTexture(textureArray[currentTexture + 1]);
		currentTexture++;
	}
}

// Передвижение
void Spell::Move(short position)
{
	if (alreadyGone == timeToLive)
	{
		dead = true;
		return;
	}
	switch (position)
	{
		// Вверх
	case 0:
		vector.y -= movSpeed;
		SetRotation(270);
		break;

		// вниз
	case 1:
		vector.y += movSpeed;
		SetRotation(90);
		break;

		// влево
	case 2:
		vector.x -= movSpeed;
		SetRotation(180);
		break;

		// вправо
	case 3:
		SetRotation(0);
		vector.x += movSpeed;
		break;

	}

	sprite.setPosition(vector);
	alreadyGone += movSpeed;
}

short Spell::GetTTL()
{
	return timeToLive;
}

// Записываю сторону в которую будет лететь спелл
void Spell::SetPosition(short position)
{
	this->position = position;
}

// Выдаю сторону в которую летит спелл
short Spell::GetPosition()
{
	return position;
}

// Задать время жизни спелла
void Spell::SetTTL(short ttl)
{
	timeToLive = ttl;
}