#include "EnemiesFactory.h"

EnemiesFactory::EnemiesFactory(Scene& scene) {
	_scene = scene;
	numberOfShooters = 3;
	numberOfTanks = 1;
	numberOfPlanes = 2;

	summEnemies = numberOfShooters + numberOfTanks + numberOfPlanes;

	drawTimer = 0;
	timeToGen = 2;

	posFinish.x = path[points][0];	//Инициализирую позицию финиша по x в соответствии с последней точкой
	posFinish.y = path[points][1];	//Инициализирую позицию финиша по y в соответствии с последней точкой
}

void EnemiesFactory::createEnemies(sf::Image& enemiesImage, sf::Vector2f startPosEntity, int& playerHealth)	
{

	for (int i = 0; i < summEnemies; i++)	//Создею список врагов, пока-что по порядку
	{
		if (numberOfShooters > 0)
		{
			entities.push_back(new Enemy(enemiesImage, "Shooter", startPosEntity, 64.0, 64.0, playerHealth));//и закидываем в список всех наших врагов с карты
			numberOfShooters--;
		}
		if (numberOfTanks > 0)
		{
			entities.push_back(new Enemy(enemiesImage, "Tank", startPosEntity, 64.0, 64.0, playerHealth));//и закидываем в список всех наших врагов с карты
			numberOfTanks--;
		}
		if (numberOfPlanes > 0)
		{
			entities.push_back(new Enemy(enemiesImage, "Plane", startPosEntity, 64.0, 64.0, playerHealth));//и закидываем в список всех наших врагов с карты
			numberOfPlanes--;
		}
	}
}	

//void EnemiesFactory::drawEnemies(sf::RenderWindow& window, float time)	//Функция дя отрисовки врагов
//{
//	drawTimer += time;	//Прибавляем к нашей переменной time
//
//
//	for (auto it = entities.begin(); it != entities.end();) {
//		if (drawTimer > 2000) {	//если таймер для отрисовки больше 2000 (это примерно 2 секунды)
//			window.draw((*it)->sprite);	//то рисуем entities объекты (сейчас это только враги)
//			drawTimer = 0;	//И обнуляем таймер телепортации
//			it++;
//		}
//	}
//}

//void EnemiesFactory::deleteEnemies()	//Функция дя удаления врагов
//{
//	for (auto it = entities.begin(); it != entities.end();) {
//		if (((*it)->getPosition() == posFinish) || ((*it)->life == false)) {	// Если этот объект дошел до финиша или мертв,
//			it = entities.erase(it); delete (*it);	//То удаляю его
//		}
//		else it++;	//И иду итератором к следующему объекту. Так делаем со всеми объектами списка
//	}
//}