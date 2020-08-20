#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "../Classes.h"
#include "../Classes/Scene.h"

using namespace sf;
//////////Фабрика башен///////
class TowersFactory
{
public:

	int tower;

	//Конструктор фабрики
	TowersFactory(Scene& scene);
	//Функция для создания башен
	virtual void createTowers(sf::Image& towersImage, sf::Vector2f startPosTower, int& moneyBalance);
	//Оживляем башни
	void update(float dt);

private:
	int _numberOfTowers;
	//Создаю список, сюда буду кидать объекты башен
	std::list<Tower*> _towers;
	//Объявляю переменную, которая примет сцену
	Scene* _scene;
};

