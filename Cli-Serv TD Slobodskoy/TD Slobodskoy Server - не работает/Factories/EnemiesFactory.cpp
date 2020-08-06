#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "EnemiesFactory.h"

//////////������� ������///////
using namespace sf;
//����������� �������
EnemiesFactory::EnemiesFactory(Scene& scene) {
	_scene = &scene;

	_drawTimer = 0;
	_timeToGen = 2;

	_posFinish.x = path[points][0];	//������������� ������� ������ �� x � ������������ � ��������� ������
	_posFinish.y = path[points][1];	//������������� ������� ������ �� y � ������������ � ��������� ������
}

//������� ��� �������� ������
void EnemiesFactory::createEnemies(sf::Vector2f startPosEntity, int& playerHealth, int& gameLevel)
{
	if (gameLevel == 1) {
		//������ ������ ����� �������
		_turnOfEnemies = "ssssttssPPPttsP";
		_sizeTurnOfEnemies = 15;
	}
	

	for (int i = 0; _sizeTurnOfEnemies > i; i++) {
		if (_turnOfEnemies[i] == 's')
		{
			//� ��������� � ������
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

//�������� ���������� ����� �� �����
void EnemiesFactory::update(float time) {
	//���������� � ����� ���������� time
	_drawTimer += time;
	//���� ������ ��� ��������� ������ timeToGen - ��� 2 �������
	if (_drawTimer > _timeToGen)
		if (_enemies.size() > 0)
		{
			//������� ������ ���������
			_drawTimer = 0;
			//�������� ����� enemies ������
			_scene->AddEntity(*_enemies.begin());
			//� ������ ���
			_enemies.pop_front();
		}
}