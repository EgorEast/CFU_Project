#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "TowersFactory.h"

//////////������� �����///////
using namespace sf;
//����������� �������
TowersFactory::TowersFactory(Scene& scene) {
_scene = &scene;
_numberOfTowers = 0;
tower = 1;
}

//������� ��� �������� ������
void TowersFactory::createTowers(sf::Image& towersImage, sf::Vector2f startPosTower, int& moneyBalance)

{
	if (tower == 1) {
		_towers.push_back(new Tower(towersImage, "TowerOne", startPosTower, 58, 94, moneyBalance));
		_numberOfTowers++;
		tower--;
	}
	//if (/*���� � ������� �� ������ ��� ��������*/)
	//if (/*���� ������ ������ ���� �����*/) {
	//moneyBalance -= ����;
	//� ������

	//��������� � ������
	//if (){
	//	//��������� � ������
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

//�������� ��������� ����� �� �����
void TowersFactory::update(float dt) {
	if (_numberOfTowers > 0)
		if (_towers.size() > 0) {
		// �������� ����� towers ������
		_scene->AddEntity(*_towers.begin());
		//� ������ ���
		_towers.pop_front();
		//������� �� ���������� �����
		_numberOfTowers--;
		}
}