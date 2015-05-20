#include "Enemy.h"
#include "Header.h"

using namespace sf;

Enemy::Enemy()
{
	attackDamage = 1;

	movSpeed = 1;
	health = 50;
	dead = false;
}

// Задаем текстуры для врага
void Enemy::SetTextures(string up, string down, string left, string right)
{
	frontTexture.loadFromFile(down);
	rightTexture.loadFromFile(right);
	leftTexture.loadFromFile(left);
	backTexture.loadFromFile(up);
}

// Присвоение уже загруженных текстур
void Enemy::SetTextures(Texture t1, Texture t2, Texture t3, Texture t4)
{
	frontTexture = t2;
	rightTexture = t4;
	leftTexture = t3;
	backTexture = t1;
}

bool Enemy::Move(float playerX, float playerY)
{
	int x = playerX - vector.x;
	int y = playerY - vector.y;

	if (abs(vector.x - playerX) <= SPRITE_WIDTH && abs(vector.y - playerY) <= SPRITE_WIDTH)
	{
		return false;
	}

	if (x < -5)
	{
		MoveLeft();
	}
	if (x > 5)
	{
		MoveRight();
	}
	if (y < -5)
	{
		MoveUp();
	}
	if (y > 5)
	{
		MoveDown();
	}
	return true;
}


#pragma region Movement

void Enemy::MoveUp()
{
	if (vector.y - movSpeed <= 0)
	{
		return;
	}
	vector.y -= movSpeed;
	sprite.setPosition(vector);

	// Если нет коллизии со стеной или землей
	if (Collision::PixelPerfectTest(sprite, wall.sprite) || Collision::PixelPerfectTest(sprite, ground.sprite))
	{
		vector.y += movSpeed;
		sprite.setPosition(vector);
		//MoveDown();
	}
	sprite.setTexture(backTexture);
}

void Enemy::MoveDown()
{
	if (vector.y + movSpeed >= 700)
	{
		return;
	}

	vector.y += movSpeed;
	sprite.setPosition(vector);

	// Если нет коллизии со стеной или землей
	if (Collision::PixelPerfectTest(sprite, wall.sprite) || Collision::PixelPerfectTest(sprite, ground.sprite))
	{
		vector.y -= movSpeed;
		sprite.setPosition(vector);
		//MoveRight();
	}
	sprite.setTexture(frontTexture);
}


void Enemy::MoveLeft()
{
	if (vector.x - movSpeed <= 0)
	{
		return;
	}

	vector.x -= movSpeed;
	sprite.setPosition(vector);

	// Если нет коллизии со стеной или землей
	if (Collision::PixelPerfectTest(sprite, wall.sprite) || Collision::PixelPerfectTest(sprite, ground.sprite))
	{
		vector.x += movSpeed;
		sprite.setPosition(vector);
	}
	sprite.setTexture(leftTexture);

}

void Enemy::MoveRight()
{
	if (vector.x + movSpeed >= 950)
	{
		return;
	}

	vector.x += movSpeed;
	sprite.setPosition(vector);

	// Если нет коллизии со стеной или землей
	if (Collision::PixelPerfectTest(sprite, wall.sprite) || Collision::PixelPerfectTest(sprite, ground.sprite))
	{
		vector.x -= movSpeed;
		sprite.setPosition(vector);
	}
	sprite.setTexture(rightTexture);
}

#pragma endregion Movement



bool Enemy::MoveGhost(float playerX, float playerY)
{
	int x = playerX - vector.x;
	int y = playerY - vector.y;

	if (abs(vector.x - playerX) <= SPRITE_WIDTH && abs(vector.y - playerY) <= SPRITE_WIDTH)
	{
		return false;
	}

	if (x < -5)
	{
		MoveLeftGhost();
	}
	if (x > 5)
	{
		MoveRightGhost();
	}
	if (y < -5)
	{
		MoveUpGhost();
	}
	if (y > 5)
	{
		MoveDownGhost();
	}
	return true;
}


#pragma region Movement

void Enemy::MoveUpGhost()
{
	if (vector.y - movSpeed <= 0)
	{
		return;
	}
	vector.y -= movSpeed;
	sprite.setPosition(vector);
	sprite.setTexture(backTexture);
}

void Enemy::MoveDownGhost()
{
	if (vector.y + movSpeed >= 700)
	{
		return;
	}

	vector.y += movSpeed;
	sprite.setPosition(vector);
	sprite.setTexture(frontTexture);
}


void Enemy::MoveLeftGhost()
{
	if (vector.x - movSpeed <= 0)
	{
		return;
	}

	vector.x -= movSpeed;
	sprite.setPosition(vector);
	sprite.setTexture(leftTexture);

}

void Enemy::MoveRightGhost()
{
	if (vector.x + movSpeed >= 950)
	{
		return;
	}

	vector.x += movSpeed;
	sprite.setPosition(vector);
	sprite.setTexture(rightTexture);
}

#pragma endregion Movement

void Enemy::SetDamage(short dmg)
{
	attackDamage += dmg;
}
