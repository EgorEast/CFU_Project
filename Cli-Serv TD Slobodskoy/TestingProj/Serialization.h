#pragma once
#include <iostream>
// Подключаю библиотеку для работы с json файлами
#include <nlohmann/json.hpp>
// Библиотека чтения и записи из файла
#include <fstream>
#include <string>

using namespace std;
using namespace nlohmann;


void serialization() {
	auto j = json::parse("{ \"happy\": true, \"pi\": 3.141 }");

	// явное преобразование в строку 
	std::string s = j.dump();    // {"happy": true, "pi": 3.141} 

	// сериализация с красивой печатью 
	// передаем количество пробелов в отступ 
	std::cout << j.dump(4) << std::endl;
	// { 
	//      "happy": true, 
	//      "pi": 3.141 
	// }
}
void serStr() {
	// сохранить строку в значении JSON 
	json j_string = "this is a string";

	// получить строковое значение
	auto cpp_string = j_string.get<std::string>();
	// получить строковое значение (альтернативно, когда переменная уже существует) 
	std::string cpp_string2;
	j_string.get_to(cpp_string2);

	// получить сериализированное значение (явно JSON сериализации) 
	std::string serialized_string = j_string.dump();

	// вывод исходной строки 
	std::cout << cpp_string << " == " << cpp_string2 << " == " << j_string.get<std::string>() << '\n';
	// вывод сериализованного значения
	std::cout << j_string << " == " << serialized_string << std::endl;

}