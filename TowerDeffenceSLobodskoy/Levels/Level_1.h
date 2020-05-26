#pragma once
#include <SFML\Graphics.hpp>

const int HEIGHT_MAP = 25;//размер карты высота
const int WIDTH_MAP = 40;//размер карты ширина

//Это точки старта, поворота и конца
const int points = 6;	//Количество точек взаимодействия
extern float path[][2];

extern sf::String TileMap[];