#pragma once
bool menu(RenderWindow & window) {
	window.clear();
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images/111.png");
	menuTexture2.loadFromFile("images/222.png");
	menuTexture3.loadFromFile("images/333.png");
	aboutTexture.loadFromFile("images/about.jpg");
	menuBackground.loadFromFile("images/Motherland.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	about.setScale(1.56*2, 1.17*2);
	menu1.setPosition(1000, 30);
	menu2.setPosition(1000, 120);
	menu3.setPosition(1000, 210);
	menuBg.setPosition(0, 0);
	menu1.setScale(2, 2);
	menu2.setScale(2, 2);
	menu3.setScale(2, 2);
	menuBg.setScale(2, 2);
	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		//window.clear(Color(220, 51, 35));

		if (IntRect(1000, 30, 400, 60).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Red); menuNum = 1; }
		if (IntRect(1000, 120, 400, 60).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Red); menuNum = 2; }
		if (IntRect(1000, 210, 400, 60).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Red); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) { isMenu = false; return true; }//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape));  }
			if (menuNum == 3) { window.close(); isMenu = false; return false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
	////////////////////////////////////////////////////
}