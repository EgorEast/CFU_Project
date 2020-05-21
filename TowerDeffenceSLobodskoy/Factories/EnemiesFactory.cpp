#include "EnemiesFactory.h"

EnemiesFactory::EnemiesFactory(int gameLevel, int playerHealth, bool gameLife, int gameTime) {
	numberOfShooters = 3;
	numberOfTanks = 1;
	numberOfPlanes = 2;

	summEnemies = numberOfShooters + numberOfTanks + numberOfPlanes;

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

void EnemiesFactory::drawEnemies(sf::RenderWindow& window)
{
	for (it = entities.begin(); it != entities.end(); it++) {
		window.draw((*it)->sprite); //рисуем entities объекты (сейчас это только враги)
	}
}