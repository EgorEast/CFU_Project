#pragma once
#include <iostream>
// Подключаю библиотеку для работы с json файлами
#include <nlohmann/json.hpp>
// Библиотека чтения и записи из файла
#include <fstream>
#include <string>

using namespace std;
using namespace nlohmann;

void openFile(fstream  *file, string path) {
	(*file).open(path,
		// Открывает файл на чтение
		fstream::in |
		// и на запсь
		fstream::out
		);
	//Проверка на открытие файла
	if (!(*file).is_open()) {
		cout << "Ошибка! Не получилось открыть файл 'transfer_data.json'";
	}
}
void closeFile(fstream* file) {

}

void readJson(string path) {
	fstream jsonWorkingFile;
	//Открываю файл
	openFile(&jsonWorkingFile, path);
	// Десериализация из файла в JSON объект.
	// явный анализ
	json jsonFile = json::parse(jsonWorkingFile);

	//Будет хранить информацию из файла "transfer_data.json"
	string templateСontent;


	//Записываю информацию из файла в строку
	getline(jsonWorkingFile, templateСontent, '\0');

	//for (int i = 0; i < sizeof(templateСontent); i++) {
		cout << templateСontent;
	//}
}
