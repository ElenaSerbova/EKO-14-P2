#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <string> 
#include <conio.h>
#include "Collision.h"
#include "Mage.h"
#include "Spell.h"
#include "Header.h"

using namespace sf;

class Game
{

private:

#pragma region 

	// ������� �����
	Mage player;

	// ������ ���, help - ����������� ��������
	Pictures background, shop, help, tp, ult;

	// �������
	Texture enemy[4];
	// Fireballs
	Texture fireball[3];
	// ��� �������� ����� ������ - �������� �������
	Texture enemyPacks[7];

	Object hat, ring;
	Texture itemB, itemNotB, cursorTex;

	// ������ ��� �������
	Image icon;

	// ������� �� ��������� - ���� ��� ���� �������
	Sprite skeletonFront,
		skeletonBack,
		skeletonRight,
		skeletonLeft,
		systemMessage_Skeletons,
		cursor;

	// ����� ����� - "Papyrus Regular" 
	Font font;

	// ������ ���� ������ 
	Spell* fireBallArray = new Spell[SIZE];

	// ������ ���� ������
	Enemy* enemyArray = new Enemy[SIZE];

	// �������� ������ � ������� ������ �� �����	
	short fireBallCount = 0;
	short enemyPackCount = 10;
	short enemyCount = 0;
	uint manaChargeCounter = 0;

	unsigned short monstersKilled = 0;
	unsigned short currentEnemySpwan = 1;

	bool isTpAvailable = false,
		isUltAvailable = false,
		levelUp = false,
		ringSpawned = false,
		hatSpawned = false,
		threadWorking = true;

	// ����� ��� �������� ������ ���� �����
	Thread thread;


#pragma endregion ����

public:
	// ������ ���������� ������
	void StartScreen();

	// ����������� ��� ������������� ������ SFML
	Game() : thread(&Game::ThreadFunc, this){};

	// ����������� ��������� �������� - ����������
	void ShowStory();

	// ���� ����
	void Game::Start();

	// ���� ������� ���� Ring
	void CheckRingCollision();

	// ���� ������� ���� Hat
	void CheckHatCollision();

	// ���������� ������ �����
	void AddNewEnemy();

	// ��������� ����� fireball � ������
	void AddNewFireball();

	// ������� ultimate
	void Ultimate();

	// ��������� �� �������� ������ player'a
	void CheckGameOver();

	// ���� player �� ������ � �������
	void PlayerWon();

	// ��������� �� ���������� ������� ������ - ���� ���, �� �������������
	void IfSpellArrayFull();

	// ������� ��������� ����������, ��������� ����������� �������
	void SetStartSettings();

	// ���������
	void ManaCharge();

	// ����������� fireball'a
	void MoveSpell(Spell &fireball);

	// �������� �� ��, ������ �� ��� ����� � ������� ����
	bool AllEnemiesDead();

	// ��������� ������ ���� ������
	void SpawnNewEnemyPack();

	// �������� �� ��������� ������������� ������ ������
	void CheckNewLevel();

	// ������� ������, ������� ������� ����� ��� �����
	void ThreadFunc();
};

