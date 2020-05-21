#pragma once
#include <SFML\Graphics.hpp>

	const int HEIGHT_MAP = 25;//������ ����� ������
	const int WIDTH_MAP = 40;//������ ����� ������

	//��� ����� ������, �������� � �����
	const int points = 6;	//���������� ����� ��������������
	float path[points][2] = { {0,1 * 64}/*��� �����*/, {5 * 64,1 * 64},{5 * 64,11 * 64},{23 * 64,11 * 64},{23 * 64,18 * 64}, {39 * 64,18 * 64}/*��� ����*/ };


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

//������ - �����
//������ s - ��������� ������
//������ h - �������������� ������
//������ v - ������������ ������
//������ 1 - ����� ����
//������ 2 - ������ ����
//������ 3 - ������ ������
//������ 4 - ������ �����
//������ f - ����, �����





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
