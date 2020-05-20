#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"
//#include "../levels.h"

////////////////////////////////////////////////////КЛАСС ВГРАГОВ////////////////////////
class Enemy :public Entity {
public:
	int* ptrPlayerHealth;
	int** ptrpath;
	int* points;

	Enemy(Image& image, String Name, Vector2f startPos, int Width, int Height, int& playerHealth, int& points, float path[][2]);
	void update(float time);	//функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая врагу движение.
	int curPointInd = 1;	//Первая точка, куда будет двигаться враг
	void move(float time);	//Правила, по которым будет двигаться враг
};