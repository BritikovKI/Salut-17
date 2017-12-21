#pragma once
#include "InterObj.h"
#include "Map.h"


class Item :interObj
{
	int size;
	interObj *owner;
public:
	Item(String p, float sx, float sy, FloatRect r, bool onG, float cuF,int s, interObj* par) :interObj(p, sx, sy, r, onG, cuF)
	{
		owner = par;
		size = s;
	}
	void update(float time)
	{
		rect.left += owner->getdx * time;  //rect.left - координата х
		Collision(0);   //обработка столкновений по х

		if (!onGround) dy = owner->getdy + 0.0005*time;
		rect.top += owner->getdy*time;   //rect.top  - координата y
		onGround = false;
		Collision(1); //обработка столкновений по у


		currentFrame += 0.008*time;
		if (currentFrame > 8) currentFrame -= 8;

		if (owner->getdx>0) sprite.setTextureRect(IntRect(40 * int(currentFrame), 0, 40, 60));
		if (owner->getdy<0) sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 0, -40, 60));


		sprite.setPosition(rect.left, rect.top);

		dx = 0;
	}
};