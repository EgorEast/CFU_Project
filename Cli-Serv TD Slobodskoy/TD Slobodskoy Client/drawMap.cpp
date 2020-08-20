#pragma once
#include "drawMap.h"

//��������� �����
void drawMap(sf::Sprite& spriteMap, sf::RenderWindow& window, std::string TileMap[], const int HEIGHT_MAP, const int WIDTH_MAP) {

	/////////////////////////////������ �����/////////////////////
	for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			//���� �������� ������ ������, �� ����� 1� ��������� - �����
			if (TileMap[i][j] == ' ') spriteMap.setTextureRect(sf::IntRect(0, 0, 64, 64));
			//���� �������� ������ s, �� ����� 2� ��������� - ��������� ������
			if (TileMap[i][j] == 's') spriteMap.setTextureRect(sf::IntRect(64, 0, 64, 64));
			//���� �������� ������ h, �� ����� 3� ��������� - �������������� ������
			if (TileMap[i][j] == 'h') spriteMap.setTextureRect(sf::IntRect(128, 0, 64, 64));
			//���� �������� ������ v, �� ����� 4� ��������� - ������������ ������
			if (TileMap[i][j] == 'v') spriteMap.setTextureRect(sf::IntRect(192, 0, 64, 64));
			//���� �������� ������ 1, �� ����� 5� ��������� - ����� ����
			if (TileMap[i][j] == '1') spriteMap.setTextureRect(sf::IntRect(256, 0, 64, 64));
			//���� �������� ������ 2, �� ����� 6� ��������� - ������ ����
			if (TileMap[i][j] == '2') spriteMap.setTextureRect(sf::IntRect(320, 0, 64, 64));
			//���� �������� ������ 3, �� ����� 7� ��������� - ������ ������
			if (TileMap[i][j] == '3') spriteMap.setTextureRect(sf::IntRect(384, 0, 64, 64));
			//���� �������� ������ 4, �� ����� 8� ��������� - ������ �����
			if (TileMap[i][j] == '4') spriteMap.setTextureRect(sf::IntRect(448, 0, 64, 64));
			//���� �������� ������ f, �� ����� 9� ��������� - ����, �����
			if (TileMap[i][j] == 'f') spriteMap.setTextureRect(sf::IntRect(512, 0, 64, 64));

			//����� ������� �� ����������� �������
			//���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � � ����� ���� �������
			spriteMap.setPosition(j * 64, i * 64);

			//����� ���������� �� �����
			window.draw(spriteMap);
		}
}

