#include "Spell.h"

Spell::Spell()
{
	// ��� ������ ��� ���������� ������
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

// ����������������� ��������� ��������
void Spell::ChangeTexture()
{
	if (currentTexture == 2)
	{
		// ���� ������ ����������� ������ ��������
		sprite.setTexture(textureArray[0]);
		currentTexture = 0;
	}
	else
	{
		// ���� ����������� ������ ��� ������ ��������
		sprite.setTexture(textureArray[currentTexture + 1]);
		currentTexture++;
	}
}

// ������������
void Spell::Move(short position)
{
	if (alreadyGone == timeToLive)
	{
		dead = true;
		return;
	}
	switch (position)
	{
		// �����
	case 0:
		vector.y -= movSpeed;
		SetRotation(270);
		break;

		// ����
	case 1:
		vector.y += movSpeed;
		SetRotation(90);
		break;

		// �����
	case 2:
		vector.x -= movSpeed;
		SetRotation(180);
		break;

		// ������
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

// ��������� ������� � ������� ����� ������ �����
void Spell::SetPosition(short position)
{
	this->position = position;
}

// ����� ������� � ������� ����� �����
short Spell::GetPosition()
{
	return position;
}

// ������ ����� ����� ������
void Spell::SetTTL(short ttl)
{
	timeToLive = ttl;
}