#include "Tower.h"
#include <iostream>

////////////////////////////////////////////////////КЛАСС БАШЕН////////////////////////
	Tower::Tower(Image& image, String Name, Vector2f startPos, int Width, int Height) :Entity(image, Name, startPos, Width, Height) {
		towerLevel = 0;
		if (name == "TowerOne") {	//Выводим участок изображения из текстуры: координаты левого верхнего угла х и у, ширина и высота картинки
			sprite.setTextureRect(IntRect(0, 0, width, height));
		}
		if (name == "TowerTwo") {
			sprite.setTextureRect(IntRect(58, 0, width, height));
		}
		if (name == "TowerThree") {
			sprite.setTextureRect(IntRect(117, 0, width, height));
		}
		if (name == "TowerFour") {
			sprite.setTextureRect(IntRect(175, 0, width, height));
		}
		life = true;
		dXMouse = 0, dYMouse = 0;
	}

	void Tower::update(Event& event, Vector2f posMouse, RenderWindow& window, float time) {	//функция "оживления" объекта класса
		control(event, posMouse, window);
		shooting(time);
		checkCollisionWithMap(event, posMouse, window);
	}

	void Tower::control(Event& event, Vector2f posMouse, RenderWindow& window) {
		if (health <= 0) { life = false; isShoot = false; }	//если жизней меньше либо равно 0, то умираем и исключаем стрельбу башни после смерти

		if (life) {
			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
				if (event.key.code == Mouse::Left)//а именно левая
					if (sprite.getGlobalBounds().contains(posMouse.x, posMouse.y))//и при этом координата курсора попадает в спрайт
					{
						//std::cout << "isClicked!\n";//выводим в консоль сообщение об этом
						dXMouse = posMouse.x - sprite.getPosition().x;//делаем разность между позицией курсора и спрайта.для корректировки нажатия
						dYMouse = posMouse.y - sprite.getPosition().y;//тоже самое по игреку
						isSelect = true;
						isMove = true;//можем двигать спрайт		//это пригодится когда будет уже стоять башня			
					}

			if (event.type == Event::MouseButtonReleased)//если отпустили клавишу
				if (event.key.code == Mouse::Left) { //а именно левую
					isSelect = false;
					isMove = false; //то не можем двигать спрайт
					sprite.setColor(Color::White);//и даем ему прежний цвет
				}


			if (isSelect && isMove) {//если можем двигать
				sprite.setColor(Color::Green);//красим спрайт в зеленый 
				sprite.setPosition(posMouse.x - dXMouse, posMouse.y - dXMouse);//Движение спрайта
				checkCollisionWithMap(event, posMouse, window);
			}
		}
	}
	
	void Tower::shooting(float time) { //Функция поведения для стрельбы

	}

	void Tower::checkCollisionWithMap(Event& event, Vector2f posMouse, RenderWindow& window) {

		
	}