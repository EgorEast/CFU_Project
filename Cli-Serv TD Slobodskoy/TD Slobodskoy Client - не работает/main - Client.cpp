#include <SFML/Graphics.hpp>
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
//Подключил код с видом камеры
#include "View.h"
//Подключил код для отрисовки карты
#include "drawMap.h"
//Подключил сцену игры
#include "Classes/Scene.h"
// Подключаю заголовочный файл с другими заголовочными файлами для работы с json
#include "../IncludeMyJson.h"

//Подключаю библиотеку для работы с json файлами
#include <nlohmann/json.hpp>
//Библиотека чтения и записи из файла
#include <fstream>

//Чтобы отключить предупреждение 4996 в файле, использую прагма-директиву warning
#pragma warning(disable : 4996)

using namespace sf;
using namespace std;
using namespace nlohmann;

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
	int gameTime;

	//Хранит жизни игрока
	int playerHealth = /*20*/;
	//Игра продолжается или уже нет
	bool gameLife = /*true*/;
	//Хранит очки игрока
	int playerScore = /*0*/;
	//Начинаю игру с первого уровея
	int gameLevel = /*1*/;

	//Начальный баланс. Нужно будет сделать для каждого уровня свой
	int startMoneyBalance = /*100*/;

	//Объявляю игровую сцену
	Scene scene;
	//Объявляю фабрику врагов и передаю туда сцену

	//(Обязятельно) Пока Окно открыто (window.isOpen())
	while (window.isOpen())
	{
		//Если на базу зашло слишьком много врагов, то игра заканчивается
		if (playerHealth < 0) gameLife = false;

		//Даю прошедшее время в микросекундах
		float time = /*clock.getElapsedTime().asSeconds()*/;
		//Игровое время в секундах идёт вперед, пока жив игрок,
		//Перезагружать как time его не надо. Оно не обновляет логику игры. 
		if (gameLife) gameTime = /*gameTimeClock.getElapsedTime().asSeconds()*/;

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
			event.type == sf::Event::MouseButtonPressed ||
			//Или если отпустил кнопку мыши
			event.type == sf::Event::MouseButtonReleased ||
			//Или если мышь двигается
			event.type == sf::Event::MouseMoved
			)
			//Тогда вызываю обработчик событий мыши
			scene.onMouseEvent(event, posMouse, window);

		//Должно запускаться только по нажатии клавиши с клавиатуры
		if (Keyboard::isKeyPressed)
			//Опции камеры//в заголовочном файле View.h
			changeView();

		//Запускаю обновление всех объектов сцены
		scene.update(time);

		//Очищаю экран от старых объектов
		window.clear();
		//Отрисовка карты
		drawMap(spriteMap, window, TileMap, heighMap, widthMap);
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