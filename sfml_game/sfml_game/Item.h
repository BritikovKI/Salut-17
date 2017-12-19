#pragma once
#include "interObj.h"
#include "level.h"
using namespace sf;


class Item :public interObj
{
protected:
	interObj *owner=NULL;
public:
	Item(String p, String name, Level &lev, int W, int H, float X, float Y, interObj* par) :interObj(p,name, W, H, X, Y)
	{
		owner = par;
		obj = lev.GetAllObjects();
		sprite.setTextureRect(IntRect(50 * 4, 0, 50, 30));
	}
	void Update(float time)
	{
		if (owner == NULL)
		{
			x = x;
			y = y;
			sprite.setPosition(x, y);
		}
//		else
//		{
//			x = owner->GetX();  //rect.left - координата х
//			y = owner->GetY();
//;   //обработка столкновений по х
//
//
//			currentFrame += 0.008*time;
//			if (currentFrame > 4) currentFrame -= 4;
//
//			if (owner->getdx > 0) sprite.setTextureRect(IntRect(40 * int(currentFrame), 0, 40, 60));
//			if (owner->getdx < 0) sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 0, -40, 60));
//
//
//			sprite.setPosition(x, y);
//
//			dx = 0;
//		}
	}
};

class ActiveItem:public Item
{
protected:
	bool weared = false;
public:
	ActiveItem(String p, String name, Level &lev, int W, int H, float X, float Y, interObj * par) :Item(p, name,lev, W, H, X, Y,  par)
	{
		weared = false;
	}
	void Update(float time)
	{
		if (owner == NULL)
		{
			x = x;
			y = y;
			sprite.setPosition(x, y);
		}
		if(owner!=NULL && weared==true)
		{
			x = owner->GetX();  //rect.left - координата х
			y = owner->GetY();
		   //обработка столкновений по х
				
			currentFrame += 0.008*time;
			if (currentFrame > 4) currentFrame -= 4;
			if (owner->Getdx() > 0) sprite.setTextureRect(IntRect(40 * int(currentFrame), 0, 40, 60));
			if (owner->Getdx() < 0) sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 0, -40, 60));
			sprite.setPosition(x, y);
			dx = 0;
		}
	}

};

class Bullet : public ActiveItem
{
	int speed;
public:
	Bullet(String p, String name, Level &lev, int W, int H, float X, float Y, interObj * par,int speed) :ActiveItem(p, name, lev, W, H, X, Y, par)
	{
		weared = false;
	}
	void Append(interObj *pl)
	{
		return;
	}
};


class Gun :public ActiveItem
{
//	Bullet *obj;
public:
	Gun(String p, String name, Level &lev, int W, int H, float X, float Y,  interObj * par) :ActiveItem(p, name, lev, W, H, X, Y, par)
	{}
	void Append(interObj *pl)
	{
		owner = pl;
		weared = true;
	}
	void Draw(float x, float y)
	{

		sprite.setPosition(x, y);
	}
	void Shoot(std::list<interObj*>  interObjects, Level &lev)
	{
		interObjects.push_back(new Bullet("bullet.png", "bullet", lev, 10, 10, x, y, this, 10));
	}
};