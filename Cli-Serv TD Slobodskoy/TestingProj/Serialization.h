#pragma once
#include <iostream>
// ��������� ���������� ��� ������ � json �������
#include <nlohmann/json.hpp>
// ���������� ������ � ������ �� �����
#include <fstream>
#include <string>

using namespace std;
using namespace nlohmann;


void serialization() {
	auto j = json::parse("{ \"happy\": true, \"pi\": 3.141 }");

	// ����� �������������� � ������ 
	std::string s = j.dump();    // {"happy": true, "pi": 3.141} 

	// ������������ � �������� ������� 
	// �������� ���������� �������� � ������ 
	std::cout << j.dump(4) << std::endl;
	// { 
	//      "happy": true, 
	//      "pi": 3.141 
	// }
}
void serStr() {
	// ��������� ������ � �������� JSON 
	json j_string = "this is a string";

	// �������� ��������� ��������
	auto cpp_string = j_string.get<std::string>();
	// �������� ��������� �������� (�������������, ����� ���������� ��� ����������) 
	std::string cpp_string2;
	j_string.get_to(cpp_string2);

	// �������� ����������������� �������� (���� JSON ������������) 
	std::string serialized_string = j_string.dump();

	// ����� �������� ������ 
	std::cout << cpp_string << " == " << cpp_string2 << " == " << j_string.get<std::string>() << '\n';
	// ����� ���������������� ��������
	std::cout << j_string << " == " << serialized_string << std::endl;

}