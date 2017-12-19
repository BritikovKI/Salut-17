#include "interObj.h"


class Player : public interObj
{
	int HP = 100;
	int Skill = 1;
	enum { left, right, up, down, jump, stay } state;
	//Gun *uG;
public:
	Player(String P, String Name, Level &lev, int W, int H, float X, float Y, int Health, int Sk) : interObj(P, Name, W, H, X, Y)
	{
//		uG = NULL;
		HP = Health;
		Skill = Sk;
		obj = lev.GetAllObjects();
	}
	void Append(interObj *pl)
	{
		return;
	}
	void Update(float time);
	void Collision(float Dx, float Dy);
	void Control();
	void GetHit(int HPL) {
		HP -= 10;
		std::cout << HP;
	};
	//void setGun(Gun *m)
	//{
	//	uG = m;
	//}
};

void Player::Update(float time)
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


	currentFrame += 0.008*time;
	if (currentFrame > 4) currentFrame -= 4;

	if (dx>0) sprite.setTextureRect(IntRect(40 * int(currentFrame), 0, 40, 60));
	if (dx<0) sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 0, -40, 60));

	sprite.setPosition(x, y);
	/*if (uG != NULL)
	{
		uG->Draw(x, y);
	}*/
	GetPlayerCoordianteForView(x, y);

	state = stay;
	dx = 0; //для остановки персонажа
}
void Player::Collision(float Dx, float Dy)
{

	for (int i = 0; i<obj.size(); i++)//проходимся по объектам
		if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		{
			if (obj[i].name == "solid")//если встретили препятствие
			{
				if (Dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx>0) { x = obj[i].rect.left - w; }
				if (Dx<0) { x = obj[i].rect.left + obj[i].rect.width; }
			}


		}
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
	void Update(float time);
	void Collision(float Dx, float Dy);
	void Append(interObj *pl)
	{
		return;
	}

};
void Enemy::Update(float time)
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