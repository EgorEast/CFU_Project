#pragma once
#include <SFML\Graphics.hpp>

	const int HEIGHT_MAP = 25;//размер карты высота
	const int WIDTH_MAP = 40;//размер карты ширина

	//Это точки старта, поворота и конца
	const int points = 6;	//Количество точек взаимодействия
	float path[points][2] = { {0,1 * 64}/*Это старт*/, {5 * 64,1 * 64},{5 * 64,11 * 64},{23 * 64,11 * 64},{23 * 64,18 * 64}, {39 * 64,18 * 64}/*Это база*/ };


	sf::String TileMap[HEIGHT_MAP] = {
		"                                        ",
		"shhhh1                                  ",
		"     v                                  ",
		"     v                                  ",
		"     v                                  ",
		"     v                                  ",
		"     v                                  ",
		"     v                                  ",
		"     v                                  ",
		"     v                                  ",
		"     v                                  ",
		"     3hhhhhhhhhhhhhhhhh1                ",
		"                       v                ",
		"                       v                ",
		"                       v                ",
		"                       v                ",
		"                       v                ",
		"                       v                ",
		"                       3hhhhhhhhhhhhhhhf",
		"                                        ",
		"                                        ",
		"                                        ",
		"                                        ",
		"                                        ",
		"                                        ",
	};

//пробел - трава
//символ s - стартовая клетка
//символ h - горизонтальная дорога
//символ v - вертикальная дорога
//символ 1 - слева вниз
//символ 2 - справа вниз
//символ 3 - сверху вправо
//символ 4 - сверху влево
//символ f - база, финиш





//void drawMap(Sprite& spriteMap, RenderWindow& window) {
//	sf::String mapOne[HEIGHT_MAP] = {
//			"                                        ",
//			"shhhh1                                  ",
//			"     v                                  ",
//			"     v                                  ",
//			"     v                                  ",
//			"     v                                  ",
//			"     v                                  ",
//			"     v                                  ",
//			"     v                                  ",
//			"     v                                  ",
//			"     v                                  ",
//			"     3hhhhhhhhhhhhhhhhh1                ",
//			"                       v                ",
//			"                       v                ",
//			"                       v                ",
//			"                       v                ",
//			"                       v                ",
//			"                       v                ",
//			"                       3hhhhhhhhhhhhhhhf",
//			"                                        ",
//			"                                        ",
//			"                                        ",
//			"                                        ",
//			"                                        ",
//			"                                        ",
//	};
//	Map mapLvlOne(mapOne, points, path);
//	mapLvlOne.drawMap(spriteMap, window);
//}
