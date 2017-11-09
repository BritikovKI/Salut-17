#pragma once
#include"Map.h"
using namespace sf;



class PLAYER {
public:

	float dx, dy;
	FloatRect rect;
	bool onGround;
	Sprite sprite;
	float currentFrame;

	PLAYER(Texture &image)
	{
		sprite.setTexture(image);
		rect = FloatRect(40, 9 * 32, 40, 60);  // координаты появления персонажа и его размер

		dx = dy = 0.1;
		currentFrame = 0;
	}


	void update(float time)
	{

		rect.left += dx * time;  //rect.left - координата х
		Collision(0);   //обработка столкновений по х

		if (!onGround) dy = dy + 0.0005*time;
		rect.top += dy*time;   //rect.top  - координата y
		onGround = false;
		Collision(1); //обработка столкновений по у


		currentFrame += 0.008*time;
		if (currentFrame > 4) currentFrame -= 4;

		if (dx>0) sprite.setTextureRect(IntRect(40 * int(currentFrame), 0, 40, 60));
		if (dx<0) sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 0, -40, 60));


		sprite.setPosition(rect.left, rect.top);

		dx = 0; //для остановки персонажа
	}



	void Collision(int dir)
	{
		for (int i = rect.top / 32; i<(rect.top + rect.height) / 32; i++)
			for (int j = rect.left / 32; j<(rect.left + rect.width) / 32; j++)
			{
				if (TileMap[i][j] == 'B' || TileMap[i][j] == 'O' || TileMap[i][j] == 'W')
				{
					if ((dx>0) && (dir == 0)) rect.left = j * 32 - rect.width;
					if ((dx<0) && (dir == 0)) rect.left = j * 32 + 32;
					if ((dy>0) && (dir == 1)) { rect.top = i * 32 - rect.height;  dy = 0;   onGround = true; }
					if ((dy<0) && (dir == 1)) { rect.top = i * 32 + 32;   dy = 0; }
				}

				if (TileMap[i][j] == '0')
				{
					TileMap[i][j] = ' ';
				}

			}

	}
	float GetPlayerCoordinateX()
	{
		return rect.left;
	}
	float GetPlayerCoordinateY()
	{
		return rect.top;
	}
};