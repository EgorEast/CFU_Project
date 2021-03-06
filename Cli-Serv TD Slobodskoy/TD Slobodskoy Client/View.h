#pragma once
#include <SFML/Graphics.hpp>

//�������� sfml ������ "���", ������� � �������� �������
sf::View view;

//���������� ������� � ������� ������� ����
void viewMap(sf::RenderWindow& window, float time) {
	{
		//������ � ������ ���������� ���� ������������ ���� (�,�)
		sf::Vector2i localPosition = sf::Mouse::getPosition(window);
		//�������� ���������� ������� ������������ ���� � ������� (����� �� ����� ����)
		sf::Vector2f positionMouse = window.mapPixelToCoords(localPosition);

		//�� ������� ����������� �������� ����������� ������ �� ���������� x
		if (positionMouse.x > 30 && positionMouse.x < 2530) {
			//���� ������ �������� � ����� ���� ������, �� ������ ������ �����
			if (localPosition.x < 30) view.move(-200 * time, 0);
			//������ ����-������
			if (localPosition.x > window.getSize().x - 30) view.move(200 * time, 0);
		}
		//�� ������� ����������� �������� ����������� ������ �� ���������� y
		if (positionMouse.y > 30 && positionMouse.y < 1670) {
			//������ ���� - ����
			if (localPosition.y > window.getSize().y - 30) view.move(0, 200 * time);
			//������� ���� - �����
			if (localPosition.y < 30) view.move(0, -200 * time);
		}
	}
	
	/////���������� ������� � ����������////
	//���� ������� �� ������ D
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		//������ ����� ������
		view.move(0.2 * time, 0);
	//���� ������� �� ������ S
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		//������ ����� ���� 
		view.move(0, 0.2 * time);
	//���� ������� �� ������ A
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		//������ ����� �����
		view.move(-0.2 * time, 0);
	//���� ������� �� ������ W
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		//������ ����� ������
		view.move(0, -0.2 * time);
}

//������ ����������� ������. ���������� ��� ���������� ������
void changeView() {
	//���� ������� �� ������ U
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
		//�����������, ����������
		view.zoom(1.0100f);
		//view.zoom(1.0006f); //���� ����� ����������� ��������������
	}
	//���� ������� �� ������ I
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		//������������� ������ ������ (��������)
		view.setSize(640, 480);
	//���� ������� �� ������ P
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		//�������� ������ ������
		view.setSize(540, 380);
	//���� ������� �� ������ Q
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		//����� ������� �������� ���������� ����� ��� ���� �� �����
		//����� ������ ������� ��� ���� ������ View � ����������� � ���� ���������� ������ 2.
		view.setViewport(sf::FloatRect(0, 0, 0.5f, 1));
}