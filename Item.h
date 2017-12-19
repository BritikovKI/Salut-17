#pragma once
#include "Classes.h"
#include <vector>
using namespace sf;

class Item {
	
	int dir;

	String File; // файл с расширением
	Image image; // сфмл изображение
	Texture texture;
	Sprite sprite;
public:
	float x, y;
	float w, h;
	Item() {

	};
	float getx()
	{
		return x;
	}
	float gety()
	{
		return y;
	}
	Item(String F, int X, int Y, float W, float H)
	{
		File = F;
		w = W; h = H;
		image.loadFromFile(File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y; // координата появления спрайта
		sprite.setTextureRect(IntRect(w, h, w, h));
	}
	Item(String F)
	{
		File = F;
		image.loadFromFile(File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);// координата появления спрайта
	}
	void SetCoords(int X, int Y, float W, float H,int d)
	{
		if (dir != d)
		{
			dir = d;
			if (dir == 0)
			{
				File = "ak47.2.png";
				image.loadFromFile(File);
				texture.loadFromImage(image);
				sprite.setTexture(texture);
			}
			if(dir==1)
			{
				File = "ak47.1.png";
				image.loadFromFile(File);
				texture.loadFromImage(image);
				sprite.setTexture(texture);
			}
		}
		w = W; h = H;
		x = X; y = Y; // координата появления спрайта
		sprite.setTextureRect(IntRect(w, h, w, h));
	}
	void sp()
	{
		sprite.setPosition(x, y);
	}
	Sprite GetSpr()
	{
		return sprite;
	}
	int gd()
	{
		return dir;
	}
};

class Gun;

class Bullet :Item
{
	float speed;
	int dir;
	int dx;
	int dy;
public:
	friend Gun;
	Bullet(String F, int X, int Y, float W, float H,int d) :Item(F, X,Y,W,H) {//всё так же, только взяли в конце состояние игрока (int dir)
		speed = 0.8;
		dir = d;
		//выше инициализация в конструкторе
	}
	Bullet() {};
	Sprite GetGSpr()
	{
		return Item::GetSpr();
	}
	void update(float time)
	{
		switch (dir)
		{
		case 0: dx = -speed; dy = 0;   break;//интовое значение state = left
		case 1: dx = speed; dy = 0;   break;//интовое значение state = right
		case 2: dx = 0; dy = -speed;   break;//интовое значение state = up
		case 3: dx = 0; dy = -speed;   break;//интовое значение не имеющее отношения к направлению, пока просто стрельнем вверх, нам сейчас это не важно
		case 4: dx = 0; dy = -speed;   break;//интовое значение не имеющее отношения к направлению, пока просто стрельнем вверх, нам сейчас это не важно
		case 5: dx = 0; dy = -speed;   break;//интовое значение не имеющее отношения к направлению, пока просто стрельнем вверх, нам сейчас это не важно
		case 6: dx = speed; dy = -speed;   break;//интовое значение state = right_Top

		}

		Item::x += dx*time;//само движение пули по х
		Item::y += dy*time;//по у

		if (x <= 0) x = 1;// задержка пули в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки
		if (y <= 0) y = 1;

		//for (int i = 0; i < obj.size(); i++) {//проход по объектам solid
		//	if (getRect().intersects(obj[i].rect)) //если этот объект столкнулся с пулей,
		//	{
		//		life = false;// то пуля умирает
		//	}
		//}
		x = x + w / 2;
		y = y + h / 2;
		Item::sp();//задается позицию пуле
		x -= w / 2;
		y -= h / 2;
		
	}
};



class Gun:Item {
	String Flash;
	Image iFlash;
	Texture tFlash;
	Sprite sFlash;
	int bspeed=0.1;
	int dx, dy;
public:
	friend class Player;
	Gun():Item()
	{

	};
	Gun(String F, int X, int Y, float W, float H,String F1, String F2) :Item(F,X,Y,W,H)
	{

		Flash = F2;
		iFlash.loadFromFile(Flash);
		tFlash.loadFromImage(iFlash);
		sFlash.setTexture(tFlash);
		// координата появления спрайта
//		sShotF.setTextureRect(IntRect(w, h, w, h));
	}
	Gun(String F,String F1, String F2) :Item(F)
	{

		Flash = F2;
		iFlash.loadFromFile(Flash);
		tFlash.loadFromImage(iFlash);
		sFlash.setTexture(tFlash);
		// координата появления спрайта
		//		sShotF.setTextureRect(IntRect(w, h, w, h));
	}
	void SetCoords(int X, int Y, float W, float H,int d)
	{
		Item::SetCoords( X,  Y, W, H,d);// координата появления спрайта

	}
	void sp()
	{
		Item::sp();
	}
	void shot(std::vector<Sprite> arr)
	{
		Bullet K("explosion1.png", Item::x, Item::y, w, h, Item::gd());
		arr.push_back(K.GetSpr());
	}
	Sprite GetGSpr()
	{
		return Item::GetSpr();
	}
};