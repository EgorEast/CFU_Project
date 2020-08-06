#pragma once
#include <iostream>
// Подключаю библиотеку для работы с json файлами
#include <nlohmann/json.hpp>
// Библиотека чтения и записи из файла
#include <fstream>
#include <string>
// std::setw - потоковый манипулятор
#include <iomanip>

using namespace std;
using namespace nlohmann;

void readItBegEnd() {

	// Вы также можете анализировать JSON из диапазона итераторов; то есть из любого контейнера, 
	// доступного для итераторов, чей value_typeтип составляет 1, 2 или 4 байта, что будет 
	// интерпретироваться как UTF-8, UTF-16 и UTF-32 соответственно. 
	// Например, или std::vector<std::uint8_t>, или std::list<std::uint16_t>:
	std::vector<std::uint8_t> v = { 't', 'r', 'u', 'e' };
	json j = json::parse(v.begin(), v.end());
	cout << j.dump(3);
}

void readItAll() {
	// Вы можете пропустить итераторы для диапазона [начало, конец):
	std::vector<std::uint8_t> v = { 't', 'r', 'u', 'e' };
	json j = json::parse(v);
	cout << j.dump(3);
}