#include <SFML/Graphics.hpp>
// Открывает доступ к некоторым функциям
#pragma comment(lib, "ws2_32.lib")
// Подключаю библиотеку для работы с сетью
#include <WinSock2.h>
// Библиотека ввода и вывода
#include <iostream>
// Вывожу текст
#include <sstream>
// Подключаю вектор
#include <vector>
// Подключаю списки 
#include <list>
// Библиотека чтения и записи из файла
#include <fstream>

// Подключаю библиотеку для работы с json файлами
#include <nlohmann/json.hpp>
// Подключаю заголовочный файл с другими заголовочными файлами для работы с json
#include "../IncludeMyJson.h"

// Добавляю define, чтобы избежать некоторых ошибок
#define _WINSOCK_DEPRECATED_NO_WARNINGS
// Чтобы отключить предупреждение 4996 в файле, использую прагма-директиву warning
#pragma warning(disable : 4996)

// Подключаю свой код
#include "main - Client.h"
#include "Classes.h"
#include "drawMap.h"
#include "View.h"
#include "Classes/Scene.h"
#include "Factories.h"
//#include "Game/Game.h"

// Хранит индекс соединения
SOCKET Connection;


//Перечисление для разных типов пакетов
enum Packet {
	//Отвечает за тип пакета
	P_ChatMessage,
	P_Json
};

// Глобальная переменная, которая будет хранить тип пакета
Packet packet;
// Будет хранить глобально json файл
nlohmann::json g_jsnFile;
// Глобальный указатель на открывшееся окно
sf::RenderWindow* g_window;

//Ф-ция для обработки приходящих пакетов
bool ProcessPacket(Packet packetType) {
	switch (packetType) {
		//Принятие отправленного сервером сообщения
	case P_ChatMessage: {
		//Переменная для хранения переданной строки
		char msg[260];
		//Бесконечный цикл
		while (true) {
			//Принимаю сообщеня от сервера
			recv(Connection, msg, sizeof(msg), NULL);
			//Вывожу их на экран
			std::cout << msg << std::endl;
		}
		break;
	}
	case P_Json: {
		// Переменная для хранения размера массива
		int numSym;
		// Принимаю размер массива и записываю в переменную
		recv(Connection, (char*)&numSym, sizeof(int), NULL);
		std::cout << "Json пакет принят.\n";
		
		//Переменная для хранения переданной строки
		char* jsnChr = new char[numSym];

		// Переменная для хранения переданной json файла
		nlohmann::json jsnFile;

		// Принимаю массив и записываю его
		recv(Connection, jsnChr, numSym, NULL);

		// Создаю строку, которую буду преобразовывать в json
 		std::string jsnStr;
		// Заполняю строку символами из принятого массва
		for (int i = 0; i < numSym; i++) jsnStr.push_back(jsnChr[i]);

		// Произвожу парсинг строки
		jsnFile = nlohmann::json::parse(jsnStr);

		// Завожу в глобальную переменную
		g_jsnFile = jsnFile;

		//Вывожу принятый json файл на экран
		std::cout << jsnFile.dump(3) << std::endl;

		//Game(jsnFile, g_window);

		// Небольшая задержка 
		//Sleep(10);
		break;
	}
	default:
		std::cout << "Пакет не был принят: " << packetType << std::endl;
		return false;
	}

	//Если пакет обработан успешно, тогда true
	return true;
}

//Принимает тип пакета
void ClientHandler() {
	//Хранит тип пакета
	Packet packetType;
	while (true) {
		//Принимаю тип пакета и записываю его в переменную
		recv(Connection, (char*)&packetType, sizeof(Packet), NULL);

		packet = packetType;
		//Проверка на возвращаемое значение ф-ции
		if (!
			//Вызываю и передаю пакет ф-ции ProcessPacket
			ProcessPacket(packetType)) {
			//Если не удалось обработать пакет, то выхожу из цикла
			break;
		}
	}
	//Вышел из цикла -> закрываю сокет
	closesocket(Connection);
}

int main() {
	//Делаю так, чтобы читался русский язык как при вводе текста, так и при выводе
	//Установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleCP(1251);
	//Установка кодовой страницы win-cp 1251 в поток вывода
	SetConsoleOutputCP(1251);

	//Создаю структуру wsaData
	WSAData wsaData;
	//Создаю переменную WORD
	WORD DLLVEersion =
		//Это запрашиваемая версия библиотеки WinSock
		MAKEWORD(2, 1);
	//Делаю проверку. Если библиотека загрузилась удачно
	if (
		//Функция для загрузки библиотеки
		WSAStartup(
			//Передаю запрашиваемую версию библиотеки
			DLLVEersion,
			//Ссылка на структуру wsaData
			&wsaData)
		//Тогда она вернет значение 0
		!= 0
		)
	{
		//Если WSAStartup не вернет значение 0
		//Вывожу ошибку, что библиотека не загрузилась
		std::cout << "Ошибка. Библиотека не загрузилась!" << std::endl;
		//Выхожу из функции main
		exit(1);
	}

	//Структура, которая зранит информацию об адресе сокета
	//SOCKADDR_IN используется для интернет протокола
	SOCKADDR_IN addr;
	//Переменная, хранящая размер структуры SOCKADDR
	int sizeOfAddr = sizeof(addr);
	//sin_addr - это структура SOCKADDR_IN, которая хранит IP адрес
	addr.sin_addr.s_addr = inet_addr(
		//Здесь указан localhost, тоесть "этот компьютер"
		"127.0.0.1"
	);
	//sin_port - порт для идентификации программы поступающими данными
	addr.sin_port = htons(
		//Можно использовать любой порт, который не зарезервирован программой
		1111
	);
	//sin_family - семейство протоколов
	addr.sin_family =
		//Для интернет протоколов указывается константа AF_INET
		AF_INET;

	//Создаю новый сокет для соединения с сервером
	Connection = socket(
		//AF_INET означает, что будет использоваться семейство интернет протоколов
		AF_INET,
		//SOCK_STREAM указывает на протокол, устанавливающий интернет соединение
		SOCK_STREAM,
		//Этот параметр пока не нужен, поэтому NULL
		NULL
	);

	//Проверка на случай, если клиент не сможет соединиться с сервером
	if (
		//После создания сокета, нужно попытаться присоединиться к серверу
		connect(Connection, (SOCKADDR*)&addr, sizeof(addr))
		//Если не удалось подключиться
		!= 0
		)
	{
		//Тогда вывожу ошибку
		std::cout << "Ошибка: не получилось подключиться к серверу!\n";
		//И выхожу из программы
		return 1;
	}

	//В случае успеха вывожу в консоль, что подключился к серверу
	std::cout << "Подключение установлено!\n";

	//Запускаю функцию ClientHandler в новом потоке. ClientHandler не принимает никаких парам.
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);

	//if (packet == P_ChatMessage) {
	//	//Переменная для хранения сообщения
	//	char mesge[260];
	//	//Бесконечный цикл для считывания написанных пользователем символов и записи в переменную
	//	while (true) {
	//		//Записываю в неё написанную пользователем строку
	//		std::cin.getline(mesge, sizeof(mesge));
	//		//Отправляю тип пакета
	//		Packet packetType = P_ChatMessage;
	//		//Отправляю этот тип пакета серверу
	//		send(Connection, (char*)&packetType, sizeof(Packet), NULL);
	//		//Отправляю это сообщение
	//		send(Connection, mesge, sizeof(mesge), NULL);
	//		//Небольшая пауза после отправки сообщения
	//		Sleep(10);
	//	}
	//}

	if (true) {
		// Передаю данные из глобальной переменной
		//sf::RenderWindow window(sf::VideoMode(920, 580), "TDSLobodskoy");
		sf::RenderWindow window(sf::VideoMode(1920, 1080), "TDSLobodskoy", sf::Style::Fullscreen);

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
		int playerHealth = g_jsnFile["gameData"]["health"];
		//Игра продолжается или уже нет
		bool gameLife = g_jsnFile["gameData"]["gameLife"];
		//Хранит очки игрока
		int playerScore = g_jsnFile["gameData"]["score"];
		//Начинаю игру с первого уровея
		int gameLevel = g_jsnFile["gameData"]["gameLevel"];

		//Начальный баланс. Нужно будет сделать для каждого уровня свой
		int StartMoneyBalance = g_jsnFile["gameData"]["moneyBalance"];

		//Задаю начальное положение башни //Надо будет исправить, чтобы появлялась там, где мышка
		sf::Vector2f startPosTower(g_jsnFile["startPos"]["tower"]["x"], g_jsnFile["startPos"]["tower"]["y"]);

		//Начальное положение врага исходя из первой точки карты
		sf::Vector2f startPosEnemy(g_jsnFile["startPos"]["enemy"]["x"], g_jsnFile["startPos"]["enemy"]["y"]);

		//Объявляю игровую сцену
		Scene scene;
		//Объявляю фабрику врагов и передаю туда сцену

		EnemiesFactory enemiesFactory(scene, g_jsnFile);
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
				g_jsnFile["gameData"]["gameLife"] = gameLife;
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
			g_jsnFile["mouse"]["pos"]["x"] = posMouse.x;
			g_jsnFile["mouse"]["pos"]["y"] = posMouse.y;

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
			std::string* tileMap = new std::string[g_jsnFile["levelData"]["map"]["height"]];
			//Заполняю карту
			for (int i = 0; i < g_jsnFile["levelData"]["map"]["height"]; i++) {
				tileMap[i] = g_jsnFile["levelData"]["map"]["tileMap"][i];
			}
			//Отрисовка карты
			drawMap(spriteMap, window, tileMap, 
				g_jsnFile["levelData"]["map"]["height"], 
				g_jsnFile["levelData"]["map"]["width"]);


			float a = g_jsnFile["levelData"]["path"][0][1];

			//Отрисовка объектов сцены
			scene.Draw();
			//Вывожу на экран все изображения
			window.display();
		}
		
	}

	return 0;
}

//Функция для отрисовки спрайта. Используется в классе Entity
void DrawSprite(sf::Sprite sprite) {
	g_window->draw(sprite);
}