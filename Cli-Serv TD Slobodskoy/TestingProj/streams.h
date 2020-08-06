#pragma once
#include <iostream>
// ��������� ���������� ��� ������ � json �������
#include <nlohmann/json.hpp>
// ���������� ������ � ������ �� �����
#include <fstream>
#include <string>
// std::setw - ��������� �����������
#include <iomanip>

using namespace std;
using namespace nlohmann;

void streamsSerDes() {
	// �� ����� ������ ������������ ������ ��� ������������ � �������������� :
	// �������������� �� ������������ ����� 
	json j;
	std::cin >> j;

	// ����������� � ����������� ����� 
	std::cout << j;
	
	// ����������� setw ��� ���������� ��� ��������� ������� ��� �������� ������
	std::cout << std::setw(4) << j << std::endl;

	


}

void streamsOstrIstr() {
	// ��� ��������� �������� ��� ����� ���������� std::istream ��� std::ostream. ��� ��� �� ������ � �������:
	// ������ ���� JSON 
	std::ifstream i("file.json");
	json j2;
	i >> j2;
	// �������� �������������� �������������� JSON � ������ ���� 
	std::ofstream o("pretty.json");
	o << std::setw(4) << j2 << std::endl;
}