// ��������� ���������� ��� ������ � json �������
#include <nlohmann/json.hpp>
// ���������� ������ � ������ �� �����
#include <fstream>
#include <iostream>
#include <string>

//using namespace ;

nlohmann::json readJsonFile(std::string path) {
	std::ifstream jsonWorkingFile;
	// �������� ����
	jsonWorkingFile.open(path);
	//�������� �� �������� �����
	if (!jsonWorkingFile.is_open()) {
		std::cout << "������! �� ���������� ������� ���� 'transfer_data.json'";
	}
	// �������������� �� ����� � JSON ������.
	// ����� ������
	nlohmann::json jsonFile = nlohmann::json::parse(jsonWorkingFile);
	// �������� �������� ����
	jsonWorkingFile.close();

	//cout << jsonFile;

	return jsonFile;
}