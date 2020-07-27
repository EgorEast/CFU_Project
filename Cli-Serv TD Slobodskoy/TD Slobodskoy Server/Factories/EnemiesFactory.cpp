#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "EnemiesFactory.h"

//////////Фабрика врагов///////
using namespace sf;
//Конструктор фабрики
EnemiesFactory::EnemiesFactory(Scene& scene) {
	_scene = &scene;

	_drawTimer = 0;
	_timeToGen = 2;

	_posFinish.x = path[points][0];	//Инициализирую позицию финиша по x в соответствии с последней точкой
	_posFinish.y = path[points][1];	//Инициализирую позицию финиша по y в соответствии с последней точкой
}

//Функция для создания врагов
void EnemiesFactory::createEnemies(sf::Vector2f startPosEntity, int& playerHealth, int& gameLevel)
{
	if (gameLevel == 1) {
		//Список врагов через строчку
		_turnOfEnemies = "ssssttssPPPttsP";
		_sizeTurnOfEnemies = 15;
	}
	

	for (int i = 0; _sizeTurnOfEnemies > i; i++) {
		if (_turnOfEnemies[i] == 's')
		{
			//И закидываю в список
			_enemies.push_back(new Enemy("Shooter", startPosEntity, 16, 30, playerHealth));
		}
		if (_turnOfEnemies[i] == 't')
		{
			_enemies.push_back(new Enemy("Tank", startPosEntity, 50, 30, playerHealth));
		}
		if (_turnOfEnemies[i] == 'P')
		{
			_enemies.push_back(new Enemy("Plane", startPosEntity, 50, 50, playerHealth));
		}
	}
}

//Добавляю следующего врага на карту
void EnemiesFactory::update(float time) {
	//Прибавляем к нашей переменной time
	_drawTimer += time;
	//Если таймер для отрисовки больше timeToGen - это 2 секунды
	if (_drawTimer > _timeToGen)
		if (_enemies.size() > 0)
		{
			//Обнуляю таймер отрисовки
			_drawTimer = 0;
			//Добавляю первй enemies объект
			_scene->AddEntity(*_enemies.begin());
			//И удаляю его
			_enemies.pop_front();
		}
}