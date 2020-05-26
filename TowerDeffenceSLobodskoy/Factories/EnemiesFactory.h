#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "../Classes.h"
#include "../leves.h"	// Подключаем код уровней


using namespace sf;
class EnemiesFactory
{
	std::list<Entity*> entities;	//создаю список, сюда буду кидать объекты врагов.

	int numberOfShooters;	//Будет хранить количество пеших врагов
	int numberOfTanks;	//Будет хранить количество танков
	int numberOfPlanes;	//Будет хранить количество самолетов
	int summEnemies;	//Будет хранить количество всех врагов на карте

	float drawTimer;	//Переменная таймера отрисовки врагов
	float timeToGen;

	Vector2f posFinish;	//Объявляю позицию финиша
	Scene& _scene;
	

public:
	EnemiesFactory(Scene& scene);
	virtual void createEnemies(sf::Image& enemiesImage, sf::Vector2f startPosEntity, int& playerHealth);	//Функция дя создания врагов
	//virtual void drawEnemies(sf::RenderWindow& window, float time);	//Функция дя отрисовки врагов
	//virtual void deleteEnemies();	//Функция дя удаления врагов
	void update(float dt) {
		drawTimer += dt;
		if (drawTimer > timeToGen) {
			drawTimer = 0;
			scene.AddEntity(*entities.begin());
			entities.pop_front();
		}
	}
};

