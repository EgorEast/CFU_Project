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
void closeFile(fstream* file) {

}

void readJson(string path) {
	fstream jsonWorkingFile;
	//�������� ����
	openFile(&jsonWorkingFile, path);
	// �������������� �� ����� � JSON ������.
	// ����� ������
	json jsonFile = json::parse(jsonWorkingFile);

	//����� ������� ���������� �� ����� "transfer_data.json"
	string template�ontent;


	//��������� ���������� �� ����� � ������
	getline(jsonWorkingFile, template�ontent, '\0');

	//for (int i = 0; i < sizeof(template�ontent); i++) {
		cout << template�ontent;
	//}
}
