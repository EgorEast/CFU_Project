#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>//выводим текст
#include <vector>//Подключаю вектор
#include <list>//Подключаю списки

//ПОдключаю свой код
#include "Classes.h"// Подключаем классы
//#include "levels.h"	//подключили уровни
#include "View.h"	//подключили код с видом камеры
#include "map.h"	// Подключаем код для отрисовки карты

//#include "mission.h"//подключили код миссий
//#include "LifeBar.h"//подключили код строки здоровья
//#include "Game.h"//подключили код запуска меню игры

#pragma warning(disable : 4996) //Чтобы отключить предупреждение 4996 в файле, используйте прагма-директиву warning

using namespace sf;

void changeLevel() {//Функция проверки уровня игры

}

//bool startGame(RenderWindow& window, int& gameLevel) {//Функция начала и продолжения игры
//	sf::CircleShape shape(100.f);
//	shape.setFillColor(sf::Color::Green);
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//		window.clear();
//		window.draw(shape);
//		window.display();
//	}
//}

//void gameRunning(RenderWindow& window, int& gameLevel) {//ф-ция перезагружает игру , если это необходимо
//	if (startGame(window, gameLevel)) { numberLevel++; gameRunning(window, gameLevel); }////если startGame() == true, то вызываем занова ф-цию isGameRunning, которая в свою очередь опять вызывает startGame() 
//}



int main()
{
	RenderWindow window(VideoMode(1920, 1080), "TDSLobodskoy", sf::Style::Fullscreen);
	view.reset(sf::FloatRect(0, 0, 1920, 1080));	//размер "вида" камеры при создании объекта вида камеры. (потом можем менять как хотим) Что то типа инициализации.

	sf::Font font;//шрифт 
	font.loadFromFile("Fonts/Kenney Rocket.ttf");//передаем нашему шрифту файл шрифта

	Image towersImage; //создаем объект Image (изображение) для башен
	towersImage.loadFromFile("images/towers.png"); //загружаем в него файл

	Image enemiesImage; //создаем объект Image (изображение) для врагов
	enemiesImage.loadFromFile("images/enemies.png");

	Image ammunitionImage;//изображение для пули
	ammunitionImage.loadFromFile("images/ammunition.png");//загрузили картинку в объект изображения

	Image mapImage;
	mapImage.loadFromFile("images/mapImages.png");
	Texture textureMap;
	textureMap.loadFromImage(mapImage);
	Sprite spriteMap;
	spriteMap.setTexture(textureMap);

	sf::Clock clock; //Создаем переменную времени, т.о. привязка ко времни (а не  загружености/мощности процессора).
	sf::Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры 
	int gameTime = 0;//объявили игровое время, инициализировали.

	int playerHealth = 20;//Хранит жизни игрока
	bool gameLife = true;//Игра продолжается или уже нет
	int playerScore = 0; //Хранит очки игрока
	int gameLevel = 1;

	Vector2f startPosTower (200,200); //Задаем начальное положение башни
	
	Vector2f startPosEntity(path[0][0], path[0][1]);	//Начальное положение врага исходя их первой точки карты

	std::list<Entity*> entities;//создаю список, сюда буду кидать объекты врагов.
	std::list<Entity*>::iterator it;//итератор чтобы проходить по эл-там списка

	//std::vector<Object> e = lvl.GetObjects("EasyEnemy");//все объекты врага на tmx карте хранятся в этом векторе
	
	Tower towerOne(towersImage, "TowerOne", startPosTower, 58.0, 93.0);
	Enemy people(enemiesImage, "Shooter", startPosEntity, 64.0, 64.0, playerHealth, points, path);


	float dXMouse = 0;//корректировка нажатия мышью по х
	float dYMouse = 0;//по у

	while (window.isOpen())	//(Обязятельно) Пока Окно открыто (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		if (gameLife) gameTime = gameTimeClock.getElapsedTime().asSeconds();
		else view.move(0.1, 0); //игровое время в секундах идёт вперед, пока жив игрок, перезагружать как time его не надо. Оно не обновляет логику игры. 
		clock.restart(); //перезагружает время
		time /= 800; //скорость игры

		Vector2i pixelPosMouse = Mouse::getPosition(window);//забираем коорд курсора
		Vector2f posMouse = window.mapPixelToCoords(pixelPosMouse);//переводим их в игровые (уходим от коорд окна)

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
		}

		viewMap(window, time);	//Вызываю управление камерой//View.h
		towerOne.update(event, posMouse, dXMouse, dYMouse, window, time);
		people.update(time);	
		changeView();	//Опции камеры//в заголовочном файле View.h
		window.setView(view);	//"оживляю" камеру в окне sfml
		window.clear(Color(153,153,80));

		drawMap(spriteMap, window);	//Отрисовка карты

		window.draw(people.sprite);
		window.draw(towerOne.sprite);
		window.display();
	}
	

	return 0;
}