#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "../Classes.h"
#include "../levels.h"	// Подключаем код уровней
#include "../Classes/Scene.h"


using namespace sf;
//////////Фабрика врагов///////
class EnemiesFactory
{
public:
	//Конструктор фабрики
	EnemiesFactory(Scene& scene);
	//Функция для создания врагов
	virtual void createEnemies(sf::Vector2f startPosEntity, int& playerHealth, int& gameLevel);
	//Оживляем врагов
	void update(float dt);
private:
	//Создаю список, сюда буду кидать объекты врагов.
	std::list<Enemy*> _enemies;

	//Создам список врагов через строчку
	sf::String _turnOfEnemies;
	//Количество врагов в уровне
	int _sizeTurnOfEnemies;

	//Переменная таймера отрисовки врагов
	float _drawTimer;
	//Переменная таймера генерации врагов
	float _timeToGen;

	//Объявляю позицию финиша
	Vector2f _posFinish;
	//Объявляю переменную, которая примет сцену
	Scene* _scene;
};

