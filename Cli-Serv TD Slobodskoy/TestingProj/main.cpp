#include <SFML/Graphics.hpp>
#include <iostream>
// Вывожу текст
#include <sstream>
// Подключаю вектор
#include <vector>
// Подключаю списки
#include <list>
#include <string>


// Открывает доступ к некоторым функциям
#pragma comment(lib, "ws2_32.lib")
// Подключаю библиотеку для работы с сетью
#include <WinSock2.h>

#include <windows.h>

// Подключаю библиотеку для работы с json файлами
#include <nlohmann/json.hpp>
// Библиотека чтения и записи из файла
#include <fstream>
#include "Read json.h"
#include "CreateJson.h"
#include "Serialization.h"
#include "jsonToString.h"
#include "streams.h"
#include "ReadFromIteratorRange.h"
#include "JsonPointAndPatch.h"

// Чтобы отключить предупреждение 4996 в файле, использую прагма-директиву warning
#pragma warning(disable : 4996);

using namespace sf;
using namespace std;
using namespace nlohmann;

int main() {
	//Делаю так, чтобы читался русский язык как при вводе текста, так и при выводе
	//Установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleCP(1251);
	//Установка кодовой страницы win-cp 1251 в поток вывода
	SetConsoleOutputCP(1251);

	/*std::string str = "asdadsdd12";

	char chr[11];
	for (int i = 0; i < 11; i++) chr[i] = str[i];

	cout << "this is chars array: ";
	for (int i = 0; i < 11; i++) cout << chr[i];
	cout << endl;

	for (int i = 0; i < 11; i++) chr[i] = str[i];

	for (int i = 0; i < 11; i++) str[i] = chr[i];
	cout << "this is string: ";
	cout << str;*/

	// Переменная, хранящяя переданное клиентом сообщение
	//const short int numSym = 800;
	json jsnFile;
	std::string patToJson = "../transfer_data.json";
	jsnFile = readJsonFile(patToJson);
	std::string jsnStr = jsnFile.dump();
	//std::cout << jsnStr;
	int numSym = jsnStr.length();
	char *jsnChr = new char[numSym];
	

	for (int i = 0; i < numSym; i++) jsnChr[i] = jsnStr[i];

	for (int i = 0; i < numSym; i++) std::cout << jsnChr[i];


	/*string path = "../transfer_data.json";
	json jsonObj = readJsonFile(path);
	string jsonStr = jsnToStr(jsonObj);

	jsonObj["gameData"]["gameLevel"] = 2;

	float numFloatArr[6][2] = {
		{2,3},
		{4,5},
		{6,7},
		{8,9},
		{10,11},
		{12,13}
	};

	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 2; j++)
			jsonObj["levelData"]["path"][i][j] = numFloatArr[i][j];


	cout << jsonObj.dump(3);*/

	/*for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 2; j++) {
			cout << jsonObj["levelData"]["path"][i][j] << ", ";
		}
		cout << endl;
	}*/

	//int health = jsonObj["gameData"]["health"];
	//cout << health;

	//createJson();

	//serialization();

	//serStr();

	//cout << jsonObj;

	//streamsSerDes();
	//streamsOstrIstr();

	//readItBegEnd();
	//readItAll();

	//jsnPntAndPtch();

}