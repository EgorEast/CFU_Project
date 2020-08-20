#pragma once
#include "drawMap.h"

//Отрисовка карты
void drawMap(sf::Sprite& spriteMap, sf::RenderWindow& window, std::string TileMap[], const int HEIGHT_MAP, const int WIDTH_MAP) {

	/////////////////////////////Рисуем карту/////////////////////
	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			//Если встретил символ пробел, то рисую 1й квадратик - трава
			if (TileMap[i][j] == ' ') spriteMap.setTextureRect(sf::IntRect(0, 0, 64, 64));
			//Если встретил символ s, то рисую 2й квадратик - стартовая клетка
			if (TileMap[i][j] == 's') spriteMap.setTextureRect(sf::IntRect(64, 0, 64, 64));
			//Если встретил символ h, то рисую 3й квадратик - горизонтальная дорога
			if (TileMap[i][j] == 'h') spriteMap.setTextureRect(sf::IntRect(128, 0, 64, 64));
			//Если встретил символ v, то рисую 4й квадратик - вертикальная дорога
			if (TileMap[i][j] == 'v') spriteMap.setTextureRect(sf::IntRect(192, 0, 64, 64));
			//Если встретил символ 1, то рисую 5й квадратик - слева вниз
			if (TileMap[i][j] == '1') spriteMap.setTextureRect(sf::IntRect(256, 0, 64, 64));
			//Если встретил символ 2, то рисую 6й квадратик - справа вниз
			if (TileMap[i][j] == '2') spriteMap.setTextureRect(sf::IntRect(320, 0, 64, 64));
			//Если встретил символ 3, то рисую 7й квадратик - сверху вправо
			if (TileMap[i][j] == '3') spriteMap.setTextureRect(sf::IntRect(384, 0, 64, 64));
			//Если встретил символ 4, то рисую 8й квадратик - сверху влево
			if (TileMap[i][j] == '4') spriteMap.setTextureRect(sf::IntRect(448, 0, 64, 64));
			//Если встретил символ f, то рисую 9й квадратик - база, финиш
			if (TileMap[i][j] == 'f') spriteMap.setTextureRect(sf::IntRect(512, 0, 64, 64));

			//Задаю каждому из квадратиков позицию
			//Если убрать, то вся карта нарисуется в одном квадрате 32*32 и я увижу один квадрат
			spriteMap.setPosition(j * 64, i * 64);

			//Рисую квадратики на экран
			window.draw(spriteMap);
		}
}

