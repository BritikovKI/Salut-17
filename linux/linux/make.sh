# !/bin/bash

sudo apt-get install libtinyxml-dev
sudo apt-get install libsfml-dev
g++ -c  Main.cpp
g++ Main.o  sfml-app -lsfml-graphics -lsfml-window -lsfml-system -ltinyxml

