#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"
#include "Projectale.h"

////////////////////////////////////////////////////КЛАСС БАШЕН////////////////////////
//Наследуется от класса Entity
class Tower :public Entity {
public:

	//Конструктор класса
	Tower(String Name, Vector2f startPos, int Width, int Height, int& moneyBalance);
	//функция "оживления" объекта класса
	void update(float time) override;
	//Обработка событий мыши
	virtual void onMouseEvent(Event& event, Vector2f posMouse, RenderWindow& window);
	//Управление башней
	void control(Event& event, Vector2f posMouse, RenderWindow& window);
	//Функция поведения для стрельбы
	void shooting(/*float Rot, Vector2f Vel*/);
	//Проверка столкновения с объектами карты
	void checkCollisionWithMap(Event& event, Vector2f posMouse, RenderWindow& window);
	//Узнать, могу ли купить башню
	bool getIsBought();

	int getTowerPrice();
private:
	//Уровень башни
	int _towerLevel;
	//Переменная для определения состояния стреляет объект или нет
	bool _isShoot;
	//Корректировка нажатия мышью по х и по y
	float _dXMouse, _dYMouse;
	//Цена башни
	int _towerPrice;
	//Куплено или нет
	bool _bought;
};