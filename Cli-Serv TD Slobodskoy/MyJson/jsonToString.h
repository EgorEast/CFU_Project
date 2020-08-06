#include <iostream>
// Подключаю библиотеку для работы с json файлами
#include <nlohmann/json.hpp>
#include <string>

using namespace std;
using namespace nlohmann;

string jsnToStr(json jsonFile) {
	// явное преобразование в строку 
	string str = jsonFile.dump();
	return str;
}