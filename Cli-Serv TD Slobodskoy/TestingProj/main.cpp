#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <WinSock2.h>
#include <iostream>
//Вывожу текст
#include <sstream>
//Подключаю вектор
#include <vector>
//Подключаю списки
#include <list>

// Подключаю библиотеку для работы с json файлами
#include <nlohmann/json.hpp>
// Библиотека чтения и записи из файла
#include <fstream>
#include "Read json.h"
#include "CreateJson.h"
#include "Serialization.h"


// Чтобы отключить предупреждение 4996 в файле, использую прагма-директиву warning
#pragma warning(disable : 4996)

using namespace sf;
using namespace std;
using namespace nlohmann;

int main() {
	//Делаю так, чтобы читался русский язык как при вводе текста, так и при выводе
	//Установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleCP(1251);
	//Установка кодовой страницы win-cp 1251 в поток вывода
	SetConsoleOutputCP(1251);

	string path = "../transfer_data.json";
	//readJson(path);

	//createJson();

	//serialization();

	serStr();
}