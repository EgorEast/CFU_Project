#pragma once
#include <iostream>
#include <list>
#include "../Classes.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include "../map.h"	// Подключаем код для отрисовки карты


using namespace sf;
class EnemiesFactory
{
	std::list<Entity*> entities;	//создаю список, сюда буду кидать объекты врагов.
	std::list<Entity*>::iterator it;	//итератор чтобы проходить по эл-там списка

	int numberOfShooters;
	int numberOfTanks;
	int numberOfPlanes;
	int summEnemies;

public:
	EnemiesFactory(int gameLevel, int playerHealth, bool gameLife, int gameTime);
	virtual void createEnemies(sf::Image& enemiesImage, sf::Vector2f startPosEntity, int& playerHealth);	//Функция дя создания врагов
	virtual void drawEnemies(sf::RenderWindow& window);
};

