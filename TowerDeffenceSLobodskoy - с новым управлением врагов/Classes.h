#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "map.h"
using namespace sf;
////////////////////////////////////����� �����-��������//////////////////////////
class Entity {
protected:
	Vector2f posObject;	//���������� ����� ��������� � � �
public:
	float dx, dy, speed, moveTimer; //��������� (�� � � �� �), ���� ��������, ������ ��� ��������� ���������� �� ����� �������
	int height, width, health; //������ � ������ �������, health- ����� �������
	bool life, isMove, isSelect; //��������� �����, �������� � ������ �������
	Texture texture; //������� ������ Texture (��������) �������
	Sprite sprite; //������� ������ Sprite(������) �������
	String name; //��� �������

	Entity(Image& image, String Name, Vector2f startPos, int Width, int Height) { //����������� ��� ������ Entity
		posObject.x = startPos.x; posObject.y = startPos.y; width = Width; height = Height; name = Name; moveTimer = 0; //�������������� ����������
		speed = 0; health = 100; dx = 0; dy = 0; //������������� ��������� �� ���������
		life = true; isMove = false; isSelect = false;	//������������� ��������� �� ���������
		texture.loadFromImage(image); //�������� � ������ Texture ������ Image (�����������)
		sprite.setTexture(texture); //������� � ������ Sprite ������ Texture (��������)
		sprite.setOrigin(width / 2, height / 2); //������ ����� ��������������
		sprite.setPosition(posObject.x, posObject.y);//������� ������ � ������� x y 
	}
	FloatRect getRect() { //�-��� ��������� ��������������. ��� �����,������� (���,�����).
		return FloatRect(posObject.x, posObject.y, width, height); //��� �-��� ����� ��� �������� ������������ 
	}
	virtual void update(float time) = 0; //����������� ������� ��� ���������� �������//Ÿ ���������� �������������� � ������ ������
};

////////////////////////////////////////////////////����� �����////////////////////////
class Tower :public Entity { //����������� �� ������ Entity
public:
	int towerLevel;
	bool isShoot; //���������� ��� ����������� ��������� �������� ������ ��� ���
	float dXMouse, dYMouse;

	Tower(Image& image, String Name, Vector2f startPos, int Width, int Height) :Entity(image, Name, startPos, Width, Height) {
		towerLevel = 0;
		if (name == "TowerOne") {	//������� ������� ����������� �� ��������: ���������� ������ �������� ���� � � �, ������ � ������ ��������
			sprite.setTextureRect(IntRect(0, 0, width, height));
		}
		if (name == "TowerTwo") {
			sprite.setTextureRect(IntRect(58, 0, width, height));
		}
		if (name == "TowerThree") {
			sprite.setTextureRect(IntRect(117, 0, width, height));
		}
		if (name == "TowerFour") {
			sprite.setTextureRect(IntRect(175, 0, width, height));
		}
		life = true;
		dXMouse = 0, dYMouse = 0;
	}

	void updateTower(Event& event, Vector2f posMouse, RenderWindow& window, float time) {	//������� "���������" ������� ������
		control(event, posMouse, window);
		shooting(time);
		checkCollisionWithMap(event, posMouse, window);
	}

	void control(Event& event, Vector2f posMouse, RenderWindow& window) {
		if (health <= 0) { life = false; isShoot = false; }	//���� ������ ������ ���� ����� 0, �� ������� � ��������� �������� ����� ����� ������

		if (life) {
			if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
				if (event.key.code == Mouse::Left)//� ������ �����
					if (sprite.getGlobalBounds().contains(posMouse.x, posMouse.y))//� ��� ���� ���������� ������� �������� � ������
					{
						std::cout << "isClicked!\n";//������� � ������� ��������� �� ����
						dXMouse = posMouse.x - sprite.getPosition().x;//������ �������� ����� �������� ������� � �������.��� ������������� �������
						dYMouse = posMouse.y - sprite.getPosition().y;//���� ����� �� ������
						isSelect = true;
						isMove = true;//����� ������� ������		//��� ���������� ����� ����� ��� ������ �����			
					}

			if (event.type == Event::MouseButtonReleased)//���� ��������� �������
				if (event.key.code == Mouse::Left) { //� ������ �����
					isSelect = false;
					isMove = false; //�� �� ����� ������� ������
					sprite.setColor(Color::White);//� ���� ��� ������� ����
				}


			if (isSelect && isMove) {//���� ����� �������
				sprite.setColor(Color::Green);//������ ������ � ������� 
				sprite.setPosition(posMouse.x - dXMouse, posMouse.y - dXMouse);//�������� �������
				checkCollisionWithMap(event, posMouse, window);
			}
		}
	}
	
	void shooting(float time) { //������� ��������� ��� ��������

	}

	void checkCollisionWithMap(Event& event, Vector2f posMouse, RenderWindow& window) {

		
	}

	void update(float time) {}	//�������� ����������� �������, ����� �� ���� ������
};



////////////////////////////////////////////////////����� �������////////////////////////
class Enemy :public Entity {
public:
	int* ptrPlayerHealth;

	Enemy(Image& image, String Name, Vector2f startPos, int Width, int Height, int &playerHealth) :Entity(image, Name, startPos, Width, Height) {
		ptrPlayerHealth = &playerHealth;
		if (name == "Shooter") {
			sprite.setTextureRect(IntRect(0, 0, width, height)); //16*50
			speed = 0.2; //����� ��������
			health = 50;
		}
		if (name == "Tank") {
			sprite.setTextureRect(IntRect(64, 0, width, height)); //30*50
			speed = 0.1;
			health = 200;
		}
		if (name == "Plane") {
			sprite.setTextureRect(IntRect(128, 0, width, height)); //49*50
			speed = 0.3;
			health = 130;
		}
		life = true;
		//dx = speed;	//���� ������� �� ��������� speed
		//dy = 0;	//��������� �������� �� dy ��������
	}

	void update(float time) {	//������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ����� ��������.

		if (life) {
			move(time);

			//switch (dir)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
			//{
			//case 0: dx = speed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� ���� ���� ������ ������
			//case 1: dx = -speed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ����������, ��� ���� ���� ������ �����
			//case 2: dx = 0; dy = speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� ���� ���� ������ ����
			//case 3: dx = 0; dy = -speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� ���� ���� ������ �����
			//case 4: dx = 0; dy = 0; break;//���� ����� �� ������, �� ������������
			//}

			//if (dy == 0) { posObject.x += dx * time; }//��� ��������. ���� ��������� �� ����� �������� �������� ��������� � ��� ��������� ��������
			//if (dx == 0) { posObject.y += dy * time; }//���������� �� ������
			sprite.setPosition(posObject.x + width / 2, posObject.y + height / 2); //������ ������� ������� � ����� ��� ������
			if (health <= 0) { life = false; speed = 0; }//���� ������ ������ ���� ����� 0, �� ������� � ��������� �������� ����� ����� ������
		}
	}

	int curPointInd = 1;

	void move(float time) //�������, �� ������� ����� ��������� ����
	{	
		Vector2f me(posObject.x, posObject.y); //������� �����
		Vector2f goTo(path[curPointInd][0], path[curPointInd][1]);	//����� � ������� ���� �������������//�������� �������� �� Level_1.h
																	//

		Vector2f dir = goTo - me;	//���������� ��� ����������� �����������
		float len = sqrt(dir.x * dir.x + dir.y * dir.y);	//���������� ��� ����������� ���������� �� ����� ��������������

		Vector2f direction = dir / len;	//�������� ��������� ������ �����������

		Vector2f newMe = me + direction * speed * time;	//��������� �����, � ������� �������� ������ � ��������� ������ �������
		posObject.x = newMe.x;	//�������� �� x
		posObject.y = newMe.y;	//�������� �� y
		
		if (len < speed) curPointInd++;	//���� ���������� �� ����� �������������� ������ ��������, �� ������������� �� ��������� �����
		
		if (curPointInd == points) { speed = 0; ptrPlayerHealth--; }	//���� ����� �� ������, �� ������������ � �������� ����� ������

		//if (dy == 0) { checkCollisionWithMap(dx, 0); }//������������ ������������ �� �
		//if (dx == 0) { checkCollisionWithMap(0, dy); }//������������ ������������ �� Y
	}

	//void checkCollisionWithMap(float Dx, float Dy) {//� ��� �������� ������������ � ������
	//	for (int i = posObject.y / 64; i < (posObject.y + height) / 64; i++)//���������� �� ��������� �����
	//		for (int j = posObject.x / 64; j < (posObject.x + width) / 64; j++)
	//		{
	//		//	if (CollisionsMap[i][j] == 'R')//���� ������� ��� "r", ��
	//		//	{
	//		//		if (Dy > 0) { y = y - 2; dx = -speed; dy = 0; sprite.rotate(90); }	//���� �������� ����
	//		//		if (Dy < 0) { y = y + 2; dx = speed; dy = 0; sprite.rotate(90); }	//���� �������� �����
	//		//		if (Dx > 0) { x = x - 2; dx = 0; dy = speed; sprite.rotate(90); }	//���� �������� ������
	//		//		if (Dx < 0) { x = x + 2; dx = 0; dy = -speed; sprite.rotate(90); }	//���� ��������� �����
	//		//	}
	//		//	if (CollisionsMap[i][j] == 'L')//���� ������� ��� "L", ��
	//		//	{
	//		//		if (Dy > 0) { y = y - 2; dx = speed; dy = 0; sprite.rotate(-90); }	//���� �������� ����
	//		//		if (Dy < 0) { y = y + 2; dx = -speed; dy = 0; sprite.rotate(-90); }	//���� �������� �����
	//		//		if (Dx > 0) { x = x - 2; dx = 0; dy = -speed; sprite.rotate(-90); }	//���� �������� ������
	//		//		if (Dx < 0) { x = x + 2; dx = 0; dy = speed; sprite.rotate(-90); }	//���� ��������� �����
	//		//	}
	//		//	if (CollisionsMap[i][j] == 'F') { dx = 0; dy = 0; playerHealth--; }	//���� ����� �� ������, �� ������������ � �������� ����� ������
	//		}
	//}

	
};

////////////////////////////////////////////////////����� ��������////////////////////////
class Ammunition :public Entity {
public:
	int direction;//����������� ��������

	Ammunition(Image& image, String Name, Vector2f startPos, int Width, int Height) :Entity(image, Name, startPos, Width, Height) {//�� ��� ��, ������ ����� � ����� ��������� ������ (int dir)
		speed = 0.8;
		//width = height = 9; //���� ��� ������ ���� ��� ��������
		life = true;

		if (name == "Bullet") {	//������� ������� ����������� �� ��������: ���������� ������ �������� ���� � � �, ������ � ������ ��������
			sprite.setTextureRect(IntRect(0, 0, width, height));
		}
	}

	void update(float time) {
		move();
		collision();
	}

	void move() {

	}

	void collision() {

	}
};