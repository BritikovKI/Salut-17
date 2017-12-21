#include "interObj.h"
extern std::vector<Object> obj;
extern std::list<interObj*>  interObjects;

class Player : public interObj
{
	float shtimer = 0;
	float chtimer = 0;
	float coltime;
	int HP = 100;
	int Skill = 1;
	bool dang;
	Level l;
	enum { left, right, up, down, jump, stay, shoot, change,shootR,shootL } state;
	std::vector<interObj*> uG;
	int gun_n = 0;
	int dir = 1;
public:
	Player(String P, String Name, Level &lev, int W, int H, float X, float Y, int Health, int Sk) : interObj(P, Name, W, H, X, Y)
	{
		coltime = 0;
		HP = Health;
		Skill = Sk;
		obj = lev.GetAllObjects();
		l = lev;
	}

	Sprite Draw(float x, float y, int dir)
	{
		dang = false;
		return sprite;
	}
	void Animation(float time, bool danger);
	void Update(float time);
	void Interrupt(float time);
	void Collision(float Dx, float Dy);
	void Control();
	Sprite Dgun()
	{

			return uG[gun_n]->GetS();
	}
	void Shoot(Level &lev, int dir,int x,int y)
	{
		return;
	};
	void GetHit(int HPL) {
		HP -= 10;
		std::cout << HP;
	};
	bool hGun()
	{
		if( uG.size() > 0)
			return true;
		else
			return false;
	}
	bool setGun(interObj *m)
	{
		
		uG.push_back(m);

		if (uG.size() == 1)
		{
			return true;
		}
		else {
			return false;
		}
	};

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
		if (currentFrame > 4) currentFrame -= 4;

		if (dx>0) sprite.setTextureRect(IntRect(40 * int(currentFrame), 61, 40, 60));
		if (dx<0) sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 61, -40, 60));
	}
	
}
void Player::Update(float time)
{
	chtimer += time;
	shtimer += time;
	Control();
	switch (state)
	{
	case right:dx = speed; dir = 1; break;
	case left:
		dx = -speed; dir = 0; break;
	case up: break;
	case change:
		if (chtimer > 1500) {
			gun_n = (gun_n + 1) % uG.size();
			chtimer = 0;
		} break;
	case stay: break;
	case shoot: if (uG.size() != 0) { if (shtimer > uG[gun_n]->time) { uG[gun_n]->Shoot(l, dir, x, x + w); shtimer = 0; }; break; }
	case shootR:if (uG.size() != 0) { if (shtimer > uG[gun_n]->time) { uG[gun_n]->Shoot(l, dir, x-1, x + w+1); shtimer = 0; }; dx = speed; dir = 1; break; }
	case shootL:if (uG.size() != 0) { if (shtimer > uG[gun_n]->time) { uG[gun_n]->Shoot(l, dir, x-1, x + w+1); shtimer = 0; }; dx = -speed; dir = 0; break; }
	}
	x += dx * time;  //rect.left - координата х
	Collision(dx, 0);   //обработка столкновений по х

	if (!onGround) dy = dy + 0.0005*time;
	y += dy*time;   //rect.top  - координата y
	onGround = false;
	Collision(0, dy);
	Interrupt(time); //обработка столкновений по у


	Animation(time, dang);

	sprite.setPosition(x, y);
	if (uG.size() != 0)
	{
		uG[gun_n]->Draw(x, y,dir);
	}
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
			if (obj[i].name == "finish")
			{
				onLevel = false;
			}


		}
}
void Player::Interrupt(float time)
{
	String name;
	coltime += time;
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
					onLevel = false;
				}
				i = interObjects.erase(i);
				continue;
				
			}
			if ((*i)->GetName() == "gun") {
				bool res = false;
				//it=interObjects.erase(it);

				res=setGun(*i);
				i = interObjects.erase(i);
				continue;

			}
			if ((*i)->GetName() == "enemy" && !dang) {
				std::cout << "ok" << std::endl;
				HP -= 50;
				if (HP < 0)
				{
					onLevel = false;
				}
				coltime = 0;
				dang = true;
			}


		}
		if (coltime > 3000)
			dang = false;
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
	if ((Keyboard::isKeyPressed(Keyboard::Space))&& Keyboard::isKeyPressed(Keyboard::Right)) {
		state = shootR;

	}
	if ((Keyboard::isKeyPressed(Keyboard::Space)) && Keyboard::isKeyPressed(Keyboard::Left)) {
		state = shootL;

	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		state = change;
		
	}

}

class Enemy : public interObj
{
	int HP = 100;
	int level = 0;
	int moveTimer;
public:
	~Enemy();
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
	void Shoot(Level &lev, int dir,int x,int y)
	{
		return;
	}
	void Update(float time);
	void Collision(float Dx, float Dy);
	void Interrupt();
	Sprite Draw(float x, float y, int dir)
	{
		return sprite;
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
				HP -= (*i)->damage;
				if (HP <= 0)
				{
					onLevel = false;
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