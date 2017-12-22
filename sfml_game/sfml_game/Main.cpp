#include <SFML/Graphics.hpp>
#include "Classes.h"
//#include "Map.h"
#include "Menu.h"
#include "View.h"
#include "interObj.h"
#include <vector>
#include <list>
#include "TinyXML/tinyxml.h"
#include "level.h"
#include "Item.h"
#include "People.h"

extern std::vector<Object> obj;
extern std::list<interObj*>  interObjects;
using namespace sf;


int main()
{
	Level lvl;//создали экземпляр класса уровень
	lvl.LoadFromFile("map3.tmx");//загрузили в него карту, внутри класса с помощью методов он ее обработает.
//	int garr = [[198, 5],[]];
	Object player = lvl.GetObject("player");//объект игрока на нашей карте.задаем координаты игроку в начале при помощи него
	std::vector<Object> enemies = lvl.GetObjects("enemy");//все объекты врага на tmx карте хранятся в этом векторе
	std::vector<Object> aItems = lvl.GetObjects("aItem");//все объекты item на tmx карте хранятся в этом векторе
//создаю список, сюда буду кидать объекты.например врагов.
	std::list<interObj*>::iterator it;//итератор чтобы проходить по эл-там списка

	


		while (true)
	{
		Font font;//шрифт 
		font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
		Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
//		text.setColor(Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
		RenderWindow window(VideoMode(1600, 1200), "Test!");
		bool exit = menu(window);
		if (exit == false)
		{
			break;
		}
		

		for (int i = 0; i < enemies.size(); i++)//проходимся по элементам этого вектора(а именно по врагам)
			interObjects.push_back(new Enemy("one_more_sprite.png", "enemy", lvl, 40, 60, enemies[i].rect.left, enemies[i].rect.top));//и закидываем в список всех наших врагов с карты
		String bullets[] = { "fire.png", "bullet.png" };
		for (int i = 0; i < aItems.size(); i++)//проходимся по элементам этого вектора(а именно по врагам)
			interObjects.push_back(new Gun("weapon_sprites_by_im_not_crying.png", "gun", lvl, 64, 30, aItems[i].rect.left + 1, aItems[i].rect.top, NULL, 198 + (64 * i), 5, 50 * (i + 1)*(i + 1), bullets[i], (500 * (i))+(50*(i+1)),(40*i)+10));//и закидываем в список всех наших врагов с карты


		Player p("images/sp_with_danger.png", "Player1", lvl, 40, 60, player.rect.left, player.rect.top, 100, 1);



		Clock clock;

		RectangleShape rectangle(Vector2f(32, 32));

		while (window.isOpen())
		{
			float time = clock.getElapsedTime().asMicroseconds();
			clock.restart();

			time = time / 700;


			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}



			p.Update(time);
			if (!p.GetState())
			{
				break;
			}
			for (it = interObjects.begin(); it != interObjects.end(); ) {
				if ((*it)->GetState())
					(*it)->Update(time); //для всех элементов списка(пока это только враги,но могут быть и пули к примеру) активируем ф-цию update
				else
				{
					it = interObjects.erase(it);
					continue;
				}//проходимся по эл-там списка

	//			if ((*it)->getRect().intersects(p.getRect()))//если прямоугольник спрайта объекта пересекается с игроком
	//			{
	////				printf("first OK\n"); //выводится
	//				if ((*it)->GetName() == "enemy") {//и при этом имя объекта EasyEnemy,то..
	//					printf("second OK\n"); // не выводится
	//					p.GetHit(10);
	//					
	//				}
	//				if ((*it)->GetName() == "gun") {
	//					(*it)->Append(&p);
	//					//it=interObjects.erase(it);
	//					
	//					p.setGun(*it);
	//				}
	//				if ((*it)->GetName() == "bullet")
	//				{
	//					printf("Bullet\n");
	//					it = interObjects.erase(it);
	//					continue;
	//				}
	//			}
				it++;
			}


			window.setView(view); //ожимвляем камеру



			window.clear(Color::White);

			lvl.Draw(window);
			if (p.hGun())
			{
				window.draw(p.Dgun());
			}
			window.draw(p.GetS());
			for (it = interObjects.begin(); it != interObjects.end(); it++) {
				window.draw((*it)->GetS()); //рисуем entities объекты (сейчас это только враги)
			}


			window.display();
		}
	}
	return 0;
}




