#pragma once

class interObj 
{
private:
	float dx, dy;
	FloatRect rect;
	bool onGround;
	String path;
	Image img;
	Texture text;
	Sprite sprite;
	float currentFrame;
public:
	interObj(String p, float sx,float sy,FloatRect r,bool onG,float cuF)
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
	InterObj(void)
	{	};

	virtual void update(float time) = 0;



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