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

	// Главный герой
	Mage player;

	// Задний фон, help - статическая картинка
	Pictures background, shop, help, tp, ult;

	// Скелеты
	Texture enemy[4];
	// Fireballs
	Texture fireball[3];
	// Для создания паков врагов - загрузка текстур
	Texture enemyPacks[7];

	Object hat, ring;
	Texture itemB, itemNotB, cursorTex;

	// Иконка для курсора
	Image icon;

	// Спрайты со скелетами - пока они мейн объекты
	Sprite skeletonFront,
		skeletonBack,
		skeletonRight,
		skeletonLeft,
		systemMessage_Skeletons,
		cursor;

	// Общий шрифт - "Papyrus Regular" 
	Font font;

	// Массив моих спелов 
	Spell* fireBallArray = new Spell[SIZE];

	// Массив моих врагов
	Enemy* enemyArray = new Enemy[SIZE];

	// Счетчики врагов и текущих спелов на карте	
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

	// Поток для создания нового пака мобов
	Thread thread;


#pragma endregion Поля

public:
	// Запуск стартового экрана
	void StartScreen();

	// Конструктор для инициализации потока SFML
	Game() : thread(&Game::ThreadFunc, this){};

	// Отображение стартовых картинок - вступления
	void ShowStory();

	// Сама игра
	void Game::Start();

	// Если забрали итем Ring
	void CheckRingCollision();

	// Если забрали итем Hat
	void CheckHatCollision();

	// Добавление нового врага
	void AddNewEnemy();

	// Добавляем новый fireball в массив
	void AddNewFireball();

	// Кастуем ultimate
	void Ultimate();

	// Проверяем на проигрыш нашего player'a
	void CheckGameOver();

	// Если player всё прошел и выиграл
	void PlayerWon();

	// Проверяет на заполнение массива спелов - если ФУЛ, то перезаполнить
	void IfSpellArrayFull();

	// Задание стартовых параметров, подгрузка необходимых текстур
	void SetStartSettings();

	// Манареген
	void ManaCharge();

	// Перемещение fireball'a
	void MoveSpell(Spell &fireball);

	// Проверка на то, мертвы ли все враги в текущем паке
	bool AllEnemiesDead();

	// Появление нового пака врагов
	void SpawnNewEnemyPack();

	// Проверка на получение пользователем нового уровня
	void CheckNewLevel();

	// Функция потока, которая создает новый пак мобов
	void ThreadFunc();
};

