#pragma once
#include "interObj.h"
#include "level.h"
using namespace sf;
extern std::list<interObj*>  interObjects;
extern std::vector<Object> obj;
class Item :public interObj
{
protected:
	interObj *owner = NULL;
public:
	Item(String p, String name, Level &lev, int W, int H, float X, float Y, interObj* par) :interObj(p, name, W, H, X, Y)
	{

		owner = par;
		obj = lev.GetAllObjects();

	}
	void Update(float time)
	{
		if (owner == NULL)
		{
			x = x;
			y = y;
			sprite.setPosition(x, y);
		}

	}
};

class ActiveItem :public Item
{
protected:
	bool weared = false;
public:
	ActiveItem(String p, String name, Level &lev, int W, int H, float X, float Y, interObj * par) :Item(p, name, lev, W, H, X, Y, par)
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
		if (owner != NULL && weared == true)
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
	int img_x;
	int img_y;
	int st_pos = 0;
	int range = 0;

public:
	Bullet(String p, String name, Level &lev, int W, int H, float X, float Y, interObj * par, int spd, int direct, int rg, int sx, int sy, int dmg) :ActiveItem(p, name, lev, W, H, X, Y, par)
	{
		damage = dmg;
		img_x = sx;
		img_y = sy;
		sprite.setTextureRect(IntRect(sx, sy, W, H));
		range = rg;
		dir = direct;
		speed = spd;
		st_pos = x;
	}
	~Bullet()
	{}
	Sprite Draw(float x, float y, int dir)
	{
		return sprite;
	}
	bool Collision(float Dx, float Dy)
	{
		for (int i = 0; i<obj.size(); i++)//ïðîõîäèìñÿ ïî îáúåêòàì
			if (getRect().intersects(obj[i].rect))//ïðîâåðÿåì ïåðåñå÷åíèå èãðîêà ñ îáúåêòîì
			{
				if (obj[i].name == "solid")//åñëè âñòðåòèëè ïðåïÿòñòâèå
				{
					onLevel = false;
					return false;
				}


			}
		return true;
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
		if (dir == 1)
			if (x > range + st_pos)
			{
				onLevel = false;
			}
		if (dir == 0)
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
		printf("%u", dir);
		x += dx*time;//само движение пули по х
		y += dy*time;//по у
		bool exists;
		exists = Collision(dx, dy);
		Interrupt();
		if (x <= 0) x = 1;// задержка пули в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки
		if (y <= 0) y = 1;

		//for (int i = 0; i < obj.size(); i++) {//проход по объектам solid
		//	if (getRect().intersects(obj[i].rect)) //если этот объект столкнулся с пулей,
		//	{
		//		onGround = false;// то пуля умирает
		//	}
		//}
		if (exists == true)
			sprite.setPosition(x, y);//задается позицию пуле
	}
	void Shoot(Level &lev, int dir, int x, int y ) { return; }
};


class Gun :public ActiveItem
{
	int direct;
	int img_x;
	int img_y;
	int range;

	String bullet;
	SoundBuffer shootBuffer;//создаём буфер для звука
	
	Sound shoot;//создаем звук и загружаем в него звук из буфера
public:
	Gun(String p, String name, Level &lev, int W, int H, float X, float Y, interObj * par, int i_x, int i_y, int ra, String bul, float t, int dmg, String sound_path) :ActiveItem(p, name, lev, W, H, X, Y, par)
	{

		img_x = 0;
		img_y = 0;
		range = 0;
		time = t;
		range = ra;
		img_x = i_x;
		bullet = bul;
		//std::cout << static_cast<std::string>(bullet) << std::endl;
		img_y = i_y;
		sprite.setTextureRect(IntRect(i_x, i_y, W, H));
		sprite.setScale(0.5, 0.5);
		damage = dmg;
		shootBuffer.loadFromFile(sound_path);//загружаем в него звук
		shoot = Sound(shootBuffer);
	};
	void Update(float time);

	Sprite Draw(float xg, float yg, int dir)
	{
		direct = dir;
		if (direct == 1) {
			sprite.setTextureRect(IntRect(img_x, img_y, w, h));
			x = xg + 15;  //rect.left - êîîðäèíàòà õ
			y = yg + 15;//rect.top  - êîîðäèíàòà y
		}

		else
		{
			sprite.setTextureRect(IntRect(img_x + w, img_y, -w, h));
			x = xg - 8;
			y = yg + 15;
		}
		sprite.setPosition(x, y);
		return sprite;
	}
	void Shoot(Level &lev, int dir, int left, int right)
	{

		direct = dir;
		if (dir == 1)
		{
			interObjects.push_back(new Bullet(bullet, "bullet", lev, 20, 10, right + 5, y, this, 1, dir, range, 15, 15, damage));
				shoot.play();
			

		}
		else
		{
			interObjects.push_back(new Bullet(bullet, "bullet", lev, 20, 10, left - 25, y, this, 1, dir, range, 15, 15, damage));
				shoot.play();
			
		}

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





		sprite.setPosition(x, y);
		//GetPlayerCoordianteForView(x, y);
	}
}