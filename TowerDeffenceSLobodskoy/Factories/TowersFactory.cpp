#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "TowersFactory.h"

//////////Фабрика башен///////
using namespace sf;
//Конструктор фабрики
TowersFactory::TowersFactory(Scene& scene) {
_scene = &scene;
_numberOfTowers = 0;
tower = 1;
}

//Функция для создания врагов
void TowersFactory::createTowers(sf::Image& towersImage, sf::Vector2f startPosTower, int& moneyBalance)

{
	if (tower == 1) {
		_towers.push_back(new Tower(towersImage, "TowerOne", startPosTower, 58, 94, moneyBalance));
		_numberOfTowers++;
		tower--;
	}
	//if (/*Если я нажимаю на кнопку для создания*/)
	//if (/*если баланс больше цены башни*/) {
	//moneyBalance -= цена;
	//И создаю

	//Закидываю в список
	//if (){
	//	//Закидываю в список
	//	_towers.push_back(new Tower(towersImage, "TowerOne", startPosTower, 58, 94, moneyBalance));
	//	_numberOfTowers++;
	//}
	//if (){
	//	_towers.push_back(new Tower(towersImage, "TowerTwo", startPosTower, 58, 94, moneyBalance));
	//	_numberOfTowers++;
	//}
	//if (){
	//	_towers.push_back(new Tower(towersImage, "TowerThree", startPosTower, 58, 94, moneyBalance));
	//	_numberOfTowers++;
	//}
	//if (){
	//	_towers.push_back(new Tower(towersImage, "TowerFour", startPosTower, 58, 94, moneyBalance));
	//	_numberOfTowers++;
	//}
	//}
}

//Добавляю следующую башню на карту
void TowersFactory::update(float dt) {
	if (_numberOfTowers > 0)
		if (_towers.size() > 0) {
		// Добавляю первй towers объект
		_scene->AddEntity(*_towers.begin());
		//И удаляю его
		_towers.pop_front();
		//Вычитаю из количества башен
		_numberOfTowers--;
		}
}