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
// Убираю ошибку
#pragma warning(disable: 4996)

// Подключаю свой код
#include "Levels.h"

//Создаю массив сокетов для хранения нескольких подключений
SOCKET Connections[100];
//// Переменная, хранящая индекс соединения
//int Counter = 0;

// Глобальная переменная для хранения json файла
nlohmann::json g_jsnFile;

// Перечисление для разных типов пакетов
enum Packet {
	//Отвечает за тип пакета
	P_ChatMessage,
	P_Json
};

// Ф-ция для обработки приходящих пакетов
bool ProcessPacket(int index, Packet packetType) {
	switch (packetType) {

		// Принятие отправленного сервером сообщения
	case P_ChatMessage: {
		// Переменная, хранящяя переданное клиентом сообщение
		char msg[260];
		recv(Connections[index], msg, sizeof(msg), NULL);
		// Цикл для отправки полученного сообщения всем клиентам до того, кто отправил
		for (int i = 0; i < index; i++) {
			// Отправляю тип пакета
			Packet msgTypeC = P_ChatMessage;
			send(Connections[i], (char*)&msgTypeC, sizeof(Packet), NULL);
			// Отправляю сообщение
			send(Connections[i], msg, sizeof(msg), NULL);
		}
		// Пропускаю себя и отправляю остальным
		for (int i = index + 1; i < 100; i++) {
			//Отправляю тип пакета
			Packet msgtype = P_ChatMessage;
			send(Connections[i], (char*)&msgtype, sizeof(Packet), NULL);
			// Отправляю сообщение
			send(Connections[i], msg, sizeof(msg), NULL);
		}
		break;
	}
	case P_Json: {
		std::cout << "json прилетел";
		// Переменная для хранения размера массива
		int numSym;
		// Принимаю размер массива и записываю в переменную
		recv(Connections[index], (char*)&numSym, sizeof(int), NULL);
		std::cout << "Json пакет принят.\n";
		//Переменная для хранения переданной строки
		char* jsnChr = new char[numSym];

		// Переменная для хранения переданной json файла
		nlohmann::json jsnFile;

		// Принимаю массив и записываю его
		recv(Connections[index], jsnChr, numSym, NULL);

		// Создаю строку, которую буду преобразовывать в json
		std::string jsnStr;
		// Заполняю строку символами из принятого массва
		for (int i = 0; i < numSym; i++) jsnStr.push_back(jsnChr[i]);

		// Произвожу парсинг строки
		jsnFile = nlohmann::json::parse(jsnStr);
		
		// Произвести какие-то действия
		//
		//
		//
		
		// Отправляю файл обратно клиенту

		// Преобразую его в строку
		jsnStr = jsnFile.dump();

		// Переменная для хранения длины строки
		numSym = jsnStr.length();
		// Динамический массив символов для в который размещу полученную строку
		jsnChr = new char[numSym];
		// Заполняю массив данными из строки
		for (int i = 0; i < numSym; i++) jsnChr[i] = jsnStr[i];

		// Отправляю тип пакета
		Packet msgTypeJ = P_Json;
		send(Connections[index], (char*)&msgTypeJ, sizeof(Packet), NULL);
		// Теперь отправлю размер массива
		send(Connections[index], (char*)&numSym, sizeof(numSym), NULL);
		// Отправляю массив чаров
		send(Connections[index], jsnChr, numSym, NULL);

		//Небольшая пауза после отправки файла
		Sleep(10);
		break;
		//// Задержка на 5 секунд
		//Sleep(5000);
	}
	default:
		std::cout << "Пакет не был принят: " << packetType << std::endl;
		
		return false;
	}

	// Если пакет обработан успешно, тогда true
	return true;
}

// Обработчик клиента
// Функция принимающая индекс соединения в сокет массиве
void clientHandler(int index) {
	// Хранит тип пакета
	Packet packetType;
	while (true) {
		// Принимаю и записываю тип пакета в packetType
		recv(Connections[index], (char*)&packetType, sizeof(Packet), NULL);
		// Проверка на возвращаемое значение ф-ции
		if (!
			// Вызываю и передаю пакет ф-ции ProcessPacket
			ProcessPacket(index, packetType)) {
			// Если не удалось обработать пакет, то выхожу из цикла
			break;
		}
	}
	// Вышел из цикла -> закрываю сокет
	closesocket(Connections[index]);
}

int main() {
	// Делаю так, чтобы читался русский язык как при вводе текста, так и при выводе
	// Установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleCP(1251);
	// Установка кодовой страницы win-cp 1251 в поток вывода
	SetConsoleOutputCP(1251);

	//Функция для загрузки библиотеки
	//WSAStartup

	// Создаю структуру wsaData
	WSAData wsaData;
	// Создаю переменную WORD
	WORD DLLVEersion =
		// Это запрашиваемая версия библиотеки WinSock
		MAKEWORD(2, 1);
	// Делаю проверку. Если библиотека загрузилась удачно
	if (
		// Функция для загрузки библиотеки
		WSAStartup(
			// Передаю запрашиваемую версию библиотеки
			DLLVEersion,
			// Ссылка на структуру wsaData
			&wsaData)
		// Тогда она вернет значение 0
		!= 0
		)
	{
		// Если WSAStartup не вернет значение 0
		// Вывожу ошибку, что библиотека не загрузилась
		std::cout << "Ошибка. Библиотека не загрузилась!" << std::endl;
		// Выхожу из функции main
		exit(1);
	}

	// Структура, которая хранит информацию об адресе сокета
	// SOCKADDR_IN используется для интернет протокола
	SOCKADDR_IN addr;
	// Переменная, хранящая размер структуры SOCKADDR
	int sizeOfAddr = sizeof(addr);
	// sin_addr - это структура SOCKADDR_IN, которая хранит IP адрес
	addr.sin_addr.s_addr = inet_addr(
		// Здесь указан localhost, тоесть "этот компьютер"
		"127.0.0.1"
	);
	// sin_port - порт для идентификации программы поступающими данными
	addr.sin_port = htons(
		// Можно использовать любой порт, который не зарезервирован программой
		1111
	);
	// sin_family - семейство протоколов
	addr.sin_family =
		// Для интернет протоколов указывается константа AF_INET
		AF_INET;

	/* Чтобы два компьютера смогли установить соединение,
	один из них должен запустить прослушивание на определенном порту */

	// Создаю Сокет sListen, которому присвоил результат выполнения функции socket()
	SOCKET sListen = socket(
		// AF_INET означает, что будет использоваться семейство интернет протоколов
		AF_INET,
		// SOCK_STREAM указывает на протокол, устанавливающий интернет соединение
		SOCK_STREAM,
		// Этот параметр пока не нужен, поэтому NULL
		NULL
	);

	// Привязываю адрес сокету
	bind(
		// Предварительно созданный сокет
		sListen,
		// Указатель на структуру SOCKADDR
		(SOCKADDR*)&addr,
		// Размер структуры SOCKADDR
		sizeof(addr)
	);

	// Прослушивание порта в ожидании соединения со стороны клиента
	listen(
		// Пепредаю сокет
		// По этим данным функция определит по какому порту необходимо запустить прослушивание
		sListen,
		// Максимально допустимое число запросов ожидающих обработки
		SOMAXCONN);

	// Принимаю соединение

	// Создаю новый сокет, чтобы удерживать соединение с клиентом
	SOCKET newConnection;

	// Делаю выбор, чтобы значть какой пакет отправлять
	std::string typeProg;
	std::cout << "Если хочешь зайти в чат введи - 'Ch'. Если хочешь начать игру - 'Gm': ";
	do {
		std::cin >> typeProg;
		// Проверка на корректность
		if (typeProg != "Ch" && typeProg != "Gm") {
			std::cout << "Некорректно введён тип программы! Повтори ввод: ";
		}
	} while (typeProg != "Ch" && typeProg != "Gm");
	std::cout << std::endl;
	std::cout << "Будет обработано 100 подключений." << std::endl;

	std::cout << "Ожидаю подключения Клиента." << std::endl;

	// Переменная для храниения прочитанного json файла в формате json
	nlohmann::json jsnFile;
	// Путь к json файлу
	std::string patToJson = "../transfer_data.json";
	// Открываю файл
	jsnFile = readJsonFile(patToJson);

	if (typeProg == "Gm") {
		//Хранит жизни игрока
		int playerHealth = 20;
		jsnFile["gameData"]["health"] = playerHealth;

		//Игра продолжается или уже нет
		bool gameLife = true;
		jsnFile["gameData"]["gameLife"] = gameLife;

		//Хранит очки игрока
		int playerScore = 0;
		jsnFile["gameData"]["score"] = playerScore;

		//Начинаю игру с первого уровея
		int gameLevel = 1;
		jsnFile["gameData"]["gameLevel"] = gameLevel;

		//Начальный баланс. Нужно будет сделать для каждого уровня свой
		int StartMoneyBalance = 100;
		jsnFile["gameData"]["moneyBalance"] = StartMoneyBalance;

		//Задаю начальное положение башни //Надо будет исправить, чтобы появлялась там, где мышка
		sf::Vector2f startPosTower(200, 200);
		jsnFile["startPos"]["tower"]["x"] = startPosTower.x;
		jsnFile["startPos"]["tower"]["y"] = startPosTower.y;

		//Начальное положение врага исходя из первой точки карты
		sf::Vector2f startPosEemy(path[0][0], path[0][1]);
		jsnFile["startPos"]["enemy"]["x"] = startPosEemy.x;
		jsnFile["startPos"]["enemy"]["y"] = startPosEemy.y;

		// Отправляю данные карты 1-го уровня
		jsnFile["levelData"]["map"]["height"] = HEIGHT_MAP;
		jsnFile["levelData"]["map"]["width"] = WIDTH_MAP;

		jsnFile["levelData"]["points"] = points;

		for (int i = 0; i < points; i++) {
			for (int j = 0; j < 2; j++) {
				jsnFile["levelData"]["path"][i][j] = path[i][j];
			}
		}

		for (int i = 0; i < HEIGHT_MAP; i++) {
			jsnFile["levelData"]["map"]["tileMap"][i] = TileMap[i];
		}


	}

	// Цикл, обрабатывающий 100 соединения
	for (int i = 0; i < 100; i++) {
		// Принял новое соединение
		// accept возвращает указатель на новый сокет
		newConnection = accept(
			// Только что созданный и запущенный на прослушивание сокет
			sListen,
			// Указатель на структуру
			(SOCKADDR*)&addr,
			// Ссылка на размер структуры 
			&sizeOfAddr
		);
		

		// Если accept() вернет нулевое значение, значит клиент не смог подключиться к серверу
		// На этот случай проверка
		if (newConnection == 0)
			std::cout << "Ошибка. Клиент не смог подключиться к серверу!\n";
		// Если соединение прошло
		else {
			std::cout << "Клиент подключился к серверу!\n";

			if (typeProg == "Ch") {
				char msg[256] = "Привет. Ты зашёл в чат! Напиши сообщение\n";
				// Посылаю эту строчку клиенту

				// Отправляю тип пакета
				Packet msgtype = P_ChatMessage;
				send(newConnection, (char*)&msgtype, sizeof(Packet), NULL);
				// Отправляю сообщение
				send(
					/* Сокет, который хранит соединение с пользователем,
					которуму необходимо отправить строчку */
					newConnection,
					// Сама строчка
					msg,
					// Размер строчки
					sizeof(msg),
					// Пока не нужен
					NULL
				);
			}
			if (typeProg == "Gm") {
				// Преобразую json файл в строку
				std::string jsnStr = jsnFile.dump();
				// Переменная для хранения длины строки
				int numSym = jsnStr.length();
				// Динамический массив символов для в который размещу полученную строку
				char* jsnChr = new char[numSym];
				// Заполняю массив данными из строки
				for (int i = 0; i < numSym; i++) jsnChr[i] = jsnStr[i];
								
				// Отправляю тип пакета
				Packet msgTypeJ = P_Json;
				send(newConnection, (char*)&msgTypeJ, sizeof(Packet), NULL);

				// Теперь отправлю размер массива
				send(newConnection, (char*)&numSym, sizeof(numSym), NULL);
				// Отправляю массив чаров
				send(newConnection, jsnChr, numSym, NULL);
			}

			
			// Передаю в массив данное соединение
			Connections[i] = newConnection;
			//Counter++;

			// После выполнения данной функции сразу будут работать два потока или несколько\
			// Создю поток функцией CreateThread
			CreateThread(NULL, NULL,
				// В которой будет выполняться функция clientHandler()
				// Это указатель на процедуру, с которой следует начать выполнение потока
				(LPTHREAD_START_ROUTINE)clientHandler,
				// С переданным параметром i
				// Это аргумент процедуры переданной предыдущим аргументом
				// (обычно здесь указатель на некую структуру)
				(LPVOID)(i),
				// Флаг
				NULL,
				// Куда стоит записать ThreadId созданного потока
				// В случае успеха процедура возвратит Handle созданного потока. 
				// В случае ошибки возвращается нулевое значение
				NULL);

		}
	}

	system("pause");
	return 0;
}