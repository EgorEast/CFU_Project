#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
sf::View view;//объявили sfml объект "вид", который и является камерой


void viewMap(RenderWindow& window, float time) {
	{//Управление камерой с помощью курсора мыши
		sf::Vector2i localPosition = Mouse::getPosition(window);//заносим в вектор координаты мыши относительно окна (х,у)
		Vector2f positionMouse = window.mapPixelToCoords(localPosition);//переводим координаты курсора относительно окна в игровые (уходим от коорд окна)

		if (positionMouse.x > 30 && positionMouse.x < 2530) {//по игровым координатам допускаю перемещение камеры по координате x
			if (localPosition.x < 30) { view.move(-0.2 * time, 0); }//если пришли курсором в левый край экрана,то двигаем камеру влево
			if (localPosition.x > window.getSize().x - 30) { view.move(0.2 * time, 0); }//правый край-вправо
		}
		if (positionMouse.y > 30 && positionMouse.y < 1670) {//по игровым координатам допускаю перемещение камеры по координате y
			if (localPosition.y > window.getSize().y - 30) { view.move(0, 0.2 * time); }//нижний край - вниз
			if (localPosition.y < 30) { view.move(0, -0.2 * time); }//верхний край - вверх
		}
	}
	
	{//Управление камерой с клавиатуры
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			view.move(0.2 * time, 0);//скроллим карту вправо
		}

		if (Keyboard::isKeyPressed(Keyboard::S)) {
			view.move(0, 0.2 * time);//скроллим карту вниз 
		}

		if (Keyboard::isKeyPressed(Keyboard::A)) {
			view.move(-0.2 * time, 0);//скроллим карту влево
		}
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			view.move(0, -0.2 * time);//скроллим карту вправо
		}
	}
}

void changeView() { //Пригодится для добавления кнопок

	if (Keyboard::isKeyPressed(Keyboard::U)) {
		view.zoom(1.0100f); //масштабируем, уменьшение
		//view.zoom(1.0006f); //тоже самое помедленнее соответственно
	}

	if (Keyboard::isKeyPressed(Keyboard::R)) {
		//view.setRotation(90);//сразу же задает поворот камере
		view.rotate(1);//постепенно поворачивает камеру (отрицательное значение - в обратную сторону)
	}


	if (Keyboard::isKeyPressed(Keyboard::I)) {
		view.setSize(640, 480);//устанавливает размер камеры (наш исходный)
	}

	if (Keyboard::isKeyPressed(Keyboard::P)) {
		view.setSize(540, 380);//например другой размер
	}


	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		view.setViewport(sf::FloatRect(0, 0, 0.5f, 1));//таким образом делается раздельный экран для игры на двоих. нужно только создать ещё один объект View и привязывать к нему координаты игрока 2.
	}
}