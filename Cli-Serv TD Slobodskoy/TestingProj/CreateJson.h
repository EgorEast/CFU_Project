#pragma once
#include <iostream>
// Подключаю библиотеку для работы с json файлами
#include <nlohmann/json.hpp>
// Библиотека чтения и записи из файла
#include <fstream>
#include <string>

using namespace std;
using namespace nlohmann;

void createJson() {
    //С помощью этой библиотеки вы можете написать :

    // создать пустую структуру (null) 
    json j; 

    // добавить число, которое хранится как double (обратите внимание на неявное преобразование j в объект) 
    j["pi"] = 3.141; 

    // добавить логическое значение, которое сохраняется как bool 
    j["happy"] = true;

    // добавить строку, которая хранится как std :: string 
    j["name"] = "Niels";

    // добавляем еще один нулевой объект, передавая nullptr 
    j["nothing"] = nullptr;

    // добавить объект внутри объекта 
    j["answer"]["everything"] = 42;

    // добавить массив, который хранится как std :: vector (используя список инициализаторов) 
    j["list"] = { 1, 0, 2 };

    // добавляем другой объект (используя список пар инициализатора) 
    j["object"] = { {"currency", "USD"}, {"value", 42.99} };

    cout << j << endl << endl;
    
    // вместо этого вы также можете написать (что очень похоже на JSON выше) 
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