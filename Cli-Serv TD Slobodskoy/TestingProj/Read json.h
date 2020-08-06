#pragma once
// ��������� ���������� ��� ������ � json �������
#include <nlohmann/json.hpp>
// ���������� ������ � ������ �� �����
#include <fstream>
#include <iostream>
#include <string>


using namespace nlohmann;
using namespace std;

json readJsonFile(string path) {
	ifstream jsonWorkingFile;
	// �������� ����
	jsonWorkingFile.open(path);
	//�������� �� �������� �����
	if (!jsonWorkingFile.is_open()) {
		cout << "������! �� ���������� ������� ���� 'transfer_data.json'";
	}
	// �������������� �� ����� � JSON ������.
	// ����� ������
	json jsonFile = json::parse(jsonWorkingFile);
	// �������� �������� ����
	jsonWorkingFile.close();

	//cout << jsonFile;

	return jsonFile;
}