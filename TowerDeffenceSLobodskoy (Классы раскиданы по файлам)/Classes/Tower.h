#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"

////////////////////////////////////////////////////КЛАСС БАШЕН////////////////////////
class Tower :public Entity { //Наследуется от класса Entity
public:
	int towerLevel;
	bool isShoot; //Переменная для определения состояния стреляет объект или нет

	Tower(Image& image, String Name, Vector2f startPos, int Width, int Height);
	void update(Event& event, Vector2f posMouse, float dXMouse, float dYMouse, RenderWindow& window, float time);
	void control(Event& event, Vector2f posMouse, float dXMouse, float dYMouse, RenderWindow& window);
	void shooting(float time);
	void checkCollisionWithMap(Event& event, Vector2f posMouse, RenderWindow& window);
};