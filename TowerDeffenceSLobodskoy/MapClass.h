#pragma once
#include <SFML\Graphics.hpp>


using namespace sf;
class Map
{
public:
	sf::String* TileMap;
	const int HEIGHT_MAP = 25;//размер карты высота
	const int WIDTH_MAP = 40;//размер карты ширина
	int points;
	float** path;
	float start, base;
	Map(String map[], const int points, float path[]) {
		this->points = points;
		this->path = new float* [points];
		for (int i = 0; i <= WIDTH_MAP; i++)
		{
			TileMap[i] = map[i];
		}
	}

	void pathMap() {
		for (int x = 0; x < points; x++) 
			for (int y = 0; y <= 1; y++) {
				//this->path[x][y] = Path[x][y];
			}
	}

	void drawMap(Sprite& spriteMap, RenderWindow& window) {
		/////////////////////////////Рисуем карту/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ') spriteMap.setTextureRect(IntRect(0, 0, 64, 64));		//если встретили символ пробел, то рисуем 1й квадратик
				if (TileMap[i][j] == 's') spriteMap.setTextureRect(IntRect(64, 0, 64, 64));		//если встретили символ s, то рисуем 2й квадратик
				if (TileMap[i][j] == 'h') spriteMap.setTextureRect(IntRect(128, 0, 64, 64));	//если встретили символ h, то рисуем 3й квадратик
				if (TileMap[i][j] == 'v') spriteMap.setTextureRect(IntRect(192, 0, 64, 64));	//если встретили символ v, то рисуем 4й квадратик
				if (TileMap[i][j] == '1') spriteMap.setTextureRect(IntRect(256, 0, 64, 64));	//если встретили символ 1, то рисуем 5й квадратик - слева вниз
				if (TileMap[i][j] == '2') spriteMap.setTextureRect(IntRect(320, 0, 64, 64));	//если встретили символ 2, то рисуем 6й квадратик - справа вниз
				if (TileMap[i][j] == '3') spriteMap.setTextureRect(IntRect(384, 0, 64, 64));	//если встретили символ 3, то рисуем 7й квадратик - сверху вправо
				if (TileMap[i][j] == '4') spriteMap.setTextureRect(IntRect(448, 0, 64, 64));	//если встретили символ 4, то рисуем 8й квадратик - сверху влево
				if (TileMap[i][j] == 'f') spriteMap.setTextureRect(IntRect(512, 0, 64, 64));	//если встретили символ f, то рисуем 9й квадратик

				spriteMap.setPosition(j * 64, i * 64);	//раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

				window.draw(spriteMap);	//рисуем квадратики на экран
			}
	}
	//пробел - трава
	//символ s - стартовая клетка
	//символ h - горизонтальная дорога
	//символ v - вертикальная дорога
	//символ 1 - слева вниз
	//символ 2 - справа вниз
	//символ 3 - сверху вправо
	//символ 4 - сверху влево
	//символ f - база, финиш

};
