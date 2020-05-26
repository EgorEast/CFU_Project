#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "../Classes.h"
#include "../leves.h"	// ���������� ��� �������


using namespace sf;
class EnemiesFactory
{
	std::list<Entity*> entities;	//������ ������, ���� ���� ������ ������� ������.

	int numberOfShooters;	//����� ������� ���������� ����� ������
	int numberOfTanks;	//����� ������� ���������� ������
	int numberOfPlanes;	//����� ������� ���������� ���������
	int summEnemies;	//����� ������� ���������� ���� ������ �� �����

	float drawTimer;	//���������� ������� ��������� ������
	float timeToGen;

	Vector2f posFinish;	//�������� ������� ������
	Scene& _scene;
	

public:
	EnemiesFactory(Scene& scene);
	virtual void createEnemies(sf::Image& enemiesImage, sf::Vector2f startPosEntity, int& playerHealth);	//������� �� �������� ������
	//virtual void drawEnemies(sf::RenderWindow& window, float time);	//������� �� ��������� ������
	//virtual void deleteEnemies();	//������� �� �������� ������
	void update(float dt) {
		drawTimer += dt;
		if (drawTimer > timeToGen) {
			drawTimer = 0;
			scene.AddEntity(*entities.begin());
			entities.pop_front();
		}
	}
};

