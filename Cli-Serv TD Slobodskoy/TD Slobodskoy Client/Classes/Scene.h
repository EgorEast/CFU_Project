#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "../Classes.h"

///////////////��������� � ���������� ���� ������� ��������///////////////
class Scene
{
public:
	//��������� ���� ������� �������� �����
	void Draw();	
	//���������� ���� ������� �������� �����
	void update(float dt);
	//��������� ������� ����
	void onMouseEvent(sf::Event& event, sf::Vector2f posMouse, sf::RenderWindow& window);
	//���������� ����� �������� �� �����
	void AddEntity(Entity* entity);
	//void shooting();
private:
	//������ ������ ���� �������� �����
	std::list<Entity*> _entities;

	//std::list<Projectale*> _projectales;

	//std::list<Entity*>::iterator it;
};