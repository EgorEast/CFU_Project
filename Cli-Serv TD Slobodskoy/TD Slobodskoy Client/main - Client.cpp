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

SOCKET Connection;

//Перечисление для разных типов пакетов
enum Packet {
	//Отвечает за тип пакета
	P_ChatMessage,
	P_Json
};

Packet packet;

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
		json jsnFile;

		// Принимаю массив и записываю его
		recv(Connection, jsnChr, numSym, NULL);

		// Создаю строку, которую буду преобразовывать в json
 		std::string jsnStr;
		// Заполняю строку символами из принятого массва
		for (int i = 0; i < numSym; i++) jsnStr.push_back(jsnChr[i]);

		// Произвожу парсинг строки
		jsnFile = json::parse(jsnStr);

		//Вывожу принятый json файл на экран
		std::cout << jsnFile.dump(3) << std::endl;

		// Небольшая задержка 
		Sleep(10);
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

	if (packet == P_ChatMessage) {
		//Переменная для хранения сообщения
		char mesge[260];
		//Бесконечный цикл для считывания написанных пользователем символов и записи в переменную
		while (true) {
			//Записываю в неё написанную пользователем строку
			std::cin.getline(mesge, sizeof(mesge));
			//Отправляю тип пакета
			Packet packetType = P_ChatMessage;
			//Отправляю этот тип пакета серверу
			send(Connection, (char*)&packetType, sizeof(Packet), NULL);
			//Отправляю это сообщение
			send(Connection, mesge, sizeof(mesge), NULL);
			//Небольшая пауза после отправки сообщения
			Sleep(10);
		}
	}
	if (packet == P_Json) {


	}



	system("pause");
	return 0;
}