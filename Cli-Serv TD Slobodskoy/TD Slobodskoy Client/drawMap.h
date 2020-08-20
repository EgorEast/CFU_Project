#pragma once
#include <SFML\Graphics.hpp>

//Отрисовка карты
void drawMap(sf::Sprite& spriteMap, sf::RenderWindow& window, std::string TileMap[], const int HEIGHT_MAP, const int WIDTH_MAP);
