#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Scene.h"

using namespace sf;
///////////////Отрисовка и обновление всех игровых объектов///////////////
//Отрисовка всех игровых объектов сцены
void Scene::Draw() {
	for (auto i = _entities.begin(); i != _entities.end(); i++)
		(*i)->Draw();
	//for (auto i = _projectales.begin(); i != _projectales.end(); i++)
	//	(*i)->Draw();
}

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

/*Удалить то можно, но не нужно. 
Сцена хранит ссылку на него (если мы про врага), если удалишь его все сломается при следующем обращении. 
Сцена должна удалять объекты, а они просто должны об этом сказать. 
Например у него может быть поле needDel, в котором он сообщает что можно его удалять
и сцена в очередном кадре может это сделать.*/


//void Scene::shooting() {
//	for (it = _entities.begin(); it != _entities.end(); it++)
//	{
//		if ((*it)->name ==)
//	}
//}