#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Enemy.h"

extern nlohmann::json g_jsnFile;

////////////////////////////////////////////////////КЛАСС ВГРАГОВ////////////////////////
//Конструктор класса врага
Enemy::Enemy(sf::Image& image, sf::String Name, sf::Vector2f startPos, int Width, int Height, int& playerHealth)
	:Entity(image, Name, startPos, Width, Height) {
	//Инициализируем указатель на жизни игрока по адресу
	_ptrPlayerHealth = &playerHealth;
	if (name == "Shooter") {
		//width = 16; height = 30
		sprite.setTextureRect(sf::IntRect(0, 0, width, height)); //16*30
		//Задаём скорость
		speed = 200;
		//Задаем количество жизней
		health = 50;
	}
	if (name == "Tank") {
		//width = 50; height = 30
		sprite.setTextureRect(sf::IntRect(18, 0, width, height)); //50*30
		speed = 100;
		health = 200;
	}
	if (name == "Plane") {
		//width = 50; height = 50
		sprite.setTextureRect(sf::IntRect(69, 0, width, height)); //50*50
		speed = 300;
		health = 130;
	}
}

//Функция "оживления" объекта класса
void Enemy::update(float time) {
	if (life) {
		//Вызываю функцию движения
		move(time);

		//Задаем позицию спрайта в место его центра
		sprite.setPosition(posObject.x, posObject.y);
	}
	//Если жизней меньше либо равно 0, то умираем и исключаем движение врага после смерти
	if (health <= 0) { life = false; speed = 0; }
	if (!life) deleteMe = true;
}

//Правила, по которым будет двигаться враг
void Enemy::move(float time) 
{
	//Позиция врага
	sf::Vector2f me(posObject.x, posObject.y);
	//Точка в которую хочу переместиться. Забирает значения из Level_1.h
	sf::Vector2f goTo(g_jsnFile["levelData"]["path"][_curPointInd][0], g_jsnFile["levelData"]["path"][_curPointInd][1]);

	//Переменная для определения направления
	sf::Vector2f dir = goTo - me;
	//Переменная для определения длины вектора
	float lenDir = sqrt(dir.x * dir.x + dir.y * dir.y);

	//Получаем единичный вектор направления
	sf::Vector2f direction = dir / lenDir;

	//Следующая точка, в которой появится объект в следующий попент времени
	sf::Vector2f newMe = me + direction * speed * time;


	//Движение по x
	posObject.x = newMe.x;
	//Движение по y
	posObject.y = newMe.y;

	//Если расстояние до точки взаимодействия меньше скорости, то переключаемся на следующую точку
	if (lenDir < (speed * time))
	{
		_curPointInd++;
	}

	//Условия для поворота объекта
	if (name != "Shooter") {
		//чтобы найти угол нужно вначале найти косинус угла, а затем от него найти арккосинус
		_angle = acos(dir.x / lenDir) / PI * 180;
		//Нужно для определения движения: вниз или вверх
		if (dir.y != 0) _angle *= dir.y / abs(dir.y);
			sprite.setRotation(_angle);
	}
	//Если дошли до финиша, то остановились и потеряли жизнь игрока
	if (_curPointInd == g_jsnFile["levelData"]["points"]) { speed = 0; _ptrPlayerHealth--; life = false; }
}