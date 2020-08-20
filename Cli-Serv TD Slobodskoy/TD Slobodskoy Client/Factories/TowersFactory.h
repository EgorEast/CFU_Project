#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "../Classes.h"
#include "../Classes/Scene.h"

using namespace sf;
//////////������� �����///////
class TowersFactory
{
public:

	int tower;

	//����������� �������
	TowersFactory(Scene& scene);
	//������� ��� �������� �����
	virtual void createTowers(sf::Image& towersImage, sf::Vector2f startPosTower, int& moneyBalance);
	//�������� �����
	void update(float dt);

private:
	int _numberOfTowers;
	//������ ������, ���� ���� ������ ������� �����
	std::list<Tower*> _towers;
	//�������� ����������, ������� ������ �����
	Scene* _scene;
};

