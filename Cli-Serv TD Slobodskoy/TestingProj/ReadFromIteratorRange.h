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

void readItBegEnd() {

	// �� ����� ������ ������������� JSON �� ��������� ����������; �� ���� �� ������ ����������, 
	// ���������� ��� ����������, ��� value_type��� ���������� 1, 2 ��� 4 �����, ��� ����� 
	// ������������������ ��� UTF-8, UTF-16 � UTF-32 ��������������. 
	// ��������, ��� std::vector<std::uint8_t>, ��� std::list<std::uint16_t>:
	std::vector<std::uint8_t> v = { 't', 'r', 'u', 'e' };
	json j = json::parse(v.begin(), v.end());
	cout << j.dump(3);
}

void readItAll() {
	// �� ������ ���������� ��������� ��� ��������� [������, �����):
	std::vector<std::uint8_t> v = { 't', 'r', 'u', 'e' };
	json j = json::parse(v);
	cout << j.dump(3);
}