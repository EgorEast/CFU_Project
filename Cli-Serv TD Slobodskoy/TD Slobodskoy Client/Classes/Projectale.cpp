#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Projectale.h"

////////////////////////////////////////////////////КЛАСС СНАРЯДОВ////////////////////////
//Конструктор класса снарядов
Projectale::Projectale(sf::Image& image, sf::String Name, sf::Vector2f startPos, int Width, int Height, float Rot, sf::Vector2f Vel)
	:Entity(image, Name, startPos, Width, Height) {
	//Если имя - "Пуля"
	if (name == "Bullet") {
		//width = height = 9;
		sprite.setTextureRect(sf::IntRect(0, 0, width, height));
		//Задаю скорость снаряду
		speed = 800;
	}

	/*this->Vel = Vel;
	Rotation = Rot;*/

	//direction = dir;
}

//Функция "оживления" объекта класса
void Projectale::update(float time) {
	if (life) {
		//Вызываю функцию движения
		move(time);
		collision();
		//Задаем позицию спрайта в место его центра
		sprite.setPosition(posObject.x + width / 2, posObject.y + height / 2);
	}
	//Если жизней меньше либо равно 0, то умираем и исключаем движение врага после смерти
	if (health <= 0) { life = false; speed = 0; }
}

//Движение пули
void Projectale::move(float time) {
	
	//posObject = Vel * speed;

	//switch ( direction)
	//{
	//case 0: dx = -speed; dy = 0;   break;//интовое значение state = left
	//case 1: dx = speed; dy = 0;   break;//интовое значение state = right
	//case 2: dx = 0; dy = -speed;   break;//интовое значение state = up
	//case 3: dx = 0; dy = -speed;   break;//интовое значение не имеющее отношения к направлению, пока просто стрельнем вверх, нам сейчас это не важно
	//case 4: dx = 0; dy = -speed;   break;//интовое значение не имеющее отношения к направлению, пока просто стрельнем вверх, нам сейчас это не важно
	//case 5: dx = 0; dy = -speed;   break;//интовое значение не имеющее отношения к направлению, пока просто стрельнем вверх, нам сейчас это не важно
	//}
	//posObject.x += dx * time;//само движение пули по х
	//posObject.y += dy * time;//по у
	//if (posObject.x <= 0) posObject.x = 1;// задержка пули в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки
	//if (posObject.y <= 0) posObject.y = 1;

	////Позиция врага
	//Vector2f me(posObject.x, posObject.y);
	////Точка в которую хочу переместиться. Забирает значения из Level_1.h
	//Vector2f goTo();

	////Переменная для определения направления
	//Vector2f dir = goTo - me;
	////Переменная для определения расстояния до точки взаимозействия
	//float len = sqrt(dir.x * dir.x + dir.y * dir.y);

	////Получаем единичный вектор направления
	//Vector2f direction = dir / len;

	////Следующая точка, в которой появится объект в следующий попент времени
	//Vector2f newMe = me + direction * speed * time;
	////Движение по x
	//posObject.x = newMe.x;
	////Движение по y
	//posObject.y = newMe.y;

	////Если расстояние до точки взаимодействия меньше скорости, то переключаемся на следующую точку
	//if (len < (speed * time))
	//{
	//	_curPointInd++;
	//}

	////Если дошли до финиша, то остановились и потеряли жизнь игрока
	//if (_curPointInd == points) { speed = 0; _ptrPlayerHealth--; life = false; }
}

//Взаимодействие с объектами
void Projectale::collision() {

}