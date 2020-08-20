#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "../Classes.h"
#include "../Classes/Scene.h"
#include "nlohmann/json.hpp"


using namespace sf;
//////////‘абрика врагов///////
class EnemiesFactory
{
public:
	// онструктор фабрики
	EnemiesFactory(Scene& scene, nlohmann::json& jsonFile);
	//‘ункци€ дл€ создани€ врагов
	virtual void createEnemies(sf::Image& enemiesImage, sf::Vector2f startPosEntity, int& playerHealth, int& gameLevel);
	//ќживл€ем врагов
	void update(float dt);
private:
	//—оздаю список, сюда буду кидать объекты врагов.
	std::list<Enemy*> _enemies;

	//—оздам список врагов через строчку
	sf::String _turnOfEnemies;
	// оличество врагов в уровне
	int _sizeTurnOfEnemies;

	//ѕеременна€ таймера отрисовки врагов
	float _drawTimer;
	//ѕеременна€ таймера генерации врагов
	float _timeToGen;

	//ќбъ€вл€ю позицию финиша
	Vector2f _posFinish;
	//ќбъ€вл€ю переменную, котора€ примет сцену
	Scene* _scene;

	// ќбъ€влю переменную, котора€ будет хранить прин€тый json файл
	nlohmann::json _jsonFile;
	// ’ранит число точек пути карты
	int _points;
};

