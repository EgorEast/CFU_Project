#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Scene.h"

using namespace sf;
///////////////Отрисовка и обновление всех игровых объектов///////////////

//Обновление всех игровых объектов сцены
void Scene::update(float time) {
	for (auto i = _entities.begin(); i != _entities.end(); i++)
		(*i)->update(time);
	//for (auto i = _projectales.begin(); i != _projectales.end(); i++)
	//	(*i)->update(time);
}

//Обработка событий мыши
void Scene::onMouseEvent(Event& event, Vector2f posMouse, RenderWindow& window) {
	for (auto i = _entities.begin(); i != _entities.end(); i++)
		(*i)->onMouseEvent(event, posMouse, window);
}

//Добавление новых объектов на сцену
void Scene::AddEntity(Entity* entity) {
	_entities.push_back(entity);
}