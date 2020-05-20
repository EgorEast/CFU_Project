#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>//������� �����
#include <vector>//��������� ������
#include <list>//��������� ������

//��������� ���� ���
#include "Classes.h"// ���������� ������
//#include "levels.h"	//���������� ������
#include "View.h"	//���������� ��� � ����� ������
#include "map.h"	// ���������� ��� ��� ��������� �����

//#include "mission.h"//���������� ��� ������
//#include "LifeBar.h"//���������� ��� ������ ��������
//#include "Game.h"//���������� ��� ������� ���� ����

#pragma warning(disable : 4996) //����� ��������� �������������� 4996 � �����, ����������� ������-��������� warning

using namespace sf;

void changeLevel() {//������� �������� ������ ����

}

//bool startGame(RenderWindow& window, int& gameLevel) {//������� ������ � ����������� ����
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

//void gameRunning(RenderWindow& window, int& gameLevel) {//�-��� ������������� ���� , ���� ��� ����������
//	if (startGame(window, gameLevel)) { numberLevel++; gameRunning(window, gameLevel); }////���� startGame() == true, �� �������� ������ �-��� isGameRunning, ������� � ���� ������� ����� �������� startGame() 
//}



int main()
{
	RenderWindow window(VideoMode(1920, 1080), "TDSLobodskoy", sf::Style::Fullscreen);
	view.reset(sf::FloatRect(0, 0, 1920, 1080));	//������ "����" ������ ��� �������� ������� ���� ������. (����� ����� ������ ��� �����) ��� �� ���� �������������.

	sf::Font font;//����� 
	font.loadFromFile("Fonts/Kenney Rocket.ttf");//�������� ������ ������ ���� ������

	Image towersImage; //������� ������ Image (�����������) ��� �����
	towersImage.loadFromFile("images/towers.png"); //��������� � ���� ����

	Image enemiesImage; //������� ������ Image (�����������) ��� ������
	enemiesImage.loadFromFile("images/enemies.png");

	Image ammunitionImage;//����������� ��� ����
	ammunitionImage.loadFromFile("images/ammunition.png");//��������� �������� � ������ �����������

	Image mapImage;
	mapImage.loadFromFile("images/mapImages.png");
	Texture textureMap;
	textureMap.loadFromImage(mapImage);
	Sprite spriteMap;
	spriteMap.setTexture(textureMap);

	sf::Clock clock; //������� ���������� �������, �.�. �������� �� ������ (� ��  ������������/�������� ����������).
	sf::Clock gameTimeClock;//���������� �������� �������, ����� ����� ������� ����� ���� 
	int gameTime = 0;//�������� ������� �����, ����������������.

	int playerHealth = 20;//������ ����� ������
	bool gameLife = true;//���� ������������ ��� ��� ���
	int playerScore = 0; //������ ���� ������
	int gameLevel = 1;

	Vector2f startPosTower (200,200); //������ ��������� ��������� �����
	
	Vector2f startPosEntity(path[0][0], path[0][1]);	//��������� ��������� ����� ������ �� ������ ����� �����

	std::list<Entity*> entities;//������ ������, ���� ���� ������ ������� ������.
	std::list<Entity*>::iterator it;//�������� ����� ��������� �� ��-��� ������

	//std::vector<Object> e = lvl.GetObjects("EasyEnemy");//��� ������� ����� �� tmx ����� �������� � ���� �������
	
	Tower towerOne(towersImage, "TowerOne", startPosTower, 58.0, 93.0);
	Enemy people(enemiesImage, "Shooter", startPosEntity, 64.0, 64.0, playerHealth, points, path);


	float dXMouse = 0;//������������� ������� ����� �� �
	float dYMouse = 0;//�� �

	while (window.isOpen())	//(�����������) ���� ���� ������� (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
		if (gameLife) gameTime = gameTimeClock.getElapsedTime().asSeconds();
		else view.move(0.1, 0); //������� ����� � �������� ��� ������, ���� ��� �����, ������������� ��� time ��� �� ����. ��� �� ��������� ������ ����. 
		clock.restart(); //������������� �����
		time /= 800; //�������� ����

		Vector2i pixelPosMouse = Mouse::getPosition(window);//�������� ����� �������
		Vector2f posMouse = window.mapPixelToCoords(pixelPosMouse);//��������� �� � ������� (������ �� ����� ����)

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
		}

		viewMap(window, time);	//������� ���������� �������//View.h
		towerOne.update(event, posMouse, dXMouse, dYMouse, window, time);
		people.update(time);	
		changeView();	//����� ������//� ������������ ����� View.h
		window.setView(view);	//"�������" ������ � ���� sfml
		window.clear(Color(153,153,80));

		drawMap(spriteMap, window);	//��������� �����

		window.draw(people.sprite);
		window.draw(towerOne.sprite);
		window.display();
	}
	

	return 0;
}