//
//  main.cpp
//  fisrt
//
//  Created by Петрос Адамян on 27.10.2017.
//  Copyright © 2017 Петрос Адамян. All rights reserved.
//

#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window( sf::VideoMode( 640, 480 ), "First Game" );
    
    sf::Texture texture; //загрузка текстуры
    
    if( !texture.loadFromFile("/Users/petrosadaman/Downloads/PROJECT/fisrt/fisrt/res/img/brick.png") ) //без полного пути не работает ((
    {
        std::cout << "Load Failed!!!" << std::endl;
        system("pause");
    }
    
    texture.setRepeated(true); //чет неработает
    
    if( texture.isRepeated() )
    {
        std::cout << "is repeated" << std::endl;
    }
    
    sf::Sprite sprite;  //какая-то обёртка над текстурой
    sprite.setTexture(texture);
    
    
  //  sprite.setTextureRect(sf::IntRect(0,0,64,64)); //хз не поюмню
  //  sprite.setColor(sf::Color(0,0,255)); // цветовой фильтр
    
sprite.setPosition(sf::Vector2f(320, 240)); //установить позицию
/*  //позиция
 
 
    
    sprite.move(sf::Vector2f(50,0)); // относительно текущей позиции
    
    sf::Vector2f position =  sprite.getPosition(); //ret Vector2f - можно вытащить позицию
    
    position.x; //причем по осям
    position.y;
*/
    
/* //вращение
    
    sprite.setRotation(45); //задать наклон
    sprite.rotate(10); //относительно текущего наклона
    
    float rotation = sprite.getRotation(); // ret float
    
*/
    
/*  //растяжение
 
    sprite.setScale(sf::Vector2f(2.0f, 2.0f)); //установить растяжение
    
    sprite.scale(sf::Vector2f(0.5f, 0.5f)); //растянуть относительно текущего
    
    sf::Vector2f scale = sprite.getScale(); // можно вытащить растчжение
    
    std::cout << scale.x << ' ' << scale.y << std::endl; // даже по осям
*/
  
/*  //что-то непонятное
 
    sf::Rect<float> size = sprite.getGlobalBounds();
    
    sprite.setOrigin(size.width / 2, size.height / 2);
*/
    
    while( window.isOpen() )
    {
        sf::Event event;
        
        while( window.pollEvent(event))
        {
            
            switch ( event.type )
            {
                    
                case sf::Event::EventType::Closed:
                    window.close();
                    break;
                

                case sf::Event::EventType::Resized:
                {
                    std::cout << event.size.width << " : " << event.size.height << std::endl;
                    break;
                }
                    
                case sf::Event::EventType::LostFocus:
                {
                    std::cout << "Lost Focus" << std::endl;
                    break;
                }
                    
                case sf::Event::EventType::GainedFocus:
                {
                    std::cout << "Gained Focus" << std::endl;
                    break;
                }
                
                case sf::Event::EventType::TextEntered:
                {
                    if( event.text.unicode < 128 )
                    {
                        std::cout << static_cast<char>(event.text.unicode);
                    }
                    break;
                }
                    
                case sf::Event::EventType::KeyPressed:
                {
                    std::cout << "Key has been pressed!" << std::endl;
                    if( sf::Keyboard::Key::Left == event.key.code )
                    {
                        std::cout << "left key has been pressed" << std::endl;
                    }
                    
                    std::cout << "Control: " << event.key.control << std::endl;
                    std::cout << "Alt: " << event.key.alt << std::endl;
                    std::cout << "Shift: " << event.key.shift << std::endl;
                    std::cout << "System: " << event.key.system << std::endl;
                    break;
                    
                }
                    
                case sf::Event::EventType::KeyReleased:
                {
                    std::cout << "Key has been released!" << std::endl;
                    if( sf::Keyboard::Key::Left == event.key.code )
                    {
                        std::cout << "left key has been released" << std::endl;
                    }
                    
                    std::cout << "Control: " << event.key.control << std::endl;
                    std::cout << "Alt: " << event.key.alt << std::endl;
                    std::cout << "Shift: " << event.key.shift << std::endl;
                    std::cout << "System: " << event.key.system << std::endl;
                    break;
                    
                }
                    
                case sf::Event::EventType::MouseButtonPressed:
                {
                    std::cout << "Mouse button pressed" << std::endl;
                    
                    break;
                }
                    
                case sf::Event::EventType::MouseButtonReleased:
                {
                    std::cout << "Moude buttin released" << std::endl;
                    
                    break;
                }
                    
                default:
                    break;
            }
        }
        
        window.clear();
        
        window.draw(sprite);
        
        window.display();
    }

    return 0;
}
