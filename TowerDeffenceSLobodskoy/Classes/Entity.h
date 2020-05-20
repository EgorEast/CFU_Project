#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
////////////////////////////////////Общий класс-родитель//////////////////////////
class Entity {
protected:
	Vector2f posObject;	//координаты наших предметов х и у
public:
	float dx, dy, speed, moveTimer; //ускорение (по х и по у), сама скорость, таймер для изменения напрвления по этому таймеру
	int height, width, health; //Высота и ширина спрайта, health- жизни объекта
	bool life, isMove, isSelect; //Состояние жизни, движения и выбора объекта
	Texture texture; //создаем объект Texture (текстура) объекта
	Sprite sprite; //создаем объект Sprite(спрайт) объекта
	String name; //Имя объекта

	Entity(Image& image, String Name, Vector2f startPos, int Width, int Height);	//Конструктор для класса Entity
	FloatRect getRect();	//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
};