#pragma once
#include <SFML\Graphics.hpp>

//Размер карты - высота
const int HEIGHT_MAP = 25;
//Размер карты - ширина
const int WIDTH_MAP = 40;

//Количество точек взаимодействия
const int points = 6;
//Это точки старта, поворота и конца
extern float path[][2];
//Сама карта
extern sf::String TileMap[];