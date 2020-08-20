#include "Game.h"
#include "../Classes.h"
#include "../drawMap.h"
#include "../View.h"
#include "../Classes/Scene.h"
#include "../Factories.h"

void Game(nlohmann::json jsonFile, sf::RenderWindow *g_window) {
	// ������� ������ �� ���������� ����������
	nlohmann::json jsnFile = jsonFile;
	sf::RenderWindow window(sf::VideoMode(920, 580), "TDSLobodskoy");
	//RenderWindow window(VideoMode(1920, 1080), "TDSLobodskoy", sf::Style::Fullscreen);

	g_window = &window;
	//������ "����" ������ ��� �������� ������� ���� ������. (����� ����� ������ ��� �����) ��� �� ���� �������������.
	view.reset(sf::FloatRect(0, 0, 1920, 1080));

	//����� 
	sf::Font font;
	//������� ������ ������ ���� ������
	font.loadFromFile("Fonts/Kenney Rocket.ttf");

	//������ ������ Image (�����������) ��� �����
	sf::Image towersImage;
	//�������� � ���� ����
	towersImage.loadFromFile("images/towers.png");

	//������ ������ Image (�����������) ��� ������
	sf::Image enemiesImage;
	enemiesImage.loadFromFile("images/enemies.png");

	//����������� ��� ����
	sf::Image projectaleBulletImage;
	//�������� �������� � ������ �����������
	projectaleBulletImage.loadFromFile("images/projectale.png");

	//����������� ��� �����
	sf::Image mapImage;
	//�������� ��������
	mapImage.loadFromFile("images/mapImages.png");
	//�������� ��� �����
	sf::Texture textureMap;
	//���� �������� �� ��������
	textureMap.loadFromImage(mapImage);
	//������ ��� ����� �����
	sf::Sprite spriteMap;
	//�������� �������� � ������
	spriteMap.setTexture(textureMap);

	//������ ���������� �������, �.�. �������� �� ������ (� ��  ������������/�������� ����������).
	sf::Clock clock;
	//���������� �������� �������, ���� ����� ������� ����� ����
	sf::Clock gameTimeClock;
	//������� ������� ����� � ��������������� ���
	int gameTime = 0;

	//������ ����� ������
	int playerHealth = jsnFile["gameData"]["health"];
	//���� ������������ ��� ��� ���
	bool gameLife = jsnFile["gameData"]["gameLife"];
	//������ ���� ������
	int playerScore = jsnFile["gameData"]["score"];
	//������� ���� � ������� ������
	int gameLevel = jsnFile["gameData"]["gameLevel"];

	//��������� ������. ����� ����� ������� ��� ������� ������ ����
	int StartMoneyBalance = jsnFile["gameData"]["moneyBalance"];

	//����� ��������� ��������� ����� //���� ����� ���������, ����� ���������� ���, ��� �����
	sf::Vector2f startPosTower(jsnFile["startPos"]["tower"]["x"], jsnFile["startPos"]["tower"]["y"]);

	//��������� ��������� ����� ������ �� ������ ����� �����
	sf::Vector2f startPosEnemy(jsnFile["startPos"]["enemy"]["x"], jsnFile["startPos"]["enemy"]["y"]);

	//�������� ������� �����
	Scene scene;
	//�������� ������� ������ � ������� ���� �����

	EnemiesFactory enemiesFactory(scene, jsnFile);
	//������ ��� ������� �� �����
	enemiesFactory.createEnemies(enemiesImage, startPosEnemy, playerHealth, gameLevel);
	//����� �������� ������� ����� � ������� ���� �����
	TowersFactory towersFactory(scene);
	//������ ��� ������� �� �����
	towersFactory.createTowers(towersImage, startPosTower, playerHealth);
	//(�����������) ���� ���� ������� (window.isOpen())
	while (window.isOpen())
	{
		//���� �� ���� ����� �������� ����� ������, �� ���� �������������
		if (playerHealth < 0) {
			gameLife = false;
			jsnFile["gameData"]["gameLife"] = gameLife;
		}

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
		jsnFile["mouse"]["pos"]["x"] = posMouse.x;
		jsnFile["mouse"]["pos"]["y"] = posMouse.y;

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
			event.type == sf::Event::MouseButtonPressed ||
			//��� ���� �������� ������ ����
			event.type == sf::Event::MouseButtonReleased ||
			//��� ���� ���� ���������
			event.type == sf::Event::MouseMoved
			)
		{
			//����� ������� ���������� ������� ����
			scene.onMouseEvent(event, posMouse, window);
		}


		//������ ����������� ������ �� ������� ������� � ����������
		if (Keyboard::isKeyPressed)
			//����� ������//� ������������ ����� View.h
			changeView();

		//�������� ���������� ���� ������, �.�. ����������
		enemiesFactory.update(time);
		//���������� �������� ���������� ���� ����, ��� ���� ����������
		towersFactory.update(time);
		//�������� ���������� ���� �������� �����
		scene.update(time);

		//������ ����� �� ������ ��������
		window.clear();
		// �������� ������ � ������ ������ ����� ��� �����
		std::string* tileMap = new std::string[jsnFile["levelData"]["map"]["height"]];
		//�������� �����
		for (int i = 0; i < jsnFile["levelData"]["map"]["height"]; i++) {
			tileMap[i] = jsnFile["levelData"]["map"]["tileMap"][i];
		}
		//��������� �����
		drawMap(spriteMap, window, tileMap, jsnFile["levelData"]["map"]["height"], jsnFile["levelData"]["map"]["width"]);
		// ������� ������ json ����
		scene.setJsonFile(jsnFile);
		//��������� �������� �����
		scene.Draw();
		//������ �� ����� ��� �����������
		window.display();
	}
}