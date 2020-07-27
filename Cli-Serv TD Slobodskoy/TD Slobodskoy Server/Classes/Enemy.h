#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"
#include "../levels.h"

using namespace sf;
////////////////////////////////////////////////////КЛАСС ВГРАГОВ////////////////////////
class Enemy :public Entity {
public:
	//Конструктор класса врага
	Enemy(String Name, Vector2f startPos, int Width, int Height, int& playerHealth);
	//Функция "оживления" объекта класса
	void update(float time) override;
	//Правила, по которым будет двигаться враг
	void move(float time);
private:
	//Указатель на жизни игрока
	int* _ptrPlayerHealth;
	//Первая точка, куда будет двигаться враг
	int _curPointInd = 1;
	//Угол поворота объекта
	float _angle;
};