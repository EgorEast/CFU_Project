#include "Entity.h"

////////////////////////////////////Общий класс-родитель//////////////////////////

Entity::Entity(Image& image, String Name, Vector2f startPos, int Width, int Height) { //Конструктор
	posObject.x = startPos.x; posObject.y = startPos.y; width = Width; height = Height; name = Name; moveTimer = 0; //Инициализируем переменные
	speed = 0; health = 100; dx = 0; dy = 0; //Устанавливаем параметры по умолчанию
	life = true; isMove = false; isSelect = false;	//Устанавливаем параметры по умолчанию
	texture.loadFromImage(image); //передаем в объект Texture объект Image (изображения)
	sprite.setTexture(texture); //передаём в объект Sprite объект Texture (текстуры)
	sprite.setOrigin(width / 2, height / 2); //задаем точку взаимодействия
	sprite.setPosition(posObject.x, posObject.y);//выводим спрайт в позицию x y 
}

FloatRect Entity::getRect() { //ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
	return FloatRect(posObject.x, posObject.y, width, height); //эта ф-ция нужна для проверки столкновений 
}

Vector2f Entity::getPosition() {
	return (posObject);
}