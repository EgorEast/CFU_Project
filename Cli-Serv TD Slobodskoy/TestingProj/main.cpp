#include <SFML/Graphics.hpp>
#include <iostream>
// ������ �����
#include <sstream>
// ��������� ������
#include <vector>
// ��������� ������
#include <list>
#include <string>


// ��������� ������ � ��������� ��������
#pragma comment(lib, "ws2_32.lib")
// ��������� ���������� ��� ������ � �����
#include <WinSock2.h>

#include <windows.h>

// ��������� ���������� ��� ������ � json �������
#include <nlohmann/json.hpp>
// ���������� ������ � ������ �� �����
#include <fstream>
#include "Read json.h"
#include "CreateJson.h"
#include "Serialization.h"
#include "jsonToString.h"
#include "streams.h"
#include "ReadFromIteratorRange.h"
#include "JsonPointAndPatch.h"

// ����� ��������� �������������� 4996 � �����, ��������� ������-��������� warning
#pragma warning(disable : 4996);

using namespace sf;
using namespace std;
using namespace nlohmann;

int main() {
	//����� ���, ����� ������� ������� ���� ��� ��� ����� ������, ��� � ��� ������
	//��������� ������� �������� win-cp 1251 � ����� �����
	SetConsoleCP(1251);
	//��������� ������� �������� win-cp 1251 � ����� ������
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

	// ����������, �������� ���������� �������� ���������
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