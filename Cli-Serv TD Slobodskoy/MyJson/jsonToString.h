#include <iostream>
// ��������� ���������� ��� ������ � json �������
#include <nlohmann/json.hpp>
#include <string>

using namespace nlohmann;

std::string jsnToStr(json jsonFile) {
	// ����� �������������� � ������ 
	std::string str = jsonFile.dump();
	return str;
}