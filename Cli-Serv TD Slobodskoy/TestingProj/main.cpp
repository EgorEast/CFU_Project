#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <WinSock2.h>
#include <iostream>
//������ �����
#include <sstream>
//��������� ������
#include <vector>
//��������� ������
#include <list>

// ��������� ���������� ��� ������ � json �������
#include <nlohmann/json.hpp>
// ���������� ������ � ������ �� �����
#include <fstream>
#include "Read json.h"
#include "CreateJson.h"
#include "Serialization.h"


// ����� ��������� �������������� 4996 � �����, ��������� ������-��������� warning
#pragma warning(disable : 4996)

using namespace sf;
using namespace std;
using namespace nlohmann;

int main() {
	//����� ���, ����� ������� ������� ���� ��� ��� ����� ������, ��� � ��� ������
	//��������� ������� �������� win-cp 1251 � ����� �����
	SetConsoleCP(1251);
	//��������� ������� �������� win-cp 1251 � ����� ������
	SetConsoleOutputCP(1251);

	string path = "../transfer_data.json";
	//readJson(path);

	//createJson();

	//serialization();

	serStr();
}