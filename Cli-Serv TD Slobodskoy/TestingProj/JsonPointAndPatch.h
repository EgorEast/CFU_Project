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

void jsnPntAndPtch() {
	// JSON переменная
	json j_original = R"({
	"baz": ["one", "two", "three"],
	"foo": "bar"
	})"_json;

	// доступ к членам с помощью указателя JSON (RFC 6901) 
	j_original["/baz/1"_json_pointer];
	// "two"

	// патч JSON (RFC 6902) 
	json j_patch = R"([
		{ "op": "replace", "path": "/baz", "value": "boo" },
		{ "op": "add", "path": "/hello", "value": ["world"] },
		{ "op": "remove", "path": "/foo"}
	])"_json;

	// применить патч
	json j_result = j_original.patch(j_patch);
	// {
	//    "baz": "boo",
	//    "hello": ["world"]
	// }

	//cout << j_result.dump(3);

	// вычисляем JSON-патч из двух значений JSON 
	json::diff(j_result, j_original);
	// [
	//   { "op":" replace", "path": "/baz", "value": ["one", "two", "three"] },
	//   { "op": "remove","path": "/hello" },
	//   { "op": "add", "path": "/foo", "value": "bar" }
	// ]
	cout << j_original.dump(3);
}