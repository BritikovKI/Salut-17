//
//  classes.hpp
//  fisrt
//
//  Created by Петрос Адамян on 28.10.2017.
//  Copyright © 2017 Петрос Адамян. All rights reserved.
//

#ifndef classes_hpp
#define classes_hpp

#include <stdio.h>
#include <string>
#include <vector>
#endif /* classes_hpp */

class Item
{
    std::string res;
    int HealthPoints();
};


class Obstacle
{
    
};

class Creature
{
    int HealthPoints;
    std::string res;
    std::vector<Item> items;
    void movejump();
public:
    Creature();
   ~Creature();

    void listen();
};

class GameSession
{
    
    /*
     создание окна
     отследивание нажатий
     режимы: пауза, игра, меню
     завершение сеанса
     и т д
    */
};

class Location
{
    std::string blockPath;
    std::string bckgrndPath;
    void mapGen(std::string block, std::string img);
public:
    Location();
   ~Location();

    void addCreature(Creature & cr);
    void delCreaturw();
};
