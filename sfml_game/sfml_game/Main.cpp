#include <SFML/Graphics.hpp>
#include "Classes.h"
//#include "Map.h"
#include "View.h"
#include "interObj.h"
#include <vector>
#include <list>
#include "TinyXML/tinyxml.h"
#include "level.h"
#include "Item.h"
#include "People.h"


using namespace sf;


int main()
{
	RenderWindow window(VideoMode(800, 600), "Test!"); 
	std::list<interObj*>  interObjects;//создаю список, сюда буду кидать объекты.например врагов.
	std::list<interObj*>::iterator it;//итератор чтобы проходить по эл-там списка
	
	Level lvl;//создали экземпл€р класса уровень
	lvl.LoadFromFile("map3.tmx");//загрузили в него карту, внутри класса с помощью методов он ее обработает.


	Object player = lvl.GetObject("player");//объект игрока на нашей карте.задаем координаты игроку в начале при помощи него
	std::vector<Object> enemies = lvl.GetObjects("enemy");//все объекты врага на tmx карте хран€тс€ в этом векторе
	std::vector<Object> aItems = lvl.GetObjects("aItem");//все объекты item на tmx карте хран€тс€ в этом векторе

	for (int i = 0; i < enemies.size(); i++)//проходимс€ по элементам этого вектора(а именно по врагам)
		interObjects.push_back(new Enemy("one_more_sprite.png", "enemy", lvl,  40, 60, enemies[i].rect.left, enemies[i].rect.top));//и закидываем в список всех наших врагов с карты

	for (int i = 0; i < aItems.size(); i++)//проходимс€ по элементам этого вектора(а именно по врагам)
		interObjects.push_back(new Gun("weapon_sprites_by_im_not_crying.png", "gun", lvl, 10, 20, aItems[i].rect.left, aItems[i].rect.top,NULL));//и закидываем в список всех наших врагов с карты


	Player p("one_more_sprite.png", "Player1", lvl, 40, 60, player.rect.left, player.rect.top,100,1);
	


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
		for (it = interObjects.begin(); it != interObjects.end(); ) { 
			(*it)->Update(time); //дл€ всех элементов списка(пока это только враги,но могут быть и пули к примеру) активируем ф-цию update
														//проходимс€ по эл-там списка
		
			if ((*it)->getRect().intersects(p.getRect()))//если пр€моугольник спрайта объекта пересекаетс€ с игроком
			{
				printf("first OK\n"); //выводитс€
				if ((*it)->GetName() == "enemy") {//и при этом им€ объекта EasyEnemy,то..
					printf("second OK\n"); // не выводитс€
					p.GetHit(10);
					
				}
				if ((*it)->GetName() == "gun") {
					(*it)->Append(&p);
					//it=interObjects.erase(it);
					printf("Gun");
//					p.setGun(*it);
				}
			}
			it++;
		}
																				

		window.setView(view); //ожимвл€ем камеру



		window.clear(Color::White);

		lvl.Draw(window);
		window.draw(p.GetS());
		for (it = interObjects.begin(); it != interObjects.end(); it++) {
			window.draw((*it)->GetS()); //рисуем entities объекты (сейчас это только враги)
		}

		
		window.display();
	}

	return 0;
}




