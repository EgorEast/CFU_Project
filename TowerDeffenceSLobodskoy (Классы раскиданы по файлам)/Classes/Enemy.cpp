#include "Enemy.h"


	Enemy::Enemy(Image& image, String Name, Vector2f startPos, int Width, int Height, int& playerHealth, int& points, float path[][2]) :Entity(image, Name, startPos, Width, Height) {
		this->points = &points;
		ptrPlayerHealth = &playerHealth;
		for (int i = 0; i < points; i++)
			for (int j = 0; j < 2; j++) {
				ptrpath[i][j] = path[i][j];
			}
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
	}

	void Enemy::update(float time) {	//функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая врагу движение.

		if (life) {
			move(time);

			sprite.setPosition(posObject.x + width / 2, posObject.y + height / 2); //задаем позицию спрайта в место его центра
			if (health <= 0) { life = false; speed = 0; }//если жизней меньше либо равно 0, то умираем и исключаем движение врага после смерти
		}
	}

	void Enemy::move(float time) //Правила, по которым будет двигаться враг
	{
		Vector2f me(posObject.x, posObject.y); //Позиция врага
		Vector2f goTo(ptrpath[curPointInd][0], ptrpath[curPointInd][1]);	//Точка в которую хочу переместиться//Забирает значения из Level_1.h
																	//

		Vector2f dir = goTo - me;	//Переменная для определения направления
		float len = sqrt(dir.x * dir.x + dir.y * dir.y);	//Переменная для определения расстояния до точки взаимозействия

		Vector2f direction = dir / len;	//Получаем единичный вектор направления

		Vector2f newMe = me + direction * speed * time;	//Следующая точка, в которой появится объект в следующий попент времени
		posObject.x = newMe.x;	//Движение по x
		posObject.y = newMe.y;	//Движение по y

		if (len < speed) curPointInd++;	//Если расстояние до точки взаимодействия меньше скорости, то переключаемся на следующую точку

		if (curPointInd == *points) { speed = 0; ptrPlayerHealth--; }	//Если дошли до финиша, то остановились и потеряли жизнь игрока
	}