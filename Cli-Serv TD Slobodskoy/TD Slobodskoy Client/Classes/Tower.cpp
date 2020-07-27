#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include<cmath>
#include "Tower.h"


////////////////////////////////////////////////////КЛАСС БАШЕН////////////////////////
//Конструктор класса
Tower::Tower(Image& image, String Name, Vector2f startPos, int Width, int Height, int& moneyBalance)
	:Entity(image, Name, startPos, Width, Height) {

	//Time = 0;


	_towerLevel = 0;
	//Выводим участок изображения из текстуры: координаты левого верхнего угла х и у, ширина и высота картинки
	if (name == "TowerOne") {	
		sprite.setTextureRect(IntRect(0, 0, width, height));
		//Устанавливаю цену на башню
		_towerPrice = 50;
	}
	if (name == "TowerTwo") {
		sprite.setTextureRect(IntRect(58, 0, width, height));
		_towerPrice = 70;
	}
	if (name == "TowerThree") {
		sprite.setTextureRect(IntRect(117, 0, width, height));
		_towerPrice = 100;
	}
	if (name == "TowerFour") {
		sprite.setTextureRect(IntRect(175, 0, width, height));
		_towerPrice = 150;
	}

	if (moneyBalance >= _towerPrice) _bought = true;
	else _bought = false;

	life = true;
	_dXMouse = 0, _dYMouse = 0;
}

//Узнать, могу ли купить башню
bool Tower::getIsBought() {
	return _bought;
}

int Tower::getTowerPrice() {
	return _towerPrice;
}

//Функция "оживления" объекта класса
void Tower::update(float time) {
	/*Vector2f posMouse = (Vector2f)Mouse::getPosition(window);
	float Rot = (float)(atan2(posMouse.x, posMouse.y) * 180 / 3.14);

	Vector2f Vel = posMouse / (float)sqrt(pow(posMouse.x,2)+ pow(posMouse.y, 2));

	if (Time > 0) Time -= 0.5f;

	shooting(Rot, Vel);*/
	if (!life) deleteMe = true;
}

//Обработка событий мыши
void Tower::onMouseEvent(Event& event, Vector2f posMouse, RenderWindow& window) {
	control (event, posMouse, window);
	checkCollisionWithMap (event, posMouse, window);
}

//Управление башней
void Tower::control(Event& event, Vector2f posMouse, RenderWindow& window) {
	//Если нажата клавиша мыши
	if (event.type == Event::MouseButtonPressed)
		//А именно левая
		if (event.key.code == Mouse::Left)
			//И при этом координата курсора попадает в спрайт
			if (sprite.getGlobalBounds().contains(posMouse.x, posMouse.y))
			{
				//выводим в консоль сообщение об этом
				//std::cout << "isClicked!\n";
				//Делаю разность между позицией курсора и спрайта.для корректировки нажатия
				_dXMouse = posMouse.x - sprite.getPosition().x;
				//тоже самое по игреку
				_dYMouse = posMouse.y - sprite.getPosition().y;
				//Объект становится выбранным
				isSelect = true;
				//могу двигать спрайт	//это пригодится когда будет уже стоять башня
				isMove = true;
			}

	//Если отпустили клавишу
	if (event.type == Event::MouseButtonReleased)
		//А именно левую
		if (event.key.code == Mouse::Left) {
			//Объект перестает быть выбранным
			isSelect = false;
			//Не можем двигать спрайт
			isMove = false;
			//Даем ему прежний цвет
			sprite.setColor(Color::White);
		}

	//Если можем двигать
	if (isSelect && isMove) {
		//Красим спрайт в зеленый
		sprite.setColor(Color::Green);
		//Движение спрайта
		sprite.setPosition(posMouse.x - _dXMouse, posMouse.y - _dXMouse);
		//Проверяю столкновения с объектами карты
		checkCollisionWithMap(event, posMouse, window);
	}
}
	
//Функция поведения для стрельбы
void Tower::shooting(/*float Rot, Vector2f Vel*/) {
	//Projectale p =  (new Projectale())

}

//Проверка столкновения с объектами карты
void Tower::checkCollisionWithMap(Event& event, Vector2f posMouse, RenderWindow& window) {

		
}