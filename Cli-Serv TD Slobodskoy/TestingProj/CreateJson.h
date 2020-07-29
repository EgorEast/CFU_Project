#pragma once
#include <iostream>
// ��������� ���������� ��� ������ � json �������
#include <nlohmann/json.hpp>
// ���������� ������ � ������ �� �����
#include <fstream>
#include <string>

using namespace std;
using namespace nlohmann;

void createJson() {
    //� ������� ���� ���������� �� ������ �������� :

    // ������� ������ ��������� (null) 
    json j; 

    // �������� �����, ������� �������� ��� double (�������� �������� �� ������� �������������� j � ������) 
    j["pi"] = 3.141; 

    // �������� ���������� ��������, ������� ����������� ��� bool 
    j["happy"] = true;

    // �������� ������, ������� �������� ��� std :: string 
    j["name"] = "Niels";

    // ��������� ��� ���� ������� ������, ��������� nullptr 
    j["nothing"] = nullptr;

    // �������� ������ ������ ������� 
    j["answer"]["everything"] = 42;

    // �������� ������, ������� �������� ��� std :: vector (��������� ������ ���������������) 
    j["list"] = { 1, 0, 2 };

    // ��������� ������ ������ (��������� ������ ��� ��������������) 
    j["object"] = { {"currency", "USD"}, {"value", 42.99} };

    cout << j << endl << endl;
    
    // ������ ����� �� ����� ������ �������� (��� ����� ������ �� JSON ����) 
    json j2 = {
      {"pi", 3.141},
      {"happy", true},
      {"name", "Niels"},
      {"nothing", nullptr},
      {"answer", {
        {"everything", 42}
      }},
      {"list", {1, 0, 2}},
      {"object", {
        {"currency", "USD"},
        {"value", 42.99}
      }}
    };

    cout << j2 << endl;
}