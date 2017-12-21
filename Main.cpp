#include <SFML/Graphics.hpp>
#include "Classes.h"
//#include "Map.h"
#include "View.h"
#include "interObj.h"
#include <vector>
#include <list>
#include <sstream>
#include "TinyXML/tinyxml.h"
#include "level.h"
#include "Item.h"
#include "People.h"
#include "Menu.h"
extern std::vector<Object> obj;
extern std::list<interObj*>  interObjects;
using namespace sf;


int main()
{

	
	//ñîçäàþ ñïèñîê, ñþäà áóäó êèäàòü îáúåêòû.íàïðèìåð âðàãîâ.
	std::list<interObj*>::iterator it;//èòåðàòîð ÷òîáû ïðîõîäèòü ïî ýë-òàì ñïèñêà

	Level lvl;//ñîçäàëè ýêçåìïëÿð êëàññà óðîâåíü
	lvl.LoadFromFile("map3.tmx");//çàãðóçèëè â íåãî êàðòó, âíóòðè êëàññà ñ ïîìîùüþ ìåòîäîâ îí åå îáðàáîòàåò.


	Object player = lvl.GetObject("player");//îáúåêò èãðîêà íà íàøåé êàðòå.çàäàåì êîîðäèíàòû èãðîêó â íà÷àëå ïðè ïîìîùè íåãî
	std::vector<Object> enemies = lvl.GetObjects("enemy");//âñå îáúåêòû âðàãà íà tmx êàðòå õðàíÿòñÿ â ýòîì âåêòîðå
	std::vector<Object> aItems = lvl.GetObjects("aItem");//âñå îáúåêòû item íà tmx êàðòå õðàíÿòñÿ â ýòîì âåêòîðå

	for (int i = 0; i < enemies.size(); i++)//ïðîõîäèìñÿ ïî ýëåìåíòàì ýòîãî âåêòîðà(à èìåííî ïî âðàãàì)
		interObjects.push_back(new Enemy("one_more_sprite.png", "enemy", lvl, 40, 60, enemies[i].rect.left, enemies[i].rect.top));//è çàêèäûâàåì â ñïèñîê âñåõ íàøèõ âðàãîâ ñ êàðòû

	for (int i = 0; i < aItems.size(); i++)//ïðîõîäèìñÿ ïî ýëåìåíòàì ýòîãî âåêòîðà(à èìåííî ïî âðàãàì)
		interObjects.push_back(new Gun("images/weapon_sprites_by_im_not_crying.png", "gun", lvl, 64, 30, aItems[i].rect.left, aItems[i].rect.top, NULL, 198, 5, 50));//è çàêèäûâàåì â ñïèñîê âñåõ íàøèõ âðàãîâ ñ êàðòû

	

	while (true) {
		RenderWindow window(VideoMode(800, 600), "Test!");
		bool exit;
		exit=menu(window);
		if (exit == false)
		{
			break;
		}
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
				break;
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
