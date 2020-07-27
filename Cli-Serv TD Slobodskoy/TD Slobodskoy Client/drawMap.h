#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;
//Отрисовка карты
void drawMap(Sprite& spriteMap, RenderWindow& window, sf::String TileMap[], const int HEIGHT_MAP, const int WIDTH_MAP);
