#include <iostream>
// ��������� ���������� ��� ������ � json �������
#include <nlohmann/json.hpp>
#include <string>

std::string jsnToStr(nlohmann::json jsonFile) {
	// ����� �������������� � ������ 
	std::string str = jsonFile.dump();
	return str;
}