#include <SFML/Graphics.hpp>
#include "Classes.h"
#include "Map.h"
#include "View.h"


using namespace sf;


int main()
{
	RenderWindow window(VideoMode(640, 480), "Test!");

	Texture t;
	//t.loadFromFile("fang.png");
	t.loadFromFile("one_more_sprite.png"); 

	Image map_image;//объект для карты
	map_image.loadFromFile("ground.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);


	float currentFrame = 0;

	PLAYER p(t);

	Clock clock;

	RectangleShape rectangle(Vector2f(32, 32));

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 700;

		//if (time>20) time = 20;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			p.dx = -0.1;

		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			p.dx = 0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (p.onGround) { p.dy = -0.35; p.onGround = false; }
		}

		p.update(time);

		GetPlayerCoordianteForView(p.GetPlayerCoordinateX(), p.GetPlayerCoordinateY()); // передаем координаты игрока в ф-ию управления камерой
																				

		window.setView(view); //ожимвляем камеру


		/*if (p.rect.left>300) offsetX = p.rect.left - 300;
		offsetY = p.rect.top - 200;*/

		window.clear(Color::White);


		for (int i = 0; i<H; i++)
			for (int j = 0; j<W; j++)
			{
				if (TileMap[i][j] == 'B') s_map.setTextureRect(IntRect(0, 0, 32, 32));

				if (TileMap[i][j] == 'G') s_map.setTextureRect(IntRect(32, 0, 32, 32));

				if (TileMap[i][j] == 'O') s_map.setTextureRect(IntRect(64, 0, 32, 32));

				if (TileMap[i][j] == 'W') s_map.setTextureRect(IntRect(128, 0, 32, 32));

				if (TileMap[i][j] == '0')  s_map.setTextureRect(IntRect(160, 0, 32, 32));

				if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(96, 0, 32, 32));

				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);

			}
		
		window.draw(p.sprite);
		window.display();
	}

	return 0;
}




