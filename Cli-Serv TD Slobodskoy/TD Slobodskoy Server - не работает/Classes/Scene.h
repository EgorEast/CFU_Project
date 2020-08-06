#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "../Classes.h"

using namespace sf;
///////////////��������� � ���������� ���� ������� ��������///////////////
class Scene
{
public:
	//���������� ���� ������� �������� �����
	void update(float dt);
	//��������� ������� ����
	void onMouseEvent(Event& event, Vector2f posMouse, RenderWindow& window);
	//���������� ����� �������� �� �����
	void AddEntity(Entity* entity);

	//void shooting();
private:
	//������ ������ ���� �������� �����
	std::list<Entity*> _entities;

};