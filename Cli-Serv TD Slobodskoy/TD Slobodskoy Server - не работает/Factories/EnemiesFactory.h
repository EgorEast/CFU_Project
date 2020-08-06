#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "../Classes.h"
#include "../levels.h"	// ���������� ��� �������
#include "../Classes/Scene.h"


using namespace sf;
//////////������� ������///////
class EnemiesFactory
{
public:
	//����������� �������
	EnemiesFactory(Scene& scene);
	//������� ��� �������� ������
	virtual void createEnemies(sf::Vector2f startPosEntity, int& playerHealth, int& gameLevel);
	//�������� ������
	void update(float dt);
private:
	//������ ������, ���� ���� ������ ������� ������.
	std::list<Enemy*> _enemies;

	//������ ������ ������ ����� �������
	sf::String _turnOfEnemies;
	//���������� ������ � ������
	int _sizeTurnOfEnemies;

	//���������� ������� ��������� ������
	float _drawTimer;
	//���������� ������� ��������� ������
	float _timeToGen;

	//�������� ������� ������
	Vector2f _posFinish;
	//�������� ����������, ������� ������ �����
	Scene* _scene;
};

