#include "Projectale.h"

////////////////////////////////////////////////////КЛАСС СНАРЯДОВ////////////////////////
	Projectale::Projectale(Image& image, String Name, Vector2f startPos, int Width, int Height) :Entity(image, Name, startPos, Width, Height) {//всё так же, только взяли в конце состояние игрока (int dir)
		speed = 0.8;
		//width = height = 9; //пока что только один вид снарядов
		life = true;

		if (name == "Bullet") {	//Выводим участок изображения из текстуры: координаты левого верхнего угла х и у, ширина и высота картинки
			sprite.setTextureRect(IntRect(0, 0, width, height));
		}
	}

	void Projectale::update(float time) {
		move();
		collision();
	}

	void Projectale::move() {

	}

	void Projectale::collision() {

	}