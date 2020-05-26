#include "EnemiesFactory.h"

EnemiesFactory::EnemiesFactory(Scene& scene) {
	_scene = scene;
	numberOfShooters = 3;
	numberOfTanks = 1;
	numberOfPlanes = 2;

	summEnemies = numberOfShooters + numberOfTanks + numberOfPlanes;

	drawTimer = 0;
	timeToGen = 2;

	posFinish.x = path[points][0];	//������������� ������� ������ �� x � ������������ � ��������� ������
	posFinish.y = path[points][1];	//������������� ������� ������ �� y � ������������ � ��������� ������
}

void EnemiesFactory::createEnemies(sf::Image& enemiesImage, sf::Vector2f startPosEntity, int& playerHealth)	
{

	for (int i = 0; i < summEnemies; i++)	//������ ������ ������, ����-��� �� �������
	{
		if (numberOfShooters > 0)
		{
			entities.push_back(new Enemy(enemiesImage, "Shooter", startPosEntity, 64.0, 64.0, playerHealth));//� ���������� � ������ ���� ����� ������ � �����
			numberOfShooters--;
		}
		if (numberOfTanks > 0)
		{
			entities.push_back(new Enemy(enemiesImage, "Tank", startPosEntity, 64.0, 64.0, playerHealth));//� ���������� � ������ ���� ����� ������ � �����
			numberOfTanks--;
		}
		if (numberOfPlanes > 0)
		{
			entities.push_back(new Enemy(enemiesImage, "Plane", startPosEntity, 64.0, 64.0, playerHealth));//� ���������� � ������ ���� ����� ������ � �����
			numberOfPlanes--;
		}
	}
}	

//void EnemiesFactory::drawEnemies(sf::RenderWindow& window, float time)	//������� �� ��������� ������
//{
//	drawTimer += time;	//���������� � ����� ���������� time
//
//
//	for (auto it = entities.begin(); it != entities.end();) {
//		if (drawTimer > 2000) {	//���� ������ ��� ��������� ������ 2000 (��� �������� 2 �������)
//			window.draw((*it)->sprite);	//�� ������ entities ������� (������ ��� ������ �����)
//			drawTimer = 0;	//� �������� ������ ������������
//			it++;
//		}
//	}
//}

//void EnemiesFactory::deleteEnemies()	//������� �� �������� ������
//{
//	for (auto it = entities.begin(); it != entities.end();) {
//		if (((*it)->getPosition() == posFinish) || ((*it)->life == false)) {	// ���� ���� ������ ����� �� ������ ��� �����,
//			it = entities.erase(it); delete (*it);	//�� ������ ���
//		}
//		else it++;	//� ��� ���������� � ���������� �������. ��� ������ �� ����� ��������� ������
//	}
//}