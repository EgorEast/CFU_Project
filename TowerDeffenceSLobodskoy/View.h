#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
//Объявляю sfml объект "вид", который и является камерой
sf::View view;

//Управление камерой с помощью курсора мыши
void viewMap(RenderWindow& window, float time) {
	{
		//Заношу в вектор координаты мыши относительно окна (х,у)
		sf::Vector2i localPosition = Mouse::getPosition(window);
		//Перевожу координаты курсора относительно окна в игровые (ухожу от коорд окна)
		Vector2f positionMouse = window.mapPixelToCoords(localPosition);

		//По игровым координатам допускаю перемещение камеры по координате x
		if (positionMouse.x > 30 && positionMouse.x < 2530) {
			//Если пришел курсором в левый край экрана, то двигаю камеру влево
			if (localPosition.x < 30) view.move(-200 * time, 0);
			//правый край-вправо
			if (localPosition.x > window.getSize().x - 30) view.move(200 * time, 0);
		}
		//По игровым координатам допускаю перемещение камеры по координате y
		if (positionMouse.y > 30 && positionMouse.y < 1670) {
			//Нижний край - вниз
			if (localPosition.y > window.getSize().y - 30) view.move(0, 200 * time);
			//Верхний край - вверх
			if (localPosition.y < 30) view.move(0, -200 * time);
		}
	}
	
	/////Управление камерой с клавиатуры////
	//Если нажимаю на кнопку D
	if (Keyboard::isKeyPressed(Keyboard::D))
		//Смещаю карту вправо
		view.move(0.2 * time, 0);
	//Если нажимаю на кнопку S
	if (Keyboard::isKeyPressed(Keyboard::S))
		//Смещаю карту вниз 
		view.move(0, 0.2 * time);
	//Если нажимаю на кнопку A
	if (Keyboard::isKeyPressed(Keyboard::A))
		//Смещаю карту влево
		view.move(-0.2 * time, 0);
	//Если нажимаю на кнопку W
	if (Keyboard::isKeyPressed(Keyboard::W))
		//Смещаю карту вправо
		view.move(0, -0.2 * time);
}

//Другие возможности камеры. Пригодится для добавления кнопок
void changeView() {
	//Если нажимаю на кнопку U
	if (Keyboard::isKeyPressed(Keyboard::U)) {
		//Масштабирую, уменьшение
		view.zoom(1.0100f);
		//view.zoom(1.0006f); //тоже самое помедленнее соответственно
	}
	//Если нажимаю на кнопку I
	if (Keyboard::isKeyPressed(Keyboard::I))
		//Устанавливает размер камеры (исходный)
		view.setSize(640, 480);
	//Если нажимаю на кнопку P
	if (Keyboard::isKeyPressed(Keyboard::P))
		//например другой размер
		view.setSize(540, 380);
	//Если нажимаю на кнопку Q
	if (Keyboard::isKeyPressed(Keyboard::Q))
		//таким образом делается раздельный экран для игры на двоих
		//Нужно только создать ещё один объект View и привязывать к нему координаты игрока 2.
		view.setViewport(sf::FloatRect(0, 0, 0.5f, 1));
}