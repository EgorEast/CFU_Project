#include <iostream>
// ��������� ���������� ��� ������ � json �������
#include <nlohmann/json.hpp>
#include <string>

using namespace std;
using namespace nlohmann;

string jsnToStr(json jsonFile) {
	// ����� �������������� � ������ 
	string str = jsonFile.dump();
	return str;
}