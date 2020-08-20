// Подключаю библиотеку для работы с json файлами
#include <nlohmann/json.hpp>
// Библиотека чтения и записи из файла
#include <fstream>
#include <iostream>
#include <string>

//using namespace ;

nlohmann::json readJsonFile(std::string path) {
	std::ifstream jsonWorkingFile;
	// Открываю файл
	jsonWorkingFile.open(path);
	//Проверка на открытие файла
	if (!jsonWorkingFile.is_open()) {
		std::cout << "Ошибка! Не получилось открыть файл 'transfer_data.json'";
	}
	// Десериализация из файла в JSON объект.
	// явный анализ
	nlohmann::json jsonFile = nlohmann::json::parse(jsonWorkingFile);
	// Закрываю открытый файл
	jsonWorkingFile.close();

	//cout << jsonFile;

	return jsonFile;
}