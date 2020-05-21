#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"
#include "../level.h"

////////////////////////////////////////////////////КЛАСС ВГРАГОВ////////////////////////
class Enemy :public Entity {
public:
	
	int* ptrPlayerHealth;	//Указатель на жизни игрока

	Enemy(Image& image, String Name, Vector2f startPos, int Width, int Height, int& playerHealth);
	void update(float time);	//функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая врагу движение.
	int curPointInd = 1;	//Первая точка, куда будет двигаться враг
	void move(float time);	//Правила, по которым будет двигаться враг
};