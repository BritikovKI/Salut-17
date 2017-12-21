#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
View view; // объект вид, €вл€ющийс€ камерой
View GetPlayerCoordianteForView(float x, float y) //ф-и€ считывани€ координат игрока
{
	float TempX = x, TempY = y;
	if (x < 200) TempX = 200;
	if (x > 3650) TempX = 3650; // обработать позже, поскольку карта будет расшир€тьс€
	if (y < 160) TempY = 160;
	if (y > 650) TempY = 650;

	view.setSize(400, 320); //400 320
	view.setCenter(TempX, TempY); // следим за игроком
	return view; // возвращаем нашу камеру, что обновл€ет ее
}
//View ViewMap(float time)
//{
//	if (Keyboard::isKeyPressed(Keyboard::D))
//	{
//		view.move(0.1*time, 0);
//	}
//	if (Keyboard::isKeyPressed(Keyboard::A))
//	{
//		view.move(-0.1*time, 0);
//	}
//	if (Keyboard::isKeyPressed(Keyboard::S))
//	{
//		view.move(0, 0.1*time);
//	}
//	if (Keyboard::isKeyPressed(Keyboard::W))
//	{
//		view.move(0, -0.1*time);
//	}
//	return view;
//}
//View ChangeView()
//{
//	if (Keyboard::isKeyPressed(Keyboard::U))
//	{
//		view.zoom(1.0100f);
//	}
//	return view;
//}