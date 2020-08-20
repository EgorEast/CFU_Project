#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"

////////////////////////////////////Общий класс-родитель//////////////////////////
//Конструктор
Entity::Entity(sf::Image& image, sf::String Name, sf::Vector2f startPos, int Width, int Height) {
	//Инициализируем переменные
	//Позиция объекта
	posObject.x = startPos.x; posObject.y = startPos.y;
	//Высота и ширина
	width = Width; height = Height; 
	//Имя
	name = Name;
	//Устанавливаем параметры по умолчанию
	speed = 0; health = 100;
	//Ускорение по х и у
	dx = 0; dy = 0; 
	//Говорю, что объект живой, не движется, не выбран
	life = true; isMove = false; isSelect = false;
	//Передаю в объект Texture объект Image (изображения)
	texture.loadFromImage(image);
	//Передаю в объект Sprite объект Texture (текстуры)
	sprite.setTexture(texture);
	//Задаю точку взаимодействия по середине спрайта
	sprite.setOrigin(width / 2, height / 2);
	//Вывожу спрайт в позицию x y
	sprite.setPosition(posObject.x, posObject.y);

	//Меня удалять не нужно
	deleteMe = false;
}

//Ф-ция получения прямоугольника: его координаты и размеры (ширина и высота).
sf::FloatRect Entity::getRect() {
	//Она нужна для проверки столкновений 
	return sf::FloatRect(posObject.x, posObject.y, width, height);
}

//Ф-ция получения позиции объекта
sf::Vector2f Entity::getPosition() {
	return (posObject);
}

bool Entity::getDeleteMe() {
	return deleteMe;
}