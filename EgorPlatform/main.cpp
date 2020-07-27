#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "view.h"
#include <iostream>
//#include <sstream>//������ �� �����. ������ �������� ����� ( � 13 �� ����� )
#include "mission.h"
#include "iostream"
#include "level.h"
#include <vector>
#include <list>
#include "LifeBar.h"
#include "Game.h"


using namespace sf;
////////////////////////////////////����� �����-��������//////////////////////////
class Entity {
public:
	std::vector<Object> obj;//������ �������� �����
	float dx, dy, x, y, speed,moveTimer;
	int w,h,health;
	bool life, isMove, onGround;
	Texture texture;
	Sprite sprite;
	String name;
	Entity(Image &image, String Name, float X, float Y, int W, int H){
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true; onGround = false; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}

	FloatRect getRect(){//�-��� ��������� ��������������. ��� �����,������� (���,�����).
		return FloatRect(x, y, w, h);//��� �-��� ����� ��� �������� ������������ 
	}

	virtual void update(float time) = 0;
};
////////////////////////////////////////////////////����� ������////////////////////////
class Player :public Entity {
public:
	enum { left, right, up, down, jump, stay, right_Top } state;
	int playerScore;
	bool isShoot;

	Player(Image &image, String Name, Level &lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H ){
		   playerScore = 0; state = stay; obj = lev.GetAllObjects();//��������������.�������� ��� ������� ��� �������������� ��������� � ������
		   if (name == "Player1"){
			   sprite.setTextureRect(IntRect(4, 19, w, h));
		   }
	   }

	   void control(){
		   if (Keyboard::isKeyPressed){
			   if (Keyboard::isKeyPressed(Keyboard::Left)) {
				   state = left; speed = 0.1;
			   }
			   if (Keyboard::isKeyPressed(Keyboard::Right)) {
				   state = right; speed = 0.1;
			   }

			   if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) {
				   state = jump; dy = -0.6; onGround = false;
			   }

			   if (Keyboard::isKeyPressed(Keyboard::Down)) {
				   state = down;
			   }

			   if ((Keyboard::isKeyPressed(Keyboard::Right)) && (Keyboard::isKeyPressed(Keyboard::Up))) {
				   state = right_Top;
			   }

			   ///�������
			   if (Keyboard::isKeyPressed(Keyboard::Space)) {
				   isShoot = true;
			   }
		   }
	   } 

	   

	   void checkCollisionWithMap(float Dx, float Dy)
	   {
		   for (int i = 0; i<obj.size(); i++)//���������� �� ��������
		   if (getRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
		   {
			   if (obj[i].name == "solid")//���� ��������� �����������
			   {
				   if (Dy>0)	{ y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				   if (Dy<0)	{ y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				   if (Dx>0)	{ x = obj[i].rect.left - w; }
				   if (Dx<0)	{ x = obj[i].rect.left + obj[i].rect.width; }
			   }
		   }
	   }
	    
	   void update(float time)
	   {
		   control();
		   switch (state)
		   {
		   case right:dx = speed; break;
		   case left:dx = -speed; break;
		   case up: break;
		   case down: dx = 0; break;
		   case stay: break;
		   case right_Top:dx = speed; break;//��������� ������ �����, ������ ���������� ���� ������
		   }
		   x += dx*time;
		   checkCollisionWithMap(dx, 0);
		   y += dy*time;
		   checkCollisionWithMap(0, dy);
		   sprite.setPosition(x + w / 2, y + h / 2);
		   if (health <= 0){ life = false; }
		   if (!isMove){ speed = 0; }
		   setPlayerCoordinateForView(x, y);
		   if (life) { setPlayerCoordinateForView(x, y); }
		   dy = dy + 0.0015*time;
	   } 
};



class Enemy :public Entity{
public:
	Enemy(Image &image, String Name,Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H){
		obj = lvl.GetObjects("solid");//��������������.�������� ������ ������� ��� �������������� ����� � ������
		if (name == "EasyEnemy"){
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dx = 0.1;
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = 0; i<obj.size(); i++)//���������� �� ��������
		if (getRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
		{
			//if (obj[i].name == "solid"){//���� ��������� ����������� (������ � ������ solid)
				if (Dy>0)	{ y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy<0)	{ y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx>0)	{ x = obj[i].rect.left - w;  dx = -0.1; sprite.scale(-1, 1); }
				if (Dx<0)	{ x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1, 1); }
			//}
		}
	}

	void update(float time)
	{
		if (name == "EasyEnemy"){
			//moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }//������ ����������� �������� ������ 3 ���
			checkCollisionWithMap(dx, 0);
			x += dx*time;
			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0){ life = false; }
		}

		if (health <= 0) { life = false; }
	}
};

class MovingPlatform : public Entity {//����� ���������� ���������
public:
	MovingPlatform(Image& image, String Name, Level& lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
		sprite.setTextureRect(IntRect(0, 0, W, H));//������������� 
		dx = 0.08;//����������� ��������� �� �
	}

	void update(float time)//������� ���������� ���������.
	{
		x += dx * time;//���������� �������� �� �����������
		moveTimer += time;//���������� ������
		if (moveTimer > 2000) { dx *= -1; moveTimer = 0; }//���� ������ �������� 2 ���, �� �������� ����������� �������� ���������,� ������ ����������
		sprite.setPosition(x + w / 2, y + h / 2);//������ ������� �������
	}
};

class Bullet :public Entity {//����� ����
public:
	int direction;//����������� ����

	Bullet(Image& image, String Name, Level& lvl, float X, float Y, int W, int H, int dir) :Entity(image, Name, X, Y, W, H) {//�� ��� ��, ������ ����� � ����� ��������� ������ (int dir)
		obj = lvl.GetObjects("solid");//�������������� .�������� ������ ������� ��� �������������� ���� � ������
		x = X;
		y = Y;
		direction = dir;
		speed = 0.8;
		w = h = 16;
		life = true;
		//���� ������������� � ������������
	}


	void update(float time)
	{
		switch (direction)
		{
		case 0: dx = -speed; dy = 0;   break;//������� �������� state = left
		case 1: dx = speed; dy = 0;   break;//������� �������� state = right
		case 2: dx = 0; dy = -speed;   break;//������� �������� state = up
		case 3: dx = 0; dy = -speed;   break;//������� �������� �� ������� ��������� � �����������, ���� ������ ��������� �����, ��� ������ ��� �� �����
		case 4: dx = 0; dy = -speed;   break;//������� �������� �� ������� ��������� � �����������, ���� ������ ��������� �����, ��� ������ ��� �� �����
		case 5: dx = 0; dy = -speed;   break;//������� �������� �� ������� ��������� � �����������, ���� ������ ��������� �����, ��� ������ ��� �� �����
		case 6: dx = speed; dy = -speed;   break;//������� �������� state = right_Top
		}

		x += dx * time;//���� �������� ���� �� �
		y += dy * time;//�� �

		if (x <= 0) x = 1;// �������� ���� � ����� �����, ����� ��� ���������� ������ ��� �������� �� �������� �� ������ ����� � �� ���� ������
		if (y <= 0) y = 1;

		for (int i = 0; i < obj.size(); i++) {//������ �� �������� solid
			if (getRect().intersects(obj[i].rect)) //���� ���� ������ ���������� � �����,
			{
				life = false;// �� ���� �������
			}
		}

		sprite.setPosition(x + w / 2, y + h / 2);//�������� ������� ����
	}
};

void changeLevel(Level& lvl, int& numberLevel) {
	switch (numberLevel)
	{
	case 1: lvl.LoadFromFile("map.tmx"); break;//��������� � ���� ����� 1, ������ ������ � ������� ������� �� �� ����������.
	case 2: lvl.LoadFromFile("map2.tmx"); break;
	case 3: lvl.LoadFromFile("map3.tmx"); break;
	default: numberLevel = 1; lvl.LoadFromFile("map.tmx"); break;
	}
}

bool startGame(RenderWindow& window, int &numberLevel) {

	view.reset(FloatRect(0, 0, 640, 480));

	Level lvl;//������� ��������� ������ �������
	changeLevel(lvl, numberLevel);//��� �������� ����� ��� ������� ������

	SoundBuffer shootBuffer;//������ ����� ��� �����
	shootBuffer.loadFromFile("shoot.ogg");//��������� � ���� ����
	Sound shoot(shootBuffer);//������� ���� � ��������� � ���� ���� �� ������

	Music music;//������� ������ ������
	music.openFromFile("music.ogg");//��������� ����
	music.play();//������������� ������
	music.setLoop(true);

	Image heroImage;
	heroImage.loadFromFile("images/MilesTailsPrower.gif");

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/shamaich.png");
	easyEnemyImage.createMaskFromColor(Color(255, 0, 0));

	Image movePlatformImage;
	movePlatformImage.loadFromFile("images/MovingPlatform.png");

	Image BulletImage;//����������� ��� ����
	BulletImage.loadFromFile("images/bullet.png");//��������� �������� � ������ �����������
	BulletImage.createMaskFromColor(Color(0, 0, 0));//����� ��� ���� �� ������� �����

	std::list<Entity*>  entities;
	std::list<Entity*>::iterator it;
	std::list<Entity*>::iterator it2;//������ ��������.��� �������������� ����� ��������� ������


	std::vector<Object> e = lvl.GetObjects("EasyEnemy");

	for (int i = 0; i < e.size(); i++) entities.push_back(new Enemy(easyEnemyImage, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 200, 97));

	Object player = lvl.GetObject("player");

	Player p(heroImage, "Player1", lvl, player.rect.left, player.rect.top, 40, 30);

	e = lvl.GetObjects("MovingPlatform");//�������� ��� ��������� � ������ 

	for (int i = 0; i < e.size(); i++) entities.push_back(new MovingPlatform(movePlatformImage, "MovingPlatform", lvl, e[i].rect.left, e[i].rect.top, 95, 22));//���������� ��������� � ������.�������� ����������� ��� ������� ���������� ��������� (����� �� tmx �����), � ��� �� �������

	Clock clock;

	LifeBar lifeBarPlayer;//��������� ������ ������� ��������

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (p.isShoot == true) {
				p.isShoot = false; entities.push_back(new Bullet(BulletImage, "Bullet", lvl, p.x, p.y, 16, 16, p.state));
				shoot.play();
			}//������ ���� ���� //���� ����������, �� ���������� ����. enum �������� ��� int 
		}

		lifeBarPlayer.update(70);//���� �������� ��������, ������� ���� ����������. ����� �������� �������� ������ ����� ����� lifeBarPlayer.update(player.getHealth())

		for (it = entities.begin(); it != entities.end();)//������� ��� ���������� �� ������ �� �����
		{
			Entity* b = *it;//��� ��������, ����� �� ������ (*it)->
			b->update(time);//�������� �-��� update ��� ���� �������� (�� ���� ��� ���, ��� ���)
			if (b->life == false) { it = entities.erase(it); delete b; }// ���� ���� ������ �����, �� ������� ���
			else it++;//� ���� �������� (����������) � ���� �������. ��� ������ �� ����� ��������� ������
		}

		for (it = entities.begin(); it != entities.end(); it++)//���������� �� ��-��� ������
		{
			if (((*it)->name == "MovingPlatform") && ((*it)->getRect().intersects(p.getRect())))//���� ����� ���������� � �������� ������ � ��� ����� ������� movingplatform
			{
				Entity* movPlat = *it;
				if ((p.dy > 0) || (p.onGround == false))//��� ���� ����� ��������� � ��������� ����� ������, �.� ������ ����
					if (p.y + p.h < movPlat->y + movPlat->h)//���� ����� ��������� ���� ���������, �.� ��� ��� ���� ������� (�� �� ��� ��������� ��� �� ���������� � ����������)
					{
						p.y = movPlat->y - p.h + 3; p.x += movPlat->dx * time; p.dy = 0; p.onGround = true; // �� ����������� ������ ���, ����� �� ��� �� ����� �� ���������
					}
			}

			if ((*it)->getRect().intersects(p.getRect()))
			{
				if ((*it)->name == "EasyEnemy") {//� ��� ���� ��� ������� EasyEnemy,��..

					////////������������ �����
					if ((*it)->dx > 0)//���� ���� ���� ������
					{
						std::cout << "(*it)->x" << (*it)->x << "\n";//����� ������
						std::cout << "p.x" << p.x << "\n\n";//����� �����

						(*it)->x = p.x - (*it)->w; //����������� ��� �� ������ ����� (�������)
						(*it)->dx = 0;//�������������

						std::cout << "new (*it)->x" << (*it)->x << "\n";//����� ����� �����
						std::cout << "new p.x" << p.x << "\n\n";//����� ����� ������ (��������� �������)
					}
					if ((*it)->dx < 0)//���� ���� ���� �����
					{
						(*it)->x = p.x + p.w; //���������� - ����������� ������
						(*it)->dx = 0;//�������������
					}
					///////������������ ������
					if (p.dx < 0) { p.x = (*it)->x + (*it)->w; }//���� ����������� � ������ � ����� ���� ����� �� ����������� ������
					if (p.dx > 0) { p.x = (*it)->x - p.w; }//���� ����������� � ������ � ����� ���� ������ �� ����������� ������
				}
			}

			for (it2 = entities.begin(); it2 != entities.end(); it2++)
			{
				if ((*it)->getRect() != (*it2)->getRect())//��� ���� ��� ������ ���� ������ ��������������
					if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "EasyEnemy"))//���� ����������� ��� ������� � ��� �����
					{
						(*it)->dx *= -1;//������ ����������� �������� �����
						(*it)->sprite.scale(-1, 1);//�������� ������ �� �����������
					}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::T)) { lvl.levelNumber++; return true; }
		if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }//���� ���, �� ������������� ����
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }//���� ������, �� ������� �� ����		if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }//���� ������, �� ������� �� ����

		p.update(time);
		window.setView(view);
		window.clear(Color(77, 83, 140));
		lvl.Draw(window);

		lifeBarPlayer.draw(window);//������ ������� ��������

		for (it = entities.begin(); it != entities.end(); it++) {
			window.draw((*it)->sprite);
		}
		window.draw(p.sprite);
		window.display();
	}
}

void gameRunning(RenderWindow& window, int& numberLevel) {//�-��� ������������� ���� , ���� ��� ����������
	if (startGame(window, numberLevel)) { numberLevel++; gameRunning(window, numberLevel); }////���� startGame() == true, �� �������� ������ �-��� isGameRunning, ������� � ���� ������� ����� �������� startGame() 
}

int main()
{
	RenderWindow window(VideoMode(1920, 1080), "Egor's Game", sf::Style::Fullscreen);
	
	menu(window);//����� ����

	int numberLevel = 1;//������� 1-�� �������
	gameRunning(window, numberLevel);
	return 0;
}