#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "map.h"
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

	Entity(Image& image, String Name, Vector2f startPos, int Width, int Height) { //Конструктор для класса Entity
		posObject.x = startPos.x; posObject.y = startPos.y; width = Width; height = Height; name = Name; moveTimer = 0; //Инициализируем переменные
		speed = 0; health = 100; dx = 0; dy = 0; //Устанавливаем параметры по умолчанию
		life = true; isMove = false; isSelect = false;	//Устанавливаем параметры по умолчанию
		texture.loadFromImage(image); //передаем в объект Texture объект Image (изображения)
		sprite.setTexture(texture); //передаём в объект Sprite объект Texture (текстуры)
		sprite.setOrigin(width / 2, height / 2); //задаем точку взаимодействия
		sprite.setPosition(posObject.x, posObject.y);//выводим спрайт в позицию x y 
	}
	FloatRect getRect() { //ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
		return FloatRect(posObject.x, posObject.y, width, height); //эта ф-ция нужна для проверки столкновений 
	}
	virtual void update(float time) = 0; //Виртуальная функция для Обновления событий//Её необходимо переопределять в каждом классе
};

////////////////////////////////////////////////////КЛАСС БАШЕН////////////////////////
class Tower :public Entity { //Наследуется от класса Entity
public:
	int towerLevel;
	bool isShoot; //Переменная для определения состояния стреляет объект или нет
	float dXMouse, dYMouse;

	Tower(Image& image, String Name, Vector2f startPos, int Width, int Height) :Entity(image, Name, startPos, Width, Height) {
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

	void updateTower(Event& event, Vector2f posMouse, RenderWindow& window, float time) {	//функция "оживления" объекта класса
		control(event, posMouse, window);
		shooting(time);
		checkCollisionWithMap(event, posMouse, window);
	}

	void control(Event& event, Vector2f posMouse, RenderWindow& window) {
		if (health <= 0) { life = false; isShoot = false; }	//если жизней меньше либо равно 0, то умираем и исключаем стрельбу башни после смерти

		if (life) {
			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
				if (event.key.code == Mouse::Left)//а именно левая
					if (sprite.getGlobalBounds().contains(posMouse.x, posMouse.y))//и при этом координата курсора попадает в спрайт
					{
						std::cout << "isClicked!\n";//выводим в консоль сообщение об этом
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
	
	void shooting(float time) { //Функция поведения для стрельбы

	}

	void checkCollisionWithMap(Event& event, Vector2f posMouse, RenderWindow& window) {

		
	}

	void update(float time) {}	//Объявляю виртуальную функцию, чтобы не было ошибки
};



////////////////////////////////////////////////////КЛАСС ВГРАГОВ////////////////////////
class Enemy :public Entity {
public:
	int* ptrPlayerHealth;

	Enemy(Image& image, String Name, Vector2f startPos, int Width, int Height, int &playerHealth) :Entity(image, Name, startPos, Width, Height) {
		ptrPlayerHealth = &playerHealth;
		if (name == "Shooter") {
			sprite.setTextureRect(IntRect(0, 0, width, height)); //16*50
			speed = 0.2; //Задаём скорость
			health = 50;
		}
		if (name == "Tank") {
			sprite.setTextureRect(IntRect(64, 0, width, height)); //30*50
			speed = 0.1;
			health = 200;
		}
		if (name == "Plane") {
			sprite.setTextureRect(IntRect(128, 0, width, height)); //49*50
			speed = 0.3;
			health = 130;
		}
		life = true;
		//dx = speed;	//Идет направо со скоростью speed
		//dy = 0;	//Начальную скорость по dy зануляем
	}

	void update(float time) {	//функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая врагу движение.

		if (life) {
			move(time);

			//switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
			//{
			//case 0: dx = speed; dy = 0; break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что враг идет только вправо
			//case 1: dx = -speed; dy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что враг идет только влево
			//case 2: dx = 0; dy = speed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что враг идет только вниз
			//case 3: dx = 0; dy = -speed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что враг идет только вверх
			//case 4: dx = 0; dy = 0; break;//Если дошли до финиша, то остановились
			//}

			//if (dy == 0) { posObject.x += dx * time; }//это движение. наше ускорение на время получаем смещение координат и как следствие движение
			//if (dx == 0) { posObject.y += dy * time; }//аналогично по игреку
			sprite.setPosition(posObject.x + width / 2, posObject.y + height / 2); //задаем позицию спрайта в место его центра
			if (health <= 0) { life = false; speed = 0; }//если жизней меньше либо равно 0, то умираем и исключаем движение врага после смерти
		}
	}

	int curPointInd = 1;

	void move(float time) //Правила, по которым будет двигаться враг
	{	
		Vector2f me(posObject.x, posObject.y); //Позиция врага
		Vector2f goTo(path[curPointInd][0], path[curPointInd][1]);	//Точка в которую хочу переместиться//Забирает значения из Level_1.h
																	//

		Vector2f dir = goTo - me;	//Переменная для определения направления
		float len = sqrt(dir.x * dir.x + dir.y * dir.y);	//Переменная для определения расстояния до точки взаимозействия

		Vector2f direction = dir / len;	//Получаем единичный вектор направления

		Vector2f newMe = me + direction * speed * time;	//Следующая точка, в которой появится объект в следующий попент времени
		posObject.x = newMe.x;	//Движение по x
		posObject.y = newMe.y;	//Движение по y
		
		if (len < speed) curPointInd++;	//Если расстояние до точки взаимодействия меньше скорости, то переключаемся на следующую точку
		
		if (curPointInd == points) { speed = 0; ptrPlayerHealth--; }	//Если дошли до финиша, то остановились и потеряли жизнь игрока

		//if (dy == 0) { checkCollisionWithMap(dx, 0); }//обрабатываем столкновение по Х
		//if (dx == 0) { checkCollisionWithMap(0, dy); }//обрабатываем столкновение по Y
	}

	//void checkCollisionWithMap(float Dx, float Dy) {//ф ция проверки столкновений с картой
	//	for (int i = posObject.y / 64; i < (posObject.y + height) / 64; i++)//проходимся по элементам карты
	//		for (int j = posObject.x / 64; j < (posObject.x + width) / 64; j++)
	//		{
	//		//	if (CollisionsMap[i][j] == 'R')//если элемент это "r", то
	//		//	{
	//		//		if (Dy > 0) { y = y - 2; dx = -speed; dy = 0; sprite.rotate(90); }	//Если движется вниз
	//		//		if (Dy < 0) { y = y + 2; dx = speed; dy = 0; sprite.rotate(90); }	//Если движется вверх
	//		//		if (Dx > 0) { x = x - 2; dx = 0; dy = speed; sprite.rotate(90); }	//Если движется вправо
	//		//		if (Dx < 0) { x = x + 2; dx = 0; dy = -speed; sprite.rotate(90); }	//Если двигается влево
	//		//	}
	//		//	if (CollisionsMap[i][j] == 'L')//если элемент это "L", то
	//		//	{
	//		//		if (Dy > 0) { y = y - 2; dx = speed; dy = 0; sprite.rotate(-90); }	//Если движется вниз
	//		//		if (Dy < 0) { y = y + 2; dx = -speed; dy = 0; sprite.rotate(-90); }	//Если движется вверх
	//		//		if (Dx > 0) { x = x - 2; dx = 0; dy = -speed; sprite.rotate(-90); }	//Если движется вправо
	//		//		if (Dx < 0) { x = x + 2; dx = 0; dy = speed; sprite.rotate(-90); }	//Если двигается влево
	//		//	}
	//		//	if (CollisionsMap[i][j] == 'F') { dx = 0; dy = 0; playerHealth--; }	//Если дошли до финиша, то остановились и потеряли жизнь игрока
	//		}
	//}

	
};

////////////////////////////////////////////////////КЛАСС СНАРЯДОВ////////////////////////
class Ammunition :public Entity {
public:
	int direction;//направление снарядов

	Ammunition(Image& image, String Name, Vector2f startPos, int Width, int Height) :Entity(image, Name, startPos, Width, Height) {//всё так же, только взяли в конце состояние игрока (int dir)
		speed = 0.8;
		//width = height = 9; //пока что только один вид снарядов
		life = true;

		if (name == "Bullet") {	//Выводим участок изображения из текстуры: координаты левого верхнего угла х и у, ширина и высота картинки
			sprite.setTextureRect(IntRect(0, 0, width, height));
		}
	}

	void update(float time) {
		move();
		collision();
	}

	void move() {

	}

	void collision() {

	}
};