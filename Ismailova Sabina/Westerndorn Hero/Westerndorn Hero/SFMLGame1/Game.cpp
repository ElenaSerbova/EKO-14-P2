#include "Game.h"

RenderWindow window(VideoMode(1280, 800), "WESTERNDORN HERO");

// Запуск стартового экрана
void Game::StartScreen()
{
	cursorTex.loadFromFile("tileset/cursor.png");
	cursor.setTexture(cursorTex);

	window.setFramerateLimit(30);
	window.setVerticalSyncEnabled(true);

	// Cursor
	window.setMouseCursorVisible(false);

	icon.loadFromFile("tileset/down.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


	Texture startPic;
	startPic.loadFromFile("tileset/startPic1.jpg");
	Sprite startPicSprite;
	startPicSprite.setTexture(startPic);
	window.draw(startPicSprite);

	Texture aboutPic;
	aboutPic.loadFromFile("tileset/about.png");
	Sprite aboutSprite;
	aboutSprite.setTexture(aboutPic);
	Vector2i mousePos;
	font.loadFromFile("tileset/papyrus.TTF");

#pragma region

	Text play;
	play.setFont(font);
	play.setColor(Color::Black);
	play.setPosition(590, 280);
	play.setCharacterSize(65);
	play.setString("PLAY");

	Text about;
	about.setFont(font);
	about.setColor(Color::Black);
	about.setPosition(545, 380);
	about.setCharacterSize(65);
	about.setString("ABOUT");

	Text exit;
	exit.setFont(font);
	exit.setColor(Color::Black);
	exit.setPosition(600, 485);
	exit.setCharacterSize(65);
	exit.setString("EXIT");

	Text loading;
	loading.setFont(font);
	loading.setColor(Color::Yellow);
	loading.setCharacterSize(70);
	loading.setPosition(800, 600);
	loading.setString("LOADING...");


#pragma endregion Все по тексту

	while (1)
	{
		window.clear();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();
		}
		mousePos = Mouse::getPosition(window);

		if (mousePos.x >= 590 && mousePos.x <= 750 && mousePos.y >= 280 && mousePos.y <= 360)
		{
			play.setColor(Color::Yellow);
		}
		else if (mousePos.x >= 600 && mousePos.x <= 760 && mousePos.y >= 485 && mousePos.y <= 565)
		{
			exit.setColor(Color::Yellow);
		}
		else if (mousePos.x >= 545 && mousePos.x <= 800 && mousePos.y >= 380 && mousePos.y <= 460)
		{
			about.setColor(Color::Yellow);
		}
		else
		{
			play.setColor(Color::Black);
			about.setColor(Color::Black);
			exit.setColor(Color::Black);
		}

		if (event.type == Event::MouseButtonReleased)
		{
			mousePos = Mouse::getPosition(window);

			// --- PLAY ---
			if (mousePos.x >= 590 && mousePos.x <= 750 && mousePos.y >= 280 && mousePos.y <= 360)
			{
				window.draw(loading);
				window.display();
				ShowStory();
				Start();
			}
			// --- ABOUT --- 
			else if (mousePos.x >= 545 && mousePos.x <= 800 && mousePos.y >= 380 && mousePos.y <= 460)
			{
				bool temp = true;
				while (temp)
				{
					Event event;
					while (window.pollEvent(event))
					{
						if (Keyboard::isKeyPressed(Keyboard::U))
						{
							temp = false;
							break;
						}
						window.clear();
						window.draw(aboutSprite);
						window.display();
					}
				}
			}
			// --- EXIT --- 
			else if (mousePos.x >= 600 && mousePos.x <= 760 && mousePos.y >= 485 && mousePos.y <= 565)
			{
				window.close();
			}
			event.type = Event::JoystickButtonPressed;
		}

		window.draw(startPicSprite);
		window.draw(play);
		window.draw(exit);
		window.draw(about);
		cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
		window.draw(cursor);
		window.display();
	}
}

// Отображение стартовых картинок - вступления
void Game::ShowStory()
{
	Texture textures[3];
	textures[0].loadFromFile("tileset/story/1.png");
	textures[1].loadFromFile("tileset/story/2.png");
	textures[2].loadFromFile("tileset/story/3.png");

	Sprite sprites[3];
	for (size_t i = 0; i < 3; i++)
	{
		sprites[i].setTexture(textures[i]);
	}

	bool temp = true;
	short iterator = 0;
	Vector2i mousePos;

	Text loading;
	loading.setFont(font);
	loading.setColor(Color::Yellow);
	loading.setCharacterSize(70);
	loading.setPosition(800, 600);
	loading.setString("LOADING...");

	Sprite sprite = sprites[iterator];
	while (temp)
	{
		Event event;
		while (window.pollEvent(event))
		{
			window.clear();
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
			else if (Mouse::isButtonPressed(Mouse::Left))
			{
				mousePos = Mouse::getPosition(window);
				if (mousePos.x > 40 && mousePos.x < 200 && mousePos.y > 700 && mousePos.y < 800)
				{
					window.clear();
					window.draw(loading);
					temp = false;
					return;
				}
				else if (mousePos.x > 1100 && mousePos.x < 1240 && mousePos.y > 700 && mousePos.y < 800)
				{
					iterator++;
					if (iterator == 3)
					{
						window.clear();
						window.draw(loading);
						temp = false;
						return;
					}
					else
					{
						sprite = sprites[iterator];
						window.draw(sprite);
						cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
						window.draw(cursor);
						window.display();
					}
				}
			}
			else
			{
				window.draw(sprite);
				cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
				window.draw(cursor);
				window.display();
			}
		}

	}
}

// Сама игра
void Game::Start()
{
	int counter = 0;
	Vector2i mousePos;

	// Выставляем тектуры
	SetStartSettings();

	hat.vector.x = 200;
	hat.vector.y = 100;
	hat.sprite.setPosition(hat.vector);

	ring.vector.x = 300;
	ring.vector.y = 500;
	ring.sprite.setPosition(ring.vector);


#pragma region

	Text health, mana, experience, enemiesKilled, gold, playerLevel;

	health.setFont(font);
	mana.setFont(font);
	experience.setFont(font);
	playerLevel.setFont(font);
	enemiesKilled.setFont(font);
	gold.setFont(font);

	health.setCharacterSize(FONT_SIZE);
	mana.setCharacterSize(FONT_SIZE);
	experience.setCharacterSize(24);
	playerLevel.setCharacterSize(FONT_SIZE);
	enemiesKilled.setCharacterSize(FONT_SIZE);
	gold.setCharacterSize(FONT_SIZE);

	health.setColor(Color::White);
	health.setPosition(Vector2f(1150, 410));

	mana.setColor(Color::White);
	mana.setPosition(Vector2f(1150, 462));

	experience.setColor(Color::Yellow);
	experience.setPosition(Vector2f(1175, 75));

	playerLevel.setColor(Color::Yellow);
	playerLevel.setPosition(Vector2f(1160, 20));

	enemiesKilled.setColor(Color::Yellow);
	enemiesKilled.setPosition(Vector2f(1200, 550));

	gold.setColor(Color::Yellow);
	gold.setPosition(Vector2f(1180, 300));

	// ---------- WINDOW MESSAGES -------
	Text windowMessage;
	windowMessage.setFont(font);
	windowMessage.setCharacterSize(FONT_SIZE);
	windowMessage.setColor(Color::Red);
	windowMessage.setPosition(Vector2f(350, 10));

	string windowInfo = "";
	// -----------------------------------


#pragma endregion Text part

	while (window.isOpen())
	{
		// Очистка окна и отрисовка бэкграунда
		window.clear();
		window.draw(background.sprite);

		// Отрисовка телепорта и ульты
		if (isTpAvailable)
		{
			window.draw(tp.sprite);
			if (isUltAvailable)
			{
				window.draw(ult.sprite);
			}
		}
		windowInfo = "";

#pragma region 
		Event eventa;
		while (window.pollEvent(eventa))
		{
			if (eventa.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::A) && Mouse::isButtonPressed(Mouse::Left))
		{
			player.MoveLeft();
			AddNewFireball();
		}
		else if (Keyboard::isKeyPressed(Keyboard::D) && Mouse::isButtonPressed(Mouse::Left))
		{
			player.MoveRight();
			AddNewFireball();
		}
		else if (Keyboard::isKeyPressed(Keyboard::S) && Mouse::isButtonPressed(Mouse::Left))
		{
			player.MoveDown();
			AddNewFireball();
		}
		else if (Keyboard::isKeyPressed(Keyboard::W) && Mouse::isButtonPressed(Mouse::Left))
		{
			player.MoveUp();
			AddNewFireball();
		}
		else if (Keyboard::isKeyPressed(Keyboard::A))
		{
			player.MoveLeft();
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			player.MoveRight();
		}
		else if (Keyboard::isKeyPressed(Keyboard::W))
		{
			player.MoveUp();
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			player.MoveDown();
		}
		else if (Keyboard::isKeyPressed(Keyboard::P))
		{
			// ------------ Pause - Unpause --------------
			Texture texture;
			Sprite sprite;
			texture.loadFromFile("tileset/pause.png");
			sprite.setTexture(texture);

			bool temp = true;
			while (temp)
			{
				window.clear();
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::KeyPressed)
					{
						if (event.key.code == Keyboard::U)
						{
							temp = false;
							break;
						}
					}
				}
				window.draw(background.sprite);
				window.draw(sprite);
				window.display();
			}
		}
		else if (Mouse::isButtonPressed(Mouse::Left))
		{
			mousePos = Mouse::getPosition(window);

			// ----------- HELP --------------
			if (mousePos.x >= 1170 && mousePos.x <= 1230 && mousePos.y <= 175 && mousePos.y >= 135)
			{
				bool temp = true;
				while (temp)
				{
					window.clear();
					Event event;
					while (window.pollEvent(event))
					{
						if (event.type == Event::KeyPressed && event.key.code == Keyboard::U)
						{
							temp = false;
							break;
						}
					}
					window.draw(background.sprite);
					window.draw(help.sprite);
					window.display();
				}
			}
			// ----------------- SHOP ---------------
			else if (mousePos.x >= 1090 && mousePos.x <= 1230 && mousePos.y >= 350 && mousePos.y <= 390)
			{
				Text money;
				money.setFont(font);
				money.setCharacterSize(FONT_SIZE);
				money.setColor(Color::White);
				money.setPosition(Vector2f(498, 215));

				string temp = "";
				bool flag = true;
				bool item = true;
				short gold = player.GetGold();

				while (flag)
				{
					window.clear();
					gold = player.GetGold();
					Event event;
					while (window.pollEvent(event))
					{
						if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
						{
							window.close();
						}
						else if (event.type == Event::KeyPressed && event.key.code == Keyboard::U)
						{
							shop.sprite.setTexture(shop.texture);
							flag = false;
							break;
						}
						else if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left && item)
						{
							Vector2i mousePos = Mouse::getPosition(window);
							// ------------- Покупаем итем 1 -----------------
							if (mousePos.x > 377 && mousePos.x < 477 && mousePos.y > 443 && mousePos.y < 468)
							{
								if (gold >= 1000)
								{
									player.BuyItem(1000);
									shop.sprite.setTexture(itemB);
									player.damage += 10;
								}
								else
								{
									shop.sprite.setTexture(itemNotB);
								}
								item = false;
							}
							// ------------- Покупаем итем 2 -----------------
							else if (mousePos.x > 695 && mousePos.x < 791 && mousePos.y > 443 && mousePos.y < 468)
							{
								if (gold >= 2000)
								{
									player.BuyItem(2000);
									player.healthregen = 2;
									shop.sprite.setTexture(itemB);
								}
								else
								{
									shop.sprite.setTexture(itemNotB);
								}
								item = false;
							}
							// ------------- Покупаем итем 3 -----------------
							else if (mousePos.x > 1008 && mousePos.x < 1103 && mousePos.y > 443 && mousePos.y < 468)
							{
								shop.sprite.setTexture(itemNotB);
								item = false;
							}
							// ------------- Покупаем итем 4 -----------------
							else if (mousePos.x > 377 && mousePos.x < 477 && mousePos.y > 633 && mousePos.y < 658)
							{
								shop.sprite.setTexture(itemNotB);
								item = false;
							}
							// ------------- Покупаем итем 5 -----------------
							else if (mousePos.x > 695 && mousePos.x < 791 && mousePos.y > 633 && mousePos.y < 658)
							{
								shop.sprite.setTexture(itemNotB);
								item = false;
							}
							// ------------- Покупаем итем 6 -----------------
							else if (mousePos.x > 1008 && mousePos.x < 1103 && mousePos.y > 633 && mousePos.y < 658)
							{
								shop.sprite.setTexture(itemNotB);
								item = false;
							}
						}
					}
					temp = std::to_string(gold);
					money.setString(temp);

					window.clear();
					window.draw(background.sprite);
					window.draw(shop.sprite);
					window.draw(money);
					cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));
					window.draw(cursor);
					window.display();
				}
			}

			// Если вкастовываем обычный спел
			else if (mousePos.x <= 985)
			{
				if (player.mana >= SPELL_MANACOST)
				{
					AddNewFireball();
				}
			}
		}
		else if (Mouse::isButtonPressed(Mouse::Right) && isTpAvailable)
		{
			mousePos = Mouse::getPosition(window);
			if (mousePos.x <= 950 && player.mana >= 50)
			{
				// Запоминаю координаты, если будет коллизия
				short x = player.vector.x;
				short y = player.vector.y;

				player.vector.x = mousePos.x;
				player.vector.y = mousePos.y;
				player.sprite.setPosition(player.vector);

				// Проверяю коллизию со стеной или граундом
				if (Collision::PixelPerfectTest(player.sprite, player.wall.sprite) || Collision::PixelPerfectTest(player.sprite, player.ground.sprite))
				{
					player.vector.x = x;
					player.vector.y = y;
					player.sprite.setPosition(player.vector);
				}
				else
				{
					player.mana -= 50;
				}
			}
		}

		else if (Mouse::isButtonPressed(Mouse::Middle) && isUltAvailable)
		{
			if (player.mana == 100)
			{
				Ultimate();
			}
		}


#pragma endregion Movement + window

		for (short i = 0; i < fireBallCount; i++)
		{
			// Если следующий элемент - не мертвый
			if (!fireBallArray[i].dead)
			{
				// каждый третий раз меняем текстуру
				if (counter % 3 == 0)
				{
					fireBallArray[i].ChangeTexture();
				}
				MoveSpell(fireBallArray[i]);

				if (fireBallArray[i].vector.x != 0 && fireBallArray[i].vector.y != 0)
				{
					window.draw(fireBallArray[i].sprite);
				}				
			}
		}
		IfSpellArrayFull();
		if (AllEnemiesDead())
		{
			SpawnNewEnemyPack();
		}

		for (int i = 0; i < enemyCount; i++)
		{
			if (!enemyArray[i].dead)
			{
				bool col = true;
				if (currentEnemySpwan > 4)
				{
					col = enemyArray[i].MoveGhost(player.vector.x, player.vector.y);
				}
				else
				{
					col = enemyArray[i].Move(player.vector.x, player.vector.y);
				}

				// Если коллизия с игроком - метод вернет false
				if (!col)
				{
					player.health -= enemyArray[i].attackDamage;
				}
				window.draw(enemyArray[i].sprite);
			}
		}
		player.sprite.setPosition(player.vector);

		string healthInfo = std::to_string(player.health) + "/100";
		health.setString(healthInfo);
		window.draw(health);

		string levelInfo = std::to_string(player.GetLevel());
		playerLevel.setString(levelInfo);
		window.draw(playerLevel);

		string exp = std::to_string(player.GetExperience()) + "/100";
		experience.setString(exp);
		window.draw(experience);

		string monstKilled = std::to_string(monstersKilled);
		enemiesKilled.setString(monstKilled);
		window.draw(enemiesKilled);

		string goldrecieved = std::to_string(player.GetGold());
		gold.setString(goldrecieved);
		window.draw(gold);

		windowMessage.setString(windowInfo);
		window.draw(windowMessage);
		CheckGameOver();

		counter++;

		ManaCharge();
		string manaInfo = std::to_string(player.mana) + "/100";
		mana.setString(manaInfo);
		window.draw(mana);

		ManaCharge();

		// Добавляю хп реген для плеера
		player.health += player.healthregen;

		if (player.health > 100)
		{
			player.health = 100;
		}
		manaChargeCounter++;

		if (ringSpawned)
		{
			window.draw(ring.sprite);
			CheckRingCollision();
		}

		if (hatSpawned)
		{
			window.draw(hat.sprite);
			CheckHatCollision();
		}

		// Для установки картинки на положение курсора     
		cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));
		window.draw(cursor);
		window.draw(player.sprite);
		window.display();
	}
}

// Если забрали итем Ring
void Game::CheckRingCollision()
{
	if (Collision::BoundingBoxTest(ring.sprite, player.sprite))
	{
		player.manaregen *= 2;
		ringSpawned = false;

		Texture tempTex;
		tempTex.loadFromFile("tileset/ringRecieved.png");
		Sprite tempSprite;
		tempSprite.setTexture(tempTex);

		bool flag = true;
		while (flag)
		{
			window.clear();
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				{
					window.close();
				}
				else if (event.type == Event::KeyPressed && event.key.code == Keyboard::U)
				{
					flag = false;
					break;
				}
			}
			window.draw(background.sprite);
			window.draw(tempSprite);
			window.display();
		}
	}
}

// Если забрали итем Hat
void Game::CheckHatCollision()
{
	if (Collision::BoundingBoxTest(hat.sprite, player.sprite))
	{
		player.damage += 10;
		hatSpawned = false;

		Texture tempTex;
		tempTex.loadFromFile("tileset/hatRecieved.png");
		Sprite tempSprite;
		tempSprite.setTexture(tempTex);

		bool flag = true;
		while (flag)
		{
			window.clear();
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				{
					window.close();
				}
				else if (event.type == Event::KeyPressed && event.key.code == Keyboard::U)
				{
					flag = false;
					break;
				}
			}
			window.draw(background.sprite);
			window.draw(tempSprite);
			window.display();
		}
	}
}

// Добавление нового врага
void Game::AddNewEnemy()
{
	enemyArray[enemyCount].SetTextures(enemy[0], enemy[1], enemy[2], enemy[3]);
	enemyArray[enemyCount].health = 50;

	// -----  Задаю создание мобов по краям карты ------
	// Если 1
	if (rand() % 2 + 0)
	{
		enemyArray[enemyCount].vector.x = 5;
		enemyArray[enemyCount].vector.y = rand() % 350 + 0;
	}
	// Если 0
	else
	{
		enemyArray[enemyCount].vector.x = 930;
		enemyArray[enemyCount].vector.y = rand() % 250 + 200;
	}
	enemyArray[enemyCount].sprite.setPosition(enemyArray[enemyCount].vector);
	enemyArray[enemyCount].sprite.setTexture(enemyArray[enemyCount].frontTexture);

	if (currentEnemySpwan == 2)
	{
		enemyArray[enemyCount].movSpeed += 1;
	}
	else if (currentEnemySpwan == 3)
	{
		enemyArray[enemyCount].SetDamage(5);
	}

	else if (currentEnemySpwan == 5)
	{
		enemyArray[enemyCount].movSpeed += 1;
	}
	else if (currentEnemySpwan == 6)
	{
		enemyArray[enemyCount].movSpeed += 1;
		enemyArray[enemyCount].SetDamage(5);
	}
	else if (currentEnemySpwan == 7)
	{
		enemyArray[enemyCount].movSpeed += 2;
		enemyArray[enemyCount].SetDamage(10);
	}
	enemyCount++;
}

// Добавляем новый fireball в массив
void Game::AddNewFireball()
{
	fireBallArray[fireBallCount].vector.x = player.vector.x;
	fireBallArray[fireBallCount].vector.y = player.vector.y;
	fireBallArray[fireBallCount].sprite.setPosition(fireBallArray[fireBallCount].vector);
	fireBallArray[fireBallCount].SetPosition(player.GetPosition());
	fireBallCount++;
	player.mana -= SPELL_MANACOST;
}

// Кастуем ultimate
void Game::Ultimate()
{
	short x = player.vector.x - 1;
	short y = player.vector.y - 1;
	for (size_t j = 0; j < 3; j++)
	{
		for (size_t i = 0; i < 4; i++)
		{
			fireBallArray[fireBallCount].vector.x = x;
			fireBallArray[fireBallCount].vector.y = y;
			fireBallArray[fireBallCount].sprite.setPosition(fireBallArray[fireBallCount].vector);
			fireBallArray[fireBallCount].SetPosition(i);
			fireBallCount++;
		}
		y++;
		x++;
	}
	IfSpellArrayFull();
	player.mana = 0;
}

// Проверяем на проигрыш нашего player'a
void Game::CheckGameOver()
{
	if (player.health == 0 || player.health > 42000)
	{
		Texture texture;
		Sprite sprite;

		texture.loadFromFile("tileset/lost.png");
		sprite.setTexture(texture);

		bool flag = true;

		while (flag)
		{
			window.clear();
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				{
					window.close();
				}
			}
			window.draw(sprite);
			window.display();
		}
	}
}

// Если player всё прошел и выиграл
void Game::PlayerWon()
{
	Texture text[2];
	Sprite sprite;

	text[0].loadFromFile("tileset/End/1.png");
	text[1].loadFromFile("tileset/End/2.png");
	sprite.setTexture(text[0]);

	bool flag = true;

	while (flag)
	{
		window.clear();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}

			else if (Mouse::isButtonPressed(Mouse::Left))
			{
				Vector2i mousePos = Mouse::getPosition(window);
				// Exit
				if (mousePos.x > 40 && mousePos.x < 200 && mousePos.y > 700 && mousePos.y < 800)
				{
					window.close();
				}
				// Next
				else if (mousePos.x > 1100 && mousePos.x < 1240 && mousePos.y > 700 && mousePos.y < 800)
				{
					sprite.setTexture(text[1]);
				}
			}
		}
		window.draw(sprite);
		cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
		window.draw(cursor);
		window.display();
	}
}

// Проверяет на заполнение массива спелов - если ФУЛ, то перезаполнить
void Game::IfSpellArrayFull()
{

	if (fireBallCount <= SIZE - 10)
	{
		return;
	}

	int index = 0;
	int j = 0;
	cout << "In IsSpellArrayFull\n";
	//Считаю кол-во живых элементов
	for (int i = 0; i < SIZE; i++)
	{
		if (!fireBallArray[i].dead)
		{
			index++;
		}
	}

	Spell* tempArray = new Spell[index];

	for (int i = 0; i < SIZE; i++)
	{
		if (!fireBallArray[i].dead)
		{
			tempArray[j] = fireBallArray[i];
			j++;
		}
	}

	// удаляю массив старый
	delete[]fireBallArray;

	fireBallArray = new Spell[SIZE];
	for (int i = 0; i < j; i++)
	{
		fireBallArray[i] = tempArray[i];
	}
	for (int i = j; i < SIZE; i++)
	{
		Spell a;
		fireBallArray[i] = a;
	}
	fireBallCount = j;
}

// Задание стартовых параметров, подгрузка необходимых текстур
void Game::SetStartSettings()
{
	// Настройки для player'a 
	player.SetTextures("tileset/fireUp.png", "tileset/fireDown.png", "tileset/fireLeft.png", "tileset/fireRight.png");
	player.sprite.setTexture(player.frontTexture);
	player.vector.x = 500;
	player.vector.y = 300;
	player.sprite.setPosition(player.vector);

	background.texture.loadFromFile("tileset/tempBackground.jpg");
	background.sprite.setTexture(background.texture);

	// Магазин
	shop.texture.loadFromFile("tileset/shop.png");
	shop.sprite.setTexture(shop.texture);

	help.texture.loadFromFile("tileset/help.png");
	help.sprite.setTexture(help.texture);

	// Для Enemy Spawns
	enemyPacks[0].loadFromFile("tileset/enemyPacks/1.png");
	systemMessage_Skeletons.setTexture(enemyPacks[0]);

	enemyPacks[1].loadFromFile("tileset/enemyPacks/2.png");
	enemyPacks[2].loadFromFile("tileset/enemyPacks/3.png");
	enemyPacks[3].loadFromFile("tileset/enemyPacks/4.png");
	enemyPacks[4].loadFromFile("tileset/enemyPacks/5.png");
	enemyPacks[5].loadFromFile("tileset/enemyPacks/6.png");
	enemyPacks[6].loadFromFile("tileset/enemyPacks/7.png");

	// Телепорт и ульт - маленькие иконки
	tp.texture.loadFromFile("tileset/tp.png");
	tp.sprite.setTexture(tp.texture);
	ult.texture.loadFromFile("tileset/ult.png");
	ult.sprite.setTexture(ult.texture);

	// Текстуры для итемов
	hat.frontTexture.loadFromFile("tileset/hat1.png");
	hat.sprite.setTexture(hat.frontTexture);
	ring.frontTexture.loadFromFile("tileset/ring.png");
	ring.sprite.setTexture(ring.frontTexture);

	// Еукстуры для врагов
	enemy[0].loadFromFile("tileset/skeletonUp.png");
	enemy[1].loadFromFile("tileset/skeletonDown.png");
	enemy[2].loadFromFile("tileset/skeletonLeft.png");
	enemy[3].loadFromFile("tileset/skeletonRight.png");
	skeletonFront.setTexture(enemy[1]);
	skeletonBack.setTexture(enemy[0]);
	skeletonLeft.setTexture(enemy[2]);
	skeletonRight.setTexture(enemy[3]);

	itemB.loadFromFile("tileset/itemBought.png");
	itemNotB.loadFromFile("tileset/notEnoughMoney.png");
}

// Манареген
void Game::ManaCharge()
{
	if (manaChargeCounter % 40 == 0)
	{
		if (player.mana + player.manaregen < 100)
		{
			player.mana += player.manaregen;
		}
		else
		{
			player.mana = 100;
		}
	}

	else if (player.mana > 100)
	{
		player.mana = 100;
	}
}

// Перемещение fireball'a
void Game::MoveSpell(Spell &fireball)
{
	short movSpeed = fireball.GetMovSpeed();
	if (fireball.alreadyGone == fireball.GetTTL())
	{
		fireball.dead = true;
		return;
	}
	switch (fireball.GetPosition())
	{
		// Вверх
	case 0:
		fireball.vector.y -= movSpeed;
		fireball.SetRotation(270);
		break;

		// вниз
	case 1:
		fireball.vector.y += movSpeed;
		fireball.SetRotation(90);
		break;

		// влево
	case 2:
		fireball.vector.x -= movSpeed;
		fireball.SetRotation(180);
		break;

		// вправо
	case 3:
		fireball.SetRotation(0);
		fireball.vector.x += movSpeed;
		break;

	}
	fireball.sprite.setPosition(fireball.vector);

	// Проверяю на коллизию с врагами
	for (size_t i = 0; i < enemyCount; i++)
	{
		if (Collision::BoundingBoxTest(fireball.sprite, enemyArray[i].sprite) && !enemyArray[i].dead)
		{
			enemyArray[i].health -= player.damage;
			if (enemyArray[i].health <= 0 || enemyArray[i].health >= 40000)
			{
				enemyArray[i].dead = true;
				monstersKilled++;
				levelUp = player.SetExpirience();
				if (levelUp)
				{
					cout << "Level Up!" << endl;
					CheckNewLevel();
				}
				player.SetGold();
			}
			fireball.alreadyGone = fireball.GetTTL();
			fireball.dead = true;
			return;
		}
	}
	fireball.alreadyGone += movSpeed;
}

// Проверка на то, мертвы ли все враги в текущем паке
bool Game::AllEnemiesDead()
{
	if (enemyCount == 0)
	{
		return true;
	}
	for (size_t i = 0; i < enemyCount; i++)
	{
		if (!enemyArray[i].dead)
		{
			return false;
		}
	}
	enemyCount = 0;
	return true;
}

// Появление нового пака врагов
void Game::SpawnNewEnemyPack()
{
	switch (currentEnemySpwan)
	{
	case 1:
		enemyPackCount = 13;
		break;
	case 2:
		enemyPacks[0] = enemyPacks[1];
		enemyPackCount = 23;
		break;
	case 3:
		enemyPacks[0] = enemyPacks[2];
		enemyPackCount = 43;
		break;

		// Здесь появляются духи
	case 4:
		enemyPacks[0] = enemyPacks[3];
		enemy[0].loadFromFile("tileset/up.png");
		enemy[1].loadFromFile("tileset/down.png");
		enemy[2].loadFromFile("tileset/left.png");
		enemy[3].loadFromFile("tileset/right.png");
		enemyPackCount = 23;
		break;
	case 5:
		enemyPacks[0] = enemyPacks[4];
		enemyPackCount = 33;

		break;
	case 6:
		enemyPacks[0] = enemyPacks[5];
		enemyPackCount = 43;
		break;
	case 7:
		enemyPacks[0] = enemyPacks[6];
		enemyPackCount = 49;
		break;
	case 8:
		PlayerWon();
		break;
	}

	thread.launch();
	systemMessage_Skeletons.setTexture(enemyPacks[0]);


	while (threadWorking)
	{
		window.clear();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
		}
		window.draw(background.sprite);
		window.draw(systemMessage_Skeletons);
		window.display();
	}
	thread.terminate();
	threadWorking = true;
	return;
}

// Проверка на получение пользователем нового уровня
void Game::CheckNewLevel()
{
	unsigned int level = player.GetLevel();
	Texture texture;
	Sprite sprite;

	if (level == 3)
	{
		hatSpawned = true;
		return;
	}
	else if (level == 5)
	{
		texture.loadFromFile("tileset/newSkillTP.png");
		sprite.setTexture(texture);
		isTpAvailable = true;
	}
	else if (level == 8)
	{
		ringSpawned = true;
		return;
	}
	else if (level == 10)
	{
		texture.loadFromFile("tileset/newSkillULT.png");
		sprite.setTexture(texture);
		isUltAvailable = true;
	}
	else
	{
		return;
	}

	bool flag = true;
	while (flag)
	{
		window.clear();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::U)
				{
					flag = false;
					break;
				}
			}
		}
		window.draw(background.sprite);
		window.draw(sprite);
		window.display();
	}
}

// Функция потока, которая создает новый пак мобов
void Game::ThreadFunc()
{
	delete[] enemyArray;
	enemyArray = new Enemy[SIZE];
	for (int i = 0; i < enemyPackCount; i++)
	{
		AddNewEnemy();
	}
	currentEnemySpwan++;
	threadWorking = false;

}