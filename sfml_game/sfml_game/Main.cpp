#include <SFML/Graphics.hpp>
#include "Classes.h"
//#include "Map.h"
#include "View.h"
#include "interObj.h"
#include <vector>
#include <list>
#include "TinyXML/tinyxml.h"
#include "level.h"



using namespace sf;


int main()
{
	RenderWindow window(VideoMode(800, 600), "Test!");
	std::list<interObj*>  interObjects;//������ ������, ���� ���� ������ �������.�������� ������.
	std::list<interObj*>::iterator it;//�������� ����� ��������� �� ��-��� ������

	Level lvl;//������� ��������� ������ �������
	lvl.LoadFromFile("map3.tmx");//��������� � ���� �����, ������ ������ � ������� ������� �� �� ����������.


	Object player = lvl.GetObject("player");//������ ������ �� ����� �����.������ ���������� ������ � ������ ��� ������ ����
	std::vector<Object> enemies = lvl.GetObjects("enemy");//��� ������� ����� �� tmx ����� �������� � ���� �������


	for (int i = 0; i < enemies.size(); i++)//���������� �� ��������� ����� �������(� ������ �� ������)
		interObjects.push_back(new Enemy("one_more_sprite.png", "enemy", lvl, 40, 60, enemies[i].rect.left, enemies[i].rect.top));//� ���������� � ������ ���� ����� ������ � �����

	Player p("one_more_sprite.png", "Player1", lvl, 40, 60, player.rect.left, player.rect.top);



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
		for (it = interObjects.begin(); it != interObjects.end(); it++) { (*it)->Update(time); }//��� ���� ��������� ������(���� ��� ������ �����,�� ����� ���� � ���� � �������) ���������� �-��� update



		window.setView(view); //��������� ������



		window.clear(Color::White);

		lvl.Draw(window);
		window.draw(p.GetS());
		for (it = interObjects.begin(); it != interObjects.end(); it++) {
			window.draw((*it)->GetS()); //������ entities ������� (������ ��� ������ �����)
		}
		window.display();
	}

	return 0;
}




