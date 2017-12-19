#pragma once
#include "level.h"

class interObj
{
protected:
	String name;
	float dx, dy, speed;
	float x, y;
	int w, h;
	bool onGround;
	String path;
	Image img;
	Texture text;
	Sprite sprite;
	float currentFrame;
	std::vector<Object> obj;//вектор объектов карты
public:
	interObj(String p, String Name, int W, int H, float X, float Y)
	{
		path = p;
		img.loadFromFile(path);
		text.loadFromImage(img);
		sprite.setTexture(text);
		sprite.setTextureRect(IntRect(40 * int(currentFrame), 0, 40, 60));
		dx = 0;
		dy = 0;
		x = X;
		y = Y;
		w = W;
		h = H;
		name = Name;
		onGround = false;
		currentFrame = 0;
		speed = 0;
	};
	
	FloatRect getRect()
	{
		return FloatRect(x, y, w, h);
	}


	virtual void Update(float time) = 0;
	virtual void Append(interObj *pl) = 0;
	float GetX() {
		return x;
	}
	float GetY() {
		return y;
	}

	float Getdx() {
		return dx;
	}
	String GetName()
	{
		return name;
	}
	Sprite GetS()
	{
		return sprite;
	}

};

