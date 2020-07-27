#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
//Вывожу текст
#include <sstream>
//Подключаю вектор
#include <vector>
//Подключаю списки
#include <list>

////Подключаю свой код////

// Подключил классы
#include "Classes.h"
//Подключил уровни
//#include "Levels.h"
//Подключил код с видом камеры
#include "View.h"
//Подключил код для отрисовки карты
#include "map.h"
//Подключил фабрику создания врагов
#include "Factories.h"
//Подключил сцену игры
#include "Classes/Scene.h"

//#include "mission.h"//подключили код миссий
//#include "LifeBar.h"//подключили код строки здоровья
//#include "Game.h"//подключили код запуска меню игры

//Чтобы отключить предупреждение 4996 в файле, использую прагма-директиву warning
#pragma warning(disable : 4996)

using namespace sf;

//Функция проверки уровня игры
void changeLevel() {

}

////Функция начала и продолжения игры
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

////Ф-ция перезагружает игру , если это необходимо
//void gameRunning(RenderWindow& window, int& gameLevel) {
////если startGame() == true, то вызываем заново ф-цию isGameRunning, которая в свою очередь опять вызывает startGame() 
//	if (startGame(window, gameLevel)) { numberLevel++; gameRunning(window, gameLevel); }
//}


RenderWindow* g_window;

int main()
{
	RenderWindow window(VideoMode(920, 580), "TDSLobodskoy");
	//RenderWindow window(VideoMode(1920, 1080), "TDSLobodskoy", sf::Style::Fullscreen);

	g_window = &window;
	//Размер "вида" камеры при создании объекта вида камеры. (потом можем менять как хотим) Что то типа инициализации.
	view.reset(sf::FloatRect(0, 0, 1920, 1080));	

	//Шрифт 
	sf::Font font;
	//Передаю нашему шрифту файл шрифта
	font.loadFromFile("Fonts/Kenney Rocket.ttf");

	//Создаю объект Image (изображение) для башен
	Image towersImage;
	//Загружаю в него файл
	towersImage.loadFromFile("images/towers.png");

	//Создаю объект Image (изображение) для врагов
	Image enemiesImage;
	enemiesImage.loadFromFile("images/enemies.png");

	//Изображение для пули
	Image projectaleBulletImage;
	//Загружаю картинку в объект изображения
	projectaleBulletImage.loadFromFile("images/projectale.png");

	//Изображение для карты
	Image mapImage;
	//Загружаю картинку
	mapImage.loadFromFile("images/mapImages.png");
	//Текстура для карты
	Texture textureMap;
	//Беру текстуру из картинки
	textureMap.loadFromImage(mapImage);
	//Спрайт для блока карты
	Sprite spriteMap;
	//Загружаю текстуру в спрайт
	spriteMap.setTexture(textureMap);

	//Создаю переменную времени, т.о. привязка ко времни (а не  загружености/мощности процессора).
	sf::Clock clock;
	//Переменная игрового времени, буду здесь хранить время игры
	sf::Clock gameTimeClock;
	//Объявил игровое время и инициализировал его
	int gameTime = 0;

	//Хранит жизни игрока
	int playerHealth = 20;
	//Игра продолжается или уже нет
	bool gameLife = true;
	//Хранит очки игрока
	int playerScore = 0;
	//Начинаю игру с первого уровея
	int gameLevel = 1;

	//Начальный баланс. Нужно будет сделать для каждого уровня свой
	int StartMoneyBalance = 100;

	//Задаю начальное положение башни //Надо будет исправить, чтобы появлялась там, где мышка
	Vector2f startPosTower (200,200);
	
	//Начальное положение врага исходя из первой точки карты
	Vector2f startPosEntity (path[0][0], path[0][1]);
	
	//Создаю по одному объекту башни и врага	//Надо будет удалить, когда сделаю создание
	//Tower towerOne(towersImage, "TowerOne", startPosTower, 58, 93, StartMoneyBalance);
	//Enemy people(enemiesImage, "Shooter", startPosEntity, 16, 30, playerHealth);
	//Enemy tank(enemiesImage, "Tank", startPosEntity, 31, 50, playerHealth);

	//Объявляю игровую сцену
	Scene scene;
	//Объявляю фабрику врагов и передаю туда сцену

	EnemiesFactory enemiesFactory(scene);
	//Создаю все объекты из сцены
	enemiesFactory.createEnemies(enemiesImage, startPosEntity, playerHealth, gameLevel);
	//Также объявляю фабрику башен и передаю туда сцену
	TowersFactory towersFactory(scene);
	//Создаю все объекты из сцены
	towersFactory.createTowers(towersImage, startPosTower, playerHealth);

	//(Обязятельно) Пока Окно открыто (window.isOpen())
	while (window.isOpen())
	{
		//Если на базу зашло слишьком много врагов, то игра заканчивается
		if (playerHealth < 0) gameLife = false;

		//Даю прошедшее время в микросекундах
		float time = clock.getElapsedTime().asSeconds();
		//Игровое время в секундах идёт вперед, пока жив игрок,
		//Перезагружать как time его не надо. Оно не обновляет логику игры. 
		if (gameLife) gameTime = gameTimeClock.getElapsedTime().asSeconds();	
		//else view.move(0.1, 0);	//Еслит умер, то камера двигается вправо
		
		//Перезагружаю время
		clock.restart();

		//Забираю координаты курсора
		Vector2i pixelPosMouse = Mouse::getPosition(window);
		//Перевожу их в игровые (ухожу от координат окна)
		Vector2f posMouse = window.mapPixelToCoords(pixelPosMouse);

		//Вызываю управление камерой//View.h
		viewMap(window, time);
		
		//"Оживляю" камеру в окне sfml
		window.setView(view);

		//Объявляю переменную событий
		sf::Event event;

		while (window.pollEvent(event))
		{
			//Если событие event приняло значение Closed, то программа закрывает окно
			if (event.type == sf::Event::Closed) window.close();
		}

		//Должно запускаться только по происшествию события мыши
		if (
			//Если нажал кнопку мыши
			event.type == sf::Event::MouseButtonPressed	||
			//Или если отпустил кнопку мыши
			event.type == sf::Event::MouseButtonReleased||
			//Или если мышь двигается
			event.type == sf::Event::MouseMoved
			)
			//Тогда вызываю обработчик событий мыши
			scene.onMouseEvent(event, posMouse, window);

		//Должно запускаться только по нажатии клавиши с клавиатуры
		if (Keyboard::isKeyPressed)
			//Опции камеры//в заголовочном файле View.h
			changeView();

		//Запускаю обновление всех врагов, т.е. добавление
		enemiesFactory.update(time);
		//Аналогично запускаю обновление всех баше, это таже добавление
		towersFactory.update(time);//- ПОЧЕМУ-ТО РУГАЕТСЯ
		//Запускаю обновление всех объектов сцены
		scene.update(time);

		//Очищаю экран от старых объектов
		window.clear();
		//Отрисовка карты
		drawMap(spriteMap, window);
		//Отрисовка объектов сцены
		scene.Draw();
		//Вывожу на экран все изображения
		window.display();
	}
	return 0;
}

//Функция для отрисовки спрайта. Используется в классе Entity
void DrawSprite(Sprite sprite) {
	g_window->draw(sprite);
}