#include "interObj.h"

extern std::list<interObj*>  interObjects;

class Player : public interObj
{
	int HP = 100;
	int Skill = 1;
	Level l;
	enum { left, right, up, down, jump, stay, shoot } state;
	interObj *uG;
	int dir = 1;
public:
	Player(String P, String Name, Level &lev, int W, int H, float X, float Y, int Health, int Sk) : interObj(P, Name, W, H, X, Y)
	{
		uG = NULL;
		HP = Health;
		Skill = Sk;
		obj = lev.GetAllObjects();
		l = lev;
	}
	void Append(interObj *pl)
	{
		return;
	}
	void Update(float time);
	void Interrupt();
	void Collision(float Dx, float Dy);
	void Control();
	void Shoot(Level &lev, int dir)
	{
		return;
	}
	void GetHit(int HPL) {
		HP -= 10;
		std::cout << HP;
	};
	void setGun(interObj *m)
	{
		uG = m;
		m->Append(this);
	}
};

void Player::Update(float time)
{
	Control();
	switch (state)
	{
	case right:dx = speed; dir = 1; break;
	case left:dx = -speed; dir = 0; break;
	case up: break;
	case down: dx = 0; break;
	case stay: break;
	case shoot: if(uG!=NULL)uG->Shoot(l,dir);
	}
	x += dx * time;  //rect.left - координата х
	Collision(dx, 0);   //обработка столкновений по х

	if (!onGround) dy = dy + 0.0005*time;
	y += dy*time;   //rect.top  - координата y
	onGround = false;
	Collision(0, dy);
	Interrupt(); //обработка столкновений по у
	

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

	for (int i = 0; i<obj.size(); i++)//ïðîõîäèìñÿ ïî îáúåêòàì
		if (getRect().intersects(obj[i].rect))//ïðîâåðÿåì ïåðåñå÷åíèå èãðîêà ñ îáúåêòîì
		{
			if (obj[i].name == "solid")//åñëè âñòðåòèëè ïðåïÿòñòâèå
			{
				if (Dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx>0) { x = obj[i].rect.left - w; }
				if (Dx<0) { x = obj[i].rect.left + obj[i].rect.width; }
			}


		}
}
void Player::Interrupt()
{
	String name;
	for (std::list<interObj*>::iterator i = interObjects.begin(); i != interObjects.end(); ) {//проходимся по объектам
		name = (*i)->GetName();
		if (getRect().intersects((*i)->getRect()))//проверяем пересечение игрока с объектом
		{
			if ((*i)->GetName() == "solid")//если встретили препятствие
			{
				if (dy > 0) { 
					y = (*i)->getRect().top - h;  dy = 0; onGround = true; }
				if (dy < 0) {
					y = (*i)->getRect().top + (*i)->getRect().height;   dy = 0; }
				if (dx > 0) { 
					x = (*i)->getRect().left - w; dx = -dx; }
				if (dx < 0) { 
					x = (*i)->getRect().left + (*i)->getRect().width; dx = -dx; }
			}
			
			if ((*i)->GetName() == "bullet")
			{
				HP -= 10;
				if (HP <= 0)
				{
					std::cout << "GameOver\n";
				}
				i = interObjects.erase(i);
				continue;
			}


		}
		i++;
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
	if ((Keyboard::isKeyPressed(Keyboard::Space))) {
		state = shoot;

	}
	/*if (Keyboard::isKeyPressed(Keyboard::Down)) {
	state = down;
	}*/

}

class Enemy : public interObj
{
	int HP = 100;
	int level = 0;
	int moveTimer;
public:
	Enemy(String P, String Name, Level &lev, int W, int H, float X, float Y) : interObj(P, Name, W, H, X, Y) {
		dx = 0.1; moveTimer = 0;
		dy = 0;
		obj = lev.GetAllObjects();
		sprite.setTextureRect(IntRect(40 * 4, 0, 40, 60));
	}
	void GetHit(int HPL) {
		HP -= 10;
		std::cout << HP;
	};
	void Shoot(Level &lev, int dir)
	{
		return;
	}
	void Update(float time);
	void Collision(float Dx, float Dy);
	void Interrupt();
	void Append(interObj *pl)
	{
		return;
	}

};
void Enemy::Update(float time)
{
	x += dx * time;  //rect.left - êîîðäèíàòà õ
	Collision(dx, 0);   //îáðàáîòêà ñòîëêíîâåíèé ïî õ

	if (!onGround) dy = dy + 0.0005*time;
	y += dy*time;   //rect.top  - êîîðäèíàòà y
	onGround = false;
	Collision(0, dy); //îáðàáîòêà ñòîëêíîâåíèé ïî ó
	Interrupt();

	currentFrame += 0.008*time;
	if (currentFrame > 8) currentFrame -= 4;

	if (dx>0) sprite.setTextureRect(IntRect(40 * int(currentFrame), 0, 40, 60));
	if (dx<0) sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 0, -40, 60));


	sprite.setPosition(x, y);
	//GetPlayerCoordianteForView(x, y);
}
void Enemy::Interrupt()
{
	String name;
	for (std::list<interObj*>::iterator i = interObjects.begin(); i != interObjects.end(); ) {//проходимся по объектам
		name = (*i)->GetName();
		if (getRect().intersects((*i)->getRect()))//проверяем пересечение игрока с объектом
		{

			if ((*i)->GetName() == "bullet")
			{
				HP -= 10;
				if (HP <= 0)
				{
					std::cout << "GameOver\n";
				}
				i = interObjects.erase(i);
				continue;
			}



		}
		i++;
	}
}
void Enemy::Collision(float Dx, float Dy)
{
	for (int i = 0; i<obj.size(); i++)//ïðîõîäèìñÿ ïî îáúåêòàì
		if (getRect().intersects(obj[i].rect))//ïðîâåðÿåì ïåðåñå÷åíèå èãðîêà ñ îáúåêòîì
		{
			if (obj[i].name == "solid")//åñëè âñòðåòèëè ïðåïÿòñòâèå
			{
				if (Dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx > 0) { x = obj[i].rect.left - w; dx = -dx; }
				if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; dx = -dx; }
			}


		}
}