#pragma once
#include"Map.h"
#include "InterObj.h"
using namespace sf;



//class PLAYER:interObj {
//public:
//	PLAYER(Texture &image)
//	{
//		sprite.setTexture(image);
//		rect = FloatRect(40, 9 * 32, 40, 60);  // ���������� ��������� ��������� � ��� ������
//
//		dx = dy = 0.1;
//		currentFrame = 0;
//	}
//
//
//	void update(float time)
//	{
//
//		rect.left += dx * time;  //rect.left - ���������� �
//		Collision(0);   //��������� ������������ �� �
//
//		if (!onGround) dy = dy + 0.0005*time;
//		rect.top += dy*time;   //rect.top  - ���������� y
//		onGround = false;
//		Collision(1); //��������� ������������ �� �
//
//
//		currentFrame += 0.008*time;
//		if (currentFrame > 4) currentFrame -= 4;
//
//		if (dx>0) sprite.setTextureRect(IntRect(40 * int(currentFrame), 0, 40, 60));
//		if (dx<0) sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 0, -40, 60));
//
//
//		sprite.setPosition(rect.left, rect.top);
//
//		dx = 0; //��� ��������� ���������
//	}
//	void goLeft()
//	{
//
//	}
//
//
//};