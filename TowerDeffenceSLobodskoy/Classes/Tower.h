#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"

////////////////////////////////////////////////////КЛАСС БАШЕН////////////////////////
class Tower :public Entity { //Наследуется от класса Entity
public:
	int towerLevel;
	bool isShoot; //Переменная для определения состояния стреляет объект или нет
	float dXMouse, dYMouse; //Корректировка нажатия мышью по х и по y

	Tower(Image& image, String Name, Vector2f startPos, int Width, int Height);
	void update(Event& event, Vector2f posMouse, RenderWindow& window, float time);
	void control(Event& event, Vector2f posMouse, RenderWindow& window);
	void shooting(float time);
	void checkCollisionWithMap(Event& event, Vector2f posMouse, RenderWindow& window);
};