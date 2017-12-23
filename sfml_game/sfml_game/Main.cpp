//#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
	Level lvl;//ñîçäàëè ýêçåìïëÿð êëàññà óðîâåíü
	lvl.LoadFromFile("map3.tmx");//çàãðóçèëè â íåãî êàðòó, âíóòðè êëàññà ñ ïîìîùüþ ìåòîäîâ îí åå îáðàáîòàåò.
								 //	int garr = [[198, 5],[]];
	Object player = lvl.GetObject("player");//îáúåêò èãðîêà íà íàøåé êàðòå.çàäàåì êîîðäèíàòû èãðîêó â íà÷àëå ïðè ïîìîùè íåãî
	std::vector<Object> enemies = lvl.GetObjects("enemy");//âñå îáúåêòû âðàãà íà tmx êàðòå õðàíÿòñÿ â ýòîì âåêòîðå
	std::vector<Object> aItems = lvl.GetObjects("aItem");//âñå îáúåêòû item íà tmx êàðòå õðàíÿòñÿ â ýòîì âåêòîðå
														 //ñîçäàþ ñïèñîê, ñþäà áóäó êèäàòü îáúåêòû.íàïðèìåð âðàãîâ.
	std::list<interObj*>::iterator it;//èòåðàòîð ÷òîáû ïðîõîäèòü ïî ýë-òàì ñïèñêà




	while (true)
	{
		
		RenderWindow window(VideoMode(800, 600), "RHA!");
		bool exit = menu(window);
		if (exit == false) 
		{
			break;
		}
		Music music;//создаем объект музыки
		music.openFromFile("sounds/main_theme.wav");//загружаем файл
		music.setVolume(25);
		music.play();//воспроизводим музыку

		for (int i = 0; i < enemies.size(); i++)//ïðîõîäèìñÿ ïî ýëåìåíòàì ýòîãî âåêòîðà(à èìåííî ïî âðàãàì)
			interObjects.push_back(new Enemy("one_more_sprite.png", "enemy", lvl, 40, 60, enemies[i].rect.left, enemies[i].rect.top));//è çàêèäûâàåì â ñïèñîê âñåõ íàøèõ âðàãîâ ñ êàðòû
		String bullets[] = { "images/fire.png", "images/bullet_black.png" };
		String sounds[] = {"sounds/m4a1-1.wav"  ,"sounds/ak47-2.wav" };
		for (int i = 0; i < aItems.size(); i++)//ïðîõîäèìñÿ ïî ýëåìåíòàì ýòîãî âåêòîðà(à èìåííî ïî âðàãàì)
			interObjects.push_back(new Gun("images/weapon_sprites_by_im_not_crying.png", "gun", lvl, 64, 30, aItems[i].rect.left + 1, aItems[i].rect.top, NULL, 198 + (64 * i), 5, 50 * (i + 1)*(i + 1), bullets[i], (500 * (i)) + (50 * (i + 1)), (40 * i) + 10, sounds[i]));//è çàêèäûâàåì â ñïèñîê âñåõ íàøèõ âðàãîâ ñ êàðòû


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
					(*it)->Update(time); //äëÿ âñåõ ýëåìåíòîâ ñïèñêà(ïîêà ýòî òîëüêî âðàãè,íî ìîãóò áûòü è ïóëè ê ïðèìåðó) àêòèâèðóåì ô-öèþ update
				else
				{
					it = interObjects.erase(it);
					continue;
				}
				it++;
			}


			window.setView(view); //îæèìâëÿåì êàìåðó



			window.clear(Color::White);

			lvl.Draw(window);
			if (p.hGun())
			{
				window.draw(p.Dgun());
			}
			window.draw(p.GetS());
			for (it = interObjects.begin(); it != interObjects.end(); it++) {
				window.draw((*it)->GetS()); //ðèñóåì entities îáúåêòû (ñåé÷àñ ýòî òîëüêî âðàãè)
			}


			window.display();
		}
	}
	return 0;
}
