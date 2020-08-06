#pragma once
#include <iostream>
// ѕодключаю библиотеку дл€ работы с json файлами
#include <nlohmann/json.hpp>
// Ѕиблиотека чтени€ и записи из файла
#include <fstream>
#include <string>
// std::setw - потоковый манипул€тор
#include <iomanip>

using namespace std;
using namespace nlohmann;

void streamsSerDes() {
	// ¬ы также можете использовать потоки дл€ сериализации и десериализации :
	// десериализаци€ из стандартного ввода 
	json j;
	std::cin >> j;

	// сериализуем в стандартный вывод 
	std::cout << j;
	
	// манипул€тор setw был перегружен дл€ установки отступа дл€ красивой печати
	std::cout << std::setw(4) << j << std::endl;

	


}

void streamsOstrIstr() {
	// Ёти операторы работают дл€ любых подклассов std::istream или std::ostream. ¬от тот же пример с файлами:
	// читаем файл JSON 
	std::ifstream i("file.json");
	json j2;
	i >> j2;
	// записать предварительно подтвержденный JSON в другой файл 
	std::ofstream o("pretty.json");
	o << std::setw(4) << j2 << std::endl;
}