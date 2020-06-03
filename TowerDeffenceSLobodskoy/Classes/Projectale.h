#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"

using namespace sf;
////////////////////////////////////////////////////КЛАСС СНАРЯДОВ////////////////////////
class Projectale :public Entity {
public:
	//Направление снарядов
	int direction;

	/*Vector2f Vel;
	float Rotation;*/

	//Конструктор класса снарядов
	Projectale(Image& image, String Name, Vector2f startPos, int Width, int Height, float Rot, Vector2f Vel);
	//Функция "оживления" объекта класса
	virtual void update(float time);
	//Движение пули
	void move(float time);
	//Взаимодействие с объектами
	void collision();
};