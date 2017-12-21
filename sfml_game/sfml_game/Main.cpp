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
	Level lvl;//������� ��������� ������ �������
	lvl.LoadFromFile("map3.tmx");//��������� � ���� �����, ������ ������ � ������� ������� �� �� ����������.
//	int garr = [[198, 5],[]];
	Object player = lvl.GetObject("player");//������ ������ �� ����� �����.������ ���������� ������ � ������ ��� ������ ����
	std::vector<Object> enemies = lvl.GetObjects("enemy");//��� ������� ����� �� tmx ����� �������� � ���� �������
	std::vector<Object> aItems = lvl.GetObjects("aItem");//��� ������� item �� tmx ����� �������� � ���� �������
//������ ������, ���� ���� ������ �������.�������� ������.
	std::list<interObj*>::iterator it;//�������� ����� ��������� �� ��-��� ������

	


		while (true)
	{
		Font font;//����� 
		font.loadFromFile("CyrilicOld.ttf");//�������� ������ ������ ���� ������
		Text text("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
//		text.setColor(Color::Red);//��������� ����� � �������. ���� ������ ��� ������, �� �� ��������� �� �����
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������
		RenderWindow window(VideoMode(1600, 1200), "Test!");
		bool exit = menu(window);
		if (exit == false)
		{
			break;
		}
		

		for (int i = 0; i < enemies.size(); i++)//���������� �� ��������� ����� �������(� ������ �� ������)
			interObjects.push_back(new Enemy("one_more_sprite.png", "enemy", lvl, 40, 60, enemies[i].rect.left, enemies[i].rect.top));//� ���������� � ������ ���� ����� ������ � �����
		String bullets[] = { "fire.png", "bullet.png" };
		for (int i = 0; i < aItems.size(); i++)//���������� �� ��������� ����� �������(� ������ �� ������)
			interObjects.push_back(new Gun("weapon_sprites_by_im_not_crying.png", "gun", lvl, 64, 30, aItems[i].rect.left + 1, aItems[i].rect.top, NULL, 198 + (64 * i), 5, 50 * (i + 1)*(i + 1), bullets[i], (500 * (i))+(50*(i+1)),(40*i)+10));//� ���������� � ������ ���� ����� ������ � �����


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
					(*it)->Update(time); //��� ���� ��������� ������(���� ��� ������ �����,�� ����� ���� � ���� � �������) ���������� �-��� update
				else
				{
					it = interObjects.erase(it);
					continue;
				}//���������� �� ��-��� ������

	//			if ((*it)->getRect().intersects(p.getRect()))//���� ������������� ������� ������� ������������ � �������
	//			{
	////				printf("first OK\n"); //���������
	//				if ((*it)->GetName() == "enemy") {//� ��� ���� ��� ������� EasyEnemy,��..
	//					printf("second OK\n"); // �� ���������
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


			window.setView(view); //��������� ������



			window.clear(Color::White);

			lvl.Draw(window);
			if (p.hGun())
			{
				window.draw(p.Dgun());
			}
			window.draw(p.GetS());
			for (it = interObjects.begin(); it != interObjects.end(); it++) {
				window.draw((*it)->GetS()); //������ entities ������� (������ ��� ������ �����)
			}


			window.display();
		}
	}
	return 0;
}




