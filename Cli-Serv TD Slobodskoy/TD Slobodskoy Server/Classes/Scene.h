#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "../Classes.h"

using namespace sf;
///////////////Отрисовка и обновление всех игровых объектов///////////////
class Scene
{
public:
	//Обновление всех игровых объектов сцены
	void update(float dt);
	//Обработка событий мыши
	void onMouseEvent(Event& event, Vector2f posMouse, RenderWindow& window);
	//Добавление новых объектов на сцены
	void AddEntity(Entity* entity);

	//void shooting();
private:
	//Создаю список всех объектов карты
	std::list<Entity*> _entities;

};