#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
sf::View view;//�������� sfml ������ "���", ������� � �������� �������


void viewMap(RenderWindow& window, float time) {
	{//���������� ������� � ������� ������� ����
		sf::Vector2i localPosition = Mouse::getPosition(window);//������� � ������ ���������� ���� ������������ ���� (�,�)
		Vector2f positionMouse = window.mapPixelToCoords(localPosition);//��������� ���������� ������� ������������ ���� � ������� (������ �� ����� ����)

		if (positionMouse.x > 30 && positionMouse.x < 2530) {//�� ������� ����������� �������� ����������� ������ �� ���������� x
			if (localPosition.x < 30) { view.move(-0.2 * time, 0); }//���� ������ �������� � ����� ���� ������,�� ������� ������ �����
			if (localPosition.x > window.getSize().x - 30) { view.move(0.2 * time, 0); }//������ ����-������
		}
		if (positionMouse.y > 30 && positionMouse.y < 1670) {//�� ������� ����������� �������� ����������� ������ �� ���������� y
			if (localPosition.y > window.getSize().y - 30) { view.move(0, 0.2 * time); }//������ ���� - ����
			if (localPosition.y < 30) { view.move(0, -0.2 * time); }//������� ���� - �����
		}
	}
	
	{//���������� ������� � ����������
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			view.move(0.2 * time, 0);//�������� ����� ������
		}

		if (Keyboard::isKeyPressed(Keyboard::S)) {
			view.move(0, 0.2 * time);//�������� ����� ���� 
		}

		if (Keyboard::isKeyPressed(Keyboard::A)) {
			view.move(-0.2 * time, 0);//�������� ����� �����
		}
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			view.move(0, -0.2 * time);//�������� ����� ������
		}
	}
}

void changeView() { //���������� ��� ���������� ������

	if (Keyboard::isKeyPressed(Keyboard::U)) {
		view.zoom(1.0100f); //������������, ����������
		//view.zoom(1.0006f); //���� ����� ����������� ��������������
	}

	if (Keyboard::isKeyPressed(Keyboard::R)) {
		//view.setRotation(90);//����� �� ������ ������� ������
		view.rotate(1);//���������� ������������ ������ (������������� �������� - � �������� �������)
	}


	if (Keyboard::isKeyPressed(Keyboard::I)) {
		view.setSize(640, 480);//������������� ������ ������ (��� ��������)
	}

	if (Keyboard::isKeyPressed(Keyboard::P)) {
		view.setSize(540, 380);//�������� ������ ������
	}


	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		view.setViewport(sf::FloatRect(0, 0, 0.5f, 1));//����� ������� �������� ���������� ����� ��� ���� �� �����. ����� ������ ������� ��� ���� ������ View � ����������� � ���� ���������� ������ 2.
	}
}