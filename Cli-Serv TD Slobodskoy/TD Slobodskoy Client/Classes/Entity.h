#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../main - Client.h"

////////////////////////////////////Общий класс-родитель//////////////////////////
class Entity {
public:
	//Конструктор для класса Entity
	Entity(sf::Image& image, sf::String Name, sf::Vector2f startPos, int Width, int Height);
	//Ф-ция получения прямоугольника: его координаты и размеры (ширина и высота).
	sf::FloatRect getRect();
	//Ф-ция получения позиции объекта
	sf::Vector2f getPosition();

	//Рисую объект. Делаю виртуальной и применяю во всех объектах класса
	virtual void Draw() {
		DrawSprite(sprite);
	}
	//Даю всем объектам движение. Делаю виртуальной и применяю во всех объектах класса
	virtual void update(float dt) = 0;
	//Функция обработки событий мыши. Делаю виртуальной и применяю во всех объектах класса
	virtual void onMouseEvent(sf::Event& event, sf::Vector2f posMouse, sf::RenderWindow& window) {}
	//Нужно для проверки на необходимость удаления объекта
	virtual bool getDeleteMe();
	// Функция для получения json файла
	void setJsonFile(nlohmann::json takeJsnFile);
	//Определение числа Пи с помощью одной из обратных тригонометрических функций
	const double PI = acos(-1.0);
protected:
	//Координаты наших предметов х и у
	sf::Vector2f posObject;
	//Ускорение по х и по у, скорость
	float dx, dy, speed;
	//Высота и ширина спрайта, жизни объекта
	int height, width, health;
	//Состояние жизни, движения и выбора объекта
	bool life, isMove, isSelect;
	//Создаю объект Texture (текстура) объекта
	sf::Texture texture;
	//Создаю объект Sprite(спрайт) объекта
	sf::Sprite sprite;
	//Имя объекта
	sf::String name;
	//Переменная для того, чтобы сказать, что нужно удалить этот объект
	bool deleteMe;
};