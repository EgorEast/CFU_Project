#include <iostream>
// Подключаю библиотеку для работы с json файлами
#include <nlohmann/json.hpp>
#include <string>

std::string jsnToStr(nlohmann::json jsonFile) {
	// явное преобразование в строку 
	std::string str = jsonFile.dump();
	return str;
}