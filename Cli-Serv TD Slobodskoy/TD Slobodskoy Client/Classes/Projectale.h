#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"

////////////////////////////////////////////////////КЛАСС СНАРЯДОВ////////////////////////
class Projectale :public Entity {
public:
	//Направление снарядов
	int direction;

	/*Vector2f Vel;
	float Rotation;*/

	//Конструктор класса снарядов
	Projectale(sf::Image& image, sf::String Name, sf::Vector2f startPos, int Width, int Height, float Rot, sf::Vector2f Vel);
	//Функция "оживления" объекта класса
	void update(float time) override;
	//Движение пули
	void move(float time);
	//Взаимодействие с объектами
	void collision();
};