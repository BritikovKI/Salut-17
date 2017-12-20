#pragma once
#include "interObj.h"
#include "level.h"
using namespace sf;
extern std::list<interObj*>  interObjects;

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
		onGround = true;
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
	int dir;
	
	int st_pos = 0;
	int range = 0;
public:
	Bullet(String p, String name, Level &lev, int W, int H, float X, float Y, interObj * par,int spd,int direct,int rg) :ActiveItem(p, name, lev, W, H, X, Y, par)
	{
		range = rg;
		dir = direct;
		speed = spd;
		st_pos = x;
	}
	~Bullet()
	{}
	Sprite Draw(float x,float y)
	{
		return sprite;
	}
	void Collision(float Dx, float Dy)
	{
		for (int i = 0; i<obj.size(); i++)//ïðîõîäèìñÿ ïî îáúåêòàì
			if (getRect().intersects(obj[i].rect))//ïðîâåðÿåì ïåðåñå÷åíèå èãðîêà ñ îáúåêòîì
			{
				if (obj[i].name == "solid")//åñëè âñòðåòèëè ïðåïÿòñòâèå
				{
					onLevel = false;
					this->~Bullet();
				}


			}
	}
	void Interrupt()
	{
		for (std::list<interObj*>::iterator i = interObjects.begin(); i != interObjects.end(); ) {//проходимся по объектам
			if (getRect().intersects((*i)->getRect()))//проверяем пересечение игрока с объектом
			{
				if ((*i)->GetName() == "solid")//если встретили препятствие
				{
					onLevel = false;
				}
				
				if ((*i)->GetName() == "enemy")
				{
					onLevel = false;
				}


			}
			i++;
		}
	}
	void Update(float time)
	{
		if(dir==1)
			if (x > range + st_pos)
			{
				onLevel = false;
			}
		if(dir==0)
		{
			if (x < st_pos - range)
				onLevel = false;
		}
		switch (dir)
		{
		case 0: dx = -speed; dy = 0;   break;//интовое значение state = left
		case 1: dx = speed; dy = 0;   break;//интовое значение state = right
		case 2: dx = 0; dy = -speed;   break;//интовое значение state = up
		case 3: dx = 0; dy = -speed;   break;//интовое значение не имеющее отношения к направлению, пока просто стрельнем вверх, нам сейчас это не важно
		case 4: dx = 0; dy = -speed;   break;//интовое значение не имеющее отношения к направлению, пока просто стрельнем вверх, нам сейчас это не важно
		case 5: dx = 0; dy = -speed;   break;//интовое значение не имеющее отношения к направлению, пока просто стрельнем вверх, нам сейчас это не важно
		}
		printf("%u",dir);
		x += dx*time;//само движение пули по х
		y += dy*time;//по у
		Collision(dx, dy);
		Interrupt();
		if (x <= 0) x = 1;// задержка пули в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки
		if (y <= 0) y = 1;

		//for (int i = 0; i < obj.size(); i++) {//проход по объектам solid
		//	if (getRect().intersects(obj[i].rect)) //если этот объект столкнулся с пулей,
		//	{
		//		onGround = false;// то пуля умирает
		//	}
		//}

		sprite.setPosition(x , y );//задается позицию пуле
	}
	void Shoot(Level &lev, int dir,int x,int y) { return; }
};


class Gun :public ActiveItem
{
//	Bullet *obj;

public:
	Gun(String p, String name, Level &lev, int W, int H, float X, float Y, interObj * par) :ActiveItem(p, name, lev, W, H, X, Y, par)
	{};
	void Update(float time) ;
	Sprite Draw(float xg, float yg)
	{
		x = xg;  //rect.left - êîîðäèíàòà õ
		y = yg;   //rect.top  - êîîðäèíàòà y
		sprite.setPosition(x, y);
		return sprite;
	}
	void Shoot(Level &lev,int dir,int left,int right)
	{
		if(dir==1)
			interObjects.push_back(new Bullet("fire.png", "bullet", lev, 43, 26, right+1, y, this, 1,dir,50));
		else
			interObjects.push_back(new Bullet("fire.png", "bullet", lev,43, 26, left-43, y, this, 1, dir,50));
	}
	void Interrupt()
	{
		return;
	}
};

void Gun::Update(float time)
{
	if (owner == NULL)
	{
		x = x;
		y = y;
		sprite.setPosition(x, y);
	}
	else
	{
		x = owner->GetX();  //rect.left - êîîðäèíàòà õ
		y = owner->GetY();   //rect.top  - êîîðäèíàòà y
		onGround = false;


		//if (dx > 0) sprite.setTextureRect(IntRect(40 * int(currentFrame), 0, 40, 60));
		//if (dx < 0) sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 0, -40, 60));


		sprite.setPosition(x, y);
		//GetPlayerCoordianteForView(x, y);
	}
}