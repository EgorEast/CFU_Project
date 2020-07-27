#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../main.h"


using namespace sf;
////////////////////////////////////Общий класс-родитель//////////////////////////
class Entity {
public:
	//Конструктор для класса Entity
	Entity(Image& image, String Name, Vector2f startPos, int Width, int Height);
	//Ф-ция получения прямоугольника: его координаты и размеры (ширина и высота).
	FloatRect getRect();
	//Ф-ция получения позиции объекта
	Vector2f getPosition();

	//Рисую объект. Делаю виртуальной и применяю во всех объектах класса
	virtual void Draw() {
		DrawSprite(sprite);
	}
	//Даю всем объектам движение. Делаю виртуальной и применяю во всех объектах класса
	virtual void update(float dt) = 0;
	//Функция обработки событий мыши. Делаю виртуальной и применяю во всех объектах класса
	virtual void onMouseEvent(Event& event, Vector2f posMouse, RenderWindow& window) {}
	//Нужно для проверки на необходимость удаления объекта
	virtual bool getDeleteMe();
	//Определение числа Пи с помощью одной из обратных тригонометрических функций
	const double PI = acos(-1.0);
protected:
	//Координаты наших предметов х и у
	Vector2f posObject;
	//Ускорение по х и по у, скорость
	float dx, dy, speed;
	//Высота и ширина спрайта, жизни объекта
	int height, width, health;
	//Состояние жизни, движения и выбора объекта
	bool life, isMove, isSelect;
	//Создаю объект Texture (текстура) объекта
	Texture texture;
	//Создаю объект Sprite(спрайт) объекта
	Sprite sprite;
	//Имя объекта
	String name;
	//Переменная для того, чтобы сказать, что нужно удалить этот объект
	bool deleteMe;
};