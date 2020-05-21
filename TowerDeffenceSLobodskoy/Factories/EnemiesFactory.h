#pragma once
#include <iostream>
#include <list>
#include "../Classes.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include "../map.h"	// ���������� ��� ��� ��������� �����


using namespace sf;
class EnemiesFactory
{
	std::list<Entity*> entities;	//������ ������, ���� ���� ������ ������� ������.
	std::list<Entity*>::iterator it;	//�������� ����� ��������� �� ��-��� ������

	int numberOfShooters;
	int numberOfTanks;
	int numberOfPlanes;
	int summEnemies;

public:
	EnemiesFactory(int gameLevel, int playerHealth, bool gameLife, int gameTime);
	virtual void createEnemies(sf::Image& enemiesImage, sf::Vector2f startPosEntity, int& playerHealth);	//������� �� �������� ������
	virtual void drawEnemies(sf::RenderWindow& window);
};

