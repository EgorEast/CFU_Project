#include <SFML/Graphics.hpp>
#include <iostream>
// Вывожу текст
#include <sstream>
// Подключаю вектор
#include <vector>
// Подключаю списки
#include <list>

// Открывает доступ к некоторым функциям
#pragma comment(lib, "ws2_32.lib")
// Подключаю библиотеку для работы с сетью
#include <WinSock2.h>
//
#include <windows.h>

////Подключаю свой код////

// Подключил классы
#include "Classes.h"
// Подключил фабрику создания врагов
#include "Factories.h"
// Подключил сцену игры
#include "Classes/Scene.h"
// Подключаю заголовочный файл с другими заголовочными файлами для работы с json
#include "../IncludeMyJson.h"

// Подключаю библиотеку для работы с json файлами
#include <nlohmann/json.hpp>
// Библиотека чтения и записи из файла
#include <fstream>

// Чтобы отключить предупреждение 4996 в файле, использую прагма-директиву warning
#pragma warning(disable : 4996)

using namespace sf;
using namespace std;
using namespace nlohmann;

RenderWindow* g_window;

int main() {
	RenderWindow window(VideoMode(920, 580), "TDSLobodskoy");
	// RenderWindow window(VideoMode(1920, 1080), "TDSLobodskoy", sf::Style::Fullscreen);

	g_window = &window;

	// Создаю переменную времени, т.о. привязка ко времни (а не  загружености/мощности процессора).
	sf::Clock clock;
	// Переменная игрового времени, буду здесь хранить время игры
	sf::Clock gameTimeClock;
	// Объявил игровое время и инициализировал его
	int gameTime = 0;

	//Хранит жизни игрока
	int playerHealth = 20;
	// Игра продолжается или уже нет
	bool gameLife = true;
	// Хранит очки игрока
	int playerScore = 0;
	// Начинаю игру с первого уровея
	int gameLevel = 1;

	// Начальный баланс. Нужно будет сделать для каждого уровня свой
	int startMoneyBalance = 100;

	// Задаю начальное положение башни //Надо будет исправить, чтобы появлялась там, где мышка
	Vector2f startPosTower(200, 200);

	// Начальное положение врага исходя из первой точки карты
	Vector2f startPosEntity(path[0][0], path[0][1]);

	//// Объявляю игровую сцену
	//Scene scene;
	//// Объявляю фабрику врагов и передаю туда сцену
	//EnemiesFactory enemiesFactory(scene);
	//// Создаю все объекты из сцены
	//enemiesFactory.createEnemies(startPosEntity, playerHealth, gameLevel);
	//// Также объявляю фабрику башен и передаю туда сцену
	//TowersFactory towersFactory(scene);
	//// Создаю все объекты из сцены
	//towersFactory.createTowers(startPosTower, playerHealth);

	json jsonFile = readJsonFile("../transfer_data.json");

	// (Обязятельно) Пока Окно открыто (window.isOpen())
	while (window.isOpen())
	{
		//// Если на базу зашло слишком много врагов, то игра заканчивается
		//if (playerHealth < 0) gameLife = false;

		//// Даю прошедшее время в микросекундах
		//float time = clock.getElapsedTime().asSeconds();
		//// Игровое время в секундах идёт вперед, пока жив игрок,
		// Перезагружать как time его не надо. Оно не обновляет логику игры. 
		if (gameLife) gameTime = gameTimeClock.getElapsedTime().asSeconds();
		// else view.move(0.1, 0);	// Еслит умер, то камера двигается вправо

		//// Перезагружаю время
		//clock.restart();

		// Забираю координаты курсора
		/*Vector2i pixelPosMouse = Mouse::getPosition(window);*/
		// Перевожу их в игровые (ухожу от координат окна)
		//Vector2f posMouse = /*window.mapPixelToCoords(pixelPosMouse)*/;

		//bool isMouseEvent = false;

		//// Объявляю переменную событий
		//sf::Event event;

		//while (window.pollEvent(event))
		//{
		//	// Если событие event приняло значение Closed, то программа закрывает окно
		//	if (event.type == sf::Event::Closed) window.close();
		//}

		//// Должно запускаться только по происшествию события мыши
		//if (isMouseEvent)
			//// Тогда вызываю обработчик событий мыши
			//scene.onMouseEvent(event, posMouse, window);


		//// Запускаю обновление всех врагов, т.е. добавление
		//enemiesFactory.update(time);
		//// Аналогично запускаю обновление всех баше, это таже добавление
		//towersFactory.update(time);
		//// Запускаю обновление всех объектов сцены
		//scene.update(time);

	}
	return 0;
}