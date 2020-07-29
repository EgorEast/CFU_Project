#pragma once
#include <iostream>
// ��������� ���������� ��� ������ � json �������
#include <nlohmann/json.hpp>
// ���������� ������ � ������ �� �����
#include <fstream>
#include <string>

using namespace std;
using namespace nlohmann;

void openFile(fstream  *file, string path) {
	(*file).open(path,
		// ��������� ���� �� ������
		fstream::in |
		// � �� �����
		fstream::out
		);
	//�������� �� �������� �����
	if (!(*file).is_open()) {
		cout << "������! �� ���������� ������� ���� 'transfer_data.json'";
	}
}

void readJson(string path) {
	fstream jsonFileRead;
	openFile(&jsonFileRead, path);
	json jsonFile;
	//����� ������� ���������� �� ����� "transfer_data.json"
	string template�ontent;


	//��������� ���������� �� ����� � ������
	getline(jsonFileRead, template�ontent, '\0');

	//for (int i = 0; i < sizeof(template�ontent); i++) {
		cout << template�ontent;
	//}
}
