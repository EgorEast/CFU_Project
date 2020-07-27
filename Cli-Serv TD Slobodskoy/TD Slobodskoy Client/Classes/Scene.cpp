#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Scene.h"

using namespace sf;
///////////////��������� � ���������� ���� ������� ��������///////////////
//��������� ���� ������� �������� �����
void Scene::Draw() {
	for (auto i = _entities.begin(); i != _entities.end(); i++)
		(*i)->Draw();
}

//���������� ���� ������� �������� �����
void Scene::update(float time) {
	for (auto i = _entities.begin(); i != _entities.end(); i++)
		(*i)->update(time);
}

//��������� ������� ����
void Scene::onMouseEvent(Event& event, Vector2f posMouse, RenderWindow& window) {
	for (auto i = _entities.begin(); i != _entities.end(); i++)
		(*i)->onMouseEvent(event, posMouse, window);
}

//���������� ����� �������� �� �����
void Scene::AddEntity(Entity* entity) {
	_entities.push_back(entity);
}