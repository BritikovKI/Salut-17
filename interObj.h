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
		onGround = false;
		currentFrame = 0;
		speed = 0;
		name = Name;
	};
	
	virtual FloatRect getRect()
	{
		return FloatRect(x, y, w, h);
	}


	virtual void Update(float time, bool) = 0;

	String GetName()
	{
		return name;
	}
	Sprite GetS()
	{
		return sprite;
	}
};

class Player : public interObj
{
	enum { left, right, up, down, jump, stay } state;
	float count_time;
	bool dang; // флаг для выбора анимации;
public:
	Player(String P, String Name, Level &lev, int W, int H, float X, float Y) : interObj(P, Name, W, H, X, Y)
	{
		obj = lev.GetAllObjects();
		count_time = 0;
		dang = false;
	}
	void Update(float time, bool danger);
	void Collision(float Dx, float Dy);
	void Control();
	bool Interrupt(interObj* obj, float time);
	void Animation(float time, bool danger);
};
void Player::Animation(float time, bool danger)
{
	if (danger == false) {
		currentFrame += 0.008*time;
		if (currentFrame > 4) currentFrame -= 4;

		if (dx>0) sprite.setTextureRect(IntRect(40 * int(currentFrame), 0, 40, 60));
		if (dx<0) sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 0, -40, 60));
	}
	else {
		currentFrame += 0.008*time;
		if (currentFrame > 8) currentFrame -= 4;

		if (dx>0) sprite.setTextureRect(IntRect(40 * int(currentFrame), 0, 40, 60));
		if (dx<0) sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 0, -40, 60));
	}
	
}
void Player::Update(float time, bool danger)
{
	Control();
	switch (state)
	{
	case right:dx = speed; break;
	case left:dx = -speed; break;
	case up: break;
	case down: dx = 0; break;
	case stay: break;
	}
	x += dx * time;  //rect.left - координата х
	Collision(dx, 0);   //обработка столкновений по х

	if (!onGround) dy = dy + 0.0005*time;
	y += dy*time;   //rect.top  - координата y
	onGround = false;
	Collision(0, dy); //обработка столкновений по у

	Animation(time, danger);
	/*currentFrame += 0.008*time;
	if (currentFrame > 4) currentFrame -= 4;

	if (dx>0) sprite.setTextureRect(IntRect(40 * int(currentFrame), 0, 40, 60));
	if (dx<0) sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 0, -40, 60));*/


	sprite.setPosition(x, y);
	GetPlayerCoordianteForView(x, y);

	state = stay;
	dx = 0; //для остановки персонажа
}
void Player::Collision(float Dx, float Dy)
{
	for (int i = 0; i < obj.size(); i++)
	{//проходимся по объектам 
		if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		{
			if (obj[i].name == "solid")//если встретили препятствие
			{
				if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx > 0) { x = obj[i].rect.left - w; }
				if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
			}

		}
	}

}
bool Player::Interrupt(interObj* object, float time)
{
	count_time += time;
	//std::cout << count_time << "\n";
	if (getRect().intersects(object->getRect())) {
		if (object->GetName() == "enemy"  && !dang) {
			std::cout << "ok" << std::endl;
			count_time = 0;
			dang = true;
		}
	}
	if (count_time > 15000)
		dang = false;

	return dang;
}
void Player::Control() {
	 
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			state = left; 
			speed = 0.1;
			//dx = -0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			state = right; 
			speed = 0.1;
			//dx = 0.1;
		}
	

		if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) {
			state = jump; 
			dy = -0.35; onGround = false;
		}

		/*if (Keyboard::isKeyPressed(Keyboard::Down)) {
			state = down;
		}*/
	
}

class Enemy : public interObj
{
	int moveTimer;
public:
	Enemy(String P, String Name, Level &lev, int W, int H, float X, float Y) : interObj(P, Name, W, H, X, Y) {
		dx = 0.1; moveTimer = 0;
		dy = 0;
		obj = lev.GetAllObjects();
		sprite.setTextureRect(IntRect(40 * 4, 0, 40, 60));
	}
	void Update(float time, bool);
	void Collision(float Dx, float Dy);
	

};
void Enemy::Update(float time, bool danger)
{
	x += dx * time;  //rect.left - координата х
	Collision(dx, 0);   //обработка столкновений по х

	if (!onGround) dy = dy + 0.0005*time;
	y += dy*time;   //rect.top  - координата y
	onGround = false;
	Collision(0, dy); //обработка столкновений по у


	currentFrame += 0.008*time;
	if (currentFrame > 8) currentFrame -= 4;

	if (dx>0) sprite.setTextureRect(IntRect(40 * int(currentFrame), 0, 40, 60));
	if (dx<0) sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 0, -40, 60));


	sprite.setPosition(x, y);
	//GetPlayerCoordianteForView(x, y);
}
void Enemy::Collision(float Dx, float Dy)
{
	for (int i = 0; i<obj.size(); i++)//проходимся по объектам
		if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		{
			if (obj[i].name == "solid")//если встретили препятствие
			{
				if (Dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx > 0) { x = obj[i].rect.left - w; dx = -dx; }
				if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; dx = -dx; }
			}

		}
}