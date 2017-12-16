class interObj
{
protected:
	float dx, dy;
	FloatRect rect;
	bool onGround;
	String path;
	Image img;
	Texture text;
	Sprite sprite;
	float currentFrame;
public:
	interObj(String p, float sx, float sy, FloatRect r, bool onG, float cuF)
	{
		path = p;
		img.loadFromFile(path);
		text.loadFromImage(img);
		sprite.setTexture(text);
		dx = sx;
		dy = sy;
		rect = r;
		onGround = onG;
		currentFrame = cuF;
	};


	virtual void Update(float time) = 0;



	void Collision(int dir)
	{
		for (int i = rect.top / 32; i<(rect.top + rect.height) / 32; i++)
			for (int j = rect.left / 32; j<(rect.left + rect.width) / 32; j++)
			{
				if (TileMap[i][j] == 'B' || TileMap[i][j] == 'O' || TileMap[i][j] == 'W')
				{
					if ((dx>0) && (dir == 0)) rect.left = j * 32 - rect.width;
					if ((dx<0) && (dir == 0)) rect.left = j * 32 + 32;
					if ((dy>0) && (dir == 1)) { rect.top = i * 32 - rect.height;  dy = 0;   onGround = true; }
					if ((dy<0) && (dir == 1)) { rect.top = i * 32 + 32;   dy = 0; }
				}

				if (TileMap[i][j] == '0')
				{
					TileMap[i][j] = ' ';
				}

			}

	}
	void SetDx(float _dx)
	{
		dx = _dx;
	}
	void SetDy(float _dy)
	{
		dy = _dy;
	}
	void SetOnGround(bool _onGround)
	{
		onGround = _onGround;
	}
	bool GetOnGround()
	{
		return onGround;
	}
	float GetX()
	{
		return rect.left;
	}
	float GetY()
	{
		return rect.top;
	}
	Sprite GetS()
	{
		return sprite;
	}
};

class Player : public interObj
{
public:
	Player(String p, float sx, float sy, FloatRect r, bool onG, float cuF) : interObj(p, sx, sy, r, onG, cuF){}
	void Update(float time);
};
void Player::Update(float time)
{
	rect.left += dx * time;  //rect.left - координата х
	Collision(0);   //обработка столкновений по х

	if (!onGround) dy = dy + 0.0005*time;
	rect.top += dy*time;   //rect.top  - координата y
	onGround = false;
	Collision(1); //обработка столкновений по у


	currentFrame += 0.008*time;
	if (currentFrame > 4) currentFrame -= 4;

	if (dx>0) sprite.setTextureRect(IntRect(40 * int(currentFrame), 0, 40, 60));
	if (dx<0) sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 0, -40, 60));


	sprite.setPosition(rect.left, rect.top);

	dx = 0; //для остановки персонажа
}

class Enemy : public interObj
{
	int moveTimer;
public:
	Enemy(String p, float sx, float sy, FloatRect r, bool onG, float cuF) : interObj(p, sx, sy, r, onG, cuF) {
		dx = 0.1; moveTimer = 0;
		dy = 0;
	}
	void Update(float time);
	void Collision(int dir, float time)
	{
		for (int i = rect.top / 32; i<(rect.top + rect.height) / 32; i++)
			for (int j = rect.left / 32; j<(rect.left + rect.width) / 32; j++)
			{
				if (TileMap[i][j] == 'B' || TileMap[i][j] == 'O' || TileMap[i][j] == 'W')
				{
					if ((dx > 0) && (dir == 0)) { rect.left = j * 32 - rect.width; }
					if ((dx < 0) && (dir == 0)) { rect.left = j * 32 + 32;  }
					if ((dy>0) && (dir == 1)) { rect.top = i * 32 - rect.height;  dy = 0;   onGround = true; }
					if ((dy<0) && (dir == 1)) { rect.top = i * 32 + 32;   dy = 0; }
				}
				else if (TileMap[i][j] == 'R' && dy == 0 && dx > 0)
				{
					dy = -0.35;
				}
				else if (TileMap[i][j] == 'L' && dy == 0 && dx < 0)
				{
					dy = -0.35;
				}

				if (TileMap[i][j] == '0')
				{
					TileMap[i][j] = ' ';
				}

			}

	}

};
void Enemy::Update(float time)
{
	
	moveTimer += time;
	std::printf("%d",moveTimer); 
	if (moveTimer>8500) { dx *= -1; moveTimer = 0; }
	rect.left += dx * time;  //rect.left - координата х
	Collision(0 , time);   //обработка столкновений по х
	if (!onGround) dy = dy + 0.0005*time;
	rect.top += dy*time;   //rect.top  - координата y
	onGround = false;
	Collision(1, time); //обработка столкновений по у


	currentFrame += 0.008*time;
	if (currentFrame > 8) currentFrame -= 4;

	if (dx>0) sprite.setTextureRect(IntRect(40 * int(currentFrame), 0, 40, 60));
	if (dx<0) sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 0, -40, 60));


	sprite.setPosition(rect.left, rect.top);

	//dx = 0; //для остановки персонажа
}
