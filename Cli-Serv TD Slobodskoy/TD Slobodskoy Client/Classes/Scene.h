#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "../Classes.h"

///////////////Отрисовка и обновление всех игровых объектов///////////////
class Scene
{
public:
	//Отрисовка всех игровых объектов сцены
	void Draw();	
	//Обновление всех игровых объектов сцены
	void update(float dt);
	//Обработка событий мыши
	void onMouseEvent(sf::Event& event, sf::Vector2f posMouse, sf::RenderWindow& window);
	//Добавление новых объектов на сцены
	void AddEntity(Entity* entity);
	//void shooting();
private:
	//Создаю список всех объектов карты
	std::list<Entity*> _entities;

	//std::list<Projectale*> _projectales;

	//std::list<Entity*>::iterator it;
};