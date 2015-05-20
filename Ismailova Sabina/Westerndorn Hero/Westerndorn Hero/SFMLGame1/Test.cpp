#include "Test.h"


Test::Test()
{

}

Test::~Test()
{

}

void Test::Start()
{
	Mage player;
	bool flag = true;

	SetPlayerSettings(player);

	Object background;
	background.frontTexture.loadFromFile("tileset/start.jpg");
	background.sprite.setTexture(background.frontTexture);

	RenderWindow window(VideoMode(1280, 800), "Test Game xd");
	// Настройки окна 
	window.setFramerateLimit(30);
	window.setVerticalSyncEnabled(true);

	Rect<int> rect(30, 30, 50, 100);
	Vector2i mousePos;

	Font font;
	font.loadFromFile("tileset/ARIAL.TTF");

	Text info;
	info.setFont(font);
	info.setColor(Color::Green);
	info.setPosition(500, 400);
	info.setCharacterSize(35);
	info.setString("New Game");

	Text exit;
	exit.setFont(font);
	exit.setColor(Color::Green);
	exit.setPosition(500, 450);
	exit.setCharacterSize(35);
	exit.setString("Exit");


	Vector2f playerCoords;

	while (flag && window.isOpen())
	{
		window.clear();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();
		}
		mousePos = Mouse::getPosition(window);
		if (mousePos.x >= 500 && mousePos.x <= 600 && mousePos.y >= 405 && mousePos.y <= 430)
		{
			info.setColor(Color::Yellow);
		}
		else if (mousePos.x >= 500 && mousePos.x <= 580 && mousePos.y >= 450 && mousePos.y <= 485)
		{
			exit.setColor(Color::Yellow);
		}
		else
		{
			info.setColor(Color::Green);
			exit.setColor(Color::Green);
		}

		if (event.type == Event::MouseButtonReleased)
		{
			mousePos = Mouse::getPosition(window);
			if (mousePos.x >= 500 && mousePos.x <= 600 && mousePos.y >= 405 && mousePos.y <= 430)
			{
				flag = false;
			}
			else if (mousePos.x >= 500 && mousePos.x <= 580 && mousePos.y >= 450 && mousePos.y <= 485)
			{
				window.close();
			}

			cout << "Mouse is : " << mousePos.y << "," << mousePos.y << endl;
			event.type = Event::JoystickButtonPressed;
		}

		window.draw(background.sprite);
		window.draw(info);
		window.draw(exit);
		window.display();
	}

	while (window.isOpen())
	{
		window.clear();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();
		}

		if (event.type == Event::MouseButtonReleased)
		{
			mousePos = Mouse::getPosition(window);
			player.sprite.getPosition();
			if (mousePos.x - playerCoords.x > mousePos.y - playerCoords.y && mousePos.y > playerCoords.y)
			{
				player.MoveRight();
			}
			else if (mousePos.y - playerCoords.y > mousePos.x - playerCoords.x && mousePos.y > playerCoords.y)
			{
				player.MoveUp();
			}
			else if (mousePos.y - playerCoords.y < mousePos.x - playerCoords.x)
			{
				player.MoveDown();
			}
			else
			{
				player.MoveLeft();
			}
			event.type = Event::JoystickButtonPressed;
		}

		window.draw(background.sprite);
		window.draw(player.sprite);
		window.display();
	}
}

void Test::SetPlayerSettings(Mage& player)
{
	player.SetTextures("tileset/fireUp.png", "tileset/fireDown.png", "tileset/fireLeft.png", "tileset/fireRight.png");
	player.SetType(0);
	player.sprite.setTexture(player.frontTexture);
	player.vector.x = 500;
	player.vector.y = 300;
	player.sprite.setPosition(player.vector);
}