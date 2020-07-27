#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
//������ �����
#include <sstream>
//��������� ������
#include <vector>
//��������� ������
#include <list>

////��������� ���� ���////

// ��������� ������
#include "Classes.h"
//��������� ������
//#include "Levels.h"
//��������� ��� � ����� ������
#include "View.h"
//��������� ��� ��� ��������� �����
#include "map.h"
//��������� ������� �������� ������
#include "Factories.h"
//��������� ����� ����
#include "Classes/Scene.h"

//#include "mission.h"//���������� ��� ������
//#include "LifeBar.h"//���������� ��� ������ ��������
//#include "Game.h"//���������� ��� ������� ���� ����

//����� ��������� �������������� 4996 � �����, ��������� ������-��������� warning
#pragma warning(disable : 4996)

using namespace sf;

//������� �������� ������ ����
void changeLevel() {

}

////������� ������ � ����������� ����
//bool startGame(RenderWindow& window, int& gameLevel) {
//	sf::CircleShape shape(100.f);
//	shape.setFillColor(sf::Color::Green);
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//		window.clear();
//		window.draw(shape);
//		window.display();
//	}
//}

////�-��� ������������� ���� , ���� ��� ����������
//void gameRunning(RenderWindow& window, int& gameLevel) {
////���� startGame() == true, �� �������� ������ �-��� isGameRunning, ������� � ���� ������� ����� �������� startGame() 
//	if (startGame(window, gameLevel)) { numberLevel++; gameRunning(window, gameLevel); }
//}


RenderWindow* g_window;

int main()
{
	RenderWindow window(VideoMode(920, 580), "TDSLobodskoy");
	//RenderWindow window(VideoMode(1920, 1080), "TDSLobodskoy", sf::Style::Fullscreen);

	g_window = &window;
	//������ "����" ������ ��� �������� ������� ���� ������. (����� ����� ������ ��� �����) ��� �� ���� �������������.
	view.reset(sf::FloatRect(0, 0, 1920, 1080));	

	//����� 
	sf::Font font;
	//������� ������ ������ ���� ������
	font.loadFromFile("Fonts/Kenney Rocket.ttf");

	//������ ������ Image (�����������) ��� �����
	Image towersImage;
	//�������� � ���� ����
	towersImage.loadFromFile("images/towers.png");

	//������ ������ Image (�����������) ��� ������
	Image enemiesImage;
	enemiesImage.loadFromFile("images/enemies.png");

	//����������� ��� ����
	Image projectaleBulletImage;
	//�������� �������� � ������ �����������
	projectaleBulletImage.loadFromFile("images/projectale.png");

	//����������� ��� �����
	Image mapImage;
	//�������� ��������
	mapImage.loadFromFile("images/mapImages.png");
	//�������� ��� �����
	Texture textureMap;
	//���� �������� �� ��������
	textureMap.loadFromImage(mapImage);
	//������ ��� ����� �����
	Sprite spriteMap;
	//�������� �������� � ������
	spriteMap.setTexture(textureMap);

	//������ ���������� �������, �.�. �������� �� ������ (� ��  ������������/�������� ����������).
	sf::Clock clock;
	//���������� �������� �������, ���� ����� ������� ����� ����
	sf::Clock gameTimeClock;
	//������� ������� ����� � ��������������� ���
	int gameTime = 0;

	//������ ����� ������
	int playerHealth = 20;
	//���� ������������ ��� ��� ���
	bool gameLife = true;
	//������ ���� ������
	int playerScore = 0;
	//������� ���� � ������� ������
	int gameLevel = 1;

	//��������� ������. ����� ����� ������� ��� ������� ������ ����
	int StartMoneyBalance = 100;

	//����� ��������� ��������� ����� //���� ����� ���������, ����� ���������� ���, ��� �����
	Vector2f startPosTower (200,200);
	
	//��������� ��������� ����� ������ �� ������ ����� �����
	Vector2f startPosEntity (path[0][0], path[0][1]);
	
	//������ �� ������ ������� ����� � �����	//���� ����� �������, ����� ������ ��������
	//Tower towerOne(towersImage, "TowerOne", startPosTower, 58, 93, StartMoneyBalance);
	//Enemy people(enemiesImage, "Shooter", startPosEntity, 16, 30, playerHealth);
	//Enemy tank(enemiesImage, "Tank", startPosEntity, 31, 50, playerHealth);

	//�������� ������� �����
	Scene scene;
	//�������� ������� ������ � ������� ���� �����

	EnemiesFactory enemiesFactory(scene);
	//������ ��� ������� �� �����
	enemiesFactory.createEnemies(enemiesImage, startPosEntity, playerHealth, gameLevel);
	//����� �������� ������� ����� � ������� ���� �����
	TowersFactory towersFactory(scene);
	//������ ��� ������� �� �����
	towersFactory.createTowers(towersImage, startPosTower, playerHealth);

	//(�����������) ���� ���� ������� (window.isOpen())
	while (window.isOpen())
	{
		//���� �� ���� ����� �������� ����� ������, �� ���� �������������
		if (playerHealth < 0) gameLife = false;

		//��� ��������� ����� � �������������
		float time = clock.getElapsedTime().asSeconds();
		//������� ����� � �������� ��� ������, ���� ��� �����,
		//������������� ��� time ��� �� ����. ��� �� ��������� ������ ����. 
		if (gameLife) gameTime = gameTimeClock.getElapsedTime().asSeconds();	
		//else view.move(0.1, 0);	//����� ����, �� ������ ��������� ������
		
		//������������ �����
		clock.restart();

		//������� ���������� �������
		Vector2i pixelPosMouse = Mouse::getPosition(window);
		//�������� �� � ������� (����� �� ��������� ����)
		Vector2f posMouse = window.mapPixelToCoords(pixelPosMouse);

		//������� ���������� �������//View.h
		viewMap(window, time);
		
		//"�������" ������ � ���� sfml
		window.setView(view);

		//�������� ���������� �������
		sf::Event event;

		while (window.pollEvent(event))
		{
			//���� ������� event ������� �������� Closed, �� ��������� ��������� ����
			if (event.type == sf::Event::Closed) window.close();
		}

		//������ ����������� ������ �� ������������ ������� ����
		if (
			//���� ����� ������ ����
			event.type == sf::Event::MouseButtonPressed	||
			//��� ���� �������� ������ ����
			event.type == sf::Event::MouseButtonReleased||
			//��� ���� ���� ���������
			event.type == sf::Event::MouseMoved
			)
			//����� ������� ���������� ������� ����
			scene.onMouseEvent(event, posMouse, window);

		//������ ����������� ������ �� ������� ������� � ����������
		if (Keyboard::isKeyPressed)
			//����� ������//� ������������ ����� View.h
			changeView();

		//�������� ���������� ���� ������, �.�. ����������
		enemiesFactory.update(time);
		//���������� �������� ���������� ���� ����, ��� ���� ����������
		towersFactory.update(time);//- ������-�� ��������
		//�������� ���������� ���� �������� �����
		scene.update(time);

		//������ ����� �� ������ ��������
		window.clear();
		//��������� �����
		drawMap(spriteMap, window);
		//��������� �������� �����
		scene.Draw();
		//������ �� ����� ��� �����������
		window.display();
	}
	return 0;
}

//������� ��� ��������� �������. ������������ � ������ Entity
void DrawSprite(Sprite sprite) {
	g_window->draw(sprite);
}