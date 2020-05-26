#pragma once
#include <SFML\Graphics.hpp>


using namespace sf;
class Map
{
public:
	sf::String* TileMap;
	const int HEIGHT_MAP = 25;//������ ����� ������
	const int WIDTH_MAP = 40;//������ ����� ������
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
		/////////////////////////////������ �����/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ') spriteMap.setTextureRect(IntRect(0, 0, 64, 64));		//���� ��������� ������ ������, �� ������ 1� ���������
				if (TileMap[i][j] == 's') spriteMap.setTextureRect(IntRect(64, 0, 64, 64));		//���� ��������� ������ s, �� ������ 2� ���������
				if (TileMap[i][j] == 'h') spriteMap.setTextureRect(IntRect(128, 0, 64, 64));	//���� ��������� ������ h, �� ������ 3� ���������
				if (TileMap[i][j] == 'v') spriteMap.setTextureRect(IntRect(192, 0, 64, 64));	//���� ��������� ������ v, �� ������ 4� ���������
				if (TileMap[i][j] == '1') spriteMap.setTextureRect(IntRect(256, 0, 64, 64));	//���� ��������� ������ 1, �� ������ 5� ��������� - ����� ����
				if (TileMap[i][j] == '2') spriteMap.setTextureRect(IntRect(320, 0, 64, 64));	//���� ��������� ������ 2, �� ������ 6� ��������� - ������ ����
				if (TileMap[i][j] == '3') spriteMap.setTextureRect(IntRect(384, 0, 64, 64));	//���� ��������� ������ 3, �� ������ 7� ��������� - ������ ������
				if (TileMap[i][j] == '4') spriteMap.setTextureRect(IntRect(448, 0, 64, 64));	//���� ��������� ������ 4, �� ������ 8� ��������� - ������ �����
				if (TileMap[i][j] == 'f') spriteMap.setTextureRect(IntRect(512, 0, 64, 64));	//���� ��������� ������ f, �� ������ 9� ���������

				spriteMap.setPosition(j * 64, i * 64);	//����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� �������

				window.draw(spriteMap);	//������ ���������� �� �����
			}
	}
	//������ - �����
	//������ s - ��������� ������
	//������ h - �������������� ������
	//������ v - ������������ ������
	//������ 1 - ����� ����
	//������ 2 - ������ ����
	//������ 3 - ������ ������
	//������ 4 - ������ �����
	//������ f - ����, �����

};
