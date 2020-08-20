#include "Game.h"
#include "../Classes.h"
#include "../drawMap.h"
#include "../View.h"
#include "../Classes/Scene.h"
#include "../Factories.h"

void Game(nlohmann::json jsonFile, sf::RenderWindow *g_window) {
	// Передаю данные из глобальной переменной
	nlohmann::json jsnFile = jsonFile;
	sf::RenderWindow window(sf::VideoMode(920, 580), "TDSLobodskoy");
	//RenderWindow window(VideoMode(1920, 1080), "TDSLobodskoy", sf::Style::Fullscreen);

	g_window = &window;
	//Размер "вида" камеры при создании объекта вида камеры. (потом можем менять как хотим) Что то типа инициализации.
	view.reset(sf::FloatRect(0, 0, 1920, 1080));

	//Шрифт 
	sf::Font font;
	//Передаю нашему шрифту файл шрифта
	font.loadFromFile("Fonts/Kenney Rocket.ttf");

	//Создаю объект Image (изображение) для башен
	sf::Image towersImage;
	//Загружаю в него файл
	towersImage.loadFromFile("images/towers.png");

	//Создаю объект Image (изображение) для врагов
	sf::Image enemiesImage;
	enemiesImage.loadFromFile("images/enemies.png");

	//Изображение для пули
	sf::Image projectaleBulletImage;
	//Загружаю картинку в объект изображения
	projectaleBulletImage.loadFromFile("images/projectale.png");

	//Изображение для карты
	sf::Image mapImage;
	//Загружаю картинку
	mapImage.loadFromFile("images/mapImages.png");
	//Текстура для карты
	sf::Texture textureMap;
	//Беру текстуру из картинки
	textureMap.loadFromImage(mapImage);
	//Спрайт для блока карты
	sf::Sprite spriteMap;
	//Загружаю текстуру в спрайт
	spriteMap.setTexture(textureMap);

	//Создаю переменную времени, т.о. привязка ко времни (а не  загружености/мощности процессора).
	sf::Clock clock;
	//Переменная игрового времени, буду здесь хранить время игры
	sf::Clock gameTimeClock;
	//Объявил игровое время и инициализировал его
	int gameTime = 0;

	//Хранит жизни игрока
	int playerHealth = jsnFile["gameData"]["health"];
	//Игра продолжается или уже нет
	bool gameLife = jsnFile["gameData"]["gameLife"];
	//Хранит очки игрока
	int playerScore = jsnFile["gameData"]["score"];
	//Начинаю игру с первого уровея
	int gameLevel = jsnFile["gameData"]["gameLevel"];

	//Начальный баланс. Нужно будет сделать для каждого уровня свой
	int StartMoneyBalance = jsnFile["gameData"]["moneyBalance"];

	//Задаю начальное положение башни //Надо будет исправить, чтобы появлялась там, где мышка
	sf::Vector2f startPosTower(jsnFile["startPos"]["tower"]["x"], jsnFile["startPos"]["tower"]["y"]);

	//Начальное положение врага исходя из первой точки карты
	sf::Vector2f startPosEnemy(jsnFile["startPos"]["enemy"]["x"], jsnFile["startPos"]["enemy"]["y"]);

	//Объявляю игровую сцену
	Scene scene;
	//Объявляю фабрику врагов и передаю туда сцену

	EnemiesFactory enemiesFactory(scene, jsnFile);
	//Создаю все объекты из сцены
	enemiesFactory.createEnemies(enemiesImage, startPosEnemy, playerHealth, gameLevel);
	//Также объявляю фабрику башен и передаю туда сцену
	TowersFactory towersFactory(scene);
	//Создаю все объекты из сцены
	towersFactory.createTowers(towersImage, startPosTower, playerHealth);
	//(Обязятельно) Пока Окно открыто (window.isOpen())
	while (window.isOpen())
	{
		//Если на базу зашло слишьком много врагов, то игра заканчивается
		if (playerHealth < 0) {
			gameLife = false;
			jsnFile["gameData"]["gameLife"] = gameLife;
		}

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
		jsnFile["mouse"]["pos"]["x"] = posMouse.x;
		jsnFile["mouse"]["pos"]["y"] = posMouse.y;

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
		{
			//Тогда вызываю обработчик событий мыши
			scene.onMouseEvent(event, posMouse, window);
		}


		//Должно запускаться только по нажатии клавиши с клавиатуры
		if (Keyboard::isKeyPressed)
			//Опции камеры//в заголовочном файле View.h
			changeView();

		//Запускаю обновление всех врагов, т.е. добавление
		enemiesFactory.update(time);
		//Аналогично запускаю обновление всех баше, это таже добавление
		towersFactory.update(time);
		//Запускаю обновление всех объектов сцены
		scene.update(time);

		//Очищаю экран от старых объектов
		window.clear();
		// Принимаю размер и создаю массив строк для карты
		std::string* tileMap = new std::string[jsnFile["levelData"]["map"]["height"]];
		//Заполняю карту
		for (int i = 0; i < jsnFile["levelData"]["map"]["height"]; i++) {
			tileMap[i] = jsnFile["levelData"]["map"]["tileMap"][i];
		}
		//Отрисовка карты
		drawMap(spriteMap, window, tileMap, jsnFile["levelData"]["map"]["height"], jsnFile["levelData"]["map"]["width"]);
		// Передам врагам json файл
		scene.setJsonFile(jsnFile);
		//Отрисовка объектов сцены
		scene.Draw();
		//Вывожу на экран все изображения
		window.display();
	}
}