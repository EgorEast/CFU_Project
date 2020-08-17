#include <iostream>
// Подключаю библиотеку для работы с json файлами
#include <nlohmann/json.hpp>
#include <string>

using namespace nlohmann;

std::string jsnToStr(json jsonFile) {
	// явное преобразование в строку 
	std::string str = jsonFile.dump();
	return str;
}